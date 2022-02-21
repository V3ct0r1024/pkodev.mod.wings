#include <Windows.h>
#include <detours.h>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "loader.h"
#include "address.h"
#include "pointer.h"
#include "hook.h"
#include "structure.h"

// Disable integer overflow warning
#pragma warning(disable:26454)

namespace pkodev
{
    // Patch 1 bytes
    char patch__0[] = { 
        (char)0x51, (char)0x8B, (char)0xCE, (char)0xE8, 
        (char)0x00, (char)0x00, (char)0x00, (char)0x00, // bool CCharacter::GetIsFly() offset
        (char)0x59, (char)0x84, (char)0xC0, (char)0x74, 
        (char)0x16, (char)0x90, (char)0x90, (char)0x90, 
        (char)0x90, (char)0x90, (char)0x90, (char)0x90, 
        (char)0x90, (char)0x90, (char)0x90, (char)0x90, 
        (char)0x90, (char)0x90, (char)0x90 
    };

    // Patch 2 bytes
    char patch__1[] = { 
        (char)0x51, (char)0x8B, (char)0xCE, (char)0xE8, 
        (char)0x00, (char)0x00, (char)0x00, (char)0x00, // bool CCharacter::GetIsFly() offset
        (char)0x59, (char)0x84, (char)0xC0, (char)0x74, 
        (char)0x40, (char)0x90, (char)0x90, (char)0x90, 
        (char)0x90, (char)0x90, (char)0x90, (char)0x90, 
        (char)0x90 
    };

    // Patch 1 backup bytes
    char patch__backup__0[sizeof(patch__0)]{ 0x00 };

    // Patch 2 backup bytes
    char patch__backup__1[sizeof(patch__1)]{ 0x00 };

    // List of wings IDs
    std::vector<unsigned int> wings_ids;


    // Load settings from file
    void settings(const std::string& path);

    // Write a sequence of bytes to the proccess memory
    void patch(unsigned int address, const char* bytes, unsigned int length, char *backup);
}


// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Reserve some memory for wings ids
    pkodev::wings_ids.reserve(32);

    // Load settings from file
    char buf[MAX_PATH]{ 0x00 };
    sprintf_s(buf, sizeof(buf), "%s\\%s.cfg", path, TOSTRING(MOD_NAME));
    pkodev::settings( std::string(buf) );

    // Make patches
    {
        // Patch 1
        {
            // Calculate offset 1
            unsigned int offset__0 = pkodev::address::MOD_EXE_VERSION::CCharacter__GetIsFly
                - pkodev::address::MOD_EXE_VERSION::patch__0 - 8;

            // Write offset 1 to patch 1 bytes
            std::memcpy(reinterpret_cast<void*>(pkodev::patch__0 + 0x04),
                reinterpret_cast<const void*>(&offset__0), sizeof(const void*));

            // Write patch 1
            pkodev::patch(pkodev::address::MOD_EXE_VERSION::patch__0, pkodev::patch__0,
                sizeof(pkodev::patch__0), pkodev::patch__backup__0);
        }

        // Patch 2
        {
            // Calculate offset 2
            unsigned int offset__1 = pkodev::address::MOD_EXE_VERSION::CCharacter__GetIsFly
                - pkodev::address::MOD_EXE_VERSION::patch__1 - 8;

            // Write offset 2 to patch 2 bytes
            std::memcpy(reinterpret_cast<void*>(pkodev::patch__1 + 0x04),
                reinterpret_cast<const void*>(&offset__1), sizeof(const void*));

            // Write patch 2
            pkodev::patch(pkodev::address::MOD_EXE_VERSION::patch__1, pkodev::patch__1,
                sizeof(pkodev::patch__1), pkodev::patch__backup__1);
        }
    }

    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CCharacter__GetIsFly, pkodev::hook::CCharacter__GetIsFly);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CCharacter__GetIsFly, pkodev::hook::CCharacter__GetIsFly);
    DetourTransactionCommit();

    // Rollback patches
    {
        // Patch 2
        pkodev::patch(pkodev::address::MOD_EXE_VERSION::patch__1, pkodev::patch__backup__1,
            sizeof(pkodev::patch__1), nullptr);

        // Patch 1
        pkodev::patch(pkodev::address::MOD_EXE_VERSION::patch__0, pkodev::patch__backup__0,
            sizeof(pkodev::patch__0), nullptr);
    }
}

// bool CCharacter::GetIsFly()
bool __fastcall pkodev::hook::CCharacter__GetIsFly(void* This, void* NotUsed)
{
    // Get wings item ID
    const unsigned int wings_id = *reinterpret_cast<unsigned int*>(
        reinterpret_cast<unsigned int>(This) + 0xD0C
    );

    // Check that wings are equipped
    if (wings_id != 0)
    {
        // Search ID in the wings list
        const auto it = std::find_if
        (
            pkodev::wings_ids.begin(),
            pkodev::wings_ids.end(),
            [&wings_id](unsigned int id_) -> bool
            {
                return (wings_id == id_);
            }
        );

        // Check that ID is found
        if (it != pkodev::wings_ids.end())
        {
            return true;
        }
    }
    
    // Call the original method bool CCharacter::GetIsFly()
    return pkodev::pointer::CCharacter__GetIsFly(This);
}

// Load settings from file
void pkodev::settings(const std::string& path)
{
    // Cleanup the old list
    pkodev::wings_ids.clear();

    // Trying open file
    std::ifstream file(path, std::ios::in);

    // Check that file is open
    if (file.is_open() == false)
    {
        // Error!
        return;
    }

    // Read file line by line
    for (std::string line{""}; std::getline(file, line); )
    {
        // Remove spaces from string
        line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

        // Check that line is not empty
        if (line.empty() == true)
        {
            // Skip the line
            continue;
        }

        // Move line to stream
        std::stringstream ss(line);

        // Split line by comma
        for (std::string value{ "" }; std::getline(ss, value, ','); )
        {
            // Check that value is not empty
            if (value.empty() == true)
            {
                // Skip the value
                continue;
            }

            // Check that value consists only of digits
            if (value.find_first_not_of("0123456789") != std::string::npos)
            {
                // Skip the value
                continue;
            }

            // Wings item ID
            unsigned int id = 0;

            // std::string -> unsigned int
            try
            {
                // Convert value to unsigned int 
                id = std::stoul(value);
            }
            catch (...) // std::invalid_argument, std::out_of_range
            {
                // Conversion error?!
                continue;
            }
            
            // Search ID in the wings list
            const auto it = std::find_if
            (
                pkodev::wings_ids.begin(),
                pkodev::wings_ids.end(),
                [&id](unsigned int id_) -> bool
                {
                    return (id == id_);
                }
            );

            // Check that ID is not already exists in the list
            if (it == pkodev::wings_ids.end())
            {
                // Add ID to the list
                pkodev::wings_ids.push_back(id);
            }
        }
    }

    // Close the file
    file.close();
}

// Write a sequence of bytes to the proccess memory
void pkodev::patch(unsigned int address, const char* bytes, unsigned int length, char* backup)
{
    // Access type
    DWORD access = PAGE_EXECUTE_READWRITE;

    // Change the access protection of the proccess
    VirtualProtect(reinterpret_cast<LPVOID>(address), length, access, &access);

    // Save backup bytes
    if (backup != nullptr)
    {
        ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address),
            reinterpret_cast<LPVOID>(backup), length, nullptr);
    }

    // Write patch bytes
    WriteProcessMemory( GetCurrentProcess(), reinterpret_cast<LPVOID>(address),
        reinterpret_cast<LPCVOID>(bytes), length, nullptr);

    // Rollback the access protection of the proccess
    VirtualProtect(reinterpret_cast<LPVOID>(address), length, access, &access);
}