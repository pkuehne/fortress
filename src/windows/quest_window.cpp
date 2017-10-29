#include <quest_window.h>
#include <../core/window_manager.h>
#include "label.h"
#include "listbox.h"

#include <iostream>

void QuestWindow::registerWidgets()
{
    Label* l = nullptr;
    l = this->createWidget<Label>(1, 1);
    l->text("Your Quests");
    l = this->createWidget<Label>(1, 2);
    l->text("===========");
    
    ListBox* b = nullptr;
    b = this->createWidget<ListBox>(1, 3);
    b->items.push_back("Quest 1");
    b->items.push_back("Quest 2");
    b->items.push_back("Quest 3");
    b->height = 2;
    b->width = 10;
}

void QuestWindow::resize()
{
    setDimensions (10,10, 20, 20);
}

void QuestWindow::keyPress (unsigned char key)
{
    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
