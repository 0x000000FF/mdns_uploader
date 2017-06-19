#include "upload_window.h"
#include "ui_upload_window.h"
#include "error_number.h"
#include <regex>
#include <QCoreApplication>
#include <QMessageBox>
#include <QWaitCondition>
#include <QDesktopServices>
#include <QEventLoop>
#include <QFileInfo>
#include <QScrollBar>

upload_window::upload_window(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::upload_window)
{
    ui->setupUi(this);
    this->ui->btn_upload->setDisabled(true);
    this->ui->btn_upl_print->setDisabled(true);
    this->ui->upload_percent->setVisible(false);
    this->ui->upload_percent->setValue(0);
    this->ui->btn_cancel->setVisible(false);
    this->ui->btn_panel->setVisible(false);
    this->ui->btn_quit->setVisible(false);

    this->standard_iterm_model = new QStandardItemModel(this);
    this->list_printer_info.clear();
//    this->ui->list_printers->s

//    this->ui->table_printerstatus->setRowCount(0);
//    this->ui->table_printerstatus->setColumnCount(2);
//    this->ui->table_printerstatus->horizontalHeader()->setVisible(false);
//    this->ui->table_printerstatus->verticalHeader()->setVisible(false);
//    this->ui->table_printerstatus->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    this->ui->table_printerstatus->setSelectionBehavior(QAbstractItemView::SelectRows);
//    this->ui->table_printerstatus->setShowGrid(false);
//    this->ui->table_printerstatus->setColumnWidth(0,300);
//    this->ui->table_printerstatus->setColumnWidth(1,60);

    this->detector = new zero_conf_scaner();
    this->controller = new panel_controller("");

    this->autostart = false;
    this->is_login = false;

    this->argvs = QCoreApplication::arguments();

    qDebug()<<this->argvs;
    qDebug()<<argvs.length();

    if(argvs.length() == 1)
    {
        this->ui->btn_upload->setVisible(false);
        this->ui->btn_upl_print->setVisible(false);
        this->ui->label_prompt->setVisible(true);

    }
    else
    {
        this->ui->label_prompt->setVisible(false);
    }

    connect(this->detector, SIGNAL(add_item(QZeroConfService *)), this, SLOT(add_new_priner(QZeroConfService *)));
    connect(this->detector, SIGNAL(del_item(QZeroConfService *)), this, SLOT(del_printer(QZeroConfService *)));
    connect(this->controller, SIGNAL(percent_mesg(int)),this,SLOT(show_percent(int)));
//    connect(this->controller, SIGNAL(finished_mesg(QString)),this,SLOT(show_return(QString)));
    connect(this->controller, SIGNAL(replys(QNetworkReply *)),this,SLOT(show_return(QNetworkReply *)));

    connect(this, SIGNAL(set_server_url(QString)),this->controller,SLOT(set_server(QString)));
    connect(this, SIGNAL(login_server(void)),this->controller,SLOT(post_login(void)));
    connect(this, SIGNAL(start_upload(QString)),this->controller,SLOT(upload_file(QString)));
    connect(this, SIGNAL(start_print(QString)),this->controller,SLOT(print(QString)));
    connect(this, SIGNAL(get_state(QString)),this->controller,SLOT(get_state(QString)));

    connect((QWidget*)this->ui->list_printers->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(list_scoll_sync(int)));
    connect((QWidget*)this->ui->list_printerstatus->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(list_scoll_sync(int)));
}


upload_window::~upload_window()
{
    delete ui;
}

void upload_window::list_scoll_sync(int value)
{
    this->ui->list_printerstatus->verticalScrollBar()->setValue(value);
    this->ui->list_printers->verticalScrollBar()->setValue(value);
}

bool upload_window::check_login()
{
    emit login_server();
    return false;
}

void upload_window::add_new_priner(QZeroConfService *zcs)
{
//    this->list_zcs.append(zcs);
    this->list_printer_info.append(new printer_info(zcs->ip.toString(),zcs->host,"unknown"));
//    QListWidgetItem * itm;
    this->ui->list_printers->addItem(new QListWidgetItem(QIcon(":/img/printer"),zcs->host));
    this->ui->list_printerstatus->addItem(new QListWidgetItem("--"));
    emit this->get_state(zcs->ip.toString());
    if (this->ui->list_printers->count() == 1)
    {
        this->ui->list_printers->setCurrentRow(0);
//        this->ui->list_printerstatus->setCurrentRow(0);
    }
//    this->ui->table_printerstatus->setRowCount(this->ui->table_printerstatus->rowCount() + 1);
//    this->ui->table_printerstatus->setItem(this->ui->table_printerstatus->rowCount()-1,0,new QTableWidgetItem(QIcon(":/img/printer"),zcs->host));

//    QStandardItem *item = new QStandardItem(zcs->name);
//    item->setEditable(false);
//    this->standard_iterm_model->appendRow(item);
//    this->ui->list_printers->setFixedSize(200,300);
}

void upload_window::del_printer(QZeroConfService *zcs)
{
//    for (int i = 0;i < this->list_printer_info.length(); i++)
//    {
//        if (this->list_printer_info.at(i)->get_IP() == zcs->ip.toString())
//        {
//            this->list_printer_info.removeAt(i);
//            this->ui->list_printers->removeItemWidget(this->ui->list_printers->item(i));
//            return;
//        }
//    }

}

void upload_window::on_txt_IP_textChanged(const QString &arg1)
{
//    qDebug()<<"____________________________";
    qDebug() << arg1;
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
//    int pos = regExp.indexIn(arg1);
//    qDebug() << pos;
    if(regExp.indexIn(arg1) < 0)
    {
//        qDebug()<<"disable button";
        this->ui->btn_upload->setDisabled(true);
        this->ui->btn_upl_print->setDisabled(true);
    }
    else
    {
        this->ui->btn_upload->setDisabled(false);
        this->ui->btn_upl_print->setDisabled(false);
        emit set_server_url(arg1);
    }
}

bool upload_window::login()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    this->ui->label_mesg->setPalette(pe);
    this->ui->label_mesg->setText(tr("Logging..."));
    connect(this->controller, SIGNAL(replys(QNetworkReply *)),this,SLOT(show_return(QNetworkReply *)));
    emit login_server();

    if(this->reply->error() == QNetworkReply::NoError)
    {
        this->is_login = true;
        this->ui->label_mesg->setText(tr("Login success"));
        return true;
    }
    pe.setColor(QPalette::WindowText,Qt::red);
    this->ui->label_mesg->setPalette(pe);
    this->ui->label_mesg->setText(tr("Login failed!"));
    return false;
}

bool upload_window::upload()
{
    QPalette pe;
    QFileInfo file_inf(argvs[1]);
    if (this->login() == true)
    {
        this->ui->upload_percent->setVisible(true);
        pe.setColor(QPalette::WindowText,Qt::black);
        this->ui->label_mesg->setPalette(pe);
        this->ui->label_mesg->setText("\"" + file_inf.fileName() + "\"" + tr("is uploading..."));
        emit start_upload(this->argvs[1]);

        if (this->reply->error() == QNetworkReply::NoError)
        {
            this->ui->label_mesg->setText(tr("Upload success!"));
            this->ui->upload_percent->setVisible(false);
            return true;
        }

    }
    pe.setColor(QPalette::WindowText,Qt::red);
    this->ui->label_mesg->setPalette(pe);
    this->ui->label_mesg->setText(tr("upload failed!"));
    return false;
}

void upload_window::on_btn_upload_clicked()
{
    this->ui->btn_upload->setVisible(false);
    this->ui->btn_upl_print->setVisible(false);
    this->ui->btn_cancel->setVisible(true);
//    this->autostart = false;
    this->upload();
    this->finished();
}

void upload_window::on_btn_upl_print_clicked()
{
    this->ui->btn_upload->setVisible(false);
    this->ui->btn_upl_print->setVisible(false);
    this->ui->btn_cancel->setVisible(true);
//    this->autostart = true;
//    this->autostart = false;
    if (this->upload() == true)
    {
        emit start_print(this->argvs[1]);
    }
    this->finished();
//    this->ui->label_mesg->setText("Starting print...");
}

void upload_window::show_percent(int percent)
{
    if (percent >= 0 && percent <=100)
    {
        this->ui->upload_percent->setValue(percent);
    }
}

bool upload_window::finished()
{
    this->ui->btn_cancel->setVisible(false);
    this->ui->btn_panel->setVisible(true);
    this->ui->btn_quit->setVisible(true);

    return true;
}

void upload_window::show_return(QNetworkReply * reply)
{
    this->reply = reply;

//    QString mesg = this->reply->;
    QString reply_str = reply->readAll();

//    qDebug()<<"show replays _________";
    qDebug()<<this->reply->url().toString();
    qDebug()<<this->reply->errorString();
    qDebug()<<this->reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toString();
    qDebug()<<reply_str;

    if (this->reply->error() != QNetworkReply::NoError)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);
        this->ui->label_mesg->setPalette(pe);
        this->ui->label_mesg->setText(tr("Network ERROR!"));
        QMessageBox::warning (0,"warning" , this->reply->url().toString() + ":" + this->reply->errorString(),
        QMessageBox::Cancel | QMessageBox::Escape ,0 );
    }

    if (reply->url().toString().indexOf("state")>0)
    {
        int index = 0;
        foreach (printer_info * printer, this->list_printer_info)
        {
            if(reply->url().toString().indexOf(printer->get_IP()) > -1)
            {
//                qDebug()<<"found";
                break;
            }
            index ++;
        }
        if(reply_str.indexOf("ready") > -1)
        {
            this->list_printer_info[index]->change_state("ready");
            this->ui->list_printers->item(index)->setIcon(QIcon(":/img/printer_ready"));
            this->ui->list_printerstatus->item(index)->setBackgroundColor(Qt::green);
            this->ui->list_printerstatus->item(index)->setText(tr("Ready"));
//            this->ui->table_printerstatus->setItem(index,1,new QTableWidgetItem(tr("Ready")));
        }
        else if (reply_str.indexOf("printing") > -1)
        {
            this->list_printer_info[index]->change_state("printing");
            this->ui->list_printers->item(index)->setIcon(QIcon(":/img/printer_notready"));
            this->ui->list_printerstatus->item(index)->setBackgroundColor(Qt::yellow);
            this->ui->list_printerstatus->item(index)->setText(tr("Printing"));
//            this->ui->table_printerstatus->setItem(index,1,new QTableWidgetItem(tr("Busy")));
        }
        else
        {
            this->list_printer_info[index]->change_state("unknown");
            this->ui->list_printers->item(index)->setIcon(QIcon(":/img/printer_notready"));
            this->ui->list_printerstatus->item(index)->setBackgroundColor(Qt::red);
            this->ui->list_printerstatus->item(index)->setText(tr("Error"));
//            this->ui->table_printerstatus->setItem(index,1,new QTableWidgetItem(tr("Error")));
        }
    }

//    this->ui->label_mesg->setText(mesg);
//    if (mesg =="Unknown error200{\n  \"maintenancetime\": false, \n  \"url\": \"/index/\"\n}")
//    if(reply->error() == QNetworkReply::NoError)
//    {
//        this->is_login = true;
//    }
//    else if (mesg == "Unknown error200{\"code\": 1}")
//    else
//    {
//        this->ui->label_mesg->setText("upload success!");
//        if (this->autostart)
//        {
//            qDebug()<<"***start print";
//            this->ui->label_mesg->setText("Starting print...");
//            emit start_print(this->argvs[1]);
//        }
//        else
//        {
//            this->finished();
//        }
//    }
//    else if (mesg == "Unknown error200{\"code\": 2}")
//    {
//        QPalette pe;
//        pe.setColor(QPalette::WindowText,Qt::red);
//        this->ui->label_mesg->setPalette(pe);
//        this->ui->label_mesg->setText("can not start printing!");
//        QMessageBox::warning (0,"warning" , "mostfun Pro is busy!Can not start printing!",
//        QMessageBox::Cancel | QMessageBox::Escape ,0 );
//        this->finished();
//    }

//    else
//    {
//        this->ui->label_mesg->setText("Unknown ERROR");
//        QPalette pe;
//        pe.setColor(QPalette::WindowText,Qt::red);
//        this->ui->label_mesg->setPalette(pe);
//        this->ui->label_mesg->setText("Unknow ERROR!");
//        QMessageBox::warning (0,"warning" ,mesg,QMessageBox::Cancel | QMessageBox::Escape ,0 );
//        this->finished();
//    }
}


void upload_window::on_btn_cancel_clicked()
{
    int ret = QMessageBox::warning(this, tr("Cancel upload"),
                                   tr("Are you sure to cancel?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        exit(0);
    }
}

void upload_window::on_btn_panel_clicked()
{
    QDesktopServices::openUrl(QUrl("http://" + this->ui->txt_IP->text()));
}

void upload_window::on_btn_quit_clicked()
{
    exit(0);
}

void upload_window::on_list_printers_doubleClicked(const QModelIndex &index)
{
    QDesktopServices::openUrl(QUrl("http://" + this->ui->txt_IP->text()));
}

void upload_window::on_list_printerstatus_currentRowChanged(int currentRow)
{
    this->ui->list_printers->setCurrentRow(currentRow);
}

void upload_window::on_list_printers_currentRowChanged(int currentRow)
{
    QString str_IP = this->list_printer_info[currentRow]->get_IP();
    this->ui->txt_IP->setText(str_IP);
//    this->ui->list_printerstatus->setCurrentRow(currentRow);
//    QPalette pe;
//    if(this->list_printer_info[currentRow]->get_state() != "ready")
//    {
//        this->ui->btn_upl_print->setDisabled(true);
//        if (this->list_printer_info[currentRow]->get_state() == "printing")
//        {
//            pe.setColor(QPalette::WindowText,Qt::blue);
//            this->ui->label_mesg->setPalette(pe);
//            this->ui->label_mesg->setText(tr("Busy"));
//        }
//        else if (this->list_printer_info[currentRow]->get_state() == "unknown")
//        {
//            pe.setColor(QPalette::WindowText,Qt::red);
//            this->ui->label_mesg->setPalette(pe);
//            this->ui->label_mesg->setText(tr("Error"));
//        }
//    }
//    else
//    {
//        pe.setColor(QPalette::WindowText,Qt::green);
//        this->ui->label_mesg->setPalette(pe);
//        this->ui->label_mesg->setText(tr("Ready"));
//        this->ui->btn_upl_print->setDisabled(false);
//    }
}

