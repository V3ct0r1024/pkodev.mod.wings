#pragma once

namespace pkodev { namespace address {

	// Game.exe 0 (1222073761)
	namespace GAME_13X_0
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A3310;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A3DDF;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4363;
	}

	// Game.exe 1 (1243412597)
	namespace GAME_13X_1
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A3420;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A3EEF;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4473;
	}

	// Game.exe 2 (1252912474)
	namespace GAME_13X_2
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A34A0;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A3F8F;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4513;
	}

	// Game.exe 3 (1244511158)
	namespace GAME_13X_3
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A34B0;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A3F7F;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4503;
	}

	// Game.exe 4 (1585009030)
	namespace GAME_13X_4
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A36F0;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A41BF;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4743;
	}

	// Game.exe 5 (1207214236)
	namespace GAME_13X_5
	{
		// bool CCharacter::GetIsFly()
		const unsigned int CCharacter__GetIsFly = 0x004A3110;

		// Patch 1 address
		// [8B 86 0C 0D 00 00 3D 80 00 00 00 7C 16 3D 8C 00 00 00 7F 0F 3D 87 00 00 00 74 08]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 16 90 90 90 90 90 90 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__FrameMove_Patch = 0x004A3C11;

		// Patch 2 address
		// [3D 80 00 00 00 7C 46 3D 8C 00 00 00 7F 3F 3D 87 00 00 00 74 38]
		// ->
		// [51 8B CE E8 XX XX XX XX 59 84 C0 74 40 90 90 90 90 90 90 90 90]
		const unsigned int CCharacter__PlayPose_Patch = 0x004A4193;
	}

} }