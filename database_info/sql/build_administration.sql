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
.import "data/banned_users.csv" banned_users
.import "data/admins.csv"      admins
.import "data/reports.csv"     reports