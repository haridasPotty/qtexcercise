#include "datasource_interface.h"

DataSource_Interface::DataSource_Interface(){
    if(dbc.DBInit()){
        if (dbc.DBConnect()){
           qDebug() << "connection successful";
           dbConnectionStatus = true;
        }
        else{
               qDebug() << "connection failed";
            }
    }
    else{
        qDebug() << "DB initialization has been failed";
    }
}
/*Insert Employee information into the data base.So
 *  mentioned Employee type as per the enumeration(EmpType),
 *  and then fill the relevant information.
 *   On success it returns true else false
*/
RetType DataSource_Interface::SetData(EmpType empType, EmpInfo& eInfo){
    if (empType == EmpType::MEMP){
        std::unique_ptr<MEmployee> mptr = std::make_unique<MEmployee>();
        mptr->SetMonthlyCompensation(eInfo.Mcompensation);
        eInfo.Mcompensation = mptr->NetSalaryCalculate();
        qDebug() <<eInfo.Name<< " Mcompensation" <<eInfo.Mcompensation;
        if (dbc.DBConnect()){
           qDebug() << "connection successful";
           MetaInfo mInfo;
           if(dbc.DBSearch(empType,eInfo.SCNumber,mInfo)){
               qDebug()<< eInfo.SCNumber <<"Already existing";
               return RetType::AlreadyExist;
           }
           if(dbc.DBInsert(EmpType::MEMP, eInfo)){
               return RetType::OK;
           }
           return RetType::NOK;
        }
    }
    else if (empType == EmpType::HEMP){
        std::unique_ptr<HEmp> hptr = std::make_unique<HEmp>();
        hptr->SetHourComp(eInfo.HourCompensation);
        hptr->SetHourDone(eInfo.HourDone);
        eInfo.NetSalary = hptr->NetSalaryCalculate();
        qDebug() << eInfo.Name<<": Netsalary" <<eInfo.NetSalary;
        if (dbc.DBConnect()){
           qDebug() << "connection successful";
           MetaInfo mInfo;
           if(dbc.DBSearch(empType,eInfo.SCNumber,mInfo)){
               qDebug()<< eInfo.SCNumber <<"Already existing";
               return RetType::AlreadyExist;
           }
           if(dbc.DBInsert(EmpType::HEMP, eInfo)){
               return RetType::OK;
           }
           return RetType::NOK;
        }
    }
    else if (empType == EmpType::SALESMAN){
        std::unique_ptr<Salesman> sptr = std::make_unique<Salesman>();
        sptr->SetBonus(eInfo.SBonus);
        sptr->SetMonthlyCompensation(eInfo.Mcompensation);
        sptr->SetRealOutcome(eInfo.SRealisedOutcome);
        sptr->SetOutcomeClaim(eInfo.SoutcomeClaim);
        eInfo.Mcompensation = sptr->NetSalaryCalculate();
        qDebug() << eInfo.Name<<": Mcompensation" <<eInfo.Mcompensation;
        if (dbc.DBConnect()){
           qDebug() << "connection successful";
           MetaInfo mInfo;
           if(dbc.DBSearch(empType,eInfo.SCNumber,mInfo)){
               qDebug()<< eInfo.SCNumber <<"Already existing";
               return RetType::AlreadyExist;
           }
           if(dbc.DBInsert(EmpType::SALESMAN, eInfo)){
               return RetType::OK;
           }
           return RetType::NOK;
        }
    }
    else{
        qDebug() << "EmpType mismatching";
    }
    return RetType::EmpTypeMisMatch;
}
/*Search for a particular Employee inforlation  w.r.t
 * Social security number,Employee type
 * On success it returns true else false*/
bool DataSource_Interface::GetData(EmpType empType,uint32_t secNumber,
                                                   MetaInfo& mInfo) {
    if (dbc.DBConnect()){
       qDebug() << "connection successful";
      if (dbc.DBSearch(empType, secNumber,mInfo) )
        return true;
      else
          qDebug() <<secNumber << "  Search failed";
    }
    return false;
}
/*Delete particular Employee information from the database,
 * based on Social security number,Employee type.
 * On success it returns true else false */
bool DataSource_Interface::DeleteData(EmpType empType,
                                       uint32_t secNumber) {
    if (dbc.DBConnect()){
       qDebug() << "connection successful";
      if (dbc.DBDelete(empType, secNumber) )
        return true;
      else
          qDebug() <<secNumber << "  Search failed";
    }
    return false;
}
/*Show all or particular group of Employees information
 *  On success it returns true else false*/
bool DataSource_Interface::Show(EmpType empType,std::vector<MetaInfo>& vMetaInfo){
    if (dbc.DBConnect()){
       qDebug() << "connection successful";
      if (dbc.DBShow(empType, vMetaInfo) )
        return true;
    }
    return false;
}
