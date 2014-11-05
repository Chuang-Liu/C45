#include <stdio.h>
#include <math.h>

const int TOTAL = 14;
const int TOTALYES = 9;

double info(int, int);
double infoa(int);
double splitinfoa(int);
double gainratio(int);
void count(int);
void split(int);

int outlook[14] = {'s','s','o','r','r','r','o','s','s','r','s','o','o','r'};
int temperature[14] = {85,80,83,70,68,65,64,72,69,75,75,72,81,71};
int humidity[14] = {85,90,83,96,80,70,65,95,70,80,70,90,81,91};
int windy[14] = {'f','t','f','f','f','t','t','f','f','f','t','t','f','t'};
int ans[14] = {0,0,1,1,1,0,1,0,1,1,1,1,1,0};
int attribute[5][14] = {{'s','s','o','r','r','r','o','s','s','r','s','o','o','r'},
                        {85,80,83,70,68,65,64,72,69,75,75,72,81,71},
                        {85,90,83,96,80,70,65,95,70,80,70,90,81,91},
                        {0,1,0,0,0,1,1,0,0,0,1,1,0,1},
                        {0,0,1,1,1,0,1,0,1,1,1,1,1,0}};
int totalclass[4];
double infod;

struct dataset
{
    int cardinality;
    int positive;
}d[4][14];

int main()
{
	int i,j;
	infod = info(TOTALYES, TOTAL - TOTALYES);

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
        printf("%f",gainratio(i));
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
        //printf("%f ",ret);
    }
    return ret;
}

double gainratio(int no)
{
    double ret = infod;
    ret -= infoa(no);
    ret /= splitinfoa(no);
    return ret;
}

void count(int no)
{
	int i,j;
	int classpattern[14];

	totalclass[no] = 1;
	classpattern[0] = attribute[no][0];
	d[no][0].cardinality = 1;
	d[no][0].positive = (attribute[no][0]?1:0);
	for (i=1;i<TOTAL;i++)
	{
		for (j=0;j<totalclass[no];j++)
		{
			if (classpattern[j] == attribute[no][i])
			{
				d[no][j].cardinality += 1;
				if (attribute[no][i]) d[no][j].positive += 1;
				break;
			}
		}
		if (j == totalclass[no])
		{
			classpattern[j] = attribute[no][i];
			d[no][j].cardinality = 1;
			d[no][j].positive = attribute[no][i]?1:0;
			totalclass[no] += 1;
		}
	}
}

void split(int no)
{
    int i,j,k;
    int t;
    int yescount = 0;
    int minyescount, mini;
    double temp,min;
    for (i=0;i<TOTAL;i++)
    {
        for (j=i+1;j<TOTAL;j++)
        {
            if (attribute[no][i]>attribute[no][j])
            {
                for (k=0; k<4; k++)
                {
                    t = attribute[k][i];
                    attribute[k][i] = attribute[k][j];
                    attribute[k][j] = t;
                }
            }
        }
    }
    for (i=0;i<TOTAL;i++)
    {
        printf("%d ",attribute[no][i]);
    }
    putchar('\n');

    min = 100000;
    totalclass[no] = 2;
    for (i=0;i<(TOTAL -1 );i++)
    {
        if (attribute[4][i]) yescount += 1;
        d[no][0].cardinality = i;
        d[no][0].positive = yescount;
        d[no][1].cardinality = TOTAL - i;
        d[no][1].positive = TOTALYES - yescount;
        temp = infoa(no);
        if (temp < min)
        {
            min = temp;
            mini = i;
            minyescount = yescount;
        }
    }
    d[no][0].cardinality = mini;
    d[no][0].positive = minyescount;
    d[no][1].cardinality = TOTAL - mini;
    d[no][1].positive = TOTALYES - minyescount;

    printf("split:%d\n",mini);
}
