#include <iostream>
#include "Individuo.h"
#include "Poblacion.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <string.h>

using namespace std;

int cantidadCiudades = 0;   //debe ser una variable global para que las demás clases puedan acceder a ella
int tamanioMatriz;

string leerTxt(){ //toma la informacion del txt, le da valor al atributo cantidadCiudades y regresa un string con la informacion

    ifstream archivoCiudades("kn57_dist.txt");
    string linea = "";
    int cantidadCiudades;
    string final="";
    int contador = 0;

    try{
        if (archivoCiudades.is_open())
        {
            while(!archivoCiudades.eof())
            {
                getline(archivoCiudades,linea);
                final.append(linea);
                final.append(" ");
            }
            archivoCiudades.close();
        }
    }catch(int e){
        cout<<"a";
    }

    return final;

}
vector<string> separarString (string txt){
    vector<string> resultado;
    string letra;
    string temp = "";

    while(txt.size() > 0){
        letra = txt[0];
        if((letra == " ") || (letra == "\n")){
            if(temp != ""){
                resultado.push_back(temp);
                temp="";
                txt.erase(txt.begin());
            }
            else{
                txt.erase(txt.begin());
            }
        }
        else{
            temp += txt[0];
            txt.erase(txt.begin());
            if(txt.size()==0){
                resultado.push_back(temp);
            }
        }
    }
    return resultado;
}

vector<vector<float> >  setMatrizCostos(vector<string> listaDistancias){//convierte la informacion que se ha leido del txt en una matriz

    cantidadCiudades = atoi(listaDistancias[0].c_str());
    listaDistancias.erase(listaDistancias.begin());
    vector<vector<float> >  matrizDistancias;
    matrizDistancias.resize(cantidadCiudades);

    for (int i = 0; i<cantidadCiudades; i++){   //para incializar el vector
        matrizDistancias[i].resize(cantidadCiudades);
    }

    int contador = 0;

    for(int i = 0; i<cantidadCiudades;i++){
        for (int j = 0; j<cantidadCiudades;j++){
            float numero = atof(listaDistancias.at(contador).c_str());
            if (numero == 0){
                matrizDistancias[i][j] = 100000;
                contador++;
            }else{
                matrizDistancias[i][j] = numero;
                contador++;
            }
        }
    }
    return matrizDistancias;
}

void imprimirMatriz(vector<vector<float> >  matriz){
    for(int i = 0; i<matriz.size();i++){
        for(int j = 0; j<matriz.size();j++){
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isNumber(const char* string){
    for (int i = 0; strlen(string); i++){
        if(!std::isdigit(string[i]) || *string == '-'){
			return false;
		}
    }
	return true;
}

int main(int argc, char** argv)
{
	
	if(argc <= 1){
		return 1;
	}
	
    srand(time(NULL));

    string txt = leerTxt();
    vector<string> txtSeparado = separarString(txt);
    vector<vector<float> >  matCosto = setMatrizCostos(txtSeparado);

    Poblacion test = Poblacion(cantidadCiudades, matCosto);
    test.setPoblacionInicial();
	
	int cantidadGeneraciones = atoi(argv[1]);
	cout<<"Cantidad De Generaciones: " << cantidadGeneraciones <<endl;
    cout<<"Por favor espere mientras se calculan las rutas "<<endl;
    //for (int i = 0; i<800; i++){
    for(int i = 0;i < cantidadGeneraciones;i++){
		if(argc == 3){
			cout <<"Generacion: "<<i <<endl;
		}
		if(argc == 3){
		test.verMejorIndividuo();
	}
		else{//si no, sólo imprime valores mínimos.
			test.imprimirMejorCosto();
		}
        test = test.evolucionar();
    }
	
	//si le llegan tres argumentos, entra en modo "verbose", lo cual hace que imprima todo
	cout <<"Poblacion Final-----------------------" <<endl;
	if(argc == 3){
		test.verMejorIndividuo();
	}
	else{//si no, sólo imprime valores mínimos.
		test.imprimirMejorCosto();
	}

    return 0;
}
