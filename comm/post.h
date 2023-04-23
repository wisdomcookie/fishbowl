#ifndef POST_H
#define POST_H


#include "qdatetime.h"
#include <vector>
class Profile;
class Group;


class PostComment;

class Post
{
public:
    Post();
    Post(int id, Profile *creator, Group *group, QString title, QString content, QDateTime dateCreated, std::vector<PostComment*> comments); // Load from database
    Post(Profile *creator, Group *group, QString title, QString content); // User creates new post
    ~Post();

    void set_content(QString newContent);

    int get_id();
    Profile *get_creator();
    Group *get_sourceGroup();
    QString get_title();
    QString get_content();
    QDateTime get_dateCreated();
    std::vector<PostComment*> get_comments();

private:
    int id;
    Profile *creator;
    Group *sourceGroup;
    QString title;
    QString content;
    QDateTime dateCreated;
    std::vector<PostComment*> comments;
};

#endif // POST_H
