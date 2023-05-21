#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

class post{
private:
    string nombre_usuario_creador;
    string contenido;
    int votos;
    chrono::system_clock::time_point tiempo;

public:
    post(string nombre, string contenido){
        votos = 0;
        this->contenido = contenido;
        nombre_usuario_creador = nombre;
        tiempo = chrono::system_clock::now();
    }

    string getContenido(){
        return contenido;
    }

    void imprimirContenido(){
        cout<<contenido<<endl;
    }

    int getVotos(){
        return votos;
    }

    void votarUp(){
        votos += 1;
    }

    void votarDown(){
        votos -= 1;
    }
    
};