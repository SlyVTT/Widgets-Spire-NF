#include "DropBoxWidget.hpp"

#include "../Managers/KeyManager.hpp"
#include "../Managers/MouseManager.hpp"
#include "../Renderers/ScreenRenderer.hpp"
#include "../Engines/ColorEngine.hpp"
#include "../Engines/FontEngine.hpp"


DropBoxWidget::DropBoxWidget() : Widget()
{
    widgettype = "DropBox";

    dropbutton = new MiniButtonWidget();
    dropbutton->SetType( MiniButtonWidget::Bottom_Arrow );
    AddChild(dropbutton);

    listbox = new ListBoxWidget();
    AddChild( listbox );
    listbox->SetParent( this );

    listbox->SetLabel( "Hello Listbox" );
    listbox->SetInvisible();

    parent->AddPopupChild( listbox );
};


DropBoxWidget::DropBoxWidget(std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "DropBox";

    this->SetDimensions( x, y, w-h, h );

    MiniButtonWidget *tempbutton = new MiniButtonWidget();
    dropbutton = tempbutton;
    dropbutton->SetDimensions( x+w, y, h, h );
    dropbutton->SetType( MiniButtonWidget::Bottom_Arrow );
    AddChild(dropbutton);

    ListBoxWidget *templist = new ListBoxWidget();
    listbox = templist;
    listbox->SetDimensions( x, y+h, w+h, 5*h );
    AddChild( listbox );
    listbox->SetParent( this );

    listbox->SetLabel( "Hello Listbox" );
    listbox->SetInvisible();

    parent->AddPopupChild( listbox );
}

DropBoxWidget::~DropBoxWidget( void )
{
    delete dropbutton;
    delete listbox;
}

void DropBoxWidget::Drop( void )
{
    is_dropped = true;
    this->listbox->SetVisible();
    has_been_updated = false;
};


void DropBoxWidget::Undrop( void )
{
    is_dropped = false;
    this->listbox->SetInvisible();
};


void DropBoxWidget::AddItem( std::string item )
{
    listbox->AddItem( item );
};


int DropBoxWidget::GetNbItem( void )
{
    return listbox->GetNbItem();
};

std::string DropBoxWidget::GetItem( int itemnumber )
{
    return listbox->GetItem( itemnumber );
};

int DropBoxWidget::GetSelected( void )
{
    return listbox->GetSelected();
};

std::string DropBoxWidget::GetSelectedItem( void )
{
    return listbox->GetSelectedItem();
};


bool DropBoxWidget::IsUpdated( void )
{
    return has_been_updated;
};


bool DropBoxWidget::IsPressed( void )
{
    return is_pressed;
}

void DropBoxWidget::Validate( void )
{
    this->selected_item = this->listbox->GetSelected();
    this->selected_item_value = this->listbox->GetSelectedItem();

    this->SetLabel( selected_item_value );

    this->dropbutton->Invert();
    this->Undrop();

    has_been_updated = true;
}

void DropBoxWidget::Escape( void )
{
    this->selected_item = -1;
    this->selected_item_value = " ";

    this->SetLabel( " " );

    this->dropbutton->Invert();
    this->Undrop();

    has_been_updated = false;
}

void DropBoxWidget::Adjust( void )
{

    this->SetDimensions( xpos, ypos, width-height, height );

    dropbutton->SetDimensions( xpos+width, ypos, height, height );

    listbox->SetDimensions( xpos, ypos+height, width+height, 5*height );

    for (auto& c : children )
        c->Adjust();
}

void DropBoxWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        is_hovering = CursorOn(  );
        bool currently_pressed = (MouseManager::GetB() || KeyManager::kbSCRATCH() ) && is_hovering;

        if(currently_pressed && !is_pressed)
        {
            if (clickfunction) clickfunction( (char*) "test" );
        }
        else if(!currently_pressed && is_pressed)
        {
            if (releasefunction) releasefunction( (char*) "test" );
        }
        else if(is_hovering)
        {
            if (hoverfunction) hoverfunction( (char*) "test" );
        }

        is_pressed = currently_pressed;

        dropbutton->Logic(  );

        if (dropbutton->IsTicked())
        {
            dropbutton->SetType( MiniButtonWidget::Up_Arrow );
            this->Drop();
        }
        else
        {
            dropbutton->SetType( MiniButtonWidget::Bottom_Arrow );
            this->Undrop();
        }

        //for (auto& c : children )
        //    c->logic( mouse, keyboard );
    }
}

void DropBoxWidget::Render( void )
{
    if (is_visible)
    {
        if (is_enabled)
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Enable) );

            if (!is_hovering)
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Enable) );
            }
            else
            {
                ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Cursoron) );
            }

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Enable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5 );

            if ((drawablecharlabel!=0) && (selected_item!=-1))
            {
                 drawablelabel =  FontEngine::ReduceStringToVisible( label, width-5 -5  );

                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+5, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Enable) );
            }
        }
        else
        {
            ScreenRenderer::DrawFilledRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Filling_Disable) );

            ScreenRenderer::DrawRoundedRectangle( xpos, ypos, xpos+width, ypos+height, 3, ColorEngine::GetColor(ColorEngine::Widget_Border_Disable) );

            // THIS IS THE PART OF THE ROUTINE THAT CHECK IF THE TEXT TO BE RENDERED IS TOO LONG AND IF SO THAT REDUCES IT TO THE DRAWABLE LENGTH
            FontEngine::SetCurrentFontSet( FontEngine::Widget_Text_Disable );
            drawablecharlabel =  FontEngine::AssertStringLength( label, width-5-5 );

            if ((drawablecharlabel!=0) && (selected_item!=-1))
            {
                 drawablelabel =  FontEngine::ReduceStringToVisible( label, width-5 -5  );

                int sh =  FontEngine::GetStringHeight( drawablelabel );

                 FontEngine::DrawStringLeft( drawablelabel, xpos+5, ypos+(height-sh)/2, ColorEngine::GetColor(ColorEngine::Widget_Text_Disable) );
            }
        }

        dropbutton->Render( );

        for (auto& c : children ) c->Render( );

    }
}
