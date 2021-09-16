#include "Widget.hpp"

#include "../Globals/GlobalFunctions.hpp"
#include "../Globals/GUIToolkitNFGlobals.hpp"
#if DEBUG_MODE == 1
    #include "../Debugger/Debugger.hpp"
#endif // DEBUG_MODE


#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/DepthBufferRenderer.hpp"
#include "../Engines/FontEngine.hpp"
#include "../Renderers/ScreenRenderer.hpp"


unsigned int GlobalWidgetIDCounter;



Widget* Widget::GetClosestMainParent()
{


    Widget* temp = this;
    Widget* temp2=nullptr;

    /*
        FILE *pFile;

        pFile = fopen( "/documents/Widget/closepar.txt.tns", "a" );
        fprintf( pFile, "Enter the GetClosestParent Loop \n" );
        fprintf( pFile, "widgetID = %ld \n", this->WidgetID );
    */


    if (( this->GetWidgetType() == "Desktop" ) || ( this->GetWidgetType() == "Window" ))
    {
        //     fprintf( pFile, "This is me = %ld \n", this->WidgetID );
        //     fclose( pFile );
        return this;
    }
    else
    {
        //    fprintf( pFile, "go to my parent \n" );
        temp = this->parent;
        while (temp!=nullptr)
        {
            if (( temp->GetWidgetType() == "Desktop" ) || (temp->GetWidgetType() == "Window" ))
            {
                //            fprintf( pFile, "This is me = %ld \n", temp->WidgetID );
                //            fclose( pFile );
                return temp;
            }
            else
            {
                //            fprintf( pFile, "go to my grand-parent \n" );
                temp2=temp;
                temp = temp2->parent;
            }
        }

        //    fprintf( pFile, "Houston, we have a problem !! \n" );
        //    fclose( pFile );

        return nullptr;
    }
};


Widget* Widget::GetWidgetByID( uint32_t IDsearched )
{
    if (IDsearched>=GlobalWidgetIDCounter)  return nullptr;
    if (this->WidgetID == IDsearched)
    {
        // we are lucky, we are on the widget we are looking for
        return this;
    }
    else
    {
        if (children.size()!=0)
            for( auto&c : children)
                c->GetWidgetByID( IDsearched );
    }
    return nullptr;
};

/*
void Widget::DEBUG_draw_widget_tree_structure( int level, char* filename )
{

    FILE *pFile;

    pFile = fopen( filename, "a" );
    if (pFile==NULL)
    {
        return;
    }

    for( int i=0; i<level; i++ )
    {
        fprintf( pFile, "| " );
    }

    fprintf( pFile, "_ " );

    if (parent!=nullptr)
        fprintf( pFile, " ID = %ld : Type = %s : Name = %s | Parent (ID= %ld , Tp= %s) | Nb Children = %d | Nb PopUpChildren = %d | Ultimate Patent : ID = %ld - Type = %s \n", WidgetID, GetWidgetType(), getlabel(), parent->WidgetID, parent->GetWidgetType(), children.size(), popupchildren.size(), getclosestmainparent()->WidgetID, getclosestmainparent()->GetWidgetType() );
    else
        fprintf( pFile, " ID = %ld : Type = %s : Name = %s | Parent (ID= %ld , Tp= %s) | Nb Children = %d | Nb PopUpChildren = %d | Ultimate Patent : ID = %ld - Type = %s \n", WidgetID, GetWidgetType(), getlabel(), -1, (char*) "NULL_NOP", children.size(), popupchildren.size(), getclosestmainparent()->WidgetID,  (char*) "NULL_NOP" );

    fclose( pFile );


    if (children.size()!=0)
        for( auto& c : children )
            c->DEBUG_draw_widget_tree_structure( level+1, filename );

    if (popupchildren.size()!=0)
        for( auto& c : popupchildren )
            c->DEBUG_draw_widget_tree_structure( level+1, filename );

}
*/


void Widget::SetDimensions( unsigned int mx, unsigned int my, unsigned int mw, unsigned int mh )
{
    xpos=mx;
    ypos=my;
    width=mw;
    height=mh;
};

void Widget::SetXPos( unsigned int mx )
{
    xpos=mx;
};

void Widget::SetYPos( unsigned int my )
{
    ypos=my;
};

void Widget::SetWidth( unsigned int mw )
{
    width=mw;
};

void Widget::SetHeight( unsigned int mh )
{
    height=mh;
};

void Widget::SetLabel(std::string l)
{
    label = l;
};

void Widget::SetContainerStatus( bool status )
{
    is_container = status;
};

unsigned int Widget::GetXPos()
{
    return xpos;
};

unsigned int Widget::GetYPos()
{
    return ypos;
};

unsigned int Widget::GetWidth()
{
    return width;
};

unsigned int Widget::GetHeight()
{
    return height;
};

unsigned int Widget::GetUseableXPos()
{
    return xpos + 2 ;
};

unsigned int Widget::GetUseableYPos()
{
    return ypos + 2 ;
};

unsigned int Widget::GetUseableWidth()
{
    return width - 4;
};

unsigned int Widget::GetUseableHeight()
{
    return height - 4;
};

std::string Widget::GetLabel()
{
    return label;
};

bool Widget::GetContainerStatus()
{
    return is_container;
};

Widget* Widget::GetParent()
{
    return parent;
};

bool Widget::IsEnabled()
{
    return is_enabled;
};

bool Widget::IsVisible()
{
    return is_visible;
};

std::string Widget::GetWidgetType()
{
    return widgettype;
};

void Widget::LinkOnClick( void(*func)(char*) )
{
    clickfunction = func;
};

void Widget::LinkOnRelease( void(*func)(char*) )
{
    releasefunction = func;
};

void Widget::LinkOnHover( void(*func)(char*) )
{
    hoverfunction = func;
};

void Widget::Activate()
{
    is_activated = true;
};

void Widget::Desactivate()
{
    is_activated = false;
};

bool Widget::IsActivated()
{
    return is_activated;
};

void Widget::Lock()
{
    is_locked = true;
};

void Widget::Unlock()
{
    is_locked = false;
};

bool Widget::IsLocked()
{
    return is_locked;
};


Widget::Widget( )
{
    WidgetID = GlobalWidgetIDCounter;
    GlobalWidgetIDCounter++;

#if DEBUG_MODE == 1
    Debugger::TimerLog( "Create Widget( ) : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE

}

Widget::Widget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p )
{


    label=l;
    xrel=x;
    yrel=y;
    widrel=w;
    heirel=h;
    parent=p;

    WidgetID = GlobalWidgetIDCounter;
    GlobalWidgetIDCounter++;


#if DEBUG_MODE == 1
    Debugger::TimerLog( "Create Widget( ... ) : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE


    if (parent)
    {
        parent->AddChild( this );

        // if the widget has a parent, then we have to compute relative coordinates
        // if the parent is directly the desktop, we are free to position the widget as we want
        if (parent->GetWidgetType() == "Desktop" )
            //if (parent->GetWidgetType() == (char*) "Desktop")
        {
            xpos = xrel;
            ypos = yrel;
            width = widrel;
            height = heirel;
        }
        else
        {
            // else we need to take care of the useable dimension of the parent widget
            xpos = parent->GetUseableXPos() + xrel;
            ypos = parent->GetUseableYPos() + yrel;

            if ((xpos+widrel) > (parent->GetUseableXPos()+parent->GetUseableWidth()))
            {
                width = parent->GetUseableXPos()+parent->GetUseableWidth() -xpos;
            }
            else
            {
                width = widrel;
            }

            if ((ypos+heirel) > (parent->GetUseableYPos()+parent->GetUseableHeight()))
            {
                height = parent->GetUseableYPos()+parent->GetUseableHeight() -ypos;
            }
            else
            {
                height = heirel;
            }
        }
    }
    else
    {
        xpos = xrel;
        ypos = yrel;
        width = widrel;
        height = heirel;
    }

}

Widget::~Widget()
{

#if DEBUG_MODE == 1
    Debugger::TimerLog( "Delete ~Widget() : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE


#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t Will start killing the children of Widget() : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE

    for(auto& c : children)
    {
#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t Child : ID : %ld \t - Type : %s \t - Label :  %s \n", c->WidgetID, c->GetWidgetType().c_str(), c->GetLabel().c_str() );
#endif // DEBUG_MODE

        delete c;

#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t OK Done ...\n\n");
#endif // DEBUG_MODE
    }



    children.clear();

#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t List of Children CLEARED for Widget() : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE



#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t Will start killing the popup children of Widget() : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE

/*
    for (auto& d : popupchildren )
        {
#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t PopupChild : ID : %ld \t - Type : %s \t - Label :  %s \n", d->WidgetID, d->GetWidgetType().c_str(), d->GetLabel().c_str() );
#endif // DEBUG_MODE

        delete d;

#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t\t OK Done ... \n\n");
#endif // DEBUG_MODE
        }

    popupchildren.clear();


#if DEBUG_MODE == 1
    Debugger::TimerLog( "\t List of Popup Children CLEARED for Widget() : ID : %ld \t - Type : %s \t - Label :  %s \n", WidgetID, GetWidgetType().c_str(), GetLabel().c_str() );
#endif // DEBUG_MODE
*/

}


void Widget::Adjust()
{
    for (auto& c : children )
        c->Adjust();
}

void Widget::Logic(  )
{
    for (auto& c : children )
        c->Logic(  );
}

void Widget::Focus( Widget *emitter)
{


    // We go up to the first parent==nullptr (root of the tree
    if (parent)
    {
        parent->UnfocusUp( emitter );
    }
    /*    else //and then if parent is nullptr, we cascade down to the final leafs
        {
            for (auto& c : children )
            {
                if (c!=emitter)
                    c->unfocusdown( emitter );
            }
        }
    */
    has_focus = true;
}

void Widget::UnfocusUp( Widget *emitter)
{
    has_focus = false;


    // We go up to the first parent==nullptr (root of the tree
    if (parent)
    {
        parent->UnfocusUp( emitter );
    }
    else  //and then if parent is nullptr, we cascade down to the final leafs
    {
        for (auto& c : children )
        {
//            if (c!=emitter)
            c->UnfocusDown( emitter );
        }
    }
}

void Widget::UnfocusDown( Widget *emitter)
{
    has_focus = false;

    for (auto& c : children )
    {
//        if (c!=emitter)
        c->UnfocusDown( emitter );
    }
}



void Widget::Render( void )
{
    for (auto& c : children )
        if (c->IsVisible()) c->Render(  );
}


void Widget::RenderDepth( void )
{

    if (is_visible)
    {
        //if the widget is a Window or a DialogBox or the Desktop, then we plot the corresponding zone in the depth buttfer with a color representing its ID

        if ((GetWidgetType() == "Desktop") || (GetWidgetType() == "Window") || (GetWidgetType() == "DialogBox") || (GetWidgetType() == "FileDialogBox")) // || (strcmp( GetWidgetType(),(char*) "MenuBar" )==0) || (strcmp( GetWidgetType(),(char*) "MenuPane" )==0) )
        {
            //This part of the routine convert the Wedgit ID into a color code
            //It assumes a maximum number of widget limited to 999 per desktop

            //The number of units codes the BB component
            unsigned int B=0;
            unsigned int u = WidgetID % 10;
            B = u*25;

            //The number of tens codes the GG component
            unsigned int G=0;
            unsigned int d=((WidgetID-u)/10) % 10;
            G = d*25;

            //The number of hundreds codes the RR component
            unsigned int R=0;
            unsigned int c=((WidgetID-u-10*d) / 100) % 10;
            R = c*25;

/*
                    char tempID[100];
                    sprintf( tempID, "ID=%d / R=%d / G=%d / B=%d / c=%d / d=%d / u=%d", WidgetID, R, G, B, c, d, u );
                    FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
                    unsigned int length=FontEngine::GetStringWidth( tempID );
                    ScreenRenderer::DrawFilledRectangle( 5, 5, 5+length, 5 +10, 0, 0, 0, 255 );
                    FontEngine::DrawStringLeft( tempID, 5, 5, 0, 255, 0, 255 );

                    ScreenRenderer::FlipScreen();
*/

            //Draw the corresponding shape in the Depth Buffer Image
            DepthBufferRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, R, G, B, 255 );
        }
        else if (((GetWidgetType() == "MenuBar") || (GetWidgetType() == "MenuPane") || (GetWidgetType() == "IconBar")) && (GetClosestMainParent()->GetWidgetType() == "Desktop" ))
        {
            //This part of the routine convert the Wedgit ID into a color code
            //It assumes a maximum number of widget limited to 999 per desktop

            //The number of units codes the BB component
            unsigned int B=0;
            unsigned int u = WidgetID % 10;
            B = u*25;

            //The number of tens codes the GG component
            unsigned int G=0;
            unsigned int d=((WidgetID-u)/10) % 10;
            G = d*25;

            //The number of hundreds codes the RR component
            unsigned int R=0;
            unsigned int c=((WidgetID-u-10*d) / 100) % 10 ;
            R = c*25;

            //Draw the corresponding shape in the Depth Buffer Image
            DepthBufferRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, R, G, B, 255 );
        }

        for (auto& c : children )
            if (c->IsVisible()) c->RenderDepth(  );

    }
}



void Widget::Enable( )
{
    is_enabled = true;
    for (auto& c : children )
        c->Enable( );
}

void Widget::Disable( )
{
    is_enabled = false;
    for (auto& c : children )
        c->Disable( );
}

void Widget::SetVisible( )
{
    is_visible = true;
}

void Widget::SetInvisible( )
{
    is_visible = false;
}


void Widget::AddChild( Widget *child )
{
    children.push_back( child );
    nbchildren++;
    child->SetParent( this );
}


void Widget::AddPopupChild( Widget *child )
{
    if ((GetWidgetType() == "Window" ) || (GetWidgetType() == "Desktop" ))
    {
        popupchildren.push_back( child );
    }
    else if (parent)
    {
        parent->AddPopupChild( child );
    }
}


void Widget::SetParent( Widget *p )
{
    parent = p;
};


bool Widget::CursorOn( void )
{
    return (((unsigned int) MouseManager::GetX() >= xpos)
           && ((unsigned int) MouseManager::GetY() >= ypos)
           && ((unsigned int) MouseManager::GetX() <= xpos+width)
           && ((unsigned int) MouseManager::GetY() <= ypos+height));
}
