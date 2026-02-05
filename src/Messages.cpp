// internal
#include "Messages.h"

fourbune::messages::message_manager::message_manager(){
    std::cout << "Created new message manager\n";
}

int fourbune::messages::message_manager::newMessage(message& msg){
    messages.push_back(msg);
    std::cout << "New message : " << 
        msg.userAgent << '(' << msg.timestamp << ')' <<
        msg.content << std::endl;
    return messages.size() -1;
}

std::vector<fourbune::messages::message> 
fourbune::messages::message_manager::getMessages(){
    return messages;
}

std::vector<fourbune::messages::message> 
fourbune::messages::message_manager::getMessagesFrom(size_t lastId){
    std::vector<fourbune::messages::message> queue;

    for(size_t i = (lastId < 0 ? 0 : lastId); i < messages.size(); i++){
        queue.push_back(messages[i]);
    }

    return queue;
}

fourbune::messages::message
fourbune::messages::message_manager::getMessage(size_t id){
    message defaultMsg;
    defaultMsg.timestamp = 0;
    defaultMsg.content = "Incorrect message ID " + std::to_string(id);
    defaultMsg.userAgent = "SYSTEM";

    if(id < messages.size()) return messages[id];

    return defaultMsg;
}

fourbune::messages::message_manager::~message_manager(){
    messages.clear();
}