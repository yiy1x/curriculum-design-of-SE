#include "stu_baoxiu1.h"
#include "ui_stu_baoxiu1.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QTextCodec>

stu_baoxiu1::stu_baoxiu1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_baoxiu1)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
}

stu_baoxiu1::~stu_baoxiu1()
{
    delete ui;
}

void stu_baoxiu1::initUI(QString id)
{
    this->id = id;
}



void stu_baoxiu1::on_pushButton_clicked()
{
    QString content = ui->tiwen_lineEdit->text().trimmed();
    QString theDate = ui->dateEdit->text().trimmed();
    QString beizhu = ui->tiwen_lineEdit_2->text().trimmed();
    if(content.isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入事项内容");
        return;
    }
    QSqlQuery ser_sushe_query;
    QString sushe_sql = QString("select address_building,address_room from stuinfo where sid = '%1'").arg(id);
     qDebug()<<sushe_sql;
     ser_sushe_query.exec(sushe_sql);
     QString address_building;
     QString address_room;
     while (ser_sushe_query.next())//得到宿舍数据
     {
           address_building = ser_sushe_query.value(0).toString();
           address_room = ser_sushe_query.value(1).toString();
     }

    //是否今日已填报
    QSqlQuery ifin_query;
    QString in_sql = QString("select address_building,address_room,shendate from apartxiu "
                             "where address_building = '%1' and address_room = '%2' and shendate = '%3'")
            .arg(address_building).arg(address_room).arg(theDate);
    qDebug()<<in_sql;
    ifin_query.exec(in_sql);
    while (ifin_query.next())//有数据
    {
        QMessageBox::information(this,"提示","该宿舍今日已经申请维修！");
        return;
    }
    QSqlQuery query;
    QString sql = QString("insert into apartxiu (address_building,address_room,shendate,content,beizhu,type)"
                          " values (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",'0')")
              .arg(address_building,address_room,theDate,content,beizhu);

    qDebug()<<sql;
    if(query.exec(sql))
    {

        ui->tiwen_lineEdit->clear();
        ui->tiwen_lineEdit_2->clear();
        QMessageBox::information(this,"成功","申请成功");
    }
    else
        QMessageBox::critical(this,"失败","申请失败");
}
