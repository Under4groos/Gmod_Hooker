#pragma once
#include "CustomFuncs.h"
#include "Chanel.h"

struct ViewMatrix_t;
struct player_info_t;

 
struct player_info_t
{
	char name[32];
	int  id;
	char guid[33];
	struct
	{
		uint32_t id;
		char name[32];
	} buddy;
	bool bot;
	bool hltv;
	uint32_t files[4];
	uint8_t  downloaded;
};

 

class IEngineClient
{
public:
	inline size_t get_local_player()
	{
		using get_local_player_t = size_t(__thiscall*)(void*);
		return method<get_local_player_t>(12, this)(this);
	}

	inline float GetLastTimeStamp(void)
	{
		typedef float(__thiscall* OriginalFn)(PVOID);
		return GetVFunc<OriginalFn>(this, 14)(this);
	}

	inline Channel* get_net_channel()
	{
		using get_net_channel_t = Channel * (__thiscall*)(void*);
		return method<get_net_channel_t>(72, this)(this);
	}

	inline bool get_player_info(size_t index, player_info_t* info)
	{
		using get_player_info_t = bool(__thiscall*)(void*, size_t, player_info_t*);
		return method<get_player_info_t>(8, this)(this, index, info);
	}

	/*inline const matrix4x4_t& get_view_matrix()
	{
		using get_view_matrix_t = const matrix4x4_t& (__thiscall*)(void*);
		return method<get_view_matrix_t>(36, this)(this);
	}*/

	inline size_t get_max_clients()
	{
		using get_max_clients_t = size_t(__thiscall*)(void*);
		return method<get_max_clients_t>(21, this)(this);
	}

	inline void get_screen_size(int& width, int& height)
	{
		using get_screen_size_t = void(__thiscall*)(void*, int&, int&);
		return method<get_screen_size_t>(5, this)(this, width, height);
	}

	//inline void set_view_angles(Angle& Angles)
	//{
	//	using  set_view_angles_t = void(__thiscall*)(void*, Angle& Angles);
	//	return method<set_view_angles_t>(20, this)(this, Angles);
	//}

	inline bool is_ingame()
	{
		using is_ingame_t = bool(__thiscall*)(void*);
		return method<is_ingame_t>(26, this)(this);
	}
};
//class IEngineClient {
//public:
//	virtual void pad0() = 0;
//	virtual void pad1() = 0;
//	virtual void pad2() = 0;
//	virtual void pad3() = 0;
//	virtual void pad4() = 0;
//	virtual void GetScreenSize(int& w, int& h) = 0;
//	virtual void ServerCmd(const char* szCmdString, bool bReliable) = 0;
//	virtual void ClientCmd(const char* szCmdString) = 0;
//	virtual bool GetPlayerInfo(int entNum, player_info_t* pInfo) = 0;
//	virtual void pad7() = 0;
//	virtual void pad8() = 0;
//	virtual bool Con_IsVisible() = 0;
//	virtual int GetLocalPlayer() = 0;
//	virtual void pad9() = 0;
//	virtual void pad10() = 0;
//	virtual void pad11() = 0;
//	virtual void pad12() = 0;
//	virtual void pad13() = 0;
//	virtual void pad14() = 0;
//	//virtual void GetViewAngles(QAngle& va) = 0;
//	//virtual void SetViewAngles(QAngle& va) = 0;
//	virtual int GetMaxClients() = 0;
//	virtual void pad15() = 0;
//	virtual void pad16() = 0;
//	virtual void pad17() = 0;
//	virtual void pad18() = 0;
//	virtual bool IsInGame() = 0;
//	virtual bool IsConnected() = 0;
//	virtual void pad19() = 0;
//	virtual void pad20() = 0;
//	virtual void pad21() = 0;
//	virtual void pad22() = 0;
//	virtual void pad23() = 0;
//	virtual void pad24() = 0;
//	virtual void pad25() = 0;
//	virtual void pad26() = 0;
//	virtual ViewMatrix_t& WorldToScreenMatrix() = 0;
//	virtual ViewMatrix_t& WorldToViewMatrix() = 0;
//};