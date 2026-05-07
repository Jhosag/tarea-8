#include <iostream>
#include "Estudiante.h"
using namespace std;
int main()
{
	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono=0, id_tipo_sangre=0, id_estudiante=0;
	cout << "Ingrese el codigo del estudiante: ";
	cin >> codigo;
	cin.ignore();
	cout << "Ingrese nombres del estudiante: ";
	getline(cin, nombres);
	cout << "Ingrese apellidos del estudiante: ";
	getline(cin, apellidos);
	cout << "Ingrese direccion del estudiante: ";
	getline(cin, direccion);
	cout << "Ingrese telefono del estudiante: ";
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese fecha de nacimiento del estudiante: ";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese tipo de sangre del estudiante: ";
	cin >> id_tipo_sangre;

	Estudiante e = Estudiante(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, id_estudiante);
	e.crear();
	e.leer();

	// Actualizacion
	cout << "Ingrese el ID a modificar:";
	cin >> id_estudiante;
	cout << "Ingrese Codigo:";
	cin >> codigo;
	cin.ignore();
	cout << "Ingres Nombres:";
	getline(cin, nombres);
	cout << "Ingres Apellidos:";
	getline(cin, apellidos);
	cout << "Ingres Direccion:";
	getline(cin, direccion);
	cout << "Ingrese Telefono:";
	cin >> telefono;
	cin.ignore();
	cout << "Ingres Fecha Nacimiento:";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre:";
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
	cout << "Ingrese el ID a Eliminar:";
	cin >> id_estudiante;
	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();
}

