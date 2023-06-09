#include "stuguanli.h"
#include "ui_stuguanli.h"
#include<QSqlQuery>
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>

stuGuanLi::stuGuanLi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stuGuanLi)
{
    ui->setupUi(this);
    \
    // 设置列表列头
    ui->information_tableWidget->setColumnCount(10);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("密码"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("员工姓名"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("电话"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("所在部门"));
    ui->information_tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("入职时间"));
    ui->information_tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("职位"));
    ui->information_tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("工位"));
    ui->information_tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("薪水"));
    // 设置列表自动填充满窗口(针对姓名，院系和密码）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,60);//选择栏
    ui->information_tableWidget->setColumnWidth(1,120);//工号
    ui->information_tableWidget->setColumnWidth(2,100);//密码
    ui->information_tableWidget->setColumnWidth(3,100);//name
    ui->information_tableWidget->setColumnWidth(4,115);//电话
    ui->information_tableWidget->setColumnWidth(5,150);//apart
    ui->information_tableWidget->setColumnWidth(6,150);//入职时间
    ui->information_tableWidget->setColumnWidth(7,80);//职位
    ui->information_tableWidget->setColumnWidth(8,60);//工位
    ui->information_tableWidget->setColumnWidth(9,80);//薪水
    // 刷新表格数据
    tableReflash();
}

stuGuanLi::~stuGuanLi()
{
    delete ui;
}


// 设置单元格信息
void stuGuanLi::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}

// 刷新表格数据
void stuGuanLi::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }
    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select username,password,staname,tel,stadepart,entry_time,job,address_pos,salary from (select * from staff_info,users where username = sid) a"
                      " order by username ";
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
        cellSetting(row,6, query.value(5).toString());
        cellSetting(row,7, query.value(6).toString());
        cellSetting(row,8, query.value(7).toString());
        cellSetting(row,9, query.value(8).toString());
        cellSetting(row,10, query.value(9).toString());
        qDebug()<<query.value(0).toString()<<","<<query.value(1).toString()<<","<<query.value(2).toString()<<
                  ","<<query.value(3).toString()<<","<<query.value(4).toString();
        row++;
    }
}

// 查询学生信息
void stuGuanLi::selectStudent()
{
    QString searchParam = ui->select_param_edit_3->text().trimmed();
    if(searchParam.isEmpty()) {
        tableReflash();
        return;
    }
    tableReflash(QString("select username,password,staname,tel,stadepart,entry_time,job,address_pos,salary from (select * from staff_info,users where username = sid) a"
                         " where staname like \"%1%2\" or sid like \"%3%4\"")
                 .arg(searchParam,"%",searchParam,"%"));
}

void stuGuanLi::on_refer_pushButton_3_clicked()
{
    selectStudent();
}

void stuGuanLi::on_clear_pushButton_3_clicked()
{
    ui->select_param_edit_3->clear();
    tableReflash();
}

void stuGuanLi::on_reMiMa_pushButton_clicked()
{
    int rowCount = ui->information_tableWidget->rowCount();
    QList<QString> ids;

    for(int row = 0;row<rowCount;row++) {
        QTableWidgetItem * item = ui->information_tableWidget->item(row,0);
        Qt::CheckState status = item->checkState();
        if(status == Qt::CheckState::Checked) {
            QLineEdit* idItem = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 1);
            //ids.append(idItem->text().toInt());
            ids.append(idItem->text());
        }
    }
    if(ids.isEmpty()) {
        QMessageBox::information(this,"提示","请先勾选要重置密码的行");
        return;
    }
    qDebug()<<"重置数据ids: "<<ids;
    QString idsStr;
    for(int i = 0;i< ids.size();i++) {
        if(i == 0) {
           // idsStr = idsStr + QString::number(ids.at(i));
            idsStr = idsStr + ids.at(i);
      } else {
            //idsStr = idsStr + "\',\'"+QString::number(ids.at(i));
            idsStr = idsStr + "\',\'"+ids.at(i);
        }
    }
    qDebug()<<idsStr;
    QString sql = "update users set password = 123456 where username in(\'" + idsStr + "\')";
    qDebug()<<sql;
    QSqlQuery query;
    if(query.exec(sql)) {
        // 刷新表格
        tableReflash();
        QMessageBox::information(this,"成功","重置成功");
    } else {
        QMessageBox::information(this,"失败","重置失败");
    }
}
