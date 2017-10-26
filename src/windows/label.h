#pragma once

#include "widget.h"

class Label : public Widget {
    public:
        Label() {}

        std::string text = "";
        bool sensitive = true;
        unsigned int commandChar = 0;

        virtual void render();

    private:

};
