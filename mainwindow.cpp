#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nuevoproyecto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicio(){

    QList<QAction*> actions = ui->funciones->actions();

    for(int i=0;i<actions.count();i++){
        if(actions.at(i)->isEnabled() == false){
            actions.at(i)->setEnabled(true);
        }
    }

    actions = ui->toolBar->actions();

    for(int i=0;i<actions.count();i++){
        if(actions.at(i)->isEnabled() == false){
            actions.at(i)->setEnabled(true);
        }
    }

}


void MainWindow::on_actionNuevo_Proyecto_triggered(){
    NuevoProyecto n(this);

    n.exec();

    if(n.GetOk()){
        inicio();
    }
}

