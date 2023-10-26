#pragma once
class SettingMenu
{
	private:
	int MAX_INDEX = 3;
	public:
		enum SettingMenuOption {
		NONE = -1,
		BACK = 0,
		CHANGE_CHARACTER = 1,
		BACKGROUND_MUSIC = 2,
		EFFECT_MUSIC = 3,

	};

	SettingMenuOption SettingMenuScreen();
	SettingMenuOption ChangeCharacterMenu();

	SettingMenu();
	~SettingMenu();
};

