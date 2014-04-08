#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void r(int **temp, int n)	// for generating the random number using time seed.
{
	int num, i, *a,*t;
	t = *temp;
	a = (int*)calloc(n+1, sizeof(int));
	for (i = 0; i < n; i++)
	{
		num = rand() % n + 1;
		//printf("\n num=%d and a[%d]=%d", num, num, a[num]);
		while (a[num] != 0)
		{
			num = rand() % n + 1;
		}
		t[i] = num;
		a[num] = 1;
	}
	free(a);
}
/*check if the random list generated has already been used or not ? every bit have some weight , it is ensured no two randomly genrated list have the same numbers.*/
int checksum(int *temp, int n)  	
{
	int i, t = 1, sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += temp[i] * t;
		t *= 2;
	}
	return sum;
}
float d(int *l, int *s, int n, int m) // Finding the distance with all the sets of permutations.
{
	int i, j,sum=0;
	float d;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			sum += abs(s[j] - (*(l + i*n + j)));
		}
	}
	d = (float)sum / (0.5*n*n*m);
	return d;
}
int main()
{
	int n, m, i, j, sum, i1;
	time_t t;
	srand((unsigned int)&t);
	int *l, *temp,*l1,*s;		// l: matrix containg m permutations and n numbers each ,temp: A particular set of permutation,l1: for checking for the repetition of set,s:shortest distance set.
	float dis1, dis;
	printf("\n Enter the value of m and n : ");
	scanf_s("%d %d", &m, &n);
	l = (int*)malloc(m*n*sizeof(int));
	l1 = (int*)malloc(m*sizeof(int));
	for (i = 0; i < m; i++)
	{
	cc:	temp = (int*)malloc(n*sizeof(int));
		r(&temp, n);
		if (i == 0)
		{
			l1[i] = checksum(temp, n);
		}
		else
		{
			sum = checksum(temp, n);
			for (i1 = 0; i1 < i; i1++)
			{
				if (l1[i1] == sum)
				{
					free(temp);
					goto cc;
				}
			}
			l1[i] = sum;
		}
		for (j = 0; j < n; j++)
		{
			*(l + i*n + j) = temp[j];
			printf("%2d ", *(l + i*n + j));
		}
		printf("\t %d \n",checksum(temp,n));
		free(temp);
	}
	s = (int*)malloc(n*sizeof(int));
	for (j = 0; j < n; j++)
	{
		sum = 0;
		for (i = 0; i < m; i++)
		{
			sum += *(l + i*n + j);
		}
		s[j] = sum / m;
	}
	dis1 = d(l, s, n, m);
	for (i = 0; i < n; i++)
	{
		s[i]++;
	}
	dis = d(l, s, n, m);
	printf("\n dis=%f and dis1=%f", dis, dis1);
	_getch();
	return 0;
}