#include <framework.h>

DLLHOOK OnLoad()
{
	MH_Initialize();
	GameHook::CreateGameHooks();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved)
{
	if(callReason == DLL_PROCESS_ATTACH)
		DisableThreadLibraryCalls(hModule);
	else if(callReason == DLL_PROCESS_DETACH)
        MH_Uninitialize();

    return TRUE;
}