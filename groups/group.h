#ifndef GROUP_H
#define GROUP_H
#include "../admin/administrator.h"
#include "../profiles/aquarium.h"
#include "../profiles/person.h"
#include "../comm/post.h"
#include <string>
#include <vector>

class Group
{
public:
    Group();
    Group(std::string name);

    ~Group();

    void add_member();
    void remove_member(Person *profile);

    std::string get_name();
    std::string get_description();
    std::string get_admin();
    std::string get_members();
    Aquarium get_aquarium();


private:
    std::string name;
    std::string description;
    std::vector<Administrator*> admin;
    std::vector<Person*> members;
    std::vector<Post*> postHistory;
    Aquarium aquarium;

};

#endif // GROUP_H
