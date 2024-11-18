// Representacion enlazada mediante nodos y punteros a siguientes nodos.
/*
OPERACIONES:
- AddVertice
- GetVertice
- SetVertice
- RemoveVertice
- GetCantidadLados
- GetPerimetro
*/

#include <iostream>
#include <math.h>
using namespace std;

struct Punto{
    double x;
    double y;
};

struct Nodo{
    Punto dato;
    Nodo *siguiente;
};

struct Poligono{
    Nodo *lista = NULL; 
};

//Prototipos
void addVertice(Poligono &, Punto); //recibe el 'Poligono' por referencia creado y el 'Punto' a agregar y devuelve nada (modifica el Poligono) 
Punto getVertice(Poligono,unsigned); //recibe el 'Poligono' creado y elemento de la lista(> 0) y devuelve el 'Punto' 
void setVertice(Poligono &, Punto, unsigned); // cambia el valor del punto indicado
void removeVertice(Poligono &, unsigned); //recibe el 'Poligono' por referencia creado y el 'Punto' a remover y devuelve nada (modifica el Poligono)
unsigned getCantidadLados(Poligono); // premisa, en un poligono simple y cerrado, la cantidad de vertices es igual a la cantidad de lados
double getPerimetro(Poligono); 


int main(){
    return 0;
}

//Implementaciones

// agregar un nodo al final de la lista
void addVertice(Poligono &pol, Punto coordenada){

    Nodo *nuevo_nodo = new Nodo;
    nuevo_nodo -> dato = coordenada;
    nuevo_nodo -> siguiente = NULL;         

    if(pol.lista == NULL){ 
        pol.lista = nuevo_nodo;
    } else{
        Nodo *actual = pol.lista;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual -> siguiente = nuevo_nodo;
    }
}

Punto getVertice(Poligono pol,unsigned n){
    
    Nodo *aux = pol.lista; 
    unsigned contador = 1;

    while(n != contador){
        aux = aux -> siguiente;
        contador++;
    } 

    return aux -> dato;
}

void setVertice(Poligono &pol, Punto coordenada, unsigned n){
    
    Nodo *aux = pol.lista;
    unsigned contador = 1;

    while(n != contador){
        aux = aux->siguiente;
        contador++;
    }
    aux -> dato = coordenada;
}

void removeVertice(Poligono &pol, unsigned n){
    
    Nodo *aux = pol.lista;
    Nodo *anterior = pol.lista;
    unsigned contador = 1;

    while(n != contador){
        anterior = aux;
        aux = aux -> siguiente;
        contador ++;
    }

    anterior -> siguiente = aux -> siguiente;
    delete aux;

}

unsigned getCantidadLados(Poligono pol){
    
    Nodo *aux = pol.lista;
    unsigned contador = 1;

    while(aux->siguiente != NULL){
        aux = aux -> siguiente;
        contador ++; 
    }
    return contador;
}

double getPerimetro(Poligono pol) {
    if (pol.lista == NULL) return 0.0; 

    Nodo *aux = pol.lista;
    Nodo *anterior = pol.lista;
    double distanciaAcumulada = 0.0;

    while (aux->siguiente != NULL) {
        anterior = aux;
        aux = aux->siguiente;
        distanciaAcumulada += sqrt(pow(aux->dato.x - anterior->dato.x, 2) + pow(aux->dato.y - anterior->dato.y, 2));  
    }

    // Cierra el polígono - Distancia de ultimo nodo a primero
    distanciaAcumulada += sqrt(pow(pol.lista->dato.x - aux->dato.x, 2) + pow(pol.lista->dato.y - aux->dato.y, 2));

    return distanciaAcumulada;
}
