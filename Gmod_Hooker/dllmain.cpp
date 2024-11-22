// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"
#include "Include/Modules/GameILuaInterface.h"
 
 
HwndThread Thread, Threadun;



HMODULE hModule_dll;
 



 
void Init_ClientJoinGame() {




 
	GameILuaInterface::SetOwnerName("[XUILO][CODER][C++/C]Dalbaeb Ebobo");
	
	GameILuaInterface::ConsolePrint( "Start game");
	
	GameILuaInterface::RunScript(LuaInterfaceType::LUAINTERFACE_CLIENT, "concommand.Add('run_c', function(a, b, c, d) RunString(d, '', true) end)");
	GameILuaInterface::RunScript(LuaInterfaceType::LUAINTERFACE_MENU, "concommand.Add('run_m', function(a, b, c, d) RunString(d, '', true) end)");

	/*GameILuaInterface::LUAINTERFACE_CLIENT->RunString("", "", 
		"concommand.Add('run_c', function(a, b, c, d) RunString(d, '', true) end)", true, true);*/
	/*GameILuaInterface::LUAINTERFACE_MENU->RunString("", "",
		"concommand.Add('run_m', function(a, b, c, d) RunString(d, '', true) end)", true, true);*/

	//GameILuaInterface::ConsolePrint( std::to_string(GameILuaInterface::GetPlayerCount()).c_str() );
	
	GameILuaInterface::InitAll_RegisterFunction();
	
}


void InitGameEngine() {
 
	GameILuaInterface::Init();

	bool is_loaded_base_script = false;

	string name_app = "";
	while (true)
	{
		if (!GameILuaInterface::EngineClient)
			continue;
		if (GameILuaInterface::EngineClient->is_ingame() && GameILuaInterface::LuaShared) {
			if (is_loaded_base_script == false) {

				Console::WriteLog("Connected");
				Sleep(1000);
				 
				GameILuaInterface::Init_Client_or_Menu();
				if (GameILuaInterface::LUAINTERFACE_CLIENT)
				{
					Init_ClientJoinGame();
						 
				}
				 

				is_loaded_base_script = true;

			}
		}
		else {
			is_loaded_base_script = false;
		}

		Sleep(1000);
	}

}

//GMOD_MODULE_OPEN()
//{
//	GameILuaInterface::InitAll_RegisterFunction();
//
//	return  0;
//}
 



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
	if (GameILuaInterface::IsValid_Engine()) {
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
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		Thread = CreateThread(NULL, 4096, (LPTHREAD_START_ROUTINE)ThreadInit, hModule, 0, NULL);
	return TRUE;
}

