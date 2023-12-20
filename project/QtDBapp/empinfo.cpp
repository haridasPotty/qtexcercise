#include "empinfo.h"

    Emp::Emp(){}

    bool Emp::SetName(QString name_){
        Name = name_;
        return true;
    }

    bool Emp::SetMonth(QString month_){
        this->Month = month_;
        return true;
    }

    bool Emp::SetSCNumber(uint32_t scnum_){
        this->SCNumber = scnum_;
        return true;
    }




