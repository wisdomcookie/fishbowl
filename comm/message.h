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
    ~Message();

    void set_content(QString newContent);

    int get_id();
    QString get_content();
    Profile *get_sender();
    GroupChat *get_groupchat();
    QDateTime get_time_sent();

private:
    int id;
    Profile *sender;
    GroupChat *groupchat;
    QString content;
    QDateTime timeSent;

};

#endif // MESSAGE_H
