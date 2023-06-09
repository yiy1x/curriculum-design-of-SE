#ifndef STU_BAOXIU2_H
#define STU_BAOXIU2_H

#include <QWidget>

namespace Ui {
class stu_baoxiu2;
}

class stu_baoxiu2 : public QWidget
{
    Q_OBJECT

public:
    explicit stu_baoxiu2(QWidget *parent = nullptr);
    ~stu_baoxiu2();
       void tableReflash(QString selectSql = QString());//刷新表格
        void initUI(QString id);

private:
    Ui::stu_baoxiu2 *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
    QString id;
};

#endif // STU_BAOXIU2_H
