#ifndef POBLACION_H
#define POBLACION_H
#include "Individuo.h"
#include <vector>
#include <iostream>

using namespace std;

class Poblacion
{
    public:
        Poblacion(int pCantidad, vector<vector<float> > matCostos);
        int cantidadCiudades;
        vector<Individuo> individuos;  //lista con los miembros de esta poblacion
        vector<vector<float> > matrizDeCostos;

        void setPoblacionInicial();
        void mutar(); //hace uso del metodo mutar en Individuo, solo que este es para aplicar la mutacion a toda lo poblacion
        Individuo hacerCruce();
        Individuo cruce(Individuo padre, Individuo madre);
        void agregarIndividuo(Individuo a);
        Poblacion evolucionar();
        void verPoblacion();
        void verMejorIndividuo();
		void imprimirMejorCosto();
		
        virtual ~Poblacion();

    protected:
    private:
        void ordenarIndividuos(); //para que la población esté siempre ordenada, con lo que tengan un mejor fitness al principio
};

#endif // POBLACION_H
