#include "stu_apartinfo.h"
#include "ui_stu_apartinfo.h"
#include<QSqlQuery>
#include<QDebug>
#include<QLineEdit>

stu_apartinfo::stu_apartinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_apartinfo)
{
    ui->setupUi(this);

}

stu_apartinfo::~stu_apartinfo()
{
    delete ui;
}

// 设置单元格信息
void stu_apartinfo::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}

// 刷新表格数据
void stu_apartinfo::tableReflash(QString id)
{
    // 设置列表列头
    ui->information_tableWidget->setColumnCount(6);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("所在部门"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("姓名"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("性别"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("房间号"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("工位"));

    // 设置列表自动填充满窗口(针对姓名和院系）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,80);//部门
    ui->information_tableWidget->setColumnWidth(1,150);//工号
    ui->information_tableWidget->setColumnWidth(2,60);//姓名
    ui->information_tableWidget->setColumnWidth(3,60);//性别

    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }
    // 查询数据添加到表格
    QSqlQuery query;
   //  query.exec(QString("select address_building,address_room,address_bed,stuname,stusex,studepart from stuinfo"
     //                   " where (address_building,address_room) in"
       //                 " (select address_building,address_room from stuinfo where sid = %1 )").arg(id));
    query.exec(QString(" select stadepart,sid,staname,stasex,address_building,address_pos from staff_info"
                         " where stadepart in"
                         " (select stadepart from staff_info where sid = %1 )").arg(id));

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


