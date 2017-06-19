#include <QNetworkInterface>
#include "zero_conf_detector.h"
#include <qdebug>

#ifdef Q_OS_IOS
    #define	OS_NAME		"iOS"
#elif defined(Q_OS_MAC)
    #define	OS_NAME		"Mac"
#elif defined(Q_OS_ANDROID)
    #define	OS_NAME		"Android"
#elif defined(Q_OS_LINUX)
    #define	OS_NAME		"Linux"
#elif defined(Q_OS_WIN)
    #define	OS_NAME		"Windows"
#endif

zero_conf_scaner::zero_conf_scaner()
{
    connect(&zeroConf, SIGNAL(serviceAdded(QZeroConfService *)), this, SLOT(addService(QZeroConfService *)));
    connect(&zeroConf, SIGNAL(serviceRemoved(QZeroConfService *)), this, SLOT(removeService(QZeroConfService *)));

    zeroConf.startBrowser("_http._tcp");
}

void zero_conf_scaner::addService(QZeroConfService *zcs)
{
    if (zcs->name.indexOf("mostfun") > -1)
    {
        emit add_item(zcs);
        qDebug()<<"new service found !";
    }
    qDebug()<<zcs->name;
    qDebug()<<zcs->host;
    qDebug()<<zcs->ip.toString();
    qDebug()<<"===============";
}

void zero_conf_scaner::removeService(QZeroConfService *zcs)
{
    emit del_item(zcs);
    qDebug()<<"**service removed!";
    qDebug()<<zcs->name;
    qDebug()<<zcs->host;
    qDebug()<<zcs->ip.toString();
    qDebug()<<"***************";
}
