#include "mqtt_mine.h"
#include "ui_mqtt_mine.h"

mqtt_mine::mqtt_mine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mqtt_mine)
{
    ui->setupUi(this);
}

mqtt_mine::~mqtt_mine()
{
    delete ui;
}



void mqtt_mine::on_btn_openled_clicked()
{

}

