#include "message.h"
#include "../profiles/profile.h"
#include "groupchat.h"

Message::Message()
{

}

Message::Message(int id, Profile *sender, GroupChat *groupchat, QDateTime dateCreated, QString content):
    messageId(id), senderId(sender->get_id()), groupchatId(groupchat->get_id()), dateCreated(dateCreated), content(content), sender(sender), groupchat(groupchat)
{

} // user creates new message

Message::Message(std::map<QString, QString> messageData){
    messageId = messageData[QString("message_id")].toInt();
    senderId = messageData[QString("senderr_id")].toInt();
    groupchatId = messageData[QString("groupchat_id")].toInt();

    QString dateString = messageData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    content = messageData[QString("content")];
} // load from database

Message::~Message(){

}

void Message::set_content(QString newContent){
    content = newContent;
}

int Message::get_id(){
    return messageId;
}

QString Message::get_content(){
    return content;
}

Profile *Message::get_sender(){
    return sender;
}

GroupChat *Message::get_groupchat(){
    return groupchat;
}

QDateTime Message::get_dateCreated(){
    return dateCreated;
}

