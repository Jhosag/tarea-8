#include <iostream>
#include "Estudiante.h"

using namespace std;

int main() {
    string codigo, nombres, apellidos, direccion, fecha_nacimiento, telefono;
    int id_tipo_sangre = 0, id_estudiante = 0;
    int opcion = 0;

    Estudiante e;

    do {
        cout << "     Menu de Opciones   " << endl;
        cout << "************************" << endl;
        cout << "1. Crear estudiante" << endl;
        cout << "2. Leer estudiantes" << endl;
        cout << "3. Modificar estudiante" << endl;
        cout << "4. Borrar estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "************************" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        cout << endl;

        switch (opcion) {

        case 1: 
            cout << "    CREAR ESTUDIANTE    " << endl;
            cout << "************************" << endl;
            cout << "Ingrese el codigo: ";
            cin >> codigo;
            cin.ignore();
            cout << "Ingrese los nombres: ";
            getline(cin, nombres);
            cout << "Ingrese los apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese la direccion: ";
            getline(cin, direccion);
            cout << "Ingrese el telefono: ";
            getline(cin, telefono);
            cout << "Ingrese la fecha de nacimiento (AAAA-MM-DD): ";
            getline(cin, fecha_nacimiento);
            cout << "Ingrese el id del tipo de sangre: ";
            cin >> id_tipo_sangre;
            cin.ignore();

            e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, codigo, 0);
            e.crear();
            break;

        case 2: 
            e.leer();
            break;

        case 3:
            cout << "    MODIFICAR ESTUDIANTE    " << endl;
            cout << "************************" << endl;
            cout << "Ingrese el ID a modificar: ";
            cin >> id_estudiante;
            cin.ignore();
            cout << "Ingrese el nuevo codigo: ";
            cin >> codigo;
            cin.ignore();
            cout << "Ingrese los nombres: ";
            getline(cin, nombres);
            cout << "Ingrese los apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese la direccion: ";
            getline(cin, direccion);
            cout << "Ingrese el telefono: ";
            getline(cin, telefono);
            cout << "Ingrese la fecha de nacimiento (AAAA-MM-DD): ";
            getline(cin, fecha_nacimiento);
            cout << "Ingrese el id del tipo de sangre: ";
            cin >> id_tipo_sangre;
            cin.ignore();

            e.setId_estudiante(id_estudiante);
            e.setCodigo(codigo);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(telefono);
            e.setFecha_Nacimiento(fecha_nacimiento);
            e.setId_Tipo_Sangre(id_tipo_sangre);
            e.actualizar();
            break;

        case 4: 
            cout << "==============================" << endl;
            cout << "      BORRAR ESTUDIANTE       " << endl;
            cout << "==============================" << endl;
            cout << "Ingrese el ID a eliminar: ";
            cin >> id_estudiante;
            cin.ignore();
            if (e.buscarPorId(id_estudiante)) {
                cout << "Seguro que desea eliminar a: " << endl;
                e.mostrar();
                cout << "1. Si" << endl;
                cout << "2. No" << endl;
                cout << "Seleccione una opcion: ";
                int confirmar = 0;
                cin >> confirmar;
                cin.ignore();

                if (confirmar == 1) {
                    e.borrar();
                }
                else {
                    cout << "Eliminacion cancelada." << endl;
                }
            }
            break;
        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion invalida, intente de nuevo." << endl;
            break;
        }

        cout << endl;

    } while (opcion != 5);

    return 0;
}