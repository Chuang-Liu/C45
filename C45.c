#include <stdio.h>
#include <math.h>

const int TOTAL = 14;
const int TOTALYES = 9;

double info(int, int);
double infoa(int);
double splitinfoa(int);
void count(int);
void split(int);

int outlook[14] = {'s','s','o','r','r','r','o','s','s','r','s','o','o','r'};
int temperature[14] = {85,80,83,70,68,65,64,72,69.75,75,72,81,71};
int humidity[14] = {85,90,83,96,80,70,65,95,70,80,70,90,81,91};
int windy[14] = {'f','t','f','f','f','t','t','f','f','f','t','t','f','t'};
int ans[14] = {0,0,1,1,1,0,1,0,1,1,1,1,1,0};
int attribute[4][14] = {{'s','s','o','r','r','r','o','s','s','r','s','o','o','r'},
                        {85,80,83,70,68,65,64,72,69.75,75,72,81,71},
                        {85,90,83,96,80,70,65,95,70,80,70,90,81,91},
                        {0,0,1,1,1,0,1,0,1,1,1,1,1,0}};
int totalclass[4];

struct dataset
{
    int cardinality;
    int positive;
}d[4][14];

int main()
{
	int i,j;

    totalclass[0] = 3;
	d[0][0].cardinality = 4;d[0][0].positive = 2;
	d[0][1].cardinality = 6;d[0][1].positive = 4;
	d[0][2].cardinality = 4;d[0][2].positive = 3;
	printf("%f\n",splitinfoa(0));

	count(0);
	split(1);
	split(2);
	count(3);
	for (i=0;i<4;i++)
    {
        printf("%d\n",totalclass[i]);
        for (j=0;j<totalclass[i];j++)
        {
            printf("%d %d\n",d[i][j].cardinality, d[i][j].positive);
        }
        printf("\n");
    }

    for (i=0;i<4;i++,putchar('\n'))
    {
        printf("%f",infoa(i));
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

double infoa(int no)
{
    int i;
    double ret = 0;
    for (i=0;i<totalclass[no];i++)
    {
        ret += info(d[no][i].positive, d[no][i].cardinality-d[no][i].positive) * d[no][i].cardinality / TOTAL;
        //printf("%d:%f\n",i,ret);
    }
    return ret;
}

double splitinfoa(int no)
{
    double ret = 0;
    int i;

    for (i=0;i<totalclass[no];i++)
    {
        ret -= log((double)d[no][i].cardinality/TOTAL) / log(2) * d[no][i].cardinality / TOTAL;
        printf("%f ",ret);
    }
    return ret;
}

void count(int no)
{
	int i,j;
	int classpattern[14];

	totalclass[no] = 1;
	classpattern[0] = attribute[no][0];
	d[no][0].cardinality = 1;
	d[no][0].positive = (ans[0]?1:0);
	for (i=1;i<TOTAL;i++)
	{
		for (j=0;j<totalclass[no];j++)
		{
			if (classpattern[j] == attribute[no][i])
			{
				d[no][j].cardinality += 1;
				if (ans[i]) d[no][j].positive += 1;
				break;
			}
		}
		if (j == totalclass[no])
		{
			classpattern[j] = attribute[no][i];
			d[no][j].cardinality = 1;
			d[no][j].positive = ans[i]?1:0;
			totalclass[no] += 1;
		}
	}
}

void split(int no)
{
    int i,j;
    int t;
    int yescount = 0;
    double temp,min;
    for (i=0;i<TOTAL;i++)
    {
        for (j=i+1;j<TOTAL;j++)
        {
            if (attribute[no][i]>attribute[no][j])
            {
                t = attribute[no][i];
                attribute[no][i] = attribute[no][j];
                attribute[no][j] = t;
            }
        }
    }

    min = 100000;
    for (i=0;i<TOTAL;i++)
    {
        if (ans[i]) yescount += 1;
        temp = info(yescount, i-yescount) * i / TOTAL + info(TOTALYES - yescount, TOTAL - i -TOTALYES + yescount);
        if (temp < min)
        {
            d[no][0].cardinality = i;
            d[no][0].positive = yescount;
            d[no][1].cardinality = TOTAL - i;
            d[no][1].positive = TOTALYES - yescount;
        }
    }

    totalclass[no] = 2;
}
