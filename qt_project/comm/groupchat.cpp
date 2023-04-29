#include "groupchat.h"
#include "../profiles/profile.h"
#include "message.h"

GroupChat::GroupChat()
{

}

GroupChat::GroupChat(int id, Profile *owner, QString name, QDateTime dateCreated, std::vector<Profile*> participants):
    groupchatId(id), ownerId(owner->get_id()), name(name), size(participants.size()), dateCreated(dateCreated){

    for(Profile *profile: participants){
        this->participants[profile->get_id()] = profile;
    }
} // user creates new groupchat

GroupChat::GroupChat(std::map<QString, QString> groupchatData){
    groupchatId = groupchatData[QString("groupchat_id")].toInt();
    ownerId = groupchatData[QString("owner_id")].toInt();
    name = groupchatData[QString("name")];
    size = groupchatData[QString("size")].toInt();

    QString dateString = groupchatData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

} // load from database

GroupChat::~GroupChat(){

}

void GroupChat::add_message(Message *message){
    messageHistory[message->get_id()] = message;
}

void GroupChat::add_participant(Profile *profile){

    participants[profile->get_id()] = profile;
    size++;
}

void GroupChat::remove_message(Message *message){
    messageHistory.erase(message->get_id());
}

void GroupChat::remove_participant(Profile *profile){

    participants.erase(profile->get_id());
    size--;
}

void GroupChat::set_owner(Profile *profile){
    owner = profile;
}

int GroupChat::get_id(){
    return groupchatId;
}
QString GroupChat::get_name(){
    return name;
}
int GroupChat::get_size(){
    return size;
}
QDateTime GroupChat::get_dateCreated(){
    return dateCreated;
}
Profile *GroupChat::get_owner(){
    return owner;
}

std::map<int, Profile*> GroupChat::get_participants(){
    return participants;
}
std::map<int, Message*> GroupChat::get_messageHistory(){
    return messageHistory;
}
