#include <stdio.h>

int day_of_week (int , int , int );
int leap_year (int );
int days_in_date (int , int , int );
int number_of_week (int , int , int );
int days_in_month (int , int );
char* name_day_of_week (int , int , int );

int main () {
	int day = 7;
	int month = 5;
	int year = 2020;
	int i, j;

	for (i = 1; i <= month; i++) {
		for (j = 1; j <= days_in_month(i, year); j++) {
			printf ("\nEl %d-%d-%d (%s) corresponde a la semana nro %d", 
				j, i, year, name_day_of_week(j, i, year), number_of_week (j, i, year));
			if (j == day && i == month)
				break;
		}
	}

	return 0;
}

/* Retorna el nro. de días que tiene un mes
   Se asume que month > 0 y < 13 */
int days_in_month (int month, int year) {
	int count_days_in_month[] = 
		{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	return ((month == 2 && leap_year (year) == 1) ? 
		count_days_in_month[month] + 1 : 
			count_days_in_month[month]);
}

int number_of_week (int day, int month, int year) {
	/* El algoritmo para el nro de la semana
	1- Sumar los días hasta el día de la fecha
	2- Si 01/enero es:
		sábado, sumarle 6
		viernes, sumarle 5
		...
		lunes, sumarle 1
	3- Dividir el resultado por el nro. 7
	4- Si el resto de la división no es cero, 
	   sumarle 1 y así obtendremos el nro de semana */
	int op = days_in_date (day, month, year);
	op += day_of_week (1, 1, year);
	int result = op / 7;
	int rest = op % 7;
	if (rest > 0)
		result++;

	return result;
}

/* Retorna la cantidad de días entre el 1/1 
   hasta el día de la fecha pasada por parámetro */
int days_in_date (int day, int month, int year) {
	int days = 0;
	int i;
	
	for (i = 1; i < month; i++) 
		days += days_in_month(i, year);
	days += day;

	return days;
}

/* Retorna 1 si el año es bisiesto */
int leap_year (int year) {
	if ((year % 4 == 0) && !(year % 100 == 0)) {
    	return 1;
	}
	else if (year%400==0) {
    	return 1;
	}
	else {
    	return 0;
	}
}

char* name_day_of_week (int day, int month, int year) {
	switch (day_of_week (day, month, year)) {
		case 6: return "sabado";
			break;
		case 5: return "viernes";
			break;
		case 4: return "jueves";
			break;
		case 3: return "miércoles";
			break;
		case 2: return "martes";
			break;
		case 1: return "lunes";
			break;
		case 0: return "domingo";
			break;
	}
}

/* Retorna un entero que indica el día de la semana
   6 sabado, 5 viernes, ... 0 domingo 
   Fuente: https://programador-apli.blogspot.com/2012/04/calcular-el-dia-de-la-semana-partir-de.html*/
int day_of_week (int day, int month, int year) {
	// Declaracion de vectores y variables
	int regular[]={0,3,3,6,1,4,6,2,5,0,3,5};
	int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6};

	// Para simplificar el algoritmo 
	// vamos a dividirlo en partes más pequeñas
	int result1,result2,result3,result4,result5;


	// Comprobamos primero si el año es bisiesto o es regular
	// Si es bisiesto, asignamos a m la posición del vector bisiesto -1
	// Si es regular, asignamos a m la posición del vector regular -1
	if (leap_year(year) == 1)
		month = bisiesto[month-1];
	else
		month = regular[month-1];

	//Resolvermos la fórmula poco a poco
	result1=(year-1)%7;
	result2=(year-1)/4;
	result3=(3*(((year-1)/100)+1))/4;
	result4=(result2-result3)%7;
	result5=day%7;
	day=(result1+result4+month+result5)%7;

	return day;
}
