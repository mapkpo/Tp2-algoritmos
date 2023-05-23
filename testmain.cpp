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

comentario c1("comentador 1","comentario 1",1);         //a que post lo quiero mandar es el id
comentario c2("comentador 2","comentario 2",2);
comentario c3("comentador 3","comentario 3",3);
comentario c4("comentador 4","comentario 4",3);

//primer lugar el objeto, 
//segundo lugar a cual post se quiere agregar


miArbol.AgregarPost(p1,p1.getId());
miArbol.AgregarPost(p2,p2.getId());
miArbol.AgregarPost(p3,p3.getId());



miArbol.AgregarComentario(c1,c1.getId(),1);
miArbol.AgregarComentario(c2,c2.getId(),1);
miArbol.AgregarComentario(c3,c3.getId(),1);         //a que comentario quiero responder
miArbol.AgregarComentario(c4,c4.getId(),4);




miArbol.VerArbol();




}