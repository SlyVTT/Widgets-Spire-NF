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

}

FontEngine& FontEngine::Get( void )
{
       static FontEngine m_font;
       return m_font;
}

void FontEngine::InternalInitialize()
{
       LoadFontFromFile( "/documents/Widget/Fonts/THIN.WFE.tns" );
       LoadFontFromFile( "/documents/Widget/Fonts/VGA.WFE.tns" );
       LoadFontFromFile( "/documents/Widget/Fonts/SPACE.WFE.tns" );
       LoadFontFromFile( "/documents/Widget/Fonts/TINY.WFE.tns" );
       LoadFontFromFile( "/documents/Widget/Fonts/STANDARD.WFE.tns" );
       LoadFontFromFile( "/documents/Widget/Fonts/FANTASY.WFE.tns" );
       InternalSetDefaultFontPreset();
       InternalSetCurrentFont( THIN_FONT );
       vspacing = 3;
       hspacing = -1;
       currentmodifiertypo = Normal;  // set text as normal
       currentmodifierunder = NoUnder; // No underlining
       currentmodifierstrike = NoStrike; // No striking
}


void FontEngine::InternalResetState( void )
{
       SetCurrentFont( THIN_FONT );
       vspacing = 3;
       hspacing = -1;
       currentmodifiertypo = Normal;  // set text as normal
       currentmodifierunder = NoUnder; // No underlining
       currentmodifierstrike = NoStrike; // No striking
}


void FontEngine::InternalClose()
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

FontEngine::FontData* FontEngine::InternalLoadFontFromFilePointer( std::string filename )
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

void FontEngine::InternalLoadFontFromFile( std::string filename )
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

unsigned int FontEngine::InternalGetStringWidth( char *str )
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


unsigned int FontEngine::InternalGetStringWidth( std::string str )
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
unsigned int FontEngine::InternalGetStringHeight( char *str )
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
unsigned int FontEngine::InternalGetStringHeight( std::string str )
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


unsigned int FontEngine::InternalGetCharWidth( char str )
{
       return currentfont->Font[str]->CharWidth;
}

unsigned int FontEngine::InternalGetCharHeight( char str )
{
       return currentfont->Font[str]->CharHeight;
}


unsigned int FontEngine::InternalAssertStringLength( char *str, unsigned int width )
{
       unsigned int lengthstr = InternalGetStringWidth( str );
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
                     current_length += InternalGetCharWidth(str[i]);
                     if (current_length >= width) return i;
                     current_length += hspacing;
              }
       }
       return 0;
}

unsigned int FontEngine::InternalAssertStringLength( std::string str, unsigned int width )
{
       unsigned int lengthstr = InternalGetStringWidth( str );
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
                     current_length += InternalGetCharWidth(str[i]);
                     if (current_length >= width) return i;
                     current_length += hspacing;
              }
       }
       return 0;
}


unsigned int FontEngine::InternalAssertStringLength( std::string str, unsigned int width, FontEngine::FontName name, FontEngine::FontModifierTypo typo, FontEngine::FontModifierUnder under, FontEngine::FontModifierStrike strike )
{
       InternalSetCurrentFont( name );
       InternalSetCurrentModifierTypo( typo );
       InternalSetCurrentModifierUnder( under );
       InternalSetCurrentModifierStrike( strike );

       unsigned int lengthstr = InternalGetStringWidth( str );
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
                     current_length += InternalGetCharWidth(str[i]);
                     if (current_length >= width) return i;
                     current_length += hspacing;
              }
       }
       return 0;
}


std::string FontEngine::InternalReduceStringToVisible( std::string str, unsigned int width )
{
       unsigned int maxlength = InternalAssertStringLength( str, width );
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



std::string FontEngine::InternalReduceStringToVisible( std::string str, unsigned int width, FontEngine::FontName name, FontEngine::FontModifierTypo typo, FontEngine::FontModifierUnder under, FontEngine::FontModifierStrike strike )
{
       InternalSetCurrentFont( name );
       InternalSetCurrentModifierTypo( typo );
       InternalSetCurrentModifierUnder( under );
       InternalSetCurrentModifierStrike( strike );

       unsigned int maxlength = InternalAssertStringLength( str, width );
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


FontEngine::FontSet FontEngine::InternalGetFontSet( FontEngine::FontEnum forwhat )
{
       switch (forwhat)
       {
       case Widget_Text_Enable:
              return widget_text_enable;
              break;

       case Widget_Text_Disable:
              return widget_text_disable;
              break;

       case Widget_Text_Selected:
              return widget_text_selected;
              break;

       case Window_Titlebartext_Enable:
              return window_titlebartext_enable;
              break;

       case Window_Titlebartext_Disable:
              return window_titlebartext_disable;
              break;
       }

      return widget_text_enable;
}

void FontEngine::InternalSetCurrentFontSet( FontEngine::FontEnum forwhat )
{
        switch (forwhat)
       {
       case Widget_Text_Enable:
              InternalSetCurrentFont( widget_text_enable.name );
              InternalSetCurrentModifierTypo( widget_text_enable.typo );
              InternalSetCurrentModifierUnder( widget_text_enable.under );
              InternalSetCurrentModifierStrike( widget_text_enable.strike );
              break;

       case Widget_Text_Disable:
              InternalSetCurrentFont( widget_text_disable.name );
              InternalSetCurrentModifierTypo( widget_text_disable.typo );
              InternalSetCurrentModifierUnder( widget_text_disable.under );
              InternalSetCurrentModifierStrike( widget_text_disable.strike );
              break;

       case Widget_Text_Selected:
              InternalSetCurrentFont( widget_text_selected.name );
              InternalSetCurrentModifierTypo( widget_text_selected.typo );
              InternalSetCurrentModifierUnder( widget_text_selected.under );
              InternalSetCurrentModifierStrike( widget_text_selected.strike );
              break;

       case Window_Titlebartext_Enable:
              InternalSetCurrentFont( window_titlebartext_enable.name );
              InternalSetCurrentModifierTypo( window_titlebartext_enable.typo );
              InternalSetCurrentModifierUnder( window_titlebartext_enable.under );
              InternalSetCurrentModifierStrike( window_titlebartext_enable.strike );
              break;

       case Window_Titlebartext_Disable:
              InternalSetCurrentFont( window_titlebartext_disable.name );
              InternalSetCurrentModifierTypo( window_titlebartext_disable.typo );
              InternalSetCurrentModifierUnder( window_titlebartext_disable.under );
              InternalSetCurrentModifierStrike( window_titlebartext_disable.strike );
              break;
       }
}


void FontEngine::InternalSetFontSet( FontEngine::FontEnum forwhat, FontEngine::FontSet fontset )
{
       switch (forwhat)
       {
       case Widget_Text_Enable:
              widget_text_enable = fontset;
              break;

       case Widget_Text_Disable:
              widget_text_disable = fontset;
              break;

       case Widget_Text_Selected:
              widget_text_selected = fontset;
              break;

       case Window_Titlebartext_Enable:
              window_titlebartext_enable = fontset;
              break;

       case Window_Titlebartext_Disable:
              window_titlebartext_disable = fontset;
              break;
       }
}

void FontEngine::InternalSetCurrentFont( FontEngine::FontName curfont ) // To be checked for internam parameters
{
       currentfont = FontCollection[ curfont ];
}

void FontEngine::InternalSetCurrentSpacing( int hspace, int vspace )
{
       hspacing = hspace;
       vspacing = vspace;
}

int FontEngine::InternalGetCurrentHSpacing( )
{
       return hspacing;
}

int FontEngine::InternalGetCurrentVSpacing( )
{
       return vspacing;
}

void FontEngine::InternalSetCurrentModifierTypo( FontEngine::FontModifierTypo mod )
{
       currentmodifiertypo = mod;
}

void FontEngine::InternalSetCurrentModifierUnder( FontEngine::FontModifierUnder mod )
{
       currentmodifierunder = mod;
}

void FontEngine::InternalSetCurrentModifierStrike( FontEngine::FontModifierStrike mod )
{
       currentmodifierstrike = mod;
}

void FontEngine::InternalDrawStringLeft( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{

       int length = (int) strlen( str );
       int posx = x;
       int posy = y;

       for(int i=0; i< length; i++)
       {
              InternalDrawCharLeft( str[i], posx, posy, R, G, B, A );
              posx += currentfont->Font[str[i]]->CharWidth + hspacing;
       }
}


void FontEngine::InternalDrawStringLeft(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{

       int length = str.size();
       int posx = x;
       int posy = y;

       for(int i=0; i< length; i++)
       {
              InternalDrawCharLeft( str[i], posx, posy, R, G, B, A );
              posx += currentfont->Font[str[i]]->CharWidth + hspacing;
       }
}



void FontEngine::InternalDrawCharLeft( char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
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

void FontEngine::InternalDrawStringCenter( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) (InternalGetStringWidth( str ) / 2);
       InternalDrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalDrawStringCenter(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) (InternalGetStringWidth( str ) / 2);
       InternalDrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalDrawCharCenter(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) (InternalGetCharWidth( str ) / 2);
       InternalDrawCharLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalDrawStringRight(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) InternalGetStringWidth( str );
       InternalDrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalDrawStringRight(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) InternalGetStringWidth( str );
       InternalDrawStringLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalDrawCharRight(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )
{
       int dx = (int) InternalGetCharWidth( str );
       InternalDrawCharLeft( str, x-dx, y, R, G, B, A);
}


void FontEngine::InternalSetDefaultFontPreset( )
{
       widget_text_enable = { THIN_FONT, Normal, NoUnder, NoStrike };
       widget_text_disable = { THIN_FONT, Normal, NoUnder, NoStrike };
       widget_text_selected = { THIN_FONT, Normal, NoUnder, NoStrike };

       window_titlebartext_enable = { THIN_FONT, Bold, NoUnder, NoStrike };
       window_titlebartext_disable = { THIN_FONT, Bold, NoUnder, NoStrike };
}
