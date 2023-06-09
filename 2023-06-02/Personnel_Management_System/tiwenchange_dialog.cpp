#include "tiwenchange_dialog.h"
#include "ui_tiwenchange_dialog.h"
#include <QSqlQuery>
#include<QMessageBox>
#include<qdebug.h>
#include"searchtiwen.h"

TiWenchange_Dialog::TiWenchange_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TiWenchange_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("修改异常体温信息");
}

TiWenchange_Dialog::~TiWenchange_Dialog()
{
    delete ui;
}


void TiWenchange_Dialog::load(QString id,QString date)
{
    this->id = id;
    this->date = date;
    qDebug()<<date<<"  "<<id;
    QSqlQuery query;
    query.exec(QString("select date,tiwen,address_building,address_room,sid,stuname from stuinfo NATURAL JOIN stutem "
                       "where sid = %1 and date = '%2'").arg(id).arg(date));
   // if(!query.exec())
   // {
    //    QMessageBox::information(this,"错误","shibai");
   // }
    QString _date;
    QString sid;
    QString stuname;
    QString address_building;
    QString address_room;
    QString tiwen;
    while(query.next())
    {
        _date = query.value(0).toString();
        tiwen = query.value(1).toString();
        address_building = query.value(2).toString();
        address_room = query.value(3).toString();
        sid = query.value(4).toString();
        stuname = query.value(5).toString();
    }
    ui->date_lineEdit->setText(_date);
    ui->date_lineEdit->setReadOnly(true);
    ui->sid_lineEdit->setText(sid);
    ui->sid_lineEdit->setReadOnly(true);
    ui->stuname_lineEdit->setText(stuname);
    ui->stuname_lineEdit->setReadOnly(true);
    ui->building_lineEdit->setText(address_building);
    ui->building_lineEdit->setReadOnly(true);
    ui->room_lineEdit->setText(address_room);
    ui->room_lineEdit->setReadOnly(true);
    ui->tiwen_lineEdit->setText(tiwen);
    ui->tiwen_lineEdit->setReadOnly(true);
    ui->tiwenchange_lineEdit->setText(tiwen);
}

void TiWenchange_Dialog::on_update_pushButton_clicked()
{
    QString sid = ui->sid_lineEdit->text().trimmed();
    QString theDate = ui->date_lineEdit->text().trimmed();
    QString new_tiwen = ui->tiwenchange_lineEdit->text().trimmed();
    if(new_tiwen.isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入完整内容");
        return;
    }
    double theTiwen = new_tiwen.toFloat();
    if(theTiwen<36||theTiwen>37)
    {
        QMessageBox::warning(this,"提示","您输入的新体温异常");
        return;
    }
    QSqlQuery query;
    QString sql = QString("update stutem set tiwen =%1 where sid = %2 and date = '%3'"
                          " ")
              .arg(new_tiwen,sid,theDate);

    qDebug()<<sql;
    if(query.exec(sql))
    {
        // 关闭窗口
        close();

        // 刷新列表
        searchTiWen*  searchStuWeight = (searchTiWen*) parentWidget();
        searchStuWeight->tableReflash();
        QMessageBox::information(this,"成功","修改成功");
    }
    else
        QMessageBox::information(this,"失败","修改失败");
}
