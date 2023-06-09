#ifndef STUGUANLI_H
#define STUGUANLI_H

#include <QWidget>

namespace Ui {
class stuGuanLi;
}

class stuGuanLi : public QWidget
{
    Q_OBJECT

public:
    explicit stuGuanLi(QWidget *parent = nullptr);
    ~stuGuanLi();
    void tableReflash(QString selectSql = QString());//刷新表格

private slots:
    void on_refer_pushButton_3_clicked();

    void on_clear_pushButton_3_clicked();

    void on_reMiMa_pushButton_clicked();

private:
    Ui::stuGuanLi *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
    // 查询学生信息
    void selectStudent();
};

#endif // STUGUANLI_H
