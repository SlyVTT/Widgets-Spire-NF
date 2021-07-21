#include "KeyboardManager.h"

#include <libndls.h>



/// Constructor of the KeyboardManager class.
/// Defines the adresses to be scrutinized in the memory to access the status of the keys.
KeyboardManager::KeyboardManager()
{

    // The base adress is common for all the NSpire, CX and CX II
    base=(unsigned short *)0x900E0010;

    // the ON key is mapped differently for the CX and the CX II so we need to adress it by the correct adress
    if (is_cx2)
        specialON=(unsigned short *)0x90140810;
    else
        specialON=(unsigned short *)0x900B0028;
}


/// Destructor of the KeyboardManager class.
/// Nothing to be deallocated
KeyboardManager::~KeyboardManager()
{
    // Nothing to be done
}

/// Method that return true if at least one key is currently pressed and false otherwise
bool KeyboardManager::IsAnyKeyPressed()
{
    // We add all the bits corresponding to the key mapping in memory
    keysum = base[0] + base[1] + base[2] + base[3] + base[4] + base[5] + base[6] + base[7];

    // If there is no bit set to 1 AND On is not pressed (special address) then return false
    if (is_cx2 && (keysum==0) && ((specialON[0] & 256) != 0))
        return false;
    else if (!is_cx2 && (keysum==0) && ((specialON[0] & 16) != 0))
        return false;
    // Else at least one key is pressed and return true
    else return true;
}



char KeyboardManager::AsciiGet( void )
{
    this->Logic();

    //start scrutinizing the keyboard
    // first we look at the letter keys
    if (keyevent && kbA && !capsonmode && !kbSHIFT && ! kbCTRL) return 'a';
    if (keyevent && kbA && (capsonmode || kbSHIFT) && !kbCTRL) return 'A';
    if (keyevent && kbA && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbB && !capsonmode && !kbSHIFT && ! kbCTRL) return 'b';
    if (keyevent && kbB && (capsonmode || kbSHIFT) && !kbCTRL) return 'B';
    if (keyevent && kbB && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbC && !capsonmode && !kbSHIFT && ! kbCTRL) return 'c';
    if (keyevent && kbC && (capsonmode || kbSHIFT) && !kbCTRL) return 'C';
    if (keyevent && kbC && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is COPY shortcut

    if (keyevent && kbD && !capsonmode && !kbSHIFT && ! kbCTRL) return 'd';
    if (keyevent && kbD && (capsonmode || kbSHIFT) && !kbCTRL) return 'D';
    if (keyevent && kbD && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbE && !capsonmode && !kbSHIFT && ! kbCTRL) return 'e';
    if (keyevent && kbE && (capsonmode || kbSHIFT) && !kbCTRL) return 'E';
    if (keyevent && kbE && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbF && !capsonmode && !kbSHIFT && ! kbCTRL) return 'f';
    if (keyevent && kbF && (capsonmode || kbSHIFT) && !kbCTRL) return 'F';
    if (keyevent && kbF && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbG && !capsonmode && !kbSHIFT && ! kbCTRL) return 'g';
    if (keyevent && kbG && (capsonmode || kbSHIFT) && !kbCTRL) return 'G';
    if (keyevent && kbG && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbH && !capsonmode && !kbSHIFT && ! kbCTRL) return 'h';
    if (keyevent && kbH && (capsonmode || kbSHIFT) && !kbCTRL) return 'H';
    if (keyevent && kbH && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbI && !capsonmode && !kbSHIFT && ! kbCTRL) return 'i';
    if (keyevent && kbI && (capsonmode || kbSHIFT) && !kbCTRL) return 'I';
    if (keyevent && kbI && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbJ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'j';
    if (keyevent && kbJ && (capsonmode || kbSHIFT) && !kbCTRL) return 'J';
    if (keyevent && kbJ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbK && !capsonmode && !kbSHIFT && ! kbCTRL) return 'k';
    if (keyevent && kbK && (capsonmode || kbSHIFT) && !kbCTRL) return 'K';
    if (keyevent && kbK && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbL && !capsonmode && !kbSHIFT && ! kbCTRL) return 'l';
    if (keyevent && kbL && (capsonmode || kbSHIFT) && !kbCTRL) return 'L';
    if (keyevent && kbL && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbM && !capsonmode && !kbSHIFT && ! kbCTRL) return 'm';
    if (keyevent && kbM && (capsonmode || kbSHIFT) && !kbCTRL) return 'M';
    if (keyevent && kbM && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbN && !capsonmode && !kbSHIFT && ! kbCTRL) return 'n';
    if (keyevent && kbN && (capsonmode || kbSHIFT) && !kbCTRL) return 'N';
    if (keyevent && kbN && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbO && !capsonmode && !kbSHIFT && ! kbCTRL) return 'o';
    if (keyevent && kbO && (capsonmode || kbSHIFT) && !kbCTRL) return 'O';
    if (keyevent && kbO && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbP && !capsonmode && !kbSHIFT && ! kbCTRL) return 'p';
    if (keyevent && kbP && (capsonmode || kbSHIFT) && !kbCTRL) return 'P';
    if (keyevent && kbP && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbQ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'q';
    if (keyevent && kbQ && (capsonmode || kbSHIFT) && !kbCTRL) return 'Q';
    if (keyevent && kbQ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbR && !capsonmode && !kbSHIFT && ! kbCTRL) return 'r';
    if (keyevent && kbR && (capsonmode || kbSHIFT) && !kbCTRL) return 'R';
    if (keyevent && kbR && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbS && !capsonmode && !kbSHIFT && ! kbCTRL) return 's';
    if (keyevent && kbS && (capsonmode || kbSHIFT) && !kbCTRL) return 'S';
    if (keyevent && kbS && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbT && !capsonmode && !kbSHIFT && ! kbCTRL) return 't';
    if (keyevent && kbT && (capsonmode || kbSHIFT) && !kbCTRL) return 'T';
    if (keyevent && kbT && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbU && !capsonmode && !kbSHIFT && ! kbCTRL) return 'u';
    if (keyevent && kbU && (capsonmode || kbSHIFT) && !kbCTRL) return 'U';
    if (keyevent && kbU && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbV && !capsonmode && !kbSHIFT && ! kbCTRL) return 'v';
    if (keyevent && kbV && (capsonmode || kbSHIFT) && !kbCTRL) return 'V';
    if (keyevent && kbV && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is PASTE shortcut

    if (keyevent && kbW && !capsonmode && !kbSHIFT && ! kbCTRL) return 'w';
    if (keyevent && kbW && (capsonmode || kbSHIFT) && !kbCTRL) return 'W';
    if (keyevent && kbW && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbX && !capsonmode && !kbSHIFT && ! kbCTRL) return 'x';
    if (keyevent && kbX && (capsonmode || kbSHIFT) && !kbCTRL) return 'X';
    if (keyevent && kbX && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is CUT shortcut

    if (keyevent && kbY && !capsonmode && !kbSHIFT && ! kbCTRL) return 'y';
    if (keyevent && kbY && (capsonmode || kbSHIFT) && !kbCTRL) return 'Y';
    if (keyevent && kbY && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbZ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'z';
    if (keyevent && kbZ && (capsonmode || kbSHIFT) && !kbCTRL) return 'Z';
    if (keyevent && kbZ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


    //then the number keys

    if (keyevent && kb0 && !capsonmode && !kbSHIFT && ! kbCTRL) return '0';
    if (keyevent && kb0 && (capsonmode || kbSHIFT) && !kbCTRL) return '0';
    if (keyevent && kb0 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke    /!\ this is SCREENSHOT shortcut

    if (keyevent && kb1 && !capsonmode && !kbSHIFT && ! kbCTRL) return '1';
    if (keyevent && kb1 && (capsonmode || kbSHIFT) && !kbCTRL) return '1';
    if (keyevent && kb1 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb2 && !capsonmode && !kbSHIFT && ! kbCTRL) return '2';
    if (keyevent && kb2 && (capsonmode || kbSHIFT) && !kbCTRL) return '2';
    if (keyevent && kb2 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb3 && !capsonmode && !kbSHIFT && ! kbCTRL) return '3';
    if (keyevent && kb3 && (capsonmode || kbSHIFT) && !kbCTRL) return '3';
    if (keyevent && kb3 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb4 && !capsonmode && !kbSHIFT && ! kbCTRL) return '4';
    if (keyevent && kb4 && (capsonmode || kbSHIFT) && !kbCTRL) return '4';
    if (keyevent && kb4 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb5 && !capsonmode && !kbSHIFT && ! kbCTRL) return '5';
    if (keyevent && kb5 && (capsonmode || kbSHIFT) && !kbCTRL) return '5';
    if (keyevent && kb5 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb6 && !capsonmode && !kbSHIFT && ! kbCTRL) return '6';
    if (keyevent && kb6 && (capsonmode || kbSHIFT) && !kbCTRL) return '6';
    if (keyevent && kb6 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb7 && !capsonmode && !kbSHIFT && ! kbCTRL) return '7';
    if (keyevent && kb7 && (capsonmode || kbSHIFT) && !kbCTRL) return '7';
    if (keyevent && kb7 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb8 && !capsonmode && !kbSHIFT && ! kbCTRL) return '8';
    if (keyevent && kb8 && (capsonmode || kbSHIFT) && !kbCTRL) return '8';
    if (keyevent && kb8 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kb9 && !capsonmode && !kbSHIFT && ! kbCTRL) return '9';
    if (keyevent && kb9 && (capsonmode || kbSHIFT) && !kbCTRL) return '9';
    if (keyevent && kb9 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


    //then the symbols keys
    //(note that right now they are mapped as per nio_ascii_get, but this can be changed easily)

    if (keyevent && kbEX && !capsonmode && !kbSHIFT && ! kbCTRL) return '#';
    if (keyevent && kbEX && (capsonmode || kbSHIFT) && !kbCTRL) {}; //nothing for this combination of keystroke
    if (keyevent && kbEX && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbPAROPEN && !capsonmode && !kbSHIFT && ! kbCTRL) return '(';
    if (keyevent && kbPAROPEN && (capsonmode || kbSHIFT) && !kbCTRL) return '[';
    if (keyevent && kbPAROPEN && !(capsonmode || kbSHIFT) && kbCTRL) return '{';

    if (keyevent && kbPARCLOSE && !capsonmode && !kbSHIFT && ! kbCTRL) return ')';
    if (keyevent && kbPARCLOSE && (capsonmode || kbSHIFT) && !kbCTRL) return ']';
    if (keyevent && kbPARCLOSE && !(capsonmode || kbSHIFT) && kbCTRL) return '}';

    if (keyevent && kbEQUAL && !capsonmode && !kbSHIFT && ! kbCTRL) return '=';
    if (keyevent && kbEQUAL && (capsonmode || kbSHIFT) && !kbCTRL) return '|';
    if (keyevent && kbEQUAL && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbPOWER && !capsonmode && !kbSHIFT && ! kbCTRL) return '^';
    if (keyevent && kbPOWER && (capsonmode || kbSHIFT) && !kbCTRL) return '\''; //nothing for this combination of keystroke
    if (keyevent && kbPOWER && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbEE && !capsonmode && !kbSHIFT && ! kbCTRL) return '&';
    if (keyevent && kbEE && (capsonmode || kbSHIFT) && !kbCTRL) return '%';
    if (keyevent && kbEE && !(capsonmode || kbSHIFT) && kbCTRL) return '@';

    if (keyevent && kbCOMMA && !capsonmode && !kbSHIFT && ! kbCTRL) return ',';
    if (keyevent && kbCOMMA && (capsonmode || kbSHIFT) && !kbCTRL) return ';';
    if (keyevent && kbCOMMA && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbDOT && !capsonmode && !kbSHIFT && ! kbCTRL) return '.';
    if (keyevent && kbDOT && (capsonmode || kbSHIFT) && !kbCTRL) return ':';
    if (keyevent && kbDOT && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke !!! BE CAREFULL : SCREENSHOT SHORTCUT

    if (keyevent && kbMINUSPAR && !capsonmode && !kbSHIFT && ! kbCTRL) return '-';
    if (keyevent && kbMINUSPAR && (capsonmode || kbSHIFT) && !kbCTRL) return '_';
    if (keyevent && kbMINUSPAR && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbMULTIPLY && !capsonmode && !kbSHIFT && ! kbCTRL) return '*';
    if (keyevent && kbMULTIPLY && (capsonmode || kbSHIFT) && !kbCTRL) return '\"';
    if (keyevent && kbMULTIPLY && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbDIV && !capsonmode && !kbSHIFT && ! kbCTRL) return '/';
    if (keyevent && kbDIV && (capsonmode || kbSHIFT) && !kbCTRL) return '\\';
    if (keyevent && kbDIV && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbPLUS && !capsonmode && !kbSHIFT && ! kbCTRL) return '+';
    if (keyevent && kbPLUS && (capsonmode || kbSHIFT) && !kbCTRL) return '>';
    if (keyevent && kbPLUS && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbMINUS && !capsonmode && !kbSHIFT && ! kbCTRL) return '-';
    if (keyevent && kbMINUS && (capsonmode || kbSHIFT) && !kbCTRL) return '<';
    if (keyevent && kbMINUS && !(capsonmode || kbSHIFT) && kbCTRL) return '_';

    if (keyevent && kbENTER && !capsonmode && !kbSHIFT && ! kbCTRL) return '\n';
    if (keyevent && kbENTER && (capsonmode || kbSHIFT) && !kbCTRL) return '~';
    if (keyevent && kbENTER && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbQUESTION && !capsonmode && !kbSHIFT && ! kbCTRL) return '?';
    if (keyevent && kbQUESTION && (capsonmode || kbSHIFT) && !kbCTRL) return '!';
    if (keyevent && kbQUESTION && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

    if (keyevent && kbSPACE && !capsonmode && !kbSHIFT && ! kbCTRL) return ' ';
    if (keyevent && kbSPACE && (capsonmode || kbSHIFT) && !kbCTRL) return '_';
    if (keyevent && kbSPACE && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


    //and finally the special characters
    if (keyevent && kbRET) return '\n';
    if (keyevent && kbDEL) return '\b';
    if (keyevent && kbTAB) return '\t';

    return 0;
}


void KeyboardManager::ResetState( void )
{
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
}


bool KeyboardManager::IsAnyKeyEvent( void )
{
    return keyevent;
}

bool KeyboardManager::IsKeyPressEvent( void )
{
    return keypressevent;
}

bool KeyboardManager::IsKeyReleaseEvent( void )
{
    return keyreleaseevent;
}

bool KeyboardManager::IsKeyArrowEvent( void )
{
    return keyevent_arrow;
}


void KeyboardManager::SetSelection( std::string select )
{
    selection = select;
}

std::string KeyboardManager::GetSelection( void )
{
    return selection;
}

void KeyboardManager::FlushSelection( void )
{
    selection.clear();
}


void KeyboardManager::Logic( void )
{

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


    kbON_Previous =  kbON;
    if (is_cx2)
    {
        kbON = ((specialON[0] & 256) == 0 ) ? true : false;
    }
    else
    {
        kbON = ((specialON[0] & 16) == 0 ) ? true : false;
    }
    kbON_Press_Event = (!kbON_Previous && kbON) ? true : false;
    kbON_Release_Event = (kbON_Previous && !kbON) ? true : false;


    // Mapping of the very first adress, corresponding to the first unsigned short at base (or base[0]) adress
    temp = base[0];
    {
        kbRET_Previous =  kbRET;
        kbRET = (temp  & 1) ? true : false;
        kbRET_Press_Event = (!kbRET_Previous && kbRET) ? true : false;
        kbRET_Release_Event = (kbRET_Previous && !kbRET) ? true : false;

        kbENTER_Previous =  kbENTER;
        kbENTER = (temp  & 2) ? true : false;
        kbENTER_Press_Event = (!kbENTER_Previous && kbENTER) ? true : false;
        kbENTER_Release_Event = (kbENTER_Previous && !kbENTER) ? true : false;

        // bit #2 is not assigned to a key

        kbMINUSPAR_Previous =  kbMINUSPAR;
        kbMINUSPAR = (temp  & 8) ? true : false;
        kbMINUSPAR_Press_Event = (!kbMINUSPAR_Previous && kbMINUSPAR) ? true : false;
        kbMINUSPAR_Release_Event = (kbMINUSPAR_Previous && !kbMINUSPAR) ? true : false;

        kbSPACE_Previous =  kbSPACE;
        kbSPACE = (temp  & 16) ? true : false;
        kbSPACE_Press_Event = (!kbSPACE_Previous && kbSPACE) ? true : false;
        kbSPACE_Release_Event = (kbSPACE_Previous && !kbSPACE) ? true : false;

        kbZ_Previous =  kbZ;
        kbZ = (temp  & 32) ? true : false;
        kbZ_Press_Event = (!kbZ_Previous && kbZ) ? true : false;
        kbZ_Release_Event = (kbZ_Previous && !kbZ) ? true : false;

        kbY_Previous =  kbY;
        kbY = (temp  & 64) ? true : false;
        kbY_Press_Event = (!kbY_Previous && kbY) ? true : false;
        kbY_Release_Event = (kbY_Previous && !kbY) ? true : false;

        kb0_Previous =  kb0;
        kb0 = (temp  & 128) ? true : false;
        kb0_Press_Event = (!kb0_Previous && kb0) ? true : false;
        kb0_Release_Event = (kb0_Previous && !kb0) ? true : false;

        kbQUESTION_Previous =  kbQUESTION;
        kbQUESTION = (temp  & 256) ? true : false;
        kbQUESTION_Press_Event = (!kbQUESTION_Previous && kbQUESTION) ? true : false;
        kbQUESTION_Release_Event = (kbQUESTION_Previous && !kbQUESTION) ? true : false;

        // bit #9 is not assigned to a key

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+1 (or base[1]) adress
    temp = base[1];
    {
        kbX_Previous =  kbX;
        kbX = (temp  & 1) ? true : false;
        kbX_Press_Event = (!kbX_Previous && kbX) ? true : false;
        kbX_Release_Event = (kbX_Previous && !kbX) ? true : false;

        kbW_Previous =  kbW;
        kbW = (temp  & 2) ? true : false;
        kbW_Press_Event = (!kbW_Previous && kbW) ? true : false;
        kbW_Release_Event = (kbW_Previous && !kbW) ? true : false;

        kbV_Previous =  kbV;
        kbV = (temp  & 4) ? true : false;
        kbV_Press_Event = (!kbV_Previous && kbV) ? true : false;
        kbV_Release_Event = (kbV_Previous && !kbV) ? true : false;

        kb3_Previous =  kb3;
        kb3 = (temp  & 8) ? true : false;
        kb3_Press_Event = (!kb3_Previous && kb3) ? true : false;
        kb3_Release_Event = (kb3_Previous && !kb3) ? true : false;

        kbU_Previous =  kbU;
        kbU = (temp  & 16) ? true : false;
        kbU_Press_Event = (!kbU_Previous && kbU) ? true : false;
        kbU_Release_Event = (kbU_Previous && !kbU) ? true : false;

        kbT_Previous =  kbT;
        kbT = (temp  & 32) ? true : false;
        kbT_Press_Event = (!kbT_Previous && kbT) ? true : false;
        kbT_Release_Event = (kbT_Previous && !kbT) ? true : false;

        kbS_Previous =  kbS;
        kbS = (temp  & 64) ? true : false;
        kbS_Press_Event = (!kbS_Previous && kbS) ? true : false;
        kbS_Release_Event = (kbS_Previous && !kbS) ? true : false;

        kb1_Previous =  kb1;
        kb1 = (temp  & 128) ? true : false;
        kb1_Press_Event = (!kb1_Previous && kb1) ? true : false;
        kb1_Release_Event = (kb1_Previous && !kb1) ? true : false;

        kbPI_Previous =  kbPI;
        kbPI = (temp  & 256) ? true : false;
        kbPI_Press_Event = (!kbPI_Previous && kbPI) ? true : false;
        kbPI_Release_Event = (kbPI_Previous && !kbPI) ? true : false;

        kbTRIG_Previous =  kbTRIG;
        kbTRIG = (temp  & 512) ? true : false;
        kbTRIG_Press_Event = (!kbTRIG_Previous && kbTRIG) ? true : false;
        kbTRIG_Release_Event = (kbTRIG_Previous && !kbTRIG) ? true : false;

        kb10X_Previous =  kb10X;
        kb10X = (temp  & 1024) ? true : false;
        kb10X_Press_Event = (!kb10X_Previous && kb10X) ? true : false;
        kb10X_Release_Event = (kb10X_Previous && !kb10X) ? true : false;
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+2 (or base[2]) adress
    temp = base[2];
    {
        kbR_Previous =  kbR;
        kbR = (temp  & 1) ? true : false;
        kbR_Press_Event = (!kbR_Previous && kbR) ? true : false;
        kbR_Release_Event = (kbR_Previous && !kbR) ? true : false;

        kbQ_Previous =  kbQ;
        kbQ = (temp  & 2) ? true : false;
        kbQ_Press_Event = (!kbQ_Previous && kbQ) ? true : false;
        kbQ_Release_Event = (kbQ_Previous && !kbQ) ? true : false;

        kbP_Previous =  kbP;
        kbP = (temp  & 4) ? true : false;
        kbP_Press_Event = (!kbP_Previous && kbP) ? true : false;
        kbP_Release_Event = (kbP_Previous && !kbP) ? true : false;

        kb6_Previous =  kb6;
        kb6 = (temp  & 8) ? true : false;
        kb6_Press_Event = (!kb6_Previous && kb6) ? true : false;
        kb6_Release_Event = (kb6_Previous && !kb6) ? true : false;

        kbO_Previous =  kbO;
        kbO = (temp  & 16) ? true : false;
        kbO_Press_Event = (!kbO_Previous && kbO) ? true : false;
        kbO_Release_Event = (kbO_Previous && !kbO) ? true : false;

        kbN_Previous =  kbN;
        kbN = (temp  & 32) ? true : false;
        kbN_Press_Event = (!kbN_Previous && kbN) ? true : false;
        kbN_Release_Event = (kbN_Previous && !kbN) ? true : false;

        kbM_Previous =  kbM;
        kbM = (temp  & 64) ? true : false;
        kbM_Press_Event = (!kbM_Previous && kbM) ? true : false;
        kbM_Release_Event = (kbM_Previous && !kbM) ? true : false;

        kb4_Previous =  kb4;
        kb4 = (temp  & 128) ? true : false;
        kb4_Press_Event = (!kb4_Previous && kb4) ? true : false;
        kb4_Release_Event = (kb4_Previous && !kb4) ? true : false;

        kbEE_Previous =  kbEE;
        kbEE = (temp  & 256) ? true : false;
        kbEE_Press_Event = (!kbEE_Previous && kbEE) ? true : false;
        kbEE_Release_Event = (kbEE_Previous && !kbEE) ? true : false;

        kbX2_Previous =  kbX2;
        kbX2 = (temp  & 512) ? true : false;
        kbX2_Press_Event = (!kbX2_Previous && kbX2) ? true : false;
        kbX2_Release_Event = (kbX2_Previous && !kbX2) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+3 (or base[3]) adress
    temp = base[3];
    {
        kbL_Previous =  kbL;
        kbL = (temp  & 1) ? true : false;
        kbL_Press_Event = (!kbL_Previous && kbL) ? true : false;
        kbL_Release_Event = (kbL_Previous && !kbL) ? true : false;

        kbK_Previous =  kbK;
        kbK = (temp  & 2) ? true : false;
        kbK_Press_Event = (!kbK_Previous && kbK) ? true : false;
        kbK_Release_Event = (kbK_Previous && !kbK) ? true : false;

        kbJ_Previous =  kbJ;
        kbJ = (temp  & 4) ? true : false;
        kbJ_Press_Event = (!kbJ_Previous && kbJ) ? true : false;
        kbJ_Release_Event = (kbJ_Previous && !kbJ) ? true : false;

        kb9_Previous =  kb9;
        kb9 = (temp  & 8) ? true : false;
        kb9_Press_Event = (!kb9_Previous && kb9) ? true : false;
        kb9_Release_Event = (kb9_Previous && !kb9) ? true : false;

        kbI_Previous =  kbI;
        kbI = (temp  & 16) ? true : false;
        kbI_Press_Event = (!kbI_Previous && kbI) ? true : false;
        kbI_Release_Event = (kbI_Previous && !kbI) ? true : false;

        kbH_Previous =  kbH;
        kbH = (temp  & 32) ? true : false;
        kbH_Press_Event = (!kbH_Previous && kbH) ? true : false;
        kbH_Release_Event = (kbH_Previous && !kbH) ? true : false;

        kbG_Previous =  kbG;
        kbG = (temp  & 64) ? true : false;
        kbG_Press_Event = (!kbG_Previous && kbG) ? true : false;
        kbG_Release_Event = (kbG_Previous && !kbG) ? true : false;

        kb7_Previous =  kb7;
        kb7 = (temp  & 128) ? true : false;
        kb7_Press_Event = (!kb7_Previous && kb7) ? true : false;
        kb7_Release_Event = (kb7_Previous && !kb7) ? true : false;

        kbDIV_Previous =  kbDIV;
        kbDIV = (temp  & 256) ? true : false;
        kbDIV_Press_Event = (!kbDIV_Previous && kbDIV) ? true : false;
        kbDIV_Release_Event = (kbDIV_Previous && !kbDIV) ? true : false;

        kbEX_Previous =  kbEX;
        kbEX = (temp  & 512) ? true : false;
        kbEX_Press_Event = (!kbEX_Previous && kbEX) ? true : false;
        kbEX_Release_Event = (kbEX_Previous && !kbEX) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+4 (or base[4]) adress
    temp = base[4];
    {
        kbF_Previous =  kbF;
        kbF = (temp  & 1) ? true : false;
        kbF_Press_Event = (!kbF_Previous && kbF) ? true : false;
        kbF_Release_Event = (kbF_Previous && !kbF) ? true : false;

        kbE_Previous =  kbE;
        kbE = (temp  & 2) ? true : false;
        kbE_Press_Event = (!kbE_Previous && kbE) ? true : false;
        kbE_Release_Event = (kbE_Previous && !kbE) ? true : false;

        kbD_Previous =  kbD;
        kbD = (temp  & 4) ? true : false;
        kbD_Press_Event = (!kbD_Previous && kbD) ? true : false;
        kbD_Release_Event = (kbD_Previous && !kbD) ? true : false;

        // bit #3 is not assigned to a key

        kbC_Previous =  kbC;
        kbC = (temp  & 16) ? true : false;
        kbC_Press_Event = (!kbC_Previous && kbC) ? true : false;
        kbC_Release_Event = (kbC_Previous && !kbC) ? true : false;

        kbB_Previous =  kbB;
        kbB = (temp  & 32) ? true : false;
        kbB_Press_Event = (!kbB_Previous && kbB) ? true : false;
        kbB_Release_Event = (kbB_Previous && !kbB) ? true : false;

        kbA_Previous =  kbA;
        kbA = (temp  & 64) ? true : false;
        kbA_Press_Event = (!kbA_Previous && kbA) ? true : false;
        kbA_Release_Event = (kbA_Previous && !kbA) ? true : false;

        kbEQUAL_Previous =  kbEQUAL;
        kbEQUAL = (temp  & 128) ? true : false;
        kbEQUAL_Press_Event = (!kbEQUAL_Previous && kbEQUAL) ? true : false;
        kbEQUAL_Release_Event = (kbEQUAL_Previous && !kbEQUAL) ? true : false;

        kbMULTIPLY_Previous =  kbMULTIPLY;
        kbMULTIPLY = (temp  & 256) ? true : false;
        kbMULTIPLY_Press_Event = (!kbMULTIPLY_Previous && kbMULTIPLY) ? true : false;
        kbMULTIPLY_Release_Event = (kbMULTIPLY_Previous && !kbMULTIPLY) ? true : false;

        kbPOWER_Previous =  kbPOWER;
        kbPOWER = (temp  & 512) ? true : false;
        kbPOWER_Press_Event = (!kbPOWER_Previous && kbPOWER) ? true : false;
        kbPOWER_Release_Event = (kbPOWER_Previous && !kbPOWER) ? true : false;

        // bit #10 is not assigned to a key
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+5 (or base[5]) adress
    temp = base[5];
    {
        // bit #0 is not assigned to a key

        kbVAR_Previous =  kbVAR;
        kbVAR = (temp  & 2) ? true : false;
        kbVAR_Press_Event = (!kbVAR_Previous && kbVAR) ? true : false;
        kbVAR_Release_Event = (kbVAR_Previous && !kbVAR) ? true : false;

        kbMINUS_Previous =  kbMINUS;
        kbMINUS = (temp  & 4) ? true : false;
        kbMINUS_Press_Event = (!kbMINUS_Previous && kbMINUS) ? true : false;
        kbMINUS_Release_Event = (kbMINUS_Previous && !kbMINUS) ? true : false;

        kbPARCLOSE_Previous =  kbPARCLOSE;
        kbPARCLOSE = (temp  & 8) ? true : false;
        kbPARCLOSE_Press_Event = (!kbPARCLOSE_Previous && kbPARCLOSE) ? true : false;
        kbPARCLOSE_Release_Event = (kbPARCLOSE_Previous && !kbPARCLOSE) ? true : false;

        kbDOT_Previous =  kbDOT;
        kbDOT = (temp  & 16) ? true : false;
        kbDOT_Press_Event = (!kbDOT_Previous && kbDOT) ? true : false;
        kbDOT_Release_Event = (kbDOT_Previous && !kbDOT) ? true : false;

        kbPAROPEN_Previous =  kbPAROPEN;
        kbPAROPEN = (temp  & 32) ? true : false;
        kbPAROPEN_Press_Event = (!kbPAROPEN_Previous && kbPAROPEN) ? true : false;
        kbPAROPEN_Release_Event = (kbPAROPEN_Previous && !kbPAROPEN) ? true : false;

        kb5_Previous =  kb5;
        kb5 = (temp  & 64) ? true : false;
        kb5_Press_Event = (!kb5_Previous && kb5) ? true : false;
        kb5_Release_Event = (kb5_Previous && !kb5) ? true : false;

        kbCATALOG_Previous =  kbCATALOG;
        kbCATALOG = (temp  & 128) ? true : false;
        kbCATALOG_Press_Event = (!kbCATALOG_Previous && kbCATALOG) ? true : false;
        kbCATALOG_Release_Event = (kbCATALOG_Previous && !kbCATALOG) ? true : false;

        kbFRAC_Previous =  kbFRAC;
        kbFRAC = (temp  & 256) ? true : false;
        kbFRAC_Press_Event = (!kbFRAC_Previous && kbFRAC) ? true : false;
        kbFRAC_Release_Event = (kbFRAC_Previous && !kbFRAC) ? true : false;

        kbDEL_Previous =  kbDEL;
        kbDEL = (temp  & 512) ? true : false;
        kbDEL_Press_Event = (!kbDEL_Previous && kbDEL) ? true : false;
        kbDEL_Release_Event = (kbDEL_Previous && !kbDEL) ? true : false;

        kbSCRATCH_Previous =  kbSCRATCH;
        kbSCRATCH = (temp  & 1024) ? true : false;
        kbSCRATCH_Press_Event = (!kbSCRATCH_Previous && kbSCRATCH) ? true : false;
        kbSCRATCH_Release_Event = (kbSCRATCH_Previous && !kbSCRATCH) ? true : false;
    }

    // Mapping of the following adress, corresponding to the first unsigned short at base+6 (or base[6]) adress
    temp = base[6];
    {
        kbFLAG_Previous =  kbFLAG;
        kbFLAG = (temp  & 1) ? true : false;
        kbFLAG_Press_Event = (!kbFLAG_Previous && kbFLAG) ? true : false;
        kbFLAG_Release_Event = (kbFLAG_Previous && !kbFLAG) ? true : false;

        // bit #1 is not assigned to a key

        kbPLUS_Previous =  kbPLUS;
        kbPLUS = (temp  & 4) ? true : false;
        kbPLUS_Press_Event = (!kbPLUS_Previous && kbPLUS) ? true : false;
        kbPLUS_Release_Event = (kbPLUS_Previous && !kbPLUS) ? true : false;

        kbDOC_Previous =  kbDOC;
        kbDOC = (temp  & 2) ? true : false;
        kbDOC_Press_Event = (!kbDOC_Previous && kbDOC) ? true : false;
        kbDOC_Release_Event = (kbDOC_Previous && !kbDOC) ? true : false;

        kb2_Previous =  kb2;
        kb2 = (temp  & 16) ? true : false;
        kb2_Press_Event = (!kb2_Previous && kb2) ? true : false;
        kb2_Release_Event = (kb2_Previous && !kb2) ? true : false;

        kbMENU_Previous =  kbMENU;
        kbMENU = (temp  & 32) ? true : false;
        kbMENU_Press_Event = (!kbMENU_Previous && kbMENU) ? true : false;
        kbMENU_Release_Event = (kbMENU_Previous && !kbMENU) ? true : false;

        kb8_Previous =  kb8;
        kb8 = (temp  & 64) ? true : false;
        kb8_Press_Event = (!kb8_Previous && kb8) ? true : false;
        kb8_Release_Event = (kb8_Previous && !kb8) ? true : false;

        kbESC_Previous =  kbESC;
        kbESC = (temp  & 128) ? true : false;
        kbESC_Press_Event = (!kbESC_Previous && kbESC) ? true : false;
        kbESC_Release_Event = (kbESC_Previous && !kbESC) ? true : false;

        // bit #8 is not assigned to a key

        kbTAB_Previous =  kbTAB;
        kbTAB = (temp  & 512) ? true : false;
        kbTAB_Press_Event = (!kbTAB_Previous && kbTAB) ? true : false;
        kbTAB_Release_Event = (kbTAB_Previous && !kbTAB) ? true : false;

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

        kbSHIFT_Previous =  kbSHIFT;
        kbSHIFT = (temp  & 256) ? true : false;
        kbSHIFT_Press_Event = (!kbSHIFT_Previous && kbSHIFT) ? true : false;
        kbSHIFT_Release_Event = (kbSHIFT_Previous && !kbSHIFT) ? true : false;

        kbCTRL_Previous =  kbCTRL;
        kbCTRL = (temp  & 512) ? true : false;
        kbCTRL_Press_Event = (!kbCTRL_Previous && kbCTRL) ? true : false;
        kbCTRL_Release_Event = (kbCTRL_Previous && !kbCTRL) ? true : false;

        kbCOMMA_Previous =  kbCOMMA;
        kbCOMMA = (temp  & 1024) ? true : false;
        kbCOMMA_Press_Event = (!kbCOMMA_Previous && kbCOMMA) ? true : false;
        kbCOMMA_Release_Event = (kbCOMMA_Previous && !kbCOMMA) ? true : false;
    }

    keyevent_arrow = false;

    if (isKeyPressed( KEY_NSPIRE_UP ))
    {
        keyevent_arrow = true;
        kbUP = true;
    }
    else
    {
        kbUP = false;
    }

    if (isKeyPressed( KEY_NSPIRE_UPRIGHT ))
    {
        keyevent_arrow = true;
        kbUPRIGHT = true;
    }
    else
    {
        kbUPRIGHT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_RIGHT ))
    {
        keyevent_arrow = true;
        kbRIGHT = true;
    }
    else
    {
        kbRIGHT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_RIGHTDOWN ))
    {
        keyevent_arrow = true;
        kbRIGHTDOWN = true;
    }
    else
    {
        kbRIGHTDOWN = false;
    }

    if (isKeyPressed( KEY_NSPIRE_DOWN ))
    {
        keyevent_arrow = true;
        kbDOWN = true;
    }
    else
    {
        kbDOWN = false;
    }

    if (isKeyPressed( KEY_NSPIRE_DOWNLEFT ))
    {
        keyevent_arrow = true;
        kbDOWNLEFT = true;
    }
    else
    {
        kbDOWNLEFT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_LEFT ))
    {
        keyevent_arrow = true;
        kbLEFT = true;
    }
    else
    {
        kbLEFT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_LEFTUP ))
    {
        keyevent_arrow = true;
        kbLEFTUP = true;
    }
    else
    {
        kbLEFTUP = false;
    }


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
        if (!capsonmode && kbCTRL && kbSHIFT) capsonmode=true;
        //if capital mode is on and SHIFT is pressed without CTRL --> we switch back to normal mode
        else if (capsonmode && !kbCTRL && kbSHIFT) capsonmode = false;
        //if capital mode is on and CTRL is pressed without SHIFT --> we switch back to normal mode
        else if (capsonmode && kbCTRL && !kbSHIFT) capsonmode = false;
    }



}
