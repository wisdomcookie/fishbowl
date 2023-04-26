#ifndef POSTCOMMENT_H
#define POSTCOMMENT_H

#include "qdatetime.h"
class Profile;
class Post;

class PostComment
{
public:
    PostComment();
    //load from database
    PostComment(int id, Profile *creator, QDateTime dateCreated, Post *sourcePost, PostComment *sourceComment, QString content);
    PostComment(int id, Profile *creator, Post *post, QString content);  // User creates new comment
    PostComment(int id, Profile *creator, Post *post, PostComment *parentComment, QString content); //User creates new comment that is a reply to another comment
    PostComment(std::map<QString, QString> commentData); // load from database actual

    ~PostComment();

    void add_reply(PostComment *reply);

    void set_parentComment(PostComment *comment);

    int get_id();
    Profile *get_creator();
    QDateTime get_dateCreated();
    Post *get_sourcePost();
    PostComment *get_parentComment();
    std::vector<PostComment*> get_replies();
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
