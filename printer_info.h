#ifndef PRINTER_INFO_H
#define PRINTER_INFO_H
#include <QString>

class printer_info
{
public:
    printer_info(QString,QString,QString);

private:
    QString IP_addr;
    QString hostname;
    QString state;

public:
    QString get_IP(void);
    QString get_hostname(void);
    QString get_state(void);
    void change_state(QString);
};

#endif // PRINTER_INFO_H
