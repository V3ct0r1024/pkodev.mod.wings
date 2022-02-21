#pragma once
#include "address.h"
#include "structure.h"

namespace pkodev
{
	namespace pointer
	{
		// bool CCharacter::GetIsFly()
		typedef bool(__thiscall* CCharacter__GetIsFly__Ptr)(void*);
		CCharacter__GetIsFly__Ptr CCharacter__GetIsFly = (CCharacter__GetIsFly__Ptr)(void*)(address::MOD_EXE_VERSION::CCharacter__GetIsFly);
	}
}