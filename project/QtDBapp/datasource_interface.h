#ifndef DATASOURCE_INTERFACE_H
#define DATASOURCE_INTERFACE_H

#include "hemp.h"
#include "salesman.h"
#include "dbinteraction.h"
#include "DataSourceModel.h"
class DataSource_Interface : protected DataSource_Salesman::Salesman,
                                    DataSource_HourlyEmployee::HEmp{
    DBInteraction dbc;
    bool dbConnectionStatus = false;
public:
    DataSource_Interface();
    ~DataSource_Interface() = default;
    /*Insert Employee information into the data base.So
     *  mentioned Employee type as per the enumeration(EmpType),
     *  and then fill the relevant information
    */
    RetType SetData(EmpType,EmpInfo&);
    /*Search for a particular Employee inforlation  w.r.t
     * Social security number,Employee type
    */
    bool GetData(EmpType,std::uint32_t,MetaInfo&);
    /*Delete particular Employee information from the database,
     * based on Social security number,Employee type */
    bool DeleteData(EmpType,std::uint32_t);
    /*Show all or particular group of Employees information*/
    bool Show(EmpType,std::vector<MetaInfo>&);
};

#endif // DATASOURCE_INTERFACE_H
