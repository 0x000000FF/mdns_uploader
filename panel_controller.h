#ifndef LOGIN_H
#define LOGIN_H
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkCookieJar>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QNetworkRequest>


class panel_controller : public QObject
{
    Q_OBJECT

public:
    panel_controller(QString);

private slots:
    void get_state(QString);
    void post_login(void);
    void print(QString);
    void set_server(QString);
    void upload_file(QString);
    void upload_progress(qint64 bytesSent, qint64);
    void get_reply(void);

private:
//    QNetworkCookie my_cookie;
    QNetworkCookieJar * cookie_jar;
    qint64 upload_percent;
    QString server_url;
    QList<QString> files;
    QNetworkReply * login_reply;
    QNetworkReply * upload_reply;
    QNetworkReply * print_reply;
    QNetworkReply * state_reply;

    bool is_login;

    QString url_server = "";
    QString url_print = "/print-test/";
    QString url_login = "/login/";
    QString url_upload = "/upload-file/";
    QString url_state = "/device/state/";

public:
    QNetworkReply * reply;

signals:
    void login_replys(QNetworkReply *);
    void upload_replys(QNetworkReply *);
    void print_replys(QNetworkReply *);
    void replys(QNetworkReply *);
    void percent_mesg(int);
    void finished_mesg(QString);
    void printer_state(QString);
};

#endif // LOGIN_H
