#ifndef CHAT_H
#define CHAT_H
#include "QDateTime"
#include "../profiles/profile.h"

class Chat
{
public:
    Chat();
    Chat(int id, QDateTime dateCreated, std::set<Profile*> participants, std::vector<Message> messageHistory); // load from database
    Chat(QString name, std::vector<Profile*> participants); // user creates new groupchat
    ~Chat();

    void send_message(Profile *sender, QString content); // create and send message
    void send_message(Message msg); // send pre created message
    void delete_message(Message msg);

    std::vector<Profile*> get_participants();
    std::vector<Message> get_history();

protected:
    int id;
    int size;
    QDateTime dateCreated;
    std::vector<Profile*> participants;
    std::vector<Message> messageHistory;

};

#endif // CHAT_H
