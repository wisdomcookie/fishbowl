#ifndef GROUP_H
#define GROUP_H


#include <vector>
#include <QDateTime>

class Profile;
class Post;
class Aquarium;

class Group
{
public:
    Group();
    Group(int id, Profile *creator, QString name, QDateTime dateCreated, QString description); // user creates new group
    Group(std::map<QString, QString> groupData); // load from database

    ~Group();

    void add_member(Profile *profile);
    void add_admin(Profile *admin);
    void add_post(Post *post);

    void remove_member(Profile *profile);
    void remove_admin(Profile *admin);
    void remove_post(Post *post);

    void ban_from_group(Profile *profile);

    bool is_admin(Profile *profile);
    bool is_member(Profile *profile);
    bool is_banned(Profile *profile);

    void set_description(QString newDescription);

    int get_id();
    QString get_name();
    int get_size();
    QDateTime get_dateCreated();
    QString get_description();
    std::map<int, Profile*> get_admin();
    std::map<int, Profile*> get_members();
    Aquarium *get_aquarium();

private:
    int groupId;
    QString name;
    int size;
    QDateTime dateCreated;
    QString description;

    std::map<int, Profile*> admin;
    std::map<int, Profile*> members;
    std::map<int, Profile*> bannedUsers;
    std::map<int, Post*> posts;
    Aquarium *aquarium;

};

#endif // GROUP_H
