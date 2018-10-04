#include "Individuo.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

Individuo::Individuo(int pCantidad, int ciudadInicial, vector<vector<float> > pMatrizCostos)
{
    cantidadCiudades = pCantidad;
    setRutaAleatoria(ciudadInicial);
    fitness = calcularCostoRuta(pMatrizCostos);
}

void Individuo::setRutaAleatoria(int ciudadInicial){  // int cantidadCiudades
   vector<int> ruta;

   ruta.push_back(ciudadInicial);
   while (ruta.size()<this->cantidadCiudades){

        int randomNum = std::rand() % this->cantidadCiudades + 0;
        if(randomNum != ciudadInicial){

            if( std::find(ruta.begin(), ruta.end(), randomNum) != ruta.end()) {
                continue;
            } else {
                ruta.push_back(randomNum);
            }
        }
   }
   ruta.push_back(ciudadInicial);
   this->rutaViaje = ruta;
}

float Individuo::calcularCostoRuta(vector<vector<float> > pMatrizCostos){
    vector<int> ruta;
    ruta  = this->rutaViaje;
    float costoTotal;
    for (int i = 0; i<ruta.size()-1; i++){
        vector<float> origen = pMatrizCostos[ruta[i]];
        float destino = origen[ruta[i+1]];
        costoTotal += destino;
    }

    return costoTotal;

}

void imprimirVector(vector<int> lista){
    for(int i = 0; i<lista.size();i++){
        cout << lista[i] << "->";
    }
}



Individuo Individuo::mutar(Individuo original, vector<vector<float> >  matCosto){

    int cCiudades = original.cantidadCiudades;
    int cantidadMutacion = 5;

    for(int i = 1; i<=cantidadMutacion;i++){

        Individuo aux = original;
        vector<int> rutaTemp = aux.rutaViaje;

        int ciudad1 = std::rand() % (cCiudades-1) + 1;
        int ciudad2 = std::rand() % (cCiudades-1) + 1;
        while(ciudad1 == ciudad2){
            ciudad1 = std::rand() % (cCiudades-1) + 1;
            ciudad2 = std::rand() % (cCiudades-1) + 1;
        }

        int temp1 = rutaTemp[ciudad1];
        int temp2 = rutaTemp[ciudad2];


        rutaTemp[ciudad1] = temp2;   //donde se aplica la mutacion
        rutaTemp[ciudad2] = temp1;

        aux.rutaViaje = rutaTemp;
        aux.fitness = aux.calcularCostoRuta(matCosto);

        original = aux;


    }
    return original;



}

void Individuo::verRuta(){
    cout<<"\n";
    imprimirVector(rutaViaje);
    cout<<"\n";

}
string IntToString (int a)
{
    string str;
   ostringstream temp;
    temp<<a;
    return temp.str();
}


string stringConvert_Aux(vector<int> lista){
    string dato;

    for(int i = 0; i<lista.size();i++){
       dato = dato+IntToString(lista[i])+"->";
    }
    return dato;
}

string Individuo::stringConvert(){
    string str=stringConvert_Aux(rutaViaje);
    return str;
}






Individuo::~Individuo()
{
    //dtor
}
