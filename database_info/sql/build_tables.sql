create table profiles (
      profile_id   INT  NOT NULL UNIQUE ,
      username     TEXT NOT NULL UNIQUE ,
      name         TEXT NOT NULL        ,
      type         TEXT NOT NULL        ,
      date_created DATE NOT NULL        ,
      description  TEXT                 ,
    primary key (profile_id));

create table groups (
      group_id     INT  NOT NULL UNIQUE ,
      name         TEXT NOT NULL UNIQUE ,
      size         INT  NOT NULL        ,
      date_created TEXT NOT NULL        ,
      description  TEXT                 ,
    primary key (group_id));

create table group_participants (
      group_id     INT NOT NULL                       ,
      profile_id   INT NOT NULL                       ,
    foreign key (group_id) references groups(group_id) ,
    foreign key (profile_id) references profiles(profile_id));

create table friends (
      requestor_id INT NOT NULL                               ,
      requested_id INT NOT NULL                               ,
    CONSTRAINT request UNIQUE(requestor_id, requested_id)     , 
    foreign key (requestor_id) references profiles(profile_id) ,
    foreign key (requested_id) references profiles(profile_id));

create table fish (
      fish_id  INT NOT NULL                               ,
      owner_id INT NOT NULL                               ,
    primary key (fish_id)                                 ,
    foreign key (fish_id) references profiles(profile_id)  ,
    foreign key (owner_id) references profiles(profile_id));

create table login (
      username TEXT NOT NULL UNIQUE ,
      password TEXT NOT NULL        ,
    primary key (username)          ,
    foreign key (username) references profiles(username));


create table posts (
      post_id     INT  NOT NULL UNIQUE ,
      poster_id   INT  NOT NULL        ,
      date_posted TEXT NOT NULL        ,
      post_text   TEXT NOT NULL        ,
      group_id    INT  NOT NULL        ,
      visibility  TEXT NOT NULL        ,
    primary key (post_id)              ,
    foreign key (poster_id) references profiles(profile_id)
    foreign key (group_id) references groups(group_id));

create table post_comments (
      comment_id   INT  NOT NULL UNIQUE ,
      post_id      INT  NOT NULL        ,
      commenter_id INT  NOT NULL        ,
      comment_text TEXT NOT NULL        ,
      comment_date TEXT NOT NULL        ,
    primary key (comment_id)            ,
    foreign key (post_id) references posts(post_id),
    foreign key (commenter_id) references profiles(profile_id));

create table messages (
      sender_id     INT  NOT NULL ,
      receiver_id   INT  NOT NULL ,
      content       TEXT NOT NULL ,
      message_date  TEXT NOT NULL ,
    foreign key (sender_id) references profiles(profile_id) ,
    foreign key (receiver_id) references profiles(profile_id));


create table banned_users (
      profile_id  INT  NOT NULL ,
      group_id    INT  NOT NULL ,
      ban_date    TEXT NOT NULL ,
      reason      TEXT NOT NULL ,
    foreign key (profile_id) references profiles(profile_id) ,
    foreign key (group_id) references groups(group_id));

create table admins (
      profile_id  INT  NOT NULL ,
      group_id    INT  NOT NULL ,
    foreign key (profile_id) references profiles(profile_id) ,
    foreign key (group_id) references groups(group_id));

create table reports (
      reporter_id INT  NOT NULL ,
      reported_id INT  NOT NULL ,
      type        TEXT NOT NULL ,
      reasoning   TEXT NOT NULL ,
    foreign key (reporter_id) references profiles(profile_id),
    foreign key (reported_id) references profiles(profile_id));

.separator ","
.mode csv

.import "data/profiles.csv"            profiles
.import "data/groups.csv"              groups
.import "data/group_participants.csv" group_participants
.import "data/friends.csv"            friends
.import "data/fish.csv"               fish
.import "data/login.csv"              login

.import "data/posts.csv"         posts
.import "data/post_comments.csv"  post_comments
.import "data/messages.csv"      messages

.import "data/banned_users.csv" banned_users
.import "data/admins.csv"      admins
.import "data/reports.csv"     reports