/***********************************************************/
/*                                                         */
/*      Base program for Monte-Karlo Method                */
/*      Olexandr Selin (c) 2002                            */
/*      http://selin.kiev.ua                               */
/*      e-mail: oselin@mmsa.ntu-kpi.kiev.ua                */
/*                                                         */
/***********************************************************/
#include "stdafx.h"

#include <fstream>
#include <math.h>
#include <stdlib.h>

#include <ctime>
#include <iostream>

//  (  знаком + позначено  )
using namespace std;
//  (  рядки, якi треба    )
const double                     // Програма обчислює об'єм пiвсфери         ( змiнити за варiантом )
//r = 1.0,
h = 1,                     // радiусу r з центром у (0; 0; 0).                          +
x1 = 0, x2 = 1,               // Тодi її можна вписати у паралелепiпед                  +
y11 = 0, y2 = 1,               // з координатами по x та y вiд -r до +r,                +
z1 = 0, z2 = +h,            // а по z - вiд 0 до +r.                                    +

V1 = (x2 - x1)*(y2 - y11)*(z2 - z1),  // Об'єм описаного паралелепiпеда.
V2 = 0.5,                      // Об'єм вписаного конуса.                            +
Vexact = (M_PI) / 2,               // Точне значення об'єму пiвсфери.                 +

p2 = V2 / V1,                    // Ймовiрнiсть потрапити до конусу.

m = 0.01,                      // Вiдносна помилка обчислення надiйного iнтервалую
za = 1.96,                     // za: Ф(z) = alpha = 0,95.   +/- 3.4e-5

N = (za*za) / (m*m)*(1 - p2) / p2;   // Кiлькiсть точок, що їх треба згенерувати.

double
p,                             // Ймовiрнiсть потрапити до пiвсфери.
V,                             // Оцiнка об'єму пiвсфери.
x, y, z,                         // координати випадкової точки.
mnew;                          // Нове значення вiдносної помилки.

unsigned long i, j,
Nx = 0;                          // Кiлькiсть точок, що потрапляють до пiвсфери.

int InBody(double x, double y, double z) {  // Перевiрка належностi точки до пiвсфери.
	//if (1 >= z && 0 <= z && x >= 1-y && x <= sqrt(1-y*y))    //                           +
	if (1 >= y && 0 <= y && x >= 0 && x <= sqrt(1 - y*y) && z <=0 && z >= 1/(sqrt(1-x*x-y*y)))
		return 1;  // true
	else return 0;  // false
}

ofstream fout("MonteCar.txt");// , ios::app);

int main() {

	//randomize();
	srand(time(0));

	for (i = 1; i <= N; i++) {
		// Згенерувати випадкову точку, 0 <= rand()/RAND_MAX < 1
		
		x = (x2 - x1) * (rand() % RAND_MAX) / RAND_MAX + x1; // x1 <= x <= x2;
		y = (y2 - y11) * (rand() % RAND_MAX) / RAND_MAX + y11; // y11 <= y <= y2;
		z = (z2 - z1) * (rand() % RAND_MAX) / RAND_MAX + z1; // z1 <= z <= z2;
		
		if (InBody(x, y, z)) Nx++;               // Якщо належить, порахувати.
	}

	p = Nx / N;
	V = V1 * p;
	mnew = za * sqrt((1 - p) / (N*p));


	fout << "Half-sphere volume by Monte-Carlo method" << endl;
	fout << "V1 = " << V1 << endl;
	fout << "V2 = " << V2 << endl;
	fout << "p2 = " << p2 << endl;
	fout << "N  = " << (long)N << endl;
	fout << "Nx = " << Nx << endl;
	fout << "p  = " << p << endl;
	fout << "V  = " << V << endl;
	fout << "m  = " << mnew * 100 << "%" << endl;
	fout << "Volume is in [" << V*(1 - mnew) << "; " << V*(1 + mnew) << "] with probability alpha = 0,95" << endl;
	fout << "Vexact  = " << Vexact << " is ";

	if ((Vexact <= V*(1 - mnew)) || (V*(1 + mnew) <= Vexact))
	{
		fout << endl << "NOT ";
		system("pause");
	}
	fout << "in. " << endl << endl;

	return 0;

}