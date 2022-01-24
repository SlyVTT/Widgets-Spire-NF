#include "KeyManager.hpp"

#include "../Globals/GUIToolkitNFGlobals.hpp"

#if TARGET_NSPIRE == 1
    #include <libndls.h>
#else
    #include <stdlib.h>
    #include <SDL/SDL.h>
#endif // TARGET_NSPIRE


KeyManager::KeyManager()
{

}

KeyManager& KeyManager::Get( void )
{
    static KeyManager m_keyboard;
    return m_keyboard;
}


void KeyManager::InternalSetSelection( std::string select )
{
    selection = select;
}


std::string KeyManager::InternalGetSelection( void )
{
    return selection;
}


void KeyManager::InternalFlushSelection( void )
{
    selection.clear();
}



void KeyManager::InternalInitialize( void )
{
#if TARGET_NSPIRE == 1
    // The base adress is common for all the NSpire, CX and CX II
    base=(unsigned short *)0x900E0010;

    // the ON key is mapped differently for the CX and the CX II so we need to adress it by the correct adress
    if (is_cx2)
        specialON=(unsigned short *)0x90140810;
    else
        specialON=(unsigned short *)0x900B0028;

#else

    keys = SDL_GetKeyState(NULL);

#endif // TARGET_NSPIRE

    InternalResetState();
}


void KeyManager::InternalClose( void )
{

}

void KeyManager::InternalLogic( void )
{

#if TARGET_NSPIRE == 1
    unsigned short temp;

    // This is the mechanics aiming at checking if there is a Press / Release Event
    if (IsAnyKeyPressed() || any_key_pressed())
    {
        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = false;
        }
        else
        {
            keypressevent = true;
            keyreleaseevent = false;
        }
    }
    else
    {
        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = true;
        }
        else
        {
            keypressevent = false;
            keyreleaseevent = false;
        }
    }


    m_kbON_Previous =  m_kbON;
    if (is_cx2)
    {
        m_kbON = ((specialON[0] & 256) == 0 ) ? true : false;
    }
    else
    {
        m_kbON = ((specialON[0] & 16) == 0 ) ? true : false;
    }
    m_kbON_Press_Event = (!m_kbON_Previous && m_kbON) ? true : false;
    m_kbON_Release_Event = (m_kbON_Previous && !m_kbON) ? true : false;


    // Mapping of the very first adress, corresponding to the first unsigned short at base (or base[0]) adress
    temp = base[0];
    {
        m_kbRET_Previous =  m_kbRET;
        m_kbRET = (temp  & 1) ? true : false;
        m_kbRET_Press_Event = (!m_kbRET_Previous && m_kbRET) ? true : false;
        m_kbRET_Release_Event = (m_kbRET_Previous && !m_kbRET) ? true : false;

        m_kbENTER_Previous =  m_kbENTER;
        m_kbENTER = (temp  & 2) ? true : false;
        m_kbENTER_Press_Event = (!m_kbENTER_Previous && m_kbENTER) ? true : false;
        m_kbENTER_Release_Event = (m_kbENTER_Previous && !m_kbENTER) ? true : false;

        // bit #2 is not assigned to a key

        m_kbMINUSPAR_Previous =  m_kbMINUSPAR;
        m_kbMINUSPAR = (temp  & 8) ? true : false;
        m_kbMINUSPAR_Press_Event = (!m_kbMINUSPAR_Previous && m_kbMINUSPAR) ? true : false;
        m_kbMINUSPAR_Release_Event = (m_kbMINUSPAR_Previous && !m_kbMINUSPAR) ? true : false;

        m_kbSPACE_Previous =  m_kbSPACE;
        m_kbSPACE = (temp  & 16) ? true : false;
        m_kbSPACE_Press_Event = (!m_kbSPACE_Previous && m_kbSPACE) ? true : false;
        m_kbSPACE_Release_Event = (m_kbSPACE_Previous && !m_kbSPACE) ? true : false;

        m_kbZ_Previous =  m_kbZ;
        m_kbZ = (temp  & 32) ? true : false;
        m_kbZ_Press_Event = (!m_kbZ_Previous && m_kbZ) ? true : false;
        m_kbZ_Release_Event = (m_kbZ_Previous && !m_kbZ) ? true : false;

        m_kbY_Previous =  m_kbY;
        m_kbY = (temp  & 64) ? true : false;
        m_kbY_Press_Event = (!m_kbY_Previous && m_kbY) ? true : false;
        m_kbY_Release_Event = (m_kbY_Previous && !m_kbY) ? true : false;

        m_kb0_Previous =  m_kb0;
        m_kb0 = (temp  & 128) ? true : false;
        m_kb0_Press_Event = (!m_kb0_Previous && m_kb0) ? true : false;
        m_kb0_Release_Event = (m_kb0_Previous && !m_kb0) ? true : false;

        m_kbQUESTION_Previous =  m_kbQUESTION;
        m_kbQUESTION = (temp  & 256) ? true : false;
        m_kbQUESTION_Press_Event = (!m_kbQUESTION_Previous && m_kbQUESTION) ? true : false;
        m_kbQUESTION_Release_Event = (m_kbQUESTION_Previous && !m_kbQUESTION) ? true : false;

        // bit #9 is not assigned to a key

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+1 (or base[1]) adress
    temp = base[1];
    {
        m_kbX_Previous =  m_kbX;
        m_kbX = (temp  & 1) ? true : false;
        m_kbX_Press_Event = (!m_kbX_Previous && m_kbX) ? true : false;
        m_kbX_Release_Event = (m_kbX_Previous && !m_kbX) ? true : false;

        m_kbW_Previous =  m_kbW;
        m_kbW = (temp  & 2) ? true : false;
        m_kbW_Press_Event = (!m_kbW_Previous && m_kbW) ? true : false;
        m_kbW_Release_Event = (m_kbW_Previous && !m_kbW) ? true : false;

        m_kbV_Previous =  m_kbV;
        m_kbV = (temp  & 4) ? true : false;
        m_kbV_Press_Event = (!m_kbV_Previous && m_kbV) ? true : false;
        m_kbV_Release_Event = (m_kbV_Previous && !m_kbV) ? true : false;

        m_kb3_Previous =  m_kb3;
        m_kb3 = (temp  & 8) ? true : false;
        m_kb3_Press_Event = (!m_kb3_Previous && m_kb3) ? true : false;
        m_kb3_Release_Event = (m_kb3_Previous && !m_kb3) ? true : false;

        m_kbU_Previous =  m_kbU;
        m_kbU = (temp  & 16) ? true : false;
        m_kbU_Press_Event = (!m_kbU_Previous && m_kbU) ? true : false;
        m_kbU_Release_Event = (m_kbU_Previous && !m_kbU) ? true : false;

        m_kbT_Previous =  m_kbT;
        m_kbT = (temp  & 32) ? true : false;
        m_kbT_Press_Event = (!m_kbT_Previous && m_kbT) ? true : false;
        m_kbT_Release_Event = (m_kbT_Previous && !m_kbT) ? true : false;

        m_kbS_Previous =  m_kbS;
        m_kbS = (temp  & 64) ? true : false;
        m_kbS_Press_Event = (!m_kbS_Previous && m_kbS) ? true : false;
        m_kbS_Release_Event = (m_kbS_Previous && !m_kbS) ? true : false;

        m_kb1_Previous =  m_kb1;
        m_kb1 = (temp  & 128) ? true : false;
        m_kb1_Press_Event = (!m_kb1_Previous && m_kb1) ? true : false;
        m_kb1_Release_Event = (m_kb1_Previous && !m_kb1) ? true : false;

        m_kbPI_Previous =  m_kbPI;
        m_kbPI = (temp  & 256) ? true : false;
        m_kbPI_Press_Event = (!m_kbPI_Previous && m_kbPI) ? true : false;
        m_kbPI_Release_Event = (m_kbPI_Previous && !m_kbPI) ? true : false;

        m_kbTRIG_Previous =  m_kbTRIG;
        m_kbTRIG = (temp  & 512) ? true : false;
        m_kbTRIG_Press_Event = (!m_kbTRIG_Previous && m_kbTRIG) ? true : false;
        m_kbTRIG_Release_Event = (m_kbTRIG_Previous && !m_kbTRIG) ? true : false;

        m_kb10X_Previous =  m_kb10X;
        m_kb10X = (temp  & 1024) ? true : false;
        m_kb10X_Press_Event = (!m_kb10X_Previous && m_kb10X) ? true : false;
        m_kb10X_Release_Event = (m_kb10X_Previous && !m_kb10X) ? true : false;
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+2 (or base[2]) adress
    temp = base[2];
    {
        m_kbR_Previous =  m_kbR;
        m_kbR = (temp  & 1) ? true : false;
        m_kbR_Press_Event = (!m_kbR_Previous && m_kbR) ? true : false;
        m_kbR_Release_Event = (m_kbR_Previous && !m_kbR) ? true : false;

        m_kbQ_Previous =  m_kbQ;
        m_kbQ = (temp  & 2) ? true : false;
        m_kbQ_Press_Event = (!m_kbQ_Previous && m_kbQ) ? true : false;
        m_kbQ_Release_Event = (m_kbQ_Previous && !m_kbQ) ? true : false;

        m_kbP_Previous =  m_kbP;
        m_kbP = (temp  & 4) ? true : false;
        m_kbP_Press_Event = (!m_kbP_Previous && m_kbP) ? true : false;
        m_kbP_Release_Event = (m_kbP_Previous && !m_kbP) ? true : false;

        m_kb6_Previous =  m_kb6;
        m_kb6 = (temp  & 8) ? true : false;
        m_kb6_Press_Event = (!m_kb6_Previous && m_kb6) ? true : false;
        m_kb6_Release_Event = (m_kb6_Previous && !m_kb6) ? true : false;

        m_kbO_Previous =  m_kbO;
        m_kbO = (temp  & 16) ? true : false;
        m_kbO_Press_Event = (!m_kbO_Previous && m_kbO) ? true : false;
        m_kbO_Release_Event = (m_kbO_Previous && !m_kbO) ? true : false;

        m_kbN_Previous =  m_kbN;
        m_kbN = (temp  & 32) ? true : false;
        m_kbN_Press_Event = (!m_kbN_Previous && m_kbN) ? true : false;
        m_kbN_Release_Event = (m_kbN_Previous && !m_kbN) ? true : false;

        m_kbM_Previous =  m_kbM;
        m_kbM = (temp  & 64) ? true : false;
        m_kbM_Press_Event = (!m_kbM_Previous && m_kbM) ? true : false;
        m_kbM_Release_Event = (m_kbM_Previous && !m_kbM) ? true : false;

        m_kb4_Previous =  m_kb4;
        m_kb4 = (temp  & 128) ? true : false;
        m_kb4_Press_Event = (!m_kb4_Previous && m_kb4) ? true : false;
        m_kb4_Release_Event = (m_kb4_Previous && !m_kb4) ? true : false;

        m_kbEE_Previous =  m_kbEE;
        m_kbEE = (temp  & 256) ? true : false;
        m_kbEE_Press_Event = (!m_kbEE_Previous && m_kbEE) ? true : false;
        m_kbEE_Release_Event = (m_kbEE_Previous && !m_kbEE) ? true : false;

        m_kbX2_Previous =  m_kbX2;
        m_kbX2 = (temp  & 512) ? true : false;
        m_kbX2_Press_Event = (!m_kbX2_Previous && m_kbX2) ? true : false;
        m_kbX2_Release_Event = (m_kbX2_Previous && !m_kbX2) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+3 (or base[3]) adress
    temp = base[3];
    {
        m_kbL_Previous =  m_kbL;
        m_kbL = (temp  & 1) ? true : false;
        m_kbL_Press_Event = (!m_kbL_Previous && m_kbL) ? true : false;
        m_kbL_Release_Event = (m_kbL_Previous && !m_kbL) ? true : false;

        m_kbK_Previous =  m_kbK;
        m_kbK = (temp  & 2) ? true : false;
        m_kbK_Press_Event = (!m_kbK_Previous && m_kbK) ? true : false;
        m_kbK_Release_Event = (m_kbK_Previous && !m_kbK) ? true : false;

        m_kbJ_Previous =  m_kbJ;
        m_kbJ = (temp  & 4) ? true : false;
        m_kbJ_Press_Event = (!m_kbJ_Previous && m_kbJ) ? true : false;
        m_kbJ_Release_Event = (m_kbJ_Previous && !m_kbJ) ? true : false;

        m_kb9_Previous =  m_kb9;
        m_kb9 = (temp  & 8) ? true : false;
        m_kb9_Press_Event = (!m_kb9_Previous && m_kb9) ? true : false;
        m_kb9_Release_Event = (m_kb9_Previous && !m_kb9) ? true : false;

        m_kbI_Previous =  m_kbI;
        m_kbI = (temp  & 16) ? true : false;
        m_kbI_Press_Event = (!m_kbI_Previous && m_kbI) ? true : false;
        m_kbI_Release_Event = (m_kbI_Previous && !m_kbI) ? true : false;

        m_kbH_Previous =  m_kbH;
        m_kbH = (temp  & 32) ? true : false;
        m_kbH_Press_Event = (!m_kbH_Previous && m_kbH) ? true : false;
        m_kbH_Release_Event = (m_kbH_Previous && !m_kbH) ? true : false;

        m_kbG_Previous =  m_kbG;
        m_kbG = (temp  & 64) ? true : false;
        m_kbG_Press_Event = (!m_kbG_Previous && m_kbG) ? true : false;
        m_kbG_Release_Event = (m_kbG_Previous && !m_kbG) ? true : false;

        m_kb7_Previous =  m_kb7;
        m_kb7 = (temp  & 128) ? true : false;
        m_kb7_Press_Event = (!m_kb7_Previous && m_kb7) ? true : false;
        m_kb7_Release_Event = (m_kb7_Previous && !m_kb7) ? true : false;

        m_kbDIV_Previous =  m_kbDIV;
        m_kbDIV = (temp  & 256) ? true : false;
        m_kbDIV_Press_Event = (!m_kbDIV_Previous && m_kbDIV) ? true : false;
        m_kbDIV_Release_Event = (m_kbDIV_Previous && !m_kbDIV) ? true : false;

        m_kbEX_Previous =  m_kbEX;
        m_kbEX = (temp  & 512) ? true : false;
        m_kbEX_Press_Event = (!m_kbEX_Previous && m_kbEX) ? true : false;
        m_kbEX_Release_Event = (m_kbEX_Previous && !m_kbEX) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+4 (or base[4]) adress
    temp = base[4];
    {
        m_kbF_Previous =  m_kbF;
        m_kbF = (temp  & 1) ? true : false;
        m_kbF_Press_Event = (!m_kbF_Previous && m_kbF) ? true : false;
        m_kbF_Release_Event = (m_kbF_Previous && !m_kbF) ? true : false;

        m_kbE_Previous =  m_kbE;
        m_kbE = (temp  & 2) ? true : false;
        m_kbE_Press_Event = (!m_kbE_Previous && m_kbE) ? true : false;
        m_kbE_Release_Event = (m_kbE_Previous && !m_kbE) ? true : false;

        m_kbD_Previous =  m_kbD;
        m_kbD = (temp  & 4) ? true : false;
        m_kbD_Press_Event = (!m_kbD_Previous && m_kbD) ? true : false;
        m_kbD_Release_Event = (m_kbD_Previous && !m_kbD) ? true : false;

        // bit #3 is not assigned to a key

        m_kbC_Previous =  m_kbC;
        m_kbC = (temp  & 16) ? true : false;
        m_kbC_Press_Event = (!m_kbC_Previous && m_kbC) ? true : false;
        m_kbC_Release_Event = (m_kbC_Previous && !m_kbC) ? true : false;

        m_kbB_Previous =  m_kbB;
        m_kbB = (temp  & 32) ? true : false;
        m_kbB_Press_Event = (!m_kbB_Previous && m_kbB) ? true : false;
        m_kbB_Release_Event = (m_kbB_Previous && !m_kbB) ? true : false;

        m_kbA_Previous =  m_kbA;
        m_kbA = (temp  & 64) ? true : false;
        m_kbA_Press_Event = (!m_kbA_Previous && m_kbA) ? true : false;
        m_kbA_Release_Event = (m_kbA_Previous && !m_kbA) ? true : false;

        m_kbEQUAL_Previous =  m_kbEQUAL;
        m_kbEQUAL = (temp  & 128) ? true : false;
        m_kbEQUAL_Press_Event = (!m_kbEQUAL_Previous && m_kbEQUAL) ? true : false;
        m_kbEQUAL_Release_Event = (m_kbEQUAL_Previous && !m_kbEQUAL) ? true : false;

        m_kbMULTIPLY_Previous =  m_kbMULTIPLY;
        m_kbMULTIPLY = (temp  & 256) ? true : false;
        m_kbMULTIPLY_Press_Event = (!m_kbMULTIPLY_Previous && m_kbMULTIPLY) ? true : false;
        m_kbMULTIPLY_Release_Event = (m_kbMULTIPLY_Previous && !m_kbMULTIPLY) ? true : false;

        m_kbPOWER_Previous =  m_kbPOWER;
        m_kbPOWER = (temp  & 512) ? true : false;
        m_kbPOWER_Press_Event = (!m_kbPOWER_Previous && m_kbPOWER) ? true : false;
        m_kbPOWER_Release_Event = (m_kbPOWER_Previous && !m_kbPOWER) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+5 (or base[5]) adress
    temp = base[5];
    {
        // bit #0 is not assigned to a key

        m_kbVAR_Previous =  m_kbVAR;
        m_kbVAR = (temp  & 2) ? true : false;
        m_kbVAR_Press_Event = (!m_kbVAR_Previous && m_kbVAR) ? true : false;
        m_kbVAR_Release_Event = (m_kbVAR_Previous && !m_kbVAR) ? true : false;

        m_kbMINUS_Previous =  m_kbMINUS;
        m_kbMINUS = (temp  & 4) ? true : false;
        m_kbMINUS_Press_Event = (!m_kbMINUS_Previous && m_kbMINUS) ? true : false;
        m_kbMINUS_Release_Event = (m_kbMINUS_Previous && !m_kbMINUS) ? true : false;

        m_kbPARCLOSE_Previous =  m_kbPARCLOSE;
        m_kbPARCLOSE = (temp  & 8) ? true : false;
        m_kbPARCLOSE_Press_Event = (!m_kbPARCLOSE_Previous && m_kbPARCLOSE) ? true : false;
        m_kbPARCLOSE_Release_Event = (m_kbPARCLOSE_Previous && !m_kbPARCLOSE) ? true : false;

        m_kbDOT_Previous =  m_kbDOT;
        m_kbDOT = (temp  & 16) ? true : false;
        m_kbDOT_Press_Event = (!m_kbDOT_Previous && m_kbDOT) ? true : false;
        m_kbDOT_Release_Event = (m_kbDOT_Previous && !m_kbDOT) ? true : false;

        m_kbPAROPEN_Previous =  m_kbPAROPEN;
        m_kbPAROPEN = (temp  & 32) ? true : false;
        m_kbPAROPEN_Press_Event = (!m_kbPAROPEN_Previous && m_kbPAROPEN) ? true : false;
        m_kbPAROPEN_Release_Event = (m_kbPAROPEN_Previous && !m_kbPAROPEN) ? true : false;

        m_kb5_Previous =  m_kb5;
        m_kb5 = (temp  & 64) ? true : false;
        m_kb5_Press_Event = (!m_kb5_Previous && m_kb5) ? true : false;
        m_kb5_Release_Event = (m_kb5_Previous && !m_kb5) ? true : false;

        m_kbCATALOG_Previous =  m_kbCATALOG;
        m_kbCATALOG = (temp  & 128) ? true : false;
        m_kbCATALOG_Press_Event = (!m_kbCATALOG_Previous && m_kbCATALOG) ? true : false;
        m_kbCATALOG_Release_Event = (m_kbCATALOG_Previous && !m_kbCATALOG) ? true : false;

        m_kbFRAC_Previous =  m_kbFRAC;
        m_kbFRAC = (temp  & 256) ? true : false;
        m_kbFRAC_Press_Event = (!m_kbFRAC_Previous && m_kbFRAC) ? true : false;
        m_kbFRAC_Release_Event = (m_kbFRAC_Previous && !m_kbFRAC) ? true : false;

        m_kbDEL_Previous =  m_kbDEL;
        m_kbDEL = (temp  & 512) ? true : false;
        m_kbDEL_Press_Event = (!m_kbDEL_Previous && m_kbDEL) ? true : false;
        m_kbDEL_Release_Event = (m_kbDEL_Previous && !m_kbDEL) ? true : false;

        m_kbSCRATCH_Previous =  m_kbSCRATCH;
        m_kbSCRATCH = (temp  & 1024) ? true : false;
        m_kbSCRATCH_Press_Event = (!m_kbSCRATCH_Previous && m_kbSCRATCH) ? true : false;
        m_kbSCRATCH_Release_Event = (m_kbSCRATCH_Previous && !m_kbSCRATCH) ? true : false;
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+6 (or base[6]) adress
    temp = base[6];
    {
        m_kbFLAG_Previous =  m_kbFLAG;
        m_kbFLAG = (temp  & 1) ? true : false;
        m_kbFLAG_Press_Event = (!m_kbFLAG_Previous && m_kbFLAG) ? true : false;
        m_kbFLAG_Release_Event = (m_kbFLAG_Previous && !m_kbFLAG) ? true : false;

        // bit #1 is not assigned to a key

        m_kbPLUS_Previous =  m_kbPLUS;
        m_kbPLUS = (temp  & 4) ? true : false;
        m_kbPLUS_Press_Event = (!m_kbPLUS_Previous && m_kbPLUS) ? true : false;
        m_kbPLUS_Release_Event = (m_kbPLUS_Previous && !m_kbPLUS) ? true : false;

        m_kbDOC_Previous =  m_kbDOC;
        m_kbDOC = (temp  & 8) ? true : false;
        m_kbDOC_Press_Event = (!m_kbDOC_Previous && m_kbDOC) ? true : false;
        m_kbDOC_Release_Event = (m_kbDOC_Previous && !m_kbDOC) ? true : false;

        m_kb2_Previous =  m_kb2;
        m_kb2 = (temp  & 16) ? true : false;
        m_kb2_Press_Event = (!m_kb2_Previous && m_kb2) ? true : false;
        m_kb2_Release_Event = (m_kb2_Previous && !m_kb2) ? true : false;

        m_kbMENU_Previous =  m_kbMENU;
        m_kbMENU = (temp  & 32) ? true : false;
        m_kbMENU_Press_Event = (!m_kbMENU_Previous && m_kbMENU) ? true : false;
        m_kbMENU_Release_Event = (m_kbMENU_Previous && !m_kbMENU) ? true : false;

        m_kb8_Previous =  m_kb8;
        m_kb8 = (temp  & 64) ? true : false;
        m_kb8_Press_Event = (!m_kb8_Previous && m_kb8) ? true : false;
        m_kb8_Release_Event = (m_kb8_Previous && !m_kb8) ? true : false;

        m_kbESC_Previous =  m_kbESC;
        m_kbESC = (temp  & 128) ? true : false;
        m_kbESC_Press_Event = (!m_kbESC_Previous && m_kbESC) ? true : false;
        m_kbESC_Release_Event = (m_kbESC_Previous && !m_kbESC) ? true : false;

        // bit #8 is not assigned to a key

        m_kbTAB_Previous =  m_kbTAB;
        m_kbTAB = (temp  & 512) ? true : false;
        m_kbTAB_Press_Event = (!m_kbTAB_Previous && m_kbTAB) ? true : false;
        m_kbTAB_Release_Event = (m_kbTAB_Previous && !m_kbTAB) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the last adress, corresponding to the first unsigned short at base+7 (or base[7]) adress
    temp = base[7];
    {
        // bit #0 is not assigned to a key

        // bit #1 is not assigned to a key

        // bit #2 is not assigned to a key

        // bit #3 is not assigned to a key

        // bit #4 is not assigned to a key

        // bit #5 is not assigned to a key

        // bit #6 is not assigned to a key

        // bit #7 is not assigned to a key

        m_kbSHIFT_Previous =  m_kbSHIFT;
        m_kbSHIFT = (temp  & 256) ? true : false;
        m_kbSHIFT_Press_Event = (!m_kbSHIFT_Previous && m_kbSHIFT) ? true : false;
        m_kbSHIFT_Release_Event = (m_kbSHIFT_Previous && !m_kbSHIFT) ? true : false;

        m_kbCTRL_Previous =  m_kbCTRL;
        m_kbCTRL = (temp  & 512) ? true : false;
        m_kbCTRL_Press_Event = (!m_kbCTRL_Previous && m_kbCTRL) ? true : false;
        m_kbCTRL_Release_Event = (m_kbCTRL_Previous && !m_kbCTRL) ? true : false;

        m_kbCOMMA_Previous =  m_kbCOMMA;
        m_kbCOMMA = (temp  & 1024) ? true : false;
        m_kbCOMMA_Press_Event = (!m_kbCOMMA_Previous && m_kbCOMMA) ? true : false;
        m_kbCOMMA_Release_Event = (m_kbCOMMA_Previous && !m_kbCOMMA) ? true : false;
    }

#else

    if (IsAnyKeyPressed())
    {
        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = false;
        }
        else
        {
            keypressevent = true;
            keyreleaseevent = false;
        }
    }
    else
    {
        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = true;
        }
        else
        {
            keypressevent = false;
            keyreleaseevent = false;
        }
    }


    SDL_PumpEvents();

    // TRY TO MAP SDL_KeyCode to TI NSPIRE Keys for compatibility

    m_kbRET_Previous =  m_kbRET;
    m_kbRET = keys[ SDLK_KP_EQUALS ];
    m_kbRET_Press_Event = (!m_kbRET_Previous && m_kbRET) ? true : false;
    m_kbRET_Release_Event = (m_kbRET_Previous && !m_kbRET) ? true : false;

    m_kbENTER_Previous =  m_kbENTER;
    m_kbENTER = keys[ SDLK_RETURN ];
    m_kbENTER_Press_Event = (!m_kbENTER_Previous && m_kbENTER) ? true : false;
    m_kbENTER_Release_Event = (m_kbENTER_Previous && !m_kbENTER) ? true : false;

    m_kbMINUSPAR_Previous =  m_kbMINUSPAR;
    m_kbMINUSPAR = keys[ SDLK_KP_MINUS ];
    m_kbMINUSPAR_Press_Event = (!m_kbMINUSPAR_Previous && m_kbMINUSPAR) ? true : false;
    m_kbMINUSPAR_Release_Event = (m_kbMINUSPAR_Previous && !m_kbMINUSPAR) ? true : false;

    m_kbSPACE_Previous =  m_kbSPACE;
    m_kbSPACE = keys[ SDLK_SPACE ];
    m_kbSPACE_Press_Event = (!m_kbSPACE_Previous && m_kbSPACE) ? true : false;
    m_kbSPACE_Release_Event = (m_kbSPACE_Previous && !m_kbSPACE) ? true : false;

    m_kbZ_Previous =  m_kbZ;
    m_kbZ = keys[ SDLK_z ];
    m_kbZ_Press_Event = (!m_kbZ_Previous && m_kbZ) ? true : false;
    m_kbZ_Release_Event = (m_kbZ_Previous && !m_kbZ) ? true : false;

    m_kbY_Previous =  m_kbY;
    m_kbY = keys[ SDLK_y ];
    m_kbY_Press_Event = (!m_kbY_Previous && m_kbY) ? true : false;
    m_kbY_Release_Event = (m_kbY_Previous && !m_kbY) ? true : false;

    m_kb0_Previous =  m_kb0;
    m_kb0 = keys[ SDLK_0 ] || keys[ SDLK_KP0 ];
    m_kb0_Press_Event = (!m_kb0_Previous && m_kb0) ? true : false;
    m_kb0_Release_Event = (m_kb0_Previous && !m_kb0) ? true : false;

    m_kbQUESTION_Previous =  m_kbQUESTION;
    m_kbQUESTION = keys[ SDLK_QUESTION ];
    m_kbQUESTION_Press_Event = (!m_kbQUESTION_Previous && m_kbQUESTION) ? true : false;
    m_kbQUESTION_Release_Event = (m_kbQUESTION_Previous && !m_kbQUESTION) ? true : false;

    m_kbX_Previous =  m_kbX;
    m_kbX = keys[ SDLK_x ];
    m_kbX_Press_Event = (!m_kbX_Previous && m_kbX) ? true : false;
    m_kbX_Release_Event = (m_kbX_Previous && !m_kbX) ? true : false;

    m_kbW_Previous =  m_kbW;
    m_kbW = keys[ SDLK_w ];
    m_kbW_Press_Event = (!m_kbW_Previous && m_kbW) ? true : false;
    m_kbW_Release_Event = (m_kbW_Previous && !m_kbW) ? true : false;

    m_kbV_Previous =  m_kbV;
    m_kbV = keys[ SDLK_v ];
    m_kbV_Press_Event = (!m_kbV_Previous && m_kbV) ? true : false;
    m_kbV_Release_Event = (m_kbV_Previous && !m_kbV) ? true : false;

    m_kb3_Previous =  m_kb3;
    m_kb3 = keys[ SDLK_3 ] || keys[ SDLK_KP3 ];
    m_kb3_Press_Event = (!m_kb3_Previous && m_kb3) ? true : false;
    m_kb3_Release_Event = (m_kb3_Previous && !m_kb3) ? true : false;

    m_kbU_Previous =  m_kbU;
    m_kbU = keys[ SDLK_u ];
    m_kbU_Press_Event = (!m_kbU_Previous && m_kbU) ? true : false;
    m_kbU_Release_Event = (m_kbU_Previous && !m_kbU) ? true : false;

    m_kbT_Previous =  m_kbT;
    m_kbT = keys[ SDLK_t ];
    m_kbT_Press_Event = (!m_kbT_Previous && m_kbT) ? true : false;
    m_kbT_Release_Event = (m_kbT_Previous && !m_kbT) ? true : false;

    m_kbS_Previous =  m_kbS;
    m_kbS = keys[ SDLK_s ];
    m_kbS_Press_Event = (!m_kbS_Previous && m_kbS) ? true : false;
    m_kbS_Release_Event = (m_kbS_Previous && !m_kbS) ? true : false;

    m_kb1_Previous =  m_kb1;
    m_kb1 = keys[ SDLK_1 ] || keys[ SDLK_KP1 ];
    m_kb1_Press_Event = (!m_kb1_Previous && m_kb1) ? true : false;
    m_kb1_Release_Event = (m_kb1_Previous && !m_kb1) ? true : false;

    m_kbPI_Previous =  m_kbPI;
    m_kbPI = keys[ SDLK_F1 ];
    m_kbPI_Press_Event = (!m_kbPI_Previous && m_kbPI) ? true : false;
    m_kbPI_Release_Event = (m_kbPI_Previous && !m_kbPI) ? true : false;

    m_kbTRIG_Previous =  m_kbTRIG;
    m_kbTRIG = keys[ SDLK_F2 ];
    m_kbTRIG_Press_Event = (!m_kbTRIG_Previous && m_kbTRIG) ? true : false;
    m_kbTRIG_Release_Event = (m_kbTRIG_Previous && !m_kbTRIG) ? true : false;

    m_kb10X_Previous =  m_kb10X;
    m_kb10X = keys[ SDLK_F3 ];
    m_kb10X_Press_Event = (!m_kb10X_Previous && m_kb10X) ? true : false;
    m_kb10X_Release_Event = (m_kb10X_Previous && !m_kb10X) ? true : false;

    m_kbR_Previous =  m_kbR;
    m_kbR = keys[ SDLK_r ];
    m_kbR_Press_Event = (!m_kbR_Previous && m_kbR) ? true : false;
    m_kbR_Release_Event = (m_kbR_Previous && !m_kbR) ? true : false;

    m_kbQ_Previous =  m_kbQ;
    m_kbQ = keys[ SDLK_q ];
    m_kbQ_Press_Event = (!m_kbQ_Previous && m_kbQ) ? true : false;
    m_kbQ_Release_Event = (m_kbQ_Previous && !m_kbQ) ? true : false;

    m_kbP_Previous =  m_kbP;
    m_kbP = keys[ SDLK_p ];
    m_kbP_Press_Event = (!m_kbP_Previous && m_kbP) ? true : false;
    m_kbP_Release_Event = (m_kbP_Previous && !m_kbP) ? true : false;

    m_kb6_Previous =  m_kb6;
    m_kb6 = keys[ SDLK_6 ] || keys[ SDLK_KP6 ];
    m_kb6_Press_Event = (!m_kb6_Previous && m_kb6) ? true : false;
    m_kb6_Release_Event = (m_kb6_Previous && !m_kb6) ? true : false;

    m_kbO_Previous =  m_kbO;
    m_kbO = keys[ SDLK_o ];
    m_kbO_Press_Event = (!m_kbO_Previous && m_kbO) ? true : false;
    m_kbO_Release_Event = (m_kbO_Previous && !m_kbO) ? true : false;

    m_kbN_Previous =  m_kbN;
    m_kbN = keys[ SDLK_n ];
    m_kbN_Press_Event = (!m_kbN_Previous && m_kbN) ? true : false;
    m_kbN_Release_Event = (m_kbN_Previous && !m_kbN) ? true : false;

    m_kbM_Previous =  m_kbM;
    m_kbM = keys[ SDLK_m ];
    m_kbM_Press_Event = (!m_kbM_Previous && m_kbM) ? true : false;
    m_kbM_Release_Event = (m_kbM_Previous && !m_kbM) ? true : false;

    m_kb4_Previous =  m_kb4;
    m_kb4 = keys[ SDLK_4 ] || keys[ SDLK_KP4 ];
    m_kb4_Press_Event = (!m_kb4_Previous && m_kb4) ? true : false;
    m_kb4_Release_Event = (m_kb4_Previous && !m_kb4) ? true : false;

    m_kbEE_Previous =  m_kbEE;
    m_kbEE = keys[ SDLK_F4 ];
    m_kbEE_Press_Event = (!m_kbEE_Previous && m_kbEE) ? true : false;
    m_kbEE_Release_Event = (m_kbEE_Previous && !m_kbEE) ? true : false;

    m_kbX2_Previous =  m_kbX2;
    m_kbX2 = keys[ SDLK_F5 ];
    m_kbX2_Press_Event = (!m_kbX2_Previous && m_kbX2) ? true : false;
    m_kbX2_Release_Event = (m_kbX2_Previous && !m_kbX2) ? true : false;

    m_kbL_Previous =  m_kbL;
    m_kbL = keys[ SDLK_l ];
    m_kbL_Press_Event = (!m_kbL_Previous && m_kbL) ? true : false;
    m_kbL_Release_Event = (m_kbL_Previous && !m_kbL) ? true : false;

    m_kbK_Previous =  m_kbK;
    m_kbK = keys[ SDLK_k ];
    m_kbK_Press_Event = (!m_kbK_Previous && m_kbK) ? true : false;
    m_kbK_Release_Event = (m_kbK_Previous && !m_kbK) ? true : false;

    m_kbJ_Previous =  m_kbJ;
    m_kbJ = keys[ SDLK_j ];
    m_kbJ_Press_Event = (!m_kbJ_Previous && m_kbJ) ? true : false;
    m_kbJ_Release_Event = (m_kbJ_Previous && !m_kbJ) ? true : false;

    m_kb9_Previous =  m_kb9;
    m_kb9 = keys[ SDLK_9 ] || keys[ SDLK_KP9 ];
    m_kb9_Press_Event = (!m_kb9_Previous && m_kb9) ? true : false;
    m_kb9_Release_Event = (m_kb9_Previous && !m_kb9) ? true : false;

    m_kbI_Previous =  m_kbI;
    m_kbI = keys[ SDLK_i ];
    m_kbI_Press_Event = (!m_kbI_Previous && m_kbI) ? true : false;
    m_kbI_Release_Event = (m_kbI_Previous && !m_kbI) ? true : false;

    m_kbH_Previous =  m_kbH;
    m_kbH = keys[ SDLK_h ];
    m_kbH_Press_Event = (!m_kbH_Previous && m_kbH) ? true : false;
    m_kbH_Release_Event = (m_kbH_Previous && !m_kbH) ? true : false;

    m_kbG_Previous =  m_kbG;
    m_kbG = keys[ SDLK_g ];
    m_kbG_Press_Event = (!m_kbG_Previous && m_kbG) ? true : false;
    m_kbG_Release_Event = (m_kbG_Previous && !m_kbG) ? true : false;

    m_kb7_Previous =  m_kb7;
    m_kb7 = keys[ SDLK_7 ] || keys[ SDLK_KP7 ];
    m_kb7_Press_Event = (!m_kb7_Previous && m_kb7) ? true : false;
    m_kb7_Release_Event = (m_kb7_Previous && !m_kb7) ? true : false;

    m_kbDIV_Previous =  m_kbDIV;
    m_kbDIV = keys[ SDLK_KP_DIVIDE ];
    m_kbDIV_Press_Event = (!m_kbDIV_Previous && m_kbDIV) ? true : false;
    m_kbDIV_Release_Event = (m_kbDIV_Previous && !m_kbDIV) ? true : false;

    m_kbEX_Previous =  m_kbEX;
    m_kbEX = keys[ SDLK_F6 ];
    m_kbEX_Press_Event = (!m_kbEX_Previous && m_kbEX) ? true : false;
    m_kbEX_Release_Event = (m_kbEX_Previous && !m_kbEX) ? true : false;

    m_kbF_Previous =  m_kbF;
    m_kbF = keys[ SDLK_f ];
    m_kbF_Press_Event = (!m_kbF_Previous && m_kbF) ? true : false;
    m_kbF_Release_Event = (m_kbF_Previous && !m_kbF) ? true : false;

    m_kbE_Previous =  m_kbE;
    m_kbE = keys[ SDLK_e ];
    m_kbE_Press_Event = (!m_kbE_Previous && m_kbE) ? true : false;
    m_kbE_Release_Event = (m_kbE_Previous && !m_kbE) ? true : false;

    m_kbD_Previous =  m_kbD;
    m_kbD = keys[ SDLK_d ];
    m_kbD_Press_Event = (!m_kbD_Previous && m_kbD) ? true : false;
    m_kbD_Release_Event = (m_kbD_Previous && !m_kbD) ? true : false;

    m_kbC_Previous =  m_kbC;
    m_kbC = keys[ SDLK_c ];
    m_kbC_Press_Event = (!m_kbC_Previous && m_kbC) ? true : false;
    m_kbC_Release_Event = (m_kbC_Previous && !m_kbC) ? true : false;

    m_kbB_Previous =  m_kbB;
    m_kbB = keys[ SDLK_b ];
    m_kbB_Press_Event = (!m_kbB_Previous && m_kbB) ? true : false;
    m_kbB_Release_Event = (m_kbB_Previous && !m_kbB) ? true : false;

    m_kbA_Previous =  m_kbA;
    m_kbA =keys[ SDLK_a ];
    m_kbA_Press_Event = (!m_kbA_Previous && m_kbA) ? true : false;
    m_kbA_Release_Event = (m_kbA_Previous && !m_kbA) ? true : false;

    m_kbEQUAL_Previous =  m_kbEQUAL;
    m_kbEQUAL = keys[ SDLK_KP_EQUALS ];
    m_kbEQUAL_Press_Event = (!m_kbEQUAL_Previous && m_kbEQUAL) ? true : false;
    m_kbEQUAL_Release_Event = (m_kbEQUAL_Previous && !m_kbEQUAL) ? true : false;

    m_kbMULTIPLY_Previous =  m_kbMULTIPLY;
    m_kbMULTIPLY = keys[ SDLK_KP_MULTIPLY ];
    m_kbMULTIPLY_Press_Event = (!m_kbMULTIPLY_Previous && m_kbMULTIPLY) ? true : false;
    m_kbMULTIPLY_Release_Event = (m_kbMULTIPLY_Previous && !m_kbMULTIPLY) ? true : false;

    m_kbPOWER_Previous =  m_kbPOWER;
    m_kbPOWER = keys[ SDLK_F7 ];
    m_kbPOWER_Press_Event = (!m_kbPOWER_Previous && m_kbPOWER) ? true : false;
    m_kbPOWER_Release_Event = (m_kbPOWER_Previous && !m_kbPOWER) ? true : false;

    m_kbVAR_Previous =  m_kbVAR;
    m_kbVAR = keys[ SDLK_F8 ];
    m_kbVAR_Press_Event = (!m_kbVAR_Previous && m_kbVAR) ? true : false;
    m_kbVAR_Release_Event = (m_kbVAR_Previous && !m_kbVAR) ? true : false;

    m_kbMINUS_Previous =  m_kbMINUS;
    m_kbMINUS = keys[ SDLK_KP_MINUS ];
    m_kbMINUS_Press_Event = (!m_kbMINUS_Previous && m_kbMINUS) ? true : false;
    m_kbMINUS_Release_Event = (m_kbMINUS_Previous && !m_kbMINUS) ? true : false;

    m_kbPARCLOSE_Previous =  m_kbPARCLOSE;
    m_kbPARCLOSE = keys[ SDLK_RIGHTPAREN ];
    m_kbPARCLOSE_Press_Event = (!m_kbPARCLOSE_Previous && m_kbPARCLOSE) ? true : false;
    m_kbPARCLOSE_Release_Event = (m_kbPARCLOSE_Previous && !m_kbPARCLOSE) ? true : false;

    m_kbDOT_Previous =  m_kbDOT;
    m_kbDOT = keys[ SDLK_KP_PERIOD ];
    m_kbDOT_Press_Event = (!m_kbDOT_Previous && m_kbDOT) ? true : false;
    m_kbDOT_Release_Event = (m_kbDOT_Previous && !m_kbDOT) ? true : false;

    m_kbPAROPEN_Previous =  m_kbPAROPEN;
    m_kbPAROPEN = keys[ SDLK_LEFTPAREN ];
    m_kbPAROPEN_Press_Event = (!m_kbPAROPEN_Previous && m_kbPAROPEN) ? true : false;
    m_kbPAROPEN_Release_Event = (m_kbPAROPEN_Previous && !m_kbPAROPEN) ? true : false;

    m_kb5_Previous =  m_kb5;
    m_kb5 = keys[ SDLK_5 ] || keys[ SDLK_KP5 ];
    m_kb5_Press_Event = (!m_kb5_Previous && m_kb5) ? true : false;
    m_kb5_Release_Event = (m_kb5_Previous && !m_kb5) ? true : false;

    m_kbCATALOG_Previous =  m_kbCATALOG;
    m_kbCATALOG = keys[ SDLK_F9 ];
    m_kbCATALOG_Press_Event = (!m_kbCATALOG_Previous && m_kbCATALOG) ? true : false;
    m_kbCATALOG_Release_Event = (m_kbCATALOG_Previous && !m_kbCATALOG) ? true : false;

    m_kbFRAC_Previous =  m_kbFRAC;
    m_kbFRAC = keys[ SDLK_F9 ];
    m_kbFRAC_Press_Event = (!m_kbFRAC_Previous && m_kbFRAC) ? true : false;
    m_kbFRAC_Release_Event = (m_kbFRAC_Previous && !m_kbFRAC) ? true : false;

    m_kbDEL_Previous =  m_kbDEL;
    m_kbDEL = keys[ SDLK_DELETE ];
    m_kbDEL_Press_Event = (!m_kbDEL_Previous && m_kbDEL) ? true : false;
    m_kbDEL_Release_Event = (m_kbDEL_Previous && !m_kbDEL) ? true : false;

    m_kbSCRATCH_Previous =  m_kbSCRATCH;
    m_kbSCRATCH = keys[ SDLK_F10 ];
    m_kbSCRATCH_Press_Event = (!m_kbSCRATCH_Previous && m_kbSCRATCH) ? true : false;
    m_kbSCRATCH_Release_Event = (m_kbSCRATCH_Previous && !m_kbSCRATCH) ? true : false;

    m_kbFLAG_Previous =  m_kbFLAG;
    m_kbFLAG = keys[ SDLK_F11 ];
    m_kbFLAG_Press_Event = (!m_kbFLAG_Previous && m_kbFLAG) ? true : false;
    m_kbFLAG_Release_Event = (m_kbFLAG_Previous && !m_kbFLAG) ? true : false;

    m_kbPLUS_Previous =  m_kbPLUS;
    m_kbPLUS = keys[ SDLK_KP_PLUS ];
    m_kbPLUS_Press_Event = (!m_kbPLUS_Previous && m_kbPLUS) ? true : false;
    m_kbPLUS_Release_Event = (m_kbPLUS_Previous && !m_kbPLUS) ? true : false;

    m_kbDOC_Previous =  m_kbDOC;
    m_kbDOC = keys[ SDLK_F12 ];
    m_kbDOC_Press_Event = (!m_kbDOC_Previous && m_kbDOC) ? true : false;
    m_kbDOC_Release_Event = (m_kbDOC_Previous && !m_kbDOC) ? true : false;

    m_kb2_Previous =  m_kb2;
    m_kb2 = keys[ SDLK_2 ] || keys[ SDLK_KP2 ];
    m_kb2_Press_Event = (!m_kb2_Previous && m_kb2) ? true : false;
    m_kb2_Release_Event = (m_kb2_Previous && !m_kb2) ? true : false;

    m_kbMENU_Previous =  m_kbMENU;
    m_kbMENU = keys[ SDLK_F8 ];
    m_kbMENU_Press_Event = (!m_kbMENU_Previous && m_kbMENU) ? true : false;
    m_kbMENU_Release_Event = (m_kbMENU_Previous && !m_kbMENU) ? true : false;

    m_kb8_Previous =  m_kb8;
    m_kb8 = keys[ SDLK_8 ] || keys[ SDLK_KP8 ];
    m_kb8_Press_Event = (!m_kb8_Previous && m_kb8) ? true : false;
    m_kb8_Release_Event = (m_kb8_Previous && !m_kb8) ? true : false;

    m_kbESC_Previous =  m_kbESC;
    m_kbESC = keys[ SDLK_ESCAPE ];
    m_kbESC_Press_Event = (!m_kbESC_Previous && m_kbESC) ? true : false;
    m_kbESC_Release_Event = (m_kbESC_Previous && !m_kbESC) ? true : false;

    m_kbTAB_Previous =  m_kbTAB;
    m_kbTAB = keys[ SDLK_TAB ];
    m_kbTAB_Press_Event = (!m_kbTAB_Previous && m_kbTAB) ? true : false;
    m_kbTAB_Release_Event = (m_kbTAB_Previous && !m_kbTAB) ? true : false;

    m_kbSHIFT_Previous =  m_kbSHIFT;
    m_kbSHIFT = keys[ SDLK_LSHIFT ]  || keys[ SDLK_RSHIFT ];
    m_kbSHIFT_Press_Event = (!m_kbSHIFT_Previous && m_kbSHIFT) ? true : false;
    m_kbSHIFT_Release_Event = (m_kbSHIFT_Previous && !m_kbSHIFT) ? true : false;

    m_kbCTRL_Previous =  m_kbCTRL;
    m_kbCTRL = keys[ SDLK_LCTRL ]  || keys[ SDLK_RCTRL ];
    m_kbCTRL_Press_Event = (!m_kbCTRL_Previous && m_kbCTRL) ? true : false;
    m_kbCTRL_Release_Event = (m_kbCTRL_Previous && !m_kbCTRL) ? true : false;

    m_kbCOMMA_Previous =  m_kbCOMMA;
    m_kbCOMMA = keys[ SDLK_COMMA ];
    m_kbCOMMA_Press_Event = (!m_kbCOMMA_Previous && m_kbCOMMA) ? true : false;
    m_kbCOMMA_Release_Event = (m_kbCOMMA_Previous && !m_kbCOMMA) ? true : false;

    m_kbON_Previous =  m_kbON;
    m_kbON = keys[ SDLK_PRINT ];
    m_kbON_Press_Event = (!m_kbON_Previous && m_kbON) ? true : false;
    m_kbON_Release_Event = (m_kbON_Previous && !m_kbON) ? true : false;

#endif


    if (keypressevent || keyreleaseevent)
    {
        keyevent = true;
    }
    else
    {
        keyevent = false;
    }

    if (keypressevent)
    {
        // if not already locked in capitals and SHIFT+CTRL are pressed together --> we switch to capital mode
        if (!capsonmode && m_kbCTRL && m_kbSHIFT) capsonmode=true;
        //if capital mode is on and SHIFT is pressed without CTRL --> we switch back to normal mode
        else if (capsonmode && !m_kbCTRL && m_kbSHIFT) capsonmode = false;
        //if capital mode is on and CTRL is pressed without SHIFT --> we switch back to normal mode
        else if (capsonmode && m_kbCTRL && !m_kbSHIFT) capsonmode = false;
    }

}

bool KeyManager::InternalIsAnyKeyEvent( void )
{
    return keyevent;
}

bool KeyManager::InternalIsKeyPressEvent( void )
{
    return keypressevent;
}

bool KeyManager::InternalIsKeyReleaseEvent( void )
{
    return keyreleaseevent;
}



/*
void KeyManager::InternalSetSelection( std::string select )
{
       selection = select;
}

std::string KeyManager::InternalGetSelection( void )
{
       return selection;
}

void KeyManager::InternalFlushSelection( void )
{
       selection.clear();
}
*/

void KeyManager::InternalResetState( void )
{
    // general state variables for regular keys event
    keyevent = false;
    keypressevent = false;
    keyreleaseevent = false;

    capsonmode = false;

    // First adress block
    m_kbRET = false;
    m_kbRET_Press_Event = false;
    m_kbRET_Release_Event = false;
    m_kbENTER = false;
    m_kbENTER_Press_Event = false;
    m_kbENTER_Release_Event = false;
    m_kbMINUSPAR = false;
    m_kbMINUSPAR_Press_Event = false;
    m_kbMINUSPAR_Release_Event = false;
    m_kbSPACE = false;
    m_kbSPACE_Press_Event = false;
    m_kbSPACE_Release_Event = false;
    m_kbZ = false;
    m_kbZ_Press_Event = false;
    m_kbZ_Release_Event = false;
    m_kbY = false;
    m_kbY_Press_Event = false;
    m_kbY_Release_Event = false;
    m_kb0 = false;
    m_kb0_Press_Event = false;
    m_kb0_Release_Event = false;
    m_kbQUESTION = false;
    m_kbQUESTION_Press_Event = false;
    m_kbQUESTION_Release_Event = false;
    m_kbON = false;
    m_kbON_Press_Event = false;
    m_kbON_Release_Event = false;

    // Second adress block
    m_kbX = false;
    m_kbX_Press_Event = false;
    m_kbX_Release_Event = false;
    m_kbW = false;
    m_kbW_Press_Event = false;
    m_kbW_Release_Event = false;
    m_kbV = false;
    m_kbV_Press_Event = false;
    m_kbV_Release_Event = false;
    m_kb3 = false;
    m_kb3_Press_Event = false;
    m_kb3_Release_Event = false;
    m_kbU = false;
    m_kbU_Press_Event = false;
    m_kbU_Release_Event = false;
    m_kbT = false;
    m_kbT_Press_Event = false;
    m_kbT_Release_Event = false;
    m_kbS = false;
    m_kbS_Press_Event = false;
    m_kbS_Release_Event = false;
    m_kb1 = false;
    m_kb1_Press_Event = false;
    m_kb1_Release_Event = false;
    m_kbPI = false;
    m_kbPI_Press_Event = false;
    m_kbPI_Release_Event = false;
    m_kbTRIG = false;
    m_kbTRIG_Press_Event = false;
    m_kbTRIG_Release_Event = false;
    m_kb10X = false;
    m_kb10X_Press_Event = false;
    m_kb10X_Release_Event = false;

    // Third adress block
    m_kbR = false;
    m_kbR_Press_Event = false;
    m_kbR_Release_Event = false;
    m_kbQ = false;
    m_kbQ_Press_Event = false;
    m_kbQ_Release_Event = false;
    m_kbP = false;
    m_kbP_Press_Event = false;
    m_kbP_Release_Event = false;
    m_kb6 = false;
    m_kb6_Press_Event = false;
    m_kb6_Release_Event = false;
    m_kbO = false;
    m_kbO_Press_Event = false;
    m_kbO_Release_Event = false;
    m_kbN = false;
    m_kbN_Press_Event = false;
    m_kbN_Release_Event = false;
    m_kbM = false;
    m_kbM_Press_Event = false;
    m_kbM_Release_Event = false;
    m_kb4 = false;
    m_kb4_Press_Event = false;
    m_kb4_Release_Event = false;
    m_kbEE = false;
    m_kbEE_Press_Event = false;
    m_kbEE_Release_Event = false;
    m_kbX2 = false;
    m_kbX2_Press_Event = false;
    m_kbX2_Release_Event = false;

    // Fourth adress block
    m_kbL = false;
    m_kbL_Press_Event = false;
    m_kbL_Release_Event = false;
    m_kbK = false;
    m_kbK_Press_Event = false;
    m_kbK_Release_Event = false;
    m_kbJ = false;
    m_kbJ_Press_Event = false;
    m_kbJ_Release_Event = false;
    m_kb9 = false;
    m_kb9_Press_Event = false;
    m_kb9_Release_Event = false;
    m_kbI = false;
    m_kbI_Press_Event = false;
    m_kbI_Release_Event = false;
    m_kbH = false;
    m_kbH_Press_Event = false;
    m_kbH_Release_Event = false;
    m_kbG = false;
    m_kbG_Press_Event = false;
    m_kbG_Release_Event = false;
    m_kb7 = false;
    m_kb7_Press_Event = false;
    m_kb7_Release_Event = false;
    m_kbDIV = false;
    m_kbDIV_Press_Event = false;
    m_kbDIV_Release_Event = false;
    m_kbEX = false;
    m_kbEX_Press_Event = false;
    m_kbEX_Release_Event = false;

    // Fifth adress block
    m_kbF = false;
    m_kbF_Press_Event = false;
    m_kbF_Release_Event = false;
    m_kbE = false;
    m_kbE_Press_Event = false;
    m_kbE_Release_Event = false;
    m_kbD = false;
    m_kbD_Press_Event = false;
    m_kbD_Release_Event = false;
    m_kbC = false;
    m_kbC_Press_Event = false;
    m_kbC_Release_Event = false;
    m_kbB = false;
    m_kbB_Press_Event = false;
    m_kbB_Release_Event = false;
    m_kbA = false;
    m_kbA_Press_Event = false;
    m_kbA_Release_Event = false;
    m_kbEQUAL = false;
    m_kbEQUAL_Press_Event = false;
    m_kbEQUAL_Release_Event = false;
    m_kbMULTIPLY = false;
    m_kbMULTIPLY_Press_Event = false;
    m_kbMULTIPLY_Release_Event = false;
    m_kbPOWER = false;
    m_kbPOWER_Press_Event = false;
    m_kbPOWER_Release_Event = false;

    // Sixth adress block
    m_kbVAR = false;
    m_kbVAR_Press_Event = false;
    m_kbVAR_Release_Event = false;
    m_kbMINUS = false;
    m_kbMINUS_Press_Event = false;
    m_kbMINUS_Release_Event = false;
    m_kbPARCLOSE = false;
    m_kbPARCLOSE_Press_Event = false;
    m_kbPARCLOSE_Release_Event = false;
    m_kbDOT = false;
    m_kbDOT_Press_Event = false;
    m_kbDOT_Release_Event = false;
    m_kbPAROPEN = false;
    m_kbPAROPEN_Press_Event = false;
    m_kbPAROPEN_Release_Event = false;
    m_kb5 = false;
    m_kb5_Press_Event = false;
    m_kb5_Release_Event = false;
    m_kbCATALOG = false;
    m_kbCATALOG_Press_Event = false;
    m_kbCATALOG_Release_Event = false;
    m_kbFRAC = false;
    m_kbFRAC_Press_Event = false;
    m_kbFRAC_Release_Event = false;
    m_kbDEL = false;
    m_kbDEL_Press_Event = false;
    m_kbDEL_Release_Event = false;
    m_kbSCRATCH = false;
    m_kbSCRATCH_Press_Event = false;
    m_kbSCRATCH_Release_Event = false;

    // Seventh adress block
    m_kbFLAG = false;
    m_kbFLAG_Press_Event = false;
    m_kbFLAG_Release_Event = false;
    m_kbPLUS = false;
    m_kbPLUS_Press_Event = false;
    m_kbPLUS_Release_Event = false;
    m_kbDOC = false;
    m_kbDOC_Press_Event = false;
    m_kbDOC_Release_Event = false;
    m_kb2 = false;
    m_kb2_Press_Event = false;
    m_kb2_Release_Event = false;
    m_kbMENU = false;
    m_kbMENU_Press_Event = false;
    m_kbMENU_Release_Event = false;
    m_kb8 = false;
    m_kb8_Press_Event = false;
    m_kb8_Release_Event = false;
    m_kbESC = false;
    m_kbESC_Press_Event = false;
    m_kbESC_Release_Event = false;
    m_kbTAB = false;
    m_kbTAB_Press_Event = false;
    m_kbTAB_Release_Event = false;

    // Eigth adress block
    m_kbSHIFT = false;
    m_kbSHIFT_Press_Event = false;
    m_kbSHIFT_Release_Event = false;
    m_kbCTRL = false;
    m_kbCTRL_Press_Event = false;
    m_kbCTRL_Release_Event = false;
    m_kbCOMMA = false;
    m_kbCOMMA_Press_Event = false;
    m_kbCOMMA_Release_Event = false;


    // First adress block
    m_kbRET_Previous = false;
    m_kbENTER_Previous = false;
    m_kbMINUSPAR_Previous = false;
    m_kbSPACE_Previous = false;
    m_kbZ_Previous = false;
    m_kbY_Previous = false;
    m_kb0_Previous = false;
    m_kbQUESTION_Previous = false;
    m_kbON_Previous = false;

    // Second adress block
    m_kbX_Previous = false;
    m_kbW_Previous = false;
    m_kbV_Previous = false;
    m_kb3_Previous = false;
    m_kbU_Previous = false;
    m_kbT_Previous = false;
    m_kbS_Previous = false;
    m_kb1_Previous = false;
    m_kbPI_Previous = false;
    m_kbTRIG_Previous = false;
    m_kb10X_Previous = false;

    // Third adress block
    m_kbR_Previous = false;
    m_kbQ_Previous = false;
    m_kbP_Previous = false;
    m_kb6_Previous = false;
    m_kbO_Previous = false;
    m_kbN_Previous = false;
    m_kbM_Previous = false;
    m_kb4_Previous = false;
    m_kbEE_Previous = false;
    m_kbX2_Previous = false;

    // Fourth adress block
    m_kbL_Previous = false;
    m_kbK_Previous = false;
    m_kbJ_Previous = false;
    m_kb9_Previous = false;
    m_kbI_Previous = false;
    m_kbH_Previous = false;
    m_kbG_Previous = false;
    m_kb7_Previous = false;
    m_kbDIV_Previous = false;
    m_kbEX_Previous = false;

    // Fifth adress block
    m_kbF_Previous = false;
    m_kbE_Previous = false;
    m_kbD_Previous = false;
    m_kbC_Previous = false;
    m_kbB_Previous = false;
    m_kbA_Previous = false;
    m_kbEQUAL_Previous = false;
    m_kbMULTIPLY_Previous = false;
    m_kbPOWER_Previous = false;

    // Sixth adress block
    m_kbVAR_Previous = false;
    m_kbMINUS_Previous = false;
    m_kbPARCLOSE_Previous = false;
    m_kbDOT_Previous = false;
    m_kbPAROPEN_Previous = false;
    m_kb5_Previous = false;
    m_kbCATALOG_Previous = false;
    m_kbFRAC_Previous = false;
    m_kbDEL_Previous = false;
    m_kbSCRATCH_Previous = false;

    // Seventh adress block
    m_kbFLAG_Previous = false;
    m_kbPLUS_Previous = false;
    m_kbDOC_Previous = false;
    m_kb2_Previous = false;
    m_kbMENU_Previous = false;
    m_kb8_Previous = false;
    m_kbESC_Previous = false;
    m_kbTAB_Previous = false;

    // Eigth adress block
    m_kbSHIFT_Previous = false;
    m_kbCTRL_Previous = false;
    m_kbCOMMA_Previous = false;
}

bool KeyManager::InternalIsAnyKeyPressed()
{
#if  TARGET_NSPIRE == 1
    // We add all the bits corresponding to the key mapping in memory
    keysum = base[0] + base[1] + base[2] + base[3] + base[4] + base[5] + base[6] + base[7];

    // If there is no bit set to 1 AND On is not pressed (special address) then return false
    if (is_cx2 && (keysum==0) && ((specialON[0] & 256) != 0))
        return false;
    else if (!is_cx2 && (keysum==0) && ((specialON[0] & 16) != 0))
        return false;
    // Else at least one key is pressed and return true
    else return true;
#else

    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN)
    {
        return true;
    }
    else
    {
        return false;
    }

#endif // TARGET_NSPIRE
}

char KeyManager::InternalAsciiGet( void )
{
    InternalLogic();

    //start scrutinizing the keyboard
    // first we look at the letter keys
    if (keyevent && m_kbA && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'a';
    if (keyevent && m_kbA && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'A';
    if (keyevent && m_kbA && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbB && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'b';
    if (keyevent && m_kbB && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'B';
    if (keyevent && m_kbB && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbC && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'c';
    if (keyevent && m_kbC && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'C';
    if (keyevent && m_kbC && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is COPY shortcut

    if (keyevent && m_kbD && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'd';
    if (keyevent && m_kbD && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'D';
    if (keyevent && m_kbD && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbE && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'e';
    if (keyevent && m_kbE && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'E';
    if (keyevent && m_kbE && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbF && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'f';
    if (keyevent && m_kbF && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'F';
    if (keyevent && m_kbF && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbG && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'g';
    if (keyevent && m_kbG && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'G';
    if (keyevent && m_kbG && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbH && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'h';
    if (keyevent && m_kbH && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'H';
    if (keyevent && m_kbH && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbI && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'i';
    if (keyevent && m_kbI && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'I';
    if (keyevent && m_kbI && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbJ && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'j';
    if (keyevent && m_kbJ && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'J';
    if (keyevent && m_kbJ && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbK && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'k';
    if (keyevent && m_kbK && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'K';
    if (keyevent && m_kbK && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbL && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'l';
    if (keyevent && m_kbL && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'L';
    if (keyevent && m_kbL && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbM && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'm';
    if (keyevent && m_kbM && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'M';
    if (keyevent && m_kbM && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbN && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'n';
    if (keyevent && m_kbN && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'N';
    if (keyevent && m_kbN && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbO && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'o';
    if (keyevent && m_kbO && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'O';
    if (keyevent && m_kbO && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbP && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'p';
    if (keyevent && m_kbP && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'P';
    if (keyevent && m_kbP && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbQ && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'q';
    if (keyevent && m_kbQ && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'Q';
    if (keyevent && m_kbQ && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbR && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'r';
    if (keyevent && m_kbR && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'R';
    if (keyevent && m_kbR && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbS && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 's';
    if (keyevent && m_kbS && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'S';
    if (keyevent && m_kbS && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbT && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 't';
    if (keyevent && m_kbT && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'T';
    if (keyevent && m_kbT && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbU && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'u';
    if (keyevent && m_kbU && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'U';
    if (keyevent && m_kbU && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbV && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'v';
    if (keyevent && m_kbV && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'V';
    if (keyevent && m_kbV && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is PASTE shortcut

    if (keyevent && m_kbW && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'w';
    if (keyevent && m_kbW && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'W';
    if (keyevent && m_kbW && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbX && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'x';
    if (keyevent && m_kbX && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'X';
    if (keyevent && m_kbX && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is CUT shortcut

    if (keyevent && m_kbY && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'y';
    if (keyevent && m_kbY && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'Y';
    if (keyevent && m_kbY && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbZ && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return 'z';
    if (keyevent && m_kbZ && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return 'Z';
    if (keyevent && m_kbZ && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke


    //then the number keys

    if (keyevent && m_kb0 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '0';
    if (keyevent && m_kb0 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '0';
    if (keyevent && m_kb0 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke    /!\ this is SCREENSHOT shortcut

    if (keyevent && m_kb1 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '1';
    if (keyevent && m_kb1 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '1';
    if (keyevent && m_kb1 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb2 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '2';
    if (keyevent && m_kb2 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '2';
    if (keyevent && m_kb2 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb3 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '3';
    if (keyevent && m_kb3 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '3';
    if (keyevent && m_kb3 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb4 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '4';
    if (keyevent && m_kb4 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '4';
    if (keyevent && m_kb4 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb5 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '5';
    if (keyevent && m_kb5 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '5';
    if (keyevent && m_kb5 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb6 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '6';
    if (keyevent && m_kb6 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '6';
    if (keyevent && m_kb6 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb7 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '7';
    if (keyevent && m_kb7 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '7';
    if (keyevent && m_kb7 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb8 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '8';
    if (keyevent && m_kb8 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '8';
    if (keyevent && m_kb8 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kb9 && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '9';
    if (keyevent && m_kb9 && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '9';
    if (keyevent && m_kb9 && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke


    //then the symbols keys
    //(note that right now they are mapped as per nio_ascii_get, but this can be changed easily)

    if (keyevent && m_kbEX && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '#';
    if (keyevent && m_kbEX && (capsonmode || m_kbSHIFT) && !m_kbCTRL) {}; //nothing for this combination of keystroke
    if (keyevent && m_kbEX && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbPAROPEN && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '(';
    if (keyevent && m_kbPAROPEN && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '[';
    if (keyevent && m_kbPAROPEN && !(capsonmode || m_kbSHIFT) && m_kbCTRL) return '{';

    if (keyevent && m_kbPARCLOSE && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return ')';
    if (keyevent && m_kbPARCLOSE && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return ']';
    if (keyevent && m_kbPARCLOSE && !(capsonmode || m_kbSHIFT) && m_kbCTRL) return '}';

    if (keyevent && m_kbEQUAL && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '=';
    if (keyevent && m_kbEQUAL && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '|';
    if (keyevent && m_kbEQUAL && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbPOWER && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '^';
    if (keyevent && m_kbPOWER && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '\''; //nothing for this combination of keystroke
    if (keyevent && m_kbPOWER && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbEE && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '&';
    if (keyevent && m_kbEE && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '%';
    if (keyevent && m_kbEE && !(capsonmode || m_kbSHIFT) && m_kbCTRL) return '@';

    if (keyevent && m_kbCOMMA && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return ',';
    if (keyevent && m_kbCOMMA && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return ';';
    if (keyevent && m_kbCOMMA && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbDOT && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '.';
    if (keyevent && m_kbDOT && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return ':';
    if (keyevent && m_kbDOT && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke !!! BE CAREFULL : SCREENSHOT SHORTCUT

    if (keyevent && m_kbMINUSPAR && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '-';
    if (keyevent && m_kbMINUSPAR && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '_';
    if (keyevent && m_kbMINUSPAR && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbMULTIPLY && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '*';
    if (keyevent && m_kbMULTIPLY && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '\"';
    if (keyevent && m_kbMULTIPLY && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbDIV && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '/';
    if (keyevent && m_kbDIV && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '\\';
    if (keyevent && m_kbDIV && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbPLUS && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '+';
    if (keyevent && m_kbPLUS && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '>';
    if (keyevent && m_kbPLUS && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbMINUS && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '-';
    if (keyevent && m_kbMINUS && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '<';
    if (keyevent && m_kbMINUS && !(capsonmode || m_kbSHIFT) && m_kbCTRL) return '_';

    if (keyevent && m_kbENTER && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '\n';
    if (keyevent && m_kbENTER && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '~';
    if (keyevent && m_kbENTER && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbQUESTION && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return '?';
    if (keyevent && m_kbQUESTION && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '!';
    if (keyevent && m_kbQUESTION && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && m_kbSPACE && !capsonmode && !m_kbSHIFT && ! m_kbCTRL) return ' ';
    if (keyevent && m_kbSPACE && (capsonmode || m_kbSHIFT) && !m_kbCTRL) return '_';
    if (keyevent && m_kbSPACE && !(capsonmode || m_kbSHIFT) && m_kbCTRL) {}; //nothing for this combination of keystroke


    //and finally the special characters
    if (keyevent && m_kbRET) return '\n';
    if (keyevent && m_kbDEL) return '\b';
    if (keyevent && m_kbTAB) return '\t';

    return 0;
}
