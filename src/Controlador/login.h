#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "src/Modelo/database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:


    void on_exit_clicked();

    void on_register_2_clicked();

private:
    Ui::login *ui;
    DataBase mBaseDatos;
};
#endif // LOGIN_H
