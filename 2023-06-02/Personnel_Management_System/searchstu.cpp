#include "searchstu.h"
#include "ui_searchstu.h"
#include<QSqlQuery>
#include<QDebug>
#include <QtWidgets>
#include<QTimer>
#include"insertdialog.h"
#include"updatedialog.h"

searchStu::searchStu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchStu)
{
    ui->setupUi(this);



    // 设置列表列头
    ui->information_tableWidget->setColumnCount(11);
    ui->information_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("*选择栏"));
    ui->information_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("工号"));
    ui->information_tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("员工姓名"));
    ui->information_tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("性别"));
    ui->information_tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("电话"));
    ui->information_tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("入职时间"));
    ui->information_tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("部门"));
    ui->information_tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("职位"));
    ui->information_tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("房间号"));
    ui->information_tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("工位"));
    ui->information_tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("薪水"));
    // 设置列表自动填充满窗口(针对姓名和院系）
    //ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->information_tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    // 设置列表列宽度
    ui->information_tableWidget->setColumnWidth(0,80);
    ui->information_tableWidget->setColumnWidth(1,110);//sid
    ui->information_tableWidget->setColumnWidth(2,100);//name
    ui->information_tableWidget->setColumnWidth(3,60);//性别
    ui->information_tableWidget->setColumnWidth(4,110);//tel
    ui->information_tableWidget->setColumnWidth(5,120);//time
    ui->information_tableWidget->setColumnWidth(6,80);//part
    ui->information_tableWidget->setColumnWidth(7,60);//职位
    ui->information_tableWidget->setColumnWidth(8,60);//房间号
    ui->information_tableWidget->setColumnWidth(9,60);//工位
    ui->information_tableWidget->setColumnWidth(10,60);//薪水

    // 刷新表格数据
    tableReflash();

}

searchStu::~searchStu()
{
    delete ui;
}

// 设置单元格信息
void searchStu::cellSetting(int row, int column, QString text)
{
    QLineEdit* lineEdit = new QLineEdit(text);
    lineEdit->setStyleSheet("border: 0px;color:black"); // 设置该输入框无边框，黑色字体
    // 设置只读
    lineEdit->setReadOnly(true);
    ui->information_tableWidget->setCellWidget(row, column, lineEdit);
}



// 刷新表格数据
void searchStu::tableReflash(QString selectSql)
{
    // 先移除表格所有行
    for(int row = ui->information_tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->information_tableWidget->removeRow(row);
    }
    // 查询数据添加到表格
    QSqlQuery query;
    if(selectSql.isEmpty()) {
        QString sql = "select sid,staname,stasex,tel,entry_time,stadepart,job,address_building,address_pos,salary from staff_info order by sid ";
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
                  ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString()<<","<<query.value(6).toString();
        row++;
    }
}


// 查询学生信息
void searchStu::selectStudent()
{
    QString searchParam = ui->select_param_edit->text().trimmed();
    if(searchParam.isEmpty()) {
        tableReflash();
        return;
    }
    tableReflash(QString("select sid,staname,stasex,tel,entry_time,stadepart,job,address_building,address_pos,salary from staff_info where staname like \"%1%2\" or sid like \"%3%4\"")
                 .arg(searchParam,"%",searchParam,"%"));
}

// 删除学生信息
void searchStu::deleteStudent()
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
        QMessageBox::information(this,"提示","请先勾选要删除的行");
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
    QString sql = "delete from staff_info where sid in(" + idsStr + ")";
    QString sql2 = "delete from users where username in(" + idsStr + ")";
    QString sql10 = "delete from staff_salary where sid in(" + idsStr + ")";
    qDebug()<<sql;
    qDebug()<<sql2;
    qDebug()<<sql10;
    QSqlQuery query, query2, query3;
    if(query.exec(sql)&&query2.exec(sql2)&&query3.exec(sql10)) {
        // 刷新表格
        tableReflash();
        QMessageBox::information(this,"成功","删除成功");
    } else {
        QMessageBox::information(this,"失败","删除失败");
    }
}

void searchStu::on_refer_pushButton_clicked()
{
    selectStudent();
}

void searchStu::on_delete_pushButton_clicked()
{
    deleteStudent();
}

void searchStu::on_change_pushButton_clicked()
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
        QMessageBox::information(this,"提示","请先勾选要修改的行");
        return;
    }
    if(ids.size() > 1) {
        QMessageBox::information(this,"提示","修改时只能勾选单行数据");
        return;
    }
    updateDialog* student_update = new updateDialog(this);
    student_update->setAttribute(Qt::WA_DeleteOnClose); // 关闭时销毁对象
    student_update->setModal(true); // 设置为模态窗口，即窗口打开后只能该修改界面操作，不能在其他窗口进行操作，保证操作时的唯一性
    student_update->load(ids.at(0));
    student_update->show();
}

void searchStu::on_add_pushButton_clicked()
{
    insertDialog* student_insert = new insertDialog(this);
    student_insert->setAttribute(Qt::WA_DeleteOnClose); // 关闭时销毁对象
    student_insert->setModal(true); // 设置为模态窗口，即窗口打开后只能该修改界面操作，不能在其他窗口进行操作，保证操作时的唯一性
    student_insert->show();
}

void searchStu::on_clear_pushButton_clicked()
{
    ui->select_param_edit->clear();
    tableReflash();
}
