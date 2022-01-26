#include "ToolkitNF/GUIToolkitNF.hpp"


int main ( int argc, char **argv )
{

    WidgetApplication::Initialize();


#if DEBUG_MODE == 1
    Debugger::Initialize();
    Debugger::SetDebuggerFile( "/documents/Widget/DebugOut/Crash.txt.tns" );
    Debugger::TimerLog( "WidgetApplication Initialized \n");
#endif // DEBUG_MODE

#if TARGET_NSPIRE == 1
    WidgetApplication::SetBackgroundPicture( "/documents/Widget/Wallpapers/002.bmp.tns" );
#else
    WidgetApplication::SetBackgroundPicture( "/documents/Widget/Wallpap_PC/waterbub.bmp" );
#endif // TARGET_NSPIRE

    DesktopWidget *desktop = new DesktopWidget( "Desktop", 0, 0, SCREEN_WIDTH_GUI, SCREEN_HEIGHT_GUI, nullptr );

//-----------------------------------------



    WindowWidget *window = new WindowWidget(  "Simple Text Editor for TI nSpire v1.0", 40, 40, 260, 180, desktop );
    //window->Maximize();
    //window->SetMinimalDimensions( 320, 240 );    // This prevent resizing of the window


    MenuBarWidget *bardesk = new MenuBarWidget(  "Main Menu", 1,1,1,1, desktop );
    MenuItemWidget *mainmenufile = new MenuItemWidget(  "File", 1,1,1,1, bardesk );
    MenuPaneWidget *paneFile = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile );
    MenuItemWidget *FileOpen = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile );
    MenuItemWidget *FileSave = new MenuItemWidget(  "Save", 1,1,1,1, paneFile );
    MenuItemWidget *FileSaveAs = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile );
    SpacerWidget *spacer1 = new SpacerWidget(" ", 1,1,1,1, paneFile );
    MenuItemWidget *FileClose = new MenuItemWidget(  "Close", 1,1,1,1, paneFile );

    MenuItemWidget *mainmenuedit = new MenuItemWidget(  "Edit", 1,1,1,1, bardesk );
    MenuPaneWidget *paneEdit = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit );
    MenuItemWidget *EditCopy = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit );
    MenuItemWidget *EditCut = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit );
    MenuItemWidget *EditPaste = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit );
    MenuItemWidget *EditErase = new MenuItemWidget(  "Erase", 1,1,1,1, paneEdit );

    MenuItemWidget *mainmenuTest = new MenuItemWidget(  "Test", 1,1,1,1, bardesk );
    MenuPaneWidget *paneTest = new MenuPaneWidget(  "Test", 1,1,1,1, mainmenuTest );
    MenuItemWidget *Test1 = new MenuItemWidget(  "Test1", 1,1,1,1, paneTest );
    MenuPaneWidget *paneTest1 = new MenuPaneWidget(  "Test1", 1,1,1,1, Test1 );
    MenuItemWidget *Test11 = new MenuItemWidget(  "Test1.1", 1,1,1,1, paneTest1 );
    MenuItemWidget *Test12 = new MenuItemWidget(  "Test1.2", 1,1,1,1, paneTest1 );
    MenuItemWidget *Test2 = new MenuItemWidget(  "Test2", 1,1,1,1, paneTest );
    MenuItemWidget *Test3 = new MenuItemWidget(  "Test3", 1,1,1,1, paneTest );

    MenuItemWidget *mainmenuHelp = new MenuItemWidget(  "Help", 1,1,1,1, bardesk );
    MenuPaneWidget *paneHelp = new MenuPaneWidget(  "Help", 1,1,1,1, mainmenuHelp );
    MenuItemWidget *HelpFile = new MenuItemWidget(  "View Help File ...", 1,1,1,1, paneHelp );
    MenuItemWidget *HelpKeyb = new MenuItemWidget(  "View Keyboard Layout ...", 1,1,1,1, paneHelp );
    MenuItemWidget *HelpAbout = new MenuItemWidget(  "About ...", 1,1,1,1, paneHelp );


    IconBarWidget *baricon = new IconBarWidget(  "I am the main Bar Icon", 1,1,1,1, desktop );
    IconItemWidget *iconNew = new IconItemWidget(  "N", 1,1,1,1, baricon );
    iconNew->AssignIconEnable(  "/documents/Widget/Icons/New document.bmp.tns" );
    iconNew->AssignIconDisable(  "/documents/Widget/Icons/gr_New document.bmp.tns" );

    SpacerWidget *spacer2 = new SpacerWidget(" ", 1,1,1,1, baricon );

    IconItemWidget *iconCopy = new IconItemWidget(  "C", 1,1,1,1, baricon );
    iconCopy->AssignIconEnable(  "/documents/Widget/Icons/Copy.bmp.tns" );
    iconCopy->AssignIconDisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
    IconItemWidget *iconCut = new IconItemWidget(  "X", 1,1,1,1, baricon );
    iconCut->AssignIconEnable(  "/documents/Widget/Icons/Cut.bmp.tns" );
    iconCut->AssignIconDisable(  "/documents/Widget/Icons/gr_Cut.bmp.tns" );
    IconItemWidget *iconPaste = new IconItemWidget(  "P", 1,1,1,1, baricon );
    iconPaste->AssignIconEnable(  "/documents/Widget/Icons/Paste.bmp.tns" );
    iconPaste->AssignIconDisable(  "/documents/Widget/Icons/gr_Paste.bmp.tns" );
    IconItemWidget *iconErase = new IconItemWidget(  "E", 1,1,1,1, baricon );
    iconErase->AssignIconEnable(  "/documents/Widget/Icons/Erase.bmp.tns" );
    iconErase->AssignIconDisable(  "/documents/Widget/Icons/gr_Erase.bmp.tns" );


    ContainerVWidget *containervert = new ContainerVWidget( "Main container", 1,1,1,1, window );

    MultiLineRichTextBoxWidget *multiline = new MultiLineRichTextBoxWidget( "The Editor Text Box", 1,1,1,1, containervert );
    multiline->LoadContentFromFile( "/documents/Widget/Texts/manual.hlp.tns" );
    //multiline->SetNonEditable();

    //MultiLineTextBoxWidget *multiline2 = new MultiLineTextBoxWidget( "The Editor Text Box", 1,1,1,1, containervert );
    //multiline2->LoadContentFromFile(  "/documents/Widget/Texts/longtext.txt.tns" );
    //multiline2->SetNonEditable();


    WindowWidget *window1 = new WindowWidget(  "GUI Toolkit for nSpire rev 0.75 Demo", 45, 35, 240, 190, desktop );
    window1->SetMinimalDimensions( 90, 75 );

    MenuBarWidget *barwin1 = new MenuBarWidget(  "Main Menu",1,1,1,1, window1 );
    MenuItemWidget *mainmenufile1 = new MenuItemWidget(  "File", 1,1,1,1, barwin1 );
    MenuItemWidget *mainmenuedit1 = new MenuItemWidget(  "Edit", 1,1,1,1, barwin1 );
    MenuItemWidget *mainmenuView1 = new MenuItemWidget(  "View", 1,1,1,1, barwin1 );
    MenuItemWidget *mainmenuSearch1 = new MenuItemWidget(  "Search", 1,1,1,1, barwin1 );
    MenuPaneWidget *paneFile1 = new MenuPaneWidget(  "File", 1,1,1,1, mainmenufile1 );
    MenuItemWidget *FileOpen1 = new MenuItemWidget(  "Open ...", 1,1,1,1, paneFile1 );
    MenuItemWidget *FileSave1 = new MenuItemWidget(  "Save", 1,1,1,1, paneFile1 );
    MenuItemWidget *FileSaveAs1 = new MenuItemWidget(  "Save As ...", 1,1,1,1, paneFile1 );
    MenuItemWidget *FilePrint1 = new MenuItemWidget(  "Print ...", 1,1,1,1, paneFile1 );
    MenuItemWidget *FileClose1 = new MenuItemWidget(  "Close", 1,1,1,1, paneFile1 );
    MenuPaneWidget *paneEdit1 = new MenuPaneWidget(  "Edit", 1,1,1,1, mainmenuedit1 );
    MenuItemWidget *EditUndo1 = new MenuItemWidget(  "Undo", 1,1,1,1, paneEdit1 );
    MenuItemWidget *EditRedo1 = new MenuItemWidget(  "Redo", 1,1,1,1, paneEdit1 );
    MenuItemWidget *EditCopy1 = new MenuItemWidget(  "Copy", 1,1,1,1, paneEdit1 );
    MenuItemWidget *EditCut1 = new MenuItemWidget(  "Cut", 1,1,1,1, paneEdit1 );
    MenuItemWidget *EditPaste1 = new MenuItemWidget(  "Paste", 1,1,1,1, paneEdit1 );
    MenuPaneWidget *paneView1 = new MenuPaneWidget(  "View", 1,1,1,1, mainmenuView1 );
    MenuItemWidget *ViewZoomPlus1 = new MenuItemWidget(  "Zoom +", 1,1,1,1, paneView1 );
    MenuItemWidget *ViewZoomMinus1 = new MenuItemWidget(  "Zoom -", 1,1,1,1, paneView1 );
    MenuItemWidget *ViewZoomSelect1 = new MenuItemWidget(  "Select", 1,1,1,1, paneView1 );
    MenuItemWidget *ViewZoomFit1 = new MenuItemWidget(  "Fit All", 1,1,1,1, paneView1 );
    MenuItemWidget *ViewZomeMax1 = new MenuItemWidget(  "Zoom Max", 1,1,1,1, paneView1 );
    MenuItemWidget *ViewZomeMin1 = new MenuItemWidget(  "Zoom Min", 1,1,1,1, paneView1 );
    MenuPaneWidget *paneZoomSelect1 = new MenuPaneWidget(  "Zoom Select", 1,1,1,1, ViewZoomSelect1 );
    MenuItemWidget *ViewZoomSelect101 = new MenuItemWidget(  "10%", 1,1,1,1, paneZoomSelect1 );
    MenuItemWidget *ViewZoomSelect251 = new MenuItemWidget(  "25%", 1,1,1,1, paneZoomSelect1 );
    MenuItemWidget *ViewZoomSelect501 = new MenuItemWidget(  "50%", 1,1,1,1, paneZoomSelect1 );
    MenuItemWidget *ViewZoomSelect751 = new MenuItemWidget(  "75%", 1,1,1,1, paneZoomSelect1 );
    MenuItemWidget *ViewZoomSelect1001 = new MenuItemWidget(  "100%", 1,1,1,1, paneZoomSelect1 );
    MenuItemWidget *ViewZoomSelect1501 = new MenuItemWidget(  "150%", 1,1,1,1, paneZoomSelect1 );
    MenuPaneWidget *paneSearch1 = new MenuPaneWidget(  "Search", 1,1,1,1, mainmenuSearch1 );
    MenuItemWidget *SearchFindHere1 = new MenuItemWidget(  "Find Here ...", 1,1,1,1, paneSearch1 );
    MenuItemWidget *SearchFindAll1 = new MenuItemWidget(  "Find All Files ...", 1,1,1,1, paneSearch1 );
    MenuItemWidget *SearchReplace1 = new MenuItemWidget(  "Replace ...", 1,1,1,1, paneSearch1 );

    IconBarWidget *baricon1 = new IconBarWidget(  "M", 1,1,1,1, window1 );
    IconItemWidget *iconfile1 = new IconItemWidget(  "F", 1,1,1,1, baricon1 );
    iconfile1->AssignIconEnable(  "/documents/Widget/Icons/Folder.bmp.tns" );
    iconfile1->AssignIconDisable(  "/documents/Widget/Icons/gr_Folder.bmp.tns" );
    IconItemWidget *iconedit1 = new IconItemWidget(  "E", 1,1,1,1, baricon1 );
    iconedit1->AssignIconEnable(  "/documents/Widget/Icons/Copy.bmp.tns" );
    iconedit1->AssignIconDisable(  "/documents/Widget/Icons/gr_Copy.bmp.tns" );
    IconItemWidget *iconview1 = new IconItemWidget(  "V", 1,1,1,1, baricon1 );
    iconview1->AssignIconEnable(  "/documents/Widget/Icons/Pie chart.bmp.tns" );
    iconview1->AssignIconDisable(  "/documents/Widget/Icons/gr_Pie chart.bmp.tns" );
    IconItemWidget *iconsearch1 = new IconItemWidget(  "S", 1,1,1,1, baricon1 );
    iconsearch1->AssignIconEnable(  "/documents/Widget/Icons/Save.bmp.tns" );
    iconsearch1->AssignIconDisable(  "/documents/Widget/Icons/gr_Save.bmp.tns" );
    IconItemWidget *iconproject1 = new IconItemWidget(  "P", 1,1,1,1, baricon1 );
    iconproject1->AssignIconEnable(  "/documents/Widget/Icons/Schedule.bmp.tns" );
    iconproject1->AssignIconDisable(  "/documents/Widget/Icons/gr_Schedule.bmp.tns" );

    ContainerVWidget *containervert1 = new ContainerVWidget( "container", 1, 1, 1, 1, window1 );

    LabelWidget *label1 = new LabelWidget( "Please pick a theme for the Toolkit : ", 1, 1, 1, 1, containervert1 );
    label1->SetAlignment( LabelWidget::Left );
    DropBoxWidget *mydropbox = new DropBoxWidget( "Test Drop", 1, 1, 1, 1, containervert1 );
    LabelWidget *label2 = new LabelWidget(  "This is an InputBox", 1, 1, 1, 1, containervert1 );
    label2->SetAlignment( LabelWidget::Left );
    InputWidget *input = new InputWidget( "I am an Inputbox", 1, 1, 1, 1, containervert1 );
    input->SetContent( (char *) "Please enter something here !!!" );
    LabelWidget *label3 = new LabelWidget( "Some Radio/Checkbox examples", 1, 1, 1, 1, containervert1 );
    label3->SetAlignment( LabelWidget::Left );
    CheckBoxWidget *check = new CheckBoxWidget(  "I am a CheckBox", 1, 1, 1, 1, containervert1 );
    RadioControlWidget *radio = new RadioControlWidget( "I am a RadioControl", 1, 1, 1, 1, containervert1 );
    //    LabelWidget *label4 = new LabelWidget(  "ProgressBars (use + and - keys)", 1, 1, 1, 1, containervert1 );
    //    label4->setalignment( left );
    //    ContainerHWidget *contH5 = new ContainerHWidget(  "container", 1, 1, 1, 1, containervert1 );
    //    ProgressBarWidget *bar = new ProgressBarWidget(  "ProgressBar", 1, 1, 1, 1, contH5 );
    //    bar->setstyle( Continuous );
    //    bar->setprintvalue( true );
    //    ProgressBarWidget *bars = new ProgressBarWidget(  "ProgressBar", 1, 1, 1, 1, contH5 );
    //    bars->setstyle( Bricks );
    //    bars->setnumberbricks( 10 );
    //    bars->setprintvalue( true );
    ContainerHWidget *containerH = new ContainerHWidget( "containerH", 1, 1, 1, 1, containervert1 );
    SpacerWidget *spacer1H = new SpacerWidget( "Spacer1", 1, 1, 1, 1, containerH );
    ButtonWidget *buttonQuit = new ButtonWidget( "Quit !!", 1, 1, 1, 1, containerH );
    SpacerWidget *spacer2H = new SpacerWidget( "Spacer2", 1, 1, 1, 1, containerH );
    // We fill the list of the dropbox with items to be selectable by the user
    mydropbox->AddItem(  "Default GUI Toolkit Theme" );
    mydropbox->AddItem(  "Bright GUI Toolkit Theme" );
    mydropbox->AddItem(  "Dark GUI Toolkit Theme" );
    mydropbox->AddItem(  "Hyrule GUI Toolkit Theme" );
    // We ask for an automatic positioning of the widgets in the grid
    // Note : this will fully override the dimensions given to the Widgets manually

    window1->Adjust();



    desktop->Adjust();


    SplashScreenWidget *splash = new SplashScreenWidget("Splash", 1, 1, 1, 1, nullptr );
    splash->AssignImage( "/documents/Widget/Logos/Logo Simple Text Editor.bmp.tns" );
    desktop->AddPopupChild(splash);
    splash->SetDuration( 3000 );    // splash screen will appear 3000ms = 3 seconds

/*
//--------------------------------------------------------------------------------


//--------------------------------------------------
// WE CREATE THE KEYBOARD LAYOUT HELP BOX


        WindowWidget *keyboardhelpwin = new WindowWidget("Help : Keyboard Layout",5,5, 310, 230, desktop );
            ContainerVWidget *contverthelpkeyb = new ContainerVWidget( "Main container", 1,1,1,1, keyboardhelpwin );
                GraphicContextWidget *keyboardimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, contverthelpkeyb);

                    SDL_Surface *image2 = IMG_Load( "/documents/Widget/Logos/KeyboardLayout.bmp.tns" );
                    keyboardimage->AssignSurface( image2 );
                    keyboardimage->SetUserZoomLevel(0.95f);
                    contverthelpkeyb->AddConstraint(185, "px");

                    ContainerHWidget *conthorithelpkeyb = new ContainerHWidget( "Sub container", 1,1,1,1, contverthelpkeyb );
                    contverthelpkeyb->AddConstraint(100, "%");

                        SpacerWidget *spacerhelpleft = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpkeyb );
                        conthorithelpkeyb->AddConstraint(50, "%");
                        ButtonWidget *OKbuttonhelp = new ButtonWidget( "OK",1,1,1,1, conthorithelpkeyb);
                        conthorithelpkeyb->AddConstraint(50, "px");
                        SpacerWidget *spacerhelpright = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpkeyb );
                        conthorithelpkeyb->AddConstraint(50, "%");

        keyboardhelpwin->Adjust();
        keyboardhelpwin->SetInvisible();
    //--------------------------------------------------


//--------------------------------------------------
// WE CREATE THE ABOUT HELP BOX


        WindowWidget *abouthelpwin = new WindowWidget("Help : About ...",5,25, 310, 210, desktop );
            ContainerVWidget *contverthelpabout = new ContainerVWidget( "Main container", 1,1,1,1, abouthelpwin );
           ContainerHWidget *aboutsplit = new ContainerHWidget( "Main container", 1,1,1,1, contverthelpabout );
                contverthelpabout->AddConstraint(100, "px");

                    GraphicContextWidget *aboutimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, aboutsplit);
                    SDL_Surface *image3 = IMG_Load( "/documents/Widget/Logos/Logo Simple Text Editor.bmp.tns" );
                    aboutimage->AssignSurface( image3 );
                    aboutimage->SetUserZoomLevel(0.5f);
                    aboutsplit->AddConstraint(150, "px");

                    MultiLineRichTextBoxWidget *textabout = new MultiLineRichTextBoxWidget("Text About",1,1,1,1, aboutsplit);
                    textabout->AppendContent("#1Simple Text Editor#0 v1.0 \n Proudly coded by #3SlyVTT#0 \n using the \n #1GUI Toolkit for TI nSpire#0");
                    aboutsplit->AddConstraint(100, "%");

                GraphicContextWidget *GUIimage = new GraphicContextWidget( "Keyboard image", 1, 1,1,1, contverthelpabout);
                SDL_Surface *image4 = IMG_Load( "/documents/Widget/Logos/Logo Master White 300.bmp.tns" );
                GUIimage->AssignSurface( image4 );
                GUIimage->SetUserZoomLevel(1.0f);
                contverthelpabout->AddConstraint(115, "px");

                MultiLineTextBoxWidget *textabout2 = new MultiLineTextBoxWidget("Text About",1,1,1,1, contverthelpabout);
                textabout2->AppendContent( "Welcome to the Simple Text Editor v1.0 made \n with the GUI Toolkit for TI nSPire. " );
                textabout2->AppendContent( "Copyright SlyVTT (2021). " );
                textabout2->AppendContent( "Please visit : \n github.coom/SlyVTT/Widget-for-TI-NSpire ");
                contverthelpabout->AddConstraint(100, "%");

                ContainerHWidget *conthorithelpabout = new ContainerHWidget( "Sub container", 1,1,1,1, contverthelpabout );
                contverthelpabout->AddConstraint(20, "px");

                    SpacerWidget *spacerhelpleft1 = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpabout );
                    conthorithelpabout->AddConstraint(50, "%");
                    ButtonWidget *OKbuttonabout = new ButtonWidget( "OK",1,1,1,1, conthorithelpabout);
                    conthorithelpabout->AddConstraint(50, "px");
                    SpacerWidget *spacerhelpright1 = new SpacerWidget( "Spacer left",1,1,1,1,conthorithelpabout );
                    conthorithelpabout->AddConstraint(50, "%");

        abouthelpwin->Adjust();
        abouthelpwin->SetInvisible();
    //--------------------------------------------------

*/


    WindowWidget *window6 = new WindowWidget( "Test of GraphicContextWidget", 10, 55, 400, 200, desktop );
    window6->SetMinimalDimensions( 100, 100 );
    ContainerVWidget *containergraphic = new ContainerVWidget( "container", 1, 1, 1, 1, window6 );
    GraphicContextWidget *graphic = new GraphicContextWidget( "Graphic Context", 1, 1, 1, 1, containergraphic );
    SDL_Surface *image = graphic->CreateEmptyImage(320,240);        //IMG_Load( "/documents/Widget/Logos/Logo Master White 300.bmp.tns" );
    graphic->AssignSurface( image );
    //graphic->setuserzoomlevel(1.0f);
    //graphic->update();
    //graphic->SetMode( GraphicContextWidget::FitBest );
    window6->Adjust();


    circleRGBA( image, 160, 120, 75, 255, 255, 255, 255);
    filledCircleRGBA( image, 160, 85, 50, 255, 0, 0, 128);
    filledCircleRGBA( image, 130, 130, 50, 0, 255, 0, 128);
    filledCircleRGBA( image, 190, 130, 50, 0, 0, 255, 128);
    SDL_Flip( image );


    WindowWidget *window7 = new WindowWidget( "Test of GraphicContextWidget", 150, 55, 400, 300, desktop );
    window7->SetMinimalDimensions( 300, 200 );
    ContainerVWidget *containergraphic2 = new ContainerVWidget( "container", 1, 1, 1, 1, window7 );
    GraphicContextWidget *graphic2 = new GraphicContextWidget( "Graphic Context", 1, 1, 1, 1, containergraphic2 );


    SDL_Surface *image5 = IMG_Load( "/documents/Widget/Logos/Logo Master Black 300.bmp.tns" );
    graphic2->AssignSurface( image5 );
    //graphic2->setuserzoomlevel(1.0f);
    //graphic2->update();
    //graphic2->SetMode( GraphicContextWidget::FitBest );
    window7->Adjust();


    FileDialogBoxWidget *filedialog = new FileDialogBoxWidget( "Open/Save", 100,40, 300, 190, desktop );
    filedialog->SetDialogType( FileDialogBoxWidget::FileOpen );
    filedialog->SetInvisible();




    WidgetApplication::AddChild( desktop );

    WidgetApplication::PrepareForRun();

    splash->Start();


//      unsigned int imageKeybtoshow = 1;
//        SDL_Surface *image = nullptr;


    while (!WidgetApplication::AskForClosure() && !FileClose->IsPressed()  )
    {

        WidgetApplication::Run( WidgetApplication::ForcedRender );

        if (EditCopy->IsPressed() || iconCopy->IsPressed())
        {
            multiline->CopySelection();
        }
        if (EditCut->IsPressed() || iconCut->IsPressed())
        {
            multiline->CutSelection();
        }
        if (EditPaste->IsPressed() || iconPaste->IsPressed())
        {
            multiline->PasteSelection();
        }
        if (EditErase->IsPressed() || iconErase->IsPressed())
        {
            multiline->EraseSelection();
        }

        if (iconNew->IsPressed())
        {
            multiline->Flush();
        }

        if (mydropbox->IsUpdated() && (mydropbox->GetSelected()!=-1))
        {
            if (mydropbox->GetSelected() == 0)
            {
                // We reset the theme to default
                WidgetApplication::SetDefaultTheme();
            }
            if (mydropbox->GetSelected() == 1)
            {
                // We load a theme file and aply it on-the-fly
                // the theme NrmClr.CFG.tns is the default theme
                WidgetApplication::LoadTheme(  "/documents/Widget/Themes/NrmClr.CFG.tns" );
            }
            if (mydropbox->GetSelected() == 2)
            {
                // We load a theme file and aply it on-the-fly
                // the theme DrkClr.CFG.tns is the dark theme
                WidgetApplication::LoadTheme(  "/documents/Widget/Themes/DrkClr.CFG.tns" );
            }
            if (mydropbox->GetSelected() == 3)
            {
                // We load a theme file and aply it on-the-fly
                // the theme Hyrule.CFG.tns is the theme used is the LinkSDL example (put in a theme file)
                WidgetApplication::LoadTheme(  "/documents/Widget/Themes/Hyrule.CFG.tns" );
            }
        }

        if (FileOpen->IsPressed())
        {
            filedialog->Reset();
            filedialog->SetDialogType( FileDialogBoxWidget::FileOpen );
            //filedialog->validated = false;
            //filefiledialog->canceled = false;
            filedialog->SetVisible();
        }

        if (filedialog->IsValidated())
        {
            filedialog->Reset();
            input->Flush();
            input->SetContent( filedialog->GetSelectedFullname().c_str());

            //filedialog->validated = false;
            //filedialog->canceled = false;
            //filedialog->SetInvisible();
        }
/*
                if (HelpKeyb->IsPressed())
                {
                    multiline->AppendContent( "Keyboard Layout Help Menu  pressed \n" );
                    WidgetApplication::PutOnTop( keyboardhelpwin );
                    keyboardhelpwin->SetVisible();
                }

                if (keyboardhelpwin->IsVisible() && OKbuttonhelp->IsPressed())
                {
                    keyboardhelpwin->SetInvisible();
                }

                if (HelpAbout->IsPressed())
                {
                    multiline->AppendContent( "About Help Menu \n" );
                    WidgetApplication::PutOnTop( abouthelpwin );
                    abouthelpwin->SetVisible();
                }

                if (abouthelpwin->IsVisible() && OKbuttonabout->IsPressed())
                {
                    abouthelpwin->SetInvisible();
                }
*/
    }

    SDL_FreeSurface( image );
    SDL_FreeSurface( image5 );


#if DEBUG_MODE == 1
    Debugger::TimerLog( "WidgetApplication Ready to ShutDown ...\n");
#endif // DEBUG_MODE

    WidgetApplication::Close();

#if DEBUG_MODE == 1
    Debugger::TimerLog( "WidgetApplication Closed \n");
#endif // DEBUG_MODE


#if DEBUG_MODE == 1
    Debugger::TimerLog( "Will close debugger and exit.\n");
    Debugger::Close();
#endif // DEBUG_MODE


    return 0;

}


