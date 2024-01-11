#ifndef EVENTOS_H
#define EVENTOS_H

#include <QDialog>

namespace Ui {
class eventos;
}

class eventos : public QDialog
{
    Q_OBJECT

public:
    explicit eventos(QWidget *parent = nullptr);
    ~eventos();

private:
    Ui::eventos *ui;
private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // EVENTOS_H
