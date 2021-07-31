#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <vector>
#include <string>



class FontEngine
{
public:
    FontEngine();
    virtual ~FontEngine();

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


    virtual void LoadFontFromFile( std::string filename );
    static FontData* LoadFontFromFilePointer( std::string filename );

    virtual unsigned int AssertStringLength( char *str, unsigned int width );
    virtual unsigned int AssertStringLength( std::string str, unsigned int width );
    virtual unsigned int AssertStringLength( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike );

    virtual std::string ReduceStringToVisible( std::string str, unsigned int width );
    virtual std::string ReduceStringToVisible( std::string str, unsigned int width, FontName name, FontModifierTypo typo, FontModifierUnder under, FontModifierStrike strike );

    virtual void SetCurrentFont( FontName curfont ); // To be checked for internam parameters
    virtual void SetSpacing( int hspace, int vspace );
    virtual void SetModifierTypo( FontModifierTypo mod );
    virtual void SetModifierUnder( FontModifierUnder mod );
    virtual void SetModifierStrike( FontModifierStrike mod );

    virtual unsigned int GetStringWidth( char *str );
    virtual unsigned int GetStringHeight( char *str );
    virtual unsigned int GetCharWidth( char str );
    virtual unsigned int GetCharHeight( char str );

    virtual int GetHSpacing();
    virtual int GetVSpacing();

    virtual void DrawStringLeft( char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawCharLeft( char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawStringCenter(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawCharCenter(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawStringRight(  char *str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawCharRight(  char str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );

    virtual unsigned int GetStringWidth( std::string str );
    virtual unsigned int GetStringHeight( std::string str );
    virtual void DrawStringLeft(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawStringCenter(  std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );
    virtual void DrawStringRight( std::string str, unsigned int x, unsigned int y, unsigned short R, unsigned short G, unsigned short B, unsigned short A );


    /// Method for assigning default font shemes to the FontEngine.
    ///
    /// To be used to assign the default font scheme the FontEngine.
    virtual void SetDefaultFontPreset( );


    /// Default font names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    FontSet widget_text_enable;
    FontSet widget_text_disable;
    FontSet widget_text_selected;

    FontSet window_titlebartext_enable;
    FontSet window_titlebartext_disable;



protected:
    FontData *currentfont = nullptr;
    FontModifierTypo currentmodifiertypo;
    FontModifierUnder currentmodifierunder;
    FontModifierStrike currentmodifierstrike;

    std::vector <FontData*> FontCollection;
    int vspacing = 0;
    int hspacing = 0;

private:
};

#endif // FONTENGINE_H
