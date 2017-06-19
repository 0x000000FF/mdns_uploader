#ifndef UPLOAD_FILE_H
#define UPLOAD_FILE_H

#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QString>

class upload_file : public QObject
{
    Q_OBJECT
public:
    explicit upload_file();

private:
    QNetworkReply * reply;
    qint64 percent;

private slots:
    void upload(QString server_path,QString file_path);
    void upload_progress(qint64 bytesSent, qint64 bytesTotal);
    void upload_done();

signals:
    void send_percent(int percent);
    void finished_mesg(QString mesg);
};

#endif // UPLOAD_FILE_H
