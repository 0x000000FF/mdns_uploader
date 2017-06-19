#ifndef REMOTE_CTL_H
#define REMOTE_CTL_H
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class remote_ctl : public QObject
{
    Q_OBJECT

public:
    remote_ctl();

private slots:
    void print(QString server,QString path);
    void get_reply(void);

private:
    QNetworkReply * reply;
//    QString url = "/print-test/";
signals:
    void replys(QString reply);
};

#endif // REMOTE_CTL_H
