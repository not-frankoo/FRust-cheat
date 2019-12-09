#include "FMemory.h"


FMemory mem;

auto FMemory::GetProcessID(std::string_view process_name) -> std::uint32_t {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}

auto FMemory::OpenProcessHandle(const std::uint32_t process_id)->unique_handle {
	if (process_id == 0)
		return nullptr;

	unique_handle processhandle(OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ, false, process_id));

	if (processhandle.get() == nullptr)
		return nullptr;

	return processhandle;
}


auto FMemory::get_module(std::string module) -> ULONG64 {
	std::uint32_t pid = mem.GetProcessID(module);
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	auto entry = MODULEENTRY32{};
	entry.dwSize = sizeof(entry);

	while (Module32Next(snapshot, &entry)) {
		if (!strcmp(entry.szModule, module.c_str())) {
			//std::cout << "Found " + module + " at: 0x" << std::hex << reinterpret_cast<ULONG64>(entry.modBaseAddr) << std::dec << std::endl;

			CloseHandle(snapshot);
			return reinterpret_cast<ULONG64>(entry.modBaseAddr);
		}
	}

	CloseHandle(snapshot);
	return 0;
}

auto FMemory::ReadString(uintptr_t String_address, void* buffer, SIZE_T size) -> void {
	ReadProcessMemory(m_processHandle.get(), reinterpret_cast<LPVOID>(String_address), buffer, size, nullptr);
}