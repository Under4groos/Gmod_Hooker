// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"
#include "Include/Modules/GameILuaInterface.h"
HwndThread Thread, Threadun;



HMODULE hModule_dll;
 


LUA_FUNCTION(MyFirstFunction)
{
	 

	double number = (LUA -> GetNumber(1));  // Получить первый аргумент 

	if (number > 9.0) // Если число больше 9... 
	{
		LUA -> PushBool(true);  // push true... 
	}
	else
	{
		LUA -> PushBool(false);  // в противном случае push false. 
	}

	return  1;  // Сколько значений мы возвращаем 
}



//void regfunc() {
//	ModuleHandles::ClientLuaInterface->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);  // Помещаем глобальную таблицу 
//	ModuleHandles::ClientLuaInterface->PushCFunction(MyFirstFunction);  // Помещаем нашу функцию 
//	ModuleHandles::ClientLuaInterface->SetField(-2, "MyFirstFunction");  // Устанавливаем MyFirstFunction в lua в нашу функцию C++ 
//	ModuleHandles::ClientLuaInterface->Pop();  // Помещаем глобальную таблицу из стека 
//	Console::WriteLog("GMOD_MODULE_OPEN", std::to_string((int)ModuleHandles::ClientLuaInterface));
//}
 
 
void Init_ClientJoinGame() {

	GameILuaInterface::SetOwnerName("[XUILO][CODER][C++/C]Dalbaeb Ebobo");



	/*std::string script = "";

	script += " concommand.Add( \"rc\", function( ply, cmd, args, str ) ";
	script += " RunString(str) ";
	script += " end)  ";

	regfunc();

	ModuleHandles::ClientLuaInterface->RunString("", "", script.c_str(), true, true);
	Console::WriteLog("Duped: ClientLuaInterface ", std::to_string((int)ModuleHandles::ClientLuaInterface));


	 
	GConsole::print(ModuleHandles::ClientLuaInterface, "Start game");
	 


	 
	ModuleHandles::VGUI_LuaInterface->RunString("", "", "concommand.Add('rm', function(a, b, c, d) RunString(d, '', true) end)", true, true);*/
}


void InitGameEngine() {
 
	GameILuaInterface::Init();

	bool is_loaded_base_script = false;

	string name_app = "";
	while (true)
	{
		if (!GameILuaInterface::IsValid_Engine())
			continue;
		if (GameILuaInterface::EngineClient->is_ingame()) {
			if (is_loaded_base_script == false) {

				Console::WriteLog("Connected");
				Sleep(1000);
				if (GameILuaInterface::IsValid_LuaShared())
				{
					GameILuaInterface::Init_Client_or_Menu();
					if (GameILuaInterface::IsValid_LUAINTERFACE(LuaInterfaceType::LUAINTERFACE_CLIENT))
					{
						Init_ClientJoinGame();
						 
					}
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

