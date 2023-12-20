#include "salesman.h"
namespace  DataSource_Salesman {
    Salesman::Salesman(){}

    bool Salesman::SetBonus(float bonus_){
        this->S_Bonus = bonus_;
        return true;
    }

    bool Salesman::SetRealOutcome(float realOutcome){
        this->S_RealisedOutcome = realOutcome;
        return true;
    }

    bool Salesman::SetOutcomeClaim(float outcomeclaim_){
        this->S_OutcomeClaim =outcomeclaim_;
        return true;
    }

    float Salesman::NetSalaryCalculate(){
        float mComp = GetMonthlyCompensation();
        if(S_RealisedOutcome == S_OutcomeClaim){
            mComp = mComp + (mComp*S_Bonus);
        }
        return mComp;
    }

} //end of DataSource_Salesman namespace
