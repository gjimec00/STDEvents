#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QDialog>

namespace Ui {
class asientos;
}

class asientos : public QDialog
{
    Q_OBJECT

public:
    explicit asientos(QWidget *parent = nullptr);
    ~asientos();

private slots:
    void on_pushButton_4_clicked();

    int generarAsientos();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::asientos *ui;
};

#endif // ASIENTOS_H
