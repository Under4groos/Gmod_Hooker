// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"
#include "Include/Modules/LuaLoader.h"
#include "Include/Modules/ChangeName.h"


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

string GetWindowStringText(HWND hwnd)
{
	int len = GetWindowTextLength(hwnd) + 1;
	vector<wchar_t> buf(len);
	GetWindowText(hwnd, &buf[0], len);
	wstring wide = &buf[0];
	string s(wide.begin(), wide.end());
	return s;
}
void Init_ClientJoinGame() {

	set_name(EngineClient, "Dalbaeb Ebobo");

	//ModuleHandles::ClientLuaInterface->RunString("", "", "print(\"Hello world!\")", true, true);
	Console::WriteLog("Duped: ClientLuaInterface ", std::to_string((int)ModuleHandles::ClientLuaInterface));
}


void InitGameEngine() {
	EngineClient = DLLimport::CaptureInterface<IEngineClient>("engine.dll", "VEngineClient013");
	Console::WriteLog("engine.dll -> VEngineClient013", std::to_string((int)EngineClient));


	if (!EngineClient)
		return;

	ModuleHandles::LuaShared_modhandle = GetModuleHandleA("lua_shared.dll");
	Console::WriteLog("lua_shared.dll ", std::to_string((int)ModuleHandles::LuaShared_modhandle));

	if (ModuleHandles::LuaShared_modhandle)
	{
		ModuleHandles::LuaShared_createinter = (CreateInterfaceFn)GetProcAddress(ModuleHandles::LuaShared_modhandle, "CreateInterface");
		Console::WriteLog("LuaShared_createinter -> CreateInterface", std::to_string((int)ModuleHandles::LuaShared_createinter));

		if (ModuleHandles::LuaShared_createinter)
		{
			ModuleHandles::LuaShared = (ILuaShared*)ModuleHandles::LuaShared_createinter(LUASHARED_INTERFACE_VERSION, NULL);
			Console::WriteLog("LuaShared ", std::to_string((int)ModuleHandles::LuaShared));
			
		}
	}

	int w = 0;
	int h = 0;
	bool is_loaded_base_script = false;
	int c = 0;
	string name_app = "";
	while (true)
	{
		if (!EngineClient)
			continue;
		if (EngineClient->is_ingame()) {
			if (is_loaded_base_script == false) {
				
				Console::WriteLog("Connected");


				Sleep(1000);
				if (ModuleHandles::LuaShared)
				{
					ModuleHandles::ClientLuaInterface = ModuleHandles::LuaShared->GetLuaInterface(LuaInterfaceType::LUAINTERFACE_CLIENT);
					Console::WriteLog("ClientLuaInterface ", std::to_string((int)ModuleHandles::ClientLuaInterface));
					if (ModuleHandles::ClientLuaInterface)
					{
						Init_ClientJoinGame();
					}
				}

				is_loaded_base_script = true;
				
			}
			if (c > 20)
			{
				 
				string _name_app = GetWindowStringText(GetForegroundWindow());
				if (name_app != _name_app) {
					set_name(EngineClient, _name_app);
					name_app = _name_app;
				}
				
				c = 0;
			}
		}
		else {
			is_loaded_base_script = false;
		}
		


		 

		/*Console::WriteLog("tick");
		EngineClient->get_screen_size(w, h);
		Console::WriteLog(std::to_string((int)w), std::to_string((int)h));*/

		c++;
		Sleep(1000);
	}


	//set_name(EngineClient, "<void>");

	//lua_load(ModuleHandles::ClientLuaInterface , "");


	//EngineClient->is_ingame()
}


OutThread ThreadUnload() {
	int w, h;
	while (true)
	{
		if (!EngineClient)
			continue;
		Console::WriteLog("tick");



		EngineClient->get_screen_size(w, h);

		Console::WriteLog(std::to_string((int)w), std::to_string((int)h));


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

		//Threadun = CreateThread(NULL, 4096, (LPTHREAD_START_ROUTINE)ThreadUnload, hModule, 0, NULL);


		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:



		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

