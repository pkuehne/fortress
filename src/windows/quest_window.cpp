#include <quest_window.h>
#include <../core/window_manager.h>
#include "label.h"
#include "listbox.h"
#include "../core/quest.h"
#include "../core/game_state.h"

#include <iostream>

void QuestWindow::registerWidgets()
{
    Label* l = nullptr;
    l = this->createWidget<Label>("lblQuests", 1, 1);
    l->text("Your Quests");
    l = this->createWidget<Label>("lblSep1", 1, 2);
    l->text("===========");

    ListBox* b = nullptr;
    b = this->createWidget<ListBox>("lstQuests", 1, 3);
    b->height = 5;
    b->width = 10;

    for (Quest* quest : getEngine()->state()->getQuests()) {
        b->items.push_back(quest->title());
    }
    b->onItemSelected = [](ListBox* b) {
        Label* l = b->window->getWidget<Label>("lblQuestDetail");
        l->text(b->items[b->selectedItem]);
    };

    l = this->createWidget<Label>("lblSep2", 1, 7);
    l->text("===========");
    l = this->createWidget<Label>("lblQuestDetail", 1, 8);
    l->text("");
}

void QuestWindow::resize()
{
    setDimensions (0, 0, 20, 20);
}

void QuestWindow::keyPress (unsigned char key)
{
    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
    }
}
