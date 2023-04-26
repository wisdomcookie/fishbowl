#include "message.h"
#include "../profiles/profile.h"
#include "groupchat.h"

Message::Message()
{

}

Message::Message(int id, Profile *sender, GroupChat *groupchat, QString content):
    messageId(id), senderId(sender->get_id()), groupchatId(groupchat->get_id()), dateCreated(QDateTime::currentDateTimeUtc()), content(content), sender(sender), groupchat(groupchat)
{

}

Message::~Message(){

}

void Message::set_content(QString newContent){
    content = newContent;
}

int Message::get_id(){
    return id;
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

QDateTime Message::get_time_sent(){
    return timeSent;
}

