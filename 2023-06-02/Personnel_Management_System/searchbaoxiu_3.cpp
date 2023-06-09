#include "searchbaoxiu_3.h"
#include "ui_searchbaoxiu_3.h"
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>
#include<QLineEdit>

searchbaoxiu_3::searchbaoxiu_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchbaoxiu_3)
{
    ui->setupUi(this);
    // 设置列表列头
    //ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setColumnCount(6);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("时间"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("月基本工资"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("月附加工资"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("月实际工资"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("备注"));

    // 设置列表自动填充满窗口(针对事件描述和备注）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,120);//工号
    ui->information_tableWidget->setColumnWidth(1,130);//时间
    ui->information_tableWidget->setColumnWidth(2,130);//基本工资
    ui->information_tableWidget->setColumnWidth(3,130);//附加工资
    ui->information_tableWidget->setColumnWidth(4,130);//实际工资
    ui->information_tableWidget->setColumnWidth(5,130);//备注
      tableReflash();
}

searchbaoxiu_3::~searchbaoxiu_3()
{
    delete ui;
}


// 设置单元格信息
void searchbaoxiu_3::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}


// 刷新表格数据
void searchbaoxiu_3::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }

    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select * from staff_salary  ";
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
        cellSetting(row,0, query.value(0).toString());
        cellSetting(row,1, query.value(1).toString());
        cellSetting(row,2, query.value(2).toString());
        cellSetting(row,3, query.value(3).toString());
        cellSetting(row,4, query.value(4).toString());
        cellSetting(row,5, query.value(5).toString());
        qDebug()<<query.value(0).toString()<<","<<query.value(1).toString()<<","<<query.value(2).toString()<<
                  ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString();
        row++;
    }
}

void searchbaoxiu_3::on_pushButton_clicked()
{
    QString searchParam1 = ui->sid_lineEdit->text().trimmed();
    if(searchParam1.isEmpty()) {
        tableReflash();
        return;
    }
    tableReflash(QString("select * from  staff_salary where sid = '%1'").arg(searchParam1));
}
