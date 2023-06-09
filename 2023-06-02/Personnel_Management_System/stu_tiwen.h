#ifndef STU_TIWEN_H
#define STU_TIWEN_H

#include <QWidget>

namespace Ui {
class stu_tiwen;
}

class stu_tiwen : public QWidget
{
    Q_OBJECT

public:
    explicit stu_tiwen(QWidget *parent = nullptr);
     void initUI(QString id);
    ~stu_tiwen();
     bool yichang;
     bool first_of;

public slots:
     void on_pushButton_clicked();

private:
    Ui::stu_tiwen *ui;
    QString id;
};

#endif // STU_TIWEN_H
