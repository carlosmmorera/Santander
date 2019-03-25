#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

struct tCliente { // Informacion completa del cliente.
    string id;
    string sexo;
    int edad;
    string paisResi;
    string paisNaci;
    string nivelEstudios;
    string idiomaPrefe;
    string tipoTrabajo;
    string oficinaMayorVol;
    string tipoEstadoCivil;
    string codPostal;
    string codProvincia;
    string codLocalidad;
    string codAutonomia;
    string codPais;
    string codINE;
    string segmento;
};

struct tGastoMes { // Tripleta con los gastos de un mes.
    double transferencia;
    double recibo;
    double tarjeta;
};

const int NUMMESES = 12;

struct tGastosCliente {
    string id; // id del cliente (repetido, pero aumenta claridad)
    vector<tGastoMes> gastosPorMes;
};

struct tTodosDatosCliente {
    string id; // id del cliente (repetido, pero aumenta claridad)
    tCliente cliente;
    tGastosCliente gastos;
};

const string INPUTSocioDemo = "inputSocioDemo.csv"; // Nombre del archivo de info clientes
const int NUMCLIENTES = 50000; // 50.000 clientes
const char DELIMITADOR = ';'; // Los campos se separan por comas.

const string INPUTTransaccional = "inputTransaccional.csv"; // Nombre del archivo de gastos.

// Leer el archivo de informacion social y demografica de los clientes:
vector<tCliente> leerDatosClientes();

// Lee un cliente del archivo entrada (para social-demografico):
tCliente leerCliente(ifstream & entrada);

// Crea la estructura total con todos los datos:
unordered_map<string, tTodosDatosCliente> crearDatosTotales(vector<tCliente> & datosClientes);

// Lee los 12 meses de gastos de un cliente:
tGastosCliente leerGastosCliente(ifstream & entrada);

// Busca secuencialmente un cliente, dado su id:
tCliente buscarCliente(const vector<tCliente> & datosClientes, const string & id);

int main() {
    vector<tCliente> datosClientes = leerDatosClientes();
    cout << "Leido el archivo con los datos de los clientes.\n";
    unordered_map<string, tTodosDatosCliente> datosTotales = crearDatosTotales(datosClientes);
    cout << "FINALIZADO. Presiona Enter para salir.";
    char aux; cin.get(aux);
    return 0;
}

vector<tCliente> leerDatosClientes() {
    ifstream entrada;
    entrada.open(INPUTSocioDemo);
    vector<tCliente> datosClientes(NUMCLIENTES);
    // La primera linea tiene los nombres de los campos, eliminarla:
    string aux;
    getline(entrada, aux);
    // Ahora, leer los NUMCLIENTES datos:
    for (int i = 0; i < NUMCLIENTES; ++i) {
        datosClientes[i] = leerCliente(entrada);
    }
    return datosClientes;
}

tCliente leerCliente(ifstream & entrada) {
    string linea;
    getline(entrada, linea);
    tCliente cliente;
    stringstream sslinea(linea);
    getline(sslinea, cliente.id, DELIMITADOR);
    getline(sslinea, cliente.sexo, DELIMITADOR);
    string aux; // Para leer el entero.
    getline(sslinea, aux, DELIMITADOR);
    cliente.edad = stoi(aux);
    getline(sslinea, cliente.paisResi, DELIMITADOR);
    getline(sslinea, cliente.paisNaci, DELIMITADOR);
    getline(sslinea, cliente.nivelEstudios, DELIMITADOR);
    getline(sslinea, cliente.idiomaPrefe, DELIMITADOR);
    getline(sslinea, cliente.tipoTrabajo, DELIMITADOR);
    getline(sslinea, cliente.oficinaMayorVol, DELIMITADOR);
    getline(sslinea, cliente.tipoEstadoCivil, DELIMITADOR);
    getline(sslinea, cliente.codPostal, DELIMITADOR);
    getline(sslinea, cliente.codProvincia, DELIMITADOR);
    getline(sslinea, cliente.codLocalidad, DELIMITADOR);
    getline(sslinea, cliente.codAutonomia, DELIMITADOR);
    getline(sslinea, cliente.codPais, DELIMITADOR);
    getline(sslinea, cliente.codINE, DELIMITADOR);
    getline(sslinea, cliente.segmento, DELIMITADOR);
    return cliente;
}

unordered_map<string, tTodosDatosCliente> crearDatosTotales(vector<tCliente> & datosClientes) {
    unordered_map<string, tTodosDatosCliente> sol;
    ifstream entrada;
    entrada.open(INPUTTransaccional);
    string aux; // Para leer la primera linea con los nombres de los campos.
    getline(entrada, aux);
    for (int i = 0; i < NUMCLIENTES; ++i) {
        tGastosCliente gastosCliente = leerGastosCliente(entrada);
        tTodosDatosCliente todosDatos;
        todosDatos.gastos = gastosCliente;
        todosDatos.id = gastosCliente.id;
        todosDatos.cliente = buscarCliente(datosClientes, gastosCliente.id);
        sol[gastosCliente.id] = todosDatos;
    }
    return sol;
}

tGastosCliente leerGastosCliente(ifstream & entrada) {
    tGastosCliente sol;
    string linea, auxId, auxInt, auxTransferencia, auxRecibo, auxTarjeta;
    getline(entrada, linea);
    stringstream sslinea(linea);
    getline(sslinea, sol.id, DELIMITADOR);
    double transferencia, recibo, tarjeta;
    getline(sslinea, auxInt, DELIMITADOR);
    getline(sslinea, auxTransferencia, DELIMITADOR);
    transferencia = stod(auxTransferencia);
    getline(sslinea, auxRecibo, DELIMITADOR);
    recibo = stod(auxRecibo);
    getline(sslinea, auxTarjeta, DELIMITADOR);
    tarjeta = stod(auxTarjeta);
    tGastoMes gastoMes;
    gastoMes.transferencia = transferencia;
    gastoMes.recibo = recibo;
    gastoMes.tarjeta = tarjeta;
    sol.gastosPorMes.push_back(tGastoMes()); // La posicion 0 NO VALE, para acceder al indice con el mes.
    sol.gastosPorMes.push_back(gastoMes);
    for (int i = 2; i <= 12; ++i) {
        getline(entrada, linea);
        stringstream sslinea(linea);
        getline(sslinea, auxId, DELIMITADOR);
        double transferencia, recibo, tarjeta;
        getline(sslinea, auxInt, DELIMITADOR);
        getline(sslinea, auxTransferencia, DELIMITADOR);
        transferencia = stod(auxTransferencia);
        getline(sslinea, auxRecibo, DELIMITADOR);
        recibo = stod(auxRecibo);
        getline(sslinea, auxTarjeta, DELIMITADOR);
        tarjeta = stod(auxTarjeta);
        tGastoMes gastoMes;
        gastoMes.transferencia = transferencia;
        gastoMes.recibo = recibo;
        gastoMes.tarjeta = tarjeta;
        sol.gastosPorMes.push_back(gastoMes);
    }
    return sol;
}

tCliente buscarCliente(const vector<tCliente> & datosClientes, const string & id) {
    int tam = datosClientes.size();
    for (int i = 0; i < tam; ++i) {
        if (datosClientes[i].id == id) return datosClientes[i];
    }
    return tCliente(); // Nunca deberia llegar aqui.
}