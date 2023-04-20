#include "groupchat.h"

GroupChat::GroupChat()
{

}

GroupChat::GroupChat(int id, QString name, int size, QDateTime dateCreated, std::vector<Profile*> participants, std::vector<Message> messageHistory):
    id(id), name(name), size(size), dateCreated(dateCreated), participants(participants), messageHistory(messageHistory){

}

GroupChat::GroupChat(QString name, std::vector<Profile*> participants):
    name(name), participants(participants){

}

GroupChat::~GroupChat(){

}

void GroupChat::add_participant(Profile *p){
    participants.push_back(p);
    size++;
}
void GroupChat::remove_participant(Profile *p){
    for(unsigned int i = 0; i < participants.size(); i++){
        if(participants[i]->get_id() == p->get_id()){
            messageHistory.erase(messageHistory.begin() + i);
            size--;
            return;
        }
    }
}
void GroupChat::send_message(Profile *sender, QString content){
    Message msg = Message(sender, this, content);
    messageHistory.push_back(msg);
}
void GroupChat::delete_message(Message msg){
    for(unsigned int i = 0; i < messageHistory.size(); i++){
        if(messageHistory[i].get_id() == msg.get_id()){
            messageHistory.erase(messageHistory.begin() + i);
            return;
        }
    }
}

std::vector<Profile*> GroupChat::get_participants(){
    return participants;
}
std::vector<Message> GroupChat::get_history(){
    return messageHistory;
}
