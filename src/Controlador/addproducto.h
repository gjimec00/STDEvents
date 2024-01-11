#ifndef ADDPRODUCTO_H
#define ADDPRODUCTO_H

#include <QDialog>

namespace Ui {
class addproducto;
}

class addproducto : public QDialog
{
    Q_OBJECT

public:
    explicit addproducto(QWidget *parent = nullptr);
    ~addproducto();
private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::addproducto *ui;
};

#endif // ADDPRODUCTO_H
