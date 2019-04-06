//Carlos Moreno Morera
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

const unsigned long int NUMUSERS = 50000;
const long double MEDIA_GASTO = 28561.8;

//Divide los elementos de la línea l separados por ';' y los introduce en un vector
void splitPuntoYComa(const string &l, vector<string> &v) {
	int ind = 0;
	v.push_back("");

	for (int i = 0; i < l.size(); ++i) {
		if (l[i] != ';') v[ind] += l[i];
		else {
			v.push_back("");
			++ind;
		}
	}
}

//Falta por hacer
double predictora(const double &factor, const double &x) {
	return factor * (1 + ((-1 / (x + (1 / 5.28))) + 5.28) / 100);
}

int main() {
	ifstream arch;
	arch.open("entrada.txt");
	ofstream salida;
	salida.open("salida.txt");

	if (arch.is_open() && salida.is_open()) {
		string linea = "";
		vector<string> v;
		vector<vector<long double>> gastos(12, vector<long double>(3));
		long double gasto = 0;

		getline(arch, linea);
		salida << linea << '\n';

		for (int i = 0; i < NUMUSERS; ++i) {
			gasto = 0;
			for (int j = 0; j < 12; ++j){
				getline(arch, linea);
				v.clear();
				splitPuntoYComa(linea, v);
				for (int k = 0; k < 3; ++k){
					gastos[j][k] = stold(v[2 + k]);
					gasto += gastos[j][k];
				}
			}
			gasto = gasto / MEDIA_GASTO;

			for (int j = 0; j < 12; ++j) {
				salida << v[0] << ';' << j + 1 << ';';
				for (int k = 0; k < 3; ++k) {
					salida << predictora(gastos[j][k], gasto);
					if (k != 2)
						salida << ';';
					else
						salida << '\n';
				}
			}
			cout << "Usuario " << i + 1 << " procesado.\n";
		}
		arch.close();
		salida.close();
	}
	else cout << "Error en la apertura de los archivos\n";

	return 0;
}