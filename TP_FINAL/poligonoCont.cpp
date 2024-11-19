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

//Mejoras implementadas//

//1. Validar en funciones getVertice, setVertice, removeVertice si el 'n' esta en el rango. 
//2. Modularizar el recorrido de las listas con la funcion 'extra' getNodo

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
void addVertice(Poligono &, Punto); 
Punto getVertice(Poligono &, unsigned);  
void setVertice(Poligono &, Punto, unsigned); 
void removeVertice(Poligono &, unsigned); 
unsigned getCantidadLados(Poligono); 
double getPerimetro(Poligono); 

Nodo *getNodo(Poligono &, unsigned); // funcion complementaria para recorrer listas

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

Punto getVertice(Poligono pol,unsigned n){ // ver cambiar pol pasado por valor a referencia constante 'Punto getVertice(const Poligono &pol,unsigned n)'

    unsigned cantidadVertices = getCantidadLados(pol); 

    // valido que el indice este en rango
    if(n>cantidadVertices || n<1){
        cout << "Error: indice fuera de rango." << endl;
        return;
    } else {
        Nodo *aux = pol.lista; 
        unsigned contador = 1;

        while(n != contador){
            aux = aux -> siguiente;
            contador++;
    } 
    return aux -> dato;
    }
}

void setVertice(Poligono &pol, Punto coordenada, unsigned n){
    
    unsigned cantidadVertices = getCantidadLados(pol);
    
    // valido que el indice este en rango
    if(n>cantidadVertices || n<1){
        cout << "Error: indice fuera de rango." << endl;
        return;

    } else{
        Nodo *aux = pol.lista;
        unsigned contador = 1;

        while(n != contador){
            aux = aux->siguiente;
            contador++;
        }
        aux -> dato = coordenada;
    }
}

void removeVertice(Poligono &pol, unsigned n){
    
    //valido si la lista esta vacia
    if(pol.lista == NULL){
        cout << "Error: el poligono esta vacio." << endl;
        return;
    }
    
    unsigned cantidadVertices = getCantidadLados(pol);
    
    // valido que el indice este en rango
    if(n>cantidadVertices || n<1){
        cout << "Error: indice fuera de rango." << endl;
        return;

    } else{
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

// Funcion complementaria
Nodo* getNodo(Poligono &pol, unsigned n) {
    Nodo *aux = pol.lista;
    unsigned contador = 1;

    while (aux != NULL && contador < n) {
        aux = aux->siguiente;
        contador++;
    }

    // Verificar si el índice solicitado coincide exactamente con el nodo
    if (contador == n) {
        return aux; // Nodo encontrado
    } else {
        return NULL; // Índice fuera de rango
    }
}
