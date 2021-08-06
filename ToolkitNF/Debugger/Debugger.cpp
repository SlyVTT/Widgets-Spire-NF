#include "Debugger.hpp"

#include <stdio.h>


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
}


void Debugger::InternalClose( void )
{
    if (pFile)
        fclose(pFile);
}


void Debugger::InternalOpenMaintain( void )
{
            pFile = fopen( filename.c_str(), "wa" );
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
        pFile = fopen( filename.c_str(), "wa" );

    fprintf( pFile, "%s", stringtolog.c_str() );

    if (currentmode==SafeMode)
        fclose( pFile );
}


void Debugger::InternalLog( int value )
{
    if (currentmode==SafeMode)
        pFile = fopen( filename.c_str(), "wa" );

    fprintf( pFile, "%d", value );

    if (currentmode==SafeMode)
        fclose( pFile );
}
