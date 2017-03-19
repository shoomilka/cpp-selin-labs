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

//  (  ������ + ���������  )
using namespace std;
//  (  �����, ��i �����    )
const double                     // �������� �������� ��'�� �i������         ( ��i���� �� ���i����� )
//r = 1.0,
h = 1,                     // ���i��� r � ������� � (0; 0; 0).                          +
x1 = 0, x2 = 1,               // ���i �� ����� ������� � ���������i���                  +
y11 = 0, y2 = 1,               // � ������������ �� x �� y �i� -r �� +r,                +
z1 = 0, z2 = +h,            // � �� z - �i� 0 �� +r.                                    +

V1 = (x2 - x1)*(y2 - y11)*(z2 - z1),  // ��'�� ��������� ���������i����.
V2 = 0.5,                      // ��'�� ��������� ������.                            +
Vexact = (M_PI) / 2,               // ����� �������� ��'��� �i������.                 +

p2 = V2 / V1,                    // ����i��i��� ��������� �� ������.

m = 0.01,                      // �i������ ������� ���������� ���i����� i���������
za = 1.96,                     // za: �(z) = alpha = 0,95.   +/- 3.4e-5

N = (za*za) / (m*m)*(1 - p2) / p2;   // �i���i��� �����, �� �� ����� �����������.

double
p,                             // ����i��i��� ��������� �� �i������.
V,                             // ��i��� ��'��� �i������.
x, y, z,                         // ���������� ��������� �����.
mnew;                          // ���� �������� �i������ �������.

unsigned long i, j,
Nx = 0;                          // �i���i��� �����, �� ����������� �� �i������.

int InBody(double x, double y, double z) {  // �����i��� ���������i ����� �� �i������.
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
		// ����������� ��������� �����, 0 <= rand()/RAND_MAX < 1
		
		x = (x2 - x1) * (rand() % RAND_MAX) / RAND_MAX + x1; // x1 <= x <= x2;
		y = (y2 - y11) * (rand() % RAND_MAX) / RAND_MAX + y11; // y11 <= y <= y2;
		z = (z2 - z1) * (rand() % RAND_MAX) / RAND_MAX + z1; // z1 <= z <= z2;
		
		if (InBody(x, y, z)) Nx++;               // ���� ��������, ����������.
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