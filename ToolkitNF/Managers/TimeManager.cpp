#include "TimeManager.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"
#include "../Globals/GlobalFunctions.hpp"

#if RENDER_WITH_SDL == 1
#include <SDL/SDL_timer.h>
#endif // RENDER_WITH_SDL

#if TARGET_NSPIRE == 1
    #include <libndls.h>
#else
    #include <stdlib.h>
#endif // TARGET_NSPIRE


static volatile unsigned *value;
static volatile unsigned *control;


TimeManager::TimeManager()
{
       //ctor
}


TimeManager& TimeManager::Get( void )
{
       static TimeManager m_timer;
       return m_timer;
}


void TimeManager::InternalInitialize( void )
{
       start = 0;
       tick_sum = 0;

       InternalStartTicks();
}


void TimeManager::InternalClose( void )
{

}


void TimeManager::InternalStartTicks(void)
{
#if RENDER_WITH_SDL == 0
       value = (unsigned *)0x900C0004;
       control = (unsigned *)0x900C0008;
       *(volatile unsigned *)0x900C0080 = 0xA; /* "[...] on the CX to specify the 32768Hz clock as the source for the First Timer" */
       *control = 0b10000010; /* Wrapping; 32-bit; divider to 1; interrupt disabled; free-running; start */
       start = *value;
#endif // RENDER_WITH_SDL

}


uint32_t TimeManager::InternalGetTicks(void)
{
#if RENDER_WITH_SDL == 1

       return (uint32_t) SDL_GetTicks( );

#else

       if ( has_colors )
              return((start - *value) / 33);
       else
       {
              tick_sum += *value;
              *value = 0;
              return(tick_sum);
       }

#endif // RENDER_WITH_SDL
}


void TimeManager::InternalDelay(uint32_t ms)
{
#if RENDER_WITH_SDL == 1

       SDL_Delay( ms );

#else

       msleep(ms);

#endif // RENDER_WITH_SDL
}

