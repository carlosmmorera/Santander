//Carlos Moreno Morera
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

const unsigned int NUMCAMPOS = 5;
const unsigned long int NUMUSERS = 50000;
const long double MEDIA_GASTO = 5828.99;

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
double predictora(const double &r) {
	return r;
}

int main() {
	ifstream arch;
	arch.open("entrada.txt");
	ofstream salida;
	salida.open("salida.txt");

	if (arch.is_open() && salida.is_open()) {
		string linea = "";
		string user;
		vector<string> v;
		vector<vector<long double>> gastos(
		long double gasto;

		getline(arch, linea);
		salida << linea << '\n';

		for (int i = 0; i < NUMUSERS; ++i) {
			for (int j = 0; j < 12; ++j){
				getline(arch, linea);
			}
			getline(arch, linea);
			splitPuntoYComa(linea, v);
			user = v[0];

			salida << v[0] << ';' << v[1] << ';';
			for (int j = 2; j < NUMCAMPOS; ++j) {
				double r = stod(v[j]);
				salida << predictora(r);
				if (j != NUMCAMPOS - 1)
					salida << ';';
				else
					salida << '\n';
			}

			cout << "Linea " << i + 1 << " procesada.\n";
		}
		salida << "Se han procesado " << NUMLINEAS << " lineas.";
		arch.close();
		salida.close();
	}
	else cout << "Error en la apertura de los archivos\n";

	return 0;
}