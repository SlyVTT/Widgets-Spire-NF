#ifndef COLORENGINE_H
#define COLORENGINE_H

#include <vector>
#include <string>



class ColorEngine
{
public:

    struct ColorRGBA
    {
        unsigned short R;
        unsigned short G;
        unsigned short B;
        unsigned short A;
    };

    enum ColorEnum
    {
        Widget_Border_Enable = 1,
        Widget_Border_Disable = 2,
        Widget_Border_Cursoron = 3,
        Widget_Border_Hasfocus = 4,

        Widget_Tickmark_Enable = 5,
        Widget_Tickmark_Disable = 6,

        Widget_Filling_Enable = 7,
        Widget_Filling_Disable = 8,
        Widget_Selection = 9,

        Widget_Text_Enable = 10,
        Widget_Text_Disable = 11,
        Widget_Text_Selected = 12,

        Window_Titlebar_Enable = 13,
        Window_Titlebar_Disable = 14,
        Window_Titlebar_Minimize = 15,
        Window_Titlebar_Maximize = 16,
        Window_Titlebar_Restore = 17,

        Window_Titlebartext_Enable = 18,
        Window_Titlebartext_Disable = 19,

        Widget_Commuter_Active_Filling_Style1 = 20,
        Widget_Commuter_Inactive_Filling_Style1 = 21,
        Widget_Commuter_Active_Cursor_Style1 = 22,
        Widget_Commuter_Inactive_Cursor_Style1 = 23,

        Widget_Commuter_Active_Filling_Style2 = 24,
        Widget_Commuter_Inactive_Filling_Style2 = 25,
        Widget_Commuter_Active_Cursor_Style2 = 26,
        Widget_Commuter_Inactive_Cursor_Style2 = 27,

        Widget_Commuter_Active_Filling_Style3 = 28,
        Widget_Commuter_Inactive_Filling_Style3 = 29,
        Widget_Commuter_Active_Cursor_Style3 = 30,
        Widget_Commuter_Inactive_Cursor_Style3 = 31,

        Widget_Commuter_Active_Filling_Style4 = 32,
        Widget_Commuter_Inactive_Filling_Style4 = 33,
        Widget_Commuter_Active_Cursor_Style4 = 34,
        Widget_Commuter_Inactive_Cursor_Style4 = 35,

        Widget_Progressbar_Enable_Filling = 36,
        Widget_Progressbar_Disable_Filling = 37,
        Widget_Progressbar_Rainbow_Empty = 38,
        Widget_Progressbar_Rainbow_Full = 39
    };


    ColorEngine(ColorEngine&) = delete;
    ColorEngine& operator= (const ColorEngine&) = delete;

    static ColorEngine& Get( void );


    static void Initialize( void ) { Get().InternalInitialize(); };
    static void Close( void ) { Get().InternalClose(); };
    static void SetDefaultColorPreset( void )  { Get().InternalSetDefaultColorPreset(); };
    static void ResetState( void )  { Get().InternalResetState( ); };

    static ColorRGBA GetColor( ColorEnum forwhat ) { return Get().InternalGetColor( forwhat); };
    static void SetColor( ColorEnum forwhat, ColorRGBA color ) { Get().InternalSetColor( forwhat, color ); };



private:

    ColorEngine();

    static ColorEngine m_color;

    void InternalInitialize( void );
    void InternalClose( void );

    void InternalSetDefaultColorPreset( void );
    void InternalResetState( void );

    ColorRGBA InternalGetColor( ColorEnum forwhat );
    void InternalSetColor( ColorEnum forwhat, ColorRGBA color );



    ColorRGBA widget_border_enable;
    ColorRGBA widget_border_disable;
    ColorRGBA widget_border_cursoron;
    ColorRGBA widget_border_hasfocus;

    ColorRGBA widget_tickmark_enable;
    ColorRGBA widget_tickmark_disable;

    ColorRGBA widget_filling_enable;
    ColorRGBA widget_filling_disable;
    ColorRGBA widget_selection;

    ColorRGBA widget_text_enable;
    ColorRGBA widget_text_disable;
    ColorRGBA widget_text_selected;

    ColorRGBA window_titlebar_enable;
    ColorRGBA window_titlebar_disable;
    ColorRGBA window_titlebar_minimize;
    ColorRGBA window_titlebar_maximize;
    ColorRGBA window_titlebar_restore;

    ColorRGBA window_titlebartext_enable;
    ColorRGBA window_titlebartext_disable;

    ColorRGBA widget_commuter_active_filling_style1;
    ColorRGBA widget_commuter_inactive_filling_style1;
    ColorRGBA widget_commuter_active_cursor_style1;
    ColorRGBA widget_commuter_inactive_cursor_style1;

    ColorRGBA widget_commuter_active_filling_style2;
    ColorRGBA widget_commuter_inactive_filling_style2;
    ColorRGBA widget_commuter_active_cursor_style2;
    ColorRGBA widget_commuter_inactive_cursor_style2;

    ColorRGBA widget_commuter_active_filling_style3;
    ColorRGBA widget_commuter_inactive_filling_style3;
    ColorRGBA widget_commuter_active_cursor_style3;
    ColorRGBA widget_commuter_inactive_cursor_style3;

    ColorRGBA widget_commuter_active_filling_style4;
    ColorRGBA widget_commuter_inactive_filling_style4;
    ColorRGBA widget_commuter_active_cursor_style4;
    ColorRGBA widget_commuter_inactive_cursor_style4;

    ColorRGBA widget_progressbar_enable_filling;
    ColorRGBA widget_progressbar_disable_filling;
    ColorRGBA widget_progressbar_rainbow_empty;
    ColorRGBA widget_progressbar_rainbow_full;

};

#endif // COLORENGINE_H
