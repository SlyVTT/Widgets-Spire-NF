#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <vector>
#include <string>

#include "ColorEngine.hpp"


class FontEngine
{
public:

    struct FontChar
    {
        int CharWidth;
        int CharHeight;
        unsigned short *CharData;       // Should allow 4bytes coding (i.e. font up to 32x32 with only minimum changes in loading procedure
    };

    struct FontData
    {
        char FontName[25];
        int NumberChar;
        std::vector <FontChar*> Font;
    };

    enum FontEnum
    {
        Widget_Text_Enable = 1,
        Widget_Text_Disable = 2,
        Widget_Text_Selected = 3,

        Window_Titlebartext_Enable = 4,
        Window_Titlebartext_Disable = 5
    };

    enum FontName
    {
        THIN_FONT = 0,
        VGA_FONT = 1,
        SPAC_FONT = 2,
        TINY_FONT = 3,
        STAN_FONT = 4,
        FANT_FONT = 5,
    };

    enum FontModifierTypo
    {
        Normal = 1,
        Italic = 2,
        Bold = 4,
        ItalicBold = 8,
    };

    enum FontModifierUnder
    {
        NoUnder = 1,
        UnderSimple = 2,
        UnderDouble = 4,
    };

    enum FontModifierStrike
    {
        NoStrike = 1,
        StrikeSimple = 2,
        StrikeDouble = 4,
    };

    struct FontSet
    {
        FontName name;
        FontModifierTypo typo;
        FontModifierUnder under;
        FontModifierStrike strike;
    };


    FontEngine(FontEngine&) = delete;
    FontEngine& operator= (const FontEngine&) = delete;

    static FontEngine& Get( void );

    static FontSet GetFontSet( FontEnum forwhat ) { return Get().InternalGetFontSet( forwhat ); };
    static void SetFontSet( FontEnum forwhat, FontSet fontset ) { Get().InternalSetFontSet( forwhat, fontset ); };


    static void Initialize( void ) { Get().InternalInitialize(); };
    static void Close( void ) { Get().InternalClose(); };

    static void LoadFontFromFile( std::string filename ) { Get().InternalLoadFontFromFile( filename ); };
    static FontData* LoadFontFromFilePointer( std::string filename ) { return Get().InternalLoadFontFromFilePointer( filename ); };

    static unsigned int AssertStringLength( char *str, unsigned int width ) { return Get().InternalAssertStringLength( str, width ); };
    static unsigned int AssertStringLength( std::string str, unsigned int width ) { return Get().InternalAssertStringLength( str, width ); };
    static unsigned int AssertStringLength( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike ) { return Get().InternalAssertStringLength( str, width, name, typo, under, strike ); };

    static std::string ReduceStringToVisible( std::string str, unsigned int width ) { return Get().InternalReduceStringToVisible( str, width ); };
    static std::string ReduceStringToVisible( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike )  { return Get().InternalReduceStringToVisible( str, width, name, typo, under, strike ); };

    static void SetCurrentFont( FontName curfont ) { Get().InternalSetCurrentFont( curfont ); };
    static void SetCurrentSpacing( int hspace, int vspace ) { Get().InternalSetCurrentSpacing( hspace, vspace ); };
    static void SetCurrentModifierTypo( FontModifierTypo mod ) { Get().InternalSetCurrentModifierTypo( mod ); };
    static void SetCurrentModifierUnder( FontModifierUnder mod ) { Get().InternalSetCurrentModifierUnder( mod ); };
    static void SetCurrentModifierStrike( FontModifierStrike mod ) { Get().InternalSetCurrentModifierStrike( mod ); };
    static void SetCurrentFontSet( FontEnum forwhat ) { Get().InternalSetCurrentFontSet( forwhat ); };

    static unsigned int GetStringWidth( char *str ) { return Get().InternalGetStringWidth( str ); };
    static unsigned int GetStringHeight( char *str ) { return Get().InternalGetStringHeight( str ); };
    static unsigned int GetStringWidth( std::string str ) { return Get().InternalGetStringWidth( str ); };
    static unsigned int GetStringHeight( std::string str ) { return Get().InternalGetStringHeight( str ); };
    static unsigned int GetCharWidth( char str ) { return Get().InternalGetCharWidth( str ); };
    static unsigned int GetCharHeight( char str ) { return Get().InternalGetCharHeight( str ); };

    static int GetCurrentHSpacing( void)  { return Get().InternalGetCurrentHSpacing(); };
    static int GetCurrentVSpacing(void)  { return Get().InternalGetCurrentVSpacing(); };

    static void DrawStringLeft( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A )  { Get().InternalDrawStringLeft( str, x, y, R, G, B, A ); };
    static void DrawStringLeft(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawStringLeft( str, x, y, R, G, B, A ); };
    static void DrawCharLeft( char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawCharLeft( str, x, y, R, G, B, A ); };

    static void DrawStringCenter(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawStringCenter( str, x, y, R, G, B, A ); };
    static void DrawStringCenter(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawStringCenter( str, x, y, R, G, B, A ); };
    static void DrawCharCenter(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawCharCenter( str, x, y, R, G, B, A ); };

    static void DrawStringRight(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawStringRight( str, x, y, R, G, B, A ); };
    static void DrawStringRight( std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawStringRight( str, x, y, R, G, B, A ); };
    static void DrawCharRight(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A ) { Get().InternalDrawCharRight( str, x, y, R, G, B, A ); };


    static void DrawStringLeft( char *str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color )  { Get().InternalDrawStringLeft( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawStringLeft(  std::string str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawStringLeft( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawCharLeft( char str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawCharLeft( str, x, y, color.R, color.G, color.B, color.A ); };

    static void DrawStringCenter(  char *str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawStringCenter( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawStringCenter(  std::string str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawStringCenter( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawCharCenter(  char str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawCharCenter( str, x, y, color.R, color.G, color.B, color.A ); };

    static void DrawStringRight(  char *str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawStringRight( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawStringRight( std::string str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawStringRight( str, x, y, color.R, color.G, color.B, color.A ); };
    static void DrawCharRight(  char str, unsigned int x, unsigned int y, ColorEngine::ColorRGBA color ) { Get().InternalDrawCharRight( str, x, y, color.R, color.G, color.B, color.A ); };

    static void SetDefaultFontPreset( void )  { Get().InternalSetDefaultFontPreset(); };

    static void ResetState( void )  { Get().InternalResetState( ); };



private:

    FontEngine();

    static FontEngine m_font;


    FontData *currentfont = nullptr;
    FontModifierTypo currentmodifiertypo;
    FontModifierUnder currentmodifierunder;
    FontModifierStrike currentmodifierstrike;

    std::vector <FontData*> FontCollection;
    int vspacing = 0;
    int hspacing = 0;


    void InternalInitialize( void );
    void InternalClose( void );

    void InternalLoadFontFromFile( std::string filename );
    FontData* InternalLoadFontFromFilePointer( std::string filename );

    unsigned int InternalAssertStringLength( char *str, unsigned int width );
    unsigned int InternalAssertStringLength( std::string str, unsigned int width );
    unsigned int InternalAssertStringLength( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike );

    std::string InternalReduceStringToVisible( std::string str, unsigned int width );
    std::string InternalReduceStringToVisible( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike );

    void InternalSetCurrentFont( FontName curfont );
    void InternalSetCurrentSpacing( int hspace, int vspace );
    void InternalSetCurrentModifierTypo( FontModifierTypo mod );
    void InternalSetCurrentModifierUnder( FontModifierUnder mod );
    void InternalSetCurrentModifierStrike( FontModifierStrike mod );
    void InternalSetCurrentFontSet( FontEnum forwhat );

    unsigned int InternalGetStringWidth( char *str );
    unsigned int InternalGetStringHeight( char *str );
    unsigned int InternalGetStringWidth( std::string str );
    unsigned int InternalGetStringHeight( std::string str );
    unsigned int InternalGetCharWidth( char str );
    unsigned int InternalGetCharHeight( char str );

    int InternalGetCurrentHSpacing( void );
    int InternalGetCurrentVSpacing( void );

    void InternalDrawStringLeft( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawStringLeft(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawCharLeft( char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    void InternalDrawStringCenter(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawStringCenter(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawCharCenter(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    void InternalDrawStringRight(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawStringRight( std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    void InternalDrawCharRight(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    void InternalSetDefaultFontPreset( void );
    void InternalResetState( void );

    FontSet InternalGetFontSet( FontEnum forwhat );
    void InternalSetFontSet( FontEnum forwhat, FontSet fontset );


    FontSet widget_text_enable;
    FontSet widget_text_disable;
    FontSet widget_text_selected;

    FontSet window_titlebartext_enable;
    FontSet window_titlebartext_disable;
};

#endif // FONTENGINE_H
