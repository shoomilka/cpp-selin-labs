//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                                                             //
// Meshkantsev Mykhaylo KA-04 (QuickSort, Selection)           //
// Selin Olexander MMSA dept. (ShellSort, Insertion,           //
//                           BubbleSort, ShakerSort)  	       //
//                                                             //
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#include <stdlib.h> // div_t    rand
#include <conio.h>  // clrscr()
#include <math.h>
#include <iostream> // cin, cout
#include <fstream>  // ofstream
#include <time.h>

using namespace std;

long int
N,  // Array dimension
M;   // Parameter for ShellSort. Never change it !

int shoo_count;

unsigned long moves, compares;

struct tItem {
	int key;
	char data[4];
	friend bool operator < (tItem x, tItem y) { return (x.key < y.key); }
	friend bool operator <= (tItem x, tItem y) { return (x.key <= y.key); }
	friend bool operator > (tItem x, tItem y) { return (x.key > y.key); }
	friend bool operator >= (tItem x, tItem y) { return (x.key >= y.key); }
	friend void swap(tItem& a, tItem& b);
	friend void copy(tItem& a, tItem& b);
	tItem& operator = (tItem& y) { copy(*this, y); return *this; };
};

void swap(tItem& x, tItem& y) {
	int k = x.key; x.key = y.key; y.key = k;
	char s[4];
	//strcpy(s, x.data); strcpy(x.data, y.data); strcpy(y.data, s);
	strcpy_s(s, x.data); strcpy_s(x.data, y.data); strcpy_s(y.data, s);
	moves++;
	moves++;
	moves++;
};

void copy(tItem& x, tItem& y) {
	x.key = y.key;
	//strcpy(x.data, y.data);
	strcpy_s(x.data, y.data);
	moves++;
};

//ofstream fout("sort.txt");
ofstream fout;

void print(char * text, tItem * a, int N, bool sorted) {
	fout << endl << text;
	//if (N<101 && !sorted) {
		fout << endl;
		for (int i = 0; i<N; i++) {
			fout << a[i].key << " " << a[i].data << "\n";
			if ((i + 1) % 10 == 0) fout << endl;
		}
	/*}
	if (sorted) {
		for (int i = 0; i < N; i++) {
			if (i > 0 && a[i - 1] > a[i]) {
				fout << a[i - 1].key << "(" << a[i - 1].data << ") > " << a[i].key << "(" << a[i].data << ") ! " << endl;
			}
		}
	}*/
}

//++++++++++++++++Quicksort++++++++++++++++++++++++++++++++++

void QuickSort(tItem * a, int L, int R) {
	int m, i, j;
	tItem x;

	i = L;
	j = R;
	m = (L + R) / 2;
	x = a[m];

	while (i <= j) {
		while (a[i]<x) { i++; }
		while (x<a[j]) { j--; }
		if (i <= j) {
			if (i<j) {
				swap(a[i], a[j]);
				//c = a[i];
				//a[i] = a[j];
				//a[j] = c;
			}
			i++; j--;
		}
	}

	if (L<j) { QuickSort(a, L, j); }
	if (i<R) { QuickSort(a, i, R); }
}

//++++++++++++++++ShellSort++++++++++++++++++++++++++++++++++

void ShellSort(tItem * a) {
	int i, t, k, m, l, j;
	int * h = new int[M];
	tItem x;

	t = (int)(log((double)N) / log((double)2) - 1);
	h[t - 1] = 1;
	for (k = t - 2; k >= 0; k--) {
		h[k] = 2 * h[k + 1] + 1;
	}

	for (m = 0; m<t; m++) { // Global iteration No
		k = h[m];           // Step

		for (l = 0; l <= k - 1; l++) {  // SubArray No
			for (i = 1; i <= (N - 1) / k; i++) {

				if (l + i*k < N) {

					x = a[l + i*k];
					j = l + (i - 1)*k;

					while ((j >= 0) && (x<a[j])) {
						a[j + k] = a[j];
						j = j - k;
					}  // while ((j>=0)
					a[j + k] = x;

				}  // if (l+i*k

			}  // for (i=1;
		}  // SubArray
	}  // Global iteration
	delete[] h;
}


//++++++++++++++++ShakerSort+++++++++++++++++++++++++++++++++

void ShakerSort(tItem * a) {
	int i = 0, j, flag = 0;

	while (flag == 0) {
		flag = 1;
		for (j = i; j<N - 1 - i; j++) {
			if (a[j]>a[j + 1]) {
				swap(a[j], a[j + 1]);
				flag = 0;
			}
		}
		if (flag == 0)
			for (j = N - 2 - i; j>i; j--) {
				if (a[j - 1]>a[j]) {
					swap(a[j - 1], a[j]);
				}
			}
		i++;
	}
}

//++++++++++++++++MergeSort++++++++++++++++++++++++++++++++++

void Merge(tItem * a, int L, int m, int R) {
	// merge a[L..m] and a[m+1..R]
	int i1, i2, i;
	tItem * b = new tItem[R - L + 1];

	for (i = 0; i<R - L + 1; ++i)
		b[i] = a[i + L];

	i = L; // index in a;
	i1 = 0; // index in b[0..m-L];
	i2 = m - L + 1; // index in b[m-L+1..R-L];

	while (i <= R) {
		if ((i1 <= m - L) && (i2 <= R - L)) {
			if (b[i1]<b[i2])
				a[i++] = b[i1++];
			else
				a[i++] = b[i2++];
			continue;
		}
		if ((i1>m - L) && (i2 <= R - L)) {
			a[i++] = b[i2++];
			continue;
		}
		if ((i1 <= m - L) && (i2>R - L)) {
			a[i++] = b[i1++];
			continue;
		}
		if ((i1>m - L) && (i2>R - L)) {
			cout << "!!!!!!!!!!!!! ";
			continue;
		}
	}
	delete[] b;
}

void MergeSort(tItem * a, int L, int R) {
	int m, i, j;
	tItem x;
	//cout << L << " " << R << endl;
	if (R <= L) return;
	if (R - L == 1) {
		if (a[L] > a[R])
			swap(a[L], a[R]);
		return;
	}
	m = (R + L) / 2;
	if (L<m) MergeSort(a, L, m);
	if (R>m + 1) MergeSort(a, m + 1, R);

	Merge(a, L, m, R);

}

//++++++++++++++++HeapSort++++++++++++++++++++++++++++++++++

void pushdown(tItem * a, int L, int R) {
	int i = L;
	while (i + 1 <= (R + 1) / 2) {
		if (R + 1 == 2 * (i + 1)) {
			if (a[i] < a[2 * i + 1])
				swap(a[i], a[2 * i + 1]);
			compares++;
			i = R;
		}
		else {
			if ((a[i] < a[2 * i + 1]) && (a[2 * i + 1] >= a[2 * (i + 1)])) {
				swap(a[i], a[2 * i + 1]);
				i = 2 * i + 1;
			} else {
				if ((a[i] < a[2 * (i + 1)]) && (a[2 * (i + 1)] > a[2 * i + 1])) {
					swap(a[i], a[2 * (i + 1)]);
					i = 2 * (i + 1);
				}
				else {
					i = R;
				} // if ((a[i] > a[2*i+1]) ...
				compares++;
				compares++;
			} // if ((a[i] > a[2*i]) ...
			compares++;
			compares++;
		}  // if (R == 2*i)
	} // while
}

void HeapSort(tItem * a) {
	int i;

	for (i = (N - 1) / 2; i >= 0; i--) {
		pushdown(a, i, N - 1);
		//print("", a, N, false);
	}
	//fout << "-----------------------------------" << endl;

	for (i = N - 1; i>0; i--) {
		swap(a[0], a[i]);
		//print("Swap:", a, N, false);
		pushdown(a, 0, i - 1);
		//print("pushdown:", a, N, false);
		//fout << endl;
	}

}

void myInter(tItem * a) {
	int j;
	tItem x;

	for (int i = 1; i < N; i++) {
		copy(x, a[i]);
		j = i;
		while (j > 0 && a[j - 1] > x) {
			compares++;
			copy(a[j], a[j - 1]);
			j = j - 1;
		}
		copy(a[j], x);
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++             +++++++++++++++++++++++++++//
//+++++++++++++++++++     Main    +++++++++++++++++++++++++++//
//+++++++++++++++++++             +++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void last_main() {

	tItem * a, *b;  // Array and it's reserved copy
	int i;
	clock_t start, finish;
	double  duration;
	bool sorted = true;

	a = new tItem[N];
	b = new tItem[N];

	srand(time(0));

	//++++++++++++++++Generation+++++++++++++++++++++++++++++++++

	for (i = 0; i<N; i++) {
		a[i].key = rand();
		a[i].data[0] = 'A' + rand() % ('Z' - 'A' + 1);
		a[i].data[1] = 'A' + rand() % ('Z' - 'A' + 1);
		a[i].data[2] = 'A' + rand() % ('Z' - 'A' + 1);
		a[i].data[3] = '\0';
		b[i].key = a[i].key;
		//strcpy(b[i].data, a[i].data);
		strcpy_s(b[i].data, a[i].data);
	}

	print("Array generated", a, N, !sorted);

	//++++++++++++++++Quicksort++++++++++++++++++++++++++++++++++

	if (false) {
		moves = 0;     // кількість обмінів (копіювань)
		compares = 0;  // кількість порівнянь ключів елементів

		start = clock();
		QuickSort(a, 0, N - 1);
		finish = clock();

		print("Array sorted by QuickSort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements QuickSort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements QuickSort: "
			<< duration << endl;

		cout << compares << " - compares; " << moves << " moves \n";
		fout << compares << " - compares; " << moves << " moves \n";
	}

	//==============  my Insertion sort  =======================
	if (true) {
		

		start = clock();
		for (int shoo = 0; shoo < shoo_count; shoo++) {
			for (i = 0; i < N; i++)
				a[i] = b[i];

			moves = 0;     // кількість обмінів (копіювань)
			compares = 0;  // кількість порівнянь ключів елементів
			myInter(a);
		}
		finish = clock();

		print("Array sorted by Intersort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements by Intersort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		duration /= shoo_count;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements by Intersort: "
			<< duration << endl;

		cout << compares << " compares; " << moves << " moves \n";
		fout << compares << " compares; " << moves << " moves \n";
	}

	//++++++++++++++++ShellSort+++++++++++++++++++++++++++++++++

	if (false) {
		for (i = 0; i < N; i++)
			a[i] = b[i];

		moves = 0;     // кількість обмінів (копіювань)
		compares = 0;  // кількість порівнянь ключів елементів

		start = clock();
		ShellSort(a);
		finish = clock();

		print("Array sorted by ShellSort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements by ShellSort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements by ShellSort: "
			<< duration << endl;

		cout << compares << " compares; " << moves << " moves \n";
		fout << compares << " compares; " << moves << " moves \n";

	}

	//++++++++++++++++ShakerSort+++++++++++++++++++++++++++++++++

	if (false) {
		for (i = 0; i < N; i++)
			a[i] = b[i];

		moves = 0;     // кількість обмінів (копіювань)
		compares = 0;  // кількість порівнянь ключів елементів

		start = clock();
		ShakerSort(a);
		finish = clock();

		print("Array sorted by ShakerSort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements by ShakerSort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements by ShakerSort: "
			<< duration << endl;

		cout << compares << " compares; " << moves << " moves \n";
		fout << compares << " compares; " << moves << " moves \n";

	}
	//++++++++++++++++HeapSort+++++++++++++++++++++++++++++++++
	if (true) {
		
		start = clock();
		for (int shoo = 0; shoo < shoo_count; shoo++) {
			for (i = 0; i < N; i++)
				a[i] = b[i];

			moves = 0;     // кількість обмінів (копіювань)
			compares = 0;  // кількість порівнянь ключів елементів

			HeapSort(a);
		}
		finish = clock();

		print("Array sorted by HeapSort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements by HeapSort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		duration /= shoo_count;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements by HeapSort: "
			<< duration << endl;

		cout << compares << " compares; " << moves << " moves \n";
		fout << compares << " compares; " << moves << " moves \n";

	}

	//++++++++++++++++MergeSort+++++++++++++++++++++++++++++++++
	if (false) {
		for (i = 0; i < N; i++)
			a[i] = b[i];

		moves = 0;     // кількість обмінів (копіювань)
		compares = 0;  // кількість порівнянь ключів елементів

		start = clock();
		MergeSort(a, 0, N - 1);
		finish = clock();

		print("Array sorted by MergeSort", a, N, sorted);

		cout << "Time to sort array of " << N << " elements by MergeSort:";
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << duration << " seconds" << endl;

		fout << endl << "Time to sort array of " << N << " elements by MergeSort: "
			<< duration << endl;

		cout << compares << " compares; " << moves << " moves \n";
		fout << compares << " compares; " << moves << " moves \n";
	}

	delete[] a;
	delete[] b;
}

void set_values(long int countm, int sh) {
	N = countm;
	M = int(log((double)N) / log((double)2) + 1);
	shoo_count = sh;
}

int main() {
	fout.open("sort100.txt");
	set_values(100, 100);
	last_main();
	fout.close();

	fout.open("sort1000.txt");
	set_values(1000, 10);
	last_main();
	fout.close();

	fout.open("sort10000.txt");
	set_values(10000, 1);
	last_main();
	fout.close();

	_getch();

	return 0;
}
