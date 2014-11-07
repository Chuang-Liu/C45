#include <stdio.h>
#include <math.h>

const int TOTAL = 14;
const int TOTALYES = 9;

struct attributeclass
{
    int pattern;
    int cardinality;
    int positive;
};

void C45(int, int, int);
double info(int, int);
double infoa(int, struct attributeclass [14], int);
double splitinfoa(int);
double gainratio(int);
void count(struct attributeclass [][14], int);
void split(struct attributeclass[][14], int, int, int);

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
int next[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,-1,-1,-1};
int totalclass[4];
short ruleused[4];



int main()
{
//    freopen("out.txt","w",stdout);
	int i,j;

	struct attributeclass ac[4][14];

    C45(0,TOTAL,TOTALYES);
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

double infoa(int classcount, struct attributeclass ac[14],int dcardinality)
{
    int i;
    double ret=0;
    for (i=0; i<classcount;i++)
    {
        ret+=info(ac[i].positive,ac[i].cardinality-ac[i].positive) * ac[i].cardinality;
    }
    ret /= (double)dcardinality;
    return ret;
}

double splitinfoa(int no)
{
    double ret = 0;
    int i;

    for (i=0;i<totalclass[no];i++)
    {
        //ret -= log((double)d[no][i].cardinality/TOTAL) / log(2) * d[no][i].cardinality / TOTAL;
        //printf("%f ",ret);
    }
    return ret;
}

double gainratio(int no)
{
    double ret;
    //ret -= infoa(no);
    ret /= splitinfoa(no);
    return ret;
}

void C45(int head,int dcardinality, int positivecount)
{
    int i,j,gainmax;
    int rear1;
    double temp, min=10000;
    struct attributeclass d[4][14];

    for (i=0;i<4;i++) printf("%d",ruleused[i]);
    putchar('\n');
    if (dcardinality==0) return;
    if (positivecount==0 || dcardinality==positivecount) return;
    printf("%d %d\n",dcardinality,positivecount);
    for (i=head;i!=-1;i=next[i]) printf("%d ",i);
    putchar('\n');

    //calculate gain and find gainmax = attribute no.
    count(d,head);
    split(d,head,dcardinality,positivecount);
//    for (i=0;i<4;i++)
//    {
//        printf("total:%d\n",totalclass[i]);
//        for (j=0;j<totalclass[i];j++)
//        {
//            printf("%d %d,,,,,",d[i][j].cardinality,d[i][j].positive);
//        }
//        putchar('\n');
//    }
    for (i=0;i<4;i++)
    {
        if (ruleused[i]) continue;
        temp=infoa(totalclass[i],d[i],dcardinality);
        if (temp<min)
        {
            min=temp;
            gainmax=i;
        }
    }


    for (i=0; i<totalclass[gainmax]; i++)
    {
        next[14]=head;
        next[15]=-1;
        rear1=15;
        j=14;
        while (next[j]!=-1)
        {
            if (attribute[gainmax][next[j]]==d[gainmax][i].pattern)
            {
                if (next[j]==head) head=next[head];
                next[rear1]=next[j];
                rear1=next[j];
                next[j]=next[next[j]];
            }
            else
            {
                j=next[j];
            }
        }
        next[rear1]=-1;
//        printf("set:");
//        for (j=0;j<14;j++)
//        {
//            printf("%d ",next[j]);
//        }
//        putchar('\n');

        ruleused[gainmax]=1;
        C45(next[15],d[gainmax][i].cardinality,d[gainmax][i].positive);
        ruleused[gainmax]=0;
    }
}

void count(struct attributeclass ac[][14], int head)
{
	int i,j,k;

	for (i=0;i<4;i+=3)
	{
	    if (ruleused[i]) continue;
	    totalclass[i]=1;
        ac[i][0].pattern = attribute[i][head];
        ac[i][0].cardinality = 1;
        ac[i][0].positive = attribute[4][head];
	    for (j=next[head];j!=-1;j=next[j])
	    {
	        for (k=0;k<totalclass[i];k++)
	        {
	            if (ac[i][k].pattern == attribute[i][j])
	            {
	                ac[i][k].cardinality+=1;
	                if (attribute[4][j]) ac[i][k].positive+=1;
	                break;
	            }
	        }
	        if (k == totalclass[i])
	        {
	            ac[i][k].pattern = attribute[i][j];
	            totalclass[i]+=1;
	            ac[i][k].cardinality=1;
	            ac[i][k].positive=attribute[4][j];
	        }
	    }
	}
}

void split(struct attributeclass d[][14], int head, int total, int positivecount)
{
    int i,j,k;
    int t;
    int a[14];
    int minyescount, mini;
    double temp,min;
    struct attributeclass tt;


    for (i=1;i<3;i++)
    {
        if (ruleused[i]) continue;
        t=0;
        for (j=head;j!=-1;j=next[j])
        {
            a[t]=j;
            t+=1;
        }

        /*------------sort------------------------------------------------*/
        for (j=0;j<total;j++)
        {
            for (k=j+1;k<total;k++)
            {
                if (attribute[i][a[j]]>attribute[i][a[k]])
                {
                    t=a[j];
                    a[j]=a[k];
                    a[k]=t;
                }
            }
        }
        /*-----------------------------------------------------------------------*/

        d[i][0].cardinality=0;
        d[i][1].cardinality=total;
        d[i][0].positive=0;
        d[i][1].positive=positivecount;
        min=10000;
        totalclass[i]=2;
        for (j=0;j<total;j++)
        {
            d[i][0].cardinality+=1;
            d[i][1].cardinality-=1;
            if (attribute[4][a[j]])
            {
                d[i][0].positive+=1;
                d[i][1].positive-=1;
            }
            temp=infoa(2, d[i], total);
            if (temp<min)
            {
                tt.cardinality=d[i][0].cardinality;
                tt.positive=d[i][0].positive;
                min=temp;
            }
        }
        d[i][0].cardinality=tt.cardinality;
        d[i][0].positive=tt.positive;
        d[i][1].cardinality=total-tt.cardinality;
        d[i][1].positive=positivecount-tt.positive;
    }
}
