#ifndef SEARCHAPART_H
#define SEARCHAPART_H

#include <QWidget>

namespace Ui {
class searchApart;
}

class searchApart : public QWidget
{
    Q_OBJECT

public:
    explicit searchApart(QWidget *parent = nullptr);
    ~searchApart();
     void tableReflash(QString selectSql = QString());//刷新表格

private slots:
     void on_refer_pushButton_clicked();

     void on_clear_pushButton_clicked();

private:
    Ui::searchApart *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
    // 查询学生信息
    void selectStudent();
};

#endif // SEARCHAPART_H
