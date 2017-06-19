#ifndef ZERO_CONF_SCANER_H
#define ZERO_CONF_SCANER_H
#include "qzeroconf.h"


class zero_conf_scaner : public QObject
{
    Q_OBJECT
public:
    zero_conf_scaner();
private:
    void buildGUI();
    QString buildName(void);
    QZeroConf zeroConf;

private slots:
    void addService(QZeroConfService *item);
    void removeService(QZeroConfService *item);

signals:
    void add_item(QZeroConfService *item);
    void del_item(QZeroConfService *item);
};

#endif // ZERO_CONF_SCANER_H
