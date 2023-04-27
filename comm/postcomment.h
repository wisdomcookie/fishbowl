#ifndef POSTCOMMENT_H
#define POSTCOMMENT_H

#include <QDateTime>
class Profile;
class Post;

class PostComment
{
public:
    PostComment();
    PostComment(int id, Profile *creator, Post *post, QDateTime dateCreated, QString content);  // User creates new comment
    PostComment(int id, Profile *creator, Post *post, PostComment *parentComment, QDateTime dateCreated, QString content); //User creates new comment that is a reply to another comment
    PostComment(std::map<QString, QString> commentData); // load from database actual

    ~PostComment();

    void set_content(QString newContent);
    void add_reply(PostComment *reply);

    int get_id();
    Profile *get_creator();
    QDateTime get_dateCreated();
    Post *get_post();
    PostComment *get_parentComment();
    std::map<int, PostComment*> get_replies();
    QString get_content();
    bool get_visibility();

private:
    int commentId;
    int postId;
    int commenterId;
    int parentCommentId;
    QDateTime dateCreated;
    QString content;
    bool visibility;

    Profile *creator;
    Post *post;
    PostComment *parentComment;
    std::map<int, PostComment*> replies;

};

#endif // POSTCOMMENT_H
