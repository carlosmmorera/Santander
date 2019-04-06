//Carlos Moreno Morera
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

const unsigned int NUMCAMPOS = 5;
const unsigned long int NUMLINEAS = 600000;

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

int main() {
	ifstream arch;
	arch.open("entrada.txt");

	if (arch.is_open()) {
		string linea = "";
		string user;
		vector<string> v;
		long double sum = 0;

		for (int i = 0; i < NUMLINEAS; ++i) {
			getline(arch, linea);
			splitPuntoYComa(linea, v);

			sum += stold(v[2]) + stold(v[3]) + stold(v[4]);

			cout << "Linea " << i + 1 << " procesada.\n";
		}
		arch.close();

		cout << "La media es: " << sum / 50000 << '\n';
		getline(cin, linea);
	}
	else cout << "Error en la apertura de los archivos\n";

	return 0;
}