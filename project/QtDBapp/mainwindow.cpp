#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->comboBox->addItem("MEmp");
    ui->comboBox->addItem("HEmp");
    ui->comboBox->addItem("Salesman");
    ui->comboBox->addItem("AllEMPs");
    ui->eMonth->setText("mm_yy");
    ui->tableWidget->setVisible(false);
    SetMonthlyEmp();
    ui->EmpInfoGroup->setVisible(false);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::SetMonthlyEmp(){
    ui->Empname->setVisible(true);
    ui->Empscon->setVisible(true);
    ui->EmpmComp->setVisible(true);
    ui->EmphrComp->setVisible(false);
    ui->Empbonus->setVisible(false);
    ui->EmprealClaim->setVisible(false);
    ui->EmpclaimOutcoe->setVisible(false);
    ui->EmphrDone->setVisible(false);
    ui->tableWidget->setVisible(false);

    ui->McompLabel->setVisible(true);
    ui->NameLabel->setVisible(true);
    ui->EmpmComp->setVisible(true);
    ui->HdoneLabel->setVisible(false);
    ui->BonusLabel->setVisible(false);
    ui->HcompLabel->setVisible(false);
    ui->RealClaimLabel->setVisible(false);
    ui->ClaimOClabel->setVisible(false);
}

void MainWindow::SetHourlyEmp(){
    ui->Empname->setVisible(true);
    ui->Empscon->setVisible(true);
    ui->EmphrComp->setVisible(true);
    ui->EmphrDone->setVisible(true);
    ui->eMonth->setVisible(true);
    ui->Empbonus->setVisible(false);
    ui->EmpmComp->setVisible(false);
    ui->EmpclaimOutcoe->setVisible(false);
    ui->EmprealClaim->setVisible(false);
    ui->tableWidget->setVisible(false);

    ui->NameLabel->setVisible(true);
    ui->HdoneLabel->setVisible(true);
    ui->HcompLabel->setVisible(true);
    ui->NameLabel->setVisible(true);
    ui->SCONlabe->setVisible(true);
    ui->BonusLabel->setVisible(false);
    ui->RealClaimLabel->setVisible(false);
    ui->ClaimOClabel->setVisible(false);
    ui->McompLabel->setVisible(false);
}

void MainWindow::SetSalesEmp(){
    ui->Empname->setVisible(true);
    ui->Empscon->setVisible(true);
    ui->EmpmComp->setVisible(true);
    ui->Empbonus->setVisible(true);
    ui->EmpclaimOutcoe->setVisible(true);
    ui->EmprealClaim->setVisible(true);
    ui->EmpclaimOutcoe->setVisible(true);
    ui->EmpmComp->setVisible(true);
    ui->EmphrComp->setVisible(false);
    ui->EmphrDone->setVisible(false);    
    ui->tableWidget->setVisible(false);

    ui->BonusLabel->setVisible(true);
    ui->SCONlabe->setVisible(true);
    ui->McompLabel->setVisible(true);
    ui->NameLabel->setVisible(true);
    ui->RealClaimLabel->setVisible(true);
    ui->ClaimOClabel->setVisible(true);
    ui->HdoneLabel->setVisible(false);
    ui->HcompLabel->setVisible(false);

}

void MainWindow::UpdateMEmp(EmpInfo &einfo){
    ui->Empname->setText(einfo.Name);
    ui->Empscon->setText(QString::number(einfo.SCNumber));
    ui->EmpmComp->setText(QString::number(einfo.Mcompensation));
}

void MainWindow::UpdateHEmp(EmpInfo &einfo){
    ui->Empname->setText(einfo.Name);
    ui->Empscon->setText(QString::number(einfo.SCNumber));
    ui->EmphrComp->setText(QString::number(einfo.HourCompensation));
    ui->EmphrDone->setText(QString::number(einfo.HourDone));
    ui->EmpmComp->setText(QString::number(einfo.NetSalary));
    qDebug()<<"netsalary of Hemp=" << einfo.NetSalary;
}

void MainWindow::UpdateSaleEmp(EmpInfo &einfo){
    ui->Empname->setText(einfo.Name);
    ui->Empscon->setText(QString::number(einfo.SCNumber));
    ui->EmpmComp->setText(QString::number(einfo.Mcompensation));
    ui->Empbonus->setText(QString::number(einfo.SBonus));
    ui->EmprealClaim->setText(QString::number(einfo.SRealisedOutcome));
    ui->EmpclaimOutcoe->setText(QString::number(einfo.SoutcomeClaim));
}

bool MainWindow::MakeVectQstring(MetaInfo& mInfo, QVector<QString>& mInfoQV){
    mInfoQV.push_back(mInfo.eInfo.Name);
    mInfoQV.push_back(QString::number(mInfo.eInfo.SCNumber));
    mInfoQV.push_back(QString::number(mInfo.eInfo.Mcompensation));
    mInfoQV.push_back(QString::number(mInfo.eInfo.HourCompensation));
    mInfoQV.push_back(QString::number(mInfo.eInfo.HourDone));
    mInfoQV.push_back(QString::number(mInfo.eInfo.SBonus));
    mInfoQV.push_back(QString::number(mInfo.eInfo.SRealisedOutcome));
    mInfoQV.push_back(QString::number(mInfo.eInfo.SoutcomeClaim));
    mInfoQV.push_back(QString::number(mInfo.eInfo.NetSalary));
    mInfoQV.push_back(mInfo.eInfo.Month);
    return true;
}

bool MainWindow::TableUpdate( QString empCategory,uint16_t& row ,
                                                  uint16_t& col){
    constexpr size_t numberCol = 8;
    MetaInfo mInfo;std::vector<MetaInfo> vMetaInfo;
    obj.Show(eType,vMetaInfo);
    qDebug()<<empCategory<<vMetaInfo.size();
    QVector<QString> vqData ;    
    ui->tableWidget->setColumnCount(12);
    if (allEmpShow != true)
        ui->tableWidget->setRowCount(vMetaInfo.size()+2);
    QTableWidgetItem* iteam   = new QTableWidgetItem;     
    iteam->setText(empCategory);
    ui->tableWidget->setItem(row,col,iteam);

    for(size_t i=0;i<vMetaInfo.size();++i){
        for(size_t j=0;j<numberCol;++j){
            MakeVectQstring(vMetaInfo.at(i),vqData);
            iteam = new QTableWidgetItem;
            iteam->setText(vqData.at(j));
            ui->tableWidget->setItem(i+1+row,j+1,iteam);
            vqData.clear();
        }
    }
    row = row+ vMetaInfo.size();
    return true;
}
/*Check for null for the Monthly Emp entries*/
bool MainWindow::CheckForNull(EmpInfo& eInfo){
    if(eInfo.Name == ""){
        QMessageBox::information(this,"Error","Please fill Name field");
        return false;
    }
    if(eInfo.SCNumber == 0){
        QMessageBox::information(this,"Error","Please fill SCNumber field");
        return false;
    }
    if(eInfo.Mcompensation == 0){
        QMessageBox::information(this,"Error","Please fill Mcompensation field");
        return false;
    }
    if(eInfo.Month == ""){
        QMessageBox::information(this,"Error","Please fill month field");
        return false;
    }
    return true;
}
/*Check for null for the Hourly paid Emp entries*/
bool MainWindow::CheckForNullHrEmp(EmpInfo &eInfo){
    if(eInfo.Name == ""){
        QMessageBox::information(this,"Error","Please fill Name field");
        return false;
    }
    if(eInfo.SCNumber == 0){
        QMessageBox::information(this,"Error","Please fill SCNumber field");
        return false;
    }
    if(eInfo.HourCompensation == 0){
        QMessageBox::information(this,"Error","Please fill HourCompensation field");
        return false;
    }
    if(eInfo.HourDone == 0){
        QMessageBox::information(this,"Error","Please fill HourDone field");
        return false;
    }
    if(eInfo.Month == ""){
        QMessageBox::information(this,"Error","Please fill month field");
        return false;
    }
    return true;

}
/*Check for null for the Salesmen Emp entries*/
bool MainWindow::CheckForNullSalesEmp(EmpInfo &eInfo){
    if(eInfo.Name == ""){
        QMessageBox::information(this,"Error","Please fill Name field");
        return false;
    }
    if(eInfo.SCNumber == 0){
        QMessageBox::information(this,"Error","Please fill SCNumber field");
        return false;
    }
    if(eInfo.Mcompensation == 0){
        QMessageBox::information(this,"Error","Please fill Mcompensation field");
        return false;
    }
    if(eInfo.SBonus == 0){
        QMessageBox::information(this,"Error","Please fill Bonus field");
        return false;
    }
    if(eInfo.SRealisedOutcome == 0){
        QMessageBox::information(this,"Error","Please fill RealisedOutcome field");
        return false;
    }
    if(eInfo.SoutcomeClaim == 0){
        QMessageBox::information(this,"Error","PLease fill ClaimOutcome field");
        return false;
    }
    if(eInfo.Month == ""){
        QMessageBox::information(this,"Error","PLease fill Month field");
        return false;
    }
    return true;

}

void MainWindow::on_Emp_OK_clicked(){
    if (ui->comboBox->currentText() == "MEmp"){
        eType = EmpType::MEMP;
        SetMonthlyEmp();
        ui->Delete->setVisible(true);
        ui->Insert->setVisible(true);
        ui->Show->setVisible(true);
        ui->SearchB->setVisible(true);
        ui->tableWidget->setVisible(false);
    }
    else if (ui->comboBox->currentText() == "HEmp"){
        eType = EmpType::HEMP;
        qDebug()<< "hemp selected";
        SetHourlyEmp();
        ui->Delete->setVisible(true);
        ui->Insert->setVisible(true);
        ui->Show->setVisible(true);
        ui->SearchB->setVisible(true);
        ui->tableWidget->setVisible(false);
    }
    else if (ui->comboBox->currentText() == "Salesman"){
        eType = EmpType::SALESMAN;
        SetSalesEmp();
        ui->Delete->setVisible(true);
        ui->Insert->setVisible(true);
        ui->Show->setVisible(true);
        ui->SearchB->setVisible(true);
        ui->tableWidget->setVisible(false);
    }
    else if (ui->comboBox->currentText() == "AllEMPs"){
        eType = EmpType::AllEMPs;
        SetSalesEmp();
        ui->Delete->setVisible(false);
        ui->Insert->setVisible(false);
        ui->Show->setVisible(true);
        ui->SearchB->setVisible(false);
        ui->tableWidget->setVisible(false);
    }
    else{
        QMessageBox::information(this,"Error","EmpType mismatching");
    }
}
void MainWindow::on_Insert_clicked(){    
    bool ok;
    eInfo.Name              = (ui->Empname)->text();
    eInfo.SCNumber          = ui->Empscon->text().toInt(&ok);
    eInfo.HourCompensation  = ui->EmphrComp->text().toFloat(&ok);
    eInfo.HourDone          = ui->EmphrDone->text().toFloat(&ok);
    eInfo.SBonus            = ui->Empbonus->text().toFloat(&ok);
    eInfo.SRealisedOutcome  = ui->EmprealClaim->text().toFloat(&ok);
    eInfo.SoutcomeClaim     = ui->EmpclaimOutcoe->text().toFloat(&ok);
    eInfo.Mcompensation     = ui->EmpmComp->text().toInt(&ok);
    eInfo.Month             = ui->eMonth->text();
    if(eType == EmpType::MEMP){
        if(!CheckForNull(eInfo) )
            return;
    }
    else if(eType == EmpType::HEMP){
        if(!CheckForNullHrEmp(eInfo) )
            return;
    }
    else if(eType == EmpType::SALESMAN){
        if(!CheckForNullSalesEmp(eInfo) )
            return;
    }
    RetType retStatus =  obj.SetData(eType,eInfo);
    if( retStatus == RetType::OK){
        QMessageBox::information(this,"Info","Database updated successfully");
    }
    else if(retStatus==RetType::AlreadyExist){
        QMessageBox::information(this,"Error",QString::number(eInfo.SCNumber)+":\
                 Security Number already existing");
    }
    else{
        QMessageBox::information(this,"Error","Database updation failed");
    }
}


void MainWindow::on_SearchB_clicked(){
    bool ok;
    std::uint32_t SCNumber = ui->Empscon->text().toInt(&ok);       
    if(SCNumber == 0){
        QMessageBox::information(this,"Error","Please fill SCNumber field");
        return ;
    }
    if(obj.GetData(eType,SCNumber,mInfo)){
        QMessageBox::information(this,"Info","Search success");
        if(mInfo.eType==EmpType::MEMP){
            UpdateMEmp(mInfo.eInfo);
        }
        else if(mInfo.eType==EmpType::HEMP){
            UpdateHEmp(mInfo.eInfo);
        }
        else if(mInfo.eType==EmpType::SALESMAN){
            UpdateSaleEmp(mInfo.eInfo);
        }
        else{
            QMessageBox::information(this,"Error","Emptype error");
        }
    }
    else{
        QMessageBox::information(this,"Error","Search failed");
    }
}

void MainWindow::on_Delete_clicked(){
    bool ok;
    std::uint32_t SCNumber = ui->Empscon->text().toInt(&ok);
    if(SCNumber == 0){
        QMessageBox::information(this,"Error","Please fill SCNumber field");
        return ;
    }
    if(obj.DeleteData(eType,SCNumber)){
        QMessageBox::information(this,"Info","successfully deleted");
    }
    else{
        QMessageBox::information(this,"Error","Deletion failed");
    }
}
/* Dynamically it will set the
 *  row size in the table with help of vSize variable*/

void MainWindow::on_Show_clicked(){
    ui->tableWidget->clearContents();
    ui->tableWidget->setVisible(true);

    uint16_t rowRefcount = 0; uint16_t rowColcount = 0;
    if(eType == EmpType::MEMP){
        allEmpShow = false;
        TableUpdate("Monthly Paid Emp",rowRefcount ,rowColcount );
    }
    else  if(eType == EmpType::HEMP){
        allEmpShow = false;
        TableUpdate("Hourly Paid Emp",rowRefcount,rowColcount);
    }
    else  if(eType == EmpType::SALESMAN){
        allEmpShow = false;
        TableUpdate("Salesmen",rowRefcount,rowColcount);
    }
    else  if(eType == EmpType::AllEMPs){
        allEmpShow = true;
        std::vector<MetaInfo> vMetaInfo;
        size_t vSize = 0;
        obj.Show(EmpType::MEMP,vMetaInfo);
        vSize = vMetaInfo.size();
        vMetaInfo.clear();
        obj.Show(EmpType::HEMP,vMetaInfo);
        vSize = vSize+  vMetaInfo.size();
        vMetaInfo.clear();
        obj.Show(EmpType::SALESMAN,vMetaInfo);
        vSize = vSize+  vMetaInfo.size();
        vMetaInfo.clear();        
        ui->tableWidget->setRowCount(vSize+5);

        uint16_t rowRefcount = 0;uint16_t colRefcount = 0;
        eType = EmpType::MEMP;
        TableUpdate("Monthly Paid Emp",rowRefcount,colRefcount);
        rowRefcount++;
        eType = EmpType::HEMP;
        TableUpdate("Hourly Paid Emp",rowRefcount,colRefcount);
        rowRefcount++;
        eType = EmpType::SALESMAN;
        TableUpdate("Salesmen",rowRefcount,colRefcount);
    }
    else{
        QMessageBox::information(this,"Error","Employee type mismatching");
    }
}

/*clear-pushbutton*/
void MainWindow::on_pushButton_clicked(){
    ui->Empname->setText("");
    ui->Empscon->setText("");
    ui->EmpmComp->setText("");
    ui->EmphrComp->setText("");
    ui->EmphrDone->setText("");
    ui->Empbonus->setText("");
    ui->EmprealClaim->setText("");
    ui->EmpclaimOutcoe->setText("");
    ui->eMonth->setText("");
    ui->tableWidget->clearContents();
    ui->tableWidget->clear();
    ui->tableWidget->setVisible(false);
}

/*On successful authentication,
 * UI will load EmpInfo page
*/
void MainWindow::on_LoginButton_clicked(){
    QString userName = ui->userNameTE->toPlainText();
    QString passWord = ui->pwdEdit->toPlainText();
    if(userName == "admin" && passWord == "1234"){
        ui->LoginBox->setVisible(false);
        ui->EmpInfoGroup->setVisible(true);
    }
    else{
        QMessageBox::information(this,"Error","Login failed");
    }
    return;
}

