#pragma once

#include "../Main/Main.h"

#define FIX_MIN_FOV_HEAD	30
#define FIX_MIN_FOV_CHEST	50
#define FOV_BASE_DISTANCE	200

namespace Settings
{
	extern int skintabs;
	extern int skintabs1;
	void LoadSettings(string szIniFile);
	void SaveSettings(string szIniFile);
	extern float hitmarkerAlpha;

	extern bool TabActive;

	namespace Vladick
	{
		extern bool Debug;
		extern bool KillDelayEnd;
		extern float KillDelayVar;
	}

	namespace Aimbot
	{
		struct weapon_aim_s
		{
			//[swap_lines]
			bool aim_Active;
			bool aim_UseSecondValue;
			float aim_Smooth;
			float aim_SmoothY;
			float aim_Smoothlevel;

			float aim_SpraySmooth;
			float aim_Fov;
			float aim_SprayFov;
			bool aim_DynamicFov;
			bool aim_BestHit;
			int aim_Spot;
			float aim_DelayKillTime = 0.000f;
			bool aim_KillDelay;
			float aim_Delay;
			int aim_Rcsx;
			int aim_Rcsy;
			int aim_RcsStandalone;
			int aim_RcsAfterXShot;
			int aim_RcsType;
			int aim_RcsClampType;
			bool aim_AutoPistol;
			//[/swap_lines]
		};
		//[swap_lines]
		extern bool aim_Deathmatch;
		extern bool aim_WallAttack;
		extern bool aim_CheckSmoke;
		extern bool aim_AntiJump;
		extern bool aim_JumpCheckME;
		extern bool aim_DrawFov;
		extern bool aim_DrawSpot;
		extern bool aim_fastzoom;

		extern weapon_aim_s weapon_aim_settings[33];
		//[/swap_lines]
	}

	extern int menu_key;

	namespace Esp
	{
		//[swap_lines]
		extern int esp_Style; // 0 - Box 1 - CoalBox
		extern bool esp_Box;
		extern int esp_Size;
		extern int weapon_x, weapon_y;
		extern int name_x, name_y;
		extern bool esp_Line;
		extern bool esp_Outline; // Box ( 0 - Box 1 - OutlineBox ) ,
		extern bool esp_Name;
		extern bool esp_Rank;
		extern bool esp_Health;
		extern int esp_Armor;
		extern bool esp_Weapon;
		extern int esp_WeaponIcon;
		extern bool esp_Ammo;
		extern bool esp_Distance;
		extern bool esp_Sound;
		extern bool esp_Dlightz;
		extern int esp_WeaponIcon;
		extern float esp_Dlight[3];
		extern bool esp_NightMode;
		extern bool esp_Infoz;
		extern int esp_SkeletonStyle;
		extern bool esp_Skeleton;
		extern int esp_BulletTrace;
		extern bool esp_Team;
		extern bool esp_Enemy;
		extern bool esp_Visible;
		extern bool esp_DrawAsIcon;
		extern bool esp_ChamsVisible;

		extern int esp_SoundSize;
		extern int esp_SoundDistance;
		extern int esp_SoundType;
		extern bool esp_SoundMode;
		extern int esp_Chams;
		extern bool esp_Bomb;
		extern int esp_BombTimer;
		extern bool esp_WorldWeapons;
		extern bool esp_WorldGrenade;
		extern int esp_FillBoxOpacity;
		extern bool esp_FillBox;
		extern bool Visuals_WorldWeapons;
		extern int esp_DlightSize;

		extern float HealthBarColor[3];
		extern float ArmorBarColor[3];

		extern float esp_Color_CT[3];
		extern float esp_Color_TT[3];
		extern float esp_Color_VCT[3];
		extern float esp_Color_VTT[3];
		extern float SoundColor[3];
		extern float chams_Color_CT[3];
		extern float chams_Color_TT[3];
		extern float chams_Color_VCT[3];
		extern float chams_Color_VTT[3];
		extern float flTracer_Beam[3];
		extern bool esp_beams_tracer;
		extern float flTracersDuration;
		extern float flTracersWidth;
		//[/swap_lines]
	}

	namespace Skin
	{
		//[swap_lines]
		extern int knf_ct_model;
		extern int knf_ct_skin;
		extern int knf_tt_model;
		extern int knf_tt_skin;
		extern int gloves_skin;
		extern float gloves_wear;
		//[/swap_lines]
	}

	extern bool showworkspace;
	extern bool showtabspace;

	namespace Bot
	{
		extern bool buy_enable;
		extern int buy_rifle;
		extern int buy_pistol;
		extern int buy_kevlar;

		extern bool buy_kit;
		extern bool buy_taser;
	}

	namespace Misc
	{
		//[swap_lines]
		extern bool misc_Bhop;
		extern bool Watermark;
		extern bool misc_Punch;
		extern int misc_AwpAim;
		extern bool misc_NoFlash;
		extern bool misc_NoSmoke;
		extern bool misc_AutoStrafe;
		extern bool misc_AutoAccept;
		extern bool misc_Spectators;
		extern bool misc_FovChanger;
		extern int misc_FovView;
		extern int misc_FovModelView;
		extern float misc_AwpAimColor[3];
		extern float hitmarkerAlpha;
		extern bool misc_HitMarker;
		extern bool misc_RadioSpam;
		extern int misc_HitMarkerSound;
		extern float misc_HitMarkerColor[3];
		extern bool misc_CustomChatSpam;
		extern char misc_ChatSpamText[128];
		extern float misc_ChatSpamDelay;

		extern bool misc_namespamidkmemes;
		extern char* First_static;
		extern char* Second_static;
		extern char First[64];
		extern char Second[64];
		//[/swap_lines]
	}
}

//[enc_string_enable /]

#define HACK_NAME "Indigo MultiHack"

#define AIMBOT_TEXT "Aimbot"
#define CONFIG_TEXT "Config"
#define TRIGGER_TEXT "TriggerBot"
#define KNIFEBOT_TEXT "Knifebot"
#define VISUAL_TEXT "Visual"
#define RADAR_TEXT "Radar"
#define SKIN_TEXT "Skin"
#define MISC_TEXT "Misc"

#define CVAR_ESP_STYLE "esp_Style"
#define CVAR_ESP_WPICON "esp_WeaponIcon"
#define CVAR_ESP_SIZE "esp_Size"
#define CVAR_ESP_LINE "esp_Line"
#define CVAR_ESP_OUTLINE "esp_Outline"
#define CVAR_ESP_NAME "esp_Name"
#define CVAR_ESP_RANK "esp_Rank"
#define CVAR_ESP_INFO "esp_Infoz"

#define CVAR_ESP_HEALTH "esp_Health"
#define CVAR_ESP_ARMOR "esp_Armor"
#define CVAR_ESP_WEAPON "esp_Weapon"
#define CVAR_ESP_AMMO "esp_Ammo"
#define CVAR_ESP_DISTANCE "esp_Distance"
#define CVAR_ESP_SOUND "esp_Sound"
#define CVAR_ESP_DLIGHT "esp_Dlightz"
#define CVAR_ESP_COLOR_DLIGHT "esp_Dlight"

#define CVAR_ESP_SKELETON "esp_Skeleton"
#define CVAR_ESP_BULLETTRACE "esp_BulletTrace"
#define CVAR_ESP_TEAM "esp_Team"
#define CVAR_ESP_ENEMY "esp_Enemy"
#define CVAR_ESP_VISIBLE "esp_Visible"
#define CVAR_ESP_CHAMSVISIBLE "esp_ChamsVisible"

#define CVAR_ESP_CHAMS "esp_Chams"
#define CVAR_ESP_BOMB "esp_Bomb"
#define CVAR_ESP_BOMBTIMER "esp_BombTimer"
#define CVAR_ESP_WORLDWEAPONS "esp_WorldWeapons"
#define CVAR_ESP_WORLDGRENADE "esp_WorldGrenade"

#define CVAR_ESP_COLOR_SKELET "Skelet"
#define CVAR_ESP_COLOR_SOUNDESP "SoundVisuals_Color"
#define CVAR_ESP_COLOR_WEAPONENEMY "WeaponEnemy_Color"
#define CVAR_ESP_COLOR_WORLDWEAPON "WorldWeapon_Color"
#define CVAR_ESP_COLOR_LINE "Visuals_Line_Color"
#define CVAR_ESP_COLOR_NAME "Name_Color"

#define CVAR_ESP_COLOR_CT "esp_Color_CT"
#define CVAR_ESP_COLOR_TT "esp_Color_TT"
#define CVAR_ESP_COLOR_VCT "esp_Color_VCT"
#define CVAR_ESP_COLOR_VTT "esp_Color_VTT"

#define CVAR_CHAMS_COLOR_CT "chams_Color_CT"
#define CVAR_CHAMS_COLOR_TT "chams_Color_TT"
#define CVAR_CHAMS_COLOR_VCT "chams_Color_VCT"
#define CVAR_CHAMS_COLOR_VTT "chams_Color_VTT"

#define C4_TIMER_STRING "C4Timer: %0.2f"

#define CVAR_RAD_ENABLE "Radar_Enable"
#define CVAR_RAD_ACTIVE "rad_Active"
#define CVAR_RAD_TEAM "rad_Team"
#define CVAR_RAD_ENEMY "rad_Enemy"
#define CVAR_RAD_SOUND "rad_Sound"
#define CVAR_RAD_INGAME "rad_InGame"
#define CVAR_RAD_RANGE "rad_Range"
#define CVAR_RAD_ALPHA "rad_Alpha"

#define CVAR_RAD_COLOR_CT "rad_Color_CT"
#define CVAR_RAD_COLOR_TT "rad_Color_TT"
#define CVAR_RAD_COLOR_VCT "rad_Color_VCT"
#define CVAR_RAD_COLOR_VTT "rad_Color_VTT"

#define CVAR_SKIN_CT_MODEL "knf_ct_model"
#define CVAR_SKIN_CT_SKIN "knf_ct_skin"
#define CVAR_SKIN_TT_MODEL "knf_tt_model"
#define CVAR_SKIN_TT_SKIN "knf_tt_skin"
#define CVAR_SKIN_GLOVES "gloves_skin"

#define CVAR_MISC_BHOP "misc_Bhop"
#define CVAR_MISC_PUNCH "misc_Punch"
#define CVAR_MISC_PUNCH2 "misc_Punch2"
#define CVAR_MISC_AWPAIM "misc_AwpAim"
#define CVAR_MISC_NOFLASH "misc_NoFlash"
#define CVAR_MISC_NOSMOKE "misc_NoSmoke"
#define CVAR_MISC_AUTOSTRAFE "misc_AutoStrafe"
#define CVAR_MISC_AUTOACCEPT "misc_AutoAccept"
#define CVAR_MISC_SPECTATORS "misc_Spectators"
#define CVAR_MISC_FOV_CHANGER "misc_FovChanger"
#define CVAR_MISC_FOV_VIEW "misc_FovView"
#define CVAR_MISC_FOV_MDL_VIEW "misc_FovModelView"
#define CVAR_MISC_AWPAIM_COLOR "misc_AwpAimColor"
#define CVAR_MISC_HITMARKER "misc_HitMarker"
#define CVAR_MISC_HITMARKER_COLOR "misc_HitMarkerColor"
#define CVAR_MISC_HITMARKERSOUND "misc_HitMarkerSound"