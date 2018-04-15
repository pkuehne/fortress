#pragma once

#include "widget.h"
#include "../core/color.h"

#include <vector>
#include <functional>

class ListBoxItem
{
  public:
    ListBoxItem *setText(const std::string &text)
    {
        m_text = text;
        return this;
    }
    ListBoxItem *setValue(unsigned int value)
    {
        m_value = value;
        return this;
    }
    ListBoxItem *setIndex(unsigned int index)
    {
        m_index = index;
        return this;
    }
    ListBoxItem *setColor(Color color)
    {
        m_color = color;
        return this;
    }

    std::string getText() { return m_text; }
    unsigned int getValue() { return m_value; }
    unsigned int getIndex() { return m_index; }
    Color getColor() { return m_color; }

  private:
    std::string m_text = "";
    unsigned int m_value = 0;
    unsigned int m_index = 0;
    Color m_color = Color(WHITE);
};

class ListBox : public Widget
{
  public:
    typedef std::function<void(ListBox *)> ItemSelectedCB;

    ListBox *addItem(ListBoxItem &item)
    {
        item.setIndex(m_items.size());
        m_items.push_back(item);
        return this;
    }
    ListBox *clearItems()
    {
        m_items.clear();
        m_selection = 0; // Don't call the callback!
        return this;
    }
    std::vector<ListBoxItem> &getItems()
    {
        return m_items;
    }
    ListBox *setSelection(unsigned int item)
    {
        m_selection = item;
        updateTopOffset();
        return this;
    }
    unsigned int getSelection()
    {
        return m_selection;
    }
    ListBoxItem getSelectedItem()
    {
        if (!m_items.size())
        {
            throw std::string("Cannot get selected item from empty ListBox");
        }
        return m_items[m_selection];
    }
    ListBox *setItemSelectedCallback(ItemSelectedCB cb)
    {
        m_itemSelectedCb = cb;
        return this;
    }

    void scrollToBottom();

    virtual void render();
    virtual void keyPress(unsigned char key);

  private:
    void updateTopOffset();

  private:
    std::vector<ListBoxItem> m_items;
    unsigned int m_selection = 0;

    unsigned int m_topOffset = 0;

    ItemSelectedCB m_itemSelectedCb;
};
