#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"
#include "app.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen0_BackgroundPanel;
leLabelWidget* Screen0_LabelWidget_0;
leWidget* Screen0_PanelWidget_0;
leLabelWidget* Screen0_LabelWidget_1;
leLabelWidget* Screen0_LabelWidget_1_0;
leLabelWidget* Screen0_LabelWidget_1_0_0;
leLabelWidget* Screen0_LabelWidget_1_0_1;
leWidget* Screen0_PanelWidget_0_0;
leWidget* Screen0_PanelWidget_0_0_0;
leLabelWidget* Screen0_LabelWidget_NodeID;
leLabelWidget* Screen0_LabelWidget_Counter;
leLabelWidget* Screen0_LabelWidget_Temp;
leLabelWidget* Screen0_LabelWidget_Switch;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen0(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen0(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen0_BackgroundPanel = leWidget_New();
    Screen0_BackgroundPanel->fn->setPosition(Screen0_BackgroundPanel, 0, 0);
    Screen0_BackgroundPanel->fn->setSize(Screen0_BackgroundPanel, 320, 240);
    Screen0_BackgroundPanel->fn->setScheme(Screen0_BackgroundPanel, &DarkScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_BackgroundPanel);

    Screen0_LabelWidget_0 = leLabelWidget_New();
    Screen0_LabelWidget_0->fn->setPosition(Screen0_LabelWidget_0, 0, 9);
    Screen0_LabelWidget_0->fn->setSize(Screen0_LabelWidget_0, 320, 41);
    Screen0_LabelWidget_0->fn->setScheme(Screen0_LabelWidget_0, &DarkScheme);
    Screen0_LabelWidget_0->fn->setBackgroundType(Screen0_LabelWidget_0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget_0->fn->setHAlignment(Screen0_LabelWidget_0, LE_HALIGN_CENTER);
    Screen0_LabelWidget_0->fn->setString(Screen0_LabelWidget_0, (leString*)&string_TitleString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_0);

    Screen0_PanelWidget_0 = leWidget_New();
    Screen0_PanelWidget_0->fn->setPosition(Screen0_PanelWidget_0, 13, 61);
    Screen0_PanelWidget_0->fn->setSize(Screen0_PanelWidget_0, 295, 2);
    Screen0_PanelWidget_0->fn->setScheme(Screen0_PanelWidget_0, &OutlineScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_PanelWidget_0);

    Screen0_LabelWidget_1 = leLabelWidget_New();
    Screen0_LabelWidget_1->fn->setPosition(Screen0_LabelWidget_1, 13, 64);
    Screen0_LabelWidget_1->fn->setSize(Screen0_LabelWidget_1, 95, 24);
    Screen0_LabelWidget_1->fn->setScheme(Screen0_LabelWidget_1, &OutlineScheme);
    Screen0_LabelWidget_1->fn->setBackgroundType(Screen0_LabelWidget_1, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_IDString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_1);

    Screen0_LabelWidget_1_0 = leLabelWidget_New();
    Screen0_LabelWidget_1_0->fn->setPosition(Screen0_LabelWidget_1_0, 13, 144);
    Screen0_LabelWidget_1_0->fn->setSize(Screen0_LabelWidget_1_0, 115, 24);
    Screen0_LabelWidget_1_0->fn->setScheme(Screen0_LabelWidget_1_0, &OutlineScheme);
    Screen0_LabelWidget_1_0->fn->setBackgroundType(Screen0_LabelWidget_1_0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget_1_0->fn->setString(Screen0_LabelWidget_1_0, (leString*)&string_TemperatureString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_1_0);

    Screen0_LabelWidget_1_0_0 = leLabelWidget_New();
    Screen0_LabelWidget_1_0_0->fn->setPosition(Screen0_LabelWidget_1_0_0, 164, 64);
    Screen0_LabelWidget_1_0_0->fn->setSize(Screen0_LabelWidget_1_0_0, 115, 24);
    Screen0_LabelWidget_1_0_0->fn->setScheme(Screen0_LabelWidget_1_0_0, &OutlineScheme);
    Screen0_LabelWidget_1_0_0->fn->setBackgroundType(Screen0_LabelWidget_1_0_0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget_1_0_0->fn->setString(Screen0_LabelWidget_1_0_0, (leString*)&string_CounterString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_1_0_0);

    Screen0_LabelWidget_1_0_1 = leLabelWidget_New();
    Screen0_LabelWidget_1_0_1->fn->setPosition(Screen0_LabelWidget_1_0_1, 164, 144);
    Screen0_LabelWidget_1_0_1->fn->setSize(Screen0_LabelWidget_1_0_1, 115, 24);
    Screen0_LabelWidget_1_0_1->fn->setScheme(Screen0_LabelWidget_1_0_1, &OutlineScheme);
    Screen0_LabelWidget_1_0_1->fn->setBackgroundType(Screen0_LabelWidget_1_0_1, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget_1_0_1->fn->setString(Screen0_LabelWidget_1_0_1, (leString*)&string_SwitchString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_1_0_1);

    Screen0_PanelWidget_0_0 = leWidget_New();
    Screen0_PanelWidget_0_0->fn->setPosition(Screen0_PanelWidget_0_0, 13, 141);
    Screen0_PanelWidget_0_0->fn->setSize(Screen0_PanelWidget_0_0, 295, 2);
    Screen0_PanelWidget_0_0->fn->setScheme(Screen0_PanelWidget_0_0, &OutlineScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_PanelWidget_0_0);

    Screen0_PanelWidget_0_0_0 = leWidget_New();
    Screen0_PanelWidget_0_0_0->fn->setPosition(Screen0_PanelWidget_0_0_0, 159, 69);
    Screen0_PanelWidget_0_0_0->fn->setSize(Screen0_PanelWidget_0_0_0, 2, 161);
    Screen0_PanelWidget_0_0_0->fn->setScheme(Screen0_PanelWidget_0_0_0, &OutlineScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_PanelWidget_0_0_0);

    Screen0_LabelWidget_NodeID = leLabelWidget_New();
    Screen0_LabelWidget_NodeID->fn->setPosition(Screen0_LabelWidget_NodeID, 34, 99);
    Screen0_LabelWidget_NodeID->fn->setScheme(Screen0_LabelWidget_NodeID, &DarkScheme);
    Screen0_LabelWidget_NodeID->fn->setHAlignment(Screen0_LabelWidget_NodeID, LE_HALIGN_CENTER);
    Screen0_LabelWidget_NodeID->fn->setString(Screen0_LabelWidget_NodeID, (leString*)&string_NullString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_NodeID);

    Screen0_LabelWidget_Counter = leLabelWidget_New();
    Screen0_LabelWidget_Counter->fn->setPosition(Screen0_LabelWidget_Counter, 189, 99);
    Screen0_LabelWidget_Counter->fn->setScheme(Screen0_LabelWidget_Counter, &DarkScheme);
    Screen0_LabelWidget_Counter->fn->setHAlignment(Screen0_LabelWidget_Counter, LE_HALIGN_CENTER);
    Screen0_LabelWidget_Counter->fn->setString(Screen0_LabelWidget_Counter, (leString*)&string_NullString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_Counter);

    Screen0_LabelWidget_Temp = leLabelWidget_New();
    Screen0_LabelWidget_Temp->fn->setPosition(Screen0_LabelWidget_Temp, 34, 182);
    Screen0_LabelWidget_Temp->fn->setScheme(Screen0_LabelWidget_Temp, &DarkScheme);
    Screen0_LabelWidget_Temp->fn->setHAlignment(Screen0_LabelWidget_Temp, LE_HALIGN_CENTER);
    Screen0_LabelWidget_Temp->fn->setString(Screen0_LabelWidget_Temp, (leString*)&string_NullString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_Temp);

    Screen0_LabelWidget_Switch = leLabelWidget_New();
    Screen0_LabelWidget_Switch->fn->setPosition(Screen0_LabelWidget_Switch, 189, 182);
    Screen0_LabelWidget_Switch->fn->setScheme(Screen0_LabelWidget_Switch, &DarkScheme);
    Screen0_LabelWidget_Switch->fn->setHAlignment(Screen0_LabelWidget_Switch, LE_HALIGN_CENTER);
    Screen0_LabelWidget_Switch->fn->setString(Screen0_LabelWidget_Switch, (leString*)&string_NullString);
    root0->fn->addChild(root0, (leWidget*)Screen0_LabelWidget_Switch);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    //Screen0_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen0_OnUpdate(); // raise event
}

void screenHide_Screen0(void)
{
    //Screen0_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen0_BackgroundPanel = NULL;
    Screen0_LabelWidget_0 = NULL;
    Screen0_PanelWidget_0 = NULL;
    Screen0_LabelWidget_1 = NULL;
    Screen0_LabelWidget_1_0 = NULL;
    Screen0_LabelWidget_1_0_0 = NULL;
    Screen0_LabelWidget_1_0_1 = NULL;
    Screen0_PanelWidget_0_0 = NULL;
    Screen0_PanelWidget_0_0_0 = NULL;
    Screen0_LabelWidget_NodeID = NULL;
    Screen0_LabelWidget_Counter = NULL;
    Screen0_LabelWidget_Temp = NULL;
    Screen0_LabelWidget_Switch = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen0(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
    case 0:
    {
        return root0;
    }
    default:
    {
        return NULL;
    }
    }
}

