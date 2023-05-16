#include "message.h"
#include "../profiles/profile.h"
#include "groupchat.h"
/**
 * @brief Message::Message
 */
Message::Message()
{

}
/**
 * Constructor for creating a new message
 * @brief Message::Message
 * @param id
 * @param sender
 * @param groupchat
 * @param dateCreated
 * @param content
 */
Message::Message(int id, Profile *sender, GroupChat *groupchat, QDateTime dateCreated, QString content):
    messageId(id), senderId(sender->get_id()), groupchatId(groupchat->get_id()), dateCreated(dateCreated), content(content), sender(sender), groupchat(groupchat)
{

} // user creates new message
/**
 * Constructor used to load messages from the database
 * @brief Message::Message
 * @param messageData
 */
Message::Message(std::map<QString, QString> messageData){
    messageId = messageData[QString("message_id")].toInt();
    senderId = messageData[QString("sender_id")].toInt();
    groupchatId = messageData[QString("groupchat_id")].toInt();

    QString dateString = messageData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    content = messageData[QString("content")];
} // load from database
/**
 * @brief Message::~Message
 */
Message::~Message(){

}


/**
 * Sets the content of this message
 * @brief Message::set_content
 * @param newContent
 */
void Message::set_content(QString newContent){
    content = newContent;
}
/**
 * @brief Message::get_id
 * @return this message's id
 */
int Message::get_id(){
    return messageId;
}
/**
 * @brief Message::get_senderId
 * @return the id of the profile that sent this message
 */
int Message::get_senderId(){
    return senderId;
}
/**
 * @brief Message::get_content
 * @return this message's text
 */
QString Message::get_content(){
    return content;
}
/**
 * @brief Message::get_sender
 * @return the profile that sent this message
 */
Profile *Message::get_sender(){
    return sender;
}
/**
 * @brief Message::get_groupchat
 * @return the groupcht this message was sent in
 */
GroupChat *Message::get_groupchat(){
    return groupchat;
}
/**
 * @brief Message::get_dateCreated
 * @return the date this message was sent
 */
QDateTime Message::get_dateCreated(){
    return dateCreated;
}

