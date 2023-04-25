#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QObject>
#include "../profiles/profile.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr,
                   Profile* p = nullptr);
    ~Login();

signals:
    void back();

private slots:
    void on_loginButton_clicked();

    void on_create_accepted();

    void on_createNewAccount_clicked();

    void on_c_pword2_editingFinished();

private:
    Ui::Login *ui;
    Profile* p;
};

#endif // LOGIN_H
