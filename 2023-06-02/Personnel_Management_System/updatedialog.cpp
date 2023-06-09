#include "updatedialog.h"
#include "ui_updatedialog.h"
#include"searchstu.h"
#include <QSqlQuery>
#include<QMessageBox>
#include<qdebug.h>

updateDialog::updateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateDialog)
{
    ui->setupUi(this);
    setWindowTitle("修改员工信息");
}

void updateDialog::load(QString id)
{
    this->id = id;
    QSqlQuery query;
    query.exec(QString("select sid,staname,stasex,tel,stadepart,job,address_building,address_pos,salary from staff_info where sid = %1").arg(id));
    QString s_sid;
    QString s_name;
    QString s_sex;
    QString s_tel;
    QString s_part;
    QString s_job;
    QString s_building;
    QString s_pos;
    QString s_salary;
    while(query.next())
    {
        s_sid = query.value(0).toString();
        s_name = query.value(1).toString();
        s_sex = query.value(2).toString();
        s_tel = query.value(3).toString();
        s_part = query.value(4).toString();
        s_job = query.value(5).toString();
        s_building = query.value(6).toString();
        s_pos = query.value(7).toString();
        s_salary = query.value(8).toString();
    }
    ui->sid_lineEdit->setText(s_sid);
    ui->sid_lineEdit->setReadOnly(true);
    ui->name_lineEdit->setText(s_name);
    ui->name_lineEdit->setReadOnly(true);
    ui->sex_lineEdit->setText(s_sex);
    ui->sex_lineEdit->setReadOnly(true);
    ui->tel_lineEdit->setText(s_tel);
   // ui->college_lineEdit->setReadOnly(true);
    ui->part_lineEdit->setText(s_part);
    ui->job_lineEdit->setText(s_job);
    ui->building_lineEdit->setText(s_building);
    ui->pos_lineEdit->setText(s_pos);
    ui->salary_lineEdit->setText(s_salary);

}

updateDialog::~updateDialog()
{
    delete ui;
}

void updateDialog::on_update_pushButton_clicked()
{
    QString s_sid = ui->sid_lineEdit->text().trimmed();//工号
    QString s_name = ui->name_lineEdit->text().trimmed();//姓名
    QString s_sex = ui->sex_lineEdit->text().trimmed();//性别
    QString s_tel =ui->tel_lineEdit->text().trimmed();//电话号码
    QString s_stadepart =ui->part_lineEdit->text().trimmed();//部门
    QString s_job =ui->job_lineEdit->text().trimmed();//职位
    QString s_building =ui->building_lineEdit->text().trimmed();//楼层和房间号
    QString s_pos =ui->pos_lineEdit->text().trimmed();//工位
    QString s_salary =ui->salary_lineEdit->text().trimmed();//薪资
    //判断电话号码格式
    if(s_tel.size() != 11){
        QMessageBox::warning(this,"提示","电话号码应该为11位！");
        return;
    }
    for(int i = 0; i < s_tel.size(); i++){
        if(s_tel[i] < '0' || s_tel[i] > '9'){
            QMessageBox::warning(this,"提示","电话号码格式错误！");
            return;
        }
    }
    //判断工位是否合法
    if(s_pos.size() > 1 || s_pos[0] < '0' || s_pos[0] > '9'){
        QMessageBox::information(this,"提示","工位错误！工位代号为数字0-9！");
        return;
    }
    if(s_sid.isEmpty() || s_name.isEmpty() ||s_sex.isEmpty() ||
            s_building.isEmpty() ||s_sex.isEmpty() || s_tel.isEmpty()
            ||s_stadepart.isEmpty()||s_job.isEmpty()||s_pos.isEmpty()||s_salary.isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入完整内容");
        return;
    }
/*
    //判断宿舍是否未满
    QSqlQuery ser_room;
    QString roomsql = QString("select count(*) from stuinfo where address_building = \"%1\" and address_room = \"%2\"")
            .arg(building_change,room_change);
    qDebug()<<roomsql;
    ser_room.exec(roomsql);
    while (ser_room.next())
    {
        int count2 = ser_room.value(0).toInt();
        if(count2==4)//宿舍满员
        {
            QMessageBox::warning(this,"警告","该宿舍已满员");
            return;
        }
    }
    //检查床位是否还在
    QSqlQuery ser_bed;
    QString bedsql = QString("select address_bed from stuinfo where address_building = \"%1\" and address_room = \"%2\" ")
            .arg(building_change,room_change);
    qDebug()<<bedsql;
    ser_bed.exec(bedsql);
    while (ser_bed.next())
    {
        if(ser_bed.value(0) == bed_change)//宿舍满员
        {
            QMessageBox::warning(this,"警告","该床位已有学生");
            return;
        }
    }

    QSqlQuery query;
    QString sql = QString("update stuinfo set address_building=\"%1\" ,address_room = \"%2\","
                                     "address_bed =\"%3\"  where sid =%4")
            .arg(building_change,room_change,bed_change,id);*/
    QSqlQuery query;
    QString sql = QString("update staff_info set tel='%1',stadepart='%2' ,job = '%3',"
                                     "address_building ='%4',address_pos = '%5',salary=%6 where sid ='%7'")
            .arg(s_tel,s_stadepart,s_job,s_building,s_pos,s_salary,id);
    qDebug()<<sql;
    //tel,stadepart,job,address_building,address_pos,salary
    if(query.exec(sql))
    {
        // 关闭窗口
        close();

        // 刷新列表
        searchStu*  searchStuWeight = (searchStu*) parentWidget();
        searchStuWeight->tableReflash();
        QMessageBox::information(this,"成功","修改成功");
    }
    else
        QMessageBox::information(this,"失败","修改失败");
}
