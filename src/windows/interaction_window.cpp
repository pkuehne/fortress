#include "interaction_window.h"
#include "frame.h"
#include "label.h"
#include "text_block.h"

void InteractionWindow::setup() {
    setTitle("Interact");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);

    m_desc = getEngine()->state()->components()->get<DescriptionComponent>(
        m_arguments->entity);
    m_open = getEngine()->state()->components()->get<OpenableComponent>(
        m_arguments->entity);
}

void InteractionWindow::registerWidgets() {
    const unsigned int descriptionWidth = 15;
    const unsigned int commandWidth = 10;
    const unsigned int windowHeight = 10;

    getWidget<Frame>("frmBase")->setMergeBorders();

    Frame* frmDesc = createWidget<Frame>("frmDescription", 0, 0);
    frmDesc->setMargin()
        ->setBorder()
        ->setWidth(descriptionWidth)
        ->setHeight(windowHeight);

    createWidget<TextBlock>("txtDescription", 0, 0, frmDesc)
        ->setText("An Entity")
        ->setWidth(descriptionWidth);

    createWidget<Label>("txtInspect", descriptionWidth, 1)
        ->setText("inspect")
        ->setCommandChar(1)
        ->setSensitive(false);
    createWidget<Label>("txtOpen", descriptionWidth, 2)
        ->setText("open")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            if (m_open->open) {
                auto event = new CloseEntityEvent;
                event->entity = m_arguments->entity;
                getEngine()->raiseEvent(event);
            } else {
                auto event = new OpenEntityEvent;
                event->entity = m_arguments->entity;
                getEngine()->raiseEvent(event);
            }
            getEngine()->swapTurn();
        })
        ->setSensitive(false);
    createWidget<Label>("txtTalk", descriptionWidth, 3)
        ->setText("talk")
        ->setCommandChar(1)
        ->setSensitive(false);

    setHeight(windowHeight);
    setWidth(descriptionWidth + commandWidth);
}

void InteractionWindow::nextTurn() {
    TextBlock* txtDesc = getWidget<TextBlock>("txtDescription");
    Label* txtInspect = getWidget<Label>("txtInspect");
    Label* txtOpen = getWidget<Label>("txtOpen");

    if (m_desc) {
        setTitle(m_desc->title);
        txtDesc->setText(m_desc->text);
    }
    if (m_open) {
        txtOpen->setText(m_open->open ? "close" : "open");
    }

    txtInspect->setSensitive(m_desc != nullptr);
    txtOpen->setSensitive(m_open != nullptr);
}