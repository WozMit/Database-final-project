//#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <time.h>
#include <whitedb/dbapi.h>
#define db(x) cout << #x << " = " << x << "\n";
using namespace std;

void *db, *rec;
wg_int enc;

struct Persona{
	int dni, dd, mm, aa;
	string nombres, apellidos;
	char sexo;
	Persona(){}
	Persona(int pdni, string pnombres, string papellidos, int pdd, int pmm, int paa, char psexo){
		dni = pdni;
		nombres = pnombres;
		apellidos = papellidos;
		dd = pdd;
		mm = pmm;
		aa = paa;
		sexo = psexo;
	}
	bool operator <(Persona b) const{ return dni < b.dni; }
	int edad(){
		int gg = 2018 - aa;
		if(mm > 2 || (mm == 2 && dd > 5)) gg--;
		return gg;
	}
	void Mostrar(){
		printf(" %-20d %-25s %-25s %02d/%02d/%-10d %c\n", dni, nombres.c_str(), apellidos.c_str(), dd, mm, aa, sexo);
	}
	void AgregarDB(){
		rec = wg_create_record(db, 8);
		
		enc = wg_encode_int(db, 0);
		wg_set_field(db, rec, 0, enc);
	
		enc = wg_encode_int(db, dni);
		wg_set_field(db, rec, 1, enc);
	
		char name[nombres.size()];
		for(int k=0; k<nombres.size(); k++) name[k] = nombres[k];
		name[nombres.size()] = '\0';
		enc = wg_encode_str(db, name, NULL);
		wg_set_field(db, rec, 2, enc);
	
		char last[apellidos.size()];
		for(int k=0; k<apellidos.size(); k++) last[k] = apellidos[k];
		last[apellidos.size()] = '\0';
		enc = wg_encode_str(db, last, NULL);
		wg_set_field(db, rec, 3, enc);
	
		enc = wg_encode_int(db, dd);
		wg_set_field(db, rec, 4, enc);
	
		enc = wg_encode_int(db, mm);
		wg_set_field(db, rec, 5, enc);
	
		enc = wg_encode_int(db, aa);
		wg_set_field(db, rec, 6, enc);
		
		last[0] = sexo;
		last[1] = '\0';
		enc = wg_encode_str(db, last, NULL);
		wg_set_field(db, rec, 7, enc);
	}
	void ModificarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 0);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		
		char name[nombres.size()];
		for(int k=0; k<nombres.size(); k++) name[k] = nombres[k];
		name[nombres.size()] = '\0';
		enc = wg_encode_str(db, name, NULL);
		wg_set_field(db, rec, 2, enc);
	
		char last[apellidos.size()];
		for(int k=0; k<apellidos.size(); k++) last[k] = apellidos[k];
		last[apellidos.size()] = '\0';
		enc = wg_encode_str(db, last, NULL);
		wg_set_field(db, rec, 3, enc);
	
		enc = wg_encode_int(db, dd);
		wg_set_field(db, rec, 4, enc);
	
		enc = wg_encode_int(db, mm);
		wg_set_field(db, rec, 5, enc);
	
		enc = wg_encode_int(db, aa);
		wg_set_field(db, rec, 6, enc);
		
		last[0] = sexo;
		last[1] = '\0';
		enc = wg_encode_str(db, last, NULL);
		wg_set_field(db, rec, 7, enc);
	}
	void EliminarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 0);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		wg_delete_record(db, rec);
	}
	void Recuperar(){
		dni = wg_decode_int(db, wg_get_field(db, rec, 1));
		nombres = wg_decode_str(db, wg_get_field(db, rec, 2));
		apellidos = wg_decode_str(db, wg_get_field(db, rec, 3));
		dd = wg_decode_int(db, wg_get_field(db, rec, 4));
		mm = wg_decode_int(db, wg_get_field(db, rec, 5));
		aa = wg_decode_int(db, wg_get_field(db, rec, 6));
		sexo = wg_decode_str(db, wg_get_field(db, rec, 7))[0];
	}
};

struct Docente{
	int dni;
	string curso;
	string condicion;
	double sueldo;
	Docente(){}
	Docente(int pdni, string pcurso, string pcondicion, double psueldo){
		dni = pdni;
		curso = pcurso;
		condicion = pcondicion;
		sueldo = psueldo;
	}
	bool operator <(Docente b) const{ return dni < b.dni; }
	void Mostrar(){
		printf(" %-15d %-20s %-18s %.1f\n", dni, curso.c_str(), condicion.c_str(), sueldo);
	}
	void AgregarDB(){
		rec = wg_create_record(db, 5);
		
		enc = wg_encode_int(db, 1);
		wg_set_field(db, rec, 0, enc);
	
		enc = wg_encode_int(db, dni);
		wg_set_field(db, rec, 1, enc);
	
		char curse[curso.size()];
		for(int k=0; k<curso.size(); k++) curse[k] = curso[k];
		curse[curso.size()] = '\0';
		enc = wg_encode_str(db, curse, NULL);
		wg_set_field(db, rec, 2, enc);
	
		char condition[condicion.size()];
		for(int k=0; k<condicion.size(); k++) condition[k] = condicion[k];
		condition[condicion.size()] = '\0';
		enc = wg_encode_str(db, condition, NULL);
		wg_set_field(db, rec, 3, enc);
	
		enc = wg_encode_double(db, sueldo);
		wg_set_field(db, rec, 4, enc);
	}
	void ModificarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 1);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		
		char curse[curso.size()];
		for(int k=0; k<curso.size(); k++) curse[k] = curso[k];
		curse[curso.size()] = '\0';
		enc = wg_encode_str(db, curse, NULL);
		wg_set_field(db, rec, 2, enc);
	
		char condition[condicion.size()];
		for(int k=0; k<condicion.size(); k++) condition[k] = condicion[k];
		condition[condicion.size()] = '\0';
		enc = wg_encode_str(db, condition, NULL);
		wg_set_field(db, rec, 3, enc);
	
		enc = wg_encode_double(db, sueldo);
		wg_set_field(db, rec, 4, enc);
	}
	void EliminarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 1);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		wg_delete_record(db, rec);
	}
	void Recuperar(){
		dni = wg_decode_int(db, wg_get_field(db, rec, 1));
		curso = wg_decode_str(db, wg_get_field(db, rec, 2));
		condicion = wg_decode_str(db, wg_get_field(db, rec, 3));
		sueldo = wg_decode_double(db, wg_get_field(db, rec, 4));
	}
};

struct Alumno{
	int dni, grado;
	string nivel;
	char seccion;
	Alumno(){}
	Alumno(int pdni, int pgrado, string pnivel, char pseccion){
		dni = pdni;
		grado = pgrado;
		nivel = pnivel;
		seccion = pseccion;
	}
	bool operator <(Alumno b) const{ return dni < b.dni; }
	void Mostrar(){
		printf(" %-17d %-10d %-18s %c\n", dni, grado, nivel.c_str(), seccion);
	}
	void AgregarDB(){
		rec = wg_create_record(db, 5);
		
		enc = wg_encode_int(db, 2);
		wg_set_field(db, rec, 0, enc);
	
		enc = wg_encode_int(db, dni);
		wg_set_field(db, rec, 1, enc);
		
		enc = wg_encode_int(db, grado);
		wg_set_field(db, rec, 2, enc);
	
		char lvl[nivel.size()];
		for(int k=0; k<nivel.size(); k++) lvl[k] = nivel[k];
		lvl[nivel.size()] = '\0';
		enc = wg_encode_str(db, lvl, NULL);
		wg_set_field(db, rec, 3, enc);
		
		lvl[0] = seccion;
		lvl[1] = '\0';
		enc = wg_encode_str(db, lvl, NULL);
		wg_set_field(db, rec, 4, enc);
	}
	void ModificarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 2);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		
		enc = wg_encode_int(db, grado);
		wg_set_field(db, rec, 2, enc);
	
		char lvl[nivel.size()];
		for(int k=0; k<nivel.size(); k++) lvl[k] = nivel[k];
		lvl[nivel.size()] = '\0';
		enc = wg_encode_str(db, lvl, NULL);
		wg_set_field(db, rec, 3, enc);
		
		lvl[0] = seccion;
		lvl[1] = '\0';
		enc = wg_encode_str(db, lvl, NULL);
		wg_set_field(db, rec, 4, enc);
	}
	void EliminarDB(){
		wg_query_arg arglist[2];
		arglist[0].column = 0;
		arglist[0].cond = WG_COND_EQUAL;
		arglist[0].value = wg_encode_query_param_int(db, 2);
		arglist[1].column = 1;
		arglist[1].cond = WG_COND_EQUAL;
		arglist[1].value = wg_encode_query_param_int(db, dni);
		wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
		rec = wg_fetch(db, query);
		wg_free_query(db, query);
		wg_free_query_param(db, arglist[0].value);
		wg_free_query_param(db, arglist[1].value);
		wg_delete_record(db, rec);
	}
	void Recuperar(){
		dni = wg_decode_int(db, wg_get_field(db, rec, 1));
		grado = wg_decode_int(db, wg_get_field(db, rec, 2));
		nivel = wg_decode_str(db, wg_get_field(db, rec, 3));
		seccion = wg_decode_str(db, wg_get_field(db, rec, 4))[0];
	}
};
vector<Persona> Lista_personas;
vector<Docente> Lista_docentes;
vector<Alumno> Lista_alumnos;

void MenuPrincipal();
void MenuPersonas();
void MenuDocentes();
void MenuAlumnos();
void ReportesEspeciales();
void ListarPersonas();
void ListarDocentes();
void ListarAlumnos();
void AgregarPersona();
void AgregarDocente();
void AgregarAlumno();
void ModificarPersona();
void ModificarDocente();
void ModificarAlumno();
void EliminarPersona();
void EliminarDocente();
void EliminarAlumno();
void ReporteDocentesMatematica();
void ReporteDocentesSueldo7000();
void ReporteAlumnosSecundaria();
void ReporteDocentes20();
void ReporteOcupacionesHombres();
bool ExistePersona(int pdni);
bool ExisteDocente(int pdni);
bool ExisteAlumno(int pdni);

void ConectarDB(){
	//Crea la db con idx 1000 y 2MB
	char st1[] = "1000";
	db = wg_attach_database(st1, 2000000);
	if(!db){
		printf("Error: No se pudo conectar a la base de datos.\n");
		exit(1);
	}
}

void RecuperarPersonas(){
	Lista_personas.clear();
	wg_query_arg arglist[1];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 0);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 1);
	Persona per;
	while((rec = wg_fetch(db, query))){
		per.Recuperar();
		Lista_personas.push_back(per);
	}
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
}

void RecuperarDocentes(){
	Lista_docentes.clear();
	wg_query_arg arglist[1];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 1);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 1);
	Docente doc;
	while((rec = wg_fetch(db, query))){
		doc.Recuperar();
		Lista_docentes.push_back(doc);
	}
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
}

void RecuperarAlumnos(){
	Lista_alumnos.clear();
	wg_query_arg arglist[1];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 2);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 1);
	Alumno al;
	while((rec = wg_fetch(db, query))){
		al.Recuperar();
		Lista_alumnos.push_back(al);
	}
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
}

void MenuPrincipal(){
	puts("\n/////////////// Menú principal ///////////////\n");
	puts("1) Menú de personas");
	puts("2) Menú de docentes");
	puts("3) Menú de alumnos");
	puts("4) Reportes especiales");
	int op = -1;
	while(op < 1 || op > 4){
		printf("\nIngrese una opción: ");
		scanf("%d", &op);
	}
	switch(op){
		case 1:
			MenuPersonas();
			break;
		case 2:
			MenuDocentes();
			break;
		case 3:
			MenuAlumnos();
			break;
		case 4:
			ReportesEspeciales();
			break;
	}
}

void MenuPersonas(){
	puts("\n/////////////// Menú de personas ///////////////\n");
	puts("1) Listar personas");
	puts("2) Agregar persona");
	puts("3) Modificar datos de persona");
	puts("4) Eliminar persona");
	puts("5) Volver al menú principal");
	int op = -1;
	while(op < 1 || op > 5){
		printf("\nIngrese una opción: ");
		scanf("%d", &op);
	}
	switch(op){
		case 1:
			ListarPersonas();
			MenuPersonas();
			break;
		case 2:
			AgregarPersona();
			MenuPersonas();
			break;
		case 3:
			ModificarPersona();
			MenuPersonas();
			break;
		case 4:
			EliminarPersona();
			MenuPersonas();
			break;
		case 5:
			MenuPrincipal();
			break;
	}
}

void MenuDocentes(){
	puts("\n/////////////// Menú de docentes ///////////////\n");
	puts("1) Listar docentes");
	puts("2) Agregar docente");
	puts("3) Modificar datos de docente");
	puts("4) Eliminar docente");
	puts("5) Volver al menú principal");
	int op = -1;
	while(op < 1 || op > 5){
		printf("\nIngrese una opción: ");
		scanf("%d", &op);
	}
	switch(op){
		case 1:
			ListarDocentes();
			MenuDocentes();
			break;
		case 2:
			AgregarDocente();
			MenuDocentes();
			break;
		case 3:
			ModificarDocente();
			MenuDocentes();
			break;
		case 4:
			EliminarDocente();
			MenuDocentes();
			break;
		case 5:
			MenuPrincipal();
			break;
	}
}

void MenuAlumnos(){
	puts("\n/////////////// Menú de alumnos ///////////////\n");
	puts("1) Listar alumnos");
	puts("2) Agregar alumno");
	puts("3) Modificar datos de alumno");
	puts("4) Eliminar alumno");
	puts("5) Volver al menú principal");
	int op = -1;
	while(op < 1 || op > 5){
		printf("\nIngrese una opción: ");
		scanf("%d", &op);
	}
	switch(op){
		case 1:
			ListarAlumnos();
			MenuAlumnos();
			break;
		case 2:
			AgregarAlumno();
			MenuAlumnos();
			break;
		case 3:
			ModificarAlumno();
			MenuAlumnos();
			break;
		case 4:
			EliminarAlumno();
			MenuAlumnos();
			break;
		case 5:
			MenuPrincipal();
			break;
	}
}

void ReportesEspeciales(){
	puts("\n/////////////// Reportes especiales ///////////////\n");
	puts("1) Listar docentes de matemática");
	puts("2) Docentes que ganan más de S/.7000");
	puts("3) Listar alumnos de secundaria");
	puts("4) Listar docentes mayores de 20 años");
	puts("5) Listar a los hombres con sus ocupaciones");
	puts("6) Volver al menú principal");
	int op = -1;
	while(op < 1 || op > 6){
		printf("\nIngrese una opción: ");
		scanf("%d", &op);
	}
	switch(op){
		case 1:
			ReporteDocentesMatematica();
			ReportesEspeciales();
			break;
		case 2:
			ReporteDocentesSueldo7000();
			ReportesEspeciales();
			break;
		case 3:
			ReporteAlumnosSecundaria();
			ReportesEspeciales();
			break;
		case 4:
			ReporteDocentes20();
			ReportesEspeciales();
			break;
		case 5:
			ReporteOcupacionesHombres();
			ReportesEspeciales();
			break;
		case 6:
			MenuPrincipal();
			break;
	}
}

bool ExistePersona(int pdni){
	wg_query_arg arglist[2];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 0);
	arglist[1].column = 1;
	arglist[1].cond = WG_COND_EQUAL;
	arglist[1].value = wg_encode_query_param_int(db, pdni);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
	bool flag = false;
	if((rec = wg_fetch(db, query))) flag = true;
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
	wg_free_query_param(db, arglist[1].value);
	return flag;
}

bool ExisteDocente(int pdni){
	wg_query_arg arglist[2];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 1);
	arglist[1].column = 1;
	arglist[1].cond = WG_COND_EQUAL;
	arglist[1].value = wg_encode_query_param_int(db, pdni);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
	bool flag = false;
	if((rec = wg_fetch(db, query))) flag = true;
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
	wg_free_query_param(db, arglist[1].value);
	return flag;
}

bool ExisteAlumno(int pdni){
	wg_query_arg arglist[2];
	arglist[0].column = 0;
	arglist[0].cond = WG_COND_EQUAL;
	arglist[0].value = wg_encode_query_param_int(db, 2);
	arglist[1].column = 1;
	arglist[1].cond = WG_COND_EQUAL;
	arglist[1].value = wg_encode_query_param_int(db, pdni);
	wg_query *query = wg_make_query(db, NULL, 0, arglist, 2);
	bool flag = false;
	if((rec = wg_fetch(db, query))) flag = true;
	wg_free_query(db, query);
	wg_free_query_param(db, arglist[0].value);
	wg_free_query_param(db, arglist[1].value);
	return flag;
}

void ListarPersonas(){
	RecuperarPersonas();
	puts("\n//////////////////////////////////// Lista de personas ////////////////////////////////////\n");
	printf(" %-20s %-25s %-25s %-13s %s\n", "DNI", "Nombres", "Apellidos", "F. Nacim.", "Sexo");
	puts("---------------------------------------------------------------------------------------------");
	for(int i=0; i<Lista_personas.size(); i++)
		Lista_personas[i].Mostrar();
}

void ListarDocentes(){
	RecuperarDocentes();
	puts("\n//////////////////////////////////// Lista de docentes ////////////////////////////////////\n");
	printf(" %-15s %-20s %-18s %s\n", "DNI", "Curso", "Condición", "Sueldo");
	puts("----------------------------------------------------------------");
	for(int i=0; i<Lista_docentes.size(); i++)
		Lista_docentes[i].Mostrar();
}

void ListarAlumnos(){
	RecuperarAlumnos();
	puts("\n/////////////////////////// Lista de alumnos ///////////////////////////\n");
	printf(" %-17s %-10s %-18s %s\n", "DNI", "Grado", "Nivel", "Sección");
	puts("----------------------------------------------------------");
	for(int i=0; i<Lista_alumnos.size(); i++)
		Lista_alumnos[i].Mostrar();
}

void AgregarPersona(){
	puts("\n//////////////////////////////////// Agregar nueva persona ////////////////////////////////////\n");
	int pdni, pdd, pmm, paa;
	string pnombres, papellidos;
	char psexo;
	printf("DNI de la nueva persona: ");
	scanf("%d", &pdni);
	if(ExistePersona(pdni)){
		puts("\nLa persona ya se encuentra registrada.\n");
		printf("¿Desea agregar otra persona? (s/n): ");
		scanf(" %c", &psexo);
		if(psexo == 's') AgregarPersona();
		return;
	}
	printf("Nombres: ");
	cin >> pnombres;
	printf("Apellidos: ");
	cin >> papellidos;
	printf("Fecha de nacimiento (dd/mm/aa): ");
	scanf("%d/%d/%d", &pdd, &pmm, &paa);
	printf("Sexo (M/F): ");
	scanf(" %c", &psexo);
	Persona P = Persona(pdni, pnombres, papellidos, pdd, pmm, paa, psexo);
	printf("\n %-20s %-25s %-25s %-13s %s\n", "DNI", "Nombres", "Apellidos", "F. Nacim.", "Sexo");
	puts("---------------------------------------------------------------------------------------------");
	P.Mostrar();
	printf("\n¿Confirmar? (s/n): ");
	scanf(" %c", &psexo);
	if(psexo == 's'){
		P.AgregarDB();
		puts("\nPersona agregada con éxito!");
	} else{
		puts("\nSe canceló la operación.");
	}
}

void AgregarDocente(){
	puts("\n//////////////////////////////////// Agregar nuevo docente ////////////////////////////////////\n");
	int pdni;
	string pcurso, pcondicion;
	double psueldo;
	char op;
	printf("DNI del nuevo docente: ");
	scanf("%d", &pdni);
	if(!ExistePersona(pdni)){
		puts("\nEl docente no se encuentra registrado como persona.\n");
		printf("¿Desea agregarlo como persona? (s/n): ");
		scanf(" %c", &op);
		if(op == 's') AgregarPersona();
		return;
	}
	if(ExisteDocente(pdni)){
		puts("\nEl docente ya se encuentra registrado.\n");
		printf("¿Desea agregar otro docente? (s/n): ");
		scanf(" %c", &op);
		if(op == 's') AgregarDocente();
		return;
	}
	if(ExisteAlumno(pdni)){
		puts("\nLa persona ya se encuentra registrada como alumno.\n");
		printf("¿Desea agregar otro docente? (s/n): ");
		scanf(" %c", &op);
		if(op == 's') AgregarDocente();
		return;
	}
	printf("Curso: ");
	cin >> pcurso;
	printf("Condición: ");
	cin >> pcondicion;
	printf("Sueldo: ");
	scanf("%lf", &psueldo);
	Docente doc = Docente(pdni, pcurso, pcondicion, psueldo);
	printf(" %-15s %-20s %-18s %s\n", "DNI", "Curso", "Condición", "Sueldo");
	puts("----------------------------------------------------------------");
	doc.Mostrar();
	printf("\n¿Confirmar? (s/n): ");
	scanf(" %c", &op);
	if(op == 's'){
		doc.AgregarDB();
		puts("\nDocente agregado con éxito!");
	} else{
		puts("\nSe canceló la operación.");
	}
}

void AgregarAlumno(){
	puts("\n//////////////////////////////////// Agregar nuevo alumno ////////////////////////////////////\n");
	int pdni, pgrado;
	string pnivel;
	char pseccion;
	printf("DNI del nuevo alumno: ");
	scanf("%d", &pdni);
	if(!ExistePersona(pdni)){
		puts("\nEl alumno no se encuentra registrado como persona.\n");
		printf("¿Desea agregarlo como persona? (s/n): ");
		scanf(" %c", &pseccion);
		if(pseccion == 's') AgregarPersona();
		return;
	}
	if(ExisteAlumno(pdni)){
		puts("\nEl alumno ya se encuentra registrado.\n");
		printf("¿Desea agregar otro alumno? (s/n): ");
		scanf(" %c", &pseccion);
		if(pseccion == 's') AgregarAlumno();
		return;
	}
	if(ExisteDocente(pdni)){
		puts("\nLa persona ya se encuentra registrada como docente.\n");
		printf("¿Desea agregar otro alumno? (s/n): ");
		scanf(" %c", &pseccion);
		if(pseccion == 's') AgregarAlumno();
		return;
	}
	printf("Grado: ");
	scanf("%d", &pgrado);
	printf("Nivel (Primaria/Secundaria): ");
	cin >> pnivel;
	printf("Sección (A-Z): ");
	scanf(" %c", &pseccion);
	Alumno al = Alumno(pdni, pgrado, pnivel, pseccion);
	printf(" %-17s %-10s %-18s %s\n", "DNI", "Grado", "Nivel", "Sección");
	puts("----------------------------------------------------------");
	al.Mostrar();
	printf("\n¿Confirmar? (s/n): ");
	scanf(" %c", &pseccion);
	if(pseccion == 's'){
		al.AgregarDB();
		puts("\nAlumno agregado con éxito!");
	} else{
		puts("\nSe canceló la operación.");
	}
}

void ModificarPersona(){
	puts("\n//////////////////////////////////// Modificar los datos de una persona ////////////////////////////////////\n");
	int pdni;
	printf("DNI de la persona: ");
	scanf("%d", &pdni);
	if(!ExistePersona(pdni))
		puts("\nLa persona no se encuentra registrada en la base de datos.");
	else{
		puts("\nDatos de la persona seleccionada:\n");
		printf(" %-20s %-25s %-25s %-13s %s\n", "DNI", "(1) Nombres", "(2) Apellidos", "(3) F. Nacim.", "(4) Sexo");
		puts("---------------------------------------------------------------------------------------------");
		Persona per = Persona();
		per.Recuperar();
		per.Mostrar();
		char op, cont = 's';
		while(cont == 's'){
			printf("\nOpción(1-4): ");
			scanf(" %c", &op);
			if(op == '1'){
				string s;
				printf("\nIngrese el nuevo nombre: ");
				cin >> s;
				per.nombres = s;
			}
			else if (op == '2'){
				string s;
				printf("\nIngrese el nuevo apellido: ");
				cin >> s;
				per.apellidos = s;
			}
			else if(op == '3'){
				int d, m, a;
				printf("\nIngrese la nueva fecha de nacimiento (dd/mm/aa): ");
				scanf("%d/%d/%d", &d, &m, &a);
				per.dd = d;
				per.mm = m;
				per.aa = a;
			}
			else if(op == '4'){
				char sexo;
				printf("\nIngrese el nuevo sexo (M/F): ");
				scanf(" %c", &sexo);
				per.sexo = sexo;
			}
			printf("\n %-20s %-25s %-25s %-13s %s\n", "DNI", "(1) Nombres", "(2) Apellidos", "(3) F. Nacim.", "(4) Sexo");
			puts("---------------------------------------------------------------------------------------------");
			per.Mostrar();
			printf("\n¿Desea modificar algún dato más? (s/n): ");
			scanf(" %c", &cont);
		}
		puts("\nDatos de la persona:\n");
		printf(" %-20s %-25s %-25s %-13s %s\n", "DNI", "Nombres", "Apellidos", "F. Nacim.", "Sexo");
		puts("---------------------------------------------------------------------------------------------");
		per.Mostrar();
		printf("\n¿Desea guardar los cambios? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			per.ModificarDB();
			puts("\nDatos modificados correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void ModificarDocente(){
	puts("\n//////////////////////////////////// Modificar los datos de un docente ////////////////////////////////////\n");
	int pdni;
	printf("DNI del docente: ");
	scanf("%d", &pdni);
	if(!ExisteDocente(pdni))
		puts("\nEl docente no se encuentra registrado en la base de datos.");
	else{
		puts("\nDatos del docente seleccionado:\n");
		printf(" %-15s %-20s %-18s %s\n", "DNI", "(1) Curso", "(2) Condición", "(3) Sueldo");
		puts("----------------------------------------------------------------");
		Docente doc = Docente();
		doc.Recuperar();
		doc.Mostrar();
		char op, cont = 's';
		while(cont == 's'){
			printf("\nOpción(1-3): ");
			scanf(" %c", &op);
			if(op == '1'){
				string s;
				printf("\nIngrese el nuevo curso: ");
				cin >> s;
				doc.curso = s;
			}
			else if (op == '2'){
				string s;
				printf("\nIngrese la nueva condición: ");
				cin >> s;
				doc.condicion = s;
			}
			else if(op == '3'){
				double suel;
				printf("\nIngrese el nuevo sueldo: ");
				scanf("%lf", &suel);
				doc.sueldo = suel;
			}
			printf(" %-15s %-20s %-18s %s\n", "DNI", "(1) Curso", "(2) Condición", "(3) Sueldo");
			puts("----------------------------------------------------------------");
			doc.Mostrar();
			printf("\n¿Desea modificar algún dato más? (s/n): ");
			scanf(" %c", &cont);
		}
		puts("\nDatos del docente:\n");
		printf(" %-15s %-20s %-18s %s\n", "DNI", "Curso", "Condición", "Sueldo");
		puts("----------------------------------------------------------------");
		doc.Mostrar();
		printf("\n¿Desea guardar los cambios? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			doc.ModificarDB();
			puts("\nDatos modificados correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void ModificarAlumno(){
	puts("\n//////////////////////////////////// Modificar los datos de un alumno ////////////////////////////////////\n");
	int pdni;
	printf("DNI del alumno: ");
	scanf("%d", &pdni);
	if(!ExisteAlumno(pdni))
		puts("\nEl alumno no se encuentra registrado en la base de datos.");
	else{
		puts("\nDatos del alumno seleccionado:\n");
		printf(" %-17s %-10s %-18s %s\n", "DNI", "(1) Grado", "(2) Nivel", "(3) Sección");
		puts("----------------------------------------------------------");
		Alumno al = Alumno();
		al.Recuperar();
		al.Mostrar();
		char op, cont = 's';
		while(cont == 's'){
			printf("\nOpción(1-3): ");
			scanf(" %c", &op);
			if(op == '1'){
				int grad;
				printf("\nIngrese el nuevo grado: ");
				scanf("%d", &grad);
				al.grado = grad;
			}
			else if (op == '2'){
				string s;
				printf("\nIngrese el nuevo nivel: ");
				cin >> s;
				al.nivel = s;
			}
			else if(op == '3'){
				char seccio;
				printf("\nIngrese la nueva sección: ");
				scanf(" %c", &seccio);
				al.seccion = seccio;
			}
			printf(" %-17s %-10s %-18s %s\n", "DNI", "(1) Grado", "(2) Nivel", "(3) Sección");
			puts("----------------------------------------------------------");
			al.Mostrar();
			printf("\n¿Desea modificar algún dato más? (s/n): ");
			scanf(" %c", &cont);
		}
		puts("\nDatos del alumno:\n");
		printf(" %-17s %-10s %-18s %s\n", "DNI", "Grado", "Nivel", "Sección");
		puts("----------------------------------------------------------");
		al.Mostrar();
		printf("\n¿Desea guardar los cambios? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			al.ModificarDB();
			puts("\nDatos modificados correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void EliminarPersona(){
	puts("\n//////////////////////////////////// Eliminar persona ////////////////////////////////////\n");
	int pdni;
	printf("DNI de la persona: ");
	scanf("%d", &pdni);
	if(!ExistePersona(pdni))
		puts("\nLa persona no se encuentra registrada en la base de datos.");
	else{
		puts("\nDatos de la persona seleccionada:\n");
		printf(" %-20s %-25s %-25s %-13s %s\n", "DNI", "Nombres", "Apellidos", "F. Nacim.", "Sexo");
		puts("---------------------------------------------------------------------------------------------");
		Persona per = Persona();
		Docente doc = Docente();
		Alumno al = Alumno();
		per.Recuperar();
		per.Mostrar();
		char op;
		bool flag1 = false, flag2 = false;
		if(ExisteDocente(pdni)){
			flag1 = true;
			doc.Recuperar();
			puts("\nLa persona también se encuentra registrada como docente. Si elimina a la persona, se eliminarán todas sus apariciones.\n");
			printf(" %-15s %-20s %-18s %s\n", "DNI", "Curso", "Condición", "Sueldo");
			puts("----------------------------------------------------------------");
			doc.Mostrar();
		}
		if(ExisteAlumno(pdni)){
			flag2 = true;
			al.Recuperar();
			puts("\nLa persona también se encuentra registrada como alumno. Si elimina a la persona, se eliminarán todas sus apariciones.\n");
			printf(" %-17s %-10s %-18s %s\n", "DNI", "Grado", "Nivel", "Sección");
			puts("----------------------------------------------------------");
			al.Mostrar();
		}
		printf("\n¿Desea eliminarla de la base de datos? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			if(flag1) doc.EliminarDB();
			if(flag2) al.EliminarDB();
			per.EliminarDB();
			puts("\nPersona eliminada correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void EliminarDocente(){
	puts("\n//////////////////////////////////// Eliminar docente ////////////////////////////////////\n");
	int pdni;
	printf("DNI del docente: ");
	scanf("%d", &pdni);
	if(!ExisteDocente(pdni))
		puts("\nEl docente no se encuentra registrado en la base de datos.");
	else{
		puts("\nDatos del docente seleccionado:\n");
		printf(" %-15s %-20s %-18s %s\n", "DNI", "Curso", "Condición", "Sueldo");
		puts("----------------------------------------------------------------");
		Docente doc = Docente();
		doc.Recuperar();
		doc.Mostrar();
		char op;
		printf("\n¿Desea eliminarlo de la base de datos? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			doc.EliminarDB();
			puts("\nDocente eliminado correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void EliminarAlumno(){
	puts("\n//////////////////////////////////// Eliminar alumno ////////////////////////////////////\n");
	int pdni;
	printf("DNI del alumno: ");
	scanf("%d", &pdni);
	if(!ExisteAlumno(pdni))
		puts("\nEl alumno no se encuentra registrado en la base de datos.");
	else{
		puts("\nDatos del alumno seleccionado:\n");
		printf(" %-17s %-10s %-18s %s\n", "DNI", "Grado", "Nivel", "Sección");
		puts("----------------------------------------------------------");
		Alumno al = Alumno();
		al.Recuperar();
		al.Mostrar();
		char op;
		printf("\n¿Desea eliminarlo de la base de datos? (s/n): ");
		scanf(" %c", &op);
		if(op == 's'){
			al.EliminarDB();
			puts("\nAlumno eliminado correctamente!");
		}
		else puts("\nSe canceló la operación.");
	}
}

void ReporteDocentesMatematica(){
	RecuperarPersonas();
	RecuperarDocentes();
	puts("\n//////////////////////////////////// Docentes de Matemática ////////////////////////////////////\n");
	printf(" %-15s %-13s %-20s %-15s %s\n", "DNI", "Nombres", "Apellidos", "Condición", "Sueldo");
	puts("----------------------------------------------------------------------------");
	for(int i=0; i<Lista_docentes.size(); i++)
		if(Lista_docentes[i].curso == "Matemática"){
			Docente doc = Lista_docentes[i];
			for(int j=0; j<Lista_personas.size(); j++)
				if(doc.dni == Lista_personas[j].dni){
					Persona per = Lista_personas[j];
					printf(" %-15d %-13s %-20s %-15s %.1f\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), doc.condicion.c_str(), doc.sueldo);
				}
		}
}

void ReporteDocentesSueldo7000(){
	RecuperarPersonas();
	RecuperarDocentes();
	puts("\n//////////////////////////////////// Docentes que ganan más de 7000 ////////////////////////////////////\n");
	printf(" %-15s %-13s %-20s %-20s %-15s %s\n", "DNI", "Nombres", "Apellidos", "Curso", "Condición", "Sueldo");
	puts("-------------------------------------------------------------------------------------------------");
	for(int i=0; i<Lista_docentes.size(); i++)
		if(Lista_docentes[i].sueldo > 7000.0){
			Docente doc = Lista_docentes[i];
			for(int j=0; j<Lista_personas.size(); j++)
				if(doc.dni == Lista_personas[j].dni){
					Persona per = Lista_personas[j];
					printf(" %-15d %-13s %-20s %-20s %-15s %.1f\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), doc.curso.c_str(), doc.condicion.c_str(), doc.sueldo);
				}
		}
}

void ReporteAlumnosSecundaria(){
	RecuperarPersonas();
	RecuperarAlumnos();
	puts("\n//////////////////////////////////// Alumnos de secundaria ////////////////////////////////////\n");
	printf(" %-15s %-13s %-23s %-10s %-15s %s\n", "DNI", "Nombres", "Apellidos", "Grado", "Nivel", "Sección");
	puts("-------------------------------------------------------------------------------------------------");
	for(int i=0; i<Lista_alumnos.size(); i++)
		if(Lista_alumnos[i].nivel == "Secundaria"){
			Alumno al = Lista_alumnos[i];
			for(int j=0; j<Lista_personas.size(); j++)
				if(al.dni == Lista_personas[j].dni){
					Persona per = Lista_personas[j];
					printf(" %-15d %-13s %-23s %-10d %-15s %c\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), al.grado, al.nivel.c_str(), al.seccion);
				}
		}
}

void ReporteDocentes20(){
	RecuperarPersonas();
	RecuperarDocentes();
	puts("\n//////////////////////////////////// Docentes mayores de 20 años ////////////////////////////////////\n");
	printf(" %-15s %-13s %-20s %-10s %-20s %-15s %s\n", "DNI", "Nombres", "Apellidos", "Edad", "Curso", "Condición", "Sueldo");
	puts("-----------------------------------------------------------------------------------------------------------");
	for(int i=0; i<Lista_docentes.size(); i++)
		for(int j=0; j<Lista_personas.size(); j++)
			if(Lista_docentes[i].dni == Lista_personas[j].dni && Lista_personas[j].edad() > 20){
				Docente doc = Lista_docentes[i];
				Persona per = Lista_personas[j];
				printf(" %-15d %-13s %-20s %-10d %-20s %-15s %.1f\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), per.edad(), doc.curso.c_str(), doc.condicion.c_str(), doc.sueldo);
			}
}

void ReporteOcupacionesHombres(){
	RecuperarPersonas();
	RecuperarDocentes();
	RecuperarAlumnos();
	puts("\n//////////////////////////////////// Hombres y sus ocupaciones ////////////////////////////////////\n");
	printf(" %-15s %-18s %-25s %-15s %-10s %-12s %s\n", "DNI", "Nombres", "Apellidos", "F. Nacim.", "Sexo", "Ocupación", "Situación");
	puts("----------------------------------------------------------------------------------------------------------------");
	for(int i=0; i<Lista_personas.size(); i++)
		if(Lista_personas[i].sexo == 'M'){
			Persona per = Lista_personas[i];
			for(int j=0; j<Lista_docentes.size(); j++)
				if(Lista_docentes[j].dni == per.dni){
					Docente doc = Lista_docentes[j];
					printf(" %-15d %-18s %-25s %02d/%02d/%-10d %-10c %-10s %s\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), per.dd, per.mm, per.aa, per.sexo, "Docente", doc.curso.c_str());
				}
			for(int j=0; j<Lista_alumnos.size(); j++)
				if(Lista_alumnos[j].dni == per.dni){
					Alumno al = Lista_alumnos[j];
					printf(" %-15d %-18s %-25s %02d/%02d/%-10d %-10c %-10s %d%s\n", per.dni, per.nombres.c_str(), per.apellidos.c_str(), per.dd, per.mm, per.aa, per.sexo, "Docente", al.grado, " grado");
				}
		}
}

int main(){
	ConectarDB();
	MenuPrincipal();
	return 0;
}
