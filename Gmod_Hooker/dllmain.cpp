// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Headers.h"
#include "Include/Modules/GameILuaInterface.h"
#include "Include/Modules/LuaLoader.h"
 
HwndThread Thread, Threadun;



HMODULE hModule_dll;
 

//const char* glua_code = R"V0G0N(        
//G_ = G_ or {}
//if(G_.file_read == nil) then
//	G_.file_read =  file.Read
//end
//file.Read = function(filename, path)
//	print("[file.Read]: " .. path.."/"..filename)
//	return G_.file_read(filename, path)
//end
//concommand.Add("run_c_f", function(ply, cmd, args, str)
//	if( table.Count(args) >= 1) then
//		local str_code = file.Read(args[1], "DATA")
//		if(string != "") then
//			RunString(str_code)
//			print("Run code:\n" .. str_code)
//		else
//			print("error code! " ..  args[1])
//		end
//	end
//end)
//)V0G0N";

const char* glua_code = R"V0G0N(        
concommand.Add("run_c_f", function(ply, cmd, args, str)
	if( table.Count(args) >= 1) then
		local str_code = file.Read(args[1], "DATA")
		if(string != "") then
			RunString(str_code)
			print("Run code:\n" .. str_code)
		else
			print("error code! " ..  args[1])
		end
	end
end)

function GetEyeTrace()
	return  LocalPlayer():GetEyeTrace()
end
function GetEyeTrace_Entity()
	return  LocalPlayer():GetEyeTrace()["Entity"]
end
)V0G0N";

void Init_ClientJoinGame() {




 
	GameILuaInterface::SetOwnerName("<>");
	
	
	
	GameILuaInterface::RunScript(LuaInterfaceType::LUAINTERFACE_CLIENT, "concommand.Add('run_c', function(a, b, c, d) RunString(d, '', true) end)");
	GameILuaInterface::RunScript(LuaInterfaceType::LUAINTERFACE_MENU, "concommand.Add('run_m', function(a, b, c, d) RunString(d, '', true) end)");


	GameILuaInterface::RunScript(LuaInterfaceType::LUAINTERFACE_CLIENT, glua_code);
	
	//lua_load(GameILuaInterface::LUAINTERFACE_CLIENT, "D:\Steam\steamapps\common\GarrysMod\garrysmod\lua\main.lua");
	
	GameILuaInterface::ConsolePrint("Start game");
	
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

