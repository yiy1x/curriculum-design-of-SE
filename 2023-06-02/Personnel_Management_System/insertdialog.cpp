#include "insertdialog.h"
#include "ui_insertdialog.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include<QMessageBox>
#include<QDebug>


insertDialog::insertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::insertDialog)
{
    ui->setupUi(this);
    setWindowTitle("新增员工信息");
    ui->sid_ineEdit->setFocus();
}

insertDialog::~insertDialog()
{
    delete ui;
}

void insertDialog::on_insert_pushButton_clicked()
{
    QString s_sid = ui->sid_ineEdit->text().trimmed();//工号
    QString s_name = ui->name_lineEdit->text().trimmed();//姓名
    QString s_sex = ui->sex_lineEdit->text().trimmed();//性别
    QString s_tel =ui->tel_lineEdit->text().trimmed();//电话号码
    QString s_time ;
    //QString s_time =ui->time_lineEdit->text().trimmed();//入职时间
    QString s_stadepart =ui->part_lineEdit->text().trimmed();//部门
    QString s_job =ui->job_lineEdit->text().trimmed();//职位
    QString s_building =ui->building_lineEdit->text().trimmed();//楼层和房间号
    QString s_pos =ui->pos_lineEdit->text().trimmed();//工位
    QString s_salary =ui->salary_lineEdit->text().trimmed();//薪资

    if(s_sid.size() < 8){
        QMessageBox::information(this,"提示","工号要大于8位数！");
        return;
    }
    for(int i = 0; i < s_sid.size(); i++){
        if(s_sid[i] < '0' || s_sid[i] > '9'){
            QMessageBox::information(this,"提示","工号必须为数字！");
            return;
        }

    }
    if(s_sex != "男" && s_sex != "女"){
        QMessageBox::information(this,"提示","性别错误！性别为男或女");
        return;
    }
    if(s_pos.size() > 1 || s_pos[0] < '0' || s_pos[0] > '9'){
        QMessageBox::information(this,"提示","工位错误！工位代号为数字0-9！");
        return;
    }
    //入职时间
    for(int i =0;i<8;i++)
    {
        s_time += s_sid[i];
    }

    if(s_sid.isEmpty() || s_name.isEmpty() ||s_sex.isEmpty() ||  s_tel.isEmpty()|| s_time.isEmpty() ||
      s_stadepart.isEmpty() ||s_job.isEmpty()||s_building.isEmpty()||
            s_pos.isEmpty()||s_salary.isEmpty())
    {
       QMessageBox::information(this,"提示","请输入完整");
       return;
    }
    //判断工号是否存在
    QSqlQuery query;
    QString sql = QString("select count(1) from staff_info where sid = \"%1\"").arg(s_sid);
    qDebug()<<sql;
    query.exec(sql);
    while(query.next())
    {
        int count = query.value(0).toInt();
        if(count > 0) {
            QMessageBox::warning(this,"警告","工号已存在");
            return;
        }
    }
    //判断宿舍是否未满
/*    QSqlQuery ser_room;
    QString roomsql = QString("select count(*) from stuinfo where address_building = \"%1\" and address_room = \"%2\"")
            .arg(student_apart,student_room);
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
            .arg(student_apart,student_room);
    qDebug()<<bedsql;
    ser_bed.exec(bedsql);
    while (ser_bed.next())
    {
        if(ser_bed.value(0) == student_bed)//宿舍满员
        {
            QMessageBox::warning(this,"警告","该床位已有学生");
            return;
        }
    }*/

    //QString insertSql = QString("insert into staff_info (sid,staname,stasex,tel,entry_time,stadepart,job,address_building,address_pos) values (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\")")
      //      .arg(s_sid,s_name,s_sex,s_tel,s_time,s_stadepart,s_job,s_building,s_pos);
    QString insertSql = QString("insert into staff_info (sid,staname,stasex,tel,entry_time,stadepart,job,address_building,address_pos) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
            .arg(s_sid,s_name,s_sex,s_tel,s_time,s_stadepart,s_job,s_building,s_pos);
    QString insertSql2 = QString("update staff_info set salary = %1 where sid = '%2'").arg(s_salary, s_sid);
    qDebug()<<insertSql << insertSql2;
    if(query.exec(insertSql) && query.exec(insertSql2))
    {
        // 关闭窗口
        close();

        // 刷新列表
       searchStu*  searchStuWeight = (searchStu*) parentWidget();
        searchStuWeight->tableReflash();
        QMessageBox::information(this,"成功","插入成功");

    }
    else
        QMessageBox::information(this,"失败","插入错误");

}
