#include "dialog_window.h"
#include "../core/game_engine.h"
#include "../widgets/frame.h"
#include "../widgets/label.h"
#include "../widgets/listbox.h"

void DialogWindow::setup() {
    setTitle("Dialog");
    setHeight(15);
    setWidth(40);

    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void DialogWindow::registerWidgets() {
    getWidget<Frame>("frmBase")->setMergeBorders()->setMargin();

    createWidget<Label>("lblResponse", 0, 0)->setText("Yeah?");

    auto frmQuestions = createWidget<Frame>("frmQuestions", 0, 0);
    frmQuestions->setBorder()
        ->setHeight(7)
        ->setWidthStretchMargin(0)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);

    auto lstQuestions =
        createWidget<ListBox>("lstQuestions", 1, 0, frmQuestions);
    lstQuestions->setHeightStretchMargin(0)
        ->setWidthStretchMargin(0)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    lstQuestions->setItemSelectedCallback([=](ListBox* l) {
        ListBoxItem item = l->getSelectedItem();
        if (item.getValue() == 1) {
            getWidget<Label>("lblResponse")->setText("What do you care?");
        } else if (item.getValue() == 2) {
            getWidget<Label>("lblResponse")->setText("I ain't telling you");
        } else {
            getWidget<Label>("lblResponse")->setText("You wot, mate?");
        }
    });
    lstQuestions->clearItems();

    ListBoxItem item;
    item.setValue(1);
    item.setText("What's your name?");
    lstQuestions->addItem(item);
    item.setValue(2);
    item.setText("What groups are you a member of?");
    lstQuestions->addItem(item);
}
