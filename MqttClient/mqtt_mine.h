#ifndef MQTT_MINE_H
#define MQTT_MINE_H

#include <QWidget>

namespace Ui {
class mqtt_mine;
}

class mqtt_mine : public QWidget
{
    Q_OBJECT

public:
    explicit mqtt_mine(QWidget *parent = nullptr);
    ~mqtt_mine();

private slots:

    void on_btn_openled_clicked();

private:
    Ui::mqtt_mine *ui;
};

#endif // MQTT_MINE_H
