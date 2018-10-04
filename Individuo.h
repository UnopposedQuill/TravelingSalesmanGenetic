#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <vector>
#include <string>
using namespace std;
class Individuo
{
    public:
        Individuo(int pCantidad, int ciudadInicial, vector<vector<float> > pMatrizCostos);  //constructor
        float fitness;
        int cantidadCiudades;
        vector<int> rutaViaje;


        string stringConvert();
        float calcularCostoRuta(vector<vector<float> > pMatrizCostos);  //para el fitness
        Individuo mutar(Individuo original,vector<vector<float> >  matCosto);
        void verRuta();

        virtual ~Individuo();

    protected:

    private:
        void setRutaAleatoria(int ciudadInicial);

};

#endif // INDIVIDUO_H
