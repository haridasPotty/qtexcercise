#include "hemp.h"
namespace DataSource_HourlyEmployee {
    HEmp::HEmp(){}
    float HEmp::NetSalaryCalculate(){
        return HourCompensation*HourDone;
    }
    bool HEmp::SetHourDone(float hourDone){
        this->HourDone = hourDone;
        return true;
    }
    bool HEmp::SetHourComp(float hourComp){
        this->HourCompensation = hourComp;
        return true;
    }
} //end of DataSource_HourlyEmployee namespace
