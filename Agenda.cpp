
/*****************************
 Librerïas utilizadas
*****************************/
#include <iostream>					/*Flujo de entrada y salida de datos*/
#include <string.h>					/*Funciones de manejo de cadenas*/
#include <windows.h>				/*Permite usar comandos de Windows Console*/
#include <stdio.h>
#include <fstream>
#include <string>

#define CANTIDAD 500 				/*Cantidad maxima de contactos: 500*/

using namespace std;

/*
	Variables globales que representan contactos registrados, eliminados y una variable Regla que presentara una mejor vista en el programa.
*/
int ContactosRegistrados = 0;
int ContactosEliminados  = 0;
string Regla = "=============================================================";

/*****************************
Estructura de fecha y Agenda
*****************************/
/*Estructura de fecha de nacimiento*/
struct Cumple {
	string Nacimiento;
};

/*Estructura de Agenda, contiene todos los atributos*/
struct Agenda {
	string Nombre;
	string Telefono;
	string Celular;
	string Email;
	Cumple Fecha;					/*Referencia a la estructura Cumple*/
	Agenda();  						/*Declaracion del constructor*/
};

/*****************************
	FUNCIONES PRINCIPALES 
*****************************/

int MenuPrimario();					/*Se muestra cuando no hay contactos*/
int MenuSecundario();				/*Se muestra cuando hay contactos que gestionar*/

/*Relevante e importante*/
void Insertar(struct Agenda Contactos[]);			/*Inserta contactos en la agenda*/
void LeerArchivo();
void EscribirArchivo(struct Agenda Contacto);

/*Relevante e importante*/
void Buscar(struct Agenda Contactos[]);				/*Busca contactos en la agenda*/
int BuscarMenuCategoria();							/*Se muestra un menu para buscar por categorï¿½as*/
void BuscarPorNombre(struct Agenda Contactos[]);	/*Aplica una busqueda por nombre de contacto*/
void BuscarPorTelefono(struct Agenda Contactos[]);	/*Aplica una busqueda por telï¿½fono de contacto*/
void BuscarPorCelular(struct Agenda Contactos[]);	/*Aplica una busqueda por celular de contacto*/
void BuscarPorEmail(struct Agenda Contactos[]);		/*Aplica una busqueda por email de contacto*/

/*Relevante e importante*/
void Listar(struct Agenda Contactos[]);				/*Lista todos los contactos existentes*/
void Imprimir(struct Agenda Contactos[], int);		/*Mostrar un contacto seleccionado*/

/*Relevante e importante*/
void Actualizar(struct Agenda Contactos[], int);	/*Actualiza un contacto seleccionado en la agenda*/
/*Relevante e importante*/
void Eliminar(struct Agenda Contactos[], int);		/*Elimina un contacto seleccionado en la agenda*/

int VerificarContacto(struct Agenda Contactos[], string);	/*Verifica si el contacto especificado existe*/

/*
Esta funcion es interesante, tiene como objetivo cargar datos (contactos) en la agenda para pruebas rapidas en la ejcucion del programa.
*/
void CargarContactos(struct Agenda Contactos[]);
bool HayContactos(struct Agenda Contactos[]);		/*Verifica si hay contactos en la agenda*/

/*****************************
	FUNCIONES SECUNDARIAS
*****************************/
void Detenerse();									/*Detiene la ejecucion, hasta que se presione una tecla*/
void LimpiarPantalla();								/*Limpia la pantalla para mostrar un nuevo Menu*/
void Dormir(int);									/*Aplica un retraso temporal*/
int Salir();										/*Centinela que pregunta por la salida de los Menues*/

/*****************************
 DEFINICION DEL CONSTRUCTOR
-----------------------------
Inicializando la estructura.
*****************************/
Agenda::Agenda() {
	Nombre 		= " ";								/*Para nombre, dejar un espacio en blanco*/
	Telefono 	= "0";								/*Para telefono, dejar 0 como contenido*/
	Celular 	= "0";								/*Para celular, dejar 0 como contenido*/
	Email 		= " ";								/*Para email, dejar un espacio en blanco*/
	Fecha.Nacimiento = " ";							/*Para fecha, dejar un espacio en blanco*/
}

/*****************************
	  FUNCION PRINCIPAL
*****************************/
int main(int argc, char *argv[]) {
	//setlocale(LC_CTYPE, "spanish");
	int x;											/*Almacena las opciones seleccionadas*/
	int salir = 0;                                  /*bandera para salir*/
	Agenda Contactos[CANTIDAD]; 					/*Definicion de la variable Contactos con la cantidad*/
	//CargarContactos(Contactos);						/*Menu para cargar datos o iniciar una nueva agenda*/
	
	do {
		x = MenuSecundario();	
	} while(x < 1 || x > 4);
	
	switch (x){								/*Este Menu contiene las opciones (Insertar, buscar, listar)*/
		case 1: 
			Insertar(Contactos);
			break;
		case 2:
			Buscar(Contactos);				/*Menu para realizar una busqueda de contactos por categorias*/
			break;
		case 3: 
			Listar(Contactos);				/*Listar todos los contactos existentes de manera interactiva*/
			break;
		case 4:
			salir = Salir();				/*Centinela para Salir*/
			break;
		default:
			cout << "ERROR, presione una tecla para continuar!." << endl;
			system("PAUSE>NUL");
		}
	
	return 0;
}

int MenuPrimario(){
	int x;										/*Sirve para almacenar la respuesta (opcion)*/
	
	LimpiarPantalla();
	
	cout << Regla << endl;
	cout << "|\tBienvenido a tu Agenda Electronica de Contactos\t    |" << endl;
	cout << Regla << endl;
	
	cout << "|\t\t\t\t\t\t\t    |" << endl;
	cout << "|\t\t       No hay contactos\t\t\t    |" << endl;
	cout << "|\t\t\t\t\t\t\t    |" << endl;
	
	cout << Regla << endl;
	cout << "| (1) Nuevo contacto           |        (2) Salir           |" << endl;
	cout << Regla << endl;
	
	cout << "Esperando respuesta: ";
	cin >> x;
	
	return x;									/*Convierte y retorna la opcion seleccionada*/
}

int MenuSecundario(){
	int x;
	
	LimpiarPantalla();
	
	cout << Regla << endl;
	cout << "|\tBienvenido a tu Agenda Electronica de Contactos\t    |" << endl;
	cout << Regla << endl;
	
	cout << "|\t\t\t\t\t\t\t    |" << endl;
	cout << "|\t\t      Si hay contactos" << " (" << (ContactosRegistrados - ContactosEliminados) << ")\t\t    |" << endl;
	cout << "|\t\t\t\t\t\t\t    |" << endl;
		
	cout << Regla << endl;
	cout << "| (1) Nuevo   | (2) Buscar   |  (3) Listar   |  (4) Salir   |" << endl;
	cout << Regla << endl;
	
	cout << "Esperando respuesta: ";
	cin >> x;
	return x;
}

void Insertar(struct Agenda Contactos[]){
	int x;
	int salir =0;						/*bandera para salir*/
	
	while(!salir){ 									/*Etiqueta de Menï¿½ para insertar contactos*/
		/*Se verifica si hay espacio en la agenda*/
		if (ContactosRegistrados < CANTIDAD){

			cout << "\n\tNumero de contacto: " << (ContactosRegistrados + 1) << endl;
			cout << "\tNombre:   ";
			cin >>  Contactos[ContactosRegistrados].Nombre;
			
			cout << "\tTel?fono: ";									
			cin >>  Contactos[ContactosRegistrados].Telefono;	/*Agregando valor a atributo Telefono*/
			
			cout << "\tCelular:  ";
			cin >>  Contactos[ContactosRegistrados].Celular;	/*Agregando valor a atributo Celular*/
			
			cout << "\tEmail:    ";
			cin >>  Contactos[ContactosRegistrados].Email;	/*Agregando valor a atributo Email*/
			
			cout << "\tFecha de Nacimiento (DD/MM/AAAA): ";
			cin >>  Contactos[ContactosRegistrados].Fecha.Nacimiento;	/*Agregando valor a atributo de Fecha*/
			
			/*Se verifica si el contacto que esta intentando insertar, existe en la agenda*/
			if (VerificarContacto(Contactos, Contactos[ContactosRegistrados].Nombre)){
				cout << "\n\tEl contacto \"" << Contactos[ContactosRegistrados].Nombre << "\" ya existe!" << endl;
				
				Contactos[ContactosRegistrados].Nombre = " ";
				Contactos[ContactosRegistrados].Telefono = "0";
				Contactos[ContactosRegistrados].Celular = "0";
				Contactos[ContactosRegistrados].Fecha.Nacimiento = " ";
			}
			else{
				EscribirArchivo(Contactos[ContactosRegistrados]);
				ContactosRegistrados++;									/*Se incrementa la variable, indicando nuevo contacto*/
				cout << "\n\tAgregado con exito!" << endl << endl;
			}


			do {
				cout << "\n\t¿Desea agregar otro contacto?" << endl;
				cout << "\t(1) Si, (2) No: ";
				cin >> x;
				cout<<"Numero elegido es:"<< x <<endl;
			} while(x < 1 || x > 2);
			
			switch (x){
				case 1: 
					// volvemos a InsertarMenu
					break;
				case 2:
					salir = 1;
					Detenerse();
					break;
				default:
					cout << "ERROR, presione una tecla para continuar!." << endl;
					Detenerse();
					break;
			}
		} else {
			cout << "Llego al limite de contactos permitidos en la agenda." << endl << endl;
		}
	}
	return;
}

void LeerArchivo() {
	ifstream archivo;
	string texto;

	archivo.open("Contactos.txt", ios::in);

	if (archivo.fail()) {
		cout << "No se puedo encontrar el archivo";
		exit(1);
	}

	while (!archivo.eof()) {
		getline(archivo, texto);
		cout << texto << endl;
	}
	
}

void EscribirArchivo(struct Agenda Contacto){
	ofstream archivo;
	
	archivo.open("Contactos.txt",ios::app);
	
	if(archivo.fail()){
		cout<<"No se pudo abri el archivo"<<endl;
		exit(1);
	}
	
	archivo<<"Nombre: "<<Contacto.Nombre<<endl;
	archivo<<"Telefono: "<<Contacto.Telefono<<endl;
	archivo<<"Celular: "<<Contacto.Celular<<endl;
	archivo<<"Email: "<<Contacto.Email<<endl;
	archivo<<"Fecha Nacimiento: "<<Contacto.Fecha.Nacimiento<<endl;
	archivo<<"\n\n";
	
	archivo.close();
}

void Buscar(struct Agenda Contactos[]){
	int x = 0;
	int salir = 0;                                      /*bandera para salir*/
	
	do{ 
		LimpiarPantalla();
	
		do {
			x = BuscarMenuCategoria();				/*Menu para buscar contactos por categorias*/
		} while(x < 1 || x > 5);
		
		switch (x){
			case 1: 
				BuscarPorNombre(Contactos);			/*Buscar por nombre*/
				break;
			case 2:
				BuscarPorTelefono(Contactos);		/*Buscar por telefono*/
				break;
			case 3: 
				BuscarPorCelular(Contactos);		/*Buscar por celular*/
				break;
			case 4: 
				BuscarPorEmail(Contactos);			/*Buscar por email*/
				break;
			case 5:
				salir = Salir();
				break;
			default:
				cout << "ERROR, presione una tecla para continuar!." << endl;
				system("PAUSE>NUL");
				break;
		}
	}
	while(salir == 0);

	Detenerse();
	return;
}

int BuscarMenuCategoria(){
	int x =0 ; 
	
	cout << endl << "\n\t\t     Realizar busqueda por:" << endl << endl;
	cout << "(1)Nombre | (2)Telefono | (3)Celular | (4)Email | (5)Volver" << endl;
	cout << Regla << endl;
	cout << "Esperando respuesta: ";
	cin >> x;
	return x;
}

void BuscarPorNombre(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador en el ciclo*/
	int c = 0;					/*Coincidencias*/
	
	string PorNombre;
	cout << "\n\tDigite el nombre: "<<endl;
	//getline(cin, PorNombre);
	cin >>  PorNombre;
	//cin.ignore();
	cout << endl;
	
	/*Recorrer la cantidad de contactos registrados en la agenda*/
	for (i=0; i < ContactosRegistrados; i++){
		if (Contactos[i].Nombre == PorNombre){				/*Si lo encuentra*/
			Imprimir(Contactos, i);							/*Muestra la informacion del contacto*/
			c++;
			break;
		}
	}
	
	if (c == 0)
		cout << "\n\tEl contacto \"" << PorNombre << "\" no se ha encontrado."<< endl;
	Detenerse();
	return;
}

void BuscarPorTelefono(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;
	
	string PorTelefono;
	cout << "\n\tDigite el numero de telefono: ";
	cin >>  PorTelefono;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Telefono == PorTelefono) ==0){
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}

	if (c == 0){
		cout << "\n\tEl contacto \"" << PorTelefono << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}

void BuscarPorCelular(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;					/*Coincidencias*/
	
	string PorCelular;
	
	cout << "\n\tDigite el numero de celular: ";
	cin >>  PorCelular;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Celular == PorCelular) ==0){
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}
	
	if (c == 0){
		cout << "\n\tEl contacto \"" << PorCelular << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}

void BuscarPorEmail(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;					/*Coincidencias*/
	
	string PorEmail;
	
	cout << "\n\tDigite el Email: ";
	cin >>  PorEmail;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Email == PorEmail) ==0) {
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}
	
	if (c == 0){
		cout << "\n\tEl contacto \"" << PorEmail << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}


void Listar(struct Agenda Contactos[]){
	int i = 0;									/*Iterador del ciclo*/
	int x = 0; 									/*N?mero de contacto*/
	int contactos_restantes = 0;				/*Contactos restantes*/
	
	LeerArchivo();
	
	Detenerse();
	return;
}
void Imprimir(struct Agenda Contactos[], int posicion){
	int x;
	
	/*Imprime el contacto que esta en una posicion especifica de la agenda*/
	cout << "\n\t\tNombre:   " << Contactos[posicion].Nombre << endl;
	cout << "\t\tTelefono: " << Contactos[posicion].Telefono << endl;
	cout << "\t\tCelular:  " << Contactos[posicion].Celular << endl;
	cout << "\t\tEmail:    " << Contactos[posicion].Email << endl;
	cout << "\t\tFecha N.: " << Contactos[posicion].Fecha.Nacimiento << endl << endl;
	
	/*CENTINELA: Opciones Actualizar y Elmiminar contacto*/
	do {
		cout << "\t  Opciones del contacto \"" << Contactos[posicion].Nombre << "\"" << endl;
		cout << "\t(1) Actualizar | (2) Eliminar | (3) Volver " << endl;
		cout << Regla << endl;
		
		cout << "Esperando respuesta: ";
		cin >> x;
		
		cout << endl;
		
	} while(x < 1 || x > 3);
	
	switch (x){
		case 1: 
			Actualizar(Contactos, posicion);				/*Actualiza el contacto seleccionado*/
			break;
		case 2:
			Eliminar(Contactos, posicion);					/*Elimina el contacto seleccionado*/
			break;
		case 3: 
			if (Salir() == 1)
				return;
			break;
		default:
			cout << "\n\tERROR, presione una tecla para continuar!." << endl;
			Detenerse();
			break;
	}
	return;
}

void Actualizar(struct Agenda Contactos[], int posicion){
	int x; 
	string Nombre, Telefono, Celular, Email;			/*Declaracion de variables que almacenaran una copia*/
	int salir = 0;                                      /*bandera para salir*/
	
	do { 												//ActualizarOtroContacto: 
		
		Nombre 	= Contactos[posicion].Nombre;
		Telefono= Contactos[posicion].Telefono;
		Celular = Contactos[posicion].Celular;
		Email 	= Contactos[posicion].Email;
		
		/*Menu para seleccionar que atributos desean actualizar*/
		do {
			cout << "\n\tQue dato le gustaria actualizar de este contacto?" << endl;
			cout << "  (1)Nombre | (2)Telefono | (3)Celular (4)Email | (5)Ninguno" << endl;
			cout << Regla << endl;
			
			cout << "Esperando respuesta: ";
			cin >> x;
			
			cout << endl;
			
		} while(x < 1 || x > 5);
		
		/*Modificacion para los correspondientes atributos seleccionados*/
		switch (x){
			case 1: 
				cout << "\tDigite el nuevo nombre: ";
				cin >>  Contactos[posicion].Nombre;
				cout << "   Se ha actualizado de \"" << Nombre << "\" a " << "\"" << Contactos[posicion].Nombre << "\"" << endl; 
				break;
			case 2:
				cout << "\tDigite el nuevo telefono: ";
				cin >>  Contactos[posicion].Telefono;
				cout << "   Se ha actualizado de \"" << Telefono << "\" a " << "\"" << Contactos[posicion].Telefono << "\"" << endl; 
				break;
			case 3: 
				cout << "\tDigite el nuevo celular: ";
				cin >>  Contactos[posicion].Celular;
				cout << "   Se ha actualizado de \"" << Celular << "\" a " << "\"" << Contactos[posicion].Celular << "\"" << endl; 
				break;
			case 4: 
				cout << "\tDigite el nuevo email: ";
				cin >>  Contactos[posicion].Email;
				cout << "   Se ha actualizado de \"" << Email << "\" a " << "\"" << Contactos[posicion].Email << "\"" << endl; 
				break;
			case 5: 
				salir = Salir();
				break;
			default:
				cout << "\n\tERROR, presione una tecla para continuar!." << endl;
				Detenerse();
				break;
		}
	}
	while(salir == 0);
	
	return;
}

void Eliminar(struct Agenda Contactos[], int posicion){
	string Nombre;
	
	Nombre = Contactos[posicion].Nombre;
	
	/*Despues de ejecutar la centinela, se resetean los valores de esa posicion
	  y no se vuelven a tomar en cuenta. Este algoritmo esta trabajado para que 
	  no perjudique en ningun momento en la ejecucion del programa.
	*/
	if (Salir() == 1){
		Contactos[posicion].Nombre 	= " ";
		Contactos[posicion].Telefono= "0";
		Contactos[posicion].Celular	= "0";
		Contactos[posicion].Email	= " ";
		ContactosEliminados++;
		
		cout << "\nEl contacto \"" << Nombre <<  "\" ha sido eliminado con exito!\n\n";
	}
	
	return;
}

int VerificarContacto(struct Agenda Contactos[], string Nombre){
	int i = 0; 
	int c = 0;
	
	/*Verifica si existe un contacto en especifico*/
	for (; i < ContactosRegistrados; i++){
		if (Contactos[i].Nombre == Nombre){
			c++;
			break;
		}
	}
	
	if (c == 0)
		return false;
	
	return true;
}

void CargarContactos(struct Agenda Contactos[]){
	int x;
	
	/*Cargar datos por omision para realizar pruebas rapidas de las opciones
	  que presenta este programa sobre la gesti?n de contactos de la Agenda.
	*/
	do {
		LimpiarPantalla();
			
		cout << Regla << endl;
		cout << "|\tBienvenido a tu Agenda Electronica de Contactos\t    |" << endl;
		cout << Regla << endl;
			
		cout << "(1) Cargar contactos previos | (2) Nueva agenda | (3) Salir |" << endl;
		cout << Regla << endl;
			
		cout << "Esperando respuesta: ";
		cin >> x;
		
			
	} while(x < 1 || x > 3);
		
	switch (x){
		case 1: 
			/*Primer contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Odaliz";
			Contactos[ContactosRegistrados].Telefono 		= "084 45127";
			Contactos[ContactosRegistrados].Celular 		= "+51 913 365 389";
			Contactos[ContactosRegistrados].Email 			= "odalizangie@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "17/10/2002";
			EscribirArchivo(Contactos[ContactosRegistrados]);
			ContactosRegistrados++;
			
			/*Segundo contacto*/
            Contactos[ContactosRegistrados].Nombre          = "Patrick";
            Contactos[ContactosRegistrados].Telefono        = "084 568923";
            Contactos[ContactosRegistrados].Celular         = "+51 945 781 221";
            Contactos[ContactosRegistrados].Email           = "patrick@gmail.com";
            Contactos[ContactosRegistrados].Fecha.Nacimiento= "22/08/2000";
            EscribirArchivo(Contactos[ContactosRegistrados]);
            ContactosRegistrados++;
			break;
		case 2:
			cout<<"Iniciando agenda.."<<endl;
			break;

		case 3: 
			if (Salir() == 1)
				return;
		default:
			cout << "\n\tERROR , presione una tecla para continuar!." << endl;
			Detenerse();
			break;
	}
	
	return;
}

bool HayContactos(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador*/
	int c = 0;					/*Coincidencias*/
	
	/*Verifica si hay contactos disponibles*/
	for (i =0 ; i < CANTIDAD; i++)
		if (Contactos[i].Nombre != " ")
			c++;
	
	if (c > 0)
		return true; //Esta vacio
	
	return false;
}

void Detenerse(){
	cout << "\t=Presione una tecla para continuar!";
	system("PAUSE");								/*Pausar la aplicacion sin mensaje de salida*/
}

void LimpiarPantalla(){
	system("CLS");									/*Limpiar pantalla*/
}

void Dormir(int x){
	Sleep(x * 1000);							/*Dormir el programa*/
}

int Salir(){
	int x;
	
	/*Centinela general*/
	do {
		cout << "\n\tEsta seguro(a) de querer salir?" << endl;
		cout << "\t(1) Si, (2) No: ";
		cin >> x;
		
	} while(x < 1 || x > 2);
	
	cout << endl;
	
	return x;
}
