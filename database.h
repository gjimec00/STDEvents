#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
class DataBase
{
public:
    DataBase(const QString &nombreBaseDatos,
             const QString &nombreUsuario,
             const QString &passwordUsuario,
             const QString &direccionServidor,
             int puertoConexion);

private:
    QSqlDatabase mDb;
};

#endif // DATABASE_H
