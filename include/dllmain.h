#ifndef DLLMAIN
	#define DLLMAIN

	UINT APIENTRY MainThread(void* pHandle);

	BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason_for_call, LPVOID lpReserved);
#endif