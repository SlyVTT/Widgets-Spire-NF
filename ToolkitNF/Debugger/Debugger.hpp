#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <string>
#include <stdarg.h>


class Debugger
{
public:

        enum DebugMode
        {
            SafeMode = 1,           // Open and Close the output file at each log (safe BUT slow)
            MaintainFlow = 2       // Open the output file once and close it on order (quick BUT unsafe)
        };


       Debugger(Debugger&) = delete;
       Debugger& operator= (const Debugger&) = delete;

       static Debugger& Get( void );

       static void Initialize( void ) { Get().InternalInitialize(); };
       static void Close( void ) { Get().InternalClose(); };

        static void SetDebuggerFile( std::string file ) { Get().InternalSetDebuggerFile( file ); };
        static void SetDebuggerMode( DebugMode mode ) { Get().InternalSetDebuggerMode( mode ); };

        static void OpenMaintain( void ) { Get().InternalOpenMaintain(); };
        static void CloseMaintain( void ) { Get().InternalCloseMaintain(); };

        static void Log( const std::string& stringtolog ) { Get().InternalLog( stringtolog ); };
        static void Log( int value ) { Get().InternalLog( value ); };
        static void Log( const char *fmt, ... ); // See CPP file as it needs a special code for variadic arguments forwarding

        static void TimerLog( const std::string& stringtolog ) { Get().InternalTimerLog( stringtolog ); };
        static void TimerLog( int value ) { Get().InternalTimerLog( value ); };
        static void TimerLog( const char *fmt, ... ); // See CPP file as it needs a special code for variadic arguments forwarding


private:
       Debugger();

       void InternalInitialize( void );
       void InternalClose( void );

       void InternalSetDebuggerFile( std::string file );
       void InternalSetDebuggerMode( DebugMode mode );

       void InternalOpenMaintain( void );
       void InternalCloseMaintain( void );

       void InternalLog( const std::string& stringtolog );
       void InternalLog( int value );

       void InternalTimerLog( const std::string& stringtolog );
       void InternalTimerLog( int value );

       static Debugger m_debug;

       DebugMode currentmode;

       uint32_t timeinit;

       FILE* pFile;

       std::string filename;

};

#endif // DEBUGGER_HPP
