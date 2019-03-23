#include "Misc.h"

using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CMisc::OnRender()
{
	if (Settings::Misc::misc_RadioSpam)
	{
		const char* radioCommands[] = {
			"coverme",
			"takepoint",
			"holdpos",
			"regroup",
			"followme",
			"takingfire",
			"go",
			"fallback",
			"sticktog",
			"report",
			"roger",
			"enemyspot",
			"needbackup",
			"sectorclear",
			"inposition",
			"reportingin",
			"getout",
			"negative",
			"enemydown",
		};

		Interfaces::Engine()->ClientCmd_Unrestricted2(radioCommands[std::rand() % ARRAYSIZE(radioCommands)]);
	}
	if (Settings::Misc::misc_CustomChatSpam)
		ChatSpamCustom();

	if (Settings::Misc::misc_namespamidkmemes)
	{
		static bool steal = false;

		ConVar* Name = Interfaces::GetConVar()->FindVar("name");
		*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;

		if (Name)
		{
			if (!steal)
			{
				Name->SetValue(Settings::Misc::First);
				steal = true;
			}
			else
			{
				Name->SetValue(Settings::Misc::Second);
				steal = false;
			}
		}
	}

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (Settings::Misc::misc_AwpAim == 0 && IsLocalAlive())
	{

		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);

	}
	else if (Settings::Misc::misc_AwpAim == 1 && IsLocalAlive())
	{
		if (pPlayer->GetIsScoped() | (pPlayer->GetIsScoped() && GetKeyState(VK_SHIFT)))
		{
			ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
			crosshair1->SetValue(0);
			ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
			crosshair2->SetValue(0);
		}
		else
		{
			ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
			crosshair1->SetValue(1);
			ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
			crosshair2->SetValue(999999999);
		}
	}
	else if (Settings::Misc::misc_AwpAim == 2 && IsLocalAlive())
	{
		if (!pPlayer->GetIsScoped() && IsLocalAlive() && (g_pPlayers->GetLocal()->WeaponIndex == WEAPON_AWP | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_G3SG1 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SCAR20 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SSG08))
		{
			Color AwpAimColor = Color(int(Settings::Misc::misc_AwpAimColor[0] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[1] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[2] * 255.f));

			g_pRender->DrawFillBox(iScreenWidth / 2 - 1, iScreenHeight / 2 - 1, 3, 3, AwpAimColor);
		}
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}
	else if (Settings::Misc::misc_AwpAim == 3 && IsLocalAlive())
	{
		if (!pPlayer->GetIsScoped() && IsLocalAlive() && (g_pPlayers->GetLocal()->WeaponIndex == WEAPON_AWP | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_G3SG1 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SCAR20 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SSG08))
		{
			Color AwpAimColor = Color(int(Settings::Misc::misc_AwpAimColor[0] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[1] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[2] * 255.f));

			g_pRender->DrawLine(0, iScreenHeight / 2 , iScreenWidth, iScreenHeight / 2, AwpAimColor);
			g_pRender->DrawLine(iScreenWidth /2, 0, iScreenWidth / 2, iScreenHeight, AwpAimColor);
		}
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}
	else if (Settings::Misc::misc_AwpAim == 4 && IsLocalAlive())
	{
		if (!pPlayer->GetIsScoped() && IsLocalAlive() && ( g_pPlayers->GetLocal()->WeaponIndex == WEAPON_AWP | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_G3SG1 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SCAR20 | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SSG08))
		{
			Color AwpAimColor = Color(int(Settings::Misc::misc_AwpAimColor[0] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[1] * 255.f),
				int(Settings::Misc::misc_AwpAimColor[2] * 255.f));

			g_pRender->DrawLine(0,0,iScreenWidth, iScreenHeight , AwpAimColor);
			g_pRender->DrawLine(0, iScreenHeight, iScreenWidth, 0 , AwpAimColor);
		}
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}
}

void CMisc::OnCreateMove(CUserCmd* pCmd)
{
	bool in_water = g_pPlayers->GetLocal()->m_pEntity->m_nWaterLevel() >= 2;
	bool on_ladder = g_pPlayers->GetLocal()->m_pEntity->movetype() == MOVETYPE_LADDER;
	bool noclip = g_pPlayers->GetLocal()->m_pEntity->movetype() == MOVETYPE_NOCLIP;
	bool spectate = g_pPlayers->GetLocal()->m_pEntity->movetype() == MOVETYPE_OBSERVER;

	if (Settings::Misc::misc_Bhop)
	{
		if ((pCmd->buttons & IN_JUMP) && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND) && !on_ladder && !noclip && !spectate && !in_water)
		{
			pCmd->buttons &= ~IN_JUMP;
		}
	}

	if (Settings::Misc::misc_AutoStrafe && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND) && !on_ladder && !noclip && !spectate && !in_water)
	{
		static float float1;
		static float float2;

		if (!(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND))
		{
			float2 = CSX::Utils::RandomIntRange(-440, -450);
			float1 = CSX::Utils::RandomIntRange(440, 450);
		}

		if (pCmd->mousedx < 0)
		{
			pCmd->sidemove = float2;
		}
		else if (pCmd->mousedx > 0)
		{
			pCmd->sidemove = float1;
		}
	}
}

std::vector<const char*> smoke_materials =
{
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};

void CMisc::OnDrawModelExecute()
{
	static bool NoFlashReset = false;
	static bool NoSmoke = false;

	if (Settings::Misc::misc_NoFlash && !NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoFlashReset = true;
		}
	}
	else if (!Settings::Misc::misc_NoFlash && NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoFlashReset = false;
		}
	}
	if (Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoSmoke = true;
		}
	}
	else if (!Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoSmoke = false;

		}
	}
}

void CMisc::OnPlaySound(const char* pszSoundName)
{
	if (Settings::Misc::misc_AutoAccept && !strcmp(pszSoundName, "!UI/competitive_accept_beep.wav"))
	{
		typedef void(*IsReadyCallBackFn)();

		IsReadyCallBackFn IsReadyCallBack = 0;

		if (!IsReadyCallBack)
		{
			IsReadyCallBack = (IsReadyCallBackFn)(
				CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE", 0));

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::IsReadyCallBack = %X", IsReadyCallBack);
#endif
		}

		if (IsReadyCallBack)
		{
			IsReadyCallBack();
		}
	}
}

void CMisc::OnOverrideView(CViewSetup * pSetup)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->GetIsScoped())
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		pSetup->fov = (float)Settings::Misc::misc_FovView;
	}
}

void CMisc::OnGetViewModelFOV(float& fov)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		fov = (float)Settings::Misc::misc_FovModelView;
	}
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int DrawIndex = 1;

		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);

			if (Pinfo.m_bIsFakePlayer)
				continue;

			if (g_pRender)
			{
				string Name = Pinfo.m_szPlayerName;

				if (Name != "")
				{
					Color PlayerObsColor;
					//[junk_disable /]
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						Name.append(" - Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						Name.append(" - 3rd person");
						PlayerObsColor = Color::Aqua();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						Name.append(" - Free look");
						PlayerObsColor = Color::Red();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						Name.append(" - Deathcam");
						PlayerObsColor = Color::Yellow();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						Name.append(" - Freezecam");
						PlayerObsColor = Color::LimeGreen();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						Name.append(" - Fixed");
						PlayerObsColor = Color::Orange();
						break;
					default:
						break;
					}
					//[junk_enable /]
					g_pRender->Text(iScreenWidth - 300, 300 + (DrawIndex * 13), false, true, PlayerObsColor, "%s", Name.c_str());
					DrawIndex++;
				}
			}
		}
	}
}