#include "save_window.h"
#include "../core/file_saver.h"
#include "frame.h"
#include "label.h"
#include "progress_bar.h"
#include "tab.h"
#include "text_entry.h"
#include <iostream>
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
        ->setEnterCallback([&](TextEntry* e) {
            std::string filename;
            filename = e->getText();
            filename.append(e->getSuffix());
            this->saveState(filename);
        })
        ->setSuffix(std::string(".yaml"))
        ->setWidthStretchMargin(0)
        ->setHeightStretchMargin(0);

    createWidget<Label>("lblProgress", 1, 2)
        ->setText("Progress: ")
        ->setHorizontalAlign(Widget::HorizontalAlign::Left)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<ProgressBar>("pgbProgress", 11, 2)
        ->setWidth(getWidth() - 14)
        ->setHorizontalAlign(Widget::HorizontalAlign::Left)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);

    createWidget<Label>("lblStatus", 1, 1)
        ->setText("")
        ->setHorizontalAlign(Widget::HorizontalAlign::Left)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
}

void SaveWindow::saveState(const std::string& filename) {
    Label* lblStatus = getWidget<Label>("lblStatus");
    ProgressBar* pgbProgress = getWidget<ProgressBar>("pgbProgress");
    lblStatus->setText("Saving...");
    getWidget<TextEntry>("entFilename")->setSensitive(false);
    std::thread update([=]() {
        FileSaver saver(this->getEngine()->state());
        saver.setStatusCallback([=](unsigned int current, unsigned int max,
                                    const std::string& status) {
            lblStatus->setText(status);
            pgbProgress->setMaxValue(max)->setValue(current);
            lblStatus->setText(status);
        });
        saver.saveState(filename);
        lblStatus->setText("Saved!");
    });
    update.detach();
}
