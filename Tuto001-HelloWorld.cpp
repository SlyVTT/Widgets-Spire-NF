#include "ToolkitNF/GUIToolkitNF.hpp"

int main( void )
{
    WidgetApplication::Initialize();
    DesktopWidget *MyDesktop = new DesktopWidget( "Main Desktop", 0,0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, nullptr );


    MenuBarWidget *MenuBarTop = new MenuBarWidget( "Main Menu Bar",1,1,1,1,MyDesktop );
    MenuItemWidget *FileMenuTop = new MenuItemWidget( "File",1,1,1,1,MenuBarTop );
        MenuPaneWidget *FileMenuPane = new MenuPaneWidget( "FilePaneMenu",1,1,1,1, FileMenuTop );
            MenuItemWidget *Open = new MenuItemWidget( "Open ...",1,1,1,1,FileMenuPane );
            MenuItemWidget *SaveAs = new MenuItemWidget( "Save As ...",1,1,1,1,FileMenuPane );
            MenuItemWidget *Save = new MenuItemWidget( "Save ...",1,1,1,1,FileMenuPane );
            SpacerWidget *SpaceMenuFile = new SpacerWidget( "",1,1,1,1,FileMenuPane );
            MenuItemWidget *Exit = new MenuItemWidget( "Exit ...",1,1,1,1,FileMenuPane );

    MenuItemWidget *EditMenuTop = new MenuItemWidget( "Edit",1,1,1,1,MenuBarTop );
        MenuPaneWidget *EditMenuPane = new MenuPaneWidget( "EditPaneMenu",1,1,1,1, EditMenuTop );
            MenuItemWidget *Copy = new MenuItemWidget( "Copy",1,1,1,1,EditMenuPane );
            MenuItemWidget *Cut = new MenuItemWidget( "Cut",1,1,1,1,EditMenuPane );
            MenuItemWidget *Paste = new MenuItemWidget( "Paste",1,1,1,1,EditMenuPane );
            MenuItemWidget *Delete = new MenuItemWidget( "Delete",1,1,1,1,EditMenuPane );

    MenuItemWidget *ViewMenuTop = new MenuItemWidget( "View",1,1,1,1,MenuBarTop );
        MenuPaneWidget *ViewMenuPane = new MenuPaneWidget( "ViewPaneMenu",1,1,1,1, ViewMenuTop );
            MenuItemWidget *ZoomIn = new MenuItemWidget( "Zoom In",1,1,1,1,ViewMenuPane );
            MenuItemWidget *ZoomOut = new MenuItemWidget( "Zoom Out",1,1,1,1,ViewMenuPane );
            MenuItemWidget *ZoomValue = new MenuItemWidget( "Zoom at ...",1,1,1,1,ViewMenuPane );
                MenuPaneWidget *ZoomValueMenuPane = new MenuPaneWidget( "ViewPaneMenu",1,1,1,1, ZoomValue );
                    MenuItemWidget *Zoom010 = new MenuItemWidget( "10%",1,1,1,1,ZoomValueMenuPane );
                    MenuItemWidget *Zoom025 = new MenuItemWidget( "25%",1,1,1,1,ZoomValueMenuPane );
                    MenuItemWidget *Zoom050 = new MenuItemWidget( "50%",1,1,1,1,ZoomValueMenuPane );
                    MenuItemWidget *Zoom075 = new MenuItemWidget( "75%",1,1,1,1,ZoomValueMenuPane );
                    MenuItemWidget *Zoom100 = new MenuItemWidget( "100%",1,1,1,1,ZoomValueMenuPane );
                    MenuItemWidget *ZoomOther = new MenuItemWidget( "Other ...",1,1,1,1,ZoomValueMenuPane );
                        MenuPaneWidget *ZoomValueOtherMenuPane = new MenuPaneWidget( "ViewPaneMenu",1,1,1,1, ZoomOther );
                            MenuItemWidget *Zoom010A = new MenuItemWidget( "10%",1,1,1,1,ZoomValueOtherMenuPane );
                            MenuItemWidget *Zoom025A = new MenuItemWidget( "25%",1,1,1,1,ZoomValueOtherMenuPane );
                            MenuItemWidget *Zoom050A = new MenuItemWidget( "50%",1,1,1,1,ZoomValueOtherMenuPane );
                            MenuItemWidget *Zoom075A = new MenuItemWidget( "75%",1,1,1,1,ZoomValueOtherMenuPane );
                            MenuItemWidget *Zoom100A = new MenuItemWidget( "100%",1,1,1,1,ZoomValueOtherMenuPane );
                            MenuItemWidget *ZoomOtherA = new MenuItemWidget( "Other ...",1,1,1,1,ZoomValueOtherMenuPane );
            MenuItemWidget *ZoomFit = new MenuItemWidget( "Zoom Fit",1,1,1,1,ViewMenuPane );



    WindowWidget *MyWindow = new WindowWidget( "I am the Main Window", 40, 240, 200, 100, MyDesktop );
    ContainerVWidget *VerticalContainer = new ContainerVWidget( " ", 1,1,1,1, MyWindow );
    LabelWidget *MyLabel = new LabelWidget( "Hello World !!!", 1,1,1,1, VerticalContainer );
    MyLabel->SetAlignment( LabelWidget::Centered );
    ButtonWidget *MyButton = new ButtonWidget( "Quit !!!", 1,1,1,1, VerticalContainer );
    MyWindow->Adjust();


    WindowWidget *MyWindow2 = new WindowWidget( "I am another Window", 100, 300, 200, 100, MyDesktop );
    ContainerVWidget *VerticalContainer2 = new ContainerVWidget( " ", 1,1,1,1, MyWindow2 );
    LabelWidget *MyLabel2 = new LabelWidget( "Second Example of using GUI Toolkit NF", 1,1,1,1, VerticalContainer2 );
    MyLabel2->SetAlignment( LabelWidget::Centered );
    ContainerHWidget *HorizontalContainer = new ContainerHWidget( " ", 1,1,1,1, VerticalContainer2 );
    SpacerWidget *LeftSpacer = new SpacerWidget( " ", 1,1,1,1, HorizontalContainer );
    ButtonWidget *MyButtonCentered = new ButtonWidget( "Test", 1,1,1,1, HorizontalContainer );
    SpacerWidget *RightSpacer = new SpacerWidget( " ", 1,1,1,1, HorizontalContainer );
    MyWindow2->Adjust();

/*
    ContainerHWidget *MainContainer = new ContainerHWidget("",1,1,1,1,MyDesktop);
    ButtonWidget *Test1 = new ButtonWidget("Left",1,1,1,1,MainContainer);
    MainContainer->AddConstraint(80,"%");
    ButtonWidget *Test2 = new ButtonWidget("Right",1,1,1,1,MainContainer);
    MainContainer->AddConstraint(20,"%");
*/

    MyDesktop->Adjust();

    WidgetApplication::AddChild( MyDesktop );
    WidgetApplication::PrepareForRun();

    while (!WidgetApplication::AskForClosure() && !MyButton->IsPressed() && !Exit->IsPressed())
    {
        WidgetApplication::Run( WidgetApplication::ForcedRender );
    }

    WidgetApplication::Close();

    return 0;
}
