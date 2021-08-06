#include "ContainerHWidget.hpp"

#include <iterator>


ContainerHWidget::ContainerHWidget()
{
    widgettype = "ContainerH";
};

ContainerHWidget::ContainerHWidget( std::string l, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Widget *p ) : Widget( l, x, y, w, h, p )
{
    widgettype = "ContainerH";
};


ContainerHWidget::~ContainerHWidget()
{
    constraintvalue.clear();
    constrainttype.clear();
};

int ContainerHWidget::GetSize()
{
    return nbchildren;
};


void ContainerHWidget::AddConstraint( int value, std::string type )
{
    constraintvalue.push_back(value);
    constrainttype.push_back(type);
}


void ContainerHWidget::Adjust( void )
{
    if (parent)
    {
        if (( parent->GetWidgetType() == "ContainerV" ) || (parent->GetWidgetType() == "ContainerH" ))
        {
            // nothing to do, it comes from the parent
        }
        else
        {
            xpos = parent->GetUseableXPos();
            ypos = parent->GetUseableYPos();
            width = parent->GetUseableWidth();
            height = parent->GetUseableHeight();
        }
    }

    // If no constraint have been defined, then we just divide the size by the number of children
    if ((constraintvalue.size()==0) || (constrainttype.size()==0))
    {
        int i=0;
        nbchildren = children.size();

        for (auto& c : children )
        {
            c->SetDimensions( xpos+1 + width/nbchildren*i, ypos, width/nbchildren-2, height );
            i++;
        }
    }
    else
    {
        if ((constraintvalue.size() == constrainttype.size()) && (constraintvalue.size() == children.size()))
        {
            unsigned int remainingwidth = this->width;

            // first loop based on direct assignement of size by constraint in pixels

            auto it1 = constraintvalue.begin();
            auto it2 = constrainttype.begin();
            auto it3 = children.begin();

            for (unsigned int temp=0; temp<children.size(); temp++)
            {


                // if the constraint is an absolute pixel value, we directly report the value as the dimension that is needed
                if (*it2 == "px")
                {
                    // We have the information for width (imposed by constraint), ypos and height are coming from available space useable
                    (*it3)->SetWidth( *it1-2 );
                    (*it3)->SetHeight( height-2 );
                    (*it3)->SetYPos( ypos+1 );
                    // for xpos, we will have to compute when everything else will be computed later on

                    // before going to percentage constraint, we will have to compute the remaining space to be split by percentages
                    remainingwidth -= ( *it1 );
                }

                it1++;
                it2++;
                it3++;
            }


            // second loop based on assignement of percentages of remaining space
            it1 = constraintvalue.begin();
            it2 = constrainttype.begin();
            it3 = children.begin();

            for (unsigned int temp=0; temp<children.size(); temp++)
            {


                // if the constraint is an absolute pixel value, we directly report the value as the dimension that is needed
                if (*it2 == "%")
                {
                    // We have the information for width (imposed by constraint), ypos and height are coming from available space useable
                    (*it3)->SetWidth( (unsigned int) (*it1 * remainingwidth / 100 -2) );
                    (*it3)->SetHeight( height -2);
                    (*it3)->SetYPos( ypos +1);
                    // for xpos, we will have to compute when everything else will be computed later on
                }

                it1++;
                it2++;
                it3++;
            }

            // No we compute the remaining dimension (xpos)
            unsigned int currentx = xpos + 1;
            for( auto it=children.begin(); it!=children.end(); it++ )
            {
                (*it)->SetXPos( currentx );
                currentx += (*it)->GetWidth()+2;
            }

        }

    }

    for (auto& c : children )
        c->Adjust();
}


void ContainerHWidget::Logic( void )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->Logic( );
    }
}


void ContainerHWidget::Render( void )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->Render(  );
    }
}
