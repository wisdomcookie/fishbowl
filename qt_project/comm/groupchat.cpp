#include "groupchat.h"
#include "../profiles/profile.h"
#include "message.h"

/**
 * @brief GroupChat::GroupChat
 */
GroupChat::GroupChat()
{

}
/**
 * Constructor for creating a new groupchat
 * @brief GroupChat::GroupChat
 * @param id
 * @param owner
 * @param name
 * @param dateCreated
 * @param participants
 */
GroupChat::GroupChat(int id, Profile *owner, QString name, QDateTime dateCreated, std::vector<Profile*> participants):
    groupchatId(id), ownerId(owner->get_id()), name(name), size(participants.size()), dateCreated(dateCreated){

    for(Profile *profile: participants){
        this->participants[profile->get_id()] = profile;
    }
} // user creates new groupchat
/**
 * Constructor used to load groupchats from the database
 * @brief GroupChat::GroupChat
 * @param groupchatData
 */
GroupChat::GroupChat(std::map<QString, QString> groupchatData){
    groupchatId = groupchatData[QString("groupchat_id")].toInt();
    ownerId = groupchatData[QString("owner_id")].toInt();
    name = groupchatData[QString("name")];
    size = groupchatData[QString("size")].toInt();

    QString dateString = groupchatData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

} // load from database
/**
 * @brief GroupChat::~GroupChat
 */
GroupChat::~GroupChat(){

}


/**
 * Adds a message to the message history of this groupchat
 * @brief GroupChat::add_message
 * @param message
 */
void GroupChat::add_message(Message *message){
    messageHistory[message->get_id()] = message;
}
/**
 * Adds a user to this groupchat's list of participants
 * @brief GroupChat::add_participant
 * @param profile
 */
void GroupChat::add_participant(Profile *profile){

    participants[profile->get_id()] = profile;
    size++;
}
/**
 * Removes a message from the message history
 * @brief GroupChat::remove_message
 * @param message
 */
void GroupChat::remove_message(Message *message){
    messageHistory.erase(message->get_id());
}
/**
 * Removes a participant from this groupchat
 * @brief GroupChat::remove_participant
 * @param profile
 */
void GroupChat::remove_participant(Profile *profile){

    participants.erase(profile->get_id());
    size--;
}
/**
 * Sets the owner of this groupchat
 * @brief GroupChat::set_owner
 * @param profile
 */
void GroupChat::set_owner(Profile *profile){
    owner = profile;
}
/**
 * @brief GroupChat::get_id
 * @return id of this groupchat
 */
int GroupChat::get_id(){
    return groupchatId;
}
/**
 * @brief GroupChat::get_name
 * @return name of this groupchat
 */
QString GroupChat::get_name(){
    return name;
}
/**
 * @brief GroupChat::get_size
 * @return number of participants in this groupchat
 */
int GroupChat::get_size(){
    return size;
}
/**
 * @brief GroupChat::get_dateCreated
 * @return the date this groupchat was created
 */
QDateTime GroupChat::get_dateCreated(){
    return dateCreated;
}
/**
 * @brief GroupChat::get_owner
 * @return owner of this groupchat
 */
Profile *GroupChat::get_owner(){
    return owner;
}
/**
 * @brief GroupChat::get_participants
 * @return list of participants in this groupchat
 */
std::map<int, Profile*> GroupChat::get_participants(){
    return participants;
}
std::map<int, Message*> GroupChat::get_messageHistory(){
    return messageHistory;
}
