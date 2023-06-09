#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    e = new Engine();
    e->reload_data();

    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont("../../assets/lost_fish.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family, 60);
    ui->title_label->setFont(monospace);
    ui->title_label->setAlignment(Qt::AlignHCenter);

    ui->warning->hide();

    ui->stackedWidget->setCurrentIndex(0);
    ui->uname->setFocus();
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    p = e->loginEngine(ui->uname->text(), ui->pword->text());
    if (p == nullptr){
        ui->uname->clear();
        ui->pword->clear();
    } else {

        emit back(p, e);
        //this->hide();
        //emit back(p, e);
    }
}


void Login::on_create_accepted()
{
    e->create_profile(ui->c_uname->text(), ui->c_pword->text(), ui->fname->text(), ui->lname->text(), ui->c_age->text().toInt(),
                     ui->c_location->text(), QDateTime::currentDateTimeUtc(), ui->c_bio->toPlainText());
    p = e->get_profileList().back();
    //emit back(p);
    emit back(p, e);
}


void Login::on_createNewAccount_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Login::on_c_pword2_editingFinished()
{
    //check all necessary fields complete
    if (!ui->fname->text().isEmpty()) {
        if (!ui->lname->text().isEmpty()) {
            if (!ui->c_uname->text().isEmpty()) {
                if (!ui->c_pword->text().isEmpty()) {
                    if(ui->c_pword2->text() == ui->c_pword->text()){
                        ui->warning->hide();
                        ui->create->setEnabled(true);
                    } else ui->warning->show();
                }
            }
        }
    }
}

