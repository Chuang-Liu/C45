#include <stdio.h>
#include <math.h>

const int TOTAL = 14;

double info(int, int);
double infoa(int, int);
void count(int[]);

int outlook[14] = {'s','s','o','r','r','r','o','s','s','r','s','o','o','r'};
int temperature[14] = {85,80,83,70,68,65,64,72,69.75,75,72,81,71};
int humidity[14] = {85,90,83,96,80,70,65,95,70,80,70,90,81,91};
int windy[14] = {'f','t','f','f','f','t','t','f','f','f','t','t','f','t'};
int ans[14] = {0,0,1,1,1,0,1,0,1,1,1,1,1,0};
int classcount[14],class[14],totalclass;

int main()
{
	int i,j;
	double infod = info(9,5);
	count(outlook);
	printf("%d\n",totalclass);
	for (i=0;i<totalclass;i++,putchar('\n'))
	{
		printf("%d",classcount[i]);
	}
	count(temperature);
	printf("%d\n",totalclass);
	for (i=0;i<totalclass;i++,putchar('\n'))
	{
		printf("%d",classcount[i]);
	}
	count(humidity);
	printf("%d\n",totalclass);
	for (i=0;i<totalclass;i++,putchar('\n'))
	{
		printf("%d",classcount[i]);
	}
	count(windy);
	printf("%d\n",totalclass);
	for (i=0;i<totalclass;i++,putchar('\n'))
	{
		printf("%d",classcount[i]);
	}
	return 0;
}

double info(int a,int b)
{
	if (a==0 || b==0) return 0;
	int total = a+b;
	double x = (double)a / (a+b), y =(double)b / (a+b);
	int i;
	double ret = 0;
	ret -= x * log(x)/log(2);
	ret -= y * log(y)/log(2);
	return ret;
}

void count(int a[])
{
	int i,j;

	totalclass = 1;
	classcount[0] = 1;
	class[0] = a[0];
	for (i=1;i<TOTAL;i++)
	{
		for (j=0;j<totalclass;j++)
		{
			if (class[j] == a[i])
			{
				classcount[j]+=1;
				break;
			}
		}
		if (j == totalclass)
		{
			class[j] = a[i];
			classcount[j] = 1;
			totalclass+=1;
		}
	}
}

void spit(int a[])
{
}
