#ifndef POSTCOMMENT_H
#define POSTCOMMENT_H
#include "../profiles/profile.h"

#include "post.h"

class PostComment
{
public:
    PostComment();
    //load from database
    PostComment(int id, Profile *creator, QDateTime dateCreated, Post *sourcePost, PostComment *sourceComment, std::vector<PostComment*> replies, QString content);
    PostComment(Profile *creator, Post *sourcePost, PostComment *sourceComment, QString content);     //User creates new comment

    ~PostComment();

    int get_id();
    Profile *get_creator();
    QDateTime get_dateCreated();
    Post *get_sourcePost();
    PostComment *get_sourceComment();
    std::vector<PostComment*> get_replies();
    QString get_content();

private:
    int id;
    Profile *creator;
    QDateTime dateCreated;
    Post *sourcePost;
    PostComment *sourceComment;
    std::vector<PostComment*> replies;
    QString content;

};

#endif // POSTCOMMENT_H
