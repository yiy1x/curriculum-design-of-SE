#include "baoxiu_1.h"
#include "ui_baoxiu_1.h"
#include <QSqlQuery>
#include<QMessageBox>
#include<qdebug.h>
#include<QDateTime>
#include"searchbaoxiu.h"

baoxiu_1::baoxiu_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baoxiu_1)
{
    ui->setupUi(this);
     ui->dateEdit->setDateTime(QDateTime::currentDateTime());
     setWindowTitle("设定上门修理时间");
}

baoxiu_1::~baoxiu_1()
{
    delete ui;
}

void baoxiu_1::load(QString building, QString room, QString t_date)
{


    QSqlQuery query;
    QString sql =QString("select shendate,address_building,address_room,content,beizhu from apartxiu "
                         "where address_building = '%1' and address_room = '%2' and shendate = '%3'").arg(building).arg(room).arg(t_date);
    qDebug()<<sql;
    query.exec(sql);
   // if(!query.exec())
   // {
    //    QMessageBox::information(this,"错误","shibai");
   // }
    QString _date;
    QString address_building;
    QString address_room;
    QString content;
    QString beizhu;
    while(query.next())
    {
        _date = query.value(0).toString();
        address_building = query.value(1).toString();
        address_room = query.value(2).toString();
        content = query.value(3).toString();
        beizhu = query.value(4).toString();
    }

;
    ui->date_lineEdit->setText(_date);
     ui->date_lineEdit->setReadOnly(true);
    ui->building_lineEdit->setText(address_building);
    ui->building_lineEdit->setReadOnly(true);
    ui->room_lineEdit->setText(address_room);
    ui->room_lineEdit->setReadOnly(true);
    ui->content_lineEdit->setText(content);
    ui->content_lineEdit->setReadOnly(true);
    ui->beizhu_lineEdit->setText(beizhu);
    ui->beizhu_lineEdit->setReadOnly(true);
}

void baoxiu_1::on_update_pushButton_clicked()
{
    QString _date= ui->date_lineEdit->text().trimmed();
    QString address_building= ui->building_lineEdit->text().trimmed();
    QString address_room= ui->room_lineEdit->text().trimmed();

    QString xiudate = ui->dateEdit->text().trimmed();


    QDateTime shen = QDateTime::fromString(_date,"yyyy-mm-dd");
    QDateTime xiu = QDateTime::fromString(xiudate,"yyyy/mm/dd");
    if(xiu<shen)
    {
         QMessageBox::critical(this,"错误","处理日期不得早于申报日期");
         return;
    }



    QSqlQuery query;
    QString sql = QString("update apartxiu set xiudate = '%1',type = '1' where address_building = '%2' and address_room = '%3' and shendate = '%4' "
                          " ")
              .arg(xiudate,address_building,address_room,_date);

    qDebug()<<sql;
    if(query.exec(sql))
    {
        // 关闭窗口
        close();

        // 刷新列表
        searchbaoxiu*  searchStuWeight = (searchbaoxiu*) parentWidget();
        searchStuWeight->tableReflash();
        QMessageBox::information(this,"成功","处理成功");
    }
    else
        QMessageBox::information(this,"失败","处理失败");

}
