#pragma once
#include <iostream>
#include <string>

class Persona{
	//Atributos
protected: std::string nombres, apellidos, direccion, fecha_nacimiento;
		 int telefono = 0, id_tipo_sangre = 0;
	//Constructor
		 Persona() {}
		 Persona(std::string nom, std::string ape, std::string dir, int tel, std::string fn, int id_ts) {
			 nombres = nom;
			 apellidos = ape;
			 direccion = dir;
			 telefono = tel;
			 fecha_nacimiento = fn;
			 id_tipo_sangre = id_ts;
		 }
};

