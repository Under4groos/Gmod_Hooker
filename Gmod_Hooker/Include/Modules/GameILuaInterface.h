#pragma once
#include "../../Headers.h"

namespace GameILuaInterface {
	IEngineClient* EngineClient;
	CreateInterfaceFn LuaShared_CreateInterface;
	ILuaShared* LuaShared;

	ILuaInterface* LUAINTERFACE_CLIENT;
	ILuaInterface* LUAINTERFACE_MENU;


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
		Channel* ch = EngineClient->get_net_channel();
		if (ch) {
			ch->set_name(name);
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

}