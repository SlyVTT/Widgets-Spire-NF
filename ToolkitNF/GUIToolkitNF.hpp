#include <libndls.h>

#include "Globals/GUIToolkitNFGlobals.hpp"


#if DEBUG_MODE == 1
    #include "Debugger/Debugger.hpp"
#endif // DEBUG_MODE


#include "Managers/KeyManager.hpp"
#include "Managers/MouseManager.hpp"
#include "Managers/TimeManager.hpp"


#include "Engines/FontEngine.hpp"
#include "Engines/ColorEngine.hpp"
#include "Engines/ThemeEngine.hpp"


#include "Renderers/ScreenRenderer.hpp"
#include "Renderers/DepthBufferRenderer.hpp"


#include "Widgets/Widget.hpp"
#include "Widgets/WidgetApplication.hpp"
#include "Widgets/DesktopWidget.hpp"

#include "Widgets/ButtonWidget.hpp"
#include "Widgets/CheckBoxWidget.hpp"
#include "Widgets/InputWidget.hpp"
#include "Widgets/ContainerHWidget.hpp"
#include "Widgets/ContainerVWidget.hpp"
#include "Widgets/SpacerWidget.hpp"
#include "Widgets/SliderWidget.hpp"

#include "Widgets/FrameWidget.hpp"
#include "Widgets/LabelWidget.hpp"

#include "Widgets/CommuterWidget.hpp"
#include "Widgets/ProgressBarWidget.hpp"


