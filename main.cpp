#include <QApplication>
#include "upload_window.h"
#include <QFileInfo>
#include <QMessageBox>
#include "panel_controller.h"
#include <QDebug>
#include <QSettings>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings *configIniRead = new QSettings("D:/preferences.ini", QSettings::IniFormat);
    QString language = configIniRead->value("/preference/language").toString();
    delete configIniRead;
    qDebug()<<language;

    QTranslator translator;
    if (language == "Chinese")
    {
        translator.load("D:\\zh_CN.qm");
        a.installTranslator(&translator);
    }
//    else
//    {
//        translator.load("D:\\en_CN.qm");
//    }

//    panel_controller *lo = new panel_controller("192.168.1.5");
//    lo->post_login();
//    lo->print("D:\\extruder_air-duct.gcode");
//    lo->upload_file("D:\\test.gcode");

//    upload_file upl;
//    upl.upload("http://192.168.1.4/upload-file/","D:/logo.png");
//    upl.upload(argv[1],argv[2]);
    qDebug()<<argv[1];

    QFileInfo file_inf(argv[1]);
    if (argc == 2 && !file_inf.fileName().endsWith(".gcode"))
    {
        QMessageBox::warning (0,
        "warning" ,"\"" + file_inf.fileName() + "\"" + " is not a gcode file!",
        QMessageBox::Cancel | QMessageBox::Escape ,0 );
        return 0;
    }

    upload_window w;
    w.show();

//    re->print("http://192.168.1.4/print-test/","");
//    re->print("http://192.168.1.206:8686/api/update_cashout/","");

    return a.exec();
}
