#ifndef DBINTERACTION_H
#define DBINTERACTION_H
#include <QSqlDatabase>
#include <QtSql>
#include "DataSourceModel.h"
class DBInteraction{   
    QSqlDatabase DBConnection = QSqlDatabase::addDatabase("QSQLITE");
    bool Update(EmpType,QSqlQuery&,MetaInfo&);
    bool Update(EmpType,QSqlQueryModel&,MetaInfo&,std::uint16_t);

public:
    DBInteraction();
    ~DBInteraction() = default;

    bool DBInit();
    bool DBConnect();
    bool DBClose();
    bool DBInsert(EmpType empType,EmpInfo& );
    bool DBDelete(EmpType,std::uint32_t);
    bool DBSearch(EmpType,std::uint32_t,MetaInfo&);
    bool DBShow(EmpType,std::vector<MetaInfo>&);
};

#endif // DBINTERACTION_H
