#pragma once
#include <vector>
#include "entity_admin.h"

//Entity to spawn for a hero. STUHero::m_gameplayEntity is the hero's base entity, but D.Va's is her pilot
//(0x40A); she starts a life in her mech, 0x407 (mech model 0x11CE, Fusion Cannons 0x50A, mech ability scripts),
//which only the server knew to spawn.
inline __int64 hero_spawn_entity(__int64 hero_id, __int64 gameplay_entity) {
	constexpr __int64 HERO_DVA = 0x02E000000000007A;
	constexpr __int64 DVA_MECH = 0x0400000000000407;
	return hero_id == HERO_DVA ? DVA_MECH : gameplay_entity;
}

class player_spawner {
public:
	struct spawn_info {
		//Load
		__int64 resource_id = 0;
		__int64 skin_theme_id = 0;
		__int64 heroid = 0;
		//uint32 latest_entid;
		bool load_2f_33 = false;
		bool load_3f = false;
		//value: initData ptr
		std::vector<EntityLoader_Entry> additional_compids{};

		//Modify
		int cam_attach = 0;
		int aim_attach = 0;
		int movement_attach = 0;
		int petbackref_attach = 0;
		int team = -1;
		bool set_health = false;
		bool set_2f_movable = false;
		bool set_localent = false;
		bool set_filterbits_controller = false;
		bool weapon_attach = false;
		bool fixup_player_statescript = false;
		//bool call_component2_vodoo;
	};

private:
	void modify_ent(spawn_info info, Entity* ent);
	Entity* spawn_ent(spawn_info& info);

public:
	spawn_info controller_info{};
	spawn_info model_info{};
	Entity* controller_ent;
	Entity* model_ent;

	void template_localPlayer();

	player_spawner() {
		template_localPlayer();
	}

	player_spawner(__int64 model_entid) {
		template_localPlayer();
		model_info.resource_id = model_entid;
	}

	//returns key: controller - value: model
	std::pair<Entity*, Entity*> spawn();
};