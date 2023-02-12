#pragma once
#include "address.h"

namespace pkodev {

	class import final
	{
		public:
			// bool CCharacter::GetIsFly()
			typedef bool(__thiscall* CCharacter__GetIsFly__Ptr)(void*);
			static CCharacter__GetIsFly__Ptr CCharacter__GetIsFly;
	};

}