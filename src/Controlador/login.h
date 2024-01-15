#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "src/Modelo/conexion/database.h"

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
    Ui::login *ui;

private slots:


    void on_exit_clicked();

    void on_register_2_clicked();

    void on_login_2_clicked();

    void comprobarUsuario();

    void abrirVistaAdministrador();

    void abrirVistaCliente();

private:

    DataBase mBaseDatos;
};
#endif // LOGIN_H
