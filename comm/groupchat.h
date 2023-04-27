#ifndef GROUPCHAT_H
#define GROUPCHAT_H
#include "../profiles/profile.h"
#include "../comm_database/database.h"

#include "message.h"
#include <vector>
class GroupChat
{
public:
    GroupChat();
    GroupChat(int id, QString name, int size, QDateTime dateCreated, std::set<Profile*> participants, std::vector<Message> messageHistory); // load from database
    GroupChat(QString name, std::vector<Profile*> participants); // user creates new groupchat
    GroupChat(std::map<QString, QString> groupchatData);
    ~GroupChat();

    void add_message(Message *message);

    void add_participant(Profile *p);
    void remove_participant(Profile *p);
    void send_message(Profile *sender, QString content); // create and send message
    void send_message(Message msg); // send pre created message
    void delete_message(Message msg);

    int get_id();
    std::vector<Profile*> get_participants();
    std::vector<Message> get_history();

private:
    int id;
    QString name;
    int size;
    QDateTime dateCreated;
    std::map<int, Profile*> participants;
    std::map<int, Message> messageHistory;
    Database db;

};

#endif // GROUPCHAT_H
