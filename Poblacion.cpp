#include "Poblacion.h"
#include <algorithm>

#include <stdlib.h>
#include <time.h>


Poblacion::Poblacion(int pCantidad, vector<vector<float> > matCostos)
{
    cantidadCiudades = pCantidad;
    matrizDeCostos = matCostos;
}

void Poblacion::setPoblacionInicial(){

    int contador = 0;  //contador indica la cantidad de individuos que se le meten a la poblacion
    //con esto, la población inicial tendrá 100 rutas "diferentes", pero el numero lo podemos ir
    //cambiando según sea necesario

    while(contador<250){
       for (int j = 0; j<cantidadCiudades; j++){
            Individuo a = Individuo(cantidadCiudades, j, matrizDeCostos);
            individuos.push_back(a);
            contador++;
        }
    }
    ordenarIndividuos();
}

void Poblacion::ordenarIndividuos(){   //algoritmo de ordenamiento usado: shellsort
    int i, j, incremento;
    int n = individuos.size();
    for(incremento=n/2; incremento>0; incremento /= 2){
        for(i=incremento; i<n; i++){
            Individuo temp=individuos[i];
            for(j=i; j>=incremento; j -= incremento){
                if(temp.fitness < individuos[j-incremento].fitness)
                {
                    individuos[j] = individuos[j-incremento];
				}
                else
                {
					break;
				}
            }
            individuos[j] = temp;
        }
    }
}

void Poblacion::mutar(){

    for(int i = 0; i<individuos.size(); i++){
        int variableMutar = std::rand() % 100 + 1;
        if(variableMutar <= 70){
            Individuo temp = individuos[i];
            Individuo mutado = temp.mutar(temp, matrizDeCostos);
            individuos[i] = mutado;
        }
    }
    ordenarIndividuos();

}

void Poblacion::agregarIndividuo(Individuo a){
    individuos.push_back(a);
}

void Poblacion::verPoblacion(){
    for (int i = 0; i<individuos.size();i++){
        cout << "\nRuta:  ";
        Individuo temp = individuos[i];
        temp.verRuta();
        cout << "Fitness: " << temp.fitness << endl;
    }
}

Poblacion::~Poblacion()
{
    //dtor
}



void mostrarVector(vector<int> lista){
    for (int i=0; i<lista.size(); i++){
        cout<<lista[i]<<"->";
    }
}



bool buscaGenesRepetidos(vector<int> hijo, int dato){
    for (int i=0; i< hijo.size(); i++ ){
        if (hijo[i]= dato){
            return true;
        }
    }
    return false;
}

vector <int> intercambioGenetico_Aux(vector<int> padre, vector<int> madre){
    vector <int> hijo;
    for(int i = 0; i<padre.size(); i++){
        if (hijo.size()< padre.size()){
             if( std::find(hijo.begin(), hijo.end(), padre[i]) != hijo.end()) {
                	continue;
            } else {
                hijo.push_back(padre[i]);
            }
            if (hijo.size()== (padre.size()-1)){ // si es del tamaño del padre agrega ultimo elemento
                hijo.push_back(hijo[0]);
                return hijo;
            }
        }

        if (hijo.size()< padre.size()){
            if( std::find(hijo.begin(), hijo.end(), madre[i]) != hijo.end()) {
                continue;
            } else {
                 hijo.push_back(madre[i]);
            }

            if (hijo.size()== (padre.size()-1)){// si es del tamaño del padre agrega ultimo elemento
                hijo.push_back(hijo[0]);
                return hijo;
            }
        }
// si es del tamaño del padre agrega ultimo elemento
        if (hijo.size()== (padre.size()-1)){
            hijo.push_back(hijo[0]);
            return hijo;
        }
    }
    return hijo;
}

Individuo Poblacion::cruce(Individuo padre, Individuo madre){
     Individuo hijo =padre;
     vector<int> resultado = intercambioGenetico_Aux(padre.rutaViaje, madre.rutaViaje);
     hijo.rutaViaje = resultado;
     hijo.fitness = hijo.calcularCostoRuta(matrizDeCostos);
     return hijo;

}

Individuo Poblacion::hacerCruce(){
    vector<Individuo> vDerecho;
    vector<Individuo> vIzquierdo;
    int contador = int(individuos.size()/2);

    for(int i=0; i< contador; i++){
        vDerecho.push_back(individuos[i]);
    }

    for(int i=(contador+1);i<individuos.size(); i++){
        vIzquierdo.push_back(individuos[i]);
    }

    int radPadre= rand()% vIzquierdo.size()+0;
    int radMadre= rand()% vDerecho.size()+0;

    Individuo padre = vIzquierdo[radPadre];
    Individuo madre =vDerecho[radMadre];

    Individuo hijo= cruce(padre, madre);
    return hijo;
}

Poblacion Poblacion::evolucionar(){   //30% se va por elitismo, 70% se nace de los cruces

    Poblacion nueva = Poblacion(cantidadCiudades, matrizDeCostos);
    int elitismo = individuos.size()*0.301;  //calcula cuanto es el 30% de la poblacion

    for (int i = 0; i< elitismo; i++){
            Individuo temp = individuos[i];
            nueva.agregarIndividuo(temp);
    }

    int cruces = individuos.size()*0.701;
    for(int i = 0; i< cruces; i++){  //ciclo para agregar los individuos que resultaron de los cruces
            Individuo hijo = hacerCruce();
            nueva.agregarIndividuo(hijo);
    }

    nueva.ordenarIndividuos();
    mutar();
    return nueva;
}

void Poblacion::verMejorIndividuo(){  //imprime el orden en el que se visitan las ciudades y el costo de esa ruta
    cout<<"Mejor ruta encontrada:"<<endl;
    Individuo mejor = individuos[0];
    vector<int> ruta = mejor.rutaViaje;
    for (int i = 0; i<ruta.size()-1;i++){
            int ciudad1 = ruta[i]+1;
            int ciudad2 = ruta[i+1]+1;

            vector<float> origen = matrizDeCostos[ruta[i]];
            float destino = origen[ruta[i+1]];

            cout << ciudad1 << " -> " << ciudad2 << "  costo: " << destino << endl;

    }
    cout << "Costo de la mejor ruta encontrada: " << mejor.fitness <<endl;
}

void Poblacion::imprimirMejorCosto(){
	cout <<"Costo de la mejor ruta encontrada: " <<individuos[0].fitness <<endl;
}
