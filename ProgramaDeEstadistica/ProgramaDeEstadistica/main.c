/*
Programa: Programa de estadisticas.
Programador: Luis Ángel De Santiago Guerrero
Descripción del programa: Este es un programa de tipo estadistico y sirve de herramienta para el
análisis de datos obtenidos de algún tipo de encuenta o censo.
Obtiene la tabla de frecuencias que incluye: la Frecuencia, Frecuencia Acumulada, Frecuencia relativa,
y Frecuencia relativa acumulada de una muestra de n datos proporcionados por el usuario.

Fecha de modificación: 24 de Enero 2019 - Simplemente he comentado algunas de las funciones y arreglando
																					el código de forma estética.

Fecha de creación: Marzo de 2016
Universidad: Universidad Abierta y a Distancia de México
Licenciatura: Ingeniería en Desarrollo de Software
Matrícula: ES16300455
Contacto: ES1611300455@unadmexico.mx
*/

#include "rlutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
 * ─── GLOBAL VARIABLES ───────────────────────────────────────────────────────────
 */

// Máxima longitud para todos los arreglos
#define MAX_LENGHT 150

// Variable usada para terminar de ingresar los datos 
int	 cancelar = 1;								

// Es el conjunto de datos ingresados por el usuario
int  Datos[MAX_LENGHT] = { 0 };					

// El tipo de variable, pide el nombre de la variable a medir, edad, número de hijos, etc... 
char NombreVariable[MAX_LENGHT] = { '\0' };		

// Constantes usadas para los acentos

const char a = 160;
const char e = 130;
const char iacen = 161;
const char o = 162;
const char u = 163;
const char enhe = 164;
const char A = 181;


/*
 * ─── FUNCIONES PROTOTIPO ────────────────────────────────────────────────────────
 */

// Función para mostrar las opciones del programa
void menu();

// Función que le permite al usuario ingresar datos
void ingresoDeDatos();

// Función que muestra una demostración del comportamiento del programa
void demo();

// Función para validar los datos ingresados por el usuario
int validarDatos(char CadenaTexto[MAX_LENGHT]);


// Función utilizada para mostrar puntos (para un fin estético)
void puntitos(int velocidad, int cantidad);		


/*
 * ─── MAIN FUNCTION ──────────────────────────────────────────────────────────────
 */
main()
{
	cancelar = 1;

	// Inicialmente carga el menú
	menu();

	// Muestra los datos ingresados de forma desordenada
	system("cls");
	setColor(CYAN);
	printf("Variable: %s", NombreVariable);

	gotoxy(60, 1);
	setColor(GREEN);
	printf("Resultado final.");

	gotoxy(0, 0);
	setColor(WHITE);
	printf("\n\t\t\tPrograma estadistico\n\n");

	printf("\n\nDatos desordenados: {\n");
	setColor(YELLOW);
	int _totalElementosNoOrdenados = 0;
	for (int i = 0; i < (int)sizeof(Datos) / (int)sizeof(Datos[0]); i++)
	{
		if (Datos[i] != 0)
		{
			printf("%d,	", Datos[i]);
			_totalElementosNoOrdenados++;
		}
	}
	setColor(WHITE);
	printf("}\nTotal de elementos: %d\n", _totalElementosNoOrdenados);


	/*
	 * ──────────────────────────────────────────────────────────────────── I ──────────
	 *   :::::: O R D E N   D E   D A T O S : :  :   :    :     :        :          :
	 * ──────────────────────────────────────────────────────────────────────────────
	 * 
	 * Obtiene el número mayor de los datos, 
	 * con el fin de después ordenarlos de forma ascendente
	 * 
	 */
	int numeroMayor = 0;

	// Posiciona a numMayor al incio del arrglo para comparar uno por uno los elementos
	numeroMayor = Datos[0];		

	for (int i = 0; i < (int)sizeof(Datos) / (int)sizeof(Datos[0]); i++)
	{
		if (numeroMayor < Datos[i])
		{
			numeroMayor = Datos[i];
		}
	}


	/*
	 * ──────────────────────────────────────────────────────────────────── II ──────────
	 *   :::::: O R D E N   D E   D A T O S : :  :   :    :     :        :          :
	 * ──────────────────────────────────────────────────────────────────────────────
	 * 
	 * Recorre el arreglo de datos colocando los números ordenados en el _ArregloAuxiliar
	 * 
	 */

	// Registra los datos dados por el usuario, de forma no ordenada
	int		_ArregloAuxiliar[MAX_LENGHT] = { 0 };		
	int _totalNumerosOrdenados = 0;
	
	setColor(WHITE);
	printf("\nDatos ordenados: {\n");
	
	for (int i = 1, k = 0, color = 1; i <= numeroMayor; i++, color++)
	{
		// i recorre todos los valores ingresados hasta el número mayor
		for (int j = 0; j < (int)sizeof(Datos) / (int)sizeof(Datos[0]); j++)
		{
			//
			// Para el primer valor de la variable i, hace un recorrido completo,
			// ¿Quién es igual a 1...?, ¿Quién es igual a dos...?, 
			// así sucesivamente hasta el número mayor ingresado
			//
			if (Datos[j] == i)
			{
				setColor(color);
				_ArregloAuxiliar[k] = Datos[j];
				printf("%d,\t", _ArregloAuxiliar[k]);
				k++;
				_totalNumerosOrdenados++;
			}
			if (color > 14)  color = 1;
		}
	}
	setColor(WHITE);
	printf("}\n");
	printf("Total de elementos ordenados: %d\n", _totalNumerosOrdenados);


	// DATOS: Remueve los elementos repetidos, y los coloca en el Arreglo_A
	// Arreglo en donde se almacenan los datos finales, no repetidos de forma ordenada
	int		Arreglo_A[MAX_LENGHT] = { 0 };				
	int		datoDeArreglo = 0;

	for (int i = 0, j = 0; i < (int)sizeof(_ArregloAuxiliar) / (int)sizeof(_ArregloAuxiliar[0]); i++)
	{
		datoDeArreglo = _ArregloAuxiliar[i];
		if (datoDeArreglo != 0)
		{
			if (datoDeArreglo != _ArregloAuxiliar[i + 1])
			{
				Arreglo_A[j] = datoDeArreglo;
				j++;
			}
		}
	}

	/*
	 * ─── FRECUENCIA DE NÚMEROS ──────────────────────────────────────────────────
	 */

	int		Frecuencia[MAX_LENGHT] = { 0 };

	// Se posiciona el datoDeArreglo en el primer elemento del arreglo 
	datoDeArreglo = _ArregloAuxiliar[0];		

	int indiceFrecuencia = 0;

	Frecuencia[indiceFrecuencia] = 0;

	for (int indice = 0; indice < (int)sizeof(_ArregloAuxiliar) / (int)sizeof(_ArregloAuxiliar[0]); indice++)
	{
		if (_ArregloAuxiliar[indice] != 0)
		{
			if (datoDeArreglo == _ArregloAuxiliar[indice])
			{
				// printf("\nDato %d = %d.\tFrecuencia = %d", datoDeArreglo, _ArregloAuxiliar[indice], Frecuencia[indiceFrecuencia]);
				Frecuencia[indiceFrecuencia]++;
			}
			else
			{
				// printf("\nDato %d != %d.", datoDeArreglo, _ArregloAuxiliar[indice]);
				datoDeArreglo = _ArregloAuxiliar[indice];
				
				// printf("\nDato = %d", datoDeArreglo);
				Frecuencia[indiceFrecuencia++];
				
				// Se repite por lo menos una vez
				Frecuencia[indiceFrecuencia]++; 
			}
		}
	}


	/*
	 * ─── FRECUENCIA ACOMULADA ───────────────────────────────────────────────────────
	 */
	int FrecuenciaAcumulada[MAX_LENGHT] = { 0 };

	// Valor inicial
	int ValorInicial = Frecuencia[0]; 

	int totalDatos = 0;

	for (int i = 0, j = 0; i < (int)sizeof(Frecuencia) / (int)sizeof(Frecuencia[0]); i++)
	{
		if (i < 1)
		{
			FrecuenciaAcumulada[j] = ValorInicial;
			j++;
		}
		else
		{
			if (Frecuencia[i] != 0)
			{
				FrecuenciaAcumulada[j] = FrecuenciaAcumulada[j - 1] + Frecuencia[i];
				totalDatos = FrecuenciaAcumulada[j];
				j++;
			}
		}
	}


	/*
	 * ─── FRECUENCIA RELATIVA ────────────────────────────────────────────────────────
	 */
	double	FrecuenciaRelativa[MAX_LENGHT] = { 0 };

	double _totalSumaFrecuenciaRelativa = 0;

	for (int i = 0; i < MAX_LENGHT; i++)
	{
		if (Frecuencia[i] != 0)
		{
			FrecuenciaRelativa[i] = (double)Frecuencia[i] / totalDatos;
			/*printf("\nFrecuencia Relativa: %f = %d/%d", FrecuenciaRelativa[i], Frecuencia[i], totalDatos);*/
			_totalSumaFrecuenciaRelativa += FrecuenciaRelativa[i];
		}
	}


	/*
	 * ─── FRECUENCIA RELATIVA ACOMULADA ──────────────────────────────────────────────
	 */
	double	FrecuenciaRelativaAcumulada[MAX_LENGHT] = { 0 };

	for (int i = 0; i < MAX_LENGHT; i++)
	{
		FrecuenciaRelativaAcumulada[i] = (double)FrecuenciaAcumulada[i] / totalDatos;
		/*printf("\nFrecuencia RelativaAcumulada: %f = %d/%d", FrecuenciaRelativaAcumulada[i], FrecuenciaAcumulada[i], totalDatos);*/
	}


	/*
	 * ─── SE MUESTRA LA TABLA ────────────────────────────────────────────────────────
	 */
	printf("\nRenglon\tDatos\tFrecuencia\tFrecuenAcu\tFrecRel\t\tFrecRelAcu\n");
	setColor(GREEN);

	for (int i = 0, indice = 0; indice < MAX_LENGHT; i++, indice++)
	{
		if (Arreglo_A[indice] != 0)
		{
			printf("  [%d]\t|", indice + 1);												/* Renglon*/
			printf("%d\t|", Arreglo_A[indice]);											/* Datos */
			printf("%d\t\t|", Frecuencia[indice]);									/* Frecuencia*/
			printf("%d\t\t|", FrecuenciaAcumulada[indice]);					/* Frecuencia Acumulada*/
			printf("%.4f\t\t|", FrecuenciaRelativa[indice]);				/* Frecuenca Relativa */
			printf("%.4f\n", FrecuenciaRelativaAcumulada[indice]);	/* Frecuencia Relativa Acumulada */
			Sleep(500);
		}

	}
	printf("  Total:\t %d\t\t\t\t %.4f \n", totalDatos, _totalSumaFrecuenciaRelativa);
	system("pause");

	// Limpiando la pantalla
	cls();
	setColor(CYAN);
	gotoxy(1, 10);
	printf(" Sobre-escribiendo las bases de datos");
	puntitos(100, 20);

	for (int i = 0; i < (int)sizeof(Datos) / (int)sizeof(Datos[0]); i++)
	{
		Datos[i] = 0;
	}
	
	// Comienza de nuevo el proceso llamánsose a sí misma
	main();
}



/* ──────────────────────────────────────────────────────────────────────────────── */
/*
 * ─── CUERPO DE FUNCIONES PROTOTIPO ──────────────────────────────────────────────
 *
 * ──────────────────────────────────────────────────────────────────────────────── */

/**
 * @brief Función para mostrar las opciones del programa
 * 
 */
void menu()
{
	setColor(WHITE);
	hidecursor();
	
	char opcion;
	char texto[] = { "Acerca de este programa : \n\nEl programa que usted esta usando es de tipo estadistico y sirve de herramienta para el analisis de datos obtenidos de alguna encuesta o censo\nUsted obtendra la tabla de frecuencias que incluye la \"Frecuencia\", \"Frecuencia acumulada\", \"Frecuencia relativa\" y \"Frecuencia relativa acumulada\" de una muestra de datos ingresados por usted.\n\nComo usar:\n\nPara comenzar a utilizar el programa, es necesario que usted se dirija al menu principal, y seleccione, \"iniciar\", el sistema le pedira que ingrese el nombre de la variable, solo y unicamente en ese justo momento es posible que usted pueda cancelar la accion presionando la combinacion de telcas \"CONTROL+C\" ya que despues no sera posible, despues usted ingresara los datos uno por uno, despues de haber ingresado un dato el sistema mostrara un mensaje que le dara las opciones de continuar ingresando datos presionando la tecla ENTER, o dejar de ingresar datos presionando la tecla ESCAPE\n\n " };

	system("cls");
	puts("\n\tPrograma de estadistica\n");
	puts("a. Ayuda");
	puts("b. Iniciar");
	puts("c. Demo");
	puts("d. Salir");
	printf(":");
	opcion = _getche();
	fflush(stdin);

	switch (opcion)
	{
	case 'a':
		system("cls");
		puts("\n\tPrograma de estadistica\n\n");
		printf("%s", texto);
		setColor(LIGHTMAGENTA);
		printf("\nAutor: Luis %cngel De Santiago Guerrero\n", A);
		printf("Matricula: ES1611300455\n");
		printf("Contacto:  ES1611300455@unadmexico.mx\n");
		printf("Universidad Abierta y a Distancia de M%cxico\n", e);
		printf("Ingenier%ca en Desarrollo de Software\n\n", iacen);
		system("pause");
		main();
		break;

	case 'b':
		ingresoDeDatos();
		break;
	
	case 'c':
		demo();
		break;
	
	case 'd':
		printf("\n\n\t\t\tAdios");
		puntitos(500, 3);
		exit(0);
		break;

	default:
		setColor(RED);
		printf("\nIngrese una opcion valida\n");
		system("pause");
		main();
		break;
	}
}


/**
 * @brief Función para capturar los datos de entrada del usuario
 * 
 */
void ingresoDeDatos()
{
	// Mientras sea 1, se mantiene en el bucle
	int salir = 0;		

	// Se almacenan las entradas del teclado
	int entrada = 1;	
					
	setColor(WHITE);
	system("cls");
	printf("\n\t\t\tPrograma estadistico");
	printf("\n\nIngrese el nombre de la variable: ");
	gets(NombreVariable);
	printf("Variable \"%s\" registrada!\n\n", NombreVariable);
	Sleep(500);

	gotoxy(60, 1);
	setColor(CYAN);
	printf("Iniciando...", o);
	gotoxy(3, 10);
	setColor(YELLOW);
	printf("Cargando programa");
	puntitos(200, 5);
	printf("\n\n  Programa listo, presiona enter para continuar!");

	gotoxy(1, 20);
	setColor(RED);
	hidecursor();
	printf("si deseas cancelar, presiona: CONTROL+C");
	entrada = _getche();

	if (entrada == 3) { main(); }


	int indiceDato = 0;

	do
	{
		setColor(WHITE);
		char Dato_cadena[MAX_LENGHT] = { '\0' };
		system("cls");
		setColor(CYAN);
		printf("Variable: %s", NombreVariable);
		gotoxy(60, 1);
		setColor(GREEN);
		printf("En ejecuci%cn.", o);
		gotoxy(0, 0);
		setColor(WHITE);
		printf("\n\t\t\tPrograma estadistico\n\n");
		showcursor();
		printf("Ingresa el dato cuantitativo a registrar:");
		gets(Dato_cadena);

		if (validarDatos(Dato_cadena))
		{
			/* Convierte el Dato_cadena a entero*/
			Datos[indiceDato] = atoi(Dato_cadena);
			indiceDato++;

			/* Muestra los datos ingresados en pantalla */
			for (int i = 0; i < (int)sizeof(Datos) / (int)sizeof(Datos[0]); i++)
			{
				if (Datos[i] != 0)
				{
					printf(" %d, ", Datos[i]);
				}
			}
			gotoxy(4, 15);
			printf("ESCAPE para terminar");
			printf("\t\t\tENTER para continuar");

			/* Escucha las pulsaciones del teclado */
			for (;;)
			{
				hidecursor();
				entrada = getkey();
				/*printf("%d\n", entrada);*/
				if (entrada == 0)				/* ESCAPE  0*/
				{
					salir = 0; break;
				}
				if (entrada == 1)				/* ENTER 1*/
				{
					salir = 1; break;
				}
			}
		}
		else
		{
			salir = 1;
		}
		showcursor();

	} while (salir == 1);
}


/**
 * @brief Función para demostración del comportamiento del programa
 * 
 */
void demo()
{
	/* VARIABLES LOCALES DEMO */
	int DatosDelDemo[] = {
												816, 810, 856, 888,
												833, 817, 839, 853,
												811, 837, 881, 873,
												889, 836, 815, 860,
												888, 830, 888, 830,
												881, 844, 830, 831,
												840, 844, 840, 814,
												841, 858, 810, 888,
												883, 835, 884, 849,
												882, 856, 888, 833,
												869, 835, 835, 884,
												849, 850, 844, 840,
												858, 853, 837, 881,
												873, 889, 836, 815,
												840, 838, 874, 831,
												845, 812, 819, 887,
												842, 854, 871, 841,
												838, 814, 859, 810
												};

	// Muestra los datos ingresados de forma desordenada
	cls();

	for (int i = 0, color = 1; i < 30; i++, color++)
	{
		locate(2, (trows() / 2));
		(i < 15) ? printf("Cargando componentes principales") : printf("Estamos iniciando");
		puntitos(i, i);
		setColor(color);
		if (color > 14) color = 1;

	}
	
	cls();
	setColor(CYAN);
	printf("Variable: PROGRAMA DEMO");

	gotoxy(60, 1);
	setColor(GREEN);
	printf("Resultado final.");

	gotoxy(0, 0);
	setColor(WHITE);
	printf("\n\t\t\tPrograma estadistico\n\n");

	setColor(YELLOW);
	printf("\n\nDatos desordenados: {\n");
	
	int _totalElementosNoOrdenados = 0;
	
	for (int i = 0; i < (int)sizeof(DatosDelDemo) / (int)sizeof(DatosDelDemo[0]); i++)
	{
		if (DatosDelDemo[i] != 0)
		{
			Sleep(100);
			printf("%d,	", DatosDelDemo[i]);
			_totalElementosNoOrdenados++;
		}
	}
	
	printf("}\nTotal de elementos: %d\n", _totalElementosNoOrdenados);


	/*
	 * ──────────────────────────────────────────────────────────────────────── I ──────────
	 *   :::::: O R D E N   A S C E N D E N T E : :  :   :    :     :        :          :
	 * ──────────────────────────────────────────────────────────────────────────────────
	 * 
	 * Obtiene el número mayor de los datos, con el fin de después ordenarlos de forma ascendente
	 * 
	 */
	int numeroMayor = 0;
	numeroMayor = DatosDelDemo[0];

	for (int i = 0; i < (int)sizeof(DatosDelDemo) / (int)sizeof(DatosDelDemo[0]); i++)
	{
		if (numeroMayor < DatosDelDemo[i])
		{
			numeroMayor = DatosDelDemo[i];
		}
	}

	/*
	 * ──────────────────────────────────────────────────────────────────── II ──────────
	 *   :::::: O R D E N   D E   D A T O S : :  :   :    :     :        :          :
	 * ──────────────────────────────────────────────────────────────────────────────
	 */
	int		_ArregloAuxiliar[MAX_LENGHT] = { 0 };

	int _totalNumerosOrdenados = 0;

	setColor(WHITE);
	printf("\nDatos ordenados: {\n");

	for (int i = 1, k = 0, color = 1; i <= numeroMayor; i++, color++)
	{
		for (int j = 0; j < (int)sizeof(DatosDelDemo) / (int)sizeof(DatosDelDemo[0]); j++)
		{
			if (DatosDelDemo[j] == i)
			{
				setColor(color);
				_ArregloAuxiliar[k] = DatosDelDemo[j];
				Sleep(100);
				printf("%d,\t", _ArregloAuxiliar[k]);
				k++;
				_totalNumerosOrdenados++;
			}
		}
		if (color > 14)  color = 1;
	}
	
	setColor(WHITE);
	printf("}\n");
	printf("Total de elementos ordenados: %d\n", _totalNumerosOrdenados);


	/*
	 * ────────────────────────────────────────────────────────────────────────────────────── III ──────────
	 *   :::::: E L I M I N A   D A T O S   R E P E T I D O S : :  :   :    :     :        :          :
	 * ────────────────────────────────────────────────────────────────────────────────────────────────
	 */
	int		Arreglo_A[MAX_LENGHT] = { 0 };
	int		datoDeArreglo = 0;
	
	for (int i = 0, j = 0; i < (int)sizeof(_ArregloAuxiliar) / (int)sizeof(_ArregloAuxiliar[0]); i++)
	{
		datoDeArreglo = _ArregloAuxiliar[i];
		if (datoDeArreglo != 0)
		{
			if (datoDeArreglo != _ArregloAuxiliar[i + 1])
			{
				/*printf("%d\n", datoDeArreglo);*/
				Arreglo_A[j] = datoDeArreglo;
				j++;
			}
		}
	}

	/*
	 * ─── FRECUENCIA DE LOS NUMEROS ──────────────────────────────────────────────────
	 */
	int		Frecuencia[MAX_LENGHT] = { 0 };
	datoDeArreglo = _ArregloAuxiliar[0];
	int indiceFrecuencia = 0;
	Frecuencia[indiceFrecuencia] = 0;
	for (int indice = 0; indice < (int)sizeof(_ArregloAuxiliar) / (int)sizeof(_ArregloAuxiliar[0]); indice++)
	{
		if (_ArregloAuxiliar[indice] != 0)
		{
			if (datoDeArreglo == _ArregloAuxiliar[indice])
			{
				/*printf("\nDato %d = %d.\tFrecuencia = %d", datoDeArreglo, _ArregloAuxiliar[indice], Frecuencia[indiceFrecuencia]);*/
				Frecuencia[indiceFrecuencia]++;
			}
			else
			{
				/*printf("\nDato %d != %d.", datoDeArreglo, _ArregloAuxiliar[indice]);*/
				datoDeArreglo = _ArregloAuxiliar[indice];
				/*printf("\nDato = %d", datoDeArreglo);*/
				
				Frecuencia[indiceFrecuencia++];

				Frecuencia[indiceFrecuencia]++;
			}
		}
	}

	/*
	* ─── FRECUENCIA ACUMULADA ───────────────────────────────────────────────────────
	*/

	int FrecuenciaAcumulada[MAX_LENGHT] = { 0 };

	int ValorInicial = Frecuencia[0];

	int totalDatosDelDemo = 0;

	for (int i = 0, j = 0; i < (int)sizeof(Frecuencia) / (int)sizeof(Frecuencia[0]); i++)
	{
		if (i < 1)
		{
			FrecuenciaAcumulada[j] = ValorInicial;
			j++;
		}
		else
		{
			if (Frecuencia[i] != 0)
			{
				FrecuenciaAcumulada[j] = FrecuenciaAcumulada[j - 1] + Frecuencia[i];
				totalDatosDelDemo = FrecuenciaAcumulada[j];
				j++;
			}
		}
	}


	/*
	 * ─── FRECUENCIA RELATIVA ────────────────────────────────────────────────────────
	 */
	double	FrecuenciaRelativa[MAX_LENGHT] = { 0 };

	double _totalSumaFrecuenciaRelativa = 0;

	for (int i = 0; i < MAX_LENGHT; i++)
	{
		if (Frecuencia[i] != 0)
		{
			FrecuenciaRelativa[i] = (double)Frecuencia[i] / totalDatosDelDemo;
			/*printf("\nFrecuencia Relativa: %f = %d/%d", FrecuenciaRelativa[i], Frecuencia[i], totalDatosDelDemo);*/
			_totalSumaFrecuenciaRelativa += FrecuenciaRelativa[i];
		}
	}


	/*
	* ─── FRECUENCIA RELATIVA ACOMULADA ──────────────────────────────────────────────
	*/
	double	FrecuenciaRelativaAcumulada[MAX_LENGHT] = { 0 };
	for (int i = 0; i < MAX_LENGHT; i++)
	{
		FrecuenciaRelativaAcumulada[i] = (double)FrecuenciaAcumulada[i] / totalDatosDelDemo;
		/*printf("\nFrecuencia RelativaAcumulada: %f = %d/%d", FrecuenciaRelativaAcumulada[i], FrecuenciaAcumulada[i], totalDatosDelDemo);*/
	}


	/*
	 * ─── MUESTRA LOS DATOS EN FORMA DE TABLA ────────────────────────────────────────
	 */
	setColor(WHITE);
	printf("\nRenglon\tDatos\tFrecuencia\tFrecuenAcu\tFrecRel\t\tFrecRelAcu\n");
	setColor(GREEN);

	for (int i = 0, indice = 0; indice < MAX_LENGHT; i++, indice++)
	{
		if (Arreglo_A[indice] != 0)
		{
			printf("  [%d]\t|", indice + 1);						/* Renglon*/
			printf("%d\t|", Arreglo_A[indice]);						/* DatosDelDemo */
			printf("%d\t\t|", Frecuencia[indice]);					/* Frecuencia*/
			printf("%d\t\t|", FrecuenciaAcumulada[indice]);			/* Frecuencia Acumulada*/
			printf("%.4f\t\t|", FrecuenciaRelativa[indice]);		/* Frecuenca Relativa */
			printf("%.4f\n", FrecuenciaRelativaAcumulada[indice]);	/* Frecuencia Relativa Acumulada */
			Sleep(100);
		}

	}
	printf("  Total:\t %d\t\t\t\t %.4f \n", totalDatosDelDemo, _totalSumaFrecuenciaRelativa);
	system("pause");

	/*
	 * ─── CREDITOS ───────────────────────────────────────────────────────────────────
	 */
	cls();
	setColor(CYAN);
	gotoxy(1, 10);
	printf(" Luis %cngel De Santiago Guerrero\n", A);
	puntitos(100, 30);

	main();
}


/**
 * @brief Función para validar
 * los datos ingresados por el usuario
 * 
 * @param CadenaTexto Dato que evaluará.
 * @return int 
 */
int validarDatos(char CadenaTexto[MAX_LENGHT])
{
	int i = 0;
	int datoValido = 1;

	while (CadenaTexto[i])
	{
		if (!isdigit(CadenaTexto[i]))
		{
			setColor(RED);
			printf("\n\t\tEl formato: \"%s\" no es un formato aceptable\n", CadenaTexto);
			system("pause");
			datoValido = 0;
			break;
		}
		else
		{
			int digito = CadenaTexto[i];
			if (digito == 0)
			{
				setColor(RED);
				printf("\n\t\tNo ingreses ceros\n", CadenaTexto);
				system("pause");
				datoValido = 0;
				break;
			}
			else
			{
				datoValido = 1;
			}
		}
		i++;
	}
	return datoValido;
}


/**
 * @brief Función estética para simular el procesamiento
 * 
 * @param velocidad Variable para establecer la velocidad de impresión.
 * @param cantidad 	Cantidad de puntos que se imprimirán.
 */
void puntitos(int velocidad, int cantidad)
{
	for (int i = 0; i < cantidad; i++)
	{
		printf(".");
		Sleep(velocidad);
	}
}