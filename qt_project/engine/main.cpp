#include <iostream>
#include "database.h"
#include "QDateTime"
#include "engine.h"
#include "../profiles/profile.h"

using namespace std;

int main()
{
//    Database d;
//    d.open();

//    d.query_exec("select * from profiles;");
//    cout << d.query_size() << endl;
//    cout << d.query_string().toStdString() << endl;

//    d.query_exec("insert into profiles(username, name, type, date_created) values('nathandinh2', 'Nathan', 'user', date());");
//    d.query_exec("select * from profiles;");
//    cout << d.query_string().toStdString() << endl;

//    QString str = QDateTime::currentDateTimeUtc().toString();
//    d.query_exec("update profiles set(name, description, date_created) = ('Nathan2', 'check', '" + str + "') where username='nathandinh2';");
//    d.query_exec("select * from profiles;");
//    cout << d.query_string().toStdString() << endl;

//    d.query_exec("delete from profiles where username='nathandinh2';");
//    d.query_exec("select * from profiles;");
//    cout << d.query_string().toStdString() << endl;


//    std::vector<QString> fields = {QString("profile_id"), QString("username")};

//    std::vector<std::map<QString, QString>> res = d.query_select(QString("profiles"), fields);
//    cout << d.query_string().toStdString() << endl;

//    d.close();

//    cout << QDateTime::currentDateTimeUtc().toString(QString("yyyy-MM-dd hh:mm:ss")).toStdString() << endl;

//    QString str1("asd");
//    QString str2("gsdf");

//    cout << str1.toStdString();
//    cout << str2.toStdString();

//    str1 = str2;


//    cout << str1.toStdString();
//    cout << str2.toStdString();
//    cout << d.query_size();
//    cout << 0;

    Engine *e = new Engine();
    e->load_data();

    //e->create_profile(QString("bobby"), QString("bobby1"), QString("William"), QString("Dearing"), 1, QString("here"), QDateTime::currentDateTimeUtc(), QString("hi"));

    Profile *bobby = e->get_profileList().at(0);
    //e->create_group(p, QString("Grouptitle"), QDateTime::currentDateTimeUtc(), QString("descriptionssssssssss"));
    Group *group = e->get_groupList().at(0);
    //e->create_post(profile, group, QDateTime::currentDateTimeUtc(), QString("hi love me"), QString("please"));
    Post *post = e->get_postList().at(0);

    //e->create_comment(profile, post, QDateTime::currentDateTimeUtc(), QString("commentsssssss"));
    //e->create_profile(QString("kaela"), QString("bobby1"), QString("William"), QString("Dearing"), 6, QString("here"), QDateTime::currentDateTimeUtc(), QString("hi"));
    Profile *kaela = e->get_profileList().at(1);
//    e->join_group(kaela, group);
//    e->add_friend(bobby, kaela);
//    e->unfriend(bobby, kaela);
//    e->leave_group(kaela, group);
//    e->edit_profile(kaela, QString("Mikaela"), QString("Mercado"), 22, QString("Melbourne"), QString("katyperry"));
//    e->create_fish(kaela, QString("ad"), 34, QString("Purdue"), QString("longboi"), QDateTime::currentDateTimeUtc(), QString("pet"));
//    Fish *fish = kaela->get_fishList().at(0);
//    e->edit_fish(kaela, fish, QString("ad23"), 34, QString("PurdueTTTTT"), QString("longboi"), QString("pet"));

    e->edit_post(bobby, post, QString("newContent"));
    delete e;

    return 0;

}
