#include <framework.h>

namespace GameHook
{
    // Multi Skill Equip
    const SHORT bytePattern[] = { 0xB0, 0x01, 0xEB, 0x100, 0x48, 0x8D, 0x8B, 0x100, 0x100, 0x100, 0x100, 0xBA, 0x03 };

    const SHORT patternLength = 13;

    const SHORT patternOffset = 0xB;

    // Name of the module in which to scan for byte patterns.
    const WCHAR moduleName[] = L"ShadowOfWar.exe";

    AOBScanner pScanner;

    // Injections and scanned addresses.
    extern "C"
    {
        EXPORT BYTE* urukIntelAddress = nullptr;
        UINT_PTR urukIntelJmpAddress = 0;
        INSTRUCTIONSET UrukFullIntelInjectCode()
        {
            __asm__ 
            (
                "mov (%rcx), %edx\n\t"
                "or $0xFB, %edx\n\t" // Set temp uruk intel bitfield
                "mov %edx, (%rcx)\n\t"
                "mov 0xA(%rcx), %edx\n\t"
                "and $0xFFFFFFFE, %edx\n\t"
                "or $2, %edx\n\t" // Set perm uruk intel bitfield
                "mov %edx, 0xA(%rcx)\n\t"
                "mov $3, %edx\n\t"
                "jmp *urukIntelJmpAddress"
            );
        }

        INSTRUCTIONSET UrukPartialIntelInjectCode()
        {
            __asm__ 
            (
                "mov (%rcx), %edx\n\t"
                "or $0xDB, %edx\n\t" // Set temp uruk intel bitfield
                "mov %edx, (%rcx)\n\t"
                "mov 0xA(%rcx), %edx\n\t"
                "and $0xFFFFFFFE, %edx\n\t"
                "or $1, %edx\n\t" // Set perm uruk intel bitfield
                "mov %edx, 0xA(%rcx)\n\t"
                "mov $3, %edx\n\t"
                "jmp *urukIntelJmpAddress"
            );
        }
    }

    bool CreateUrukIntelHook()
    {
        urukIntelAddress = pScanner.PerformModuleScan(bytePattern, patternLength, patternOffset, moduleName);
        urukIntelJmpAddress = (UINT_PTR)urukIntelAddress + 5;
        return urukIntelAddress != nullptr;
    }


    // Hook startup.
    void CreateGameHooks()
    {
        bool fullIntel = GetPrivateProfileInt(L"General", L"FullIntel", 0, L".\\plugins\\urukintel.ini");
        CreateUrukIntelHook();
        if(fullIntel)
            MH_CreateHook(urukIntelAddress, (LPVOID)UrukFullIntelInjectCode, nullptr);
        else
            MH_CreateHook(urukIntelAddress, (LPVOID)UrukPartialIntelInjectCode, nullptr);

        MH_EnableHook(MH_ALL_HOOKS);
    }
}