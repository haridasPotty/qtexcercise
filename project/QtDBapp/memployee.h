#ifndef MEMPLOYEE_H
#define MEMPLOYEE_H

#include "empinfo.h"
namespace DataSource_MonthlyEmployee{
class MEmployee : public Emp{
    std::uint32_t MonthlyCompensation = 0;
public:
    MEmployee();
    virtual ~MEmployee() = default;
    float NetSalaryCalculate() override;
    bool SetMonthlyCompensation(std::uint32_t );
    std::uint32_t GetMonthlyCompensation();
};

#endif // MEMPLOYEE_H
}//end of DataSource_MonthlyEmployee namespace
