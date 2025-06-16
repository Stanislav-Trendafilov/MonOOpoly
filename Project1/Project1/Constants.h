#pragma once

namespace GlobalConstants
{

	constexpr int MAX_BUILDINGS_PROPERTY =7;
	constexpr int MAX_TRAIN_STATIONS = 4;
	constexpr int MAX_COMPANIES = 2;

	constexpr int STARTING_CASH = 1500;
	constexpr int PASS_START_CASH = 200;

	constexpr int MAX_COUNT_FIELDS = 39;
	constexpr int FIELDS_RESTART_AT = 40;
	constexpr int START_INDEX = 0;


	constexpr int JAIL_INDEX= 30;
	constexpr int ELECTRIC_COMPANY_INDEX = 12;
	constexpr int WATER_SUPPLY_INDEX = 28;

	constexpr int TRAINSTATION1_INDEX = 5;
	constexpr int TRAINSTATION2_INDEX = 15;
	constexpr int TRAINSTATION3_INDEX = 25;
	constexpr int TRAINSTATION4_INDEX = 35;

	constexpr int DICE_VALUE1 = 1;
	constexpr int DICE_VALUE2 = 2;
	constexpr int DICE_VALUE3 = 3;
	constexpr int DICE_VALUE4 = 4;
	constexpr int DICE_VALUE5 = 5;
	constexpr int DICE_VALUE6 = 6;


	enum class PropertyColors
	{
		BROWN,
		PINK,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		ORANGE
	};

} 