#ifndef GROUP_H
#define GROUP_H

#include "../profiles/aquarium.h"
#include <set>
#include <string>
#include <vector>
#include "QString"
#include "qdatetime.h"

class Profile;
class Post;
class Aquarium;

class Group
{
public:
    Group();
    Group(QString name);
    Group(QString name, std::vector<Profile*> participants);
    Group(int id, QString name, int size, QDateTime dateCreated, QString description); // load from database
    Group(std::map<QString, QString> groupData); // load from database actual
    Group(int id, Profile *creator, QString name, QString description); // user creates new group

    ~Group();

    void add_member(Profile *profile);
    void remove_member(Profile *profile);
    void add_admin(Profile *admin);
    void remove_admin(Profile *admin);
    void add_post(Post *post);
    void remove_post(Post *post);

    void set_description(QString newDescription);
    void set_members(std::set<Profile *> members);
    void set_admin(std::set<Profile*> admin);
    void set_posts(std::vector<Post*> posts);

    int get_id();
    QString get_name();
    int get_size();
    QDateTime get_dateCreated();
    QString get_description();
    std::set<Profile*> get_admin();
    std::set<Profile*> get_members();
    Aquarium get_aquarium();

private:
    int groupId;
    QString name;
    int size;
    QDateTime dateCreated;
    QString description;

    std::map<int, Profile*> admin;
    std::map<int, Profile*> members;
    std::vector<Post*> posts;
    Aquarium aquarium;

};

#endif // GROUP_H
