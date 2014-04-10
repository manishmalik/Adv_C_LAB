#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void r(int **temp, int n)
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
float d(int *l, int *s, int n, int m)
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
int median(int *temp, int m,int n)
{
	int *t, *aux,i,j;
	t = (int*)calloc(n+1, sizeof(int));
	aux = (int*)calloc(n+1, sizeof(int));
	/*Sorting the temp using Counting sort O(n)*/
	for (i = 0; i < m; i++)
	{
		t[temp[i]]++;
	}
	aux[0] = t[0];
	for (i = 2; i <= n; i++) //flag for debug
	{
		for (j = i; j >= 1; j--)
		{
			aux[i] += t[j];
		}
	}
	i = n;
	/*printf("\n b4 sorting\n");
	for (j = 0; j < m; j++)
	{
		printf("%d\n", temp[j]);
	}*/
	//printf("-------------------");
	while (i >= 1)
	{
		//printf("\n aux[%d]-1=%d", i, aux[i] - 1);
		if (aux[i] - 1>0)
			temp[aux[i] - 1] = i;
		else
			temp[aux[i]] = i;
		t[i]--;
		aux[i]--;
		if (t[i] > 0)
		{
			continue;
		}
		else
		{
			i--;
			continue;
		}
	}
	/*printf("\n after ssorting\n");
	for (j = 0; j < m; j++)
	{
		printf("%d\n", temp[j]);
	}*/
	if (m % 2 != 0)
	{
		return temp[(m / 2) + 1];
	}
	else
	{
		return (temp[m / 2] + temp[(m / 2) + 1]) / 2;
	}
}
int main()
{
	int n, m, i, j, sum, i1;
	time_t t;
	srand((unsigned int)&t);
	int *l, *temp,*l1,*s,*med;
	float dis1, dis,dis_med;
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
	printf("\n dis1:\t");
	/*Floor value of Mean value*/
	for (j = 0; j < n; j++)
	{
		sum = 0;
		for (i = 0; i < m; i++)
		{
			sum += *(l + i*n + j);
		}
		s[j] = sum / m;
		printf("%d ", s[j]);
	}
	dis1 = d(l, s, n, m);
	printf("\n dis:\t");
	/*Ceiling value of Mean value*/
	for (i = 0; i < n; i++)
	{
		s[i]++;
		printf("%d ", s[i]);
	}
	dis = d(l, s, n, m);
	/*Median*/
	//free(temp);
	med = (int*)malloc(n*sizeof(int));
	temp = (int*)malloc(m*sizeof(int));
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			temp[i] = *(l + i*n + j);
		}
		med[j] = median(temp, m,n);
	}
	dis_med = d(l, med, n, m);
	printf("\n dis_med:   ");
	for (i = 0; i < n; i++)
		printf("%2d ", med[i]);
	printf("\n dis(ceiling mean)=%f\n dis1(floor mean)=%f \n dis_med(median)=%f", dis, dis1,dis_med);
	_getch();
	return 0;
}