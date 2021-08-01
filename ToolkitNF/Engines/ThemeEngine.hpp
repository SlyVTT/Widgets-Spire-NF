#ifndef THEMEENGINE_H
#define THEMEENGINE_H

#include "ColorEngine.hpp"
#include "FontEngine.hpp"


class ThemeEngine
{
public:

    ThemeEngine(ThemeEngine&) = delete;
    ThemeEngine& operator= (const ThemeEngine&) = delete;

    static ThemeEngine& Get( void );


    static void Initialize( void ) { Get().InternalInitialize(); };
    static void Close( void ) { Get().InternalClose(); };
    static void SetDefaultThemePreset( void )  { Get().InternalSetDefaultThemePreset(); };
    static void ResetState( void )  { Get().InternalResetState( ); };

    static void LoadThemeFromFile( std::string filename) {Get().InternalLoadThemeFromFile( filename); };
    static void ApplyTheme( void ) { Get().InternalApplyTheme(); };


private:

    ThemeEngine();

    static ThemeEngine m_theme;

    void InternalInitialize( void );
    void InternalClose( void );

    void InternalSetDefaultThemePreset( void );
    void InternalResetState( void );

    void InternalLoadThemeFromFile( std::string filename);
    void InternalApplyTheme( void );


    /// Default color names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    ColorEngine::ColorRGBA widget_border_enable;
    ColorEngine::ColorRGBA widget_border_disable;
    ColorEngine::ColorRGBA widget_border_cursoron;
    ColorEngine::ColorRGBA widget_border_hasfocus;

    ColorEngine::ColorRGBA widget_tickmark_enable;
    ColorEngine::ColorRGBA widget_tickmark_disable;

    ColorEngine::ColorRGBA widget_filling_enable;
    ColorEngine::ColorRGBA widget_filling_disable;
    ColorEngine::ColorRGBA widget_selection;

    ColorEngine::ColorRGBA widget_text_enable;
    ColorEngine::ColorRGBA widget_text_disable;
    ColorEngine::ColorRGBA widget_text_selected;

    ColorEngine::ColorRGBA window_titlebar_enable;
    ColorEngine::ColorRGBA window_titlebar_disable;
    ColorEngine::ColorRGBA window_titlebar_minimize;
    ColorEngine::ColorRGBA window_titlebar_maximize;
    ColorEngine::ColorRGBA window_titlebar_restore;

    ColorEngine::ColorRGBA window_titlebartext_enable;
    ColorEngine::ColorRGBA window_titlebartext_disable;

    ColorEngine::ColorRGBA widget_commuter_active_filling_style1;
    ColorEngine::ColorRGBA widget_commuter_inactive_filling_style1;
    ColorEngine::ColorRGBA widget_commuter_active_cursor_style1;
    ColorEngine::ColorRGBA widget_commuter_inactive_cursor_style1;

    ColorEngine::ColorRGBA widget_commuter_active_filling_style2;
    ColorEngine::ColorRGBA widget_commuter_inactive_filling_style2;
    ColorEngine::ColorRGBA widget_commuter_active_cursor_style2;
    ColorEngine::ColorRGBA widget_commuter_inactive_cursor_style2;

    ColorEngine::ColorRGBA widget_commuter_active_filling_style3;
    ColorEngine::ColorRGBA widget_commuter_inactive_filling_style3;
    ColorEngine::ColorRGBA widget_commuter_active_cursor_style3;
    ColorEngine::ColorRGBA widget_commuter_inactive_cursor_style3;

    ColorEngine::ColorRGBA widget_commuter_active_filling_style4;
    ColorEngine::ColorRGBA widget_commuter_inactive_filling_style4;
    ColorEngine::ColorRGBA widget_commuter_active_cursor_style4;
    ColorEngine::ColorRGBA widget_commuter_inactive_cursor_style4;

    ColorEngine::ColorRGBA widget_progressbar_enable_filling;
    ColorEngine::ColorRGBA widget_progressbar_disable_filling;
    ColorEngine::ColorRGBA widget_progressbar_rainbow_empty;
    ColorEngine::ColorRGBA widget_progressbar_rainbow_full;


    /// Default font names used by the widgets to be rendered.
    ///
    /// To be used only for developping new Widget and keeping a coherency with the look and feel of the other widgets.
    /// Using these default name permits to have a global theming for an application.
    FontEngine::FontSet font_widget_text_enable;
    FontEngine::FontSet font_widget_text_disable;
    FontEngine::FontSet font_widget_text_selected;

    FontEngine::FontSet font_window_titlebartext_enable;
    FontEngine::FontSet font_window_titlebartext_disable;

};

#endif // THEMEENGINE_H
