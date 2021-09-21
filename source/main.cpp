#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <chrono> 
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
typedef long long T;

struct cluster_vectors{	
	T cantidad_vec, dimensiones;
	vector<vector<T>> vector_cluster;
	T vec_filas;
	vector<T> vec_dimensiones;

	cluster_vectors(T vec_filas, vector<T> vec_dimensiones){
		this->vec_dimensiones = vec_dimensiones;
		this->vec_filas = vec_filas;
		cantidad_vec=this->vec_filas;
		for (size_t j = 0; j < vec_dimensiones.size(); j++){
			dimensiones = vec_dimensiones[j];
			vector_cluster.resize(vec_filas);
			rellenar(0, j,vector_cluster);
			imprimir();
		}

	}

	void rellenar(T i,T j,vector<vector<T>>& vec_vec){
		int chatarra;
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, 1000);
		for (size_t i = 0; i < cantidad_vec; i++){
			vec_vec[i].resize(dimensiones);
			for (size_t j = 0; j < dimensiones; j++){
				vec_vec[i][j] = distrib(gen);
				//cout<<vec_vec[i][j]<<" ";
			}
			//cout<<endl;
			//cin>>chatarra;
		}
	}

	double distancia_euclides(vector<T> vec_1, vector<T> vec_2){
		T total = 0;
		for (size_t i = 0; i < vec_1.size(); i++){
			total += pow(vec_2[i] - vec_1[i], 2);
		}
		return sqrt(total);
	}
	
	void imprimir(){
        map<string,int> prob_numbers;
		vector<double> max_min;
		double distance_tmp,min,max;
		string set_decimals;
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
		start = chrono::high_resolution_clock::now();

		cout << "Cantidad de Datos: " << cantidad_vec << endl;
		cout << "Dimension de Vectores: " << dimensiones << endl;
		for (size_t i = 1; i < cantidad_vec; i++){
				distance_tmp=distancia_euclides(vector_cluster[i], vector_cluster[0]);
				max_min.push_back(distance_tmp);
		}

		sort(max_min.begin(),max_min.end()); // min y max para el rango 0 a 1
		min=max_min[0];
		max=max_min[max_min.size()-1];

		for(size_t j=0;j<max_min.size();j++){
			distance_tmp=(max_min[j]-min)/(max-min);
			set_decimals=to_string(distance_tmp);
			set_decimals=set_decimals.substr(0,set_decimals.find('.')+2); //truncar decimales a 1
			prob_numbers[set_decimals]++;			//se suman distancias iguales
		}

		//fin de ejecucion
		end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Tiempo tomado: " << duration.count() << " microsegundos" << endl<<endl;
		

		//datos para el file
		ofstream file;
		file.open("datos"+to_string(dimensiones)+".txt");
		for(map<string,int>::iterator it=prob_numbers.begin();it!=prob_numbers.end();it++){
			file<< it->first +"\t"+ to_string(it->second)+"\n";

		}
		
	}
};


int main(){   
    vector<T> dimensiones{ 2,5,10,15,20,25};
	T cantidad_vec = 200000;
	cluster_vectors task(cantidad_vec, dimensiones);
	return 0;
}