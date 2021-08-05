#include "ToolkitNF/GUIToolkitNF.hpp"


int main( void )
{
       WidgetApplication::Initialize();

       DesktopWidget* desktop = new DesktopWidget( "I am a Desktop", 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, nullptr );

       ButtonWidget* button = new ButtonWidget( "Hello World !!!", 25, 25, 250, 20, desktop );

#if RENDER_WITH_SDL == 1
       ButtonWidget* button2 = new ButtonWidget( "We are rendered with SDL", 25, 50, 250, 20, desktop );
#else
       ButtonWidget* button2 = new ButtonWidget( "We are rendered with GC", 25, 50, 250, 20, desktop );
#endif
       button2->Disable();



       WidgetApplication::AddChild( desktop );

       //WidgetApplication::SetUniformBackgroundColor( 0, 125, 125);
       WidgetApplication::SetBackgroundPicture( "/documents/Widget/Wallpapers/002.bmp.tns" );

       WidgetApplication::PrepareForRun();


       while (!WidgetApplication::AskForClosure() && !button->IsPressed()  )
       {
              WidgetApplication::Run( WidgetApplication::Normal );
       }

       WidgetApplication::Close();


       return 0;
}
