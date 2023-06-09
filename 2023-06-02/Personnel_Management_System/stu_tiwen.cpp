#include "stu_tiwen.h"
#include "ui_stu_tiwen.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QTextCodec>
#include"stu_yichang.h"
#include<QDateTime>

stu_tiwen::stu_tiwen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_tiwen)
{
    ui->setupUi(this);
    QRegExp rx("^[3]|[3][0-9]|[3][0-9][\\.]|[3][0-9][\\.][0-9]|[4]|[4][0-4]|[4][0-4][\\.]|[4][0-4][\\.][0-9]|[4][5]|[4][5][\\.]|[4][5][\\.][0]$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    //ui->tiwen_lineEdit->setValidator(pReg);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString s_date = date.toString("hh:mm:ss");
    ui->dateEdit->setDate(date);
    ui->timeEdit->setTime(time);
    ui->timeEdit->setReadOnly(true);
    ui->dateEdit->setReadOnly(true);
}


stu_tiwen::~stu_tiwen()
{
    delete ui;
}

void stu_tiwen::initUI(QString id)
{
    this->id = id;
}


void stu_tiwen::on_pushButton_clicked()
{
    //Qstring time = ui->timeEdit
    // new_tiwen = ui->tiwen_lineEdit->text().trimmed();
    QString theDate = ui->dateEdit->text().trimmed();
    /*if(new_tiwen.isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入完整内容");
        return;
    }
    double theTiwen = new_tiwen.toDouble();*/



    //是否今日已填报
    QSqlQuery ifin_query;
    QString in_sql = QString("select sid,date from attend where sid = '%1' and date = '%2'").arg(id).arg(theDate);
    qDebug()<<in_sql;
    ifin_query.exec(in_sql);
    while (ifin_query.next())//有数据
    {
        QMessageBox::information(this,"提示","您今日已经打卡！");
        return;
    }


    /*if(theTiwen<36||theTiwen>37)//体温异常弹出提示框
    {
        if(first_of)
         {   yichang = false;
        stu_yichang* stu_change = new stu_yichang(this);
        stu_change->setAttribute(Qt::WA_DeleteOnClose); // 关闭时销毁对象
        stu_change->setModal(true); // 设置为模态窗口，即窗口打开后只能该修改界面操作，不能在其他窗口进行操作，保证操作时的唯一性
        stu_change->show();
        if(!yichang)
        {
            return;
        }
        }
    }*/


    QSqlQuery query;
    QString sql = QString("insert into attend (sid,date,time) values (\"%1\",curdate(),curtime())")
              .arg(id);

    qDebug()<<sql;
    if(query.exec(sql))
    {

        //ui->tiwen_lineEdit->clear();
        first_of = true;
        QMessageBox::information(this,"成功","打卡成功");
    }
    else
        QMessageBox::critical(this,"失败","打卡失败");
}
