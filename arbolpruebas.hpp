#include <cstdlib>
#include <iostream>
#include <sstream>

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
    void rid(nodo<T>* aux);
    void ird(nodo<T>* aux);
    void idr(nodo<T>* aux); 
    void show(nodo<T>* aux, int n); 
    void borrar(nodo<T>*& p, T x);
    void bor(nodo<T>*& d);
    void mh(nodo<T>* aux); 
    T menor(nodo<T>* aux); 
    bool esta(nodo<T>* aux, T x);

    void printMasVotado(nodo<T>*& p, T post);

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void AgregarPost(T x, int postId);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
    void VerArbol() { show(raiz, 0); }
    void Borrar(T x) { borrar(raiz, x); }
    void MostrarHojas() { mh(raiz); }
    T Menor() { return menor(raiz); }
    bool Esta(T x) { return esta(raiz, x); }
    void AgregarComentario(T x, int postId, int comentarioId);
    void ImprimirComentarioMasVotado(T x){printMasVotado(raiz, x);}
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

template <class T> void arbol<T>::rid(nodo<T>* aux)
{
    if (aux != NULL) {
        cout << "\n" << *(aux->info);
        rid(aux->izq);
        rid(aux->der);
    }
}

template <class T> void arbol<T>::ird(nodo<T>* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << *(aux->info);
        ird(aux->der);
    }
}

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
template <class T> void arbol<T>::borrar(nodo<T>*& p, T x)
{
    if (p == NULL) cout << "\n El dato NO esta\n\n";
    else if (x > *(p->info)) borrar(p->der, x); //aca le saque la estrllita a la x
    else {
        if (x == *(p->info)) {

            cout<<p->info->getId()<<endl;
            p->izq = NULL;
            delete p->info;
        }
        
        
        
        
        // lo encontre en el nodo p
        q = p;
        if (q->der == NULL) p = q->izq;
        else if (q->izq == NULL) p = q->der;
        else bor(q->izq);
        delete q->info; // Elimina el objeto
        delete q; // Elimina el nodo

        
    }
}



template <class T> void arbol<T>::bor(nodo<T>*& d)
{
    if (d->der != NULL) bor(d->der);
    else {
        *(q->info) = *(d->info);
        q = d;
        d = d->izq;
        delete q->info; // Elimina el objeto
        delete q; // Elimina el nodo
    }
}
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

template <class T> bool arbol<T>::esta(nodo<T>* aux, T x)
{
    if (aux == NULL) return false;
    else if (x > *(aux->info)) return esta(aux->der, x);
    else if (x < *(aux->info)) return esta(aux->izq, x);
    return true;
}

template <class T> void arbol<T>::idr(nodo<T>* aux)
{
    if (aux != NULL) {
        idr(aux->izq);
        idr(aux->der);
        cout << "\n" << aux->info;
    }
}

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
        aux = aux->izq;

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
template <class T> void arbol<T>::ImprimirComentarioMasVotado(T x)
{
    nodo<T>* nodoPost = NULL;
    bool encontrado = BuscarPost(raiz, p, nodoPost);

    if (!encontrado) {
        cout << "El post no existe." << endl;
        return;
    }

    nodo<T>* aux = nodoPost->izq; // Comenzar desde el primer comentario en la rama izquierda
    int maxVotos = INT_MIN; // Inicializar el máximo de votos como el valor mínimo posible

    while (aux != NULL) {
        if (aux->info->getVotos() > maxVotos) {
            maxVotos = aux->info->getVotos();
        }
        aux = aux->izq;
    }

    if (maxVotos == INT_MIN) {
        cout << "El post no tiene comentarios." << endl;
        return;
    }

    // Buscar y imprimir el comentario más votado
    aux = nodoPost->izq;
    while (aux != NULL) {
        if (aux->info->getVotos() == maxVotos) {
            aux->info->imprimirContenido();
            break; // Encontramos el comentario más votado, salimos del bucle
        }
        aux = aux->izq;
    }

    // Verificar las respuestas a los comentarios en las ramas derechas
    aux = nodoPost->izq;
    while (aux != NULL) {
        if (aux->der != NULL) {
            ImprimirComentarioMasVotado(*aux->der->info);
        }
        aux = aux->izq;
    }
}*/


template <class T> void arbol<T>::printMasVotado(nodo<T>*& p, T post) //////////////ESSTA MIERDA NO ANDA AAAAAAAAAAAAAAAAAAAAAAAAAAAA
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
                } // hasta anda

                nodo<T>* auxComentariosPrincipales = p->izq; 
                
                string contenido; string usuario; int id;
                int maxVotos = 0; 
                
                while (auxComentariosPrincipales->izq != NULL){
                    
                        if(auxComentariosPrincipales->info->getVotos() > maxVotos){
                            maxVotos = auxComentariosPrincipales->info->getVotos();
                            contenido = auxComentariosPrincipales->info->getContenido();
                            usuario = auxComentariosPrincipales->info->getNombre();
                            id = auxComentariosPrincipales->info->getId();
                        }   auxComentariosPrincipales = auxComentariosPrincipales->izq;

                    }



                    if(auxComentariosPrincipales->info->getVotos() > maxVotos){
                            maxVotos = auxComentariosPrincipales->info->getVotos();
                            contenido = auxComentariosPrincipales->info->getContenido();
                            usuario = auxComentariosPrincipales->info->getNombre();
                            id = auxComentariosPrincipales->info->getId();
                        }
                    
                    cout<<maxVotos<<endl;
                    cout<<contenido<<endl;
        }           
}




