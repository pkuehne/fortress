#include "save_window.h"
#include "frame.h"
#include "label.h"
#include "tab.h"
#include "text_entry.h"
#include <thread>

void SaveWindow::setup() {
    setTitle("Save Game");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    setHeight(10);
    setWidth(30);
}

void SaveWindow::registerWidgets() {
    getWidget<Frame>("frmBase")->setMergeBorders();

    Tab* tab = createWidget<Tab>("tabSaveLocation", 1, 1);

    tab->setPageSwitchCallback([](Tab* t) {
        //
    });
    Frame* createTab = tab->addPage("Create")->getFrame();
    createTab->setMargin(0);
    createWidget<Label>("lblCreate", 0, 0, createTab)->setText("Filename:");
    createWidget<TextEntry>("entFilename", 10, 0, createTab)
        ->setEnterCallback([&](TextEntry* e) { this->saveState(e->getText()); })
        ->setSuffix(std::string(".yaml"))
        ->setWidthStretchMargin(0)
        ->setHeightStretchMargin(0);

    createWidget<Label>("lblStatus", 1, 1)
        ->setText("")
        ->setHorizontalAlign(Widget::HorizontalAlign::Left)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
}

void SaveWindow::saveState(const std::string& filename) {
    Label* lblStatus = getWidget<Label>("lblStatus");
    lblStatus->setText("Saving...");
    getWidget<TextEntry>("entFilename")->setSensitive(false);
    std::thread update([=]() {
        this->getEngine()->state()->save(filename);
        lblStatus->setText("Saved!");
    });
    update.detach();
}
