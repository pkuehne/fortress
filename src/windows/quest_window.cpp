#include "quest_window.h"
#include "../core/window_manager.h"
#include "label.h"
#include "listbox.h"
#include "../core/quest.h"
#include "../core/game_state.h"

#include <iostream>

void QuestWindow::setup()
{
    setTitle("Quest Log");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    setDimensions(0, 0, 20, 20);
}

void QuestWindow::registerWidgets()
{
    Label *l = nullptr;
    l = this->createWidget<Label>("lblQuests", 1, 1);
    l->setText("");
    l = this->createWidget<Label>("lblSep1", 1, 2);
    l->setText("===========");

    ListBox *b = nullptr;
    b = this->createWidget<ListBox>("lstQuests", 1, 3);
    b->setHeight(5)->setWidth(10);

    for (Quest *quest : getEngine()->state()->getQuests())
    {
        b->items.push_back(quest->title());
    }
    b->onItemSelected = [](ListBox *b) {
        Label *l = b->getWindow()->getWidget<Label>("lblQuestDetail");
        l->setText(b->items[b->getSelectedItem()]);
    };

    l = this->createWidget<Label>("lblSep2", 1, 7);
    l->setText("===========");
    l = this->createWidget<Label>("lblQuestDetail", 1, 8);
    l->setText("");
}