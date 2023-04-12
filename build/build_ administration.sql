create table bannedUsers (
      profile_id  INT  NOT NULL ,
      group_id    INT  NOT NULL ,
      ban_date    DATE NOT NULL ,
      reason      TEXT NOT NULL ,
    foreign key (profile_id) references profile(profile_id) ,
    foreign key (group_id) references group(group_id));

create table admins (
      profile_id  INT  NOT NULL ,
      group_id    INT  NOT NULL ,
    foreign key (profile_id) references profile(profile_id) ,
    foreign key (group_id) references group(group_id));

create table reports (
      reporter_id INT  NOT NULL ,
      reported_id INT  NOT NULL ,
      type        TEXT NOT NULL ,
      reasoning   TEXT NOT NULL ,
    foreign key (reporter_id) references profile(profile_id));
    foreign key (reported_id) references profile(profile_id));

.separator ","
.mode csv
.import "build/bannedUsers.csv" bannedUsers
.import "build/admins.csv"      admins
.import "build/reports.csv"     reports