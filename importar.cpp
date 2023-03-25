#include "importar.h"
#include "ui_importar.h"
#include<QCompleter>
#include<QFileSystemModel>
#include<QFileDialog>

Importar::Importar(QWidget *parent) : QDialog(parent),ui(new Ui::Importar){
    ui->setupUi(this);

    QFileSystemModel *m = new QFileSystemModel(this);
    QCompleter *c = new QCompleter(m,this);

    m->setRootPath(QDir::rootPath());

    ui->ruta->setCompleter(c);

    ui->base->setCurrentIndex(1);
    this->adjustSize();
}

Importar::~Importar()
{
    delete ui;
}

void Importar::on_buttonBox_accepted(){
    ui->base->setCurrentIndex(1);
}


void Importar::on_buscarRuta_clicked(){

    QStringList fileTypes;
    fileTypes << "Archivos de Excel (*.xls *.xlsx)" << "Archivos CSV (*.csv)" << "Archivos de texto (*.txt)";

    QString directory = QFileDialog::getOpenFileName(this,"Buscar Archivo",QDir::homePath(), fileTypes.join(";;"));

    ui->ruta->setText(directory);
}


void Importar::on_ruta_editingFinished(){

}

