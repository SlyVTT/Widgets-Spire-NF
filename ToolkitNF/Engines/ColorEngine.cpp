#include "ColorEngine.hpp"


ColorEngine::ColorEngine()
{

}

ColorEngine& ColorEngine::Get( void )
{
       static ColorEngine m_color;
       return m_color;
}

void ColorEngine::InternalInitialize()
{
    InternalSetDefaultColorPreset();
}


void ColorEngine::InternalResetState( void )
{
    InternalSetDefaultColorPreset();
}


void ColorEngine::InternalClose()
{

}


void ColorEngine::InternalSetDefaultColorPreset( )
{
       // Normal DEFAULT theme (Hard coded)
       widget_border_enable = { 255, 0, 0, 255 }; //RED
       widget_border_disable = { 170, 170, 170, 255 };  //BLACK
       widget_border_cursoron = { 0, 255, 0, 255  }; //GREEN
       widget_border_hasfocus = { 0, 0, 255, 255 }; //BLUE

       widget_tickmark_enable = { 0, 0, 0, 255 }; //BLACK
       widget_tickmark_disable = { 170, 170, 170, 255 }; //DARK GREY

       widget_filling_enable = { 255, 255, 255, 255 }; //WHITE
       widget_filling_disable = { 255, 255, 255, 255 }; //WHITE
       widget_selection = { 255, 0, 125, 255 }; // PURPLEISH

       widget_text_enable = { 0, 0, 0, 255 }; //BLACK
       widget_text_disable = { 170, 170, 170, 255 }; // GREY
       widget_text_selected = { 255, 255, 255, 255 }; //WHITE

       window_titlebar_enable = { 0, 155, 255, 255 }; //LIGHT BLUE/CYAN
       window_titlebar_disable = { 170, 170, 170, 255 }; // GREY
       window_titlebar_minimize = { 255, 0, 0, 255 }; // RED
       window_titlebar_maximize = { 0, 255, 0, 255 }; // GREEN
       window_titlebar_restore = { 255, 255, 0, 255 }; // YELLOW

       window_titlebartext_enable = { 255, 255, 255, 255 }; //WHITE
       window_titlebartext_disable = { 100, 100, 100, 255 }; //DARK GREY

       widget_commuter_active_filling_style1 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_filling_style1 = { 255, 191, 191, 255 }; //SALMON
       widget_commuter_active_cursor_style1 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_cursor_style1 = { 255, 255, 255, 255 }; //WHITE

       widget_commuter_active_filling_style2 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_filling_style2 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_active_cursor_style2 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_cursor_style2 = { 255, 191, 191, 255 }; //SALMON

       widget_commuter_active_filling_style3 =  { 191, 255, 191, 255 }; //TENDER GREEN
       widget_commuter_inactive_filling_style3 = { 255, 191, 191, 255 }; //SALMON
       widget_commuter_active_cursor_style3 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_cursor_style3 = { 255, 255, 255, 255 }; //WHITE

       widget_commuter_active_filling_style4 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_inactive_filling_style4 = { 255, 255, 255, 255 }; //WHITE
       widget_commuter_active_cursor_style4 = { 191, 255, 191, 255 }; //TENDER GREEN
       widget_commuter_inactive_cursor_style4 = { 255, 191, 191, 255 }; //SALMON

       widget_progressbar_enable_filling = { 0, 155, 255, 255 }; //LIGHT BLUE/CYAN
       widget_progressbar_disable_filling = { 170, 170, 170, 255 }; // GREY
       widget_progressbar_rainbow_empty = { 127, 127, 0, 255 };
       widget_progressbar_rainbow_full = { 0, 255, 0, 255 };
}


ColorEngine::ColorRGBA ColorEngine::InternalGetColor( ColorEngine::ColorEnum forwhat )
{
       switch (forwhat)
       {

       case Widget_Border_Enable:
              return widget_border_enable;
              break;
       case Widget_Border_Disable:
              return widget_border_disable;
              break;
       case Widget_Border_Cursoron:
              return widget_border_cursoron;
              break;
       case Widget_Border_Hasfocus:
              return widget_border_hasfocus;
              break;


       case Widget_Tickmark_Enable:
              return widget_tickmark_enable;
              break;
       case Widget_Tickmark_Disable:
              return widget_tickmark_disable;
              break;


       case Widget_Filling_Enable:
              return widget_filling_enable;
              break;
       case Widget_Filling_Disable:
              return widget_filling_disable;
              break;
       case Widget_Selection:
              return widget_selection;
              break;


       case Widget_Text_Enable:
              return widget_text_enable;
              break;
       case Widget_Text_Disable:
              return widget_text_disable;
              break;
       case Widget_Text_Selected:
              return widget_text_selected;
              break;


       case Window_Titlebar_Enable:
              return window_titlebar_enable;
              break;
       case Window_Titlebar_Disable:
              return window_titlebar_disable;
              break;
       case Window_Titlebar_Minimize:
              return window_titlebar_minimize;
              break;
       case Window_Titlebar_Maximize:
              return window_titlebar_maximize;
              break;
       case Window_Titlebar_Restore:
              return window_titlebar_restore;
              break;

       case Window_Titlebartext_Enable:
              return window_titlebartext_enable;
              break;
       case Window_Titlebartext_Disable:
              return window_titlebartext_disable;
              break;


       case Widget_Commuter_Active_Filling_Style1:
              return widget_commuter_active_filling_style1;
              break;
       case Widget_Commuter_Inactive_Filling_Style1:
              return widget_commuter_inactive_filling_style1;
              break;
       case Widget_Commuter_Active_Cursor_Style1:
              return widget_commuter_active_cursor_style1;
              break;
       case Widget_Commuter_Inactive_Cursor_Style1:
              return widget_commuter_inactive_cursor_style1;
              break;


       case Widget_Commuter_Active_Filling_Style2:
              return widget_commuter_active_filling_style2;
              break;
       case Widget_Commuter_Inactive_Filling_Style2:
              return widget_commuter_inactive_filling_style2;
              break;
       case Widget_Commuter_Active_Cursor_Style2:
              return widget_commuter_active_cursor_style2;
              break;
       case Widget_Commuter_Inactive_Cursor_Style2:
              return widget_commuter_inactive_cursor_style2;
              break;


       case Widget_Commuter_Active_Filling_Style3:
              return widget_commuter_active_filling_style3;
              break;
       case Widget_Commuter_Inactive_Filling_Style3:
              return widget_commuter_inactive_filling_style3;
              break;
       case Widget_Commuter_Active_Cursor_Style3:
              return widget_commuter_active_cursor_style3;
              break;
       case Widget_Commuter_Inactive_Cursor_Style3:
              return widget_commuter_inactive_cursor_style3;
              break;


       case Widget_Commuter_Active_Filling_Style4:
              return widget_commuter_active_filling_style4;
              break;
       case Widget_Commuter_Inactive_Filling_Style4:
              return widget_commuter_inactive_filling_style4;
              break;
       case Widget_Commuter_Active_Cursor_Style4:
              return widget_commuter_active_cursor_style4;
              break;
       case Widget_Commuter_Inactive_Cursor_Style4:
              return widget_commuter_inactive_cursor_style4;
              break;


       case Widget_Progressbar_Enable_Filling:
              return widget_progressbar_enable_filling;
              break;
       case Widget_Progressbar_Disable_Filling:
              return widget_progressbar_disable_filling;
              break;
       case Widget_Progressbar_Rainbow_Empty:
              return widget_progressbar_rainbow_empty;
              break;
       case Widget_Progressbar_Rainbow_Full:
              return widget_progressbar_rainbow_full;
              break;
       }

    return widget_border_enable;
}


void ColorEngine::InternalSetColor( ColorEngine::ColorEnum forwhat, ColorEngine::ColorRGBA color )
{
       switch (forwhat)
       {

       case Widget_Border_Enable:
              widget_border_enable = color;
              break;
       case Widget_Border_Disable:
              widget_border_disable = color;
              break;
       case Widget_Border_Cursoron:
              widget_border_cursoron = color;
              break;
       case Widget_Border_Hasfocus:
              widget_border_hasfocus = color;
              break;


       case Widget_Tickmark_Enable:
              widget_tickmark_enable = color;
              break;
       case Widget_Tickmark_Disable:
              widget_tickmark_disable = color;
              break;


       case Widget_Filling_Enable:
              widget_filling_enable = color;
              break;
       case Widget_Filling_Disable:
              widget_filling_disable = color;
              break;
       case Widget_Selection:
              widget_selection = color;
              break;


       case Widget_Text_Enable:
              widget_text_enable = color;
              break;
       case Widget_Text_Disable:
              widget_text_disable = color;
              break;
       case Widget_Text_Selected:
              widget_text_selected = color;
              break;


       case Window_Titlebar_Enable:
              window_titlebar_enable = color;
              break;
       case Window_Titlebar_Disable:
              window_titlebar_disable = color;
              break;
       case Window_Titlebar_Minimize:
              window_titlebar_minimize = color;
              break;
       case Window_Titlebar_Maximize:
              window_titlebar_maximize = color;
              break;
       case Window_Titlebar_Restore:
              window_titlebar_restore = color;
              break;

       case Window_Titlebartext_Enable:
              window_titlebartext_enable = color;
              break;
       case Window_Titlebartext_Disable:
              window_titlebartext_disable = color;
              break;


       case Widget_Commuter_Active_Filling_Style1:
              widget_commuter_active_filling_style1 = color;
              break;
       case Widget_Commuter_Inactive_Filling_Style1:
              widget_commuter_inactive_filling_style1 = color;
              break;
       case Widget_Commuter_Active_Cursor_Style1:
              widget_commuter_active_cursor_style1 = color;
              break;
       case Widget_Commuter_Inactive_Cursor_Style1:
              widget_commuter_inactive_cursor_style1 = color;
              break;


       case Widget_Commuter_Active_Filling_Style2:
              widget_commuter_active_filling_style2 = color;
              break;
       case Widget_Commuter_Inactive_Filling_Style2:
              widget_commuter_inactive_filling_style2 = color;
              break;
       case Widget_Commuter_Active_Cursor_Style2:
              widget_commuter_active_cursor_style2 = color;
              break;
       case Widget_Commuter_Inactive_Cursor_Style2:
              widget_commuter_inactive_cursor_style2 = color;
              break;


       case Widget_Commuter_Active_Filling_Style3:
              widget_commuter_active_filling_style3 = color;
              break;
       case Widget_Commuter_Inactive_Filling_Style3:
              widget_commuter_inactive_filling_style3 = color;
              break;
       case Widget_Commuter_Active_Cursor_Style3:
              widget_commuter_active_cursor_style3 = color;
              break;
       case Widget_Commuter_Inactive_Cursor_Style3:
              widget_commuter_inactive_cursor_style3 = color;
              break;


       case Widget_Commuter_Active_Filling_Style4:
              widget_commuter_active_filling_style4 = color;
              break;
       case Widget_Commuter_Inactive_Filling_Style4:
              widget_commuter_inactive_filling_style4 = color;
              break;
       case Widget_Commuter_Active_Cursor_Style4:
              widget_commuter_active_cursor_style4 = color;
              break;
       case Widget_Commuter_Inactive_Cursor_Style4:
              widget_commuter_inactive_cursor_style4 = color;
              break;


       case Widget_Progressbar_Enable_Filling:
              widget_progressbar_enable_filling = color;
              break;
       case Widget_Progressbar_Disable_Filling:
              widget_progressbar_disable_filling = color;
              break;
       case Widget_Progressbar_Rainbow_Empty:
              widget_progressbar_rainbow_empty = color;
              break;
       case Widget_Progressbar_Rainbow_Full:
              widget_progressbar_rainbow_full = color;
              break;

       }
}
