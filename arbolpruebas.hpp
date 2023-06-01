#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>
#include "lista.hpp"

using namespace std;

template <class T> class nodo {
public:
    T* info;
    nodo* der, * izq;
};

template <class T> class arbol {
private:
    nodo<T>* raiz, * q;
    void ArbolBusq(T x, nodo<T>*& nuevo);
    void show(nodo<T>* aux, int n); 
    void borrar(nodo<T>*& p, T x);
    void bor(nodo<T>*& d);
    void mh(nodo<T>* aux); 
    T menor(nodo<T>* aux); 
    bool esta(nodo<T>* aux, T x);
    void printMasVotado(nodo<T>*& p, T post);
    nodo<T>* buscarNodo(nodo<T>* aux, const T& objeto);
    int cantidadNodos(nodo<T>* aux);
    int sumaVotos(nodo<T>* aux);
   

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void AgregarPost(T x, int postId);
    void VerArbol() { show(raiz, 0); }
    void Borrar(T x) { borrar(raiz, x); }
    void MostrarHojas() { mh(raiz); }
    T Menor() { return menor(raiz); }
    bool Esta(T x) { return esta(raiz, x); }
    void AgregarComentario(T x, int postId, int comentarioId);
    void ImprimirComentarioMasVotado(T x){printMasVotado(raiz, x);}
    void Buscar(T x){buscarNodo(raiz, x);}
    void VotarUp(T x);
    void VotarDown(T x);
    void ValoracionPromedio(T x);
    void UsuarioMasParticipo(T x);
    void MostrarParticipaciones(string usuario);
    void llenarlista(nodo<T>* aux, Lista<T*>* lista, string usuario);

    void llenarlistausuarios(nodo<T>* aux, Lista<T*>* lista);

    
};


template <class T> void arbol<T>::AgregarPost(T x, int postId)
{   
   ArbolBusq(x, raiz);
}

template <class T> void arbol<T>::ArbolBusq(T x, nodo<T>*& nuevo)
{
    if (nuevo == NULL) {
        nuevo = new nodo<T>;
        nuevo->info = new T(x);
        nuevo->der = nuevo->izq = NULL;
    }
    if (x > *(nuevo->info)) ArbolBusq(x, nuevo->der); //aca le saque la estrllita a la x
    if (x < *(nuevo->info)) ArbolBusq(x, nuevo->izq); //aca le saque la estrllita a la x
}

/*
El metodo borrar busca y elimina un determinado post en el arbol de busqueda binaria.
Elimina tanto el nodo que contiene el post, como tambien todos sus comentarios asociados.
*/

template <class T> void arbol<T>::borrar(nodo<T>*& p, T post)
{
    if (p == NULL) {
        cout << "El post no existe." << endl;
        return;
    }
     if (*(p->info) < post) {
        borrar(p->der, post);
    } else { // Encontramos el post a borrar
        // Eliminar todos los comentarios en la rama izquierda del post
        bor(p->izq);

        // Ajustar el puntero del post anterior
        if (p->der != NULL) {
            q = p;
            p = p->der;
            delete q->info;
            delete q;
        } else {
            delete p->info;
            delete p;
            p = NULL;
        }
    }
}
/*
El metodo "bor" se encarga de eliminar todos los comentarios asociados a un post.
En nuestra implementacion lo usamos para eliminar comentarios, y comentarios a comentarios.
*/

template <class T> void arbol<T>::bor(nodo<T>*& d)
{
    if (d == NULL) return;

    if (d->der != NULL) {
        bor(d->der);
    } else {
        q = d;
        d = d->izq;
        delete q->info;
        delete q;
        q = NULL;
    }
}
/*
El metodo "esta" retorna true/false si se encuentra el parametro pasado a la funcion dentro del arbol.
*/

template <class T> bool arbol<T>::esta(nodo<T>* aux, T x)
{
    if (aux == NULL) return false;
    else if (x > *(aux->info)) return esta(aux->der, x);
    else if (x < *(aux->info)) return esta(aux->izq, x);
    return true;
}

/*
El metodo "show" muestra graficamente el contenido del arbol.
*/

template <class T> void arbol<T>::show(nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->info->getContenido() << "\n";
        show(aux->izq, n + 1);
    }
}

template <class T> void arbol<T>::mh(nodo<T>* aux)
{
    if (aux != NULL) {
        mh(aux->izq);
        if (aux->izq == NULL && aux->der == NULL)cout << "\n" << aux->info;
        mh(aux->der);
    }
}

template <class T> T arbol<T>::menor(nodo<T>* aux)
{
    if (aux->izq == NULL)return aux->info;
    return menor(aux->izq);
}

/*
El metodo "AgregarComentario" agrega un comentario a un post especifico.
parametros: x = objeto comentario a agg.
            postId = numero de post al que se añade el comentario
            comentarioId = si se quiere agregar un comentario a un comentario se pasa el valor del comentario
                            al cual se quiere responder. Caso contrario se pasa un valor que no se haya usado.
*/

template <class T> void arbol<T>::AgregarComentario(T x, int postId, int comentarioId)
{
    nodo<T>* aux = raiz;
    while (aux->info->getId() != postId) { //itero hasta llegar al post que busco
        aux = aux->der;
    }
    
    if(aux->izq == NULL){ //caso 1 no hay comentario 
    nodo<T>* comentario = new nodo<T>;
    comentario->info = new T(x);
    comentario->izq = NULL;
    comentario->der = NULL;
    aux->izq = comentario;
    return;
    } 
    
    if(aux->izq != NULL) {//caso 2 hay un comentario

    while(aux->izq != NULL && aux->info->getId() != comentarioId){
        aux = aux->izq;  
    }

    if(aux->info->getId() == comentarioId){
        //aux = aux->izq;

        while(aux->der != NULL){ //itera hasta llegar al nulo
            aux = aux->der;
        }

        if(aux->der == NULL){
            nodo<T>* comentario = new nodo<T>;
            comentario->info = new T(x);
            comentario->izq = NULL;
            comentario->der = NULL;
            aux->der = comentario;
            return;
        }
    }
    
    if(aux->info->getId() != comentarioId){
    nodo<T>* comentario = new nodo<T>;
    comentario->info = new T(x);
    comentario->izq = NULL;
    comentario->der = NULL;
    aux->izq = comentario; 
    
        }     
    }
}

/*
El metodo "printMasVotado" recorre todos los comentarios de un post especifico e imprime cual fue el comentario
mas votado y su informacion(usuario, cantVotos, ID).
El comentario mas votado puede ser un comentario, o un comentario a comentario.
*/

template <class T> void arbol<T>::printMasVotado(nodo<T>*& p, T post) 
{
    if (p == NULL) {
        cout << "El post no existe." << endl;
        return;
    }
    if (*(p->info) < post) {
        printMasVotado(p->der, post);
    } else {
            if (p->izq == NULL){
                cout<<"no tiene comentarios"<<endl;
                return;
            } 

            nodo<T>* nodoComent = p->izq;

            int maxVotos = 0;
            nodo<T>* comMaxVot = NULL;

                while (nodoComent != NULL){
                    //cout<<"aca izq"<<"    "<<nodoComent->info->getContenido()<<"  "<<nodoComent->info->getVotos()<<endl;

                    if (nodoComent->info->getVotos() > maxVotos) {
                        maxVotos = nodoComent->info->getVotos();
                        comMaxVot = nodoComent;
                        //cout<<"aca"<<endl;
                    }
                    
                    if (nodoComent->der != NULL){
                        nodo<T>* derComent = nodoComent->der;

                        while (derComent != NULL){
                            if (derComent->info->getVotos() > maxVotos){
                                maxVotos = derComent->info->getVotos();
                                comMaxVot = derComent;
                                //cout<<"aca der"<<endl;
                            }
                            derComent = derComent->der;
                        }   
                }

                nodoComent = nodoComent->izq;                 
            }        
            if (comMaxVot != NULL) {
            cout << "Comentario más votado:\n";
            cout << "Contenido: " << comMaxVot->info->getContenido() << endl;
            cout << "Votos: " << comMaxVot->info->getVotos() << endl;
            cout << "Usuario: " << comMaxVot->info->getNombre() << endl;
            cout << "ID: " << comMaxVot->info->getId() << endl;
        } else {
            cout << "No hay comentarios con votos." << endl;   
        }
    }
         
}

template <class T> nodo<T>* arbol<T>::buscarNodo(nodo<T>* aux, const T& objeto)
{
    if (aux == nullptr || *(aux->info) == objeto) {
        return aux;
    }

    nodo<T>* nodoIzquierdo = buscarNodo(aux->izq, objeto);
    if (nodoIzquierdo != nullptr) {
        return nodoIzquierdo;
    }

    nodo<T>* nodoDerecho = buscarNodo(aux->der, objeto);
    if (nodoDerecho != nullptr) {
        return nodoDerecho;
    }

    return nullptr; // Si no se encuentra el objeto en el árbol
}

template <class T> void arbol<T>::VotarUp(T x){
nodo<T>* uno = buscarNodo(raiz, x);
uno->info->votarUp();
}

template <class T> void arbol<T>::VotarDown(T x){
nodo<T>* uno = buscarNodo(raiz, x);
uno->info->votarDown();
}

template <class T> void arbol<T>::ValoracionPromedio(T x){
    nodo<T>* comentarios = buscarNodo(raiz, x);
    comentarios = comentarios->izq;
    int cantnodos = cantidadNodos(comentarios);
    int votostotales = sumaVotos(comentarios);
    cout<<"La valoracion promedio de los comentarios del post es: "<<votostotales/cantnodos<<endl;
}

template <class T> int arbol<T>::cantidadNodos(nodo<T>* aux) {
    if (aux == NULL) {
        return 0;
    }
    
    int contadorizq = cantidadNodos(aux->izq);    
    int contadorder = cantidadNodos(aux->der);   

    return 1 + contadorizq + contadorder;
}

template <class T> int arbol<T>::sumaVotos(nodo<T>* aux) {
    if (aux != NULL) {

        int sum = aux->info->getVotos(); 
        sum += sumaVotos(aux->der);
        sum += sumaVotos(aux->izq);

        return sum;
    }
    return 0;  
}

/*
El metodo "MostrarParticipaciones" devuelve el numero de interacciones que tuvo un "usuario"(parametro).
Crea una lista y almacena todos los contenidos de los comentarios que realizo en el arbol de post´s.
*/
template <class T> void arbol<T>::MostrarParticipaciones(string usuario){
Lista<T*>* participaciones = new Lista<T*>();
llenarlista(raiz, participaciones, usuario);
if(participaciones != NULL){
cout<<"el usuario: "<<participaciones->cabeza()->getNombre()<<" tuvo "<<participaciones->size()<<" participaciones"<<endl;
participaciones->ordenamientoInsercion();
cout<<participaciones->toPrint(".")<<endl;
}
}

/*
El metodo "llenarlista" almacena en la lista pasada como parametro todos los contenidos de los comentarios
realizados por "usuario" dentro del arbol de post´s.
*/

template <class T> void arbol<T>::llenarlista(nodo<T>* aux, Lista<T*>* lista, string usuario){
    if (aux != NULL) {
        if(!aux->info->esPost() && aux->info->getNombre() == usuario){lista->add(aux->info);}                   
        llenarlista(aux->der, lista, usuario);
        llenarlista(aux->izq, lista, usuario);
    }
}

/*

*/

template <class T> void arbol<T>::llenarlistausuarios(nodo<T>* aux, Lista<T*>* lista){
    if (aux != NULL) {
        lista->add(aux->info);
        llenarlistausuarios(aux->der, lista);
        llenarlistausuarios(aux->izq, lista);
    }
} 


/*
El metodo "UsuarioMasParticipo" devuelve el usuario que mas participaciones tuvo en un post.
Crea una lista de listas, que contiene en cada nodo una lista con las participaciones de cada
usuario, y devuelve el de mayor size con su informacion.
*/

template <class T>
void arbol<T>::UsuarioMasParticipo(T x) {
    nodo<T>* comentarios = buscarNodo(raiz, x); // Nodo que apunta a los comentarios del post
    Lista<T*>* listadeusuarios = new Lista<T*>();
    llenarlistausuarios(comentarios->izq, listadeusuarios);

    Lista<Lista<T*>*>* listadeListas = new Lista<Lista<T*>*>();

    // Iterar sobre la lista de usuarios y organizarlos en listas por nombre de usuario
    while (!listadeusuarios->esvacia()) {
        T* usuario = listadeusuarios->cabeza();
        listadeusuarios = listadeusuarios->resto();

        std::string nombreUsuario = usuario->getNombre();

        // Buscar la lista correspondiente al nombre del usuario en la lista de listas
        Lista<Lista<T*>*>* nodoLista = listadeListas;
        bool encontrada = false;
        while (!nodoLista->esvacia()) {
            Lista<T*>* listaActual = nodoLista->cabeza();
            nodoLista = nodoLista->resto();

            if (!listaActual->esvacia() && listaActual->cabeza()->getNombre() == nombreUsuario) {
                // Agregar el usuario a la lista actual
                listaActual->add(usuario);
                encontrada = true;
                break;
            }
        }

        if (!encontrada) {
            // Si no se encontró una lista existente para el nombre del usuario, crear una nueva lista
            Lista<T*>* nuevaLista = new Lista<T*>();
            nuevaLista->add(usuario);
            listadeListas->add(nuevaLista);
        }
    }

    // Buscar la lista de mayor tamaño dentro de la lista de listas
    int tamanoMaximo = 0;
    Lista<T*>* listaMayor = NULL;
    Lista<Lista<T*>*>* nodoLista = listadeListas;
    while (!nodoLista->esvacia()) {
        Lista<T*>* listaActual = nodoLista->cabeza();
        nodoLista = nodoLista->resto();

        int tamanoActual = listaActual->size();
        if (tamanoActual > tamanoMaximo) {
            tamanoMaximo = tamanoActual;
            listaMayor = listaActual;
        }
    }

    /*
    // Mostrar la lista de listas y su tamaño
    cout << "Lista de listas: " << listadeListas->toPrint(".") << endl;
    cout << "Tamaño de la lista de listas: " << listadeListas->size() << endl;
    */
    // Mostrar la lista de mayor tamaño
    cout << "Usuario con mas comentarios: ";
    if (listaMayor != NULL) {
        cout << listaMayor->cabeza()->getNombre();
    }
    cout << endl;
}



