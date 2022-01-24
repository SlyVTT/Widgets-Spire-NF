#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include "../Globals/GUIToolkitNFGlobals.hpp"

#include <string>

#if TARGET_NSPIRE == 0
    #include <SDL/SDL.h>        // used to get access to SDL_Event
#endif // TARGET_NSPIRE


/// KeyManager class is a Singleton devoted to manage the keyboard hardware of the TI nSpire CX and CX-II

class KeyManager
{
public:

       KeyManager(KeyManager&) = delete;
       KeyManager& operator= (const KeyManager&) = delete;

       static KeyManager& Get( void );


       static bool kbA( void ) { return Get().m_kbA; };
       static bool kbB( void ) { return Get().m_kbB; };
       static bool kbC( void ) { return Get().m_kbC; };
       static bool kbD( void ) { return Get().m_kbD; };
       static bool kbE( void ) { return Get().m_kbE; };
       static bool kbF( void ) { return Get().m_kbF; };
       static bool kbG( void ) { return Get().m_kbG; };
       static bool kbH( void ) { return Get().m_kbH; };
       static bool kbI( void ) { return Get().m_kbI; };
       static bool kbJ( void ) { return Get().m_kbJ; };
       static bool kbK( void ) { return Get().m_kbK; };
       static bool kbL( void ) { return Get().m_kbL; };
       static bool kbM( void ) { return Get().m_kbM; };
       static bool kbN( void ) { return Get().m_kbN; };
       static bool kbO( void ) { return Get().m_kbO; };
       static bool kbP( void ) { return Get().m_kbP; };
       static bool kbQ( void ) { return Get().m_kbQ; };
       static bool kbR( void ) { return Get().m_kbR; };
       static bool kbS( void ) { return Get().m_kbS; };
       static bool kbT( void ) { return Get().m_kbT; };
       static bool kbU( void ) { return Get().m_kbU; };
       static bool kbV( void ) { return Get().m_kbV; };
       static bool kbW( void ) { return Get().m_kbW; };
       static bool kbX( void ) { return Get().m_kbX; };
       static bool kbY( void ) { return Get().m_kbY; };
       static bool kbZ( void ) { return Get().m_kbZ; };
       static bool kb0( void ) { return Get().m_kb0; };
       static bool kb1( void ) { return Get().m_kb1; };
       static bool kb2( void ) { return Get().m_kb2; };
       static bool kb3( void ) { return Get().m_kb3; };
       static bool kb4( void ) { return Get().m_kb4; };
       static bool kb5( void ) { return Get().m_kb5; };
       static bool kb6( void ) { return Get().m_kb6; };
       static bool kb7( void ) { return Get().m_kb7; };
       static bool kb8( void ) { return Get().m_kb8; };
       static bool kb9( void ) { return Get().m_kb9; };
       static bool kbRET( void ) { return Get().m_kbRET; };
       static bool kbENTER( void ) { return Get().m_kbENTER; };
       static bool kbMINUSPAR( void ) { return Get().m_kbMINUSPAR; };
       static bool kbSPACE( void ) { return Get().m_kbSPACE; };
       static bool kbQUESTION( void ) { return Get().m_kbQUESTION; };
       static bool kbON( void ) { return Get().m_kbON; };
       static bool kbPI( void ) { return Get().m_kbPI; };
       static bool kbTRIG( void ) { return Get().m_kbTRIG; };
       static bool kb10X( void ) { return Get().m_kb10X; };
       static bool kbEE( void ) { return Get().m_kbEE; };
       static bool kbX2( void ) { return Get().m_kbX2; };
       static bool kbDIV( void ) { return Get().m_kbDIV; };
       static bool kbEX( void ) { return Get().m_kbEX; };
       static bool kbEQUAL( void ) { return Get().m_kbEQUAL; };
       static bool kbMULTIPLY( void ) { return Get().m_kbMULTIPLY; };
       static bool kbPOWER( void ) { return Get().m_kbPOWER; };
       static bool kbVAR( void ) { return Get().m_kbVAR; };
       static bool kbMINUS( void ) { return Get().m_kbMINUSPAR; };
       static bool kbPARCLOSE( void ) { return Get().m_kbPARCLOSE; };
       static bool kbDOT( void ) { return Get().m_kbDOT; };
       static bool kbPAROPEN( void ) { return Get().m_kbPAROPEN; };
       static bool kbCATALOG( void ) { return Get().m_kbCATALOG; };
       static bool kbFRAC( void ) { return Get().m_kbFRAC; };
       static bool kbDEL( void ) { return Get().m_kbDEL; };
       static bool kbSCRATCH( void ) { return Get().m_kbSCRATCH; };
       static bool kbFLAG( void ) { return Get().m_kbFLAG; };
       static bool kbPLUS( void ) { return Get().m_kbPLUS; };
       static bool kbDOC( void ) { return Get().m_kbDOC; };
       static bool kbMENU( void ) { return Get().m_kbMENU; };
       static bool kbESC( void ) { return Get().m_kbESC; };
       static bool kbTAB( void ) { return Get().m_kbTAB; };
       static bool kbSHIFT( void ) { return Get().m_kbSHIFT; };
       static bool kbCTRL( void ) { return Get().m_kbCTRL; };
       static bool kbCOMMA( void ) { return Get().m_kbCOMMA; };


       static bool kbA_Press_Event( void ) { return Get().m_kbA_Press_Event; };
       static bool kbB_Press_Event( void ) { return Get().m_kbB_Press_Event; };
       static bool kbC_Press_Event( void ) { return Get().m_kbC_Press_Event; };
       static bool kbD_Press_Event( void ) { return Get().m_kbD_Press_Event; };
       static bool kbE_Press_Event( void ) { return Get().m_kbE_Press_Event; };
       static bool kbF_Press_Event( void ) { return Get().m_kbF_Press_Event; };
       static bool kbG_Press_Event( void ) { return Get().m_kbG_Press_Event; };
       static bool kbH_Press_Event( void ) { return Get().m_kbH_Press_Event; };
       static bool kbI_Press_Event( void ) { return Get().m_kbI_Press_Event; };
       static bool kbJ_Press_Event( void ) { return Get().m_kbJ_Press_Event; };
       static bool kbK_Press_Event( void ) { return Get().m_kbK_Press_Event; };
       static bool kbL_Press_Event( void ) { return Get().m_kbL_Press_Event; };
       static bool kbM_Press_Event( void ) { return Get().m_kbM_Press_Event; };
       static bool kbN_Press_Event( void ) { return Get().m_kbN_Press_Event; };
       static bool kbO_Press_Event( void ) { return Get().m_kbO_Press_Event; };
       static bool kbP_Press_Event( void ) { return Get().m_kbP_Press_Event; };
       static bool kbQ_Press_Event( void ) { return Get().m_kbQ_Press_Event; };
       static bool kbR_Press_Event( void ) { return Get().m_kbR_Press_Event; };
       static bool kbS_Press_Event( void ) { return Get().m_kbS_Press_Event; };
       static bool kbT_Press_Event( void ) { return Get().m_kbT_Press_Event; };
       static bool kbU_Press_Event( void ) { return Get().m_kbU_Press_Event; };
       static bool kbV_Press_Event( void ) { return Get().m_kbV_Press_Event; };
       static bool kbW_Press_Event( void ) { return Get().m_kbW_Press_Event; };
       static bool kbX_Press_Event( void ) { return Get().m_kbX_Press_Event; };
       static bool kbY_Press_Event( void ) { return Get().m_kbY_Press_Event; };
       static bool kbZ_Press_Event( void ) { return Get().m_kbZ_Press_Event; };
       static bool kb0_Press_Event( void ) { return Get().m_kb0_Press_Event; };
       static bool kb1_Press_Event( void ) { return Get().m_kb1_Press_Event; };
       static bool kb2_Press_Event( void ) { return Get().m_kb2_Press_Event; };
       static bool kb3_Press_Event( void ) { return Get().m_kb3_Press_Event; };
       static bool kb4_Press_Event( void ) { return Get().m_kb4_Press_Event; };
       static bool kb5_Press_Event( void ) { return Get().m_kb5_Press_Event; };
       static bool kb6_Press_Event( void ) { return Get().m_kb6_Press_Event; };
       static bool kb7_Press_Event( void ) { return Get().m_kb7_Press_Event; };
       static bool kb8_Press_Event( void ) { return Get().m_kb8_Press_Event; };
       static bool kb9_Press_Event( void ) { return Get().m_kb9_Press_Event; };
       static bool kbRET_Press_Event( void ) { return Get().m_kbRET_Press_Event; };
       static bool kbENTER_Press_Event( void ) { return Get().m_kbENTER_Press_Event; };
       static bool kbMINUSPAR_Press_Event( void ) { return Get().m_kbMINUSPAR_Press_Event; };
       static bool kbSPACE_Press_Event( void ) { return Get().m_kbSPACE_Press_Event; };
       static bool kbQUESTION_Press_Event( void ) { return Get().m_kbQUESTION_Press_Event; };
       static bool kbON_Press_Event( void ) { return Get().m_kbON_Press_Event; };
       static bool kbPI_Press_Event( void ) { return Get().m_kbPI_Press_Event; };
       static bool kbTRIG_Press_Event( void ) { return Get().m_kbTRIG_Press_Event; };
       static bool kb10X_Press_Event( void ) { return Get().m_kb10X_Press_Event; };
       static bool kbEE_Press_Event( void ) { return Get().m_kbEE_Press_Event; };
       static bool kbX2_Press_Event( void ) { return Get().m_kbX2_Press_Event; };
       static bool kbDIV_Press_Event( void ) { return Get().m_kbDIV_Press_Event; };
       static bool kbEX_Press_Event( void ) { return Get().m_kbEX_Press_Event; };
       static bool kbEQUAL_Press_Event( void ) { return Get().m_kbEQUAL_Press_Event; };
       static bool kbMULTIPLY_Press_Event( void ) { return Get().m_kbMULTIPLY_Press_Event; };
       static bool kbPOWER_Press_Event( void ) { return Get().m_kbPOWER_Press_Event; };
       static bool kbVAR_Press_Event( void ) { return Get().m_kbVAR_Press_Event; };
       static bool kbMINUS_Press_Event( void ) { return Get().m_kbMINUSPAR_Press_Event; };
       static bool kbPARCLOSE_Press_Event( void ) { return Get().m_kbPARCLOSE_Press_Event; };
       static bool kbDOT_Press_Event( void ) { return Get().m_kbDOT_Press_Event; };
       static bool kbPAROPEN_Press_Event( void ) { return Get().m_kbPAROPEN_Press_Event; };
       static bool kbCATALOG_Press_Event( void ) { return Get().m_kbCATALOG_Press_Event; };
       static bool kbFRAC_Press_Event( void ) { return Get().m_kbFRAC_Press_Event; };
       static bool kbDEL_Press_Event( void ) { return Get().m_kbDEL_Press_Event; };
       static bool kbSCRATCH_Press_Event( void ) { return Get().m_kbSCRATCH_Press_Event; };
       static bool kbFLAG_Press_Event( void ) { return Get().m_kbFLAG_Press_Event; };
       static bool kbPLUS_Press_Event( void ) { return Get().m_kbPLUS_Press_Event; };
       static bool kbDOC_Press_Event( void ) { return Get().m_kbDOC_Press_Event; };
       static bool kbMENU_Press_Event( void ) { return Get().m_kbMENU_Press_Event; };
       static bool kbESC_Press_Event( void ) { return Get().m_kbESC_Press_Event; };
       static bool kbTAB_Press_Event( void ) { return Get().m_kbTAB_Press_Event; };
       static bool kbSHIFT_Press_Event( void ) { return Get().m_kbSHIFT_Press_Event; };
       static bool kbCTRL_Press_Event( void ) { return Get().m_kbCTRL_Press_Event; };
       static bool kbCOMMA_Press_Event( void ) { return Get().m_kbCOMMA_Press_Event; };


       static bool kbA_Release_Event( void ) { return Get().m_kbA_Release_Event; };
       static bool kbB_Release_Event( void ) { return Get().m_kbB_Release_Event; };
       static bool kbC_Release_Event( void ) { return Get().m_kbC_Release_Event; };
       static bool kbD_Release_Event( void ) { return Get().m_kbD_Release_Event; };
       static bool kbE_Release_Event( void ) { return Get().m_kbE_Release_Event; };
       static bool kbF_Release_Event( void ) { return Get().m_kbF_Release_Event; };
       static bool kbG_Release_Event( void ) { return Get().m_kbG_Release_Event; };
       static bool kbH_Release_Event( void ) { return Get().m_kbH_Release_Event; };
       static bool kbI_Release_Event( void ) { return Get().m_kbI_Release_Event; };
       static bool kbJ_Release_Event( void ) { return Get().m_kbJ_Release_Event; };
       static bool kbK_Release_Event( void ) { return Get().m_kbK_Release_Event; };
       static bool kbL_Release_Event( void ) { return Get().m_kbL_Release_Event; };
       static bool kbM_Release_Event( void ) { return Get().m_kbM_Release_Event; };
       static bool kbN_Release_Event( void ) { return Get().m_kbN_Release_Event; };
       static bool kbO_Release_Event( void ) { return Get().m_kbO_Release_Event; };
       static bool kbP_Release_Event( void ) { return Get().m_kbP_Release_Event; };
       static bool kbQ_Release_Event( void ) { return Get().m_kbQ_Release_Event; };
       static bool kbR_Release_Event( void ) { return Get().m_kbR_Release_Event; };
       static bool kbS_Release_Event( void ) { return Get().m_kbS_Release_Event; };
       static bool kbT_Release_Event( void ) { return Get().m_kbT_Release_Event; };
       static bool kbU_Release_Event( void ) { return Get().m_kbU_Release_Event; };
       static bool kbV_Release_Event( void ) { return Get().m_kbV_Release_Event; };
       static bool kbW_Release_Event( void ) { return Get().m_kbW_Release_Event; };
       static bool kbX_Release_Event( void ) { return Get().m_kbX_Release_Event; };
       static bool kbY_Release_Event( void ) { return Get().m_kbY_Release_Event; };
       static bool kbZ_Release_Event( void ) { return Get().m_kbZ_Release_Event; };
       static bool kb0_Release_Event( void ) { return Get().m_kb0_Release_Event; };
       static bool kb1_Release_Event( void ) { return Get().m_kb1_Release_Event; };
       static bool kb2_Release_Event( void ) { return Get().m_kb2_Release_Event; };
       static bool kb3_Release_Event( void ) { return Get().m_kb3_Release_Event; };
       static bool kb4_Release_Event( void ) { return Get().m_kb4_Release_Event; };
       static bool kb5_Release_Event( void ) { return Get().m_kb5_Release_Event; };
       static bool kb6_Release_Event( void ) { return Get().m_kb6_Release_Event; };
       static bool kb7_Release_Event( void ) { return Get().m_kb7_Release_Event; };
       static bool kb8_Release_Event( void ) { return Get().m_kb8_Release_Event; };
       static bool kb9_Release_Event( void ) { return Get().m_kb9_Release_Event; };
       static bool kbRET_Release_Event( void ) { return Get().m_kbRET_Release_Event; };
       static bool kbENTER_Release_Event( void ) { return Get().m_kbENTER_Release_Event; };
       static bool kbMINUSPAR_Release_Event( void ) { return Get().m_kbMINUSPAR_Release_Event; };
       static bool kbSPACE_Release_Event( void ) { return Get().m_kbSPACE_Release_Event; };
       static bool kbQUESTION_Release_Event( void ) { return Get().m_kbQUESTION_Release_Event; };
       static bool kbON_Release_Event( void ) { return Get().m_kbON_Release_Event; };
       static bool kbPI_Release_Event( void ) { return Get().m_kbPI_Release_Event; };
       static bool kbTRIG_Release_Event( void ) { return Get().m_kbTRIG_Release_Event; };
       static bool kb10X_Release_Event( void ) { return Get().m_kb10X_Release_Event; };
       static bool kbEE_Release_Event( void ) { return Get().m_kbEE_Release_Event; };
       static bool kbX2_Release_Event( void ) { return Get().m_kbX2_Release_Event; };
       static bool kbDIV_Release_Event( void ) { return Get().m_kbDIV_Release_Event; };
       static bool kbEX_Release_Event( void ) { return Get().m_kbEX_Release_Event; };
       static bool kbEQUAL_Release_Event( void ) { return Get().m_kbEQUAL_Release_Event; };
       static bool kbMULTIPLY_Release_Event( void ) { return Get().m_kbMULTIPLY_Release_Event; };
       static bool kbPOWER_Release_Event( void ) { return Get().m_kbPOWER_Release_Event; };
       static bool kbVAR_Release_Event( void ) { return Get().m_kbVAR_Release_Event; };
       static bool kbMINUS_Release_Event( void ) { return Get().m_kbMINUSPAR_Release_Event; };
       static bool kbPARCLOSE_Release_Event( void ) { return Get().m_kbPARCLOSE_Release_Event; };
       static bool kbDOT_Release_Event( void ) { return Get().m_kbDOT_Release_Event; };
       static bool kbPAROPEN_Release_Event( void ) { return Get().m_kbPAROPEN_Release_Event; };
       static bool kbCATALOG_Release_Event( void ) { return Get().m_kbCATALOG_Release_Event; };
       static bool kbFRAC_Release_Event( void ) { return Get().m_kbFRAC_Release_Event; };
       static bool kbDEL_Release_Event( void ) { return Get().m_kbDEL_Release_Event; };
       static bool kbSCRATCH_Release_Event( void ) { return Get().m_kbSCRATCH_Release_Event; };
       static bool kbFLAG_Release_Event( void ) { return Get().m_kbFLAG_Release_Event; };
       static bool kbPLUS_Release_Event( void ) { return Get().m_kbPLUS_Release_Event; };
       static bool kbDOC_Release_Event( void ) { return Get().m_kbDOC_Release_Event; };
       static bool kbMENU_Release_Event( void ) { return Get().m_kbMENU_Release_Event; };
       static bool kbESC_Release_Event( void ) { return Get().m_kbESC_Release_Event; };
       static bool kbTAB_Release_Event( void ) { return Get().m_kbTAB_Release_Event; };
       static bool kbSHIFT_Release_Event( void ) { return Get().m_kbSHIFT_Release_Event; };
       static bool kbCTRL_Release_Event( void ) { return Get().m_kbCTRL_Release_Event; };
       static bool kbCOMMA_Release_Event( void ) { return Get().m_kbCOMMA_Release_Event; };


       static void Initialize( void ) { Get().InternalInitialize(); };
       static void Logic( void ) { Get().InternalLogic(); };
       static void ResetState( void ) { Get().InternalResetState(); };
       static void Close( void ) { Get().InternalClose();  };

       //This is a recode of LibNDLS nio_ascii_get() to correctly map the nSpire CX/CX-II keyboard
       static char AsciiGet( void ) {return Get().InternalAsciiGet(); };

       static bool IsAnyKeyPressed( void ) { return Get().InternalIsAnyKeyPressed(); };
       static bool IsAnyKeyEvent( void ) { return Get().InternalIsAnyKeyEvent(); };

       static bool IsKeyPressEvent( void ) { return Get().InternalIsKeyPressEvent(); };
       static bool IsKeyReleaseEvent( void ) { return Get().InternalIsKeyReleaseEvent(); };

       static void SetSelection( std::string select ) { Get().InternalSetSelection( select ); };
       static std::string GetSelection( void ) { return Get().InternalGetSelection(); };
       static void FlushSelection( void ) { Get().InternalFlushSelection(); };


private:
       KeyManager();

       static KeyManager m_keyboard;

       // First adress block
       bool m_kbRET;
       bool m_kbRET_Press_Event;
       bool m_kbRET_Release_Event;
       bool m_kbENTER;
       bool m_kbENTER_Press_Event;
       bool m_kbENTER_Release_Event;
       bool m_kbMINUSPAR;
       bool m_kbMINUSPAR_Press_Event;
       bool m_kbMINUSPAR_Release_Event;
       bool m_kbSPACE;
       bool m_kbSPACE_Press_Event;
       bool m_kbSPACE_Release_Event;
       bool m_kbZ;
       bool m_kbZ_Press_Event;
       bool m_kbZ_Release_Event;
       bool m_kbY;
       bool m_kbY_Press_Event;
       bool m_kbY_Release_Event;
       bool m_kb0;
       bool m_kb0_Press_Event;
       bool m_kb0_Release_Event;
       bool m_kbQUESTION;
       bool m_kbQUESTION_Press_Event;
       bool m_kbQUESTION_Release_Event;
       bool m_kbON;
       bool m_kbON_Press_Event;
       bool m_kbON_Release_Event;

       // Second adress block
       bool m_kbX;
       bool m_kbX_Press_Event;
       bool m_kbX_Release_Event;
       bool m_kbW;
       bool m_kbW_Press_Event;
       bool m_kbW_Release_Event;
       bool m_kbV;
       bool m_kbV_Press_Event;
       bool m_kbV_Release_Event;
       bool m_kb3;
       bool m_kb3_Press_Event;
       bool m_kb3_Release_Event;
       bool m_kbU;
       bool m_kbU_Press_Event;
       bool m_kbU_Release_Event;
       bool m_kbT;
       bool m_kbT_Press_Event;
       bool m_kbT_Release_Event;
       bool m_kbS;
       bool m_kbS_Press_Event;
       bool m_kbS_Release_Event;
       bool m_kb1;
       bool m_kb1_Press_Event;
       bool m_kb1_Release_Event;
       bool m_kbPI;
       bool m_kbPI_Press_Event;
       bool m_kbPI_Release_Event;
       bool m_kbTRIG;
       bool m_kbTRIG_Press_Event;
       bool m_kbTRIG_Release_Event;
       bool m_kb10X;
       bool m_kb10X_Press_Event;
       bool m_kb10X_Release_Event;

       // Third adress block
       bool m_kbR;
       bool m_kbR_Press_Event;
       bool m_kbR_Release_Event;
       bool m_kbQ;
       bool m_kbQ_Press_Event;
       bool m_kbQ_Release_Event;
       bool m_kbP;
       bool m_kbP_Press_Event;
       bool m_kbP_Release_Event;
       bool m_kb6;
       bool m_kb6_Press_Event;
       bool m_kb6_Release_Event;
       bool m_kbO;
       bool m_kbO_Press_Event;
       bool m_kbO_Release_Event;
       bool m_kbN;
       bool m_kbN_Press_Event;
       bool m_kbN_Release_Event;
       bool m_kbM;
       bool m_kbM_Press_Event;
       bool m_kbM_Release_Event;
       bool m_kb4;
       bool m_kb4_Press_Event;
       bool m_kb4_Release_Event;
       bool m_kbEE;
       bool m_kbEE_Press_Event;
       bool m_kbEE_Release_Event;
       bool m_kbX2;
       bool m_kbX2_Press_Event;
       bool m_kbX2_Release_Event;

       // Fourth adress block
       bool m_kbL;
       bool m_kbL_Press_Event;
       bool m_kbL_Release_Event;
       bool m_kbK;
       bool m_kbK_Press_Event;
       bool m_kbK_Release_Event;
       bool m_kbJ;
       bool m_kbJ_Press_Event;
       bool m_kbJ_Release_Event;
       bool m_kb9;
       bool m_kb9_Press_Event;
       bool m_kb9_Release_Event;
       bool m_kbI;
       bool m_kbI_Press_Event;
       bool m_kbI_Release_Event;
       bool m_kbH;
       bool m_kbH_Press_Event;
       bool m_kbH_Release_Event;
       bool m_kbG;
       bool m_kbG_Press_Event;
       bool m_kbG_Release_Event;
       bool m_kb7;
       bool m_kb7_Press_Event;
       bool m_kb7_Release_Event;
       bool m_kbDIV;
       bool m_kbDIV_Press_Event;
       bool m_kbDIV_Release_Event;
       bool m_kbEX;
       bool m_kbEX_Press_Event;
       bool m_kbEX_Release_Event;

       // Fifth adress block
       bool m_kbF;
       bool m_kbF_Press_Event;
       bool m_kbF_Release_Event;
       bool m_kbE;
       bool m_kbE_Press_Event;
       bool m_kbE_Release_Event;
       bool m_kbD;
       bool m_kbD_Press_Event;
       bool m_kbD_Release_Event;
       bool m_kbC;
       bool m_kbC_Press_Event;
       bool m_kbC_Release_Event;
       bool m_kbB;
       bool m_kbB_Press_Event;
       bool m_kbB_Release_Event;
       bool m_kbA;
       bool m_kbA_Press_Event;
       bool m_kbA_Release_Event;
       bool m_kbEQUAL;
       bool m_kbEQUAL_Press_Event;
       bool m_kbEQUAL_Release_Event;
       bool m_kbMULTIPLY;
       bool m_kbMULTIPLY_Press_Event;
       bool m_kbMULTIPLY_Release_Event;
       bool m_kbPOWER;
       bool m_kbPOWER_Press_Event;
       bool m_kbPOWER_Release_Event;

       // Sixth adress block
       bool m_kbVAR;
       bool m_kbVAR_Press_Event;
       bool m_kbVAR_Release_Event;
       bool m_kbMINUS;
       bool m_kbMINUS_Press_Event;
       bool m_kbMINUS_Release_Event;
       bool m_kbPARCLOSE;
       bool m_kbPARCLOSE_Press_Event;
       bool m_kbPARCLOSE_Release_Event;
       bool m_kbDOT;
       bool m_kbDOT_Press_Event;
       bool m_kbDOT_Release_Event;
       bool m_kbPAROPEN;
       bool m_kbPAROPEN_Press_Event;
       bool m_kbPAROPEN_Release_Event;
       bool m_kb5;
       bool m_kb5_Press_Event;
       bool m_kb5_Release_Event;
       bool m_kbCATALOG;
       bool m_kbCATALOG_Press_Event;
       bool m_kbCATALOG_Release_Event;
       bool m_kbFRAC;
       bool m_kbFRAC_Press_Event;
       bool m_kbFRAC_Release_Event;
       bool m_kbDEL;
       bool m_kbDEL_Press_Event;
       bool m_kbDEL_Release_Event;
       bool m_kbSCRATCH;
       bool m_kbSCRATCH_Press_Event;
       bool m_kbSCRATCH_Release_Event;

       // Seventh adress block
       bool m_kbFLAG;
       bool m_kbFLAG_Press_Event;
       bool m_kbFLAG_Release_Event;
       bool m_kbPLUS;
       bool m_kbPLUS_Press_Event;
       bool m_kbPLUS_Release_Event;
       bool m_kbDOC;
       bool m_kbDOC_Press_Event;
       bool m_kbDOC_Release_Event;
       bool m_kb2;
       bool m_kb2_Press_Event;
       bool m_kb2_Release_Event;
       bool m_kbMENU;
       bool m_kbMENU_Press_Event;
       bool m_kbMENU_Release_Event;
       bool m_kb8;
       bool m_kb8_Press_Event;
       bool m_kb8_Release_Event;
       bool m_kbESC;
       bool m_kbESC_Press_Event;
       bool m_kbESC_Release_Event;
       bool m_kbTAB;
       bool m_kbTAB_Press_Event;
       bool m_kbTAB_Release_Event;

       // Eigth adress block
       bool m_kbSHIFT;
       bool m_kbSHIFT_Press_Event;
       bool m_kbSHIFT_Release_Event;
       bool m_kbCTRL;
       bool m_kbCTRL_Press_Event;
       bool m_kbCTRL_Release_Event;
       bool m_kbCOMMA;
       bool m_kbCOMMA_Press_Event;
       bool m_kbCOMMA_Release_Event;




       // Following are all the internal variables needed by the status machinery

       // First adress block
       bool m_kbRET_Previous;
       bool m_kbENTER_Previous;
       bool m_kbMINUSPAR_Previous;
       bool m_kbSPACE_Previous;
       bool m_kbZ_Previous;
       bool m_kbY_Previous;
       bool m_kb0_Previous;
       bool m_kbQUESTION_Previous;
       bool m_kbON_Previous;

       // Second adress block
       bool m_kbX_Previous;
       bool m_kbW_Previous;
       bool m_kbV_Previous;
       bool m_kb3_Previous;
       bool m_kbU_Previous;
       bool m_kbT_Previous;
       bool m_kbS_Previous;
       bool m_kb1_Previous;
       bool m_kbPI_Previous;
       bool m_kbTRIG_Previous;
       bool m_kb10X_Previous;

       // Third adress block
       bool m_kbR_Previous;
       bool m_kbQ_Previous;
       bool m_kbP_Previous;
       bool m_kb6_Previous;
       bool m_kbO_Previous;
       bool m_kbN_Previous;
       bool m_kbM_Previous;
       bool m_kb4_Previous;
       bool m_kbEE_Previous;
       bool m_kbX2_Previous;

       // Fourth adress block
       bool m_kbL_Previous;
       bool m_kbK_Previous;
       bool m_kbJ_Previous;
       bool m_kb9_Previous;
       bool m_kbI_Previous;
       bool m_kbH_Previous;
       bool m_kbG_Previous;
       bool m_kb7_Previous;
       bool m_kbDIV_Previous;
       bool m_kbEX_Previous;

       // Fifth adress block
       bool m_kbF_Previous;
       bool m_kbE_Previous;
       bool m_kbD_Previous;
       bool m_kbC_Previous;
       bool m_kbB_Previous;
       bool m_kbA_Previous;
       bool m_kbEQUAL_Previous;
       bool m_kbMULTIPLY_Previous;
       bool m_kbPOWER_Previous;

       // Sixth adress block
       bool m_kbVAR_Previous;
       bool m_kbMINUS_Previous;
       bool m_kbPARCLOSE_Previous;
       bool m_kbDOT_Previous;
       bool m_kbPAROPEN_Previous;
       bool m_kb5_Previous;
       bool m_kbCATALOG_Previous;
       bool m_kbFRAC_Previous;
       bool m_kbDEL_Previous;
       bool m_kbSCRATCH_Previous;

       // Seventh adress block
       bool m_kbFLAG_Previous;
       bool m_kbPLUS_Previous;
       bool m_kbDOC_Previous;
       bool m_kb2_Previous;
       bool m_kbMENU_Previous;
       bool m_kb8_Previous;
       bool m_kbESC_Previous;
       bool m_kbTAB_Previous;

       // Eigth adress block
       bool m_kbSHIFT_Previous;
       bool m_kbCTRL_Previous;
       bool m_kbCOMMA_Previous;

#if TARGET_NSPIRE == 1
       // The physical adresses of key into the memory (model dependant)
       unsigned short *base;
       unsigned short *specialON;
#else

        SDL_Event event;
        Uint8 *keys;

#endif

       // This is the content of the Clipboard
       std::string selection;

       void InternalSetSelection( std::string select );
       std::string InternalGetSelection( void );
       void InternalFlushSelection( void );

       // general state variables for regular keys event
       bool keyevent;
       bool keypressevent;
       bool keyreleaseevent;


       bool capsonmode;

       uint16_t keysum = 0;

       void InternalLogic( void );
       void InternalResetState( void );
       void InternalInitialize( void );
       void InternalClose( void );


       char InternalAsciiGet( void );
       bool InternalIsAnyKeyEvent( void );
       bool InternalIsAnyKeyPressed( void );
       bool InternalIsKeyPressEvent( void );
       bool InternalIsKeyReleaseEvent( void );

};

#endif // KEYMANAGER_H
