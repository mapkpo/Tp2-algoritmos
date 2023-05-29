#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>
#include "post.hpp"
#include "arbolpruebas.hpp"
using namespace std;

int main(){

arbol<post> miArbol;

/* Forma de crear un post post p1("nombre del usuario" , "contenido" , numero del post , "titulo del post") */

post p1("Usuario1", "Contenido1", 1 , "post 1");
post p2("Usuario2", "Contenido2", 2 , "post 2");
post p3("Usuario3", "Contenido3", 3 , "post 3");

//a que post lo quiero mandar es el id primero

comentario c1("comentador 1","comentario 1",1);         
comentario c2("comentador 2","comentario 2",2);
comentario c3("comentador 1","comentario 3",3);
comentario c4("comentador 1","comentario 4",4);
comentario c5("comentador 2","comentario 5",5);
comentario c6("comentador 1","comentario 6",6);

/* 
Primero el objeto, 
segundo lugar a cual post se quiere agregar 
*/

miArbol.AgregarPost(p1,1);
miArbol.AgregarPost(p2,2);
miArbol.AgregarPost(p3,3);

/* 
Primero el objeto comentario, luego a que post quiero agregarlo 
y ultimo a que comentario quiero ponerlo como respuesta sino un numero 
que no se haya usado para ser un comentario nuevo al post y no respuesta
*/

miArbol.AgregarComentario(c6,3,1);
miArbol.AgregarComentario(c2,1,1);
miArbol.AgregarComentario(c3,3,1);         
miArbol.AgregarComentario(c4,3,1);
miArbol.AgregarComentario(c5,3,1);
miArbol.AgregarComentario(c1,1,1);

miArbol.VerArbol();



//para borrar llamo al metodo con el post a borrar

miArbol.Borrar(p2);

cout<<"-------------------------------------------"<<endl;

miArbol.VerArbol();

cout<<"-------------------------------------------"<<endl;

miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);
miArbol.VotarUp(c4);
miArbol.VotarUp(c5);
miArbol.VotarUp(c6);
miArbol.VotarUp(c1);

miArbol.ImprimirComentarioMasVotado(p3);

cout<<"-------------------------------------------"<<endl;

miArbol.ValoracionPromedio(p3);

cout<<"-------------------------------------------"<<endl;

miArbol.MostrarParticipaciones("comentador 1");

cout<<"-------------------------------------------"<<endl;

miArbol.UsuarioMasParticipo(p3);

//system("pause");



}