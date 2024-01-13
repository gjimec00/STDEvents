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

private:
    Ui::asientos *ui;
};

#endif // ASIENTOS_H
