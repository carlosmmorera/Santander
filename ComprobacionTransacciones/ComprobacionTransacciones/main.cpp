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
bool splitPuntoYComa(const string &l, vector<string> &v) {
	bool error = false;
	int ind = 0;
	v.push_back("");
	
	for (int i = 0; i < l.size(); ++i) {
		if (l[i] != ';') v[ind] += l[i];
		else {
			v.push_back("");
			++ind;
		}
	}

	return NUMCAMPOS != v.size();
}

//Comprueba que la cadena dada sea un entero
bool esEntero(const string &str) {
	if (str == "")
		return false;
	int i = 0;
	while (i < str.size() && isdigit(str[i]))
		++i;
	return i == str.size();
}

//Convierte la cadena dada en un entero
int strToInt(const string &str) {
	int pot = 1;
	int res = 0;
	for (int i = str.size() - 1; i >= 0; --i) {
		res += pot * (int(str[i] - '0'));
		pot *= 10;
	}
	return res;
}

//Comprueba que el mes de la línea sea el correcto
bool compruebaMes(const vector<string> &v, const int mes) {
	return esEntero(v[1]) && mes == strToInt(v[1]);
}

//Comprueba que la cadena dada sea un número real
bool esReal(const string &str) {
	string entera = "", decimal = "";
	int i = 0;
	while (i < str.size() && str[i] != '.') {
		entera += str[i];
		++i;
	}
	if (i == str.size() - 1)
		return false;
	++i;
	while (i < str.size()) {
		decimal += str[i];
		++i;
	}
	if (decimal == "")
		return esEntero(entera);
	else
		return esEntero(entera) && esEntero(decimal);
}

//Comprueba los gastos de la línea
bool compruebaGastos(const vector<string> &v) {
	return esReal(v[2]) && esReal(v[3]) && esReal(v[4]);
}

int main() {
	ifstream arch;
	arch.open("transaccional.txt");
	ofstream salida;
	salida.open("comprobacion.txt");
	
	if (arch.is_open() && salida.is_open()) {
		bool error = false;
		string linea = "";
		string user;
		int mes = 1, numErrores = 0;
		vector<string> v;

		for (int i = 0; i < NUMLINEAS; ++i) {
			getline(arch, linea);
			error = splitPuntoYComa(linea, v);
			
			if (!error) {
				if (mes == 1) user = v[0];
				else if (v[0] != user) {
					++numErrores;
					salida << numErrores << ".- User error in line: " << i + 1 << '\n';
				}

				error = !compruebaMes(v, mes);
				if (error) {
					++numErrores;
					salida << numErrores << ".- Month error in line: " << i + 1 << '\n';
				}
				if (mes < 12) ++mes;
				else mes = 1;
				
				error = !compruebaGastos(v);
				if (error) {
					++numErrores;
					salida << numErrores << ".- Expense error in line: " << i + 1 << '\n';
				}
				v.clear();
			}
			else {
				++numErrores;
				salida << numErrores << ".- Split error in line: " << i + 1 << '\n';
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