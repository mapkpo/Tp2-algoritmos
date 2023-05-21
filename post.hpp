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
    int id;

public:
    post(string nombre, string contenido, int numero){
        votos = 0;
        this->contenido = contenido;
        nombre_usuario_creador = nombre;
        tiempo = chrono::system_clock::now();
        id = numero;
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

    std::chrono::time_point<std::chrono::system_clock> getTiempo() const {
        return tiempo;
    }

    int getId(){
        return id;
    }

};

class comentario : public post{};