#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTreeWidgetItem>
#include"matriz.h"
#include<QVector>
#include<vector>
#include"viewmatriz.h"
#include<chrono>
#include<QMenu>
#include"variableswidget.h"
#include<QPixmap>
#include"latex.h"
#include"graficas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Inicio();
    void actionComun(int a);
    void actionComun(int a, QWidget *w);
    void CrearMatriz(int f,int c,QString nombre);
    void InicioProceso();
    void Proceso(double);
    void FinalProceso();
    void CrearAreaOperaciones();
    void CrearImagen(QTreeWidgetItem *item);

private slots:
    void on_actionNuevo_Proyecto_triggered();
    void on_editarNombreProyecto_clicked();
    void on_lineEdit_editingFinished();
    void on_actionEntre_Matrices_triggered();
    void on_actionEntre_Escalar_triggered();
    void on_actionTrigonometria_triggered();
    void on_pushButton_11_clicked();
    void on_actionEstadistica_triggered();
    void on_actionExtrapolacion_triggered();
    void on_actionGraficar_triggered();
    void on_actionMatriz_Global_triggered();
    void on_actionLatex_triggered();
    void on_actionVariables_triggered();
    void on_actionFunciones_triggered();
    void on_actionMatrices_triggered();
    void on_actionExtras_triggered();
    void on_actionAgregar_triggered();
    void on_baseArbol_itemClicked(QTreeWidgetItem *item, int column);

    void on_baseMatrices_currentChanged(int index);

    void on_filas_textChanged(const QString &arg1);

    void on_columnas_textChanged(const QString &arg1);

    void on_amarillo_clicked();

    void on_actionArbol_triggered();

    void on_actionBarra_de_Herramientas_triggered();

    void on_baseArbol_customContextMenuRequested(const QPoint &pos);

    void on_actionCopiar_triggered();

    void on_actionPegar_triggered();

    void on_baseMatrices_customContextMenuRequested(const QPoint &pos);

    void on_AreaOperaciones_currentChanged(int index);

    void on_actionCrear_Imagen_triggered();

    void on_actionRenombrar_Matrices_triggered();

    void on_actionRenombrar_triggered();

    void on_actionRenombrar_2_triggered();

    void on_actionEliminar_triggered();

    void on_actionRenombrar_Etiquetas_triggered();

    void on_actionLaTex_triggered();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionImportar_triggered();

    void on_actionAgregar_Matriz_triggered();

    void on_actionIntercambiar_triggered();

public:
    Ui::MainWindow *ui;

    QTreeWidgetItem *ArbolMatrices = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolVariables = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolFunciones = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolGraficas = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolHistorial = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolInformacion = new QTreeWidgetItem();
    QTreeWidgetItem *ArbolConfiguraciones = new QTreeWidgetItem();
    vector<Matriz *> m;
    QVector<viewMatriz *> vM;
    std::chrono::system_clock::time_point inicio,final;
    std::chrono::duration<float> duracion;
    QString ruta;
    QTreeWidgetItem *item;
    bool pegar = false;
    QMenu *menuMatrices = new QMenu();
    QMenu *menuCarpetaMatrices = new QMenu();
    QMenu *menuVariables = new QMenu();
    QMenu *menuImagenes = new QMenu();

    QPixmap *p;


    QStringList listaVariables;

    // widgets

    VariablesWidget *vm;
    LaTex *latex;
    Graficas *g;


};
#endif // MAINWINDOW_H
