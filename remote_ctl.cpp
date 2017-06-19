#include "remote_ctl.h"
#include <QFileInfo>

remote_ctl::remote_ctl()
{

}

void remote_ctl::get_reply() {
//    qDebug() << "Finished" << reply->errorString() << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString mesg;
    mesg = reply->errorString();
    mesg += reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toString();
    mesg += reply->readAll();
    qDebug()<<"========returnmesg==========";
    qDebug()<<mesg;
    qDebug()<<"============================";

    emit replys(mesg);

    reply->deleteLater();
}

void remote_ctl::print(QString server_path,QString file_path)
{
    QFileInfo file_inf(file_path);

    QByteArray json("{\"filename\":\"" + file_inf.fileName().toLatin1() + "\",\"path\":\"/home/mostfuncp/gcode/\"}");
//    QByteArray json("{\"filename\":\"test.gcode\",\"path\":\"/home/mostfuncp/gcode/\"}");
//    QByteArray postDataSize = QByteArray::number(json.size());
    qDebug()<<json;
    QUrl url(server_path);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
//    request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"content\""));

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    this->reply = manager->post(request, json);

//    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(upload_progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(get_reply()));
}


