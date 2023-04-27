#ifndef SESSION_H
#define SESSION_H

class Profile;

class Session
{
public:
    Session();

private:
    Profile *profile;
    bool is_admin;
};

#endif // SESSION_H
