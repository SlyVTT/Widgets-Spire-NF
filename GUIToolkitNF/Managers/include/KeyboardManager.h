#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <string>


class KeyboardManager
{
    public:
        KeyboardManager();
        virtual ~KeyboardManager();

        virtual void Logic( void );

       //This is a recode of LibNDLS nio_ascii_get() to correctly map the nSpire CX/CX-II keyboard
       virtual char AsciiGet( void );

       virtual void ResetState( void );

       virtual bool IsAnyKeyPressed( void );
       virtual bool IsAnyKeyEvent( void );

       virtual bool IsKeyPressEvent( void );
       virtual bool IsKeyReleaseEvent( void );
       virtual bool IsKeyArrowEvent( void );



    public:

        // First adress block
       bool kbRET = false;
       bool kbRET_Press_Event = false;
       bool kbRET_Release_Event = false;
       bool kbENTER = false;
       bool kbENTER_Press_Event = false;
       bool kbENTER_Release_Event = false;
       bool kbMINUSPAR = false;
       bool kbMINUSPAR_Press_Event = false;
       bool kbMINUSPAR_Release_Event = false;
       bool kbSPACE = false;
       bool kbSPACE_Press_Event = false;
       bool kbSPACE_Release_Event = false;
       bool kbZ = false;
       bool kbZ_Press_Event = false;
       bool kbZ_Release_Event = false;
       bool kbY = false;
       bool kbY_Press_Event = false;
       bool kbY_Release_Event = false;
       bool kb0 = false;
       bool kb0_Press_Event = false;
       bool kb0_Release_Event = false;
       bool kbQUESTION = false;
       bool kbQUESTION_Press_Event = false;
       bool kbQUESTION_Release_Event = false;
       bool kbON = false;
       bool kbON_Press_Event = false;
       bool kbON_Release_Event = false;

       // Second adress block
       bool kbX = false;
       bool kbX_Press_Event = false;
       bool kbX_Release_Event = false;
       bool kbW = false;
       bool kbW_Press_Event = false;
       bool kbW_Release_Event = false;
       bool kbV = false;
       bool kbV_Press_Event = false;
       bool kbV_Release_Event = false;
       bool kb3 = false;
       bool kb3_Press_Event = false;
       bool kb3_Release_Event = false;
       bool kbU = false;
       bool kbU_Press_Event = false;
       bool kbU_Release_Event = false;
       bool kbT = false;
       bool kbT_Press_Event = false;
       bool kbT_Release_Event = false;
       bool kbS = false;
       bool kbS_Press_Event = false;
       bool kbS_Release_Event = false;
       bool kb1 = false;
       bool kb1_Press_Event = false;
       bool kb1_Release_Event = false;
       bool kbPI = false;
       bool kbPI_Press_Event = false;
       bool kbPI_Release_Event = false;
       bool kbTRIG = false;
       bool kbTRIG_Press_Event = false;
       bool kbTRIG_Release_Event = false;
       bool kb10X = false;
       bool kb10X_Press_Event = false;
       bool kb10X_Release_Event = false;

       // Third adress block
       bool kbR = false;
       bool kbR_Press_Event = false;
       bool kbR_Release_Event = false;
       bool kbQ = false;
       bool kbQ_Press_Event = false;
       bool kbQ_Release_Event = false;
       bool kbP = false;
       bool kbP_Press_Event = false;
       bool kbP_Release_Event = false;
       bool kb6 = false;
       bool kb6_Press_Event = false;
       bool kb6_Release_Event = false;
       bool kbO = false;
       bool kbO_Press_Event = false;
       bool kbO_Release_Event = false;
       bool kbN = false;
       bool kbN_Press_Event = false;
       bool kbN_Release_Event = false;
       bool kbM = false;
       bool kbM_Press_Event = false;
       bool kbM_Release_Event = false;
       bool kb4 = false;
       bool kb4_Press_Event = false;
       bool kb4_Release_Event = false;
       bool kbEE = false;
       bool kbEE_Press_Event = false;
       bool kbEE_Release_Event = false;
       bool kbX2 = false;
       bool kbX2_Press_Event = false;
       bool kbX2_Release_Event = false;

       // Fourth adress block
       bool kbL = false;
       bool kbL_Press_Event = false;
       bool kbL_Release_Event = false;
       bool kbK = false;
       bool kbK_Press_Event = false;
       bool kbK_Release_Event = false;
       bool kbJ = false;
       bool kbJ_Press_Event = false;
       bool kbJ_Release_Event = false;
       bool kb9 = false;
       bool kb9_Press_Event = false;
       bool kb9_Release_Event = false;
       bool kbI = false;
       bool kbI_Press_Event = false;
       bool kbI_Release_Event = false;
       bool kbH = false;
       bool kbH_Press_Event = false;
       bool kbH_Release_Event = false;
       bool kbG = false;
       bool kbG_Press_Event = false;
       bool kbG_Release_Event = false;
       bool kb7 = false;
       bool kb7_Press_Event = false;
       bool kb7_Release_Event = false;
       bool kbDIV = false;
       bool kbDIV_Press_Event = false;
       bool kbDIV_Release_Event = false;
       bool kbEX = false;
       bool kbEX_Press_Event = false;
       bool kbEX_Release_Event = false;

       // Fifth adress block
       bool kbF = false;
       bool kbF_Press_Event = false;
       bool kbF_Release_Event = false;
       bool kbE = false;
       bool kbE_Press_Event = false;
       bool kbE_Release_Event = false;
       bool kbD = false;
       bool kbD_Press_Event = false;
       bool kbD_Release_Event = false;
       bool kbC = false;
       bool kbC_Press_Event = false;
       bool kbC_Release_Event = false;
       bool kbB = false;
       bool kbB_Press_Event = false;
       bool kbB_Release_Event = false;
       bool kbA = false;
       bool kbA_Press_Event = false;
       bool kbA_Release_Event = false;
       bool kbEQUAL = false;
       bool kbEQUAL_Press_Event = false;
       bool kbEQUAL_Release_Event = false;
       bool kbMULTIPLY = false;
       bool kbMULTIPLY_Press_Event = false;
       bool kbMULTIPLY_Release_Event = false;
       bool kbPOWER = false;
       bool kbPOWER_Press_Event = false;
       bool kbPOWER_Release_Event = false;

       // Sixth adress block
       bool kbVAR = false;
       bool kbVAR_Press_Event = false;
       bool kbVAR_Release_Event = false;
       bool kbMINUS = false;
       bool kbMINUS_Press_Event = false;
       bool kbMINUS_Release_Event = false;
       bool kbPARCLOSE = false;
       bool kbPARCLOSE_Press_Event = false;
       bool kbPARCLOSE_Release_Event = false;
       bool kbDOT = false;
       bool kbDOT_Press_Event = false;
       bool kbDOT_Release_Event = false;
       bool kbPAROPEN = false;
       bool kbPAROPEN_Press_Event = false;
       bool kbPAROPEN_Release_Event = false;
       bool kb5 = false;
       bool kb5_Press_Event = false;
       bool kb5_Release_Event = false;
       bool kbCATALOG = false;
       bool kbCATALOG_Press_Event = false;
       bool kbCATALOG_Release_Event = false;
       bool kbFRAC = false;
       bool kbFRAC_Press_Event = false;
       bool kbFRAC_Release_Event = false;
       bool kbDEL = false;
       bool kbDEL_Press_Event = false;
       bool kbDEL_Release_Event = false;
       bool kbSCRATCH = false;
       bool kbSCRATCH_Press_Event = false;
       bool kbSCRATCH_Release_Event = false;

       // Seventh adress block
       bool kbFLAG = false;
       bool kbFLAG_Press_Event = false;
       bool kbFLAG_Release_Event = false;
       bool kbPLUS = false;
       bool kbPLUS_Press_Event = false;
       bool kbPLUS_Release_Event = false;
       bool kbDOC = false;
       bool kbDOC_Press_Event = false;
       bool kbDOC_Release_Event = false;
       bool kb2 = false;
       bool kb2_Press_Event = false;
       bool kb2_Release_Event = false;
       bool kbMENU = false;
       bool kbMENU_Press_Event = false;
       bool kbMENU_Release_Event = false;
       bool kb8 = false;
       bool kb8_Press_Event = false;
       bool kb8_Release_Event = false;
       bool kbESC = false;
       bool kbESC_Press_Event = false;
       bool kbESC_Release_Event = false;
       bool kbTAB = false;
       bool kbTAB_Press_Event = false;
       bool kbTAB_Release_Event = false;

       // Eigth adress block
       bool kbSHIFT = false;
       bool kbSHIFT_Press_Event = false;
       bool kbSHIFT_Release_Event = false;
       bool kbCTRL = false;
       bool kbCTRL_Press_Event = false;
       bool kbCTRL_Release_Event = false;
       bool kbCOMMA = false;
       bool kbCOMMA_Press_Event = false;
       bool kbCOMMA_Release_Event = false;

       // Keys of the Touchpad
       bool kbUP = false;
       bool kbUP_Press_Event = false;
       bool kbUP_Release_Event = false;
       bool kbUPRIGHT = false;
       bool kbUPRIGHT_Press_Event = false;
       bool kbUPRIGHT_Release_Event = false;
       bool kbRIGHT = false;
       bool kbRIGHT_Press_Event = false;
       bool kbRIGHT_Release_Event = false;
       bool kbRIGHTDOWN = false;
       bool kbRIGHTDOWN_Press_Event = false;
       bool kbRIGHTDOWN_Release_Event = false;
       bool kbDOWN = false;
       bool kbDOWN_Press_Event = false;
       bool kbDOWN_Release_Event = false;
       bool kbDOWNLEFT = false;
       bool kbDOWNLEFT_Press_Event = false;
       bool kbDOWNLEFT_Release_Event = false;
       bool kbLEFT = false;
       bool kbLEFT_Press_Event = false;
       bool kbLEFT_Release_Event = false;
       bool kbLEFTUP = false;
       bool kbLEFTUP_Press_Event = false;
       bool kbLEFTUP_Release_Event = false;


    protected:

    private:

        // Following are all the internal variables needed by the status machinery

        // First adress block
       bool kbRET_Previous = false;
       bool kbENTER_Previous = false;
       bool kbMINUSPAR_Previous = false;
       bool kbSPACE_Previous = false;
       bool kbZ_Previous = false;
       bool kbY_Previous = false;
       bool kb0_Previous = false;
       bool kbQUESTION_Previous = false;
       bool kbON_Previous = false;

       // Second adress block
       bool kbX_Previous = false;
       bool kbW_Previous = false;
       bool kbV_Previous = false;
       bool kb3_Previous = false;
       bool kbU_Previous = false;
       bool kbT_Previous = false;
       bool kbS_Previous = false;
       bool kb1_Previous = false;
       bool kbPI_Previous = false;
       bool kbTRIG_Previous = false;
       bool kb10X_Previous = false;

       // Third adress block
       bool kbR_Previous = false;
       bool kbQ_Previous = false;
       bool kbP_Previous = false;
       bool kb6_Previous = false;
       bool kbO_Previous = false;
       bool kbN_Previous = false;
       bool kbM_Previous = false;
       bool kb4_Previous = false;
       bool kbEE_Previous = false;
       bool kbX2_Previous = false;

       // Fourth adress block
       bool kbL_Previous = false;
       bool kbK_Previous = false;
       bool kbJ_Previous = false;
       bool kb9_Previous = false;
       bool kbI_Previous = false;
       bool kbH_Previous = false;
       bool kbG_Previous = false;
       bool kb7_Previous = false;
       bool kbDIV_Previous = false;
       bool kbEX_Previous = false;

       // Fifth adress block
       bool kbF_Previous = false;
       bool kbE_Previous = false;
       bool kbD_Previous = false;
       bool kbC_Previous = false;
       bool kbB_Previous = false;
       bool kbA_Previous = false;
       bool kbEQUAL_Previous = false;
       bool kbMULTIPLY_Previous = false;
       bool kbPOWER_Previous = false;

       // Sixth adress block
       bool kbVAR_Previous = false;
       bool kbMINUS_Previous = false;
       bool kbPARCLOSE_Previous = false;
       bool kbDOT_Previous = false;
       bool kbPAROPEN_Previous = false;
       bool kb5_Previous = false;
       bool kbCATALOG_Previous = false;
       bool kbFRAC_Previous = false;
       bool kbDEL_Previous = false;
       bool kbSCRATCH_Previous = false;

       // Seventh adress block
       bool kbFLAG_Previous = false;
       bool kbPLUS_Previous = false;
       bool kbDOC_Previous = false;
       bool kb2_Previous = false;
       bool kbMENU_Previous = false;
       bool kb8_Previous = false;
       bool kbESC_Previous = false;
       bool kbTAB_Previous = false;

       // Eigth adress block
       bool kbSHIFT_Previous = false;
       bool kbCTRL_Previous = false;
       bool kbCOMMA_Previous = false;

       // Keys of the Touchpad
       bool kbUP_Previous = false;
       bool kbUPRIGHT_Previous = false;
       bool kbRIGHT_Previous = false;
       bool kbRIGHTDOWN_Previous = false;
       bool kbDOWN_Previous = false;
       bool kbDOWNLEFT_Previous = false;
       bool kbLEFT_Previous = false;
       bool kbLEFTUP_Previous = false;

       // The physical adresses of key into the memory (model dependant)
       unsigned short *base;
       unsigned short *specialON;

       // This is the content of the Clipboard
       std::string selection;


       bool keypressevent = false;
       bool keyreleaseevent = false;
       bool keyevent = false;
       bool keyevent_arrow = false;
       bool capsonmode = false;
};

#endif // KEYBOARDMANAGER_H
