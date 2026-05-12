#pragma once
#include "Persona.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <regex>
#include <ctime>

using namespace std;

class Estudiante : Persona {
private:
    string codigo;
    int id_estudiante = 0;
	//Validaciones
    bool ValidarCodigo(const string& cod) {
        if (cod.empty()) {
            cout << "Error: El codigo no puede estar vacio." << endl;
            return false;
        }
        regex pattern("^E[0-9]{3}$");
        if (!regex_match(cod, pattern)) {
            cout << "Error: Codigo invalido. Debe tener el formato E001, E002..." << endl;
            return false;
        }
        return true;
    }
    bool CodigoExiste(const string& cod) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (!cn.getConector()) {
            cout << "Error: No se pudo verificar duplicado debido a fallo de conexion." << endl;
            return false;
        }
        string consulta = "SELECT COUNT(*) FROM estudiantes WHERE codigo = '" + cod + "';";
        mysql_query(cn.getConector(), consulta.c_str());
        MYSQL_RES* resultado = mysql_store_result(cn.getConector());
        MYSQL_ROW fila = mysql_fetch_row(resultado);
        int count = stoi(fila[0]);
        mysql_free_result(resultado);
        cn.cerrar_conexion();
        if (count > 0) {
            cout << "Error: El codigo " << cod << " ya existe, ingrese uno diferente." << endl;
            return true;
        }
        return false;
    }
    bool CodigoValido(const string& cod) {
        if (!ValidarCodigo(cod)) return false;
        if (CodigoExiste(cod)) return false;
        return true;
    }

    bool ValidarNombres(const string& nom) {
        if (nom.empty()) {
            cout << "Error: El nombre no puede estar vacio." << endl;
            return false;
        }
        if (nom.length() > 60) {
            cout << "Error: El nombre no puede tener mas de 60 caracteres." << endl;
            return false;
        }
        regex patron("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
        if (!regex_match(nom, patron)) {
            cout << "Error: El nombre solo puede contener letras y espacios." << endl;
            return false;
        }
        return true;
    }
    bool ValidarApellidos(const string& ape) {
        if (ape.empty()) {
            cout << "Error: El apellido no puede estar vacio." << endl;
            return false;
        }
        if (ape.length() > 60) {
            cout << "Error: El apellido no puede tener mas de 60 caracteres." << endl;
            return false;
        }
        regex patron("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
        if (!regex_match(ape, patron)) {
            cout << "Error: El apellido solo puede contener letras y espacios." << endl;
            return false;
        }
        return true;
    }

    bool ValidarDireccion(const string& dir) {
        if (dir.empty()) {
            cout << "Error: La direccion no puede estar vacia." << endl;
            return false;
        }
        if (dir.length() > 100) {
            cout << "Error: La direccion no puede tener mas de 100 caracteres." << endl;
            return false;
        }
        regex patron("['\";\\-\\-\\/\\*=\\\\]");
        if (regex_search(dir, patron)) {
            cout << "Error: La direccion contiene caracteres no permitidos." << endl;
            return false;
        }
        return true;
    }

    bool ValidarTelefono(const string& tel) {
        if (tel.empty()) {
            cout << "Error: El telefono no puede estar vacio." << endl;
            return false;
        }
        regex patron("^[0-9]{8}$");
        if (!regex_match(tel, patron)) {
            cout << "Error: El telefono debe contener exactamente 8 digitos numericos." << endl;
            return false;
        }
        return true;
    }

    bool ValidarFechaNacimiento(const string& fecha) {
        if (fecha.empty()) {
            cout << "Error: La fecha de nacimiento no puede estar vacia." << endl;
            return false;
        }
        regex patron("^([0-9]{4})-([0-9]{2})-([0-9]{2})$");
        smatch match;
        if (!regex_match(fecha, match, patron)) {
            cout << "Error: La fecha debe tener el formato AAAA-MM-DD." << endl;
            return false;
        }
        int anio = stoi(match[1]);
        int mes = stoi(match[2]);
        int dia = stoi(match[3]);

        if (mes < 1 || mes > 12) {
            cout << "Error: El mes debe estar entre 01 y 12." << endl;
            return false;
        }
        if (dia < 1 || dia > 31) {
            cout << "Error: El dia debe estar entre 01 y 31." << endl;
            return false;
        }

        int dias_por_mes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
            dias_por_mes[1] = 29;

        if (dia > dias_por_mes[mes - 1]) {
            cout << "Error: El dia " << dia << " no es valido para el mes " << mes << "." << endl;
            return false;
        }

        time_t t = time(0);
        tm ahora;
        localtime_s(&ahora, &t);
        int anio_actual = ahora.tm_year + 1900;
        int mes_actual = ahora.tm_mon + 1;
        int dia_actual = ahora.tm_mday;

        if (anio > anio_actual ||
            (anio == anio_actual && mes > mes_actual) ||
            (anio == anio_actual && mes == mes_actual && dia > dia_actual)) {
            cout << "Error: La fecha de nacimiento no puede ser futura." << endl;
            return false;
        }
        return true;
    }

    bool ValidarTipoSangre(int id_ts) {
        if (id_ts <= 0) {
            cout << "Error: El id de tipo de sangre debe ser un numero positivo." << endl;
            return false;
        }
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (!cn.getConector()) {
            cout << "Error: No se pudo verificar el tipo de sangre, fallo la conexion." << endl;
            return false;
        }
        string consulta = "SELECT COUNT(*) FROM tipos_sangre WHERE id_tipo_sangre = " + to_string(id_ts) + ";";
        mysql_query(cn.getConector(), consulta.c_str());
        MYSQL_RES* resultado = mysql_store_result(cn.getConector());
        MYSQL_ROW fila = mysql_fetch_row(resultado);
        int count = stoi(fila[0]);
        mysql_free_result(resultado);
        cn.cerrar_conexion();
        if (count == 0) {
            cout << "Error: El tipo de sangre con id " << id_ts << " no existe en la base de datos." << endl;
            return false;
        }
        return true;
    }


    bool ValidarCampos() {
        if (codigo.empty()) {
            cout << "Error: El codigo es obligatorio." << endl;
            return false;
        }
        if (nombres.empty()) {
            cout << "Error: El nombre es obligatorio." << endl;
            return false;
        }
        if (apellidos.empty()) {
            cout << "Error: El apellido es obligatorio." << endl;
            return false;
        }
        if (direccion.empty()) {
            cout << "Error: La direccion es obligatoria." << endl;
            return false;
        }
        if (telefono == 0) {
            cout << "Error: El telefono es obligatorio." << endl;
            return false;
        }
        if (fecha_nacimiento.empty()) {
            cout << "Error: La fecha de nacimiento es obligatoria." << endl;
            return false;
        }
        if (id_tipo_sangre == 0) {
            cout << "Error: El tipo de sangre es obligatorio." << endl;
            return false;
        }
        return true;
    }

public:
    Estudiante() {}
    Estudiante(string nom, string ape, string dir, string tel, string fn, int id_ts, string cod, int id_e)
        : Persona(nom, ape, dir, 0, fn, id_ts) {
        if (ValidarCodigo(cod)) {
            codigo = cod;
        }
        else {
            codigo = "";
        }
        setTelefono(tel);
        id_estudiante = id_e;
    }

    // Setters
    void setId_estudiante(int e) { id_estudiante = e; }

    bool setCodigo(string c) {
        if (CodigoValido(c)) {
            codigo = c;
            return true;
        }
        return false;
    }

    bool setNombres(string n) {
        if (ValidarNombres(n)) {
            nombres = n;
            return true;
        }
        return false;
    }

    bool setApellidos(string a) {
        if (ValidarApellidos(a)) {
            apellidos = a;
            return true;
        }
        return false;
    }

    bool setDireccion(string d) {
        if (ValidarDireccion(d)) {
            direccion = d;
            return true;
        }
        return false;
    }

    bool setTelefono(string t) {
        if (ValidarTelefono(t)) {
            telefono = stoi(t);
            return true;
        }
        return false;
    }

    bool setFecha_Nacimiento(string f) {
        if (ValidarFechaNacimiento(f)) {
            fecha_nacimiento = f;
            return true;
        }
        return false;
    }

    bool setId_Tipo_Sangre(int ts) {
        if (ValidarTipoSangre(ts)) {
            id_tipo_sangre = ts;
            return true;
        }
        return false;
    }

    // Getters
    int getId_estudiante() { return id_estudiante; }
    string getCodigo() { return codigo; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return direccion; }
    int getTelefono() { return telefono; }
    string getFecha_Nacimiento() { return fecha_nacimiento; }
    int getId_Tipo_Sangre() { return id_tipo_sangre; }

    bool buscarPorId(int id) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (!cn.getConector()) {
            cout << "Error: Fallo la conexion." << endl;
            return false;
        }
        string consulta = "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, e.id_tipo_sangre FROM estudiantes as e WHERE e.id_estudiante = " + to_string(id) + ";";
        mysql_query(cn.getConector(), consulta.c_str());
        MYSQL_RES* resultado = mysql_store_result(cn.getConector());
        MYSQL_ROW fila = mysql_fetch_row(resultado);

        if (!fila) {
            cout << "Error: No se encontro un estudiante con el ID " << id << "." << endl;
            mysql_free_result(resultado);
            cn.cerrar_conexion();
            return false;
        }

        id_estudiante = stoi(fila[0]);
        codigo = fila[1];
        nombres = fila[2];
        apellidos = fila[3];
        direccion = fila[4];
        telefono = stoi(fila[5]);
        fecha_nacimiento = fila[6];
        id_tipo_sangre = stoi(fila[7]);

        mysql_free_result(resultado);
        cn.cerrar_conexion();
        return true;
    }

    void mostrar() {
        cout << "------------------------------" << endl;
        cout << "ID:               " << id_estudiante << endl;
        cout << "Codigo:           " << codigo << endl;
        cout << "Nombres:          " << nombres << endl;
        cout << "Apellidos:        " << apellidos << endl;
        cout << "Direccion:        " << direccion << endl;
        cout << "Telefono:         " << telefono << endl;
        cout << "Fecha nacimiento: " << fecha_nacimiento << endl;
        cout << "Id tipo sangre:   " << id_tipo_sangre << endl;
        cout << "------------------------------" << endl;
    }

    // CRUD
    void crear() {
        if (!ValidarCampos()) return;
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string t = to_string(telefono);
            string id_ts = to_string(id_tipo_sangre);
            string consulta = "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipo_sangre) VALUES ('"
                + codigo + "','" + nombres + "','" + apellidos + "','"
                + direccion + "'," + t + ", '" + fecha_nacimiento + "', " + id_ts + ");";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "________Ingreso de Datos Exitoso________" << endl;
            }
            else {
                cout << "________Insercion Fallida________" << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "________Datos del Estudiante________" << endl;
            string consulta = "select e.id_estudiante as id,e.codigo,e.nombres,e.apellidos,e.direccion,e.telefono,e.fecha_nacimiento,ts.sangre from estudiantes as e inner join tipos_sangre as ts on e.id_tipo_sangre=ts.id_tipo_sangre;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << "," << fila[1] << "," << fila[2] << ","
                        << fila[3] << "," << fila[4] << "," << fila[5] << ","
                        << fila[6] << "," << fila[7] << endl;
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Consulta Fallida" << endl;
            }
        }
        else {
            cout << "Fallo la conexion" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        if (!ValidarCampos()) return;
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string t = to_string(telefono);
            string id_ts = to_string(id_tipo_sangre);
            string id_e = to_string(id_estudiante);
            string consulta = "update estudiantes set codigo= '" + codigo
                + "', nombres = '" + nombres + "', apellidos = '" + apellidos
                + "', direccion = '" + direccion + "', telefono = " + t
                + ", fecha_nacimiento = '" + fecha_nacimiento
                + "', id_tipo_sangre = " + id_ts
                + " where id_estudiante=" + id_e + " ";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "________Modificacion de Datos Exitoso________" << endl;
            }
            else {
                cout << "________Actualizacion Fallida________" << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id_e = to_string(id_estudiante);
            string consulta = "delete from estudiantes where id_estudiante=" + id_e + " ";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                cout << "________Eliminacion de Datos Exitoso________" << endl;
            }
            else {
                cout << "________Eliminacion Fallida________" << endl;
            }
        }
        cn.cerrar_conexion();
    }
};