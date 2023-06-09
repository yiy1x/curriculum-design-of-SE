#ifndef STU_STUINFO_H
#define STU_STUINFO_H

#include <QWidget>

namespace Ui {
class stu_stuinfo;
}

class stu_stuinfo : public QWidget
{
    Q_OBJECT

public:
    explicit stu_stuinfo(QWidget *parent = nullptr);
    ~stu_stuinfo();
    void initUI(QString id);

private:
    Ui::stu_stuinfo *ui;
    QString username;//用户名，即学生学号
    QString passwd;
};

#endif // STU_STUINFO_H
