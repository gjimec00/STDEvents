#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <QDialog>

namespace Ui {
class administrador;
}

class administrador : public QDialog
{
    Q_OBJECT

public:
    explicit administrador(QWidget *parent = nullptr);
    ~administrador();

private:
    Ui::administrador *ui;
};

#endif // ADMINISTRADOR_H
