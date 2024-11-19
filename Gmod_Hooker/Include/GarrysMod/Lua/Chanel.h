#pragma once
#include "CustomFuncs.h"
#include <string_view>
#include "Net.h"
class Channel
{
public:
	inline int send_data(Packet& packet, bool reliable = false)
	{
		using send_data_t = int(__thiscall*)(void*, Packet&, bool);
		return method<send_data_t>(41, this)(this, packet, reliable);
	}

	inline void set_name(std::string_view name)
	{
		char buffer[5024];
		Packet packet(buffer, std::size(buffer));

	 
		packet.write_ulong_bit(5, 6);
		packet.write_byte(1);
		packet.write_string("name");
		packet.write_string(name.data());
		this->send_data(packet);

		 

		 
	}

	inline void write(std::string_view text)
	{
		char buffer[5024];
		Packet packet(buffer, std::size(buffer));

		packet.write_ulong_bit(4, 6);
		packet.write_string(text.data());

		this->send_data(packet);
	}
};