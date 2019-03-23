#include "Client.h"
#include <chrono>

//[enc_string_enable /]
//[junk_enable /]

namespace Client
{
	//[swap_lines]
	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	string BaseDir = "";
	string LogFile = "";
	string GuiFile = "";
	string IniFile = "";

	vector<string> ConfigList;

	Vector2D	g_vCenterScreen = Vector2D(0.f, 0.f);

	CPlayers*	g_pPlayers = nullptr;
	CRender*	g_pRender = nullptr;
	CGui*		g_pGui = nullptr;

	CAimbot*	g_pAimbot = nullptr;
	CEsp*		g_pEsp = nullptr;
	CRadar*		g_pRadar = nullptr;
	CSkin*		g_pSkin = nullptr;
	CMisc*		g_pMisc = nullptr;
	//ImFont* tabfont;
	ImFont* font;
	bool		bC4Timer = false;
	int			iC4Timer = 40;

	int			iWeaponID = 0;
	int			iWeaponSelectIndex = WEAPON_DEAGLE;
	int			iWeaponSelectSkinIndex = -1;
	//[/swap_lines]

	void ReadConfigs(LPCTSTR lpszFileName)
	{
		if (!strstr(lpszFileName, "gui.ini"))
		{
			ConfigList.push_back(lpszFileName);
		}
	}

	void RefreshConfigs()
	{
		ConfigList.clear();
		string ConfigDir = BaseDir + "\\*.ini";
		SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
	}

	bool Initialize(IDirect3DDevice9* pDevice)
	{
		g_pPlayers = new CPlayers();
		g_pRender = new CRender(pDevice);
		g_pGui = new CGui();

		g_pAimbot = new CAimbot();
		g_pEsp = new CEsp();
		g_pRadar = new CRadar();
		g_pSkin = new CSkin();
		g_pMisc = new CMisc();

		GuiFile = BaseDir + "\\" + "gui.ini";
		IniFile = BaseDir + "\\" + "settings.ini";

		g_pSkin->InitalizeSkins();

		Settings::LoadSettings(IniFile);

		iWeaponSelectSkinIndex = GetWeaponSkinIndexFromPaintKit(g_SkinChangerCfg[iWeaponSelectIndex].nFallbackPaintKit);

		ImGuiIO& io = ImGui::GetIO();
		//ImFont* font1 = io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Vermin Vibes.ttf"), 14);
		ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(Avalon_compressed_data, Avalon_compressed_size, 12.f);
		//ImFont* tabfont = io.Fonts->AddFontFromMemoryCompressedTTF(icon_compressed_data, icon_compressed_size, 15.f);

		g_pGui->GUI_Init(pDevice);

		RefreshConfigs();

		return true;
	}

	void Shutdown()
	{
		DELETE_MOD(g_pPlayers);
		DELETE_MOD(g_pRender);
		DELETE_MOD(g_pGui);

		DELETE_MOD(g_pAimbot);
		DELETE_MOD(g_pEsp);
		DELETE_MOD(g_pRadar);
		DELETE_MOD(g_pSkin);
		DELETE_MOD(g_pMisc);
	}

	int get_fps()
	{
		using namespace std::chrono;
		static int count = 0;
		static auto last = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		static int fps = 0;

		count++;

		if (duration_cast<milliseconds>(now - last).count() > 1000) {
			fps = count;
			count = 0;
			last = now;
		}

		return fps;
	}

	void OnRender()
	{
		if (g_pRender && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp())
		{
			g_pRender->BeginRender();

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();

			Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			g_vCenterScreen.x = iScreenWidth / 2.f;
			g_vCenterScreen.y = iScreenHeight / 2.f;

			if (Settings::Misc::Watermark)
			{
				g_pRender->Text(186, 23, false, true, Color::Green(), "fps: %03d", get_fps());
				g_pRender->Text(62, 23, false, true, Color(108, 195, 18), "sense");
				g_pRender->Text(35, 23, false, true, Color(255, 255, 255), "game          | time: %s | ", __TIME__);
			}

			if (Client::g_pPlayers && Client::g_pPlayers->GetLocal() && Interfaces::Engine()->IsInGame())
			{
				if (g_pEsp)
					g_pEsp->OnRender();

				if (g_pMisc)
				{
					g_pMisc->OnRender();
					g_pMisc->OnRenderSpectatorList();
				}

				if (g_pAimbot)
				{
					g_pAimbot->OnRender();
				}
			}
			g_pRender->EndRender();
		}
	}

	void OnLostDevice()
	{
		if (g_pRender)
			g_pRender->OnLostDevice();

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void OnResetDevice()
	{
		if (g_pRender)
			g_pRender->OnResetDevice();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	void OnCreateMove(CUserCmd* pCmd)
	{
		if (g_pPlayers && Interfaces::Engine()->IsInGame())
		{
			g_pPlayers->Update();

			if (g_pEsp)
				g_pEsp->OnCreateMove(pCmd);

			if (IsLocalAlive())
			{
				if (!bIsGuiVisible)
				{
					int iWeaponSettingsSelectID = GetWeaponSettingsSelectID();

					if (iWeaponSettingsSelectID >= 0)
						iWeaponID = iWeaponSettingsSelectID;
				}

				if (g_pMisc)
					g_pMisc->OnCreateMove(pCmd);

				if (g_pAimbot)
					g_pAimbot->OnCreateMove(pCmd, g_pPlayers->GetLocal());

				if (g_pAimbot)
					g_pAimbot->RCS();
			}
		}
	}

	void OnFireEventClientSideThink(IGameEvent* pEvent)
	{
		if (!strcmp(pEvent->GetName(), "player_connect_full") ||
			!strcmp(pEvent->GetName(), "round_start") ||
			!strcmp(pEvent->GetName(), "cs_game_disconnected"))
		{
			if (g_pPlayers)
				g_pPlayers->Clear();

			if (g_pEsp)
				g_pEsp->OnReset();
		}

		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{

			if (g_pEsp)
				g_pEsp->OnEvents(pEvent);

			if (g_pSkin)
				g_pSkin->OnEvents(pEvent);

			if (g_pAimbot)
				g_pAimbot->OnEvents(pEvent);

			if (g_pAimbot)
				g_pAimbot->BuyBot(pEvent);
		}
	}

	void OnFrameStageNotify(ClientFrameStage_t Stage)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{
			Skin_OnFrameStageNotify(Stage);
			Gloves_OnFrameStageNotify(Stage);
		}
	}

	void OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		if (Interfaces::Engine()->IsInGame() && ctx && pCustomBoneToWorld)
		{
			if (g_pEsp)
				g_pEsp->OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			if (g_pMisc)
				g_pMisc->OnDrawModelExecute();
		}
	}

	void OnPlaySound(const Vector* pOrigin, const char* pszSoundName)
	{
		if (!pszSoundName || !Interfaces::Engine()->IsInGame())
			return;

		if (!strstr(pszSoundName, "bulletLtoR") &&
			!strstr(pszSoundName, "rics/ric") &&
			!strstr(pszSoundName, "impact_bullet"))
		{
			if (g_pEsp && IsLocalAlive() && Settings::Esp::esp_Sound && pOrigin)
			{
				if (!GetVisibleOrigin(*pOrigin))
					g_pEsp->SoundEsp.AddSound(*pOrigin);
			}
		}
	}

	void OnPlaySound(const char* pszSoundName)
	{
		if (g_pMisc)
			g_pMisc->OnPlaySound(pszSoundName);
	}

	void OnOverrideView(CViewSetup* pSetup)
	{
		if (g_pMisc)
			g_pMisc->OnOverrideView(pSetup);
	}

	void OnGetViewModelFOV(float& fov)
	{
		if (g_pMisc)
			g_pMisc->OnGetViewModelFOV(fov);
	}

	void AndroidMenu()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4(0.34f, 0.34f, 0.34f, 1.f);
	}

	void NeAndroidMenu()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	}

	void ImDrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
	{
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		Color colColor(0, 0, 0, 255);

		flRainbow += flSpeed;
		if (flRainbow > 1.f) flRainbow = 0.f;//1 0 

		for (int i = 0; i < width; i = i + 1)
		{
			float hue = (1.f / (float)width) * i;
			hue -= flRainbow;
			if (hue < 0.f) hue += 1.f;

			Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
			windowDrawList->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), colRainbow.GetU32());
		}
	}

	void OnRenderGUI()
	{
		using namespace ImGui;
		ImGuiStyle& style = ImGui::GetStyle();

		static int tabselected = 0;

		ImGui::SetNextWindowSize(ImVec2(780, 613));
		if (ImGui::BeginAndroid("##1", &bIsGuiVisible, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar ))
		{

			auto color_grey = ImGui::GetColorU32(ImVec4(0.4, 0.4, 0.4, 0.30));
			auto color_black = ImGui::GetColorU32(ImVec4(0.0, 0.0, 0.0, 0.20));
			ImVec2 p = ImGui::GetCursorScreenPos();

			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() / 2, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + 2), ImColor(122, 34, 173), ImColor(235, 29, 111), ImColor(235, 29, 111), ImColor(55, 177, 218));
			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y + 2), ImColor(51, 132, 255), ImColor(235, 29, 173), ImColor(235, 29, 111), ImColor(122, 34, 173));
			//ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x - 5, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / 2, ImGui::GetWindowPos().y + 2), color_black, color_black, color_black, color_black);
			//ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() / 2, ImGui::GetWindowPos().y - 6), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + 2), color_black, color_black, color_black, color_black);
			

			ImGui::BeginGroup();
			{
				g_pGui->iconset();
				ImGui::Spacing();
				if (tabselected == 0)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Aimbot", true, ImVec2(75, 75)))
						tabselected = 0;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("A", false, ImVec2(75, 75)))
						tabselected = 0;
				}

				if (tabselected == 1)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Misc", true, ImVec2(75, 75)))
						tabselected = 1;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("G", false, ImVec2(75, 75)))
						tabselected = 1;
				}

				if (tabselected == 2)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Visuals", true, ImVec2(75, 75)))
						tabselected = 2;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("D", false, ImVec2(75, 75)))
						tabselected = 2;
				}
				if (tabselected == 3)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Skins", true, ImVec2(75, 75)))
						tabselected = 3;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("B", false, ImVec2(75, 75)))
						tabselected = 3;
				}

				if (tabselected == 4)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Settings", true, ImVec2(75, 75)))
						tabselected = 4;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("F", false, ImVec2(75, 75)))
						tabselected = 4;
				}

				if (tabselected == 5)
				{
					ImGui::PushFont(font);
					if (ImGui::MyButton("Anti-Aim", true, ImVec2(75, 75)))
						tabselected = 5;
				}
				else
				{
					g_pGui->iconset();
					if (ImGui::MyButton("C", false, ImVec2(75, 75)))
						tabselected = 5;
				}
			}
			ImGui::EndGroup();
			ImGui::PushFont(font);
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				if (tabselected == 0)
				{
					ImGui::Text("");
					ImGui::SameLine(15.f);
					BeginChild("AimBot", ImVec2(220, 160), false, ImGuiWindowFlags_ChildZeusPaste);
					{
						Spacing();
						Spacing();
						Spacing();
						static bool boolean;
						static int slider1 = 5;
						SameLine(7);
						ImGui::Checkbox("checkbox1", &boolean);
						Spacing();
						Spacing();
						Spacing();									
						SameLine(7);
						PushItemWidth(170);
						SliderInt("Slider1", &slider1, 0, 100);
					}
					EndChild();
				}

				if (tabselected == 1)
				{

					ImGui::Text("");
					ImGui::SameLine(15.f);
					BeginChild("Misc", ImVec2(220, 160), false, ImGuiWindowFlags_ChildZeusPaste);
					{
						Spacing();
						Spacing();
						Spacing();
						SameLine(7);
						ImGui::Checkbox("Bhop", &Settings::Misc::misc_Bhop);
						Spacing();
						Spacing();
						SameLine(7);
						ImGui::Checkbox("Watermark", &Settings::Misc::Watermark);
					}
					EndChild();
				}

				if (tabselected == 2)
				{
					ImGui::Text("");
					ImGui::SameLine(15.f);
					BeginChild("Visuals", ImVec2(220, 160), false, ImGuiWindowFlags_ChildZeusPaste);
					{
						Spacing();
						Spacing();
						Spacing();
						SameLine(7);
						ImGui::Checkbox("Team", &Settings::Esp::esp_Team);
						Spacing();
						SameLine(7);
						ImGui::Checkbox("Enemy", &Settings::Esp::esp_Enemy);
						Spacing();
						Spacing();
						SameLine(7);
						ImGui::Checkbox("Bomb", &Settings::Esp::esp_Bomb);
						Spacing();
						SameLine(7);
						ImGui::Checkbox("ESP Name", &Settings::Esp::esp_Name);
						Spacing();
						SameLine(7);
						ImGui::Checkbox("ESP Skeleton", &Settings::Esp::esp_Skeleton);
						Spacing();
						SameLine(7);
						ImGui::Checkbox("ESP Weapon", &Settings::Esp::esp_Weapon);
						Spacing();
						SameLine(7);
						ImGui::Checkbox("ESP Health", &Settings::Esp::esp_Health);
						if (Settings::Esp::esp_Weapon)
						{
							Spacing();			
							Spacing();
							SameLine(7);
							ImGui::PushItemWidth(90.f);
							ImGui::Combo("Esp Weapon##", &Settings::Esp::esp_WeaponIcon, "Name\0\rIcon\0\0", -1);
							ImGui::PopItemWidth();
						}
					}
					EndChild();
				}

				if (tabselected == 3)
				{

				}

				if (tabselected == 4)
				{

				}
			}
			ImGui::EndGroup();
			ImGui::End();
		}
	}
}

