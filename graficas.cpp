#include "graficas.h"
#include "ui_graficas.h"

Graficas::Graficas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graficas)
{
    ui->setupUi(this);
}

Graficas::~Graficas()
{
    delete ui;
}

void Graficas::PasarArbolMatrices(QTreeWidgetItem *ArbolMatrices){
    this->ArbolMatrices = ArbolMatrices;
    ui->base->addTopLevelItem(this->ArbolMatrices);
}

void Graficas::PasarItem(QTreeWidgetItem *item){
    this->item = item;
}

void Graficas::on_pushButton_clicked(){
    //item = this->ArbolMatrices->child(this->ArbolMatrices->indexOfChild(item));
    qDebug()<<item->text(0);
    item->setExpanded(true);
    QTreeWidgetItem *nItem = new QTreeWidgetItem();

    nItem->setText(0,item->text(0));
    nItem->setIcon(0,QIcon(":/new/prefix1/iconos/graficar.png"));

    if(item->childCount() > 0){
        for(int i=0;i<item->childCount();i++){
            if(item->child(i)->text(0) == "Graficas"){
                item->child(i)->addChild(nItem);
                return;
            }
        }

        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);

        PItem->setText(0,"Graficas");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/barra-grafica.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
    else{
        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);
        PItem->setText(0,"Graficas");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/barra-grafica.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
}

