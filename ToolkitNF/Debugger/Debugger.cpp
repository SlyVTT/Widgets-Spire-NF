#include "Debugger.hpp"

#include <stdio.h>

#include "../Managers/TimeManager.hpp"



Debugger::Debugger()
{
       //ctor
}


Debugger& Debugger::Get( void )
{
       static Debugger m_debug;
       return m_debug;
}


void Debugger::InternalInitialize( void )
{
       // Set the default Debug filename
       filename = "/documents/Widget/DebugOut/Debug.txt.tns";

       currentmode = SafeMode;

       timeinit = TimeManager::GetTicks();
}


void Debugger::InternalClose( void )
{
       if (pFile)
              fclose(pFile);
}


void Debugger::InternalOpenMaintain( void )
{
       pFile = fopen( filename.c_str(), "a" );
}


void Debugger::InternalCloseMaintain( void )
{
       if (pFile)
              fclose(pFile);
}


void Debugger::InternalSetDebuggerFile( std::string file )
{
       filename = file;
}


void Debugger::InternalSetDebuggerMode( DebugMode mode )
{
       currentmode = mode;
}


void Debugger::InternalLog( const std::string& stringtolog )
{
       if (currentmode==SafeMode)
              pFile = fopen( filename.c_str(), "a" );

       fprintf( pFile, "%s", stringtolog.c_str() );

       if (currentmode==SafeMode)
              fclose( pFile );
}


void Debugger::InternalLog( int value )
{
       if (currentmode==SafeMode)
              pFile = fopen( filename.c_str(), "a" );

       fprintf( pFile, "%d", value );

       if (currentmode==SafeMode)
              fclose( pFile );
}

void Debugger::Log( const char *fmt, ... )
{
       char Buffer[1000];

       va_list args;
       va_start (args, fmt);
       vsprintf( Buffer, fmt, args );
       va_end (args);

       Get().InternalLog( Buffer );
}


void Debugger::InternalTimerLog( const std::string& stringtolog )
{
       if (currentmode==SafeMode)
              pFile = fopen( filename.c_str(), "a" );

       uint32_t timecurrent, timedelta;
       timecurrent = TimeManager::GetTicks();
       timedelta = timecurrent-timeinit;
       fprintf( pFile, "%ld ms : \t", timedelta );

       fprintf( pFile, "%s", stringtolog.c_str() );

       if (currentmode==SafeMode)
              fclose( pFile );
}


void Debugger::InternalTimerLog( int value )
{
       if (currentmode==SafeMode)
              pFile = fopen( filename.c_str(), "a" );

       uint32_t timecurrent, timedelta;
       timecurrent = TimeManager::GetTicks();
       timedelta = timecurrent-timeinit;
       fprintf( pFile, "%ld ms : \t", timedelta );

       fprintf( pFile, "%d", value );

       if (currentmode==SafeMode)
              fclose( pFile );
}


void Debugger::TimerLog( const char *fmt, ... )
{
       char Buffer[1000];

       va_list args;
       va_start (args, fmt);
       vsprintf( Buffer, fmt, args );
       va_end (args);

       Get().InternalTimerLog( Buffer );
}

