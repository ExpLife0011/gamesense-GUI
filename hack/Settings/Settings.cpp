#include "Settings.h"

//[enc_string_enable /]
//[junk_enable /]

using namespace Client;

namespace Settings
{
	void LoadSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());

		Aimbot::aim_Deathmatch = CSX::Cvar::LoadCvar("LEGITBOT", "aim_deathmatch", Aimbot::aim_Deathmatch);
		Aimbot::aim_CheckSmoke = CSX::Cvar::LoadCvar("LEGITBOT", "aim_checksmoke", Aimbot::aim_CheckSmoke);
		Aimbot::aim_AntiJump = CSX::Cvar::LoadCvar("LEGITBOT", "aim_checkjump", Aimbot::aim_AntiJump);
		Aimbot::aim_DrawFov = CSX::Cvar::LoadCvar("LEGITBOT", "aim_drawfov", Aimbot::aim_DrawFov);
		Aimbot::aim_DrawSpot = CSX::Cvar::LoadCvar("LEGITBOT", "aim_drawspot", Aimbot::aim_DrawSpot);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_active", 0);
			Aimbot::weapon_aim_settings[i].aim_UseSecondValue = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_usespray", 0);
			Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_smooth", 10);
			Aimbot::weapon_aim_settings[i].aim_Smoothlevel = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_smoothlevel", 2.f);
			Aimbot::weapon_aim_settings[i].aim_SpraySmooth = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_spraysmooth", 10);
			Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_fov", 11);
			Aimbot::weapon_aim_settings[i].aim_SprayFov = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_sprayfov", 11);
			Aimbot::weapon_aim_settings[i].aim_DynamicFov = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_distancefov", 0);
			Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_nearest", 0);
			Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_spot", 5);
			Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_delay", 0);
			Aimbot::weapon_aim_settings[i].aim_KillDelay = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_targetswitch", 1);
			Aimbot::weapon_aim_settings[i].aim_DelayKillTime = CSX::Cvar::LoadFloat(pWeaponData[i], "aim_targetswitchdelay", 0.f);
			Aimbot::weapon_aim_settings[i].aim_Rcsx = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_rcsx", 50);
			Aimbot::weapon_aim_settings[i].aim_Rcsy = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_rcsy", 50);
			Aimbot::weapon_aim_settings[i].aim_RcsAfterXShot = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_rcsafterxfhot", 1);
			Aimbot::weapon_aim_settings[i].aim_RcsStandalone = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_rcsstandalone", 0);

			Aimbot::weapon_aim_settings[i].aim_AutoPistol = CSX::Cvar::LoadCvar(pWeaponData[i], "aim_autopistol", 0);
		}

		Esp::esp_Enemy = CSX::Cvar::LoadCvar("ESP", "esp_enemy", Esp::esp_Enemy);
		Esp::esp_Team = CSX::Cvar::LoadCvar("ESP", "esp_team", Esp::esp_Team);

		Esp::esp_Visible = CSX::Cvar::LoadCvar("ESP", "esp_visible", Esp::esp_Visible);
		Esp::esp_ChamsVisible = CSX::Cvar::LoadCvar("ESP", "chams_visible", Esp::esp_ChamsVisible);

		Esp::esp_Size = CSX::Cvar::LoadCvar("ESP", "esp_size", Esp::esp_Size);
		Esp::esp_Box = CSX::Cvar::LoadCvar("ESP", "esp_box", Esp::esp_Box);
		Esp::esp_Style = CSX::Cvar::LoadCvar("ESP", "esp_boxstyle", Esp::esp_Style);
		Esp::esp_Outline = CSX::Cvar::LoadCvar("ESP", "esp_boxoutline", Esp::esp_Outline);
		Esp::esp_FillBox = CSX::Cvar::LoadCvar("ESP", "esp_fillbox", Esp::esp_FillBox);
		Esp::esp_FillBoxOpacity = CSX::Cvar::LoadCvar("ESP", "esp_fillboxopacity", Esp::esp_FillBoxOpacity);

		Esp::esp_Health = CSX::Cvar::LoadCvar("ESP", "esp_healthbar", Esp::esp_Health);
		Esp::esp_Armor = CSX::Cvar::LoadCvar("ESP", "esp_armorbar", Esp::esp_Armor);

		Esp::esp_Name = CSX::Cvar::LoadCvar("ESP", "esp_name", Esp::esp_Name);

		Esp::esp_Rank = CSX::Cvar::LoadCvar("ESP", "esp_rank", Esp::esp_Rank);

		Esp::esp_Weapon = CSX::Cvar::LoadCvar("ESP", "esp_weapon", Esp::esp_Weapon);
		Esp::esp_Ammo = CSX::Cvar::LoadCvar("ESP", "esp_ammo", Esp::esp_Ammo);

		Esp::esp_Line = CSX::Cvar::LoadCvar("ESP", "esp_line", Esp::esp_Line);

		Esp::esp_Bomb = CSX::Cvar::LoadCvar("ESP", "esp_bomb", Esp::esp_Bomb);

		Esp::esp_WorldWeapons = CSX::Cvar::LoadCvar("ESP", "esp_droppedweapons", Esp::esp_WorldWeapons);

		Esp::esp_WorldGrenade = CSX::Cvar::LoadCvar("ESP", "esp_droppedgrenades", Esp::esp_WorldGrenade);
		Esp::esp_DrawAsIcon = CSX::Cvar::LoadCvar("ESP", "esp_grenadeasicon", Esp::esp_DrawAsIcon);

		Esp::esp_Distance = CSX::Cvar::LoadCvar("ESP", "esp_distance", Esp::esp_Distance);

		Esp::esp_Skeleton = CSX::Cvar::LoadCvar("ESP", "esp_skeleton", Esp::esp_Skeleton);
		Esp::esp_SkeletonStyle = CSX::Cvar::LoadCvar("ESP", "esp_skeletonstyle", Esp::esp_SkeletonStyle);

		Esp::esp_Sound = CSX::Cvar::LoadCvar("ESP", "esp_sound", Esp::esp_Sound);
		Esp::esp_SoundSize = CSX::Cvar::LoadCvar("ESP", "esp_soundsize", Esp::esp_SoundSize);
		Esp::esp_SoundType = CSX::Cvar::LoadCvar("ESP", "esp_soundtype", Esp::esp_SoundType);
		Esp::esp_SoundMode = CSX::Cvar::LoadCvar("ESP", "esp_soundmode", Esp::esp_SoundMode);
		Esp::esp_SoundDistance = CSX::Cvar::LoadCvar("ESP", "esp_sounddistance", Esp::esp_SoundDistance);
		Esp::esp_Dlightz = CSX::Cvar::LoadCvar("ESP", "esp_dlight", Esp::esp_Dlightz);
		Esp::esp_DlightSize = CSX::Cvar::LoadCvar("ESP", "esp_dlightsize", Esp::esp_DlightSize);
		Esp::esp_NightMode = CSX::Cvar::LoadCvar("ESP", "esp_nightmode", Esp::esp_NightMode);

		Esp::esp_Chams = CSX::Cvar::LoadCvar("CHAMS", "chams_enable", Esp::esp_Chams);

		Misc::misc_Bhop = CSX::Cvar::LoadCvar("MISC", "misc_bhop", Misc::misc_Bhop) != false;
		Misc::misc_AutoStrafe = CSX::Cvar::LoadCvar("MISC", "misc_autostrafe", Misc::misc_AutoStrafe) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar("MISC", "misc_noflash", Misc::misc_NoFlash) != false;
		Misc::misc_AutoAccept = CSX::Cvar::LoadCvar("MISC", "misc_autoaccept", Misc::misc_AutoAccept) != false;
		Misc::misc_Spectators = CSX::Cvar::LoadCvar("MISC", "misc_spectators", Misc::misc_Spectators) != false;
		Misc::misc_FovChanger = CSX::Cvar::LoadCvar("MISC", "misc_fovchanger", Misc::misc_FovChanger) != false;
		Misc::misc_FovView = CSX::Cvar::LoadCvar("MISC", "misc_fovview", Misc::misc_FovView);
		Misc::misc_FovModelView = CSX::Cvar::LoadCvar("MISC", "misc_fovmodelview", Misc::misc_FovModelView);
		Misc::misc_AwpAim = CSX::Cvar::LoadCvar("MISC", "misc_sniper", Misc::misc_AwpAim);

		string esp_Color_CT = CSX::Cvar::LoadCvar("COLORS", "esp_boxcolorct", "0,164,255");
		string esp_Color_TT = CSX::Cvar::LoadCvar("COLORS", "esp_boxcolortt", "255,64,64");
		string esp_Color_VCT = CSX::Cvar::LoadCvar("COLORS", "esp_boxcolorvct", "124,252,0");
		string esp_Color_VTT = CSX::Cvar::LoadCvar("COLORS", "esp_boxcolorvtt", "124,252,0");

		ScanColorFromCvar(esp_Color_CT.c_str(), Settings::Esp::esp_Color_CT);
		ScanColorFromCvar(esp_Color_TT.c_str(), Settings::Esp::esp_Color_TT);
		ScanColorFromCvar(esp_Color_VCT.c_str(), Settings::Esp::esp_Color_VCT);
		ScanColorFromCvar(esp_Color_VTT.c_str(), Settings::Esp::esp_Color_VTT);

		string esp_dlightcolor = CSX::Cvar::LoadCvar("COLORS", "esp_dlightcolor", "124,252,0");

		ScanColorFromCvar(esp_dlightcolor.c_str(), Settings::Esp::esp_Dlight);

		string chams_Color_CT = CSX::Cvar::LoadCvar("COLORS", "chams_ñolor_ct", "0,164,255");
		string chams_Color_TT = CSX::Cvar::LoadCvar("COLORS", "chams_ñolor_tt", "255,64,64");
		string chams_Color_VCT = CSX::Cvar::LoadCvar("COLORS", "chams_ñolor_vct", "124,252,0");
		string chams_Color_VTT = CSX::Cvar::LoadCvar("COLORS", "chams_ñolor_vtt", "124,252,0");

		ScanColorFromCvar(chams_Color_CT.c_str(), Settings::Esp::chams_Color_CT);
		ScanColorFromCvar(chams_Color_TT.c_str(), Settings::Esp::chams_Color_TT);
		ScanColorFromCvar(chams_Color_VCT.c_str(), Settings::Esp::chams_Color_VCT);
		ScanColorFromCvar(chams_Color_VTT.c_str(), Settings::Esp::chams_Color_VTT);

		string cross = CSX::Cvar::LoadCvar("COLORS", "misc_snipercolor", "0,255,0");

		ScanColorFromCvar(cross.c_str(), Misc::misc_AwpAimColor);

		menu_key = CSX::Cvar::LoadCvar("MENU", "menu_key", menu_key);
	}

	void SaveSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());

		CSX::Cvar::SaveCvar("LEGITBOT", "aim_deathmatch", Aimbot::aim_Deathmatch);
		CSX::Cvar::SaveCvar("LEGITBOT", "aim_checksmoke", Aimbot::aim_CheckSmoke);
		CSX::Cvar::SaveCvar("LEGITBOT", "aim_checkjump", Aimbot::aim_AntiJump);
		CSX::Cvar::SaveCvar("LEGITBOT", "aim_drawfov", Aimbot::aim_DrawFov);
		CSX::Cvar::SaveCvar("LEGITBOT", "aim_drawspot", Aimbot::aim_DrawSpot);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_active", Aimbot::weapon_aim_settings[i].aim_Active);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_usespray", Aimbot::weapon_aim_settings[i].aim_UseSecondValue);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_smooth", Aimbot::weapon_aim_settings[i].aim_Smooth);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_smoothlevel", Aimbot::weapon_aim_settings[i].aim_Smoothlevel);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_spraysmooth", Aimbot::weapon_aim_settings[i].aim_SpraySmooth);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_fov", Aimbot::weapon_aim_settings[i].aim_Fov);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_sprayfov", Aimbot::weapon_aim_settings[i].aim_SprayFov);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_distancefov", Aimbot::weapon_aim_settings[i].aim_DynamicFov);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_nearest", Aimbot::weapon_aim_settings[i].aim_BestHit);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_spot", Aimbot::weapon_aim_settings[i].aim_Spot);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_delay", Aimbot::weapon_aim_settings[i].aim_Delay);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_targetswitch", Aimbot::weapon_aim_settings[i].aim_KillDelay);
			CSX::Cvar::SaveFloat(pWeaponData[i], "aim_targetswitchdelay", Aimbot::weapon_aim_settings[i].aim_DelayKillTime);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_rcsx", Aimbot::weapon_aim_settings[i].aim_Rcsx);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_rcsy", Aimbot::weapon_aim_settings[i].aim_Rcsy);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_rcsafterxfhot", Aimbot::weapon_aim_settings[i].aim_RcsAfterXShot);
			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_rcsstandalone", Aimbot::weapon_aim_settings[i].aim_RcsStandalone);

			CSX::Cvar::SaveCvar(pWeaponData[i], "aim_autopistol", Aimbot::weapon_aim_settings[i].aim_AutoPistol);
		}

		CSX::Cvar::SaveCvar("ESP", "esp_enemy", Esp::esp_Enemy);
		CSX::Cvar::SaveCvar("ESP", "esp_team", Esp::esp_Team);

		CSX::Cvar::SaveCvar("ESP", "esp_visible", Esp::esp_Visible);
		CSX::Cvar::SaveCvar("ESP", "chams_visible", Esp::esp_ChamsVisible);

		CSX::Cvar::SaveCvar("ESP", "esp_size", Esp::esp_Size);
		CSX::Cvar::SaveCvar("ESP", "esp_box", Esp::esp_Box);
		CSX::Cvar::SaveCvar("ESP", "esp_boxstyle", Esp::esp_Style);
		CSX::Cvar::SaveCvar("ESP", "esp_boxoutline", Esp::esp_Outline);
		CSX::Cvar::SaveCvar("ESP", "esp_fillbox", Esp::esp_FillBox);
		CSX::Cvar::SaveCvar("ESP", "esp_fillboxopacity", Esp::esp_FillBoxOpacity);

		CSX::Cvar::SaveCvar("ESP", "esp_healthbar", Esp::esp_Health);
		CSX::Cvar::SaveCvar("ESP", "esp_armorbar", Esp::esp_Armor);

		CSX::Cvar::SaveCvar("ESP", "esp_name", Esp::esp_Name);

		CSX::Cvar::SaveCvar("ESP", "esp_rank", Esp::esp_Rank);

		CSX::Cvar::SaveCvar("ESP", "esp_weapon", Esp::esp_Weapon);
		CSX::Cvar::SaveCvar("ESP", "esp_weaponstyle", Esp::esp_WeaponIcon);
		CSX::Cvar::SaveCvar("ESP", "esp_ammo", Esp::esp_Ammo);

		CSX::Cvar::SaveCvar("ESP", "esp_line", Esp::esp_Line);

		CSX::Cvar::SaveCvar("ESP", "esp_bomb", Esp::esp_Bomb);

		CSX::Cvar::SaveCvar("ESP", "esp_droppedweapons", Esp::esp_WorldWeapons);

		CSX::Cvar::SaveCvar("ESP", "esp_droppedgrenades", Esp::esp_WorldGrenade);
		CSX::Cvar::SaveCvar("ESP", "esp_grenadeasicon", Esp::esp_DrawAsIcon);

		CSX::Cvar::SaveCvar("ESP", "esp_distance", Esp::esp_Distance);

		CSX::Cvar::SaveCvar("ESP", "esp_skeleton", Esp::esp_Skeleton);
		CSX::Cvar::SaveCvar("ESP", "esp_skeletonstyle", Esp::esp_SkeletonStyle);

		CSX::Cvar::SaveCvar("ESP", "esp_sound", Esp::esp_Sound);
		CSX::Cvar::SaveCvar("ESP", "esp_soundsize", Esp::esp_SoundSize);
		CSX::Cvar::SaveCvar("ESP", "esp_soundtype", Esp::esp_SoundType);
		CSX::Cvar::SaveCvar("ESP", "esp_soundmode", Esp::esp_SoundMode);
		CSX::Cvar::SaveCvar("ESP", "esp_sounddistance", Esp::esp_SoundDistance);

		CSX::Cvar::SaveCvar("ESP", "esp_dlight", Esp::esp_Dlightz);
		CSX::Cvar::SaveCvar("ESP", "esp_dlightsize", Esp::esp_DlightSize);
		CSX::Cvar::SaveCvar("ESP", "esp_nightmode", Esp::esp_NightMode);

		CSX::Cvar::SaveCvar("CHAMS", "chams_enable", Esp::esp_Chams);

		CSX::Cvar::SaveCvar("MISC", "misc_bhop", Misc::misc_Bhop);
		CSX::Cvar::SaveCvar("MISC", "misc_autostrafe", Misc::misc_AutoStrafe);
		CSX::Cvar::SaveCvar("MISC", "misc_noflash", Misc::misc_NoFlash);
		CSX::Cvar::SaveCvar("MISC", "misc_autoaccept", Misc::misc_AutoAccept);
		CSX::Cvar::SaveCvar("MISC", "misc_spectators", Misc::misc_Spectators);
		CSX::Cvar::SaveCvar("MISC", "misc_fovchanger", Misc::misc_FovChanger);
		CSX::Cvar::SaveCvar("MISC", "misc_fovview", Misc::misc_FovView);
		CSX::Cvar::SaveCvar("MISC", "misc_fovmodelview", Misc::misc_FovModelView);
		CSX::Cvar::SaveCvar("MISC", "misc_sniper", Misc::misc_AwpAim);

		string esp_Color_CT =
			to_string(int(Settings::Esp::esp_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[2] * 255.f));

		string esp_Color_TT =
			to_string(int(Settings::Esp::esp_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[2] * 255.f));

		string esp_Color_VCT =
			to_string(int(Settings::Esp::esp_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[2] * 255.f));

		string esp_Color_VTT =
			to_string(int(Settings::Esp::esp_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar("COLORS", "esp_boxcolorct", esp_Color_CT);
		CSX::Cvar::SaveCvar("COLORS", "esp_boxcolortt", esp_Color_TT);
		CSX::Cvar::SaveCvar("COLORS", "esp_boxcolorvct", esp_Color_VCT);
		CSX::Cvar::SaveCvar("COLORS", "esp_boxcolorvtt", esp_Color_VTT);

		string esp_dlightcolor =
			to_string(int(Settings::Esp::esp_Dlight[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Dlight[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Dlight[2] * 255.f));

		CSX::Cvar::SaveCvar("COLORS", "esp_dlightcolor", esp_dlightcolor);

		string chams_Color_CT =
			to_string(int(Settings::Esp::chams_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[2] * 255.f));

		string chams_Color_TT =
			to_string(int(Settings::Esp::chams_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[2] * 255.f));

		string chams_Color_VCT =
			to_string(int(Settings::Esp::chams_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[2] * 255.f));

		string chams_Color_VTT =
			to_string(int(Settings::Esp::chams_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar("COLORS", "chams_color_ct", chams_Color_CT);
		CSX::Cvar::SaveCvar("COLORS", "chams_color_tt", chams_Color_TT);
		CSX::Cvar::SaveCvar("COLORS", "chams_color_vct", chams_Color_VCT);
		CSX::Cvar::SaveCvar("COLORS", "chams_color_vtt", chams_Color_VTT);

		string crossss =
			to_string(int(Misc::misc_AwpAimColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_AwpAimColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_AwpAimColor[2] * 255.f));

		CSX::Cvar::SaveCvar("COLORS", "misc_snipercolor", crossss);

		CSX::Cvar::SaveCvar("MENU", "menu_key", menu_key);
	}

	float hitmarkerAlpha;

	bool TabActive;

	namespace Vladick
	{
		bool Debug = false;
		bool KillDelayEnd = false;
		float KillDelayVar = 0.f;
	}
	int skintabs = 0;
	int skintabs1 = 0;
	namespace Aimbot
	{
		bool aim_Deathmatch = false;
		bool aim_WallAttack = false;
		bool aim_CheckSmoke = false;
		bool aim_AntiJump = false;
		bool aim_JumpCheckME = false;
		bool aim_DrawFov = false;
		bool aim_DrawSpot = false;
		bool aim_fastzoom;

		weapon_aim_s weapon_aim_settings[33] = { 0 };
	}

	int menu_key = 45;

	namespace Esp
	{
		int weapon_x, weapon_y;
		int name_x, name_y;


		bool esp_Box = 0;
		int esp_Style = 1; // 0 - Box 1 - CoalBox
		int esp_Size = 1;
		bool esp_Line = false;
		bool esp_Outline = false; // Box ( 0 - Box 1 - OutlineBox ) ,
		bool esp_Name = false;
		bool esp_Rank = false;
		bool esp_Health = false;
		int esp_Armor = 0;
		bool esp_Weapon = false;
		int esp_WeaponIcon = 0;
		bool esp_Ammo = false;
		bool esp_Distance = false;
		bool esp_Sound = false;
		bool esp_Dlightz = false;
		bool esp_NightMode = false;
		bool esp_Infoz = false;

		int esp_DlightSize = 120;
		int esp_FillBoxOpacity = 100;
		bool esp_FillBox = false;

		float esp_Dlight[3];

		bool esp_Skeleton = 0;

		bool esp_SoundMode = false;
		int esp_SoundSize = 7;
		int esp_SoundType = 0;
		int esp_SoundDistance = 750;

		int esp_SkeletonStyle = 0;
		int esp_BulletTrace = 0;
		bool esp_Team = 1;
		bool esp_Enemy = 1;
		bool esp_Visible = 1;
		bool esp_ChamsVisible = 1;

		int esp_Chams = 0;
		bool esp_Bomb = false;
		int esp_BombTimer = 40;
		bool esp_DrawAsIcon = false;
		bool esp_WorldWeapons = false;
		bool esp_WorldGrenade = false;

		float esp_Color_CT[3] = { 0.f,0.0f,0.f };
		float SoundColor[3] = { 0.f,0.0f,0.f };
		float esp_Color_TT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VCT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VTT[3] = { 0.f,0.0f,0.f };

		float chams_Color_CT[3] = { 0.f,0.0f,0.f };
		float chams_Color_TT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VCT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VTT[3] = { 0.f,0.0f,0.f };

		bool esp_HPBasedChams = false;
		bool esp_ChamsRainbow = false;

		float flTracer_Beam[3] = { 0.f,0.0f,0.f };
		bool esp_beams_tracer = false;
		float flTracersDuration;
		float flTracersWidth;
	}

	namespace Bot
	{
		bool buy_enable = false;
		int buy_rifle = 0;
		int buy_pistol = 0;
		int buy_kevlar = 0;

		bool buy_kit = false;
		bool buy_taser = false;
	}

	namespace Skin
	{
		int knf_ct_model = 0;
		int knf_ct_skin = 0;
		int knf_tt_model = 0;
		int knf_tt_skin = 0;
		int gloves_skin = 0;
		float gloves_wear = 0.0000f;
	}

	bool showworkspace = false;
	bool showtabspace = false;

	namespace Misc
	{
		bool misc_Bhop = false;
		bool Watermark = false;
		bool misc_Punch = false;
		bool misc_NoFlash = false;
		bool misc_NoSmoke = false;
		int misc_AwpAim = 0;
		bool misc_AutoStrafe = false;
		bool misc_AutoAccept = false;
		bool misc_Spectators = false;
		bool misc_FovChanger = false;
		int misc_FovView = 90;
		int misc_FovModelView = 60;
		float misc_AwpAimColor[3] = { 0.f,0.f,0.f };
		bool misc_HitMarker = false;
		float hitmarkerAlpha;
		int misc_HitMarkerSound = 0;
		bool misc_RadioSpam = false;
		float misc_HitMarkerColor[3] = { 0.f, 0.f, 0.f };
		bool misc_CustomChatSpam = false;
		char misc_ChatSpamText[128] = "SEQUENCE SOFTWARE";
		float misc_ChatSpamDelay = 0.8f;

		bool misc_namespamidkmemes = false;
		char* First_static = "-SEQUENCE";
		char* Second_static = "SEQUENCE-";
		char First[64] = "-SEQUENCE";
		char Second[64] = "SEQUENCE-";
	}
}