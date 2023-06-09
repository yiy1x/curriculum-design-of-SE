#include "stu_stuinfo.h"
#include "ui_stu_stuinfo.h"
#include<QSqlQuery>
#include<QSettings>
#include<QDebug>
#include<QMessageBox>

stu_stuinfo::stu_stuinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_stuinfo)
{
    ui->setupUi(this);
}

stu_stuinfo::~stu_stuinfo()
{
    delete ui;
}

void stu_stuinfo::initUI(QString id)
{
   // 查询数据添加到表格
    QSqlQuery query;
   bool sql =query.exec(QString("select sid,staname,stasex,tel,entry_time,stadepart,job,address_building,address_pos,salary from staff_info where sid = %1").arg(id));
   QString sid;
   QString stuname;
   QString stusex;
   QString tel;
   QString entry_time;
   QString stadepart;
   QString job;
   QString address_building;
   QString address_pos;
   QString salary;
   qDebug()<<QString("select sid,staname,stasex,tel,entry_time,stadepart,` job`,address_building,address_pos,salary from staff_info where sid = %1").arg(id)<<endl;
    if(!sql)
    {
        QMessageBox::critical(this,"错误","执行查询失败！",QMessageBox::Ok);
    }
   while(query.next())
   {
       sid = query.value(0).toString();
       stuname = query.value(1).toString();
       stusex = query.value(2).toString();
       tel = query.value(3).toString();
       entry_time = query.value(4).toString();
       stadepart = query.value(5).toString();
       job = query.value(6).toString();
       address_building = query.value(7).toString();
       address_pos = query.value(8).toString();
       salary = query.value(9).toString();
       //qDebug()<<"entry_time"<<entry_time<<endl;
       //qDebug()<<"salary"<<salary<<endl;
       qDebug()<<query.value(0).toString()<<","<<query.value(1).toString()<<","<<query.value(2).toString()<<
                 ","<<query.value(3).toString()<<","<<query.value(4).toString()<<","<<query.value(5).toString()<<","
              <<query.value(6).toString()<<","<<query.value(7).toString()<<","<<query.value(8).toString()<<","<<query.value(9).toString();
   }
   ui->lineEdit->setText(sid);
   ui->lineEdit_2->setText(stuname);
   ui->lineEdit_3->setText(stusex);
   ui->lineEdit_4->setText(tel);
   ui->lineEdit_5->setText(entry_time);
   ui->lineEdit_6->setText(stadepart);
   ui->lineEdit_7->setText(job);
   ui->lineEdit_8->setText(salary);
   ui->lineEdit->setReadOnly(true);
   ui->lineEdit_2->setReadOnly(true);
   ui->lineEdit_3->setReadOnly(true);
   ui->lineEdit_4->setReadOnly(true);
   ui->lineEdit_5->setReadOnly(true);
   ui->lineEdit_6->setReadOnly(true);
   ui->lineEdit_7->setReadOnly(true);
   ui->lineEdit_8->setReadOnly(true);
}




