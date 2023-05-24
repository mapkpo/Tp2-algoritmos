#include <cstdlib>
#include <iostream>
#include <sstream>
#include <chrono>


using namespace std;

class post{
private:
    string nombre_usuario_creador;
    string titulo;
    string contenido;
    int votos;
    chrono::system_clock::time_point tiempo;
    int id;
    
public:
    post(string nombre, string contenido, int numero , string titulo){
        votos = 0;
        this->contenido = contenido;
        this->titulo = titulo; 
        nombre_usuario_creador = nombre;
        tiempo = chrono::system_clock::now();
        id = numero;    
    }

    bool operator<(const post& other) const {  //agrege los operadores
    return id < other.id;
    }

    bool operator>(const post& other) const {
    return id > other.id;
    }

    bool operator==(const post& other) const {
    return id == other.id;
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

    int getId() const{
        return id;
    }

    string getNombre(){
        return nombre_usuario_creador;
    }

};

class comentario : public post{

public:
    comentario(string nombre, string contenido, int numero) : post(nombre, contenido, numero, "comentario"){}

};