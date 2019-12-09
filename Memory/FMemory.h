#include "..//main.h"

#ifndef FMemory_H
#define FMemory_H

class FMemory
{
public:
	
	struct HandleDisposer
	{
		using pointer = HANDLE;
		void operator()(HANDLE handle) const
		{
			if (handle != NULL || handle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(handle);
			}
		}
	};

	std::unique_ptr<HANDLE, HandleDisposer> m_processHandle;

	using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

	auto GetProcessID(std::string_view process_name) -> std::uint32_t;
	static auto OpenProcessHandle(const std::uint32_t process_id) -> unique_handle;

	template <class T>
	auto read(uintptr_t address)->T {
		T buf;
		ReadProcessMemory(m_processHandle.get(), reinterpret_cast<LPVOID>(address), &buf, sizeof(T), nullptr);
		return buf;
	}


	template <class W>
	auto write(W value, uintptr_t address) -> bool {
		if (WriteProcessMemory(m_processHandle.get(), reinterpret_cast<LPVOID>(address), &value, sizeof(W), nullptr))
			return true;
		else
			return false;
	}

	auto get_module(std::string module)->ULONG64;

	
	auto ReadString(uintptr_t String_address, void* buffer, SIZE_T size) -> void;

};


#endif