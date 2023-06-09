#ifndef STU_APARTINFO_H
#define STU_APARTINFO_H

#include <QWidget>

namespace Ui {
class stu_apartinfo;
}

class stu_apartinfo : public QWidget
{
    Q_OBJECT

public:
    explicit stu_apartinfo(QWidget *parent = nullptr);
    ~stu_apartinfo();
    void tableReflash(QString id);//刷新表格

private:
    Ui::stu_apartinfo *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
};

#endif // STU_APARTINFO_H
