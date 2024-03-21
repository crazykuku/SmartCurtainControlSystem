#include "mqttclient.h"
#include "mqtt_mine.h"
#include "login.h"

#include <QApplication>

int uid;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login ll;
    ll.show();
    uid = ll.getuid();
//    mqttclient w;
//    w.show();
//    mqtt_mine mm;
//    mm.show();
    return a.exec();
}
