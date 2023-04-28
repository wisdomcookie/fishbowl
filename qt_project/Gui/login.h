#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QObject>
#include "../profiles/profile.h"
#include "../engine/engine.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void back(Profile* p/*, Engine* e*/);

private slots:
    void on_loginButton_clicked();

    void on_create_accepted();

    void on_createNewAccount_clicked();

    void on_c_pword2_editingFinished();

private:
    Ui::Login *ui;
    Profile* p;
    Engine* e;
};

#endif // LOGIN_H
