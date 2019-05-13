#pragma once

enum StoneType{
	NORMAL_STONE, HP_STONE, DAMAGE_STONE, MP_STONE, HD_STONE, HM_STONE, DM_STONE
	//hd means hp and damage
	//hm means hp and mp
	//dm means damage and mp
};

enum EvaluateState {
	Click, Gravity, Normal, Force
	// gravity means after crushing stones
};

