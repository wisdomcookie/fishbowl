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


.separator ","
.mode csv
.import "data/profiles.csv"            profiles
.import "data/groups.csv"              groups
.import "data/group_participants.csv" group_participants
.import "data/friends.csv"            friends
.import "data/fish.csv"               fish
.import "data/login.csv"              login
