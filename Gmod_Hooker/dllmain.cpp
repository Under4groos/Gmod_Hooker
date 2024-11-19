// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"

HwndThread Thread;

IEngineClient* EngineClient;
HMODULE hModule_dll;


void InitGameEngine() {
	EngineClient = DLLimport::CaptureInterface<IEngineClient>("engine.dll", "VEngineClient013");
	Sleep(3000);
	Console::WriteLog("engine.dll -> VEngineClient013", std::to_string((int)EngineClient));
}


OutThread ThreadInit() {
	if (!AllocConsole())
		return 0;
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	Console::WriteLog("Show console", "");
	Console::WriteLog("Thread id:", std::to_string((int)Thread));


	if (GetModuleHandleA("engine.dll")) {
		InitGameEngine();	
	}
	else {
		FreeLibrary(hModule_dll);
	}
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	hModule_dll = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		Thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadInit, NULL, 0, NULL);



		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

