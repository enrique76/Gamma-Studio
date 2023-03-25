#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nuevoproyecto.h"
#include<QLineEdit>
#include<QTableWidget>
#include<QMessageBox>
#include<time.h>
#include<matriceswidget.h>
#include<funcioneswidget.h>
#include<QPixmap>
#include"latex.h"
#include"etiquetas.h"
#include"importar.h"
#include"graficas.h"
#include<QInputDialog>
#include<QDir>
#include<QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    ui->lineEdit->setVisible(false);
    ui->base->setCurrentIndex(0);
    ui->AreaOperaciones->setCurrentIndex(0);
    ui->arbol->setVisible(false);

    QList<QAction *> l;

    l << ui->actionResolver<< ui->actionEliminar << ui->actionRenombrar << ui->actionRenombrar_Etiquetas << ui->actionRenombrar_Matrices << ui->actionCopiar << ui->actionPegar << ui->actionIntercambiar <<ui->actionInformacion << ui->actionGraficar <<ui->actionLaTex <<ui->actionCrear_Imagen;

    this->menuMatrices->addActions(l);

    l.clear();

    l << ui->actionAgregar_Matriz << ui->actionImportar;

    this->menuCarpetaMatrices->addActions(l);

    // menu imageness

    l.clear();

    l << ui->actionAbrir << ui->actionEliminar_2 << ui->actionGuardar_Como << ui->actionRenombrar_2;

    this->menuImagenes->addActions(l);

    //

    ui->progressBar->setVisible(false);

    //


    this->ArbolMatrices->setText(0,"Matrices");
    this->ArbolMatrices->setIcon(0,QIcon(":/new/prefix1/iconos/agregar-carpeta.png"));


    this->ArbolVariables->setText(0,"Variables");
    this->ArbolVariables->setIcon(0,QIcon(":/new/prefix1/iconos/variable.png"));

    this->ArbolFunciones->setText(0,"Funciones");
    this->ArbolFunciones->setIcon(0,QIcon(":/new/prefix1/iconos/funcion.png"));

    this->ArbolGraficas->setText(0,"Graficas");
    this->ArbolGraficas->setIcon(0,QIcon(":/new/prefix1/iconos/graficar.png"));

    this->ArbolInformacion->setText(0,"Informacion");
    this->ArbolInformacion->setIcon(0,QIcon(":/new/prefix1/iconos/informacion.png"));

    this->ArbolHistorial->setText(0,"Historial");
    this->ArbolHistorial->setIcon(0,QIcon(":/new/prefix1/iconos/historial.png"));

    this->ArbolConfiguraciones->setText(0,"Configuraciones");
    this->ArbolConfiguraciones->setIcon(0,QIcon(":/new/prefix1/iconos/configuracion.png"));



    ui->baseArbol->addTopLevelItem(this->ArbolMatrices);
    ui->baseArbol->addTopLevelItem(this->ArbolVariables);
    ui->baseArbol->addTopLevelItem(this->ArbolFunciones);
    ui->baseArbol->addTopLevelItem(this->ArbolGraficas);
    ui->baseArbol->addTopLevelItem(this->ArbolInformacion);
    ui->baseArbol->addTopLevelItem(this->ArbolHistorial);
    ui->baseArbol->addTopLevelItem(this->ArbolConfiguraciones);

    ui->baseArbol->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->baseArbol->addActions(menuMatrices->actions());


    ui->baseMatrices->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->baseMatrices->addActions(menuMatrices->actions());

    ui->baseArbol->setStyleSheet("QTreeView { background-color: transparent; border: none; }"
                                           "QHeaderView::section { background-color: transparent; border: none; border-bottom: 1px solid black; border-top-left-radius: 5px; border-top-right-radius: 5px; color: white; }"
                                           "QHeaderView::section:checked { background-color: rgba(255, 255, 255, 100); color: black; }");



    QString style = "QDockWidget { background-color: transparent; } "
                   "QDockWidget::title { background-color: transparent; } "
                   "QDockWidget::close-button { background-color: transparent; } "
                   "QDockWidget::float-button { background-color: transparent; } "
                   "QDockWidget::float-button:hover { background-color: rgba(0, 0, 0, 20); } "
                   "QDockWidget::float-button:pressed { background-color: rgba(0, 0, 0, 40); }";

    ui->arbol->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Inicio(){

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

    actions = menuMatrices->actions();

    for(int i=0;i<actions.count();i++){
        if(actions.at(i)->isEnabled() == false){
            actions.at(i)->setEnabled(true);
        }
    }

    actions = ui->menuVer->actions();

    for(int i=0;i<actions.count();i++){
        if(actions.at(i)->isEnabled() == false){
            actions.at(i)->setEnabled(true);
        }
    }


    ui->base->setCurrentIndex(1);
    ui->arbol->setVisible(true);



    CrearAreaOperaciones();



    ui->actionPegar->setEnabled(this->pegar);
}


void MainWindow::on_actionNuevo_Proyecto_triggered(){
    NuevoProyecto n(this);

    n.setEstado(true);

    n.exec();

    if(n.GetOk()){


//        this->m.clear();
//        this->vM.clear();

//        ui->baseMatrices->clear();



        CrearMatriz(n.getFilas(),n.getColumnas(),n.getNombreMatriz());

        this->ArbolMatrices->setExpanded(true);

        ui->nombreProyecto->setText(n.getNombreProyecto());
        this->ruta = n.getRuta()+n.getNombreProyecto();

        // crear proyecto


        QFile a(this->ruta);

        if(a.exists()){

            QDir proyecto(this->ruta);

            proyecto.mkpath(this->ruta+"/"+n.getNombreMatriz());
            //proyecto.mkpath("Matrices");
        }
        else{

        }




        Inicio();



            if(n.LlenarDe1()){
                for(int i=0;i<m.at(0)->getFilas();i++){
                    for(int j=0;j<m.at(0)->getColumnas();j++){
                        vM.at(0)->setValor(i,j,"1");
                    }
                }
            }
            else if(n.LlenarDe()){
                for(int i=0;i<m.at(0)->getFilas();i++){
                    for(int j=0;j<m.at(0)->getColumnas();j++){
                       vM.at(0)->setValor(i,j,QString::number(n.Valor()));
                    }
                }
            }
            else if(n.Aleatorio()){
                ui->li->setValue(n.Inferior());
                ui->ls->setValue(n.Superior());


                on_amarillo_clicked();
            }
            else if(n.MatrizIdentidad()){
                for(int i=0;i<m.at(0)->getFilas();i++){
                    for(int j=0;j<m.at(0)->getColumnas();j++){
                        if(i==j){
                            vM.at(0)->setValor(i,j,"1");
                        }
                        else{
                            vM.at(0)->setValor(i,j,"0");
                        }
                    }
                }
            }





    }


}


void MainWindow::on_editarNombreProyecto_clicked(){
    ui->lineEdit->setVisible(!ui->lineEdit->isVisible());
    ui->nombreProyecto->setVisible(!ui->nombreProyecto->isVisible());

    ui->lineEdit->setFocus();
}


void MainWindow::on_lineEdit_editingFinished(){
    ui->nombreProyecto->setVisible(true);
    ui->lineEdit->setVisible(false);

    if(!ui->lineEdit->text().isEmpty()){
        ui->nombreProyecto->setText(ui->lineEdit->text());
        ui->lineEdit->text().clear();
    }
}

void MainWindow::actionComun(int a){
    //ui->arbol->setVisible(false);
    ui->base->setCurrentIndex(2);
    ui->AreaOperaciones->setCurrentIndex(a);
}

void MainWindow::actionComun(int a, QWidget *w){
    ui->base->setCurrentIndex(2);
    ui->AreaOperaciones->setCurrentIndex(a);
}

void MainWindow::CrearMatriz(int f, int c, QString nombre){

    /*
       1. Crear El nuevo Objeto Matriz
       2. Darle nombre
       3. Pasarlo el viewMatriz
       4. Pasarlo al vector de Matrices
       5. Pasarlo al arbol
    */


    Matriz *nuevaMatriz = new Matriz(f,c);

    nuevaMatriz->setNombre(nombre.toStdString());


    viewMatriz *v = new viewMatriz();


    v->Crear(nuevaMatriz);



    // aqui

    this->m.push_back(nuevaMatriz);

    vM.append(v);

    ui->baseMatrices->addTab(v,nombre);
    ui->baseMatrices->setCurrentIndex(ui->baseMatrices->children().size());

    ui->filas->setValue(f);
    ui->columnas->setValue(c);

    QTreeWidgetItem *s = new QTreeWidgetItem(this->ArbolMatrices);

    s->setText(0,nombre);
    s->setIcon(0,QIcon(":/new/prefix1/iconos/matriz3.png"));

    // conectar a MenuMatrices

    ui->nMatrices->setText("# Matrices: "+QString::number(this->m.size()));





}


// actions

void MainWindow::on_pushButton_11_clicked(){
    ui->base->setCurrentIndex(1);
    ui->arbol->setVisible(true);
}



void MainWindow::CrearAreaOperaciones(){
    // Variables

    vm = new VariablesWidget();



    connect(this->menuVariables,&QMenu::triggered,[=](){
        ui->base->setCurrentIndex(2);
        ui->AreaOperaciones->setCurrentIndex(0);
    });



    vm->PasarInformacion(this->ArbolVariables);
    vm->CargarVariables();




    ui->AreaOperaciones->addTab(vm,QIcon(":/new/prefix1/iconos/variable.png"),"Variables");

    // Matrices

    MatricesWidget *mw = new MatricesWidget();

    ui->AreaOperaciones->addTab(mw,QIcon(":/new/prefix1/iconos/vMatrices.png"),"Matrices");

    // Funciones

    FuncionesWidget *fw = new FuncionesWidget();


    ui->AreaOperaciones->addTab(fw,QIcon(":/new/prefix1/iconos/funcion.png"),"Funciones");

    // Entre Matrices

    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/matriz3.png"),"Entre Matrices");


    // Entre Escalar


    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/x.png"),"Entre Escalar");

    // Matriz Global


    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/intersect.png"),"Matriz Global");

    // Trigonometria

    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/trigonometria.png"),"Trigonometria");

    // Estadistica


    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/probabilidad.png"),"Estadistica");

    // Graficas
    g = new Graficas();

    g->PasarArbolMatrices(this->ArbolMatrices);
    g->PasarItem(item);

    ui->AreaOperaciones->addTab(g,QIcon(":/new/prefix1/iconos/graficar.png"),"Graficas");

    // Inter/Extrapolacion

    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/extrapolar.png"),"Inter/Expolar");


    // Latex

    latex = new LaTex();



    ui->AreaOperaciones->addTab(latex,QIcon(":/new/prefix1/iconos/OIP.jpg"),"LaTex");

    // Extra

    ui->AreaOperaciones->addTab(new QTabWidget,QIcon(":/new/prefix1/iconos/extra.png"),"Extras");

}

void MainWindow::CrearImagen(QTreeWidgetItem *item){
    item->setExpanded(true);

    QTreeWidgetItem *nItem = new QTreeWidgetItem();

    nItem->setText(0,item->text(0));
    nItem->setIcon(0,QIcon(":/new/prefix1/iconos/galeria-de-fotos.png"));


    if(item->childCount() > 0){
        for(int i=0;i<item->childCount();i++){
            if(item->child(i)->text(0) == "Imagenes"){
                item->child(i)->addChild(nItem);
                return;
            }
        }

        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);
        PItem->setText(0,"Imagenes");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/imagenes.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
    else{
        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);
        PItem->setText(0,"Imagenes");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/imagenes.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
}


void MainWindow::on_actionVariables_triggered(){
    actionComun(0);
}

void MainWindow::on_actionMatrices_triggered(){
    actionComun(1);
}

void MainWindow::on_actionFunciones_triggered(){
    actionComun(2);
}

void MainWindow::on_actionEntre_Matrices_triggered(){
    actionComun(3);
}

void MainWindow::on_actionEntre_Escalar_triggered(){
    actionComun(4);
}

void MainWindow::on_actionMatriz_Global_triggered(){
    actionComun(5);
}

void MainWindow::on_actionTrigonometria_triggered(){
    actionComun(6);
}

void MainWindow::on_actionEstadistica_triggered(){
    actionComun(7);
}

void MainWindow::on_actionGraficar_triggered(){
   actionComun(8);
}

void MainWindow::on_actionExtrapolacion_triggered(){
    actionComun(9);
}

void MainWindow::on_actionLatex_triggered(){
    actionComun(10);
}

void MainWindow::on_actionExtras_triggered(){
    actionComun(11);
}

void MainWindow::on_actionAgregar_triggered(){
    NuevoProyecto n(this);

    n.setEstado(false);

    n.exec();

    if(n.GetOk()){
        CrearMatriz(n.getFilas(),n.getColumnas(),n.getNombreMatriz());

        int indice = ui->baseMatrices->count()-1;

        QFile a(this->ruta);

        if(a.exists()){

            QDir proyecto(this->ruta);

            proyecto.mkpath(this->ruta+"/"+n.getNombreMatriz());
            //proyecto.mkpath("Matrices");
        }
        else{

        }

        if(n.LlenarDe1()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                    vM.at(indice)->setValor(i,j,"1");
                }
            }
        }
        else if(n.LlenarDe()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                   vM.at(indice)->setValor(i,j,QString::number(n.Valor()));
                }
            }
        }
        else if(n.Aleatorio()){
            ui->li->setValue(n.Inferior());
            ui->ls->setValue(n.Superior());


            on_amarillo_clicked();
        }
        else if(n.MatrizIdentidad()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                    if(i==j){
                        vM.at(indice)->setValor(i,j,"1");
                    }
                    else{
                        vM.at(indice)->setValor(i,j,"0");
                    }
                }
            }
        }

        vM.at(indice)->setFont(n.Fuente());
        vM.at(indice)->setColor(n.Color());

        ui->baseMatrices->setCurrentIndex(ui->baseMatrices->count());
    }
}

void MainWindow::on_baseArbol_itemClicked(QTreeWidgetItem *item, int column){
    QString t = item->text(0);

    if(item->parent() == nullptr){
        if(item == this->ArbolVariables || item->parent() == this->ArbolVariables){
            ui->base->setCurrentIndex(2);
            ui->AreaOperaciones->setCurrentIndex(0);
        }
        else if(t == "Informacion"){
            ui->base->setCurrentIndex(3);
        }
        else if(t == "Historial"){
            ui->base->setCurrentIndex(4);
        }
        else if(t == "Configuraciones"){
            ui->base->setCurrentIndex(5);
        }
        else if(t == "Funciones"){
            ui->base->setCurrentIndex(2);
            ui->AreaOperaciones->setCurrentIndex(2);
        }
        else if(t == "Graficas"){
            ui->base->setCurrentIndex(2);
            ui->AreaOperaciones->setCurrentIndex(8);
        }
    }
    else{
        if(item == this->ArbolMatrices){
            ui->base->setCurrentIndex(1);
        }
        else if(item->parent() == this->ArbolVariables){
            ui->base->setCurrentIndex(2);
            ui->AreaOperaciones->setCurrentIndex(0);
        }
        else if(item->parent() == this->ArbolMatrices){
            ui->base->setCurrentIndex(1);
            ui->baseMatrices->setCurrentIndex(this->ArbolMatrices->indexOfChild(item));

        }
        else if(item->parent()->parent() == this->ArbolMatrices){
            ui->base->setCurrentIndex(6);
        }
    }

}

void MainWindow::on_baseMatrices_currentChanged(int index){

    int f = this->m.at(index)->getFilas();
    int c = this->m.at(index)->getColumnas();

    ui->filas->setValue(f);
    ui->columnas->setValue(c);
}


void MainWindow::on_filas_textChanged(const QString &arg1)
{
    int f = arg1.toInt();
    int i = ui->baseMatrices->currentIndex();

    if(this->m.at(i)->getFilas() != f ){

        this->m.at(i)->Redimencionar(f,this->m.at(i)->getColumnas());

        this->vM.at(i)->Redibujar(this->m.at(i));
    }
}


void MainWindow::on_columnas_textChanged(const QString &arg1){
    int c = arg1.toInt();
    int i = ui->baseMatrices->currentIndex();

    if(this->m.at(i)->getColumnas() != c ){

        this->m.at(i)->Redimencionar(this->m.at(i)->getFilas(),c);

        this->vM.at(i)->Redibujar(this->m.at(i));
    }
}

void MainWindow::InicioProceso(){
    ui->progressBar->setValue(0);

    ui->progressBar->setVisible(true);

    this->inicio = std::chrono::system_clock::now();

}

void MainWindow::Proceso(double a){
    double max = ui->progressBar->maximum();
    ui->progressBar->setValue(ui->progressBar->value()+(max/(a)));
}

void MainWindow::FinalProceso(){
    this->final = std::chrono::system_clock::now();
    this->duracion = this->final-this->inicio;

    ui->tiempo->setText(QString::number(this->duracion.count()));

    ui->progressBar->setVisible(false);
}



// Modificadores

void MainWindow::on_amarillo_clicked(){
        // aleatorios



    if(ui->li->value() < ui->ls->value()){
        InicioProceso();

        int indice = ui->baseMatrices->currentIndex();

        int f = this->m.at(indice)->getFilas();
        int c = this->m.at(indice)->getColumnas();

        for(int i=0;i<f;i++){
            for(int j=0;j<c;j++){
                int aux = ui->li->value() + rand()%(ui->ls->value());

                this->vM.at(indice)->setValor(i,j,QString::number(aux));

                Proceso(f*c);
            }
        }
        FinalProceso();
    }
    else{
        QMessageBox::information(this,"Generar Numeros Aleatorios","El Limite inferior debe de ser menor al Limite superior");
    }


}


void MainWindow::on_actionArbol_triggered()
{
    ui->arbol->setVisible(!ui->arbol->isVisible());
}


void MainWindow::on_actionBarra_de_Herramientas_triggered()
{
    ui->toolBar->setVisible(!ui->toolBar->isVisible());
    ui->funciones->setVisible(!ui->funciones->isVisible());
    ui->toolBar_2->setVisible(!ui->toolBar_2->isVisible());
}


void MainWindow::on_baseArbol_customContextMenuRequested(const QPoint &pos){
    if(ui->baseArbol->itemAt(pos) != nullptr){
        item = ui->baseArbol->itemAt(pos);

        if(item->parent() == nullptr){
            // no tiene padre, ArbolMatrices, ArbolVariables, etc
            if(item->text(0) == "Matrices"){
                 // carpeta matriz
                 menuCarpetaMatrices->exec(ui->baseArbol->mapToGlobal(pos));
            }
        }
        else{
            // son hijos de los anterioeres
            if (item->parent()->text(0) == "Matrices") {
                // es una matriz
                menuMatrices->exec(ui->baseArbol->mapToGlobal(pos));
            }
            else if(item->parent()->text(0) == "Codigo" || item->parent()->text(0) == "Imagenes" || item->parent()->text(0) == "Graficas"){
                // es una imagen o texto
                g->PasarItem(item);
                this->menuImagenes->exec(ui->baseArbol->mapToGlobal(pos));
            }
            else if(item->parent() == this->ArbolVariables){
                qDebug()<<item->parent()->text(0);
                // una variable
                this->menuVariables->exec(ui->baseArbol->mapToGlobal(pos));
            }
        }
    }
}

void MainWindow::on_baseMatrices_customContextMenuRequested(const QPoint &pos){
//    for(int i=0;i<ui->baseMatrices->count();i++){
//        if(ui->baseMatrices-){
//            menuMatrices->exec(ui->baseMatrices->mapToGlobal(pos));
//            break;
//        }
//    }
}
// Action MenuMatrices


void MainWindow::on_actionCopiar_triggered(){
    ui->actionPegar->setEnabled(true);
    ui->actionCopiar->setEnabled(false);
}

void MainWindow::on_actionPegar_triggered(){
    ui->actionPegar->setEnabled(false);
    ui->actionCopiar->setEnabled(true);
}

void MainWindow::on_AreaOperaciones_currentChanged(int index){
    if(index == 10){
        //latex

        QList<QTreeWidgetItem *> d;

        d << this->ArbolMatrices << this->ArbolVariables;

        this->latex->PasarDatos(d);



        this->latex->PasarMatrices(this->m);

    }
    else if(index == 8){
        g->PasarItem(item);
    }
}

void MainWindow::on_actionCrear_Imagen_triggered(){
   if(item->parent() == this->ArbolMatrices){
       CrearImagen(item);
   }
}


void MainWindow::on_actionRenombrar_Matrices_triggered(){



}

void MainWindow::on_actionRenombrar_triggered(){
    QLineEdit *lineEdit = new QLineEdit(ui->baseMatrices);

    lineEdit->setText(item->text(0));

    ui->baseArbol->setItemWidget(item,0,lineEdit);

    lineEdit->setFocus();

    QObject::connect(lineEdit, &QLineEdit::editingFinished, [=]() {

            if(!lineEdit->text().isEmpty()){
                item->setText(0, lineEdit->text());
            }


            ui->baseArbol->removeItemWidget(item, 0); // Eliminar el QLineEdit del árbol
            int i = this->ArbolMatrices->indexOfChild(item);

            ui->baseMatrices->setTabText(i,item->text(0));

            m.at(i)->setNombre(item->text(0).toStdString());
            delete lineEdit; // Eliminar el objeto QLineEdit de la memoria
    });




//    item->setFlags(item->flags() | Qt::ItemIsEditable);
//    //item->setData(0,Qt::EditRole,);

//    ui->baseArbol->update();
}


void MainWindow::on_actionRenombrar_2_triggered(){
    QLineEdit *lineEdit = new QLineEdit(ui->baseMatrices);

    lineEdit->setText(item->text(0));

    ui->baseArbol->setItemWidget(item,0,lineEdit);

    lineEdit->setFocus();

    QObject::connect(lineEdit, &QLineEdit::editingFinished, [=]() {

            if(!lineEdit->text().isEmpty()){
                item->setText(0, lineEdit->text());
            }


            ui->baseArbol->removeItemWidget(item, 0); // Eliminar el QLineEdit del árbol

            delete lineEdit; // Eliminar el objeto QLineEdit de la memoria
    });
}


void MainWindow::on_actionEliminar_triggered(){
//    int i = ui->baseArbol->indexOfTopLevelItem(item);

//    ui->baseMatrices->removeTab(i);
//    ui->baseArbol->removeItemWidget(item,0);
//    vM.remove(i);
//    m.erase(m.begin()+i);

}

void MainWindow::on_actionRenombrar_Etiquetas_triggered(){
    etiquetas *e = new etiquetas();

    e->exec();

    if(e->Cambio()){
        if(e->Automatico()){
            QString t = e->Caracter();
            int c = e->Incremento();

            int index = this->ArbolMatrices->indexOfChild(item);



            QStringList filas;
            QStringList columnas;

            for(int i=0;i<m.at(index)->getFilas();i++){
                filas.push_back(t+QString::number(c+i));
            }

            //qDebug()<<"Entro";

            for(int i=0;i<m.at(index)->getColumnas();i++){
                columnas.push_back(t+QString::number(c+i));
            }

//            qDebug()<<"Filas Automatico: "<<filas;
//            qDebug()<<"Columnas Automatico: "<<columnas;

            vM.at(index)->setHLabes(filas);
            vM.at(index)->setVLabes(columnas);
        }
        else{
            QString f,c;
            QString s = e->Separador();

            int index = this->ArbolMatrices->indexOfChild(item);

            f = e->Filas();
            c = e->Columnas();

            vM.at(index)->setHLabes(f.split(s));
            vM.at(index)->setVLabes(c.split(s));
        }
    }
}


void MainWindow::on_actionLaTex_triggered(){
    item->setExpanded(true);

    QTreeWidgetItem *nItem = new QTreeWidgetItem();

    nItem->setText(0,item->text(0));
    nItem->setIcon(0,QIcon(":/new/prefix1/iconos/OIP.jpg"));

    if(item->childCount() > 0){
        for(int i=0;i<item->childCount();i++){
            if(item->child(i)->text(0) == "Codigo"){
                item->child(i)->addChild(nItem);
                return;
            }
        }

        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);

        PItem->setText(0,"Codigo");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/texas.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
    else{
        QTreeWidgetItem *PItem = new QTreeWidgetItem();

        PItem->setExpanded(true);
        PItem->setText(0,"Codigo");
        PItem->setIcon(0,QIcon(":/new/prefix1/iconos/texas.png"));

        PItem->addChild(nItem);

        item->addChild(PItem);
    }
}


void MainWindow::on_actionAbrir_triggered(){
    if(item->parent()->text(0) == "Codigo"){
        qDebug()<<"Codigo";


    }
    else if(item->parent()->text(0) == "Imagenes"){
        qDebug()<<"Imagenes";


    }
}


void MainWindow::on_actionGuardar_triggered(){

    for(int i=0;i<this->vM.size();i++){
        this->vM.at(i)->GuardarMatriz(this->ruta);
    }

}

void MainWindow::on_actionImportar_triggered(){
    Importar *i = new Importar();

    i->exec();
}


void MainWindow::on_actionAgregar_Matriz_triggered(){
    NuevoProyecto n(this);

    n.setEstado(false);

    n.exec();

    if(n.GetOk()){
        CrearMatriz(n.getFilas(),n.getColumnas(),n.getNombreMatriz());

        int indice = ui->baseMatrices->count()-1;

        if(n.LlenarDe1()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                    vM.at(indice)->setValor(i,j,"1");
                }
            }
        }
        else if(n.LlenarDe()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                   vM.at(indice)->setValor(i,j,QString::number(n.Valor()));
                }
            }
        }
        else if(n.Aleatorio()){
            ui->li->setValue(n.Inferior());
            ui->ls->setValue(n.Superior());


            on_amarillo_clicked();
        }
        else if(n.MatrizIdentidad()){
            for(int i=0;i<m.at(indice)->getFilas();i++){
                for(int j=0;j<m.at(indice)->getColumnas();j++){
                    if(i==j){
                        vM.at(indice)->setValor(i,j,"1");
                    }
                    else{
                        vM.at(indice)->setValor(i,j,"0");
                    }
                }
            }
        }

        vM.at(indice)->setFont(n.Fuente());
        vM.at(indice)->setColor(n.Color());

        ui->baseMatrices->setCurrentIndex(ui->baseMatrices->count());
    }
}




void MainWindow::on_actionIntercambiar_triggered(){
    QStringList items;

    for(int i=0;i<ui->baseMatrices->count();i++){
        items.push_back(ui->baseMatrices->tabText(i));
    }

    QString t = QInputDialog::getItem(this,"Intercambiar Matriz","Elije una Matriz",items);

    if(t != item->text(0)){
        qDebug()<<"Intercambio";
    }
}




