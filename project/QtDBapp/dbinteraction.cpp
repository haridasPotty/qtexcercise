#include "dbinteraction.h"
/*
Constructor will create a Database with name EmpDB;
*/
DBInteraction::DBInteraction(){
    DBConnection.setHostName("127.0.0.1");
    DBConnection.setPort(3306);
    DBConnection.setUserName("root");
    DBConnection.setPassword("Admin@123");
    DBConnection.setDatabaseName(QCoreApplication::applicationDirPath()+"/EmpDB");

}
/*
Data base Table craetion.
MEMP-For Monthly Compensation Employee
HEMP-For Hourly Compensation Employee
SEMP-For Salesman
MEMP table has [SSN NAME MCOMP  Month]
HEMP table has [SSN NAME HR_COMP HR_DONE NetSalary Month]
SEMP table has [SSN NAME MCOMP RealOutcome ClaimOutcome  Bonus Month]
*/
bool DBInteraction::DBInit(){
    if(DBConnection.open()){
        qDebug()<<"Database is opened";
        QSqlQuery databaseQuery(DBConnection);
        databaseQuery.prepare("CREATE TABLE IF NOT EXISTS MEMP"
                              " (SSN int not null primary key,\
                              NAME text, MCOMP integer,Month text);");

        databaseQuery.exec();
        DBConnection.commit();
        databaseQuery.prepare("CREATE TABLE IF NOT EXISTS HEMP"
                              " (SSN int not null primary key,\
                                NAME text, HR_COMP real,HR_DONE real, \
                                        NetSalary real,Month text);");
        databaseQuery.exec();
        DBConnection.commit();
        databaseQuery.prepare("CREATE TABLE IF NOT EXISTS SEMP"
                              " (SSN int not null primary key,\
                             NAME text, MCOMP integer, RealOutcome real,\
                             ClaimOutcome real,Bonus real, Month text);");
        databaseQuery.exec();
        DBConnection.commit();
        return true;
    }
    qDebug()<<"failed to open"<<DBConnection.lastError().text();
    return false;
}
/*
To connect with data base
On success it returns true else false
*/
bool DBInteraction::DBConnect(){
    if(DBConnection.open()){
        qDebug()<<"Database is opened";
        return true;
    }
    qDebug()<<"failed to open"<<DBConnection.lastError().text();
    return false;
}
/*
To close the connection with data base
Returns true*/
bool DBInteraction::DBClose(){
    DBConnection.close();
    return true;
}
/*
To add the data into data base.
On success it returns true else false
*/
bool DBInteraction::DBInsert(EmpType empType, EmpInfo& eInfo){
    if(empType == EmpType::MEMP){
        if(DBConnect()){
            qDebug()<<"MEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            query.prepare("INSERT INTO MEMP (SSN,NAME,MCOMP,Month)"
                  "VALUES (?, ?, ?, ?)");
            query.addBindValue(eInfo.SCNumber);          
            query.addBindValue(eInfo.Name);
            query.addBindValue(eInfo.Mcompensation);            
            query.addBindValue(eInfo.Month);
            query.exec();
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"MEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::HEMP){
        if(DBConnect()){
            qDebug()<<"HEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            query.prepare("INSERT INTO HEMP(SSN,NAME,HR_COMP,HR_DONE,NetSalary,Month)"
                  "VALUES (?, ?, ?, ?, ?, ?)");           
            query.addBindValue(eInfo.SCNumber);            
            query.addBindValue(eInfo.Name);
            query.addBindValue(eInfo.HourCompensation);
            query.addBindValue(eInfo.HourDone);
            query.addBindValue(eInfo.NetSalary);
            query.addBindValue(eInfo.Month);
            query.exec();
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::SALESMAN){
        if(DBConnect()){
            qDebug()<<"SalesEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            query.prepare("INSERT INTO SEMP(SSN,NAME,MCOMP,RealOutcome,"
                                   "ClaimOutcome,Bonus,Month)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(eInfo.SCNumber);
            query.addBindValue(eInfo.Name);
            query.addBindValue(eInfo.Mcompensation);
            query.addBindValue(eInfo.SRealisedOutcome);
            query.addBindValue(eInfo.SoutcomeClaim);
            query.addBindValue(eInfo.SBonus);
            query.addBindValue(eInfo.Month);
            query.exec();
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"SalesEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else{
        qDebug() << "Emptype mismatching";
    }
    return false;
}
/*
To delete selected row from the database
On success it returns true else false
*/
bool DBInteraction::DBDelete(EmpType empType,uint32_t SCNumber){
    MetaInfo mInfo;
    bool searchResult = DBSearch(empType,SCNumber,mInfo);
    if(searchResult==false){
        qDebug()<<"Search failed for" << SCNumber;
        return false;
    }
    if(empType == EmpType::MEMP){
        if(DBConnect()){
            qDebug()<<"DBDelete:MEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            char eid[100];
            sprintf(eid, "DELETE FROM MEMP where SSN= %d", SCNumber);
            query.prepare(eid);
            if (query.exec() ){
            }
            else{
               qDebug() << "Deletion failed";
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"MEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::HEMP){
        if(DBConnect()){
            qDebug()<<"DBDelete:HEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            char eid[100];
            sprintf(eid, "DELETE FROM HEMP where SSN= %d", SCNumber);
            query.prepare(eid);
            if (query.exec() ){
            }
            else{
               qDebug() << "Deletion failed";
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"HEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::SALESMAN){
        if(DBConnect()){
            qDebug()<<"DBDelete:SEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            char eid[100];
            sprintf(eid, "DELETE FROM SEMP where SSN= %d", SCNumber);
            query.prepare(eid);
            if (query.exec() ){
            }
            else{
               qDebug() << "Deletion failed";
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"SEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else{
        qDebug() << "Emp type mismatching";
    }
    return false;
}

/*
To search for a particular iteam based on Social security Number.
On success it returns true else false.
If searching is success, mInfo will hold the search result.
*/
bool DBInteraction::DBSearch(EmpType empType, uint32_t val,MetaInfo& mInfo){
    if(empType == EmpType::MEMP){
        if(DBConnect()){
            qDebug()<<"MEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);bool negStatus = false;
            char eid[100];
            sprintf(eid, "SELECT * FROM MEMP where SSN= %d", val);
            query.prepare(eid);
            if(  query.exec()){
                while(query.next()){                 
                 this->Update(EmpType::MEMP,query,mInfo);
                 negStatus = true;
                }
            }
            else{
                negStatus = false;
            }
            if(negStatus == false){
                qDebug() << "Value not found";
                DBConnection.commit();
                DBConnection.close();
                return false;
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"MEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::HEMP){
        if(DBConnect()){
            qDebug()<<"HEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            bool negStatus = false;
            char eid[100];
            sprintf(eid, "SELECT * FROM HEMP where SSN= %d", val);
            query.prepare(eid);
            if(  query.exec()){
                while(query.next()){
                 this->Update(EmpType::HEMP,query,mInfo);
                 negStatus = true;
                }
            }
            else{
                negStatus = false;
            }
            if(negStatus == false){
                qDebug() << "Value not found";
                DBConnection.commit();
                DBConnection.close();
                return false;
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"HEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(empType == EmpType::SALESMAN){
        if(DBConnect()){
            qDebug()<<"SEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);bool negStatus = false;
            char eid[100];
            sprintf(eid, "SELECT * FROM SEMP where SSN= %d", val);
            query.prepare(eid);
            if(  query.exec()){
                while(query.next()){
                 this->Update(EmpType::SALESMAN,query,mInfo);
                 negStatus = true;
                }
            }
            else{
                negStatus = false;
            }
            if(negStatus == false){
                qDebug() <<val<< "Value not found";
                DBConnection.commit();
                DBConnection.close();
                return false;
            }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"SEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else{
        qDebug() << "Employee type mismatching";
    }
    return false;
}

bool DBInteraction::DBShow(EmpType eType,std::vector<MetaInfo>& vMetaInfo){
    if(eType == EmpType::SALESMAN){
           if(DBConnect()){
               qDebug()<<"SEMP:Database is opened";
               QSqlDatabase::database().transaction();
               QSqlQuery query(DBConnection);
               char eid[100];
               sprintf(eid, "SELECT * FROM SEMP ");
               QSqlQueryModel qModel ;
               qModel.setQuery(eid);
               query.prepare(eid);
               while(qModel.canFetchMore()){
                   qModel.fetchMore();               
               }                
                MetaInfo mInfo_[qModel.rowCount()];
                 for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                     Update(eType,qModel,mInfo_[iRow],iRow);
                 }
                 for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                     vMetaInfo.push_back(mInfo_[iRow]);
                 }                 
               DBConnection.commit();
               DBConnection.close();
               return true;
           }
           qDebug()<<"SEMP:failed to open"<<DBConnection.lastError().text();
           return false;
       }
    else     if(eType == EmpType::HEMP){
        if(DBConnect()){
            qDebug()<<"HEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            char eid[100];
            sprintf(eid, "SELECT * FROM HEMP ");
            QSqlQueryModel qModel ;
            qModel.setQuery(eid);
            query.prepare(eid);
            while(qModel.canFetchMore()){
                qModel.fetchMore();
            }
             MetaInfo mInfo_[qModel.rowCount()];
              for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                  Update(eType,qModel,mInfo_[iRow],iRow);
              }
              for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                  vMetaInfo.push_back(mInfo_[iRow]);
              }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"HEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else if(eType == EmpType::MEMP){
        if(DBConnect()){
            qDebug()<<"MEMP:Database is opened";
            QSqlDatabase::database().transaction();
            QSqlQuery query(DBConnection);
            char eid[100];
            sprintf(eid, "SELECT * FROM MEMP ");
            QSqlQueryModel qModel ;
            qModel.setQuery(eid);
            query.prepare(eid);
            while(qModel.canFetchMore()){
                qModel.fetchMore();
            }
             MetaInfo mInfo_[qModel.rowCount()];
              for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                  Update(eType,qModel,mInfo_[iRow],iRow);
              }
              for(auto iRow = 0;iRow<qModel.rowCount();++iRow){
                  vMetaInfo.push_back(mInfo_[iRow]);
              }
            DBConnection.commit();
            DBConnection.close();
            return true;
        }
        qDebug()<<"MEMP:failed to open"<<DBConnection.lastError().text();
        return false;
    }
    else{
        qDebug()<<"EmpType mismatching";
    }
return false;
}

bool DBInteraction::Update(EmpType eType,QSqlQuery& qry, MetaInfo& mInfo){
    if(eType == EmpType::MEMP){
        mInfo.eInfo.SCNumber      = qry.value(0).toInt();
        mInfo.eInfo.Name          = qry.value(1).toString();
        mInfo.eInfo.Mcompensation = qry.value(2).toInt();
        mInfo.eInfo.Month         = qry.value(3).toString();
        mInfo.eType               = EmpType::MEMP;
    return true;
    }
    else if(eType == EmpType::HEMP){
        mInfo.eInfo.SCNumber        = qry.value(0).toInt();
        mInfo.eInfo.Name            = qry.value(1).toString();
        mInfo.eInfo.HourCompensation= qry.value(2).toFloat();
        mInfo.eInfo.HourDone        = qry.value(3).toFloat();
        mInfo.eInfo.NetSalary       = qry.value(4).toFloat();
        mInfo.eInfo.Month           = qry.value(5).toString();
        mInfo.eInfo.Mcompensation   = qry.value(4).toFloat();
        mInfo.eType                 = EmpType::HEMP;
        return true;
    }
    else if(eType == EmpType::SALESMAN){
        mInfo.eInfo.SCNumber        = qry.value(0).toInt();
        mInfo.eInfo.Name            = qry.value(1).toString();
        mInfo.eInfo.Mcompensation   = qry.value(2).toFloat();
        mInfo.eInfo.SRealisedOutcome= qry.value(3).toFloat();
        mInfo.eInfo.SoutcomeClaim   = qry.value(4).toFloat();
        mInfo.eInfo.SBonus          = qry.value(5).toFloat();
        mInfo.eInfo.Month           = qry.value(6).toString();
        mInfo.eType                 = EmpType::SALESMAN;
        return true;
    }
    return false;
}

bool DBInteraction::Update(EmpType eType, QSqlQueryModel& qModel,
                                 MetaInfo& mInfo, std::uint16_t index){
    if(eType == EmpType::SALESMAN){
        mInfo.eInfo.SCNumber        = qModel.record(index).value(0).toInt();
        mInfo.eInfo.Name            = qModel.record(index).value(1).toString();
        mInfo.eInfo.Mcompensation   = qModel.record(index).value(2).toInt();
        mInfo.eInfo.SRealisedOutcome= qModel.record(index).value(3).toFloat();
        mInfo.eInfo.SoutcomeClaim   = qModel.record(index).value(4).toFloat();
        mInfo.eInfo.SBonus          = qModel.record(index).value(5).toFloat();       
        mInfo.eInfo.Month           = qModel.record(index).value(6).toString();
        mInfo.eType                 = EmpType::SALESMAN;
        return true;
        }
    else if(eType == EmpType::HEMP){
        mInfo.eInfo.SCNumber        = qModel.record(index).value(0).toInt();
        mInfo.eInfo.Name            = qModel.record(index).value(1).toString();
        mInfo.eInfo.HourCompensation= qModel.record(index).value(2).toFloat();
        mInfo.eInfo.HourDone        = qModel.record(index).value(3).toFloat();
        mInfo.eInfo.Mcompensation   = qModel.record(index).value(4).toFloat();
        mInfo.eInfo.Month           = qModel.record(index).value(5).toString();
        mInfo.eType                 = EmpType::HEMP;
        return true;
    }
    else if(eType == EmpType::MEMP){
        mInfo.eInfo.SCNumber      = qModel.record(index).value(0).toInt();
        mInfo.eInfo.Name          = qModel.record(index).value(1).toString();
        mInfo.eInfo.Mcompensation = qModel.record(index).value(2).toFloat();       
        mInfo.eInfo.Month         = qModel.record(index).value(3).toString();
        mInfo.eType               = EmpType::MEMP;
        return true;
        }
    else{
        qDebug() << "EmpType mismatching";
    }
    return false;
}
