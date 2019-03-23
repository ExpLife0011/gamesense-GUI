#include "Main.h"
#include "../RL/ReflectiveLoader.h"


//[enc_string_enable /]
//[junk_enable /]
DWORD WINAPI CheatEntry(LPVOID lpThreadParameter)
{
	HMODULE hModule = (HMODULE)lpThreadParameter;

	if (Engine::Initialize())
	{
		return 0;
	}

	return 0;
}

bool IsProcessRun(const char * const processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);

	while (1) {
		if (strcmp(pe.szExeFile, processName) == 0) return true;
		if (!Process32Next(hSnapshot, &pe)) return false;
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	/*if (IsProcessRun("devenv.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("idaq64.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("idaq32.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ServiceHub.Host.CLR.x86.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ServiceHub.SettingsHost.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ServiceHub.IdentityHost.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ServiceHub.VSDetouredHost.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ServiceHub.Host.Node.x86.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("PerfWatson2.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}

	if (IsProcessRun("ollydbg.exe"))
	{
		MessageBox(0, "Dont cryak debil blyad!1!", "Anti-Crack System", MB_OK);
		exit(1);
	}*/

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		Client::BaseDir = CSX::Utils::GetHackWorkingDirectory().c_str();

		if (Client::BaseDir.size() < 1)
		{
			Client::BaseDir = CSX::Utils::GetModuleBaseDir(hinstDLL);
		}

#if ENABLE_DEBUG_FILE == 1
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		Client::LogFile = Client::BaseDir + "\\debug.log";
		DeleteFileA(Client::LogFile.c_str());
		CSX::Log::LogFile = Client::LogFile;
		printf("Client::BaseDir = %s\nClient::LogFile = %s\n", Client::BaseDir.c_str(), Client::LogFile.c_str());
		CSX::Log::Add("::Init::");

#endif

		CreateThread(0, 0, CheatEntry, hinstDLL, 0, 0);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		Engine::Shutdown();
	}

	return TRUE;
}