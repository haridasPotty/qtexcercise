#include "memployee.h"
namespace DataSource_MonthlyEmployee{
    MEmployee::MEmployee(){}

    float MEmployee::NetSalaryCalculate(){
        return this->MonthlyCompensation;
    }

    bool MEmployee::SetMonthlyCompensation(uint32_t mcompensation_) {
        this->MonthlyCompensation = mcompensation_;
        return true;
    }

    uint32_t MEmployee::GetMonthlyCompensation() {
        return this->MonthlyCompensation;
    }
}//end of DataSource_MonthlyEmployee namespace
