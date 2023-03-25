#include "latex.h"
#include "ui_latex.h"
#include<QDebug>

LaTex::LaTex(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LaTex)
{
    ui->setupUi(this);

    ui->codigo->setWordWrapMode(QTextOption::NoWrap);
}

LaTex::~LaTex(){
    delete ui;
}

void LaTex::PasarDatos(QList<QTreeWidgetItem *> d){

    ui->arbol->clear();

    for(int j=0;j<d.size();j++){
        QTreeWidgetItem *nitem = new QTreeWidgetItem();



        if(d.at(j)->childCount() > 0){



            for(int i=0;i<d.at(j)->childCount();i++){
                QTreeWidgetItem *cItem = new QTreeWidgetItem();
                cItem->setText(0,d.at(j)->child(i)->text(0));
                cItem->setIcon(0,d.at(j)->child(i)->icon(0));

                nitem->addChild(cItem);
            }


        }

        nitem->setText(0,d.at(j)->text(0));
        nitem->setIcon(0,d.at(j)->icon(0));

        ui->arbol->addTopLevelItem(nitem);
    }


}

void LaTex::PasarMatrices(vector<Matriz *> m){
    for(int i=0;i<m.size();i++){
        Matriz *nMatriz = new Matriz(m.at(i));

        this->m.push_back(nMatriz);
    }
}

void LaTex::CrearCodigoLatex(int i){
    QString codigo;

    /*

        \begin{figure}[h!]
            \centering

            \begin{equation*}
                \begin{bNiceMatrix}[first-row,first-col]
                    &u_2 & v_2 & u_1 & v_1 \\
                    u_2&1 & \sqrt{3} & -1 & -\sqrt{3} \\
                    v_2&\sqrt{3} & 3 & -\sqrt{3} & -3 \\
                    u_1&-1 & -\sqrt{3} & 1 & \sqrt{3} \\
                    v_1&-\sqrt{3} & -3 & \sqrt{3} & 3 \\
                \end{bNiceMatrix}
            \end{equation*}

            \caption{}
        \end{figure}

     */




    codigo = "\\begin{figure}[h!]\n";
    codigo += "\t \\centering\n\n";
    codigo += "\t \\begin{equation*}\n";
    codigo += "\t \t \\begin{bNiceMatrix}[first-row,first-col]\n";

    codigo += "\t \t \t ";

    for(int j=0;j<m.at(i)->getColumnas();j++){
        codigo +="&";
        codigo +=" ";
        codigo +=QString::number(j+1);
        codigo += " ";
    }

    codigo += "\\\\";

    for(int j=0;j<m.at(i)->getFilas();j++){
        codigo +="\n \t \t \t";
        codigo +=QString::number(j+1);
        for(int z=0;z<m.at(i)->getColumnas();z++){
            codigo +=" & ";
            codigo +=QString::number(m.at(i)->getValor(j,z));
        }
        codigo +="\\\\ \n";
    }

    codigo += "\t \t \\end{bNiceMatrix}\n";
    codigo += "\t \\end{equation*}\n";
    codigo += "\\end{figure}";

    ui->codigo->setText(codigo);
}

void LaTex::on_arbol_itemClicked(QTreeWidgetItem *item, int column){
    if(item->parent()->text(0) == "Matrices"){

        CrearCodigoLatex(item->parent()->indexOfChild(item));
    }
    else if(item->text(0) == "Variables"){

    }
}


