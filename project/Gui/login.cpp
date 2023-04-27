#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

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
    p = new Profile(ui->uname->text().toStdString(), ui->pword->text().toStdString());
    emit back(p);
}


void Login::on_create_accepted()
{
    p = new Profile(ui->c_uname->text().toStdString(), ui->c_pword->text().toStdString());
    p->changeBio(ui->c_bio->toPlainText().toStdString());
    p->location = ui->c_location->text().toStdString();
    p->nameFirst = ui->fname->text().toStdString();
    p->nameLast = ui->lname->text().toStdString();
    p->age = ui->c_age->text().toStdString();
    emit back(p);
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

