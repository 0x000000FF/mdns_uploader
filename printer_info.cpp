#include "printer_info.h"

printer_info::printer_info(QString IP,QString hostname,QString state)
{
    this->IP_addr = IP;
    this->hostname = hostname;
    this->state = state;
}

void printer_info::change_state(QString state)
{
    this->state = state;
}

QString printer_info::get_IP()
{
    return this->IP_addr;
}

QString printer_info::get_hostname()
{
    return this->hostname;
}

QString printer_info::get_state()
{
    return this->state;
}
