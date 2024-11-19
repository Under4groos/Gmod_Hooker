// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"
#include "Include/GarrysMod/Lua/Chanel.h"

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

	int w, h;
	EngineClient->get_screen_size(w, h);
	Console::WriteLog(std::to_string((int)w), std::to_string((int)h));


	Channel* ch = EngineClient->get_net_channel();
	if (ch) {
		ch->set_name("[C++][Coder] Underko");
	}
	/*auto id_ = EngineClient->get_local_player();
	player_info_t info{ 0 };
	EngineClient->get_player_info(id_, &info);
	Console::WriteLog(info.name, std::to_string((int)info.id));*/


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





	//ModuleHandles::ClientLuaInterface->RunString("RunString", "", "print(123)", true, true);



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
	if (AllocConsole())
	{
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
	}



	Console::WriteLog("Show console", "");
	Console::WriteLog("Thread id:", std::to_string((int)Thread));


	if (GetModuleHandleA("engine.dll")) {
		InitGameEngine();
	}

	FreeLibraryAndExitThread(hModule_dll, 0);
	Console::WriteLog("FreeLibraryAndExitThread");
	return 0;
}




BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	hModule_dll = hModule;
	DisableThreadLibraryCalls(hModule);
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

