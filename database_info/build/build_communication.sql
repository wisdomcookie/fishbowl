create table posts (
      post_id     INT  NOT NULL UNIQUE ,
      poster_id   INT  NOT NULL        ,
      date_posted DATE NOT NULL        ,
      post_text   TEXT NOT NULL        ,
      group_id    INT  NOT NULL        ,
      visibility  TEXT NOT NULL        ,
    primary key (post_id)              ,
    foreign key (poster_id) references profile(profile_id));

create table postComments (
      comment_id   INT  NOT NULL UNIQUE ,
      post_id      INT  NOT NULL        ,
      commenter_id INT  NOT NULL        ,
      comment_text TEXT NOT NULL        ,
      comment_date DATE NOT NULL        ,
    primary key (comment_id)            ,
    foreign key (post_id) references posts(post_id),
    foreign key (commenter_id) references profile(profile_id));

create table messages (
      sender_id     INT  NOT NULL ,
      receiver_id   INT  NOT NULL ,
      content       TEXT NOT NULL ,
      message_date  DATE NOT NULL ,
    foreign key (sender_id) references profile(profile_id) ,
    foreign key (receiver_id) references profile(profile_id));

.separator ","
.mode csv
.import "build/posts.csv"         posts
.import "build/postComments.csv"  postComments
.import "build/messages.csv"      messages