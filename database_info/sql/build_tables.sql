create table profiles (
      profile_id   INTEGER,
      username     TEXT NOT NULL UNIQUE ,
      name         TEXT NOT NULL        ,
      type         TEXT NOT NULL        ,
      date_created DATE NOT NULL        ,
      description  TEXT                 ,
    primary key(profile_id)
    );

create table groups (
      group_id     INTEGER ,
      name         TEXT NOT NULL UNIQUE ,
      size         INTEGER  NOT NULL        ,
      date_created TEXT NOT NULL        ,
      description  TEXT,
    primary key(group_id)             
    );

create table group_participants (
      group_id     INTEGER NOT NULL                       ,
      profile_id   INTEGER NOT NULL                       ,
    foreign key (group_id) references groups(group_id) ,
    foreign key (profile_id) references profiles(profile_id));

create table friends (
      requestor_id INTEGER NOT NULL                               ,
      requested_id INTEGER NOT NULL                               ,
    CONSTRAINT request UNIQUE(requestor_id, requested_id)     , 
    foreign key (requestor_id) references profiles(profile_id) ,
    foreign key (requested_id) references profiles(profile_id));

create table fish (
      fish_id  INTEGER                       ,
      owner_id INTEGER NOT NULL                               ,
    foreign key (fish_id) references profiles(profile_id)  ,
    foreign key (owner_id) references profiles(profile_id),
    primary key(fish_id));

create table login (
      username TEXT,
      password TEXT NOT NULL        ,
    primary key(username),
    foreign key (username) references profiles(username));

-----------------------------------------------

create table posts (
      post_id     INTEGER ,
      poster_id   INTEGER  NOT NULL        ,
      date_posted TEXT NOT NULL        ,
      post_text   TEXT NOT NULL        ,
      group_id    INTEGER  NOT NULL        ,
      visibility  TEXT NOT NULL        ,
    primary key (post_id),
    foreign key (poster_id) references profiles(profile_id)
    foreign key (group_id) references groups(group_id));

create table post_comments (
      comment_id   INTEGER,
      post_id      INTEGER  NOT NULL        ,
      commenter_id INTEGER  NOT NULL        ,
      comment_text TEXT NOT NULL        ,
      comment_date TEXT NOT NULL        ,
    primary key (comment_id),
    foreign key (post_id) references posts(post_id),
    foreign key (commenter_id) references profiles(profile_id));

create table chats (
    chat_id INTEGER,
    name TEXT, 
    size INTEGER NOT NULL,
    date_created TEXT NOT NULL,
    primary key (chat_id));

create table chat_participants (
     chat_id INTEGER NOT NULL,
     participant_id,
    foreign key (chat_id) references chats(chat_id),
    foreign key (participant_id) references profiles(profile_id));

create table messages (
      message_id    INTEGER,
      sender_id     INTEGER  NOT NULL ,
      chat_id   INTEGER  NOT NULL ,
      content       TEXT NOT NULL ,
      message_date  TEXT,
    primary key (message_id),
    foreign key (sender_id) references profiles(profile_id) ,
    foreign key (chat_id) references chats(chat_id));

-----------------------------------------------------------------------------

create table banned_users (
      profile_id  INTEGER  NOT NULL ,
      group_id    INTEGER  NOT NULL ,
      ban_date    TEXT NOT NULL ,
      reason      TEXT NOT NULL ,
    foreign key (profile_id) references profiles(profile_id) ,
    foreign key (group_id) references groups(group_id));

create table admins (
      profile_id  INTEGER  NOT NULL ,
      group_id    INTEGER  NOT NULL ,
    foreign key (profile_id) references profiles(profile_id) ,
    foreign key (group_id) references groups(group_id));

create table reports (
      reporter_id INTEGER  NOT NULL ,
      reported_id INTEGER  NOT NULL ,
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
