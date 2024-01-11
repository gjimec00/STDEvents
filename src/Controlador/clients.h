#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>

namespace Ui {
class clients;
}

class clients : public QDialog
{
    Q_OBJECT

public:
    explicit clients(QWidget *parent = nullptr);
    ~clients();

private:
    Ui::clients *ui;
private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void verificarDni();
};

#endif // CLIENTS_H
