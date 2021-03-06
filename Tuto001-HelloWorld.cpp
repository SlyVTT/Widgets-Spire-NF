// This is the tuto #3
// We restart from previous status, just removed the comments

#include "ToolkitNF/GUIToolkitNF.hpp"

int main( void )
{
    WidgetApplication::Initialize();
    DesktopWidget *MyDesktop = new DesktopWidget( "Main Desktop", 0,0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, nullptr );

    WindowWidget *MyWindow = new WindowWidget( "I am the Main Window", 40, 40, 200, 100, MyDesktop );
    ContainerVWidget *VerticalContainer = new ContainerVWidget( " ", 1,1,1,1, MyWindow );
    LabelWidget *MyLabel = new LabelWidget( "Hello World !!!", 1,1,1,1, VerticalContainer );
    MyLabel->SetAlignment( LabelWidget::Centered );
    VerticalContainer->AddConstraint( 100, "%" );
    ContainerHWidget *HorizontalContainer = new ContainerHWidget( " ", 1,1,1,1, VerticalContainer );
    VerticalContainer->AddConstraint( 20, "px" );
    SpacerWidget *LeftSpacer = new SpacerWidget( " ", 1,1,1,1, HorizontalContainer );
    HorizontalContainer->AddConstraint( 50, "%" );
    ButtonWidget *MyButton = new ButtonWidget( "Quit !!!", 1,1,1,1, HorizontalContainer );
    HorizontalContainer->AddConstraint( 50, "px" );
    SpacerWidget *RightSpacer = new SpacerWidget( " ", 1,1,1,1, HorizontalContainer );
    HorizontalContainer->AddConstraint( 50, "%" );
    MyWindow->Adjust();

    //We will add a second window, with some other Widgets
    //And we will show how they can interact altogether
    //To save time, I will copy / paste some portions of code ..
    //Let's start

    WindowWidget *MySecondWindow = new WindowWidget( "I am the Second Window", 100, 100, 300, 200, MyDesktop );
    ContainerVWidget *VerticalContainer1 = new ContainerVWidget( " ", 1,1,1,1, MySecondWindow );
    LabelWidget *MyLabel1 = new LabelWidget( "Test of widgets", 1,1,1,1, VerticalContainer1 );
    MyLabel1->SetAlignment( LabelWidget::Centered );
    VerticalContainer1->AddConstraint( 25, "px" );  // The Label will be 25pixels high

    ContainerHWidget *HorizCont1 = new ContainerHWidget( "", 1,1,1,1, VerticalContainer1 );
    VerticalContainer1->AddConstraint( 25, "px" );  // The container (and hence its content) will also be 25pixels high
    RadioControlWidget *Radio = new RadioControlWidget( "I am a RadioControlWidget", 1,1,1,1, HorizCont1 );
    LabelWidget *Label2 = new LabelWidget( "Status Radio : ", 1,1,1,1, HorizCont1 );
    Label2->SetAlignment( LabelWidget::Right );

    ContainerHWidget *HorizCont2 = new ContainerHWidget( "", 1,1,1,1, VerticalContainer1 );
    VerticalContainer1->AddConstraint( 25, "px" );  // The container (and hence its content) will also be 25pixels high
    CheckBoxWidget *Check = new CheckBoxWidget( "I am a RadioControlWidget", 1,1,1,1, HorizCont2 );
    LabelWidget *Label3 = new LabelWidget( "Status Check : ", 1,1,1,1, HorizCont2 );
    Label3->SetAlignment( LabelWidget::Right );

    // The commuter widget is inverted, very easy to change
    ContainerHWidget *HorizCont3 = new ContainerHWidget( "", 1,1,1,1, VerticalContainer1 );
    VerticalContainer1->AddConstraint( 25, "px" );  // The container (and hence its content) will also be 25pixels high
    CommuterWidget *Commut = new CommuterWidget( "I am a CommuterWidget", 1,1,1,1, HorizCont3 );
    Commut->SetReversed();
    Commut->Invert();
    LabelWidget *Label4 = new LabelWidget( "Status Check : ", 1,1,1,1, HorizCont3 );
    Label4->SetAlignment( LabelWidget::Right );

    // Now we will add a progress bar that will be filled as per the previous control status

    SpacerWidget *SpacerTop = new SpacerWidget( "", 1,1,1,1, VerticalContainer1 );
    VerticalContainer1->AddConstraint( 50, "%" );
    ProgressBarWidget *PBar = new ProgressBarWidget( " ", 1,1,1,1, VerticalContainer1 );
    PBar->SetStyle( ProgressBarWidget::Continuous );
    PBar->SetPrintValue( true );
    VerticalContainer1->AddConstraint( 25, "px" );
    SpacerWidget *SpacerBottom = new SpacerWidget( "", 1,1,1,1, VerticalContainer1 );
    VerticalContainer1->AddConstraint( 50, "%" );

    MySecondWindow->Adjust();


    MyDesktop->Adjust();

    WidgetApplication::AddChild( MyDesktop );
    WidgetApplication::PrepareForRun();

    int a=0;
    int b=0;
    int c=0;

    while (!WidgetApplication::AskForClosure() && !MyButton->IsPressed())
    {
        WidgetApplication::Run( WidgetApplication::ForcedRender );

        a = Check->IsTicked() ? 33 : 0;
        b = Radio->IsTicked() ? 33 : 0;
        c = Commut->IsTicked() ? 34 : 0;

        PBar->SetCurrentPercentage( a+b+c );
    }

    WidgetApplication::Close();

    return 0;
}
