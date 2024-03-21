#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QWidget>
#include <QtMqtt/qmqttmessage.h>
#include <QtMqtt/QMqttClient>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QHostAddress>
#include <QHostInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <json/json.h>
#include <iostream>
#include <time.h>
#include <error.h>
//#include "login.h"

extern int uid;

#define TIMEMS qPrintable (QTime::currentTime().toString("HH:mm:ss zzz"))

QT_BEGIN_NAMESPACE
namespace Ui { class mqttclient; }
QT_END_NAMESPACE

class mqttclient : public QWidget
{
    Q_OBJECT

public:
    mqttclient(QWidget *parent = nullptr);
    ~mqttclient();

private slots:
    void onMQTT_Connected();
    void onMQTT_Disconnected();
    void onMQTT_subscribed(const QString &topic);//产生订阅信号
    void receiveMess(const QByteArray &msg,const QMqttTopicName topic);//接收数据

    void on_btn_conn_clicked();

    void on_btn_pub_clicked();

    void on_btn_pub_clear_clicked();

    void on_btn_sub_clear_clicked();

    void on_pushButton_pub_clicked();

    void on_btn_sub_clicked();

    void on_btn_openled_clicked();

    void on_btn_closeled_clicked();

    void on_btn_opencurtain_clicked();

    void on_btn_closecurtain_clicked();

    void on_btn_increase_clicked();

    void on_btn_decrease_clicked();

    void on_btn_history_clicked();

    void on_btn_select_clicked();

private:
    Ui::mqttclient *ui;
    QMqttClient *client;
    QTimer *m_pTimer;
    uint16_t countTime;//定时时间
    QFont font;
    void word_style(QFont font);
    void uiChange(bool isEnabled);
    void writeSetting(void);
    void readSettings(void);

    void sqlInit();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    Json::Reader reader;
    Json::Value root;

    //int uid = 2;

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MQTTCLIENT_H
