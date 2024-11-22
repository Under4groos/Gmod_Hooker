#pragma once
#include "../../Headers.h"

namespace GameILuaInterface {

	void InitAll_RegisterFunction();

	IEngineClient* EngineClient;
	CreateInterfaceFn LuaShared_CreateInterface;
	ILuaShared* LuaShared;

	ILuaInterface* LUAINTERFACE_CLIENT;
	ILuaInterface* LUAINTERFACE_MENU;

#pragma region base_functions
	void ___ConsolePrint(ILuaInterface* LUA, const char* text) {
		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Push the global table
		LUA->GetField(-1, "print"); // Get the print function
		LUA->PushString(text); // Push our argument
		LUA->Call(1, 0); // Call the function
		LUA->Pop();
	}
	bool IsValid_Engine() {
		return GetModuleHandleA("engine.dll");
	}
	bool IsValid_LuaShared() {
		return LuaShared;
	}
	bool IsValid_LUAINTERFACE(LuaInterfaceType type) {
		if (type == LuaInterfaceType::LUAINTERFACE_CLIENT)
			return LUAINTERFACE_CLIENT;
		if (type == LuaInterfaceType::LUAINTERFACE_MENU)
			return LUAINTERFACE_MENU;
	}
#pragma endregion


	void Init(  ) {
		EngineClient = DLLimport::CaptureInterface<IEngineClient>("engine.dll", "VEngineClient013");
		Console::WriteLog("engine.dll -> VEngineClient013", std::to_string((int)EngineClient));


		LuaShared_CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("lua_shared.dll"), "CreateInterface");
		
		if (LuaShared_CreateInterface) {
			LuaShared = (ILuaShared*)LuaShared_CreateInterface(LUASHARED_INTERFACE_VERSION, NULL);
			Console::WriteLog("LuaShared", std::to_string((int)LuaShared));
		}
			



	}



	void SetOwnerName(std::string_view name) {
		if (!EngineClient)
		{
			Console::WriteLog("[CL] Error EngineClient");
			return;
		}
			
		Channel* ch = EngineClient->get_net_channel();
		if (ch) {
			ch->set_name(name);
		}
		else {
			Console::WriteLog("[CL] Error Channel");
		}
	}
	void ConsolePrint( const char* text) {
		if (!IsValid_LUAINTERFACE(LuaInterfaceType::LUAINTERFACE_CLIENT))
			return;
		
		___ConsolePrint(LUAINTERFACE_CLIENT, text);
		Console::WriteLog("[CL]", text);
	}

	
	void RunScript(LuaInterfaceType type , const char* glua_code) {

		 
		switch (type)
		{
		case LuaInterfaceType::LUAINTERFACE_CLIENT:

			LUAINTERFACE_CLIENT->RunString("", "", glua_code, true, true);
			break;
		case LuaInterfaceType::LUAINTERFACE_SERVER:
			break;
		case LuaInterfaceType::LUAINTERFACE_MENU:
			LUAINTERFACE_MENU->RunString("", "", glua_code, true, true);
			break;
		default:
			break;
		}
	}

	void Init_Client_or_Menu() {
		if (!LuaShared)
			return;
		LUAINTERFACE_CLIENT = LuaShared->GetLuaInterface(LuaInterfaceType::LUAINTERFACE_CLIENT);
		LUAINTERFACE_MENU = LuaShared->GetLuaInterface(LuaInterfaceType::LUAINTERFACE_MENU);


		Console::WriteLog("Lua CLIENT", std::to_string((int)LUAINTERFACE_CLIENT));
		Console::WriteLog("Lua _MENU", std::to_string((int)LUAINTERFACE_MENU));




	}

	 
	int GetPlayerCount() {
		int players(0);
		LUAINTERFACE_CLIENT->GetField(GarrysMod::Lua::SPECIAL_GLOB, "player");
		LUAINTERFACE_CLIENT->GetField(-1, "GetCount");
		LUAINTERFACE_CLIENT->Call(0, 1);
		players = (int)LUAINTERFACE_CLIENT->GetNumber(-1);
		LUAINTERFACE_CLIENT->Pop(2);
		 
		return (players);
	}
	 

	//void regfunc() {
	//	ModuleHandles::ClientLuaInterface->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);  // Помещаем глобальную таблицу 
	//	ModuleHandles::ClientLuaInterface->PushCFunction(MyFirstFunction);  // Помещаем нашу функцию 
	//	ModuleHandles::ClientLuaInterface->SetField(-2, "MyFirstFunction");  // Устанавливаем MyFirstFunction в lua в нашу функцию C++ 
	//	ModuleHandles::ClientLuaInterface->Pop();  // Помещаем глобальную таблицу из стека 
	//	Console::WriteLog("GMOD_MODULE_OPEN", std::to_string((int)ModuleHandles::ClientLuaInterface));
	//}



	//LUA_FUNCTION(void_set_name)
	//{
	//	/*LUA->CheckType(1, GarrysMod::Lua::Type::String);

	//	const char* name = (LUA -> ge(1));   
	//	Console::WriteLog("void_set_name: ", name);*/
	//	/*if(name != "")
	//		SetOwnerName(name);*/

	//	return  0;  
	//}


	void RegisterFunction(CLuaFunction val , const char* strName) {
		if (!LUAINTERFACE_CLIENT)
			return;
		LUAINTERFACE_CLIENT -> PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);  // Помещаем глобальную таблицу 
		LUAINTERFACE_CLIENT -> PushCFunction(val);  // Помещаем нашу функцию 
		LUAINTERFACE_CLIENT -> SetField(-2, strName);  // Устанавливаем MyFirstFunction в lua в нашу функцию C++ 
		LUAINTERFACE_CLIENT -> Pop();

		Console::WriteLog("PushCFunction: ", strName);
	}
	
	void InitAll_RegisterFunction() {
		//RegisterFunction(void_set_name, "void_set_name");
	}

}