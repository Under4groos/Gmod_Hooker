#pragma once
#include "../../Headers.h"

void lua_load(ILuaInterface* lua, const std::string& file) {
	if (!std::filesystem::exists(file))
		return;
	std::async(std::launch::async, [&]
		{
			std::ifstream File;

			File.open(file.c_str());

			if (File)
			{
				std::string lua_string((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
				if (lua_string.empty())
					return;
				lua->RunString("", "", lua_string.c_str());
			}
			File.close();
	});
}