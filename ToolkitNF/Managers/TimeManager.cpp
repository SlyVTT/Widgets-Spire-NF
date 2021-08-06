#include "TimeManager.hpp"

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

}


void InternalClose( void )
{

}


void TimeManager::InternalStartTicks(void)
{
       *(volatile unsigned *)0x900B0018 &= ~(1 << 11); /* Enable bus access */
       if ( has_colors )
       {
              value = (unsigned *)0x900C0004;
              control = (unsigned *)0x900C0008;
              *(volatile unsigned *)0x900C0080 = 0xA; /* "[...] on the CX to specify the 32768Hz clock as the source for the First Timer" */
              *control = 0b10000010; /* Wrapping; 32-bit; divider to 1; interrupt disabled; free-running; start */
              start = *value;
       }
       else
       {
              value = (unsigned *)0x900C0000;
              control = (unsigned *)0x900C0008;
              *(volatile unsigned *)0x900C0004 = 33; /* Set time divider to 33; 32768/33=993Hz (approx. 1000Hz) */
              *control = 0b00001111; /* Run infinitely; increasing; start */
              *value = 0;
       }
}


uint32_t TimeManager::InternalGetTicks(void)
{
       if ( has_colors )
              return((start - *value) / 33);
       else
       {
              tick_sum += *value;
              *value = 0;
              return(tick_sum);
       }
}


void TimeManager::InternalDelay(uint32_t ms)
{
       sleep(ms);
}

