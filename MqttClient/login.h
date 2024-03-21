#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QPalette>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include "mqttclient.h"
extern int uid;

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
int getuid();
private slots:
    void on_btn_sign_clicked();

    void on_btn_login_clicked();

private:
    Ui::login *ui;

    void sqlInit();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    //int uid;
    QString username;
    QString password;

    void paintEvent(QPaintEvent * ev);



};

#endif // LOGIN_H
