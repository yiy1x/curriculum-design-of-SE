#ifndef SEARCHBAOXIU_2_H
#define SEARCHBAOXIU_2_H

#include <QWidget>

namespace Ui {
class searchbaoxiu_2;
}

class searchbaoxiu_2 : public QWidget
{
    Q_OBJECT

public:
    explicit searchbaoxiu_2(QWidget *parent = nullptr);
    ~searchbaoxiu_2();
    void tableReflash(QString selectSql = QString());//刷新表格

private slots:
    void on_on_change_pushButton_clicked();

private:
    Ui::searchbaoxiu_2 *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
};

#endif // SEARCHBAOXIU_2_H
