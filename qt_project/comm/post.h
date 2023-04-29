#ifndef POST_H
#define POST_H


#include <QDateTime>
#include <vector>
class Profile;
class Group;


class PostComment;

class Post
{
public:
    Post();
    Post(int id, Profile *creator, Group *group, QDateTime dateCreated, QString title, QString content); // User creates new post
    Post(std::map<QString, QString> postData); // load from database actual
    ~Post();

    void set_content(QString newContent);
    void set_creator(Profile *profile);
    void set_group(Group *group);
    void add_comment(PostComment *comment);
    void remove_comment(PostComment *comment);


    int get_id();
    Profile *get_creator();
    Group *get_sourceGroup();
    QDateTime get_dateCreated();
    QString get_title();
    QString get_content();
    bool get_visibility();
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
    Group *group;
    std::map<int, PostComment*> comments;
};

#endif // POST_H
