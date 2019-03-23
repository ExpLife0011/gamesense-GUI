#include "Esp.h"
#include "../../Engine/Render.h"
#include "../../SDK/beambullets.h"
#include "../../SDK/BeamsInclude.h"
std::vector<cbullet_tracer_info> logs;

using namespace Client;
//[enc_string_enable /]
//[junk_enable /]
CSoundEsp::CSoundEsp()
{
	SoundColor = Color::White();
}

static int SoundAlpha = 255;

void CSoundEsp::Update()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		if (Sound[i].dwTime + 800 <= GetTickCount64())
		{
			if (SoundAlpha != 0)
				SoundAlpha -= 1;

			if (SoundAlpha == 0)
			{
				Sound.erase(Sound.begin() + i);
				SoundAlpha = 255;
			}
		}
	}
}

void CSoundEsp::AddSound(Vector vOrigin)
{
	Sound_s Sound_Entry;

	Sound_Entry.dwTime = GetTickCount64();
	Sound_Entry.vOrigin = vOrigin;

	Sound.push_back(Sound_Entry);
}

void Draw3DTriangle(Vector pos, float size, Color color)
{
	// Drawing a Triangle
	Vector up, right, left, up_right, up_left;
	Vector s_up, s_right, s_left, s_up_right, s_up_left;

	up[0] = pos[0];
	up[1] = pos[1];
	up[2] = pos[2] + size / 2;

	WorldToScreen(up, s_up);

	up_left[0] = pos[0] - size / 2;
	up_left[1] = pos[1] + size / 2;
	up_left[2] = pos[2] - size / 2;

	WorldToScreen(up_left, s_up_left);

	up_right[0] = pos[0] + size / 2;
	up_right[1] = pos[1] + size / 2;
	up_right[2] = pos[2] - size / 2;

	WorldToScreen(up_right, s_up_right);

	right[0] = pos[0] + size / 2;
	right[1] = pos[1] - size / 2;
	right[2] = pos[2] - size / 2;

	WorldToScreen(right, s_right);

	left[0] = pos[0] - size / 2;
	left[1] = pos[1] - size / 2;
	left[2] = pos[2] - size / 2;

	WorldToScreen(left, s_left);


	g_pRender->DrawLine(s_right[0], s_right[1], s_left[0], s_left[1], color);

	g_pRender->DrawLine(s_right[0], s_right[1], s_up_right[0], s_up_right[1], color);
	g_pRender->DrawLine(s_left[0], s_left[1], s_up_left[0], s_up_left[1], color);

	g_pRender->DrawLine(s_up_right[0], s_up_right[1], s_up_left[0], s_up_left[1], color);

	g_pRender->DrawLine(s_right[0], s_right[1], s_up[0], s_up[1], color);
	g_pRender->DrawLine(s_left[0], s_left[1], s_up[0], s_up[1], color);
	g_pRender->DrawLine(s_up_left[0], s_up_left[1], s_up[0], s_up[1], color);
	g_pRender->DrawLine(s_up_right[0], s_up_right[1], s_up[0], s_up[1], color);
}

void CSoundEsp::DrawSoundEsp()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		Vector vScreen;

		CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		CPlayer* pPlayer;

		if (WorldToScreen(Sound[i].vOrigin, vScreen))
		{
			if (Settings::Esp::esp_Sound)
			{
				if (Settings::Esp::esp_SoundType == 0)
				{
					CSoundEsp::DrawWave(Sound[i].vOrigin, (int)Settings::Esp::esp_SoundSize, Color::White());
				}
				if (Settings::Esp::esp_SoundType == 1)
				{
					g_pRender->DrawBox((int)vScreen.x, (int)vScreen.y, (int)Settings::Esp::esp_SoundSize, (int)Settings::Esp::esp_SoundSize, Color::White());
				}
				if (Settings::Esp::esp_SoundType == 2)
				{
					Draw3DTriangle(Sound[i].vOrigin, (int)Settings::Esp::esp_SoundSize, Color::White());
				}
			}
		}
	}
}

void CSoundEsp::DrawWave(Vector loc, float radius, Color color)
{
	static float Step = M_PI * 3.0f / 40;
	Vector prev;
	for (float lat = 0; lat <= M_PI * 3.0f; lat += Step)
	{
		float sin1 = sin(lat);
		float cos1 = cos(lat);
		float sin3 = sin(0.0);
		float cos3 = cos(0.0);

		Vector point1;
		point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
		Vector point3 = loc;
		Vector Out;
		point3 += point1;

		if (WorldToScreen(point3, Out))
		{
			if (lat > 0.000)
				g_pRender->DrawLine(prev.x, prev.y, Out.x, Out.y, color);
		}
		prev = Out;
	}
}

CEsp::CEsp()
{
	// Öâåòà õï áàðà

	CT_HP_ColorM.SetColor(255, 64, 64);
	TT_HP_ColorM.SetColor(255, 64, 64);

	// Öâåòà àðìîð áàðà

	CT_AR_ColorM.SetColor(255, 64, 64);
	TT_AR_ColorM.SetColor(255, 64, 64);

	visible_flat = nullptr;
	visible_tex = nullptr;
	hidden_flat = nullptr;
	hidden_tex = nullptr;

	fExplodeC4Timer = 0.f;
	fC4Timer = 0.f;
}

Color CEsp::GetPlayerColor(CPlayer* pPlayer)
{
	Color CT_Color(int(Settings::Esp::esp_Color_CT[0] * 255.f), int(Settings::Esp::esp_Color_CT[1] * 255.f), int(Settings::Esp::esp_Color_CT[2] * 255.f));
	Color TT_Color(int(Settings::Esp::esp_Color_TT[0] * 255.f), int(Settings::Esp::esp_Color_TT[1] * 255.f), int(Settings::Esp::esp_Color_TT[2] * 255.f));

	if (pPlayer->Team == TEAM_CT)
	{
		return CT_Color;
	}
	else if (pPlayer->Team == TEAM_TT)
	{
		return TT_Color;
	}

	return Color::White();
}

Color CEsp::GetPlayerVisibleColor(CPlayer* pPlayer)
{
	Color PlayerColor = GetPlayerColor(pPlayer);

	bool SetColor = false;

	if (pPlayer->bVisible)
	{
		if (Settings::Esp::esp_Visible == 1) // Âñåõ
		{
			SetColor = true;
		}

		Color VCT_Color(int(Settings::Esp::esp_Color_VCT[0] * 255.f), int(Settings::Esp::esp_Color_VCT[1] * 255.f), int(Settings::Esp::esp_Color_VCT[2] * 255.f));
		Color VTT_Color(int(Settings::Esp::esp_Color_VTT[0] * 255.f), int(Settings::Esp::esp_Color_VTT[1] * 255.f), int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		if (SetColor)
		{
			if (pPlayer->Team == TEAM_CT)
			{
				PlayerColor = VCT_Color;
			}
			else if (pPlayer->Team == TEAM_TT)
			{
				PlayerColor = VTT_Color;
			}
		}
	}

	return PlayerColor;
}

bool CEsp::CheckPlayerTeam(CPlayer* pPlayer)
{
	bool CheckTeam = false;
	bool PlayerVisible = pPlayer->bVisible;

	// Ïîêàçûâàåì esp òîëüêî íà:
	if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // Ïðîòèâíèêîâ
		CheckTeam = true;

	if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // Ñâîèõ
		CheckTeam = true;

	if (Settings::Esp::esp_Visible == 0 && !PlayerVisible)
		CheckTeam = false;

	return CheckTeam;
}

void CEsp::Dlight(CPlayer* pPlayer)
{
	if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
	{
		Vector getorig = pPlayer->m_pEntity->GetOrigin();
		Vector getheadorig = pPlayer->m_pEntity->GetEyePosition();
		Color EspVisibleColor = GetPlayerVisibleColor(pPlayer);
		dlight_t* pElight = Interfaces::Effects()->CL_AllocElight(pPlayer->m_pEntity->EntIndex());
		pElight->color.r = float(Settings::Esp::esp_Dlight[0] * 255.f);
		pElight->color.g = float(Settings::Esp::esp_Dlight[1] * 255.f);;
		pElight->color.b = float(Settings::Esp::esp_Dlight[2] * 255.f);;
		pElight->color.exponent = 8.f;
		pElight->m_Direction = getheadorig;
		pElight->origin = getheadorig;
		pElight->radius = (Settings::Esp::esp_DlightSize * 2) - 60;
		pElight->die = Interfaces::GlobalVars()->curtime + 0.1f;
		pElight->decay = 25.0f;
		pElight->key = pPlayer->m_pEntity->EntIndex();
		dlight_t* pDlight = Interfaces::Effects()->CL_AllocDlight(pPlayer->m_pEntity->EntIndex());
		pDlight->color.r = float(Settings::Esp::esp_Dlight[0] * 255.f);;
		pDlight->color.g = float(Settings::Esp::esp_Dlight[1] * 255.f);;
		pDlight->color.b = float(Settings::Esp::esp_Dlight[2] * 255.f);;
		pDlight->color.exponent = 8.f;
		pDlight->m_Direction = getorig;
		pDlight->origin = getorig;
		pDlight->radius = Settings::Esp::esp_DlightSize;
		pDlight->die = Interfaces::GlobalVars()->curtime + 0.1f;
		pDlight->decay = pDlight->radius / 5.f;
		pDlight->key = pPlayer->m_pEntity->EntIndex();
	}
}

bool nightz = false;
void CEsp::NightMode()
{
	if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
	{
		if (Settings::Esp::esp_NightMode)
		{
			if (!nightz)
			{
				static auto sv_skyname = Interfaces::GetConVar()->FindVar("sv_skyname");
				static auto r_DrawSpecificStaticProp = Interfaces::GetConVar()->FindVar("r_DrawSpecificStaticProp");
				r_DrawSpecificStaticProp->SetValue(1);
				sv_skyname->SetValue("sky_csgo_night02");

				for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
				{
					IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

					if (!pMaterial)
						continue;

					const char* group = pMaterial->GetTextureGroupName();
					const char* name = pMaterial->GetName();

					if (strstr(group, "World textures"))
					{
						pMaterial->ColorModulate(0.10, 0.10, 0.10);
					}
					if (strstr(group, "StaticProp"))
					{
						pMaterial->ColorModulate(0.30, 0.30, 0.30);
					}
					if (strstr(name, "models/props/de_dust/palace_bigdome"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					}
					if (strstr(name, "models/props/de_dust/palace_pillars"))
					{
						pMaterial->ColorModulate(0.30, 0.30, 0.30);
					}

					if (strstr(group, "Particle textures"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					}
					nightz = true;
				}

			}

		}
		else
		{
			if (nightz)
			{
				for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
				{
					IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

					if (!pMaterial)
						continue;

					const char* group = pMaterial->GetTextureGroupName();
					const char* name = pMaterial->GetName();

					if (strstr(group, "World textures"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(group, "StaticProp"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(name, "models/props/de_dust/palace_bigdome"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
					}
					if (strstr(name, "models/props/de_dust/palace_pillars"))
					{

						pMaterial->ColorModulate(1, 1, 1);
					}
					if (strstr(group, "Particle textures"))
					{
						pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
					}
				}

				nightz = false;
			}
		}
	}
}

void CEsp::Sound(CPlayer* pPlayer)
{
	int SoundDistance = pPlayer->iDistance;

	if (Settings::Esp::esp_Sound)
	{
		if (SoundDistance <= Settings::Esp::esp_SoundDistance)
			SoundEsp.DrawSoundEsp();
	}
}

void CEsp::OnRender()
{
	NightMode();

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate && CheckPlayerTeam(pPlayer))
		{
			DrawPlayerEsp(pPlayer);

			Sound(pPlayer);

			if (Settings::Esp::esp_Skeleton)
				DrawPlayerSkeleton(pPlayer);

			if (Settings::Esp::esp_BulletTrace)
				DrawPlayerBulletTrace(pPlayer);

			if (Settings::Esp::esp_Dlightz)
				Dlight(pPlayer);
		}
	}

	if (Settings::Esp::esp_BombTimer)
	{
		if (bC4Timer && iC4Timer)
		{
			float fTimeStamp = Interfaces::Engine()->GetLastTimeStamp();

			if (!fExplodeC4Timer)
			{
				fExplodeC4Timer = fTimeStamp + (float)iC4Timer;
			}
			else
			{
				fC4Timer = fExplodeC4Timer - fTimeStamp;

				if (fC4Timer < 0.f)
					fC4Timer = 0.f;
			}
		}
		else
		{
			fExplodeC4Timer = 0.f;
			fC4Timer = 0.f;
		}
	}

	if (Settings::Esp::esp_Bomb || Settings::Esp::esp_WorldWeapons || Settings::Esp::esp_WorldGrenade)
	{
		for (int EntIndex = 0; EntIndex < Interfaces::EntityList()->GetHighestEntityIndex(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity || pEntity->IsPlayer())
				continue;

			const model_t* pModel = pEntity->GetModel();
			int iHpAmY = 1;
			if (pModel)
			{
				const char* pModelName = Interfaces::ModelInfo()->GetModelName(pModel);

				if (pModelName)
				{
					Vector vEntScreen;

					if (WorldToScreen(pEntity->GetRenderOrigin(), vEntScreen))
					{
						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y + iHpAmY, true, true, Color::Yellow(),
								"[C4]");
							iHpAmY += 20;
						}
						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Yellow(), "[C4]");
						}

						if (Settings::Esp::esp_WorldWeapons && !strstr(pModelName, "models/weapons/w_eq_") && !strstr(pModelName, "models/weapons/w_ied"))
						{
							if (strstr(pModelName, "models/weapons/w_") && strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 17;

								WeaponName[WeaponName.size() - 12] = '\0';

								if (strstr(pModelName, "models/weapons/w_rif") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_pist") && strstr(pModelName, "_dropped.mdl") && !strstr(pModelName, "models/weapons/w_pist_223"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_smg") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_mach") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_shot") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_snip") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								if (strstr(pModelName, "models/weapons/w_pist_223") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "usp_s";
								}
								if (strstr(pModelName, "models/weapons/w_pist_hkp2000") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "p2000";
								}
								if (strstr(pModelName, "models/weapons/w_pist_cz_75") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "cz75";
								}
								if (strstr(pModelName, "models/weapons/w_rif_m4a1") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "m4a4";
								}
								if (strstr(pModelName, "models/weapons/w_rif_m4a1_s") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "m4a1_s";
								}
								if (strstr(pModelName, "models/weapons/w_rif_sg556") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "sg553";
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
									WeaponName.c_str());
							}
						}

						if (Settings::Esp::esp_WorldGrenade && (strstr(pModelName, "models/weapons/w_eq_") || strstr(pModelName, "models/Weapons/w_eq_")))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 20;

								WeaponName[WeaponName.size() - 12] = '\0';

								Color GrenadeColor = Color::White();

								if (strstr(pModelName, "fraggrenade"))
								{
									WeaponName = "grenade";
								}
								else if (strstr(pModelName, "molotov"))
								{
									WeaponName = "fire_molo";
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									WeaponName = "fire_ince";
								}
								else if (strstr(pModelName, "flashbang"))
								{
									WeaponName = "flash";
								}
								else if (strstr(pModelName, "smokegrenade"))
								{
									WeaponName = "smoke";

									g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
										WeaponName.c_str());

								}
								else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
								{
									string WeaponName;

									WeaponName = "smoke";

									g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
										WeaponName.c_str());

								}
								else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
								{
									string WeaponName;
									WeaponName = "smoke";

									g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
										WeaponName.c_str());

								}
								else if (strstr(pModelName, "taser.mdl") && Settings::Esp::esp_Outline == true)
								{
									string WeaponName;

									WeaponName = "Zeus";

									g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
										WeaponName.c_str());
								}
							}
						}
					}
				}
			}
		}
	}
}

void MsgFunc_ServerRankRevealAll()
{
	using tServerRankRevealAllFn = bool(__cdecl*)(int*);
	static tServerRankRevealAllFn ServerRankRevealAll = 0;

	if (!ServerRankRevealAll)
	{
		ServerRankRevealAll = (tServerRankRevealAllFn)(
			CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 8B 0D ? ? ? ? 68", 0));
	}

	if (ServerRankRevealAll)
	{
		int fArray[3] = { 0,0,0 };
		ServerRankRevealAll(fArray);
	}
}

void CEsp::OnCreateMove(CUserCmd* pCmd)
{
	if (Settings::Esp::esp_Rank && pCmd->buttons & IN_SCORE)
		MsgFunc_ServerRankRevealAll();

	g_pEsp->SoundEsp.Update();
}

void CEsp::OnReset()
{
	g_pEsp->SoundEsp.Sound.clear();

	if (Settings::Esp::esp_BombTimer)
	{
		if (Settings::Esp::esp_BombTimer > 60)
			Settings::Esp::esp_BombTimer = 60;

		bC4Timer = false;
		iC4Timer = Settings::Esp::esp_BombTimer;
	}
}

void CEsp::OnEvents(IGameEvent* pEvent)
{
	if (g_pEsp && Settings::Esp::esp_BombTimer)
	{
		if (!strcmp(pEvent->GetName(), "bomb_defused") || !strcmp(pEvent->GetName(), "bomb_exploded"))
		{
			bC4Timer = false;
		}
		else if (!strcmp(pEvent->GetName(), "bomb_planted"))
		{
			bC4Timer = true;
		}
	}
}

void CEsp::OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (!g_pPlayers || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsConnected() || !pInfo.pModel)
		return;

	static bool InitalizeMaterial = false;

	if (!InitalizeMaterial)
	{
		visible_flat = CreateMaterial(true, false);
		visible_tex = CreateMaterial(false, false);
		hidden_flat = CreateMaterial(true, true);
		hidden_tex = CreateMaterial(false, true);

		InitalizeMaterial = true;

		return;
	}

	string strModelName = Interfaces::ModelInfo()->GetModelName(pInfo.pModel);

	if (strModelName.size() <= 1)
		return;

	if (Settings::Esp::esp_Chams && Client::g_pPlayers && Client::g_pPlayers->GetLocal() && strModelName.find("models/player") != string::npos)
	{
		IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

		if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
		{
			CPlayer* pPlayer = g_pPlayers->GetPlayer(pInfo.entity_index);

			if (pPlayer && pPlayer->bUpdate)
			{
				bool CheckTeam = false;

				Color TeamHideColor;
				Color TeamVisibleColor;

				if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // Ïðîòèâíèêîâ
					CheckTeam = true;

				if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // Ñâîèõ
					CheckTeam = true;

				if (pPlayer->Team == TEAM_CT)
				{
					TeamHideColor = Color(int(Settings::Esp::chams_Color_CT[0] * 255.f),
						int(Settings::Esp::chams_Color_CT[1] * 255.f),
						int(Settings::Esp::chams_Color_CT[2] * 255.f));
				}
				else if (pPlayer->Team == TEAM_TT)
				{
					TeamHideColor = Color(int(Settings::Esp::chams_Color_TT[0] * 255.f),
						int(Settings::Esp::chams_Color_TT[1] * 255.f),
						int(Settings::Esp::chams_Color_TT[2] * 255.f));
				}

				bool SetColor = false;

				if (Settings::Esp::esp_ChamsVisible == 1) // chams wall
				{
					SetColor = true;
				}

				if (SetColor)
				{
					if (pPlayer->Team == TEAM_CT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VCT[0] * 255.f),
							int(Settings::Esp::chams_Color_VCT[1] * 255.f),
							int(Settings::Esp::chams_Color_VCT[2] * 255.f));
					}
					else if (pPlayer->Team == TEAM_TT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VTT[0] * 255.f),
							int(Settings::Esp::chams_Color_VTT[1] * 255.f),
							int(Settings::Esp::chams_Color_VTT[2] * 255.f));
					}
				}
				else
					TeamVisibleColor = TeamHideColor;

				if (CheckTeam)
				{
					if (Settings::Esp::esp_ChamsVisible == 1) //chams vis
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (Settings::Esp::esp_Chams == 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (Settings::Esp::esp_Chams == 4)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
						}
					}
					else
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (Settings::Esp::esp_Chams == 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (Settings::Esp::esp_Chams == 4)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
						}
					}

					Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

					if (Settings::Esp::esp_Chams == 1)
					{
						ForceMaterial(TeamVisibleColor, visible_flat);
						visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
					else if (Settings::Esp::esp_Chams == 2)
					{
						ForceMaterial(TeamVisibleColor, visible_tex, true);
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
					else if (Settings::Esp::esp_Chams == 3)
					{
						float Blend[3] = { (float)TeamVisibleColor[0], (float)TeamVisibleColor[1], (float)TeamVisibleColor[2] };
						Interfaces::RenderView()->SetColorModulation(Blend);
					}
					else if (Settings::Esp::esp_Chams == 4)
					{
						ForceMaterial(TeamHideColor, hidden_tex);
						hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
				}
			}
		}
	}
}


void CEsp::DrawPlayerEsp(CPlayer* pPlayer)
{
	bool bOriginScreen = (pPlayer->vOriginScreen.x > 0 && pPlayer->vOriginScreen.y > 0);
	bool bHitBoxScreen = (pPlayer->vHitboxHeadScreen.x > 0 && pPlayer->vHitboxHeadScreen.y > 0);

	if (!bOriginScreen && !bHitBoxScreen)
		return;

	Vector vLineOrigin;

	if (Settings::Esp::esp_Size < 1)
	{
		Settings::Esp::esp_Size = 1;
	}
	else if (Settings::Esp::esp_Size > 10)
	{
		Settings::Esp::esp_Size = 10;
	}

	int Height = (int)pPlayer->vOriginScreen.y - (int)pPlayer->vHitboxHeadScreen.y;

	if (Height < 18)
		Height = 18;

	int Width = Height / 2;

	int x = (int)pPlayer->vHitboxHeadScreen.x - Width / 2;
	int y = (int)pPlayer->vHitboxHeadScreen.y;

	vLineOrigin = pPlayer->vHitboxHeadScreen;
	vLineOrigin.y += Height;

	Color EspPlayerColor = GetPlayerColor(pPlayer);
	Color EspVisibleColor = GetPlayerVisibleColor(pPlayer);

	if (Settings::Esp::esp_Box)
	{
		if (Settings::Esp::esp_Style == 0)  //Box
		{
			if (Settings::Esp::esp_FillBox)
			{
				g_pRender->DrawAlphaBox(x, y, Width, Height, EspVisibleColor);
			}
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineBox(x, y, Width, Height, EspVisibleColor);
			}
		}
		else if (Settings::Esp::esp_Style == 1)  //CoalBox
		{
			if (Settings::Esp::esp_FillBox)
			{
				g_pRender->DrawAlphaBox(x, y, Width, Height, EspVisibleColor);
			}
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawCoalBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineCoalBox(x, y, Width, Height, EspVisibleColor);
			}
		}
		else if (Settings::Esp::esp_Style == 2)  //CoalBox
		{
			if (Settings::Esp::esp_FillBox)
			{
				g_pRender->DrawAlphaBox(x, y + Width / 2, Width, Width, EspVisibleColor);
			}
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawBox(x, y + Width / 2, Width, Width, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineBox(x, y + Width / 2, Width, Width, EspVisibleColor);
			}
		}
	}

	if (Settings::Esp::esp_Line)
	{
		g_pRender->DrawLine((int)vLineOrigin.x, (int)vLineOrigin.y, iScreenWidth / 2, iScreenHeight / 2, EspVisibleColor);
	}

	int DistanceMod = pPlayer->iDistance;

	if (Settings::Esp::esp_Name)
	{
		g_pRender->Text((int)vLineOrigin.x, (int)pPlayer->vHitboxHeadScreen.y - 13, true, true, EspVisibleColor, pPlayer->Name.c_str());
	}

	int iHpAmY = 1;

	if (Settings::Esp::esp_Health >= 1) //None
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_HP_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_HP_ColorM;
		}

		int iHealth = pPlayer->iHealth;

		if (iHealth)
		{
			if (Settings::Esp::esp_Health == 1) //Number
			{
				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, Color::Green(), to_string(iHealth).c_str());
				iHpAmY += 10;
			}
			else if (Settings::Esp::esp_Health == 2) //Bottom
			{
				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iHealth, Color::Green(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Health == 3) //Left
			{
				g_pRender->DrawVerBar(x - 6, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iHealth, Color::Green(), Minus);
			}
			else if (Settings::Esp::esp_Health == 4)
			{
				float flBoxes = std::ceil(pPlayer->iHealth / 10.f);
				float flX = x - 6;
				float flY = y - 1;
				float flHeight = Height / 10.f;
				float flMultiplier = 12 / 360.f;
				flMultiplier *= flBoxes - 1;
				Color ColHealth = Color::FromHSB(flMultiplier, 1, 1);

				g_pRender->DrawBox(flX, flY, 4, Height + 2, Color(80, 80, 80, 125));
				g_pRender->DrawOutlineBox(flX, flY, 4, Height + 2, Color::Black());
				g_pRender->DrawBox(flX + 1, flY, 2, flHeight * flBoxes + 1, ColHealth);

				for (int i = 0; i < 10; i++)
				{
					g_pRender->DrawLine(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color::Black());
				}
			}
		}
	}

	if (Settings::Esp::esp_Armor >= 1) //None
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_AR_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_AR_ColorM;
		}

		int iArmor = pPlayer->iArmor;

		if (iArmor)
		{
			if (Settings::Esp::esp_Armor == 1) //Number
			{
				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspVisibleColor, to_string(iArmor).c_str());
				iHpAmY += 10;
			}
			if (Settings::Esp::esp_Armor == 2) //Bottom
			{
				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iArmor, Color::White(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Armor == 3) //Right
			{
				g_pRender->DrawVerBar(x + Width + 1, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iArmor, Color::White(), Minus);
			}
			else if (Settings::Esp::esp_Armor == 4)
			{
				float flBoxes = std::ceil(pPlayer->iArmor / 10.f);
				float flX = x - 6;
				float flY = y - 1;
				float flHeight = Height / 10.f;
				float flMultiplier = 12 / 360.f;
				flMultiplier *= flBoxes - 1;
				Color ColArmor = Color::White();

				g_pRender->DrawBox(flX, flY, 4, Height + 2, Color::White());
				g_pRender->DrawOutlineBox(flX, flY, 4, Height + 2, Color::Black());
				g_pRender->DrawBox(flX + 1, flY, 2, flHeight * flBoxes + 1, ColArmor);

				for (int i = 0; i < 10; i++)
				{
					g_pRender->DrawLine(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color::Black());
				}
			}
		}
	}
	if (Settings::Esp::esp_Weapon && !pPlayer->WeaponName.empty())
	{
		string WeaponStr = pPlayer->WeaponName;

		if (Settings::Esp::esp_Ammo && pPlayer->iWAmmo)
		{
			WeaponStr += " [";
			WeaponStr += to_string(pPlayer->iWAmmo);
			WeaponStr += "]";
		}

		g_pRender->Text((int)vLineOrigin.x + Settings::Esp::weapon_x, (int)vLineOrigin.y + iHpAmY + Settings::Esp::weapon_y, true, true, EspVisibleColor, WeaponStr.c_str());
		iHpAmY += 10;
	}

	if (Settings::Esp::esp_Distance && g_pPlayers->GetLocal()->bAlive)
	{
		int Distance = pPlayer->iDistance;
		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspVisibleColor, to_string(Distance).c_str());
	}
}

void CEsp::DrawPlayerSkeleton(CPlayer* pPlayer)
{
	Color SkeletonColor = GetPlayerColor(pPlayer);

	Color EspPlayerColor = GetPlayerColor(pPlayer);
	Color EspVisibleColor = GetPlayerVisibleColor(pPlayer);

	for (BYTE IndexArray = 0; IndexArray < 18; IndexArray++)
	{
		DrawHitBoxLine(pPlayer->vHitboxSkeletonArray[IndexArray], EspVisibleColor);
	}
}

void CEsp::DrawPlayerBulletTrace(CPlayer* pPlayer)
{
	Color EspColor = GetPlayerColor(pPlayer);

	if (!pPlayer->vBulletTraceArray[0].IsZero() && !pPlayer->vBulletTraceArray[1].IsZero())
	{
		g_pRender->DrawLine(
			(int)pPlayer->vBulletTraceArray[0].x, (int)pPlayer->vBulletTraceArray[0].y,
			(int)pPlayer->vBulletTraceArray[1].x, (int)pPlayer->vBulletTraceArray[1].y, EspColor);

		g_pRender->DrawFillBox((int)pPlayer->vBulletTraceArray[1].x - 2, (int)pPlayer->vBulletTraceArray[1].y - 2, 4, 4, EspColor);
	}
}

void CEsp::DrawHitBoxLine(Vector* vHitBoxArray, Color color)
{
	Vector vHitBoxOneScreen;
	Vector vHitBoxTwoScreen;

	if (vHitBoxArray[0].IsZero() || !vHitBoxArray[0].IsValid() || vHitBoxArray[1].IsZero() || !vHitBoxArray[1].IsValid())
		return;

	if (WorldToScreen(vHitBoxArray[0], vHitBoxOneScreen) && WorldToScreen(vHitBoxArray[1], vHitBoxTwoScreen))
	{
		g_pRender->DrawLine((int)vHitBoxOneScreen.x, (int)vHitBoxOneScreen.y,
			(int)vHitBoxTwoScreen.x, (int)vHitBoxTwoScreen.y, color);
	}
}
