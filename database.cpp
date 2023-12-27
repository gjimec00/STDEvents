#include "database.h"
#include <QSqlError>

DataBase::DataBase(const QString &nombreBaseDatos,
                   const QString &nombreUsuario,
                   const QString &passwordUsuario,
                   const QString &direccionServidor,
                   int puertoConexion)

{
    mDb = QSqlDatabase::addDatabase("QMYSQL");
    mDb.setDatabaseName(nombreBaseDatos);
    mDb.setUserName(nombreUsuario);
    mDb.setPassword(passwordUsuario);
    mDb.setHostName(direccionServidor);
    mDb.setPort(puertoConexion);

}

bool DataBase::abreConexion(QString &mensajeError){

    if (!mDb.open()){
        mensajeError = mDb.lastError().text();
        return false;
    }
    return true;
}
