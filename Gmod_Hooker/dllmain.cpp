// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"

HwndThread Thread, Threadun;

IEngineClient* EngineClient;

HMODULE hModule_dll;
ILuaShared* LuaShared;

namespace ModuleHandles {
	ILuaShared* LuaShared;
	HMODULE LuaShared_modhandle;

	CreateInterfaceFn LuaShared_createinter;



	ILuaInterface* ClientLuaInterface;
}





void InitGameEngine() {
	EngineClient = DLLimport::CaptureInterface<IEngineClient>("engine.dll", "VEngineClient013");
	Console::WriteLog("engine.dll -> VEngineClient013", std::to_string((int)EngineClient));

	if (!EngineClient)
		return;



	ModuleHandles::LuaShared_modhandle = GetModuleHandleA("lua_shared.dll");
	Console::WriteLog("lua_shared.dll ", std::to_string((int)ModuleHandles::LuaShared_modhandle));

	if (!ModuleHandles::LuaShared_modhandle)
		return;


	ModuleHandles::LuaShared_createinter = (CreateInterfaceFn)GetProcAddress(ModuleHandles::LuaShared_modhandle, "CreateInterface");
	Console::WriteLog("LuaShared_createinter -> CreateInterface", std::to_string((int)ModuleHandles::LuaShared_createinter));

	if (!ModuleHandles::LuaShared_createinter)
		return;

	ModuleHandles::LuaShared = (ILuaShared*)ModuleHandles::LuaShared_createinter(LUASHARED_INTERFACE_VERSION, NULL);
	Console::WriteLog("LuaShared ", std::to_string((int)ModuleHandles::LuaShared));
	if (!ModuleHandles::LuaShared)
		return;

	ModuleHandles::ClientLuaInterface = ModuleHandles::LuaShared->GetLuaInterface(LuaInterfaceType::LUAINTERFACE_CLIENT);
	Console::WriteLog("ClientLuaInterface ", std::to_string((int)ModuleHandles::ClientLuaInterface));
	if (!ModuleHandles::ClientLuaInterface)
		return;


	ModuleHandles::ClientLuaInterface->RunString("RunString", "", "print(123)", true, true);



}


OutThread ThreadUnload() {
	while (true)
	{
		Console::WriteLog("tick");
		if (!GetModuleHandleA("Gmod_Hooker.dll")) {
			FreeConsole();
			break;
		}
		Sleep(1000);
	}
	return 0;
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

		Thread = CreateThread(NULL, 4096, (LPTHREAD_START_ROUTINE)ThreadInit, hModule, 0, NULL);




		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:



		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

