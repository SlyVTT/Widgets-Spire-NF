#include "FontEngine.hpp"

#include "../Renderers/ScreenRenderer.hpp"

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
*/

FontEngine::FontEngine()
{
    LoadFontFromFile( "/documents/Widget/Fonts/THIN.WFE.tns" );
    LoadFontFromFile( "/documents/Widget/Fonts/VGA.WFE.tns" );
    LoadFontFromFile( "/documents/Widget/Fonts/SPACE.WFE.tns" );
    LoadFontFromFile( "/documents/Widget/Fonts/TINY.WFE.tns" );
    LoadFontFromFile( "/documents/Widget/Fonts/STANDARD.WFE.tns" );
    LoadFontFromFile( "/documents/Widget/Fonts/FANTASY.WFE.tns" );
    SetCurrentFont( THIN_FONT );
    vspacing = 3;
    hspacing = -1;
    currentmodifiertypo = Normal;  // set text as normal
    currentmodifierunder = NoUnder; // No underlining
    currentmodifierstrike = NoStrike; // No striking
}

FontEngine::~FontEngine()
{
    //dtor
    for (auto& c : FontCollection )
    {
        for(auto& d : c->Font)
        {
            free( d->CharData );
        }
        delete c;
    }

    FontCollection.clear();
}

FontEngine::FontData* FontEngine::LoadFontFromFilePointer( std::string filename )
{

    FILE* pFile;
    pFile = fopen (filename.c_str(), "r");
    if (pFile!=NULL)
    {
        //bool flag = true;
        char line[20];
        //int value=0;
        int width, height, temp;
        //char p0[2], p1[2], p2[2], p3[2], p4[2], p5[2], p6[2], p7[2];
        char valstr[10];

        FontData *tempFont = new FontData;

        {
            fscanf( pFile, "%s", line );    // Should read "Name"
            fscanf( pFile, "%s", tempFont->FontName );

            fscanf( pFile, "%s", line );    // Should read "Width"
            fscanf( pFile, "%d", &width );

            fscanf( pFile, "%s", line );    // Should read "Height"
            fscanf( pFile, "%d", &height );

            fscanf( pFile, "%s", line );    // Should read "CharNumber"
            fscanf( pFile, "%d", &temp );
            tempFont->NumberChar = temp;

            fscanf( pFile, "%s", line );    // Should read "Data"

            for (int j = 0; j<tempFont->NumberChar; j++)
            {
                FontChar *tempChar = new FontChar;
                tempChar->CharWidth = width;
                tempChar->CharHeight = height;

                tempChar->CharData = (unsigned short *) malloc( height * sizeof( unsigned short ) );

                for (int i = 0; i < height; i++)
                {
                    // we read the hexadecimal value in the file
                    fscanf( pFile, "%s", valstr );

                    // we check how many characters has the Hexa value (F->1; FF->2, FFF->3, FFFF->4) (max is 4 bytes)
                    int length = strlen( valstr );
                    int nbvalue=0;
                    char digit;

                    for(int k = 0; k<length; k++)
                    {
                        digit=valstr[ k ];
                        int digitint=0;
                        switch(digit)
                        {
                        case '0' :
                            digitint=0;
                            break;
                        case '1' :
                            digitint=1;
                            break;
                        case '2' :
                            digitint=2;
                            break;
                        case '3' :
                            digitint=3;
                            break;

                        case '4' :
                            digitint=4;
                            break;
                        case '5' :
                            digitint=5;
                            break;
                        case '6' :
                            digitint=6;
                            break;
                        case '7' :
                            digitint=7;
                            break;

                        case '8' :
                            digitint=8;
                            break;
                        case '9' :
                            digitint=9;
                            break;
                        case 'A' :
                            digitint=10;
                            break;
                        case 'B' :
                            digitint=11;
                            break;

                        case 'C' :
                            digitint=12;
                            break;
                        case 'D' :
                            digitint=13;
                            break;
                        case 'E' :
                            digitint=14;
                            break;
                        case 'F' :
                            digitint=15;
                            break;
                        }

                        nbvalue += (digitint << ((length-k-1)*4));
                    }

                    tempChar->CharData[i] = nbvalue;

                }

                tempFont->Font.push_back( tempChar );
            }
        }

        fclose(pFile);

        return tempFont;
    }

    return nullptr;

}

void FontEngine::LoadFontFromFile( std::string filename )
{

    FILE* pFile;
    pFile = fopen (filename.c_str(),"r");
    if (pFile!=NULL)
    {
        //bool flag = true;
        char line[20];
        //int value=0;
        int width, height, temp;
        //char p0[2], p1[2], p2[2], p3[2], p4[2], p5[2], p6[2], p7[2];
        char valstr[10];

        FontData *tempFont = new FontData;

        {
            fscanf( pFile, "%s", line );    // Should read "Name"
            fscanf( pFile, "%s", tempFont->FontName );

            fscanf( pFile, "%s", line );    // Should read "Width"
            fscanf( pFile, "%d", &width );

            fscanf( pFile, "%s", line );    // Should read "Height"
            fscanf( pFile, "%d", &height );

            fscanf( pFile, "%s", line );    // Should read "CharNumber"
            fscanf( pFile, "%d", &temp );
            tempFont->NumberChar = temp;

            fscanf( pFile, "%s", line );    // Should read "Data"

            for (int j = 0; j<tempFont->NumberChar; j++)
            {
                FontChar *tempChar = new FontChar;
                tempChar->CharWidth = width;
                tempChar->CharHeight = height;

                tempChar->CharData = (unsigned short *) malloc( height * sizeof( unsigned short ) );

                for (int i = 0; i < height; i++)
                {
                    // we read the hexadecimal value in the file
                    fscanf( pFile, "%s", valstr );

                    // we check how many characters has the Hexa value (F->1; FF->2, FFF->3, FFFF->4) (max is 4 bytes)
                    int length = strlen( valstr );
                    int nbvalue=0;
                    char digit;

                    for(int k = 0; k<length; k++)
                    {
                        digit=valstr[ k ];
                        int digitint=0;
                        switch(digit)
                        {
                        case '0' :
                            digitint=0;
                            break;
                        case '1' :
                            digitint=1;
                            break;
                        case '2' :
                            digitint=2;
                            break;
                        case '3' :
                            digitint=3;
                            break;

                        case '4' :
                            digitint=4;
                            break;
                        case '5' :
                            digitint=5;
                            break;
                        case '6' :
                            digitint=6;
                            break;
                        case '7' :
                            digitint=7;
                            break;

                        case '8' :
                            digitint=8;
                            break;
                        case '9' :
                            digitint=9;
                            break;
                        case 'A' :
                            digitint=10;
                            break;
                        case 'B' :
                            digitint=11;
                            break;

                        case 'C' :
                            digitint=12;
                            break;
                        case 'D' :
                            digitint=13;
                            break;
                        case 'E' :
                            digitint=14;
                            break;
                        case 'F' :
                            digitint=15;
                            break;
                        }

                        nbvalue += (digitint << ((length-k-1)*4));
                    }

                    tempChar->CharData[i] = nbvalue;

                }

                tempFont->Font.push_back( tempChar );
            }
        }

        fclose(pFile);

        FontCollection.push_back( tempFont );
    }

}

unsigned int FontEngine::GetStringWidth( char *str )
{
    int length = (int) strlen( str );
    int posx = 0;

    for(int i=0; i< length-1; i++)
    {
        posx += currentfont->Font[str[i]]->CharWidth + hspacing;
    }
    posx +=currentfont->Font[str[length-1]]->CharWidth; // for the alst character we do not add the spacing

    return posx;
}


unsigned int FontEngine::GetStringWidth( std::string str )
{
    int length = str.size();
    int posx = 0;

    for(int i=0; i< length-1; i++)
    {
        posx += currentfont->Font[str[i]]->CharWidth + hspacing;
    }
    posx +=currentfont->Font[str[length-1]]->CharWidth; // for the alst character we do not add the spacing

    return posx;
}


// this is for monoline text, does not take into consideration \n character yet
unsigned int FontEngine::GetStringHeight( char *str )
{
    int length = (int) strlen( str );
    int posy = 0;

    for(int i=0; i< length; i++)
    {
        if( currentfont->Font[str[i]]->CharHeight > posy)
            posy = currentfont->Font[str[i]]->CharHeight;
    }
    return posy;
}


// this is for monoline text, does not take into consideration \n character yet
unsigned int FontEngine::GetStringHeight( std::string str )
{
    int length = str.size();
    int posy = 0;

    for(int i=0; i< length; i++)
    {
        if( currentfont->Font[str[i]]->CharHeight > posy)
            posy = currentfont->Font[str[i]]->CharHeight;
    }
    return posy;
}


unsigned int FontEngine::GetCharWidth( char str )
{
    return currentfont->Font[str]->CharWidth;
}

unsigned int FontEngine::GetCharHeight( char str )
{
    return currentfont->Font[str]->CharHeight;
}


unsigned int FontEngine::AssertStringLength( char *str, unsigned int width )
{
    unsigned int lengthstr = GetStringWidth( str );
    unsigned int nbchartotal = (unsigned int) strlen( str );

    if (width >= lengthstr)
    {
        return nbchartotal;
    }
    else
    {
        unsigned int current_length=0;
        for (unsigned int i=0; i<nbchartotal; i++)
        {
            current_length += GetCharWidth(str[i]);
            if (current_length >= width) return i;
            current_length += hspacing;
        }
    }
    return 0;
}

unsigned int FontEngine::AssertStringLength( std::string str, unsigned int width )
{
    unsigned int lengthstr = GetStringWidth( str );
    unsigned int nbchartotal = str.size();

    if (width >= lengthstr)
    {
        return nbchartotal;
    }
    else
    {
        unsigned int current_length=0;
        for (unsigned int i=0; i<nbchartotal; i++)
        {
            current_length += GetCharWidth(str[i]);
            if (current_length >= width) return i;
            current_length += hspacing;
        }
    }
    return 0;
}


unsigned int FontEngine::AssertStringLength( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike )
{
    SetCurrentFont( name );
    SetModifierTypo( typo );
    SetModifierUnder( under );
    SetModifierStrike( strike );

    unsigned int lengthstr = GetStringWidth( str );
    unsigned int nbchartotal = str.size();

    if (width >= lengthstr)
    {
        return nbchartotal;
    }
    else
    {
        unsigned int current_length = 0;
        for (unsigned int i=0; i<nbchartotal; i++)
        {
            current_length += GetCharWidth(str[i]);
            if (current_length >= width) return i;
            current_length += hspacing;
        }
    }
    return 0;
}


std::string FontEngine::ReduceStringToVisible( std::string str, unsigned int width )
{
    unsigned int maxlength = AssertStringLength( str, width );
    std::string resultstr;

    if (maxlength == str.size())
    {
        for(unsigned int i=0; i<maxlength; i++)
            resultstr += str[i];
    }
    else
    {
        for(unsigned int i=0; i<maxlength-2; i++)
            resultstr += str[i];
        resultstr += '\u0010';
    }
    return resultstr;
}



std::string FontEngine::ReduceStringToVisible( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike )
{
    SetCurrentFont( name );
    SetModifierTypo( typo );
    SetModifierUnder( under );
    SetModifierStrike( strike );

    unsigned int maxlength = AssertStringLength( str, width );
    std::string resultstr;

    if (maxlength == str.size())
    {
        for(unsigned int i=0; i<maxlength; i++)
            resultstr += str[i];
    }
    else
    {
        for(unsigned int i=0; i<maxlength-2; i++)
            resultstr += str[i];
        resultstr += '\u0010';
    }
    return resultstr;
}


void FontEngine::SetCurrentFont( FontName curfont ) // To be checked for internam parameters
{
    currentfont = FontCollection[ curfont ];
}

void FontEngine::SetSpacing( int hspace, int vspace )
{
    hspacing = hspace;
    vspacing = vspace;
}

int FontEngine::GetHSpacing( )
{
    return hspacing;
}

int FontEngine::GetVSpacing( )
{
    return vspacing;
}

void FontEngine::SetModifierTypo( FontModifierTypo mod )
{
    currentmodifiertypo = mod;
}

void FontEngine::SetModifierUnder( FontModifierUnder mod )
{
    currentmodifierunder = mod;
}

void FontEngine::SetModifierStrike( FontModifierStrike mod )
{
    currentmodifierstrike = mod;
}

void FontEngine::DrawStringLeft( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{

    int length = (int) strlen( str );
    int posx = x;
    int posy = y;

    for(int i=0; i< length; i++)
    {
        DrawCharLeft( str[i], posx, posy, R, G, B, A );
        posx += currentfont->Font[str[i]]->CharWidth + hspacing;
    }
}


void FontEngine::DrawStringLeft(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{

    int length = str.size();
    int posx = x;
    int posy = y;

    for(int i=0; i< length; i++)
    {
        DrawCharLeft( str[i], posx, posy, R, G, B, A );
        posx += currentfont->Font[str[i]]->CharWidth + hspacing;
    }
}



void FontEngine::DrawCharLeft( char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    FontChar *temp = currentfont->Font[str];

    for (int j=0; j<temp->CharHeight; j++)
    {
        int mask = 1;
        for (int i=0; i<temp->CharWidth; i++)
        {
            if ((temp->CharData[j] & (mask << i)) != 0)
            {

                if ((currentmodifiertypo & Normal) !=0 )
                {
                    // text is Normal
                    ScreenRenderer::DrawPixel( x+temp->CharWidth-i-1, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & Italic) !=0 )
                {
                    // text is Italic but not Bold
                    int shift = (int) ((temp->CharHeight-1-j)/4);
                    ScreenRenderer::DrawPixel(  x+temp->CharWidth-i-1+shift, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & Bold) !=0 )
                {
                    // text is Bold but not Italic
                    ScreenRenderer::DrawPixel(  x+temp->CharWidth-i-1, y+j, R, G, B, A);
                    ScreenRenderer::DrawPixel(  x+temp->CharWidth-i, y+j, R, G, B, A);
                }
                if ((currentmodifiertypo & ItalicBold) !=0 )
                {
                    // text is Italic and Bold
                    int shift = (int) ((temp->CharHeight-1-j)/4);
                    ScreenRenderer::DrawPixel( x+temp->CharWidth-i-1+shift, y+j, R, G, B, A);
                    ScreenRenderer::DrawPixel( x+temp->CharWidth-i+shift, y+j, R, G, B, A);
                }

            }
        }
    }

    if ((currentmodifierunder & NoUnder) !=0 )
    {
        // text is not underlined
    }
    if ((currentmodifierunder & UnderSimple) !=0 )
    {
        // text is underlined with one single line
       ScreenRenderer::DrawLine( x-1, y+temp->CharHeight+2, x+temp->CharWidth+1, y+temp->CharHeight+2, R, G, B, A );
    }
    if ((currentmodifierunder & UnderDouble) !=0 )
    {
        // text is underlined with two lines
       ScreenRenderer::DrawLine(  x-1, y+temp->CharHeight+2, x+temp->CharWidth+1, y+temp->CharHeight+2, R, G, B, A );
       ScreenRenderer::DrawLine( x-1, y+temp->CharHeight+4, x+temp->CharWidth+1, y+temp->CharHeight+4, R, G, B, A );
    }




    if ((currentmodifierstrike & NoStrike) !=0 )
    {
        // text is not underlined
    }
    if ((currentmodifierstrike & StrikeSimple) !=0 )
    {
        // text is underlined with one single line
        ScreenRenderer::DrawLine( x-1, (int) (y+temp->CharHeight/2), x+temp->CharWidth+1, (int) (y+temp->CharHeight/2), R, G, B, A );
    }
    if ((currentmodifierstrike & StrikeDouble) !=0 )
    {
        // text is underlined with two lines
        ScreenRenderer::DrawLine( x-1, (int) (y+temp->CharHeight/2)-1, x+temp->CharWidth+1, (int) (y+temp->CharHeight/2)-1, R, G, B, A );
        ScreenRenderer::DrawLine( x-1, (int) (y+temp->CharHeight/2)+1, x+temp->CharWidth+1, (int) (y+temp->CharHeight/2)+1, R, G, B, A );
    }


}

void FontEngine::DrawStringCenter( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) (GetStringWidth( str ) / 2);
    DrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::DrawStringCenter(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) (GetStringWidth( str ) / 2);
    DrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::DrawCharCenter(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) (GetCharWidth( str ) / 2);
    DrawCharLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::DrawStringRight(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) GetStringWidth( str );
    DrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::DrawStringRight(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) GetStringWidth( str );
    DrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::DrawCharRight(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
    int dx = (int) GetCharWidth( str );
    DrawCharLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::SetDefaultFontPreset( )
{
    widget_text_enable = { THIN_FONT, Normal, NoUnder, NoStrike };
    widget_text_disable = { THIN_FONT, Normal, NoUnder, NoStrike };
    widget_text_selected = { THIN_FONT, Normal, NoUnder, NoStrike };

    window_titlebartext_enable = { THIN_FONT, Bold, NoUnder, NoStrike };
    window_titlebartext_disable = { THIN_FONT, Bold, NoUnder, NoStrike };
}
