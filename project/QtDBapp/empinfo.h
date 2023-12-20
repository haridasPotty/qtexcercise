#ifndef EMPINFO_H
#define EMPINFO_H
#include <QString>
#include <memory>
#include <QDebug>

class Emp{
    QString Name = "";
    QString Month = "";
    std::uint32_t SCNumber = 0;
public:
    Emp() ;
    virtual ~Emp() = default;
    virtual float NetSalaryCalculate() = 0;
    Emp(const Emp&) = delete;
    bool SetName(QString );
    bool SetMonth(QString );
    bool SetSCNumber(std::uint32_t);
};
#endif // EMPINFO_H


