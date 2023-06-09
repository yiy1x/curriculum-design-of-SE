#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class updateDialog;
}

class updateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updateDialog(QWidget *parent = 0);
    // 通过学生表id字段值加载数据到修改界面
    void load(QString id);
    ~updateDialog();

private slots:
    void on_update_pushButton_clicked();

private:
    Ui::updateDialog *ui;
    // id,学生信息的id字段值
    QString id;
};

#endif // UPDATEDIALOG_H
