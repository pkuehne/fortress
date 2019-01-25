#pragma once

#include "component_base.h"
#include <vector>

struct LogMessageComponent : public ComponentBase {
    struct Message {
        Message(const std::string& m, const std::string& c)
            : message(m), category(c) {}
        std::string message;
        std::string category;
    };

    std::vector<Message> messages;
};