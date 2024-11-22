// CallFunction.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <filesystem>
namespace fs = std::filesystem;


using namespace std;
BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

void read() {
	int i;
	cin >> i;
}


int main()
{
	HWND hwnd = FindWindowA("Valve001", NULL);
	std::cout << hwnd << endl;
	if (is_main_window(hwnd)) {
		DWORD checkProcessID = 0;
		GetWindowThreadProcessId(hwnd, &checkProcessID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, checkProcessID);
		if (handle)
		{
			HMODULE lphModule[1024];
			DWORD cbNeeded;
			if (EnumProcessModules(handle, lphModule, sizeof(lphModule), &cbNeeded)) {
				int coub_modules = cbNeeded / sizeof(HMODULE);

				std::cout << coub_modules << endl;

				for (int i = 0; i < coub_modules; i++)
				{
					char szModName[MAX_PATH];
					DWORD szModNameSize = sizeof(szModName);
					if (GetModuleFileNameExA(handle, lphModule[i], szModName, szModNameSize))
					{
					 
						std::cout << lphModule[i] << " " << fs::path(szModName).filename()  << endl;
						 
					}
				}

			}
			CloseHandle(handle);
		}
		
		
	}


	read();
}

