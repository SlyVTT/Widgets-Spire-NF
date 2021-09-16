//TARGET_NSPIRE To be set to 1 if target architecture is TI nSpire and to 0 if target architecture is PC
#define TARGET_NSPIRE 1

#if TARGET_NSPIRE == 1
    //RENDER_WITH_SDL To be set to 1 if SDL is used as the renderer, and to 0 otherwise
    //NOTE : It MUST BE SET TO 1 if the program is defined to be used on PC and not on TI nSPire
    #define RENDER_WITH_SDL 1       // CAN be 1 (use SDL) or 0 (use nGC)
#else
    #define RENDER_WITH_SDL 1       // MUST be set to 1 (SDL mandatory)
#endif // TARGET_NSPIRE


//DEBUG_MODE to be set to 1 for enabling debugger and to 0 otherwise
#define DEBUG_MODE  1


#define SCREEN_WIDTH_GUI 320
#define SCREEN_HEIGHT_GUI 240



