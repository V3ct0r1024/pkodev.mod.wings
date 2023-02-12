#pragma once

namespace pkodev { namespace patch {

	inline char CCharacter__FrameMove[] = {
		char(0x51), char(0x8B), char(0xCE), char(0xE8),
		char(0x00), char(0x00), char(0x00), char(0x00), // bool CCharacter::GetIsFly() offset
		char(0x59), char(0x84), char(0xC0), char(0x74),
		char(0x16), char(0x90), char(0x90), char(0x90),
		char(0x90), char(0x90), char(0x90), char(0x90),
		char(0x90), char(0x90), char(0x90), char(0x90),
		char(0x90), char(0x90), char(0x90)
	};

	inline char CCharacter__PlayPose[] = {
		char(0x51), char(0x8B), char(0xCE), char(0xE8),
		char(0x00), char(0x00), char(0x00), char(0x00), // bool CCharacter::GetIsFly() offset
		char(0x59), char(0x84), char(0xC0), char(0x74),
		char(0x40), char(0x90), char(0x90), char(0x90),
		char(0x90), char(0x90), char(0x90), char(0x90),
		char(0x90)
	};

	inline char CCharacter__FrameMove_Backup[sizeof(CCharacter__FrameMove)]{ 0x00 };
	inline char CCharacter__PlayPose_Backup[sizeof(CCharacter__PlayPose)]{ 0x00 };

	constexpr unsigned int CCharacter__FrameMove_Offset = 0x04;
	constexpr unsigned int CCharacter__PlayPose_Offset = 0x04;

	constexpr unsigned int Offset(unsigned int targetAddress,
		unsigned int getIsFlyAddress, unsigned int getIsFlyOffset)
	{
		return ( getIsFlyAddress - targetAddress - (4u + getIsFlyOffset) );
	}

} }