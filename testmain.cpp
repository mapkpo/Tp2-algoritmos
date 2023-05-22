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
comentario p0("comentador 0","coment del 1",0);

miArbol.CreaArbolBus(p1);
miArbol.CreaArbolBus(p2);
miArbol.CreaArbolBus(p3);
miArbol.CreaArbolBus(p0);  

miArbol.VerArbol();

p1.votarUp();

}