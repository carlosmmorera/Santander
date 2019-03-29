#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

const int NUMUSER = 600000 / 12;
const int NUMLINEAS = 50000;

//Obtiene el nombre de usuario de la línea dada
string getUser(const string &linea) {
	int i = 0;
	string resultado = "";
	while (i < linea.size() && linea[i] != ';') {
		resultado += linea[i];
		++i;
	}
	return resultado;
}

int main() {
	ifstream tran, soc;
	ofstream salida;

	tran.open("transac.txt");
	soc.open("socialdemo.txt");
	salida.open("comprobacion.txt");

	if (tran.is_open() && soc.is_open() && salida.is_open()) {
		unordered_set<string> users;
		string aux;
		for (int i = 0; i < NUMUSER; ++i) {
			getline(tran, aux);
			aux = getUser(aux);
			cout << "Procesando usuario " << i << ".\n";
			if (users.find(aux) != users.end())
				salida << "Transacciones: Error con el usuario " << i << ", se encuentra repetido.\n";
			else
				users.insert(aux);
			for (int j = 0; j < 11; ++j)
				getline(tran, aux);
		}

		for (int i = 0; i < NUMLINEAS; ++i) {
			getline(soc, aux);
			aux = getUser(aux);
			cout << "Comprobando usuario " << i << ".\n";
			if (users.find(aux) == users.end())
				salida << "SocialDemo: Error con el usuario " << i << ", no se encuentra en el otro archivo.\n";
			else users.erase(aux);
		}

		if (users.size() > 0) {
			salida << "SocialDemo: Los siguientes usuarios no están en este archivo:\n";
			auto it = users.begin();
			while (it != users.end()) {
				salida << '-' << *it << '\n';
				++it;
			}
		}
		salida << "FIN DE LA COMPROBACION.\n";
	}
	else cout << "Error en la apertura de los archivos.";

	return 0;
}