#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "datasource_interface.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSharedPointer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Emp_OK_clicked();

    void on_Insert_clicked();

    void on_SearchB_clicked();

    void on_Delete_clicked();


    void on_Show_clicked();

    void on_pushButton_clicked();

    void on_LoginButton_clicked();

private:
    Ui::MainWindow *ui;    
    EmpInfo eInfo;
    DataSource_Interface obj;
    MetaInfo mInfo;
    EmpType eType = EmpType::MEMP;
    bool allEmpShow = false;
    void SetMonthlyEmp();
    void SetHourlyEmp();
    void SetSalesEmp();
    void UpdateMEmp(EmpInfo&einfo);
    void UpdateHEmp(EmpInfo&einfo);
    void UpdateSaleEmp(EmpInfo&einfo);
    bool MakeVectQstring(MetaInfo&,QVector<QString>&);
    bool TableUpdate(QString,uint16_t&,uint16_t&);
    bool CheckForNull(EmpInfo&);
    bool CheckForNullHrEmp(EmpInfo&);
    bool CheckForNullSalesEmp(EmpInfo&);

};
#endif // MAINWINDOW_H
