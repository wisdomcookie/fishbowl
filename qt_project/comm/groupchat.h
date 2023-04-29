#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QDateTime>
class Profile;
class Message;


class GroupChat
{
public:
    GroupChat();
    GroupChat(int id, Profile *owner, QString name, QDateTime dateCreated, std::vector<Profile*> participants); // user creates new groupchat
    GroupChat(std::map<QString, QString> groupchatData); // load from database
    ~GroupChat();

    void add_message(Message *message);
    void add_participant(Profile *profile);
    void remove_message(Message *message);
    void remove_participant(Profile *profile);
    void set_owner(Profile *profile);

    int get_id();
    QString get_name();
    int get_size();
    QDateTime get_dateCreated();
    Profile *get_owner();
    std::map<int, Profile*> get_participants();
    std::map<int, Message*> get_messageHistory();

private:
    int groupchatId;
    int ownerId;
    QString name;
    int size;
    QDateTime dateCreated;

    Profile *owner;
    std::map<int, Profile*> participants;
    std::map<int, Message*> messageHistory;

};

#endif // GROUPCHAT_H
