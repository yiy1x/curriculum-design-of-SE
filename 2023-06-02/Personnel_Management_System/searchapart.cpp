#include "searchapart.h"
#include "ui_searchapart.h"
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>

searchApart::searchApart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchApart)
{
    ui->setupUi(this);
    // 设置列表列头
    ui->information_tableWidget->setColumnCount(11);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("姓名"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("性别"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("电话"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("入职时间"));
    ui->information_tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("部门"));
    ui->information_tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("工作"));
    ui->information_tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("房间号"));
    ui->information_tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("工位"));
    ui->information_tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("薪资"));

    // 设置列表自动填充满窗口(针对姓名和院系）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,80);
    ui->information_tableWidget->setColumnWidth(1,110);//工号
    ui->information_tableWidget->setColumnWidth(2,80);//姓名
    ui->information_tableWidget->setColumnWidth(3,60);//性别
    ui->information_tableWidget->setColumnWidth(4,105);//电话
    ui->information_tableWidget->setColumnWidth(5,130);//时间
    ui->information_tableWidget->setColumnWidth(6,80);//部门
    ui->information_tableWidget->setColumnWidth(7,50);//职位
    ui->information_tableWidget->setColumnWidth(8,60);//房间号
    ui->information_tableWidget->setColumnWidth(9,60);//工位
    ui->information_tableWidget->setColumnWidth(10,80);//薪资

    // 刷新表格数据
    tableReflash();
}

searchApart::~searchApart()
{
    delete ui;
}


// 设置单元格信息
void searchApart::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}

// 刷新表格数据
void searchApart::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }
    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select * from staff_info order by stadepart asc";
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
                  ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString()<<
                  ","<<query.value(6).toString()<<","<<query.value(7).toString()<<","<<query.value(8).toString()<<","<<query.value(9).toString();
        row++;
    }
}

// 查询学生信息
void searchApart::selectStudent()
{
    QString searchParam1 = ui->search_building_edit->text().trimmed();
    if(searchParam1.isEmpty()) {
        tableReflash();
        return;
    }
    tableReflash(QString("select * from staff_info "
                         "where stadepart like \"%1%2\"")
                 .arg(searchParam1,"%"));
}



void searchApart::on_refer_pushButton_clicked()
{
    selectStudent();
}

void searchApart::on_clear_pushButton_clicked()
{
    ui->search_building_edit->clear();
    tableReflash();
}
