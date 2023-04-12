#ifndef GROUP_H
#define GROUP_H


#include <string>
#include <vector>
class Group
{
public:
    Group();
    Group(std::string name);


private:
    std::string name;
    std::string description;
    std::vector<Admin> admin;
    std::vector<Profile> members;

};

#endif // GROUP_H
