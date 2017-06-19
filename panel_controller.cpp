#include "panel_controller.h"
#include <QEventLoop>
#include <QTextCodec>
#include <QFileInfo>

panel_controller::panel_controller(QString server)
{
    this->is_login = false;
    this->url_server = "http://" + server;
}

void panel_controller::set_server(QString server)
{
    this->url_server = "http://" + server;
}

void panel_controller::get_reply() {
//    qDebug() << "Finished" << reply->errorString() << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
//    QString mesg;
//    mesg = reply->errorString();
//    mesg += reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toString();
//    mesg += reply->readAll();
    qDebug()<<"========returnmesg==========";
    qDebug()<<reply->url().toString();
//    qDebug()<<mesg;
    qDebug()<<"============================";

    emit replys(reply);

    reply->deleteLater();
}

void panel_controller::post_login()
{
    QString server_path = this->url_server + this->url_login;
    QByteArray json("{\"password\":\"mostfun\",\"remember\":\"n\"}");
    qDebug()<<server_path;
    QUrl url(server_path);
    QNetworkRequest request(url);

    request.setRawHeader(QByteArray("Connection"), QByteArray("Keep-Alive"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader(QByteArray("User-Agent"), QByteArray("Mozilla/5.0 (Windows NT 10.0; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0"));

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    this->reply = manager->post(request, json);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), this, SLOT(get_reply()));
    loop.exec();

//    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QString data= codec->toUnicode(this->reply->readAll());

//    qDebug() << data;
//    qDebug() << "+++++++++++++++++++++++++++++";

    this->cookie_jar =  manager->cookieJar();

}

void panel_controller::upload_progress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal != 0)
    {
        this->upload_percent = bytesSent*100/bytesTotal;
    }
    else
    {
        return;
    }
    qDebug() << "Uploaded " << bytesSent << " of " << bytesTotal;
    qDebug()<<this->upload_percent;

    emit percent_mesg(this->upload_percent);
}

void panel_controller::upload_file(QString file_path)
{
    QString server_path = this->url_server + this->url_upload;
    qDebug()<<server_path;
    qDebug()<<file_path;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    textPart.setBody("mostfun gcode");

//    QVariant var;
//    var.setValue(this->my_cookie);
//    textPart.setHeader(QNetworkRequest::SetCookieHeader, var);

    QFileInfo file_inf(file_path);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\";  filename=\""+file_inf.fileName()+"\""));
    QFile *file = new QFile(file_path);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);

//    multiPart->append(textPart);
    multiPart->append(imagePart);

    QUrl url(server_path);
    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::SetCookieHeader, var);

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    manager->setCookieJar(this->cookie_jar);
    this->reply = manager->post(request, multiPart);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

//    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(upload_progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(get_reply()));
    loop.exec();

}

//void panel_controller::upload_done()
//{
//    QString mesg;
//    mesg = reply->errorString();
//    mesg += reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toString();
//    mesg += reply->readAll();
//    qDebug()<<"========upload done==========";
//    qDebug()<<mesg;
//    qDebug()<<"============================";

//    qDebug() << reply->readAll();

//    emit finished_mesg(mesg);

//    reply->deleteLater();
//}

void panel_controller::print(QString file_path)
{
    QString server_path = this->url_server + this->url_print;
    QFileInfo file_inf(file_path);

    QByteArray json("{\"filename\":\"" + file_inf.fileName().toLatin1() + "\",\"path\":\"/home/mostfuncp/gcode/\"}");
    qDebug()<<json;
    qDebug()<<file_path;
    qDebug()<<server_path;
    QUrl print_url(server_path);
    QNetworkRequest print_request(print_url);

    print_request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QNetworkAccessManager * print_manager = new QNetworkAccessManager();
    print_manager->setCookieJar(this->cookie_jar);
    this->reply = print_manager->post(print_request, json);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), this, SLOT(get_reply()));
    loop.exec();
//    manager->post(request, json);

//    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(upload_progress(qint64,qint64)));
}

void panel_controller::get_state(QString IP)
{
    QString server_path = "http://" + IP + this->url_state;
    QUrl url(server_path);
    QNetworkAccessManager * print_manager = new QNetworkAccessManager();
    this->reply = print_manager->get(QNetworkRequest(url));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), this, SLOT(get_reply()));
    loop.exec();
}
