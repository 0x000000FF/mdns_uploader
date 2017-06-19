#include "upload_file.h"
#include <QFileInfo>

upload_file::upload_file()
{
    this->percent = 0;
}

void upload_file::upload_progress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal != 0)
    {
        this->percent = bytesSent*100/bytesTotal;
    }
    else
    {
        return;
    }
    qDebug() << "Uploaded " << bytesSent << " of " << bytesTotal;
    qDebug()<<this->percent;

    emit send_percent(this->percent);
}

void upload_file::upload_done() {
//    qDebug() << "Finished" << reply->errorString() << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString mesg;
    mesg = reply->errorString();
    mesg += reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toString();
    mesg += reply->readAll();
    qDebug()<<"========returnmesg==========";
    qDebug()<<mesg;
    qDebug()<<"============================";

    qDebug() << reply->readAll();

    emit finished_mesg(mesg);

    reply->deleteLater();
}

void upload_file::upload(QString server_path, QString file_path)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    textPart.setBody("mostfun gcode");

    QFileInfo file_inf(file_path);
    qDebug()<<file_inf.fileName();
    qDebug()<<server_path;
    qDebug()<<file_path;
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\";  filename=\""+file_inf.fileName()+"\""));
    QFile *file = new QFile(file_path);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);

    //multiPart->append(textPart);
    multiPart->append(imagePart);

    QUrl url(server_path);
    QNetworkRequest request(url);

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(upload_progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(upload_done()));
}

