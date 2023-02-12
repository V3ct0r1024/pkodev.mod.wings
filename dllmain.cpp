#include <Windows.h>
#include <detours.h>

#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_set>

#include "loader.h"
#include "address.h"
#include "import.h"
#include "hook.h"
#include "utils.h"
#include "patch.h"

using namespace pkodev;


using WingsSet = std::unordered_set<unsigned int>;
WingsSet wingsSet;

bool LoadWingsSet(const std::filesystem::path& path, WingsSet& out);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    return TRUE;
}

void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

void Start(const char* path)
{
	const auto wingsSetPath = std::filesystem::path(path)
       / std::string(TOSTRING(MOD_NAME)).append(".cfg");

    if (LoadWingsSet(wingsSetPath, wingsSet) == false) 
    {
        utils::log(std::cerr) << "Failed to load wings IDs from the file " << wingsSetPath.string() << '!';
        utils::log(std::cerr) << "Mod loading aborted.";
        return;
    }

    utils::log() << "Loaded " << wingsSet.size() << " wings IDs!";

    if (wingsSet.empty() == true) { return; }

    constexpr auto offsetFrameMove = patch::Offset(address::MOD_EXE_VERSION::CCharacter__FrameMove_Patch,
        address::MOD_EXE_VERSION::CCharacter__GetIsFly, patch::CCharacter__FrameMove_Offset);
	constexpr auto offsetPlayPose = patch::Offset(address::MOD_EXE_VERSION::CCharacter__PlayPose_Patch,
        address::MOD_EXE_VERSION::CCharacter__GetIsFly, patch::CCharacter__PlayPose_Offset);

    utils::set<unsigned int, patch::CCharacter__FrameMove_Offset>(patch::CCharacter__FrameMove, offsetFrameMove);
	utils::set<unsigned int, patch::CCharacter__PlayPose_Offset>(patch::CCharacter__PlayPose, offsetPlayPose);


    if (utils::patch<address::MOD_EXE_VERSION::CCharacter__FrameMove_Patch>(patch::CCharacter__FrameMove,
			sizeof(patch::CCharacter__FrameMove), patch::CCharacter__FrameMove_Backup) == false) {
        utils::log(std::cerr) << "Failed to patch CCharacter::FrameMove()!";
        wingsSet.clear();
        return;
    }

    if (utils::patch<address::MOD_EXE_VERSION::CCharacter__PlayPose_Patch>(patch::CCharacter__PlayPose,
			sizeof(patch::CCharacter__PlayPose), patch::CCharacter__PlayPose_Backup) == false) {
        utils::log(std::cerr) << "Failed to patch CCharacter::PlayPose()!";
        utils::patch<address::MOD_EXE_VERSION::CCharacter__FrameMove_Patch>(patch::CCharacter__FrameMove_Backup,
            sizeof(patch::CCharacter__FrameMove_Backup));
        wingsSet.clear();
        return;
    }

    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<PVOID*>(&import::CCharacter__GetIsFly), reinterpret_cast<PVOID>(&hook::CCharacter__GetIsFly));
    DetourTransactionCommit();
}

void Stop()
{
    if (wingsSet.empty() == true) { return; }

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(reinterpret_cast<PVOID*>(&import::CCharacter__GetIsFly), reinterpret_cast<PVOID>(&hook::CCharacter__GetIsFly));
    DetourTransactionCommit();

    utils::patch<address::MOD_EXE_VERSION::CCharacter__FrameMove_Patch>(patch::CCharacter__FrameMove_Backup,
        sizeof(patch::CCharacter__FrameMove_Backup));

    utils::patch<address::MOD_EXE_VERSION::CCharacter__PlayPose_Patch>(patch::CCharacter__PlayPose_Backup,
        sizeof(patch::CCharacter__PlayPose_Backup));
}

// bool CCharacter::GetIsFly()
bool __fastcall hook::CCharacter__GetIsFly(void* This, void*)
{
    const auto wingsId = utils::get<unsigned int, 0x0D0C>(This);

    if ( (wingsId != 0) && (wingsSet.contains(wingsId) == true) )  {
        return true;
    }

    return import::CCharacter__GetIsFly(This);
}

bool LoadWingsSet(const std::filesystem::path& path, WingsSet& out)
{
    out.clear();

    std::ifstream file(path, std::ios_base::in);
    if (file.is_open() == false) {
        utils::log(std::cerr) << "Failed to open file " << path.string() << '!';
        return false;
    }

    unsigned int id = 0;
    while (file >> id) {
        out.insert(id);
    }

    file.close();

    return true;
}