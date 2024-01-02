#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <QDialog>

namespace Ui {
class Calendario;
}

class Calendario : public QDialog
{
    Q_OBJECT

public:
    explicit Calendario(QWidget *parent = nullptr);
    ~Calendario();

private:
    Ui::Calendario *ui;
};

#endif // CALENDARIO_H
