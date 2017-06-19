#ifndef UPLOAD_WINDOW_H
#define UPLOAD_WINDOW_H

#include <QWizardPage>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QString>
#include <QStringList>

#include "zero_conf_detector.h"
#include "panel_controller.h"
#include "printer_info.h"

namespace Ui {
class upload_window;
}

class upload_window : public QWizardPage
{
    Q_OBJECT

public:
    explicit upload_window(QWidget *parent = 0);
    ~upload_window();

private slots:
    void add_new_priner(QZeroConfService *zcs);
    void del_printer(QZeroConfService *zcs);
    void on_txt_IP_textChanged(const QString &arg1);
    void on_btn_upload_clicked();
    void show_percent(int);
    void on_btn_upl_print_clicked();
    void on_btn_cancel_clicked();
    void on_btn_panel_clicked();
    void on_btn_quit_clicked();

    void list_scoll_sync(int);

    void on_list_printers_doubleClicked(const QModelIndex &index);

    void show_return(QNetworkReply * reply);

    void on_list_printerstatus_currentRowChanged(int currentRow);

    void on_list_printers_currentRowChanged(int currentRow);

signals:
    void set_server_url(QString server);
    void login_server();
    void start_upload(QString file);
    void start_print(QString file);
    void replay_received();
    void get_state(QString);

private:
    zero_conf_scaner *detector;
    panel_controller *controller;
    Ui::upload_window *ui;
    QStandardItemModel *standard_iterm_model;
//    QList<QZeroConfService *> list_zcs;
    QList<printer_info *> list_printer_info;
    QStringList argvs;
    QNetworkReply * reply;

    bool autostart;
    bool is_login;

    bool login();
    bool upload();
    bool finished();
    bool check_login();
};

#endif // UPLOAD_WINDOW_H
