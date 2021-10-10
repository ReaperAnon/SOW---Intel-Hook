#ifndef HOOKS
    #define HOOKS

    namespace GameHook
    {
        extern "C"
        {
            INSTRUCTIONSET UrukFullIntelInjectCode();
            INSTRUCTIONSET UrukPartialIntelInjectCode();
        }

        bool CreateUrukIntelHook();

        void CreateGameHooks();
    }
#endif