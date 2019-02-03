#include "inspection_window.h"
#include "../components/description_component.h"
#include "../core/game_engine.h"
#include "../widgets/text_block.h"

void InspectionWindow::setup() {
    setTitle("Details");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void InspectionWindow::registerWidgets() {
    const unsigned int l_windowWidth = 30;

    TextBlock* block = createWidget<TextBlock>("txtDescription", 1, 1);
    block->setWidth(l_windowWidth);

    DescriptionComponent* l_description =
        components()->get<DescriptionComponent>(m_entity);
    if (!l_description) {
        block->setText("There are no words...");
        return;
    }

    block->setText(l_description->text);
    setTitle(l_description->title);
    setHeight(block->getHeight() + 4);
    setWidth(l_windowWidth + 4);
}
