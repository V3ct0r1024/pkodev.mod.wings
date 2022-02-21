#pragma once
#include "structure.h"

namespace pkodev
{
	namespace hook
	{
		// bool CCharacter::GetIsFly()
		bool __fastcall CCharacter__GetIsFly(void* This, void* NotUsed);
	}
}