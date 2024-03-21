#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    sqlInit();

    ui->le_passwd->setEchoMode(QLineEdit::EchoMode::Password);
}

login::~login()
{
    delete ui;
    db.close();
}

void login::sqlInit()
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

void login::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/cover.jpg"),QRect());
}

void login::on_btn_sign_clicked()
{
    uid = ui->le_uid->text().toInt();
    username = ui->le_username->text();
    password = ui->le_passwd->text();
    QSqlQuery result;

    result.exec("SELECT uid FROM SmartCurtainSystem.T_USER;");
    QList<int> list;
    while(result.next())
    {
        //list.append(result.value(0).toString());
        list.push_back(result.value(0).toInt());
    }
    for (int s : list) {
        if(uid == s){
            QMessageBox::warning(this,"warning","用户已存在，请更改");
            return;
        }
    }
    result.prepare("insert into SmartCurtainSystem.T_USER (uid,username,password) values(?,?,?)");
    result.addBindValue(uid);
    result.addBindValue(username);
    result.addBindValue(password);
    if(result.exec())
        QMessageBox::warning(this,"warning","用户注册成功！");
    else
        QMessageBox::warning(this,"warning","用户注册失败！");

}


void login::on_btn_login_clicked()
{
    QString error;
    error = "uid,用户名或密码错误\n" + db.driverName();

    uid = ui->le_uid->text().toInt();
    username = ui->le_username->text();
    password = ui->le_passwd->text();
    QString struid = ui->le_uid->text();
    if(struid.isEmpty()||username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this,"warning","uid,用户名或密码不能为空");
    }
    else{
        QSqlQuery query;
        query.prepare("select uid,username,password from SmartCurtainSystem.T_USER where uid=:uid and username=:username and password=:password");
        query.bindValue(":uid",uid);
        query.bindValue(":username",username);
        query.bindValue(":password",password);
        query.exec();
        if(!query.next())
            QMessageBox::warning(this,"waring",error);
        else{
            QMessageBox::information(this,"信息","登录成功",QMessageBox::Ok);
            mqttclient* par = new mqttclient();
            this->close();
            par->show();
        }
    }
}

int login::getuid()
{
    return uid;
}
