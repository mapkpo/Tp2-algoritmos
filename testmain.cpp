#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>
#include "post.hpp"
#include "arbolpruebas.hpp"

using namespace std;

int main(){

arbol<post> miArbol;


post p1("Usuario1", "Contenido1", 1);
post p2("Usuario2", "Contenido2", 2);
post p3("Usuario3", "Contenido3", 3);

comentario c1("comentador 1","comentario 1",1);         //a que post lo quiero mandar es el id primero
comentario c2("comentador 2","comentario 2",2);
comentario c3("comentador 3","comentario 3",3);
comentario c4("comentador 4","comentario 4",4);
comentario c5("comentador 5","comentario 5",5);
comentario c6("comentador 6","comentario 6",6);

//primer lugar el objeto, 
//segundo lugar a cual post se quiere agregar


miArbol.AgregarPost(p1,1);
miArbol.AgregarPost(p2,2);
miArbol.AgregarPost(p3,3);



miArbol.AgregarComentario(c1,1,1);
miArbol.AgregarComentario(c2,2,2);
miArbol.AgregarComentario(c3,3,3);         //a que comentario quiero responder si es un numero nuevo se pone como comentario independiente en nueva rama izq
miArbol.AgregarComentario(c4,3,3);
miArbol.AgregarComentario(c5,3,3);
miArbol.AgregarComentario(c6,1,1);



miArbol.VerArbol();

system("pause");



}