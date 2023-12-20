#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H
#include <iostream>
#include <QString>
/*MEMP for Monthly paying employee,
 * HEMP for hourly paying employee,
 * SALESMAN for salesmen,
 * AllEMPs for getting all the employee info together
*/
enum class EmpType:std::uint16_t{
    SALESMAN,MEMP,HEMP,AllEMPs
};
/*Return types of functions*/
enum class RetType:std::uint16_t{
    OK = 0,
    NOK,
    AlreadyExist,
    EmpTypeMisMatch
};
typedef struct{
    QString Name;
    QString Month;
    std::uint32_t SCNumber = 0;
    std::uint32_t Mcompensation = 0;
    float HourDone = 0;
    float HourCompensation = 0;
    float SBonus = 0;
    float SRealisedOutcome = 0;
    float SoutcomeClaim = 0;
    float NetSalary;
}EmpInfo;

typedef struct{
    EmpInfo eInfo;
    EmpType eType;
}MetaInfo;
#endif // DATASOURCEMODEL_H
