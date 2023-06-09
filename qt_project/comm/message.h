#ifndef MESSAGE_H
#define MESSAGE_H

#include "QDateTime"

class Profile;
class GroupChat;

class Message
{
public:
    Message();
    Message(int id, Profile *sender, GroupChat *groupchat, QDateTime dateCreated, QString content); // user creates new groupchat
    Message(std::map<QString, QString> messageData); // load from database
    ~Message();

    void set_content(QString newContent);

    int get_id();
    int get_senderId();
    int get_groupchatId();
    QDateTime get_dateCreated();
    QString get_content();
    Profile *get_sender();
    GroupChat *get_groupchat();


private:
    int messageId;
    int senderId;
    int groupchatId;
    QDateTime dateCreated;
    QString content;

    Profile *sender;
    GroupChat *groupchat;


};

#endif // MESSAGE_H
