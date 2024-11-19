#pragma once
#include "../../Headers.h"



void set_name(IEngineClient* EngineClient , std::string_view name) {
	Channel* ch = EngineClient->get_net_channel();
	if (ch) {
		ch->set_name(name);
	}
}