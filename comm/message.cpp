#include "message.h"

Message::Message()
{

}

Message::Message(Profile *sender, GroupChat *groupchat, QString content):
    sender(sender), groupchat(groupchat), content(content), timeSent(QDateTime::currentDateTime())
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
