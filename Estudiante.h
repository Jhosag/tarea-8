#pragma once
#include "Persona.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Estudiante : Persona {
private:string codigo;
	   int id_estudiante = 0;
public:
	Estudiante() {}
	Estudiante(string cod, string nom, string ape, string dir, string dob, int tel, int id_ts, int id_e) : Persona(nom, ape, dir, dob, tel, id_ts) {
		codigo = cod;
		id_estudiante = id_e;
	}
	//set
	void setID_Estudiante(int e) { id_estudiante = e; }
	void setCodigo(string c) { codigo = c; }
	void setNombres(string n) { nombres = n; }
	void setApellidos(string a) { apellidos = a; }
	void setDireccion(string d) { direccion = d; }
	void setFecha_Nacimiento(string f) { fecha_nacimiento = f; }
	void settelefono(int t) { telefono = t; }
	void setTipo_Sangre(int ts) { id_tipo_sangre = ts; }

	//get
	int getID_Estudiante() { return id_estudiante; }
	string getCodigo() { return codigo; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getDireccion() { return direccion; }
	string getFecha_Nacimiento() { return fecha_nacimiento; }
	int getTelefono() { return telefono; }
	int getTipo_Sangre() { return id_tipo_sangre; }


	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConnector()) {
			string t = to_string(telefono);
			string ts = to_string(id_tipo_sangre);
			string consulta = "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipo_sangre) VALUES('"+codigo+"','"+nombres+"','"+apellidos+"','"+direccion+"','"+t+"','" + fecha_nacimiento + "','" +ts+ "');";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConnector(), c);
			if (!q_estado) {
				cout << "___________Ingreso de datos exitoso____________" << endl;
			}
			else {
				cout << "___________Consulta Fallida____________" << endl;
			}

		}
		else {
			cout << "___________Error en la conexion____________" << endl;
		}
	}
	   void leer() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   MYSQL_ROW fila;
		   MYSQL_RES* resultado;
		   cn.abrir_conexion();
		   if (cn.getConnector()) {
			   cout << "___________Datos del Estudiante____________" << endl;
			   string consulta = "SELECT * FROM db_escuela.estudiantes;";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConnector(), c);
			   if (!q_estado) {
				   resultado = mysql_store_result(cn.getConnector());
				   while (fila = mysql_fetch_row(resultado)) {
					   cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << "," << fila[5] << "," << fila[6] << "," << fila[7] << endl;
				   }
			   }
			   else {
				   cout << "___________Error en la consulta____________" << endl;
			   }
		   }
		   else {
			   cout << "___________Error en la conexion____________" << endl;
		   }
		   cn.getConnector();
	   }
	   void actualizar() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   cn.abrir_conexion();
		   if (cn.getConnector()) {
			   string t = to_string(telefono);
			   string ts = to_string(id_tipo_sangre);
			   string id_e = to_string(id_estudiante);
			   string consulta = "UPDATE estudiantes SET codigo='" + codigo + "',nombres='" + nombres + "',apellidos='" + apellidos + "',direccion='" + direccion + "',telefono='" + t + "',fecha_nacimiento='" + fecha_nacimiento + "',id_tipo_sangre='" + ts + "' WHERE id_estudiante=" + id_e+";";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConnector(), c);
			   if (!q_estado) {
				   cout << "___________Actualizacion de datos exitoso____________" << endl;
			   }
			   else {
				   cout << "___________Consulta Fallida____________" << endl;
			   }
		   }
		   else {
			   cout << "___________Error en la conexion____________" << endl;
		   }
	   }
	   void borrar() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   cn.abrir_conexion();
		   if (cn.getConnector()) {
			   string t = to_string(telefono);
			   string ts = to_string(id_tipo_sangre);
			   string id_e = to_string(id_estudiante);
			   string consulta = "delete from estudiantes WHERE id_estudiante=" + id_e + "";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConnector(), c);
			   if (!q_estado) {
				   cout << "___________Eliminacion de datos exitoso____________" << endl;
			   }
			   else {
				   cout << "___________Eliminacion Fallida____________" << endl;
			   }
		   }
		   else {
			   cout << "___________Error en la conexion____________" << endl;
		   }
	   }
};

