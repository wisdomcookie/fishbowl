#ifndef POSTCOMMENT_H
#define POSTCOMMENT_H

class Profile;

#include "post.h"

class PostComment
{
public:
    PostComment();
    //load from database
    PostComment(int id, Profile *creator, QDateTime dateCreated, Post *sourcePost, PostComment *sourceComment, std::vector<PostComment*> replies, QString content);
    PostComment(Profile *creator, Post *sourcePost, PostComment *sourceComment, QString content);     //User creates new comment
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

private:
    int commentId;
    int postId;
    int commenterId;
    int parentCommentId;
    QDateTime dateCreated;
    QString content;

    Profile *creator;
    Post *Post;
    PostComment *parentComment;
    std::map<int, PostComment*> replies;

};

#endif // POSTCOMMENT_H
