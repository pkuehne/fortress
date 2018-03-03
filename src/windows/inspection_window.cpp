#include "inspection_window.h"
#include "../core/game_engine.h"
#include "../components/description_component.h"
#include "text_block.h"

void InspectionWindow::setup()
{
    setTitle("Details");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    setDimensions(0, 0, 2, 2);
}

void InspectionWindow::registerWidgets()
{
    const unsigned int l_windowWidth = 30;

    TextBlock *block = createWidget<TextBlock>("txtDescription", 2, 2);
    block->setWidth(l_windowWidth);

    EntityId *l_entity = static_cast<EntityId *>(getArgs());
    if (!l_entity)
    {
        block->setText("There is nothing here...");
        return;
    }
    DescriptionComponent *l_description = getEngine()->state()->components()->get<DescriptionComponent>(*l_entity);
    if (!l_description)
    {
        block->setText("There are no words...");
        return;
    }

    block->setText(l_description->text);
    setTitle(l_description->title);
    setDimensions(0, 0, l_windowWidth + 4, block->getHeight() + 4);
}

void InspectionWindow::destroy()
{
    EntityId *l_entity = static_cast<EntityId *>(getArgs());
    if (l_entity)
    {
        delete l_entity;
    }
    Window::destroy();
}
