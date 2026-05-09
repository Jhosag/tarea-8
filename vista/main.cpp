#include <iostream>
#include "Estudiante.h"

using namespace std;
int main()
{
	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;
	cout << "Ingrese el codigo: " << endl;
	cin >> codigo;
	cin.ignore();
	cout << "Ingrese los nombres: " << endl;
	getline(cin, nombres);
	cout << "Ingrese los apellidos: " << endl;
	getline(cin, apellidos);
	cout << "Ingrese la direccion: " << endl;
	getline(cin, direccion);
	cout << "Ingrese el telefono: " << endl;
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese la fecha de nacimiento: " << endl;
	getline(cin, fecha_nacimiento);
	cout << "Ingrese el id del tipo de sangre: " << endl;
	cin >> id_tipo_sangre;

	Estudiante e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, codigo, id_estudiante);
	e.crear();
	e.leer();
	
	//actualizar 
	cout << "Ingrese el ID a modificar: ";
	cin >> id_estudiante;
	cout << "Ingrese el codigo: " << endl;
	cin >> codigo;
	cin.ignore();
	cout << "Ingrese los nombres: " << endl;
	getline(cin, nombres);
	cout << "Ingrese los apellidos: " << endl;
	getline(cin, apellidos);
	cout << "Ingrese la direccion: " << endl;
	getline(cin, direccion);
	cout << "Ingrese el telefono: " << endl;
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese la fecha de nacimiento: " << endl;
	getline(cin, fecha_nacimiento);
	cout << "Ingrese el id del tipo de sangre: " << endl;
	cin >> id_tipo_sangre;

	e.setId_estudiante(id_estudiante);
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_Nacimiento(fecha_nacimiento);
	e.setId_Tipo_Sangre(id_tipo_sangre);
	e.actualizar();
	e.leer();

	cout << "Ingrese el ID a Eliminar: ";
	cin >> id_estudiante;
	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();

}
 