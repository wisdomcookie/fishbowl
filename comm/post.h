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
    Post(int id, Profile *creator, Group *group, QString title, QString content, QDateTime dateCreated, std::map<int, PostComment*> comments); // Load from database
    Post(Profile *creator, Group *group, QString title, QString content); // User creates new post
    Post(std::map<QString, QString> postData); // load from database actual
    ~Post();

    void set_content(QString newContent);
    void add_comment(PostComment *comment);

    int get_id();
    Profile *get_creator();
    Group *get_sourceGroup();
    QString get_title();
    QString get_content();
    QDateTime get_dateCreated();
    std::map<int, PostComment*> get_comments();

private:
    int postId;
    int posterId;
    int groupId;
    QDateTime dateCreated;
    QString title;
    QString content;
    bool visibility;

    Profile *creator;
    Group *sourceGroup;
    std::map<int, PostComment*> comments;
};

#endif // POST_H
