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

post p1("Ramiro D", "Ramiro D: No entendi AVL", 1 , "post 1");
post p2("gustavo W", "Gustavo W: Consigna parcial 2", 2 , "post 2");

//a que post lo quiero mandar es el id primero

comentario c1("Ruben A","Ruben A: En realidad es...",1);         
comentario c2("Pablo G","Pablo G: Revisa en el aula virtual...",2);
comentario c3("Gustavo W","Gustavo W: Estoy de acuerdo con vos Pablo",3);
comentario c4("Pablo G","Pablo G: Esta dificil?",4);
comentario c5("Ruben A","Ruben A: Deberiamos...",5);
comentario c6("Ramiro D","Ramiro D: Tengamos en cuenta que...",6);
comentario c7("Ramiro D","esto es un comentario",10);
comentario c8("Ramiro D","esto es un comentario",11);
comentario c9("Ramiro D","esto es un comentario",12);
comentario c10("Ramiro D","esto es un comentario",13);
comentario c11("Ramiro D","esto es un comentario",14);
comentario c12("Ramiro D","esto es un comentario a comentario",15);
comentario c13("Ramiro D","esto es un comentario a comentario",16);
comentario c14("Ramiro D","esto es un comentario a comentario",17);


/* 
Primero el objeto, 
segundo lugar a cual post se quiere agregar 
*/

miArbol.AgregarPost(p1,1);
miArbol.AgregarPost(p2,2);

/* 
Primero el objeto comentario, luego a que post quiero agregarlo 
y ultimo a que comentario quiero ponerlo como respuesta sino un numero 
que no se haya usado para ser un comentario nuevo al post y no respuesta
*/

miArbol.AgregarComentario(c1,1,1);
miArbol.AgregarComentario(c2,1,2);
miArbol.AgregarComentario(c3,1,2);         
miArbol.AgregarComentario(c4,2,7);
miArbol.AgregarComentario(c5,2,8);
miArbol.AgregarComentario(c6,2,9);
miArbol.AgregarComentario(c7,1,10);
miArbol.AgregarComentario(c8,1,11);
miArbol.AgregarComentario(c9,1,12);
miArbol.AgregarComentario(c10,1,13);
miArbol.AgregarComentario(c11,1,14);
miArbol.AgregarComentario(c12,1,10);
miArbol.AgregarComentario(c13,1,13);
miArbol.AgregarComentario(c12,2,4);
miArbol.AgregarComentario(c13,2,5);
miArbol.AgregarComentario(c14,2,6);


cout<<"-------------------el arbol normal------------------------------"<< endl;
cout<<"\n"<< endl;

miArbol.VerArbol();

cout<<"\n"<< endl;
cout<<"----------------------------------------------------------------"<< endl;


for(int i=0; i<4; i++){
    miArbol.VotarUp(p1);
}

for(int i=0; i<15; i++){
    miArbol.VotarUp(c1);
}

for(int i=0; i<76; i++){
    miArbol.VotarDown(p2);
}

for(int i=0; i<155; i++){
    miArbol.VotarUp(c4);
}

for(int i=0; i<25; i++){
    miArbol.VotarUp(c3);
}

for(int i=0; i<3; i++){
    miArbol.VotarUp(c5);
}

for(int i=0; i<12; i++){
    miArbol.VotarDown(c6);
}

miArbol.ImprimirComentarioMasVotado(p1);


cout<<"----------------------------------------------------------------"<< endl;


miArbol.ValoracionPromedio(p1);


cout<<"----------------------------------------------------------------"<< endl;


miArbol.MostrarParticipaciones("Ramiro D");


cout<<"----------------------------------------------------------------"<< endl;


miArbol.UsuarioMasParticipo(p1);


cout<<"----------------------------------------------------------------"<< endl;


//para borrar llamo al metodo con el post a borrar

miArbol.Borrar(p2);

cout<<"---------------ahora el arbol con el post 2 borrado-------------"<<endl;
cout<<"\n"<< endl;

miArbol.VerArbol();

system("pause");

}