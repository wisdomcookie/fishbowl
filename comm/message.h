#ifndef MESSAGE_H
#define MESSAGE_H

#include "QDateTime"

class Profile;
class GroupChat;

class Message
{
public:
    Message();
    Message(Profile *sender, GroupChat *groupchat, QString content);
    Message(std::map<QString, QString> messageData);
    ~Message();

    void set_content(QString newContent);

    int get_messageId();
    int get_senderId();
    int get_groupchatId();
    QString get_content();
    Profile *get_sender();
    GroupChat *get_groupchat();
    QDateTime get_time_sent();

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
