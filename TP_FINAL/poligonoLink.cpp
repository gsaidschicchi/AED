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
#include <fstream>
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
void GenerarSVG(const Poligono &pol, const std::string &nombreArchivo);

Nodo *getNodo(Poligono &, unsigned); // funcion complementaria para recorrer listas

int main() {
    Poligono poligono;
    addVertice(poligono, {0, 0});
    addVertice(poligono, {100, 0});
    addVertice(poligono, {100, 100});
    addVertice(poligono, {0, 100});

    // Generar archivo SVG
    GenerarSVG(poligono, "poligono.svg");

    std::cout << "Archivo SVG generado: poligono.svg" << std::endl;
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
        Nodo *aux = pol.lista;
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux -> siguiente = nuevo_nodo;
    }
}

Punto getVertice(Poligono pol,unsigned n){ // ver cambiar pol pasado por valor a referencia constante 'Punto getVertice(const Poligono &pol,unsigned n)'

    unsigned cantidadVertices = getCantidadLados(pol); 

    // valido que el indice este en rango
    if(n>cantidadVertices || n<1){
        cout << "Error: indice fuera de rango." << endl;
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

#include <fstream>

void GenerarSVG(const Poligono &pol, const std::string &nombreArchivo) {
    const int TamanoCanvas = 1000;
    const int origen = TamanoCanvas / 2;

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir SVG." << std::endl;
        return;
    }

    archivo << "<svg width=\"" << TamanoCanvas << "\" height=\"" << TamanoCanvas
            << "\" viewBox=\"0 0 " << TamanoCanvas << " " << TamanoCanvas
            << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    const unsigned n = getCantidadLados(pol);

    // Graficar todos los puntos
    for (unsigned i = 0; i < n; i++) {
        Punto p = getVertice(pol, i);
        archivo << "  <circle cx=\"" << p.x + origen << "\" cy=\"" << origen - p.y
                << "\" r=\"4\" fill=\"black\" />" << std::endl;
    }

    // Unir los puntos
    for (unsigned i = 0; i < n - 1; i++) {
        Punto p1 = getVertice(pol, i);
        Punto p2 = getVertice(pol, i + 1);

        archivo << "  <line x1=\"" << p1.x + origen << "\" y1=\"" << origen - p1.y
                << "\" x2=\"" << p2.x + origen << "\" y2=\"" << origen - p2.y
                << "\" stroke=\"red\" stroke-width=\"2\" />" << std::endl;
    }

    // Unir el último punto con el primero
    if (n > 1) {
        Punto p1 = getVertice(pol, 0);
        Punto p2 = getVertice(pol, n - 1);
        archivo << "  <line x1=\"" << p1.x + origen << "\" y1=\"" << origen - p1.y
                << "\" x2=\"" << p2.x + origen << "\" y2=\"" << origen - p2.y
                << "\" stroke=\"red\" stroke-width=\"2\" />" << std::endl;
    }

    archivo << "</svg>" << std::endl;
    archivo.close();
}
