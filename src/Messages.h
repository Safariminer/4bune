#pragma once

// stl
#include <iostream>
#include <vector>

namespace fourbune{
    namespace messages{
        struct message{
            unsigned long long timestamp;
            std::string userAgent;
            std::string content;
        };
        
        class message_manager{
            std::vector<message> messages;
        public:
            message_manager();
            int newMessage(message& msg);
            std::vector<message> getMessages();
            std::vector<message> getMessagesFrom(size_t lastId);
            message getMessage(size_t id);
            ~message_manager();
        };
    }
}