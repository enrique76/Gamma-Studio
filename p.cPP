#include<iostream>
#include<windows.h>
#include "matriz.h"

using namespace std;

int main(){
    system("cls");

    // creamos matriz 2x2 llena de 0 
    Matriz m(2,2);

    // llenamos de otro valor 
    for(int i=0;i<m.getFilas();i++){
        for(int j=0;j<m.getColumnas();j++){
            m.setValor(i,j,1);
        }
    }

    cout<<"\n\n2x2 #1\n\n";
    
    //imprimimos el valor 
    for(int i=0;i<m.getFilas();i++){
        for(int j=0;j<m.getColumnas();j++){
            cout<<"  "<<m.getValor(i,j);
        }
        cout<<"\n\n";
    }

    // crecer matriz a 3x3 

    m.Redimencionar(3,3);

    // volver a imprimir 

    cout<<"\n\n3x3 #2 \n\n";

    

    for(int i=0;i<m.getFilas();i++){
        for(int j=0;j<m.getColumnas();j++){
            cout<<"  "<<m.getValor(i,j);
        }
        cout<<"\n\n";
    }

    // crecer matriz a 2x2 

    m.Redimencionar(2,3);

    // volver a imprimir 

    cout<<"\n\n2x3 #3\n\n";

    for(int i=0;i<m.getFilas();i++){
        for(int j=0;j<m.getColumnas();j++){
            cout<<"  "<<m.getValor(i,j);
        }
        cout<<"\n\n";
    }

    m.Redimencionar(3,3);

    m.CambiarValor(0,0,2,2);

    cout<<"\n\n3x3 #3\n\n";

    for(int i=0;i<m.getFilas();i++){
        for(int j=0;j<m.getColumnas();j++){
            cout<<"  "<<m.getValor(i,j);
        }
        cout<<"\n\n";
    }

    return 0;
}