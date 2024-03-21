#include "mqttclient.h"
#include "ui_mqttclient.h"


mqttclient::mqttclient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mqttclient)
{
    ui->setupUi(this);

    client = new QMqttClient(this);
    m_pTimer = new QTimer(this);
    countTime = 0;

    sqlInit();

    /*设置文字风格*/
    word_style(font);
    connect(client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onMQTT_Disconnected()));
    connect(client, SIGNAL(messageReceived(QByteArray,QMqttTopicName)), this, SLOT(receiveMess(QByteArray,QMqttTopicName)));
    readSettings();
    uiChange(true);
}

mqttclient::~mqttclient()
{
    delete ui;
    db.close();
}

void mqttclient::sqlInit()
{
    db.setHostName("47.98.122.239");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("lxw122513");
    db.setDatabaseName("SmartCurtainSystem");

    if(db.open())
        qDebug()<<"db open success\n";
    else
        qDebug()<<"db open failed:"<<db.lastError()<<"\n";
}

/*连接成功*/
void mqttclient::onMQTT_Connected(){
    if(client->Disconnected){
        qDebug()<<"connect error\n";
        uiChange(true);
    }else{
        qDebug()<<"connect success\n";
        uiChange(false);
    }

}

/*断开连接*/
void mqttclient::onMQTT_Disconnected(){
    if(client->Disconnected){
        qDebug()<<"connect error\n";
    }else{
        qDebug()<<"connect success\n";
    }
    m_pTimer->stop();
    uiChange(true);
}


/*接收数据*/
void mqttclient::receiveMess(const QByteArray &msg,const QMqttTopicName topic){
     QString content;
     content = QDateTime::currentDateTime().toString() + QLatin1Char('\n');
     content += QLatin1String(" Received Topic: ") + topic.name() + QLatin1Char('\n');
     content += QLatin1String(" Message: ") + msg + QLatin1Char('\n');
     ui->textBrowser_recv->setTextColor(QColor("green"));
     ui->textBrowser_recv->append(content);


     std::string jsonbuffer = msg.toStdString();
     double Hum,Temp,Light;
     int LightMax;
     QString Led,Beep;

     // 目前如果JSON数据格式不对会出现异常，但一两条数据出错影响不大，直接抛出
     try {

         if(reader.parse(jsonbuffer,root))
         {

             Hum = root["Hum"].asDouble();
             Temp = root["Temp"].asDouble();
             Light = root["Light"].asDouble();
             LightMax = root["LightMax"].asInt();
             Led = root["Led"].asCString();
             Beep = root["Beep"].asCString();

         }else
             throw -1;

     } catch (...) {
         qDebug()<<"JSON 数据错误\n";
     }


     qDebug()<<"hum:"<<Hum<<"\n";
     qDebug()<<"temp:"<<Temp<<"\n";
     qDebug()<<"light:"<<Light<<"\n";
     qDebug()<<"lightmax:"<<LightMax<<"\n";
     qDebug()<<"Led:"<<Led<<"\n";
     qDebug()<<"Beep:"<<Beep<<"\n";
     qDebug()<<"uid:"<<uid<<"\n";

     QSqlQuery inssql(db);

     QDateTime origin_time = QDateTime::fromString("1970-01-01 08:00:00","yyyy-MM-dd hh:mm:ss");
     QDateTime timeCurrent = QDateTime::currentDateTime();
     qint64 Timestamp = origin_time.msecsTo(timeCurrent);
     //QString timeStr = timeCurrent.toString("[yy-MM-dd hh:mm:ss]");

     inssql.prepare("insert into T_SMARTCURTAIN (uid,Hum,Temp,Light,LightMax,Led,Beep,inTime,Timestamp) values(:uid,:Hum,:Temp,:Light,:LightMax,:Led,:Beep,:inTime,:Timestamp);");
     inssql.bindValue(":uid",uid);
     inssql.bindValue(":Hum",Hum);
     inssql.bindValue(":Temp",Temp);
     inssql.bindValue(":Light",Light);
     inssql.bindValue(":LightMax",LightMax);
     inssql.bindValue(":Led",Led);
     inssql.bindValue(":Beep",Beep);
     inssql.bindValue(":inTime",timeCurrent);
     inssql.bindValue(":Timestamp",Timestamp);


     if(inssql.exec())
         qDebug()<<"insert ok\n";
     else
         qDebug()<<"insert failed\n";

}
void mqttclient::onMQTT_subscribed(const QString &topic)
{
     qDebug() << "subscribed success!!" <<topic;

     ui->textBrowser_recv->setTextColor(QColor("seagreen"));
     ui->textBrowser_recv->append(QString("时间[%1] << %2").arg(TIMER_ABSTIME).arg("订阅成功"));
}


void mqttclient::word_style(QFont font)
{
    font.setBold(true);
    font.setPointSize(9);
    font.setFamily("Arial");
    font.setUnderline(true);
}

void mqttclient::uiChange(bool isEnabled)
{
    if(isEnabled)
    {
        ui->btn_conn->setText("连接");
                 ui->CleanSession->setEnabled(true);
                 ui->lineEdit_Port->setEnabled(true);
                 ui->lineEdit_ClientId->setEnabled(true);
                 ui->lineEdit_IP->setEnabled(true);
                 ui->lineEdit_password->setEnabled(true);
                 ui->lineEdit_username->setEnabled(true);
                 ui->lineEdit_time->setEnabled(true);
                 ui->btn_sub->setEnabled(false);
                 ui->btn_pub->setEnabled(false);
                 ui->lineEdit_subscribe->setEnabled(false);
                 ui->btn_pub_clear->setEnabled(false);
                 ui->lineEdit_publish->setEnabled(false);
                 ui->textEdit_publish->setEnabled(false);
                 ui->textBrowser_pub->setEnabled(false);
                 ui->pushButton_pub->setEnabled(false);
                 ui->textBrowser_recv->setEnabled(false);
                 ui->btn_sub_clear->setEnabled(false);
                 ui->btn_openled->setEnabled(false);
                 ui->btn_opencurtain->setEnabled(false);
                 ui->btn_closeled->setEnabled(false);
                 ui->btn_closecurtain->setEnabled(false);
                 ui->btn_increase->setEnabled(false);
                 ui->btn_decrease->setEnabled(false);
                /*设置格式字体*/
                 ui->Status_label->setText("等待连接");
                 ui->Status_label->setFont(font);
                 ui->Status_label->setAlignment(Qt::AlignCenter);
                 ui->Status_label->setStyleSheet("color: red;");


    }else{
        ui->btn_conn->setText("断开");
                ui->CleanSession->setEnabled(false);
                ui->lineEdit_Port->setEnabled(false);
                ui->lineEdit_time->setEnabled(false);
                ui->lineEdit_ClientId->setEnabled(false);
                ui->lineEdit_IP->setEnabled(false);
                ui->lineEdit_password->setEnabled(false);
                ui->lineEdit_username->setEnabled(false);
                ui->btn_sub->setEnabled(true);
                ui->btn_pub->setEnabled(true);
                ui->lineEdit_subscribe->setEnabled(true);
                ui->btn_pub_clear->setEnabled(true);
                ui->lineEdit_publish->setEnabled(true);
                ui->textBrowser_pub->setEnabled(true);
                ui->textEdit_publish->setEnabled(true);
                ui->textBrowser_recv->setEnabled(true);
                 ui->btn_sub->setEnabled(true);
                ui->btn_sub_clear->setEnabled(true);
                ui->pushButton_pub->setEnabled(true);
                ui->btn_openled->setEnabled(true);
                ui->btn_opencurtain->setEnabled(true);
                ui->btn_closeled->setEnabled(true);
                ui->btn_closecurtain->setEnabled(true);
                ui->btn_increase->setEnabled(true);
                ui->btn_decrease->setEnabled(true);
               /*设置格式字体*/
                ui->Status_label->setText("连接成功");
                ui->Status_label->setFont(font);
                ui->Status_label->setAlignment(Qt::AlignCenter);
                ui->Status_label->setStyleSheet("color: blue;");
}
}

void mqttclient::readSettings()
{
    QSettings settings("Rocfly Inc.", "MQTT");
    settings.setValue("geometry", saveGeometry());
    ui->lineEdit_IP->setText(settings.value("IP").toString());
    ui->lineEdit_Port->setText(settings.value("port").toString());
    ui->lineEdit_ClientId->setText(settings.value("ID").toString());
    ui->lineEdit_username->setText(settings.value("User_name").toString());
    ui->lineEdit_password->setText(settings.value("password").toString());
    ui->lineEdit_time->setText(settings.value("Time").toString());
    ui->CleanSession->setChecked(settings.value("clean",true).toBool());
    ui->lineEdit_publish->setText(settings.value("Publish").toString());
    ui->textEdit_publish->setText(settings.value("Publish_text").toString());
    ui->lineEdit_subscribe->setText(settings.value("subscript").toString());

}

void mqttclient::closeEvent(QCloseEvent *event){
    writeSetting();
    event->accept();
}
void mqttclient::writeSetting(){
    QSettings settings("Rocfly Inc.", "MQTT");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("IP",ui->lineEdit_IP->text());
    settings.setValue("port",ui->lineEdit_Port->text());
    settings.setValue("ID",ui->lineEdit_ClientId->text());
    settings.setValue("User_name",ui->lineEdit_username->text());
    settings.setValue("password",ui->lineEdit_password->text());
    settings.setValue("Time",ui->lineEdit_time->text());
    settings.setValue("clean",ui->CleanSession->isChecked());
    settings.setValue("Publish",ui->lineEdit_publish->text());
    settings.setValue("Publish_text",ui->textEdit_publish->toPlainText());
    settings.setValue("subscript",ui->lineEdit_subscribe->text());
}


void mqttclient::on_btn_conn_clicked()
{
    if(ui->btn_conn->text() == "连接")
    {
        if(!client->Disconnected)
        {
            QHostAddress host(ui->lineEdit_IP->text());
            if(host.isNull())
            {
                QHostInfo info = QHostInfo::fromName(ui->lineEdit_IP->text());
                if(info.error() == QHostInfo::NoError)
                {
                    QString hostname=QString(info.addresses().first().toString());
                    client->setProtocolVersion(QMqttClient::MQTT_5_0);
                    client->setCleanSession(ui->CleanSession->isChecked());
                    client->setHostname(hostname);
                    client->setPort(ui->lineEdit_Port->text().toInt());
                    client->setClientId(ui->lineEdit_ClientId->text());
                    client->setUsername(ui->lineEdit_username->text());
                    client->setPassword(ui->lineEdit_password->text().toLatin1());
                    client->setKeepAlive(ui->lineEdit_time->text().toInt());
                    ui->btn_conn->setText("连接中请等待...");
                    client->connectToHost();

                }
            }
            else
            {
                QString hostname=ui->lineEdit_IP->text();
                /*qDebug() << hostname;*/
                client->setProtocolVersion(QMqttClient::MQTT_5_0);
                client->setCleanSession(ui->CleanSession->isChecked());
                client->setHostname(hostname);
                client->setPort(ui->lineEdit_Port->text().toInt());
                client->setClientId(ui->lineEdit_ClientId->text());
                client->setUsername(ui->lineEdit_username->text());
                client->setPassword(ui->lineEdit_password->text().toLatin1());
                client->setKeepAlive(ui->lineEdit_time->text().toInt());

                ui->Status_label->setText("连接中请等待...");
                ui->Status_label->setFont(font);
                ui->Status_label->setStyleSheet("color: blue;");

                client->connectToHost();
            }
        }
    }
    else if(ui->btn_conn->text()=="断开")
    {
        if(!client->Disconnected)
        {
            client->disconnectFromHost();
        }

    }

}


void mqttclient::on_btn_pub_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = ui->textEdit_publish->toPlainText();
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_pub_clear_clicked()
{
    ui->textEdit_publish->clear();
}


void mqttclient::on_btn_sub_clear_clicked()
{
    ui->textBrowser_recv->clear();
}


void mqttclient::on_pushButton_pub_clicked()
{
    ui->textBrowser_pub->clear();
}


void mqttclient::on_btn_sub_clicked()
{
    if(client->Disconnected)
        {
            this->uiChange(true);

        }
        else
        {
            client->subscribe(ui->lineEdit_subscribe->text());
            ui->textBrowser_recv->setTextColor(QColor("red"));
            ui->textBrowser_recv->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("订阅成功"));
        }

}


void mqttclient::on_btn_openled_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"LED\",\"value\":1}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_closeled_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"LED\",\"value\":0}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_opencurtain_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"OPEN\",\"value\":1}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_closecurtain_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"OPEN\",\"value\":0}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_increase_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"INCREASE\",\"value\":1}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_decrease_clicked()
{
    if(client->Disconnected)
    {
        qDebug()<<"Disconnect\n";
    }
    else
    {
        QString msg = "{\"target\":\"INCREASE\",\"value\":0}";
        QByteArray ba;
        ba.append(msg.toUtf8());
        client->publish(ui->lineEdit_publish->text(),ba);
        qDebug() << "published success:" << msg;
        ui->textBrowser_pub->setTextColor(QColor("dodgerblue"));
        ui->textBrowser_pub->append(QString("时间[%1] >> %2").arg(TIMEMS).arg("发布成功"));
    }
}


void mqttclient::on_btn_history_clicked()
{
    if(ui->widget_his->isVisible())
    {
        ui->widget_his->hide();
    }else{
        ui->widget_his->show();
    }
}


void mqttclient::on_btn_select_clicked()
{
    ui->textEdit_his->clear();

    QString Hum,Temp,Light;

    QDateTime origin_time = QDateTime::fromString("1970-01-01 08:00:00","yyyy-MM-dd hh:mm:ss");
    QDateTime edit_starttime = ui->dateTimeEdit_start->dateTime();
    QDateTime edit_endtime = ui->dateTimeEdit_end->dateTime();
    qint64 nStartSteps = origin_time.msecsTo(edit_starttime);
    qint64 nEndSteps = origin_time.msecsTo(edit_endtime);
    if(nStartSteps>nEndSteps)
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","查询开始时间晚于结束时间!");
        return;
    }
    QString sStartSteps = QString("%1").arg(nStartSteps);
    QString sEndSteps = QString("%1").arg(nEndSteps);
    QString sFilter = "";//数据库查询语句

    //根据时间范围查询数据例如
    QSqlQuery selectsql(db);
    selectsql.prepare("select Hum,Temp,Light from T_SMARTCURTAIN where Timestamp between :start_time and :end_time");
    selectsql.bindValue(":start_time",sStartSteps);
    selectsql.bindValue(":end_time",sEndSteps);

    if(!selectsql.exec())
    {
        qDebug()<<"ERROR:"<<selectsql.lastError()<<"\n";
    }else{
        while(selectsql.next())
        {
            Hum = selectsql.value(0).toString();
            Temp = selectsql.value(1).toString();
            Light = selectsql.value(2).toString();
            qDebug()<<Hum<<","<<Temp<<","<<Light<<"\n";

            ui->textEdit_his->append("Hum:" + Hum + ",Temp:" + Temp + ",Light:" + Light);
        }
    }

}

