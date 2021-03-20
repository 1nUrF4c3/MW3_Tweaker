//=====================================================================================

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

//=====================================================================================

class cMemory
{
public:
	
	template<typename TYPE>
	static BOOL MemRead(const char* process, DWORD_PTR address, TYPE* buffer)
	{
		BOOL bReturn = FALSE;

		if (auto hProcess{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, EnumProcess(process)) }; hProcess)
		{
			bReturn = ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), reinterpret_cast<LPVOID>(buffer), sizeof(TYPE), NULL);

			CloseHandle(hProcess);
		}

		return bReturn;
	}

	template<typename TYPE>
	static BOOL MemWrite(const char* process, DWORD_PTR address, TYPE buffer)
	{
		BOOL bReturn = FALSE;

		if (auto hProcess{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, EnumProcess(process)) }; hProcess)
		{
			bReturn = WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), reinterpret_cast<LPCVOID>(&buffer), sizeof(TYPE), NULL);

			CloseHandle(hProcess);
		}

		return bReturn;
	}

private:

	static DWORD EnumProcess(const char* name)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 ProcessEntry = { NULL };
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

		for (auto bSuccess{ Process32First(hSnapshot, &ProcessEntry) }; bSuccess; bSuccess = Process32Next(hSnapshot, &ProcessEntry))
		{
			if (!strcmp(ProcessEntry.szExeFile, name))
				return ProcessEntry.th32ProcessID;
		}

		return NULL;
	}
};

//=====================================================================================