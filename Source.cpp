#include <stdio.h>
#define NUM_LINE 3
#define NUM_STATION 4

// Utility function to find minimum of two numbers
int min(int x, int y, int z) {
	int smallest = 999999;
	if (x < smallest)
		smallest = x;
	if (y < smallest)
		smallest = y;
	if (z < smallest)
		smallest = z;
	return smallest;
}

int carAssemblyiterative(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x)
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

int main()
{
	int a[][NUM_STATION] = { { 4, 5, 3, 2 },
	{ 2, 10, 1, 4 }, { 4, 1, 2, 6 } };
	int t[][NUM_STATION] = { { 1, 7, 4, 5 },
	{ 1, 9, 2, 8 }, { 1, 4, 2, 5 } };
	int e[] = { 10, 12, 11 }, x[] = { 18, 7, 12 };

	printf("Processing Time : %d\n", carAssemblyiterative(a, t, e, x));
	return 0;
}
