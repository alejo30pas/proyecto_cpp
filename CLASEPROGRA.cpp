#include <iostream>
#include <locale>
#include <fstream>
using namespace std;

/* ===== ESTRUCTURAS ===== */

struct Cobertura {
    string zona;
    string distrito;
    string circuito;
};

struct Cliente {
    string nombre;
    string cedula;              // <<< NUEVO
    string linea;
    int minutosConsumidos;
    float factura;
    Cobertura cobertura;
};

/* ===== MODULO COBERTURA ===== */

void registrarCobertura(Cobertura coberturas[], int &nc) {
    cin.ignore();

    cout << "Zona: ";
    getline(cin, coberturas[nc].zona);

    cout << "Distrito: ";
    getline(cin, coberturas[nc].distrito);

    cout << "Circuito: ";
    getline(cin, coberturas[nc].circuito);

    nc++;
    cout << "\nCobertura registrada correctamente\n";
}

/* ===== GUARDAR CLIENTE EN CSV ===== */

void guardarClienteCSV(Cliente c) {
    ofstream archivo("CLIENTES.PROGRAMACION.csv", ios::app);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo CSV\n";
        return;
    }

    archivo << "Cedula:" << ";" << c.cedula << ";"
            << "Nombre:" << ";" << c.nombre << ";"
            << "Linea:" << ";" << c.linea << ";"
            << "Zona:" << ";" << c.cobertura.zona << ";"
            << "Distrito:" << ";" << c.cobertura.distrito << ";"
            << "Circuito:" << ";" << c.cobertura.circuito << ";"
            << "Minutos:" << ";" << c.minutosConsumidos << endl;

    archivo.close();
}

/* ===== MODULO CLIENTE POSPAGO ===== */

void registrarCliente(Cliente clientes[], int &n,
                      Cobertura coberturas[], int nc) {

    if (nc == 0) {
        cout << "No existen coberturas registradas\n";
        return;
    }

    cin.ignore();

    cout << "Cedula del cliente: ";      // <<< NUEVO
    getline(cin, clientes[n].cedula);

    cout << "Nombre del cliente: ";
    getline(cin, clientes[n].nombre);

    cout << "Numero de linea: ";
    getline(cin, clientes[n].linea);

    // ASIGNA AUTOMÁTICAMENTE LA ÚLTIMA COBERTURA
    clientes[n].cobertura = coberturas[nc - 1];

    cout << "Minutos consumidos: ";
    cin >> clientes[n].minutosConsumidos;

    clientes[n].factura = 0;

    // GUARDA EN ARCHIVO CSV
    guardarClienteCSV(clientes[n]);

    n++;

    cout << "\nCliente pospago registrado correctamente\n";
}

/* ===== MODULO FACTURACION ===== */

void facturarCliente(Cliente clientes[], int n) {
    string linea;
    bool encontrado = false;
    float tarifa = 0.15;

    cin.ignore();
    cout << "Ingrese numero de linea: ";
    getline(cin, linea);

    for (int i = 0; i < n; i++) {
        if (clientes[i].linea == linea) {

            float subtotal =
                clientes[i].minutosConsumidos * tarifa;
            float iva = subtotal * 0.15;
            clientes[i].factura = subtotal + iva;

            cout << "\nFACTURA POSPAGO\n";
            cout << "Cedula: " << clientes[i].cedula << endl;
            cout << "Cliente: " << clientes[i].nombre << endl;
            cout << "Linea: " << clientes[i].linea << endl;
            cout << "Zona: " << clientes[i].cobertura.zona << endl;
            cout << "Distrito: " << clientes[i].cobertura.distrito << endl;
            cout << "Circuito: " << clientes[i].cobertura.circuito << endl;
            cout << "Minutos: " << clientes[i].minutosConsumidos << endl;
            cout << "Subtotal: $" << subtotal << endl;
            cout << "IVA (15%): $" << iva << endl;
            cout << "Total a pagar: $" << clientes[i].factura << endl;

            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        cout << "Linea no encontrada\n";
}



void eliminarClienteCSV() {
    ifstream archivo("CLIENTES.PROGRAMACION.csv");
    ofstream temp("TEMP.csv");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de clientes\n";
        return;
    }

    string cedulaBuscada;
    string linea;
    bool eliminado = false;

    cin.ignore();
    cout << "Ingrese la cedula del cliente a eliminar: ";
    getline(cin, cedulaBuscada);

    while (getline(archivo, linea)) {
        // Si la línea contiene la cédula, NO se copia
        if (linea.find("Cedula;"+cedulaBuscada) != string::npos ||
            linea.find("Cedula:;" + cedulaBuscada) != string::npos) {
            eliminado = true;
        } else {
            temp << linea << endl;
        }
    }

    archivo.close();
    temp.close();

    remove("CLIENTES.PROGRAMACION.csv";
    rename("TEMP.csv", "CLIENTES.PROGRAMACION.csv");

    if (eliminado)
        cout << "\nCliente eliminado correctamente\n";
    else
        cout << "\nCedula no encontrada\n";
}








/* ===== MAIN ===== */

int main() {
    setlocale(LC_ALL, "Spanish");

    Cobertura coberturas[20];
    Cliente clientes[50];
    int nc = 0, n = 0;
    int opcion;

    do {
        cout << "\nEMPRESA TELEFONIA FIJA\n";
        cout << "1. Registrar cobertura\n";
        cout << "2. Registrar cliente pospago\n";
        cout << "3. Facturar cliente\n";
        cout << "4. Eliminar cliente por cedula.\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCobertura(coberturas, nc);
                break;
            case 2:
                registrarCliente(clientes, n, coberturas, nc);
                break;
            case 3:
                facturarCliente(clientes, n);
                break;
            case 4:
                eliminarClienteCSV();
                break;
            case 5:
            	cout << "\nSaliendo del sistema.\n";
            	break;
            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 5);

    return 0;
}
