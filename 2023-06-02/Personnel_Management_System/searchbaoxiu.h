#ifndef SEARCHBAOXIU_H
#define SEARCHBAOXIU_H

#include <QWidget>

namespace Ui {
class searchbaoxiu;
}

class searchbaoxiu : public QWidget
{
    Q_OBJECT

public:
    explicit searchbaoxiu(QWidget *parent = nullptr);
    ~searchbaoxiu();
    void tableReflash(QString selectSql = QString());//刷新表格


private slots:
    void on_on_change_pushButton_clicked();

private:
    Ui::searchbaoxiu *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);

};

#endif // SEARCHBAOXIU_H
