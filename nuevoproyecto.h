#ifndef NUEVOPROYECTO_H
#define NUEVOPROYECTO_H

#include <QDialog>

namespace Ui {
class NuevoProyecto;
}

class NuevoProyecto : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoProyecto(QWidget *parent = nullptr);
    ~NuevoProyecto();
    bool GetOk();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NuevoProyecto *ui;
    bool ok = true;
};

#endif // NUEVOPROYECTO_H
