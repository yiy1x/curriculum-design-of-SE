#include "stu_yichang.h"
#include "ui_stu_yichang.h"

stu_yichang::stu_yichang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_yichang)
{
    ui->setupUi(this);
    setWindowTitle("体温异常提示");
    Qt::WindowFlags flags = Qt::Dialog;
     this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
}

stu_yichang::~stu_yichang()
{
    delete ui;
}


void stu_yichang::on_insert_pushButton_clicked()
{
    stu_tiwen*  searchStuWeight = (stu_tiwen*) parentWidget();
    searchStuWeight->yichang = true;
    searchStuWeight->first_of = false;

    close();
    searchStuWeight->on_pushButton_clicked();
}

void stu_yichang::on_insert_pushButton_2_clicked()
{
    stu_tiwen*  searchStuWeight = (stu_tiwen*) parentWidget();
    searchStuWeight->yichang = false;
    close();
}
