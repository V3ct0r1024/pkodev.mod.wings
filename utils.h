#pragma once
#include <iostream>
#include <Windows.h>

#include "loader.h"


namespace pkodev { namespace utils {

	template <DWORD Address>
	bool patch(const char* data, unsigned int length, char* backup = nullptr)
	{
		DWORD access = PAGE_EXECUTE_READWRITE;
		HANDLE proc = GetCurrentProcess();

		if (VirtualProtect(reinterpret_cast<LPVOID>(Address), length, access, &access) == FALSE) {
			return false;
		}

		if ((backup != nullptr) && (ReadProcessMemory(proc, reinterpret_cast<LPVOID>(Address),
			reinterpret_cast<LPVOID>(backup), length, nullptr) == FALSE)) {
			return false;
		}

		if (WriteProcessMemory(proc, reinterpret_cast<LPVOID>(Address),
			reinterpret_cast<LPCVOID>(data), length, nullptr) == FALSE) {
			return false;
		}

		if (VirtualProtect(reinterpret_cast<LPVOID>(Address), length, access, &access) == FALSE) {
			return false;
		}

		return true;
	}

	template<typename T, int Offset = 0x00>
	T get(void* ptr) {
		return *reinterpret_cast<T*>(reinterpret_cast<int>(ptr) + Offset);
	}

	template<typename T, int Offset = 0x00>
	void set(void* ptr, const T& data) {
		*reinterpret_cast<T*>(reinterpret_cast<int>(ptr) + Offset) = data;
	}

	class log final
	{
		public:
			log(std::ostream& out = std::clog) : m_out(out) {
				m_out << '[' << TOSTRING(MOD_NAME) << "] ";
			}

			~log() { m_out << std::endl; }

			template<typename T>
			log& operator<<(const T& message) {
				m_out << message;
				return *this;
			}

		private:
			std::ostream& m_out;
	};

} }


