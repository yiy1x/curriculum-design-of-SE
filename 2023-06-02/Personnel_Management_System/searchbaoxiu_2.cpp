#include "searchbaoxiu_2.h"
#include "ui_searchbaoxiu_2.h"
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>
#include<QLineEdit>

searchbaoxiu_2::searchbaoxiu_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchbaoxiu_2)
{
    ui->setupUi(this);
    // 设置列表列头
    ui->information_tableWidget->setColumnCount(7);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("处理日期"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("申请日期"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("所在楼层"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("房间号"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("事项描述"));
    ui->information_tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("备注"));


    // 设置列表自动填充满窗口(针对事件描述和备注）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,80);
    ui->information_tableWidget->setColumnWidth(3,80);//楼层
    ui->information_tableWidget->setColumnWidth(4,80);//房间号
    ui->information_tableWidget->setColumnWidth(1,130);//申请日期
    ui->information_tableWidget->setColumnWidth(6,130);//处理日期

      tableReflash();
}

searchbaoxiu_2::~searchbaoxiu_2()
{
    delete ui;
}

// 设置单元格信息
void searchbaoxiu_2::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}

// 刷新表格数据
void searchbaoxiu_2::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }

    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select xiudate,shendate,address_building,address_room,content,beizhu from apartxiu where type = '1' ";
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
        qDebug()<<query.value(0).toString()<<","<<query.value(1).toString()<<","<<query.value(2).toString()<<
                  ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString()<<","<<query.value(6).toString();
        row++;
    }
}



void searchbaoxiu_2::on_on_change_pushButton_clicked()
{
    int rowCount = ui->information_tableWidget->rowCount();
    QList<QString> ids;
    QList<QString> ids2;
    QList<QString> ids3;
    for(int row = 0;row<rowCount;row++) {
        QTableWidgetItem * item = ui->information_tableWidget->item(row,0);
        Qt::CheckState status = item->checkState();
        if(status == Qt::CheckState::Checked) {
            QLineEdit* idItem = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 3);
            QLineEdit* idItem2 = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 4);
            QLineEdit* idItem3 = (QLineEdit*) ui->information_tableWidget->cellWidget(row, 2);
            //ids.append(idItem->text().toInt());
            ids.append(idItem->text());
            ids2.append(idItem2->text());
            ids3.append(idItem3->text());

        }
    }
    if(ids.isEmpty()) {
        QMessageBox::information(this,"提示","请先勾选要处理的事件");
        return;
    }
    if(ids.size() > 1) {
        QMessageBox::information(this,"提示","处理事件时只能勾选单行数据");
        return;
    }
    QSqlQuery query;
    QString sql = QString("update apartxiu set type = '2' where address_building = '%1' and address_room = '%2' and shendate = '%3' "
                          " ")
              .arg(ids.at(0),ids2.at(0),ids3.at(0));
    qDebug()<<sql;
    if(query.exec(sql))
    {
        // 关闭窗口
        //close();

        // 刷新列表
        tableReflash();
        QMessageBox::information(this,"成功","处理成功");
    }
    else
        QMessageBox::information(this,"失败","处理失败");

}
