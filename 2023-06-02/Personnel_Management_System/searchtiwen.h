﻿#ifndef SEARCHTIWEN_H
#define SEARCHTIWEN_H

#include <QWidget>

namespace Ui {
class searchTiWen;
}

class searchTiWen : public QWidget
{
    Q_OBJECT

public:
    explicit searchTiWen(QWidget *parent = nullptr);
    ~searchTiWen();
    void tableReflash(QString selectSql = QString());//刷新表格
private slots:
    void on_refer_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void on_add_pushButton_clicked();

    void on_change_pushButton_clicked();

private:
    Ui::searchTiWen *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
    // 查询学生信息
    void selectStudent();
    // 删除学生信息
    void deleteStudent();
};

#endif // SEARCHTIWEN_H
