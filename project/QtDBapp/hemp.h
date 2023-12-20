#ifndef HEMP_H
#define HEMP_H

#include "empinfo.h"
namespace DataSource_HourlyEmployee{
class HEmp : public Emp{
    float HourDone = 0;
    float HourCompensation = 0;
public:
    HEmp();
    virtual ~HEmp() = default;
    float NetSalaryCalculate() override;
    bool SetHourDone(float);
    bool SetHourComp(float);
};

#endif // HEMP_H
}//end of DataSource_HourlyEmployee namespace
