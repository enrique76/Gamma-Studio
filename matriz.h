#ifndef MATRIZ_H
#define MATRIZ_H

#include<stdlib.h>
#include<iostream>


using namespace std;

class Matriz{
    private:
        int filas;
        int columnas;
        double **matriz;
        string nombre;
        string descripcion; 
        double determinante;
    public:
        /// Constructores

        // constructor por defecto -> da dimenciones y valor de 0
        Matriz(int filas,int columnas){
            this->filas = filas;
            this->columnas = columnas;
            // Crear la matriz dinámicamente
            matriz = new double*[filas];
            for (int i = 0; i < filas; i++) {
                matriz[i] = new double[columnas];
            }

            // llenar valores 

            for(int i=0;i<this->filas;i++){
                for(int j=0;j<this->columnas;j++){
                    this->matriz[i][j] = 0;
                }
            }
        }

        Matriz(Matriz *m){
            this->filas = m->getFilas();
            this->columnas = m->getColumnas();
            // Crear la matriz dinámicamente
            matriz = new double*[filas];
            for (int i = 0; i < filas; i++) {
                matriz[i] = new double[columnas];
            }

            // llenar valores 

            for(int i=0;i<this->filas;i++){
                for(int j=0;j<this->columnas;j++){
                    this->matriz[i][j] = m->getValor(i,j);
                }
            }
        }

        ~Matriz(){
            for (int i = 0; i < filas; i++) {
                delete[] matriz[i];
            }
            delete[] matriz;
        }

        /// Metodos

        void Cambio(Matriz *m){
            this->filas = m->getFilas();
            this->columnas = m->getColumnas();
            // Crear la matriz dinámicamente
            matriz = new double*[filas];
            for (int i = 0; i < filas; i++) {
                matriz[i] = new double[columnas];
            }

            // llenar valores

            for(int i=0;i<this->filas;i++){
                for(int j=0;j<this->columnas;j++){
                    this->matriz[i][j] = m->getValor(i,j);
                }
            }
        }

        void CambiarValor(int fp,int cp, int fc, int cc){
            if((fp <= fc && fc <= this->filas) && (cp <= cc && cc <= this->columnas)){
                double aux = this->matriz[fp][cp];
                this->matriz[fp][cp] = this->matriz[fc][cc];
                this->matriz[fc][cc] = aux;
            }
        }

        void setNombre(string nombre){
            this->nombre = nombre;
        }

        string getNombre(){
            return this->nombre;
        }

        void setDescripcion(string descripcion){
            this->descripcion = descripcion;
        }

        string getDescripcion(){
            return this->descripcion;
        }

        int getFilas(){
            return this->filas;
        }

        int getColumnas(){
            return this->columnas;
        }

        double getValor(int fila,int columna){
            return this->matriz[fila][columna];
        }

        void setValor(int fila,int columna, double valor){
            this->matriz[fila][columna] = valor;
        }

        void Redimencionar(int f,int c){

                double** nuevaMatriz = new double*[f];
                for (int i = 0; i < f; i++) {
                    nuevaMatriz[i] = new double[c];
                }

                // pasar datos 
                for(int i = 0; i < f; i++) {
                    for(int j = 0; j < c; j++){
                        if(i >= this->filas || j >= this->columnas){
                            nuevaMatriz[i][j] = 0;
                        }
                        else{
                            nuevaMatriz[i][j] = this->matriz[i][j];
                        }
                    }
                }

                for (int i = 0; i < filas; i++) {
                    delete[] this->matriz[i];
                }
                delete[] this->matriz;

                this->matriz = nuevaMatriz;
                this->filas = f;
                this->columnas = c;

        
        }

          // operadores




        
};

#endif // MATRIZ_H
