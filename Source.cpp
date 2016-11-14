#include <stdio.h>
#define NUM_LINE 3
#define NUM_STATION 4
#define MAX 999999

// Utility function to find minimum of two numbers
int min(int x, int y, int z) {
	int smallest = MAX;
	if (x < smallest)
		smallest = x;
	if (y < smallest)
		smallest = y;
	if (z < smallest)
		smallest = z;
	return smallest;
}

int assemblyiterative(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x)
{
	int T1[NUM_STATION], T2[NUM_STATION], T3[NUM_STATION], i;

	T1[0] = e[0] + a[0][0]; // time taken to leave first station in line 1
	T2[0] = e[1] + a[1][0]; // time taken to leave first station in line 2
	T3[0] = e[2] + a[2][0]; // time taken to leave first station in line 3

	// Fill tables T1[],T2[] and T3[] using the above given recursive relations
	for (i = 1; i < NUM_STATION; ++i)
	{
		T1[i] = min(T1[i - 1] + a[0][i], T2[i - 1] + t[1][i] + a[0][i], T3[i - 1] + t[2][i] + a[2][i]);
		T2[i] = min(T2[i - 1] + a[1][i], T1[i - 1] + t[0][i] + a[1][i], T3[i - 1] + t[2][i] + a[2][i]);
		T3[i] = min(T3[i - 1] + a[2][i], T1[i - 1] + t[0][i] + a[0][i], T2[i - 1] + t[1][i] + a[0][i]);
	}

	// Consider exit times and return minimum
	return min(T1[NUM_STATION - 1] + x[0], T2[NUM_STATION - 1] + x[1], T3[NUM_STATION - 1] + x[2]);
}

int assemblyRec(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x, int n, int line){
	if (n == 0){
		return e[line] + a[line][0];
	}
	int T0 = MAX;
	int T1 = MAX;
	int T2 = MAX;
	if (line == 0){
		T0 = min((assemblyRec(a, t, e, x, n - 1, 0) + a[0][n]), (assemblyRec(a, t, e, x, n - 1, 1) + t[1][n] + a[0][n]),
			(assemblyRec(a, t, e, x, n - 1, 2) + t[1][n] + a[0][n]));
	}
	else if (line == 1){
		T1 = min(assemblyRec(a, t, e, x, n - 1, 0) + a[0][n], assemblyRec(a, t, e, x, n - 1, 1) + t[1][n] + a[0][n],
			assemblyRec(a, t, e, x, n - 1, 2) + t[1][n] + a[0][n]);
	}
	else if (line == 2){
		T2 = min(assemblyRec(a, t, e, x, n - 1, 0) + a[0][n], assemblyRec(a, t, e, x, n - 1, 1) + t[1][n] + a[0][n],
			assemblyRec(a, t, e, x, n - 1, 2) + t[1][n] + a[0][n]);
	}
	return min(T0, T1, T2);
}

int main()
{
	int a[][NUM_STATION] = { { 4, 5, 3, 2 },
	{ 2, 10, 1, 4 }, { 4, 1, 2, 6 } };
	int t[][NUM_STATION] = { { 0, 7, 4, 5 },
	{ 1, 9, 2, 8 }, { 1, 4, 2, 5 } };
	int e[] = { 10, 12, 11 }, x[] = { 18, 7, 12 };

	printf("Processing Time by iterative : %d\n", assemblyiterative(a, t, e, x));
	printf("Processing Time by recursive : %d\n", assemblyRec(a, t, e, x,NUM_STATION,NUM_LINE-1));
	return 0;
}

