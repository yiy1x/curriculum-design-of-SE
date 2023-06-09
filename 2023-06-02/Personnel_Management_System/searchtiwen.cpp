#include "searchtiwen.h"
#include "ui_searchtiwen.h"
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>
#include"tiwenchange_dialog.h"
#include<QDate>
#include<QDateTimeEdit>

searchTiWen::searchTiWen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchTiWen)
{
    ui->setupUi(this);
    // 设置列表列头
    ui->information_tableWidget->setColumnCount(5);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("员工姓名"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("打卡日期"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("打卡时间"));
    //ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("学生学号"));
    //ui->information_tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("学生姓名"));

    // 设置列表自动填充满窗口(针对姓名）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,80);
    ui->information_tableWidget->setColumnWidth(1,130);
    ui->information_tableWidget->setColumnWidth(2,140);//楼层
    ui->information_tableWidget->setColumnWidth(3,140);//房间号
    ui->information_tableWidget->setColumnWidth(4,150);//学号

    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    // 刷新表格数据
    tableReflash();
}

searchTiWen::~searchTiWen()
{
    delete ui;
}

// 设置单元格信息
void searchTiWen::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}

// 刷新表格数据
void searchTiWen::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }
    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select attend.sid,staname,date,time from attend NATURAL join staff_info";
        qDebug()<<sql;
        query.exec(sql);
    } else {
        qDebug()<<selectSql;
        query.exec(selectSql);
    }
    int row =0;
    while(query.next())
    {
        int index_row =ui->information_tableWidget->rowCount();
        ui->information_tableWidget->setRowCount(index_row+1);
        // 第一列插入复选框
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        check->setFlags(check->flags() ^ Qt::ItemIsEditable);
        ui->information_tableWidget->setItem(row,0,check); //插入复选框
        cellSetting(row,1, query.value(0).toString());
        cellSetting(row,2, query.value(1).toString());
        cellSetting(row,3, query.value(2).toString());
        cellSetting(row,4, query.value(3).toString());
        cellSetting(row,5, query.value(4).toString());
        //cellSetting(row,6, query.value(5).toString());
        qDebug()<<query.value(0).toString()<<","<<query.value(1).toString()<<","<<query.value(2).toString()<<
                  ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString();
        row++;
    }
}

// 查询学生信息
void searchTiWen::selectStudent()
{
    QString searchParam = ui->select_param_edit->text().trimmed();
    QString searchParam2 = ui->dateEdit->text().trimmed();//日期查询
    if(searchParam.isEmpty()&& !ui->checkBox->isChecked()) {//啥也没选
        tableReflash();
        return;
    }
    if(searchParam.isEmpty()&& ui->checkBox->isChecked())//只有日期选中
    {
        tableReflash(QString("select attend.sid,staname,date,time from attend NATURAL join staff_info where date = \"%1\"")
                     .arg(searchParam2));
        return;
    }
    if(!searchParam.isEmpty()&&!ui->checkBox->isChecked())//只选学生
    {
        tableReflash(QString("select attend.sid,staname,date,time from attend NATURAL join staff_info where staname like \"%1%2\" or sid like \"%3%4\"")
                     .arg(searchParam,"%",searchParam,"%"));
        return;
    }
    tableReflash(QString("select attend.sid,staname,date,time from attend NATURAL join staff_info where (staname like \"%1%2\" or sid like \"%3%4\") and date = \"%5\"")
                 .arg(searchParam,"%",searchParam,"%",searchParam2));
}

// 上交学生信息（删除）
void searchTiWen::deleteStudent()
{
    int rowCount = ui->information_tableWidget->rowCount();
    QList<QString> ids;
    for(int row = 0;row<rowCount;row++) {
        QTableWidgetItem * item = ui->information_tableWidget->item(row,0);
        Qt::CheckState status = item->checkState();
        if(status == Qt::CheckState::Checked) {
            QLineEdit* idItem = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 5);
            //ids.append(idItem->text().toInt());
            ids.append(idItem->text());
        }
    }
    if(ids.isEmpty()) {
        QMessageBox::information(this,"提示","请先勾选要上交信息的行");
        return;
    }
    qDebug()<<"删除数据ids: "<<ids;
    QString idsStr = "";
    for(int i = 0;i< ids.size();i++) {
        if(i == 0) {
           // idsStr = idsStr + QString::number(ids.at(i));
            idsStr = idsStr + ids.at(i);
      } else {
            //idsStr = idsStr + ","+QString::number(ids.at(i));
            idsStr = idsStr + ","+ids.at(i);
        }
    }
    QString sql = "delete from stutem where sid in(" + idsStr + ")";
    qDebug()<<sql;
    QSqlQuery query;
    if(query.exec(sql)) {
        // 刷新表格
        ui->select_param_edit->clear();
        ui->checkBox->setChecked(false);
        tableReflash();
        QMessageBox::information(this,"成功","您已成功上交数据到校园疫情防控中心！");
    } else {
        QMessageBox::information(this,"失败","上交失败");
    }
}

void searchTiWen::on_refer_pushButton_clicked()
{
    selectStudent();
}

void searchTiWen::on_clear_pushButton_clicked()
{
    ui->select_param_edit->clear();
    ui->checkBox->setChecked(false);
    tableReflash();
}

void searchTiWen::on_add_pushButton_clicked()//上交信息
{
    deleteStudent();
}

void searchTiWen::on_change_pushButton_clicked()
{
    int rowCount = ui->information_tableWidget->rowCount();
    QList<QString> ids;
    QList<QString> ids2;
    for(int row = 0;row<rowCount;row++) {
        QTableWidgetItem * item = ui->information_tableWidget->item(row,0);
        Qt::CheckState status = item->checkState();
        if(status == Qt::CheckState::Checked) {
            QLineEdit* idItem = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 5);
            QLineEdit* idItem2 = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 1);
            //ids.append(idItem->text().toInt());
            ids.append(idItem->text());
            ids2.append(idItem2->text());
        }
    }
    if(ids.isEmpty()) {
        QMessageBox::information(this,"提示","请先勾选要修改的行");
        return;
    }
    if(ids.size() > 1) {
        QMessageBox::information(this,"提示","修改时只能勾选单行数据");
        return;
    }
    TiWenchange_Dialog* student_update = new TiWenchange_Dialog(this);
    student_update->setAttribute(Qt::WA_DeleteOnClose); // 关闭时销毁对象
    student_update->setModal(true); // 设置为模态窗口，即窗口打开后只能该修改界面操作，不能在其他窗口进行操作，保证操作时的唯一性
    student_update->load(ids.at(0),ids2.at(0));
    student_update->show();
}
