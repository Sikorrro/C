// ALGO2IN1 21ALAB01
// Maciej Sikorski
// sm37916@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct struktura {
	int x;
	char y;
	float z;
};

typedef struktura st;

st** losowanie(int liczba) {
	st** tab = (st**)malloc(sizeof(st*) * liczba);
	int* randomy = (int*)malloc(sizeof(int) * 10000);
	srand(time(NULL));
	for (int a = 0; a < 10000; a++) {
		int lic = -1000 + a;
		randomy[a] = lic;
	}
	for (int k = 10000 - 1; k > 0; k--) {
		int id = (rand() % 9999) +1;
		int kt = randomy[k];
		int lt = randomy[id];
		randomy[k] = lt;
		randomy[id] = kt;
	}
		
	for (int i = 0; i < liczba; i++) {
		tab[i] = (st*)malloc(sizeof(st));
		tab[i]->x = randomy[i];
		tab[i]->y = (rand() % (83 - 63 + 1)) + 63;
		tab[i]->z = (1000 + i + 1);
	}
	free(randomy);
	return tab;
};

void kasowanie(st** tab, int liczba) {
	for (int i = 0; i < liczba; i++) {
		free(tab[i]);
	}
	free(tab);
};

void sortowanie(st** tab, int liczba){
	int i, j, zmiana, tymczas;
	for (i = 0; i < liczba - 1; ++i)
	{
		zmiana = 0;
		for (j = 0; j < liczba - 1 - i; j++)
		{
			if (tab[j + 1]->x < tab[j]->x)   
			{
				tymczas = tab[j]->x;
				tab[j]->x = tab[j + 1]->x;
				tab[j + 1]->x = tymczas;         
				zmiana = 1;
			}
		}
		if (!zmiana) break;      
	}
};

int zliczanie(st** tab, int liczba, char w) {
	int licz = 0;
	for (int i = 0; i < liczba; i++) {
		if (tab[i]->y == w) {
			licz++;
		}
	}
	return licz;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	int N; 
	char X; 
	FILE* filepoint;
	errno_t err = fopen_s(&filepoint, "inlab01.txt", "r");
	if (filepoint == NULL) return -1; 
	fscanf_s(filepoint, "%d %c", &N, &X); 
	fclose(filepoint);
	st** wsk = losowanie(N);
	sortowanie(wsk, N);
	zliczanie(wsk, N, X);
	end = clock();
	time_spent = (double)(end - begin);
	for (int i = 0; i < 20; i++) {
		printf("%d\n", wsk[i]->x);
	};
	int hu = zliczanie(wsk, N, X);
	printf("%d\n", hu);
	kasowanie(wsk, N);
	printf("%f\n", time_spent);
}

