#ifndef SALESMAN_H
#define SALESMAN_H

#include "memployee.h"
namespace DataSource_Salesman{
class Salesman : public DataSource_MonthlyEmployee::MEmployee{
    float S_Bonus = 0;
    float S_RealisedOutcome = 0;
    float S_OutcomeClaim = 0;
public:
    Salesman();
    bool SetBonus(float);
    bool SetRealOutcome(float);
    bool SetOutcomeClaim(float);
    float NetSalaryCalculate() override;
};

#endif // SALESMAN_H
}//End of DataSource_Salesman namespace
