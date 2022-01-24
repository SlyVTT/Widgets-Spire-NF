

#ifdef NSPIRE_NGC
//TARGET_NSPIRE To be set to 1 if target architecture is TI nSpire and to 0 if target architecture is PC
    #define TARGET_NSPIRE 1
    #define TARGET_PC 0
    #define RENDER_WITH_SDL 0
#endif // NSPIRE_NGC


#ifdef NSPIRE_SDL
//TARGET_NSPIRE To be set to 1 if target architecture is TI nSpire and to 0 if target architecture is PC
    #define TARGET_NSPIRE 1
    #define TARGET_PC 0
    #define RENDER_WITH_SDL 1
#endif // NSPIRE_NGC


#ifdef FOR_PC
//TARGET_NSPIRE To be set to 1 if target architecture is TI nSpire and to 0 if target architecture is PC
    #define TARGET_NSPIRE 0
    #define TARGET_PC 1
    #define RENDER_WITH_SDL 1
#endif // NSPIRE_NGC


/*
#if TARGET_NSPIRE == 1
    //RENDER_WITH_SDL To be set to 1 if SDL is used as the renderer, and to 0 otherwise
    //NOTE : It MUST BE SET TO 1 if the program is defined to be used on PC and not on TI nSPire
      // CAN be 1 (use SDL) or 0 (use nGC)
    #define RENDER_WITH_SDL 0
#else
    #define RENDER_WITH_SDL 1       // MUST be set to 1 (SDL mandatory)
#endif // TARGET_NSPIRE
*/


//DEBUG_MODE to be set to 1 for enabling debugger and to 0 otherwise
#define DEBUG_MODE  1


//Screen resolution may change between PC and NSpire
#if TARGET_NSPIRE == 1
    #define SCREEN_WIDTH_GUI 320
    #define SCREEN_HEIGHT_GUI 240
#else
    #define SCREEN_WIDTH_GUI 640
    #define SCREEN_HEIGHT_GUI 480
#endif

