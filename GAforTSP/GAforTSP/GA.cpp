#include <iostream>
using namespace std;
#include <time.h>
#include <math.h>

#define CITYNUMBER  10           
#define POPULATIONSCALE  100     
#define CROSSPROBILITY   0.9     
#define VARIATIONPROBILITY  0.1 
#define RETAINPROBILITY     0.6   
#define MAXGENERATION  200        

/************************************************************************/
/* ���������Ϣ�ṹ����                                                 */
/************************************************************************/
typedef struct individual
{
	int path[CITYNUMBER];  //�����·����Ϣ
	double cost;              //�������ֵ
}Individual,*PIndividual;

/************************************************************************/
/*������ص�֮��ľ�����Ϣ                                              */
/************************************************************************/
double pathCost[CITYNUMBER][CITYNUMBER];

/************************************************************************/
/* ������ص��λ������                                                 */
/************************************************************************/
int cityPosition[CITYNUMBER][3];

/************************************************************************/
/* ����·������                                                         */
/************************************************************************/
void calculateDistance()
{
	for(int i=0; i<CITYNUMBER; i++)
	{
		for(int j=0;j<CITYNUMBER; j++)
		{
			if(i==j)
			{
				pathCost[i][j] = 0;
				continue;
			}
			if(i > j)
			{
				pathCost[i][j] = pathCost[j][i];
				continue;
			}
			else
			{
/*				cout<<cityPosition[i][1]-cityPosition[j][1]<<" "<<cityPosition[i][2]-cityPosition[j][2]<<endl;*/
				pathCost[i][j] = sqrt(pow(cityPosition[i][1]-cityPosition[j][1], 2)+pow(cityPosition[i][2]-cityPosition[j][2], 2));
			}
		}
	}


// 	FILE *fp=fopen("data.txt","r");	
// 	for(int i = 0; i < CITYNUMBER; i++)
// 	{
// 		for(int j = 0; j < CITYNUMBER; j++)
// 		{
// 			fscanf(fp,"%d",&pathCost[i][j]);
// 		}
// 	}
}

/************************************************************************/
/* �����������λ��                                                     */
/************************************************************************/
void readPosition()
{
	FILE *fp=fopen("data.txt","r");
	for(int i=0; i<CITYNUMBER; i++)
	{
		fscanf(fp, "%d%d%d", &cityPosition[i][0], &cityPosition[i][1], &cityPosition[i][2]);
	}
}

/************************************************************************/
/* ����һ��������������֮����������                                   */
/************************************************************************/
int getRandomNum(int low,int high)
{
	int k;
	double d;
	k=rand();
	k=(k!=RAND_MAX)?k:(k-1);
	d=(double)k/((double)(RAND_MAX));
	k=(int)(d*(high-low+1));
	return (low+k);
}

/************************************************************************/
/*����ĳ��·���Ĵ���ֵ                                                  */
/************************************************************************/
void calculateCost(PIndividual p)
{
	p->cost=0;
	for(int j=1;j<=CITYNUMBER-1;j++)
	{ 
		p->cost+=pathCost[p->path[j-1]][p->path[j]];
	}
	p->cost+=pathCost[p->path[CITYNUMBER-1]][p->path[0]];
}

/************************************************************************/
/* ��ʼ����Ⱥ                                                           */
/************************************************************************/
void initial(Individual group[])
{
	int i,j,k;
	PIndividual p;
	for(i=0;i<=POPULATIONSCALE-1;i++)                     //��ʼ����Ⱥ���100������
	{
		p=&group[i];                                      //pָ����Ⱥ�ĵ�i������
		for(j=0;j<=CITYNUMBER-1;j++)                      //����10�����м��һ�����·��
		{
			k=0;
			if(j==0)  p->path[j]=getRandomNum(0,CITYNUMBER-1);
			else
			{
				p->path[j]=getRandomNum(0,CITYNUMBER-1);
				while(k<j)
				{
					if(p->path[j]==p->path[k])            //��֮ǰ�����ظ�����������һ������
					{
						p->path[j]=getRandomNum(0,CITYNUMBER-1);
						k=0;
					}
					else k++;
				}
			}
		}
		calculateCost(p);                                 //�����·���Ĵ���ֵ
	}
}

/************************************************************************/
/*������Ⱥ�е�p1��p2                                                    */
/************************************************************************/
void exchange(PIndividual p1, PIndividual p2)
{
	int tempData;
	for(int i = 0; i < CITYNUMBER; i++)
	{
		tempData = p1->path[i];
		p1->path[i] = p2->path[i];
		p2->path[i] = tempData;
	}
	tempData = p1->cost;
	p1->cost = p2->cost;
	p2->cost = tempData;
}

/************************************************************************/
/*����Ⱥ�и��尴���۴�С��������                                        */
/************************************************************************/
void sort(Individual group[])
{
	PIndividual p1,p2;
	for(int i=1;i<=POPULATIONSCALE-1;i++) //�����ܹ������N-1��
	{
		for(int j=1;j<=POPULATIONSCALE-1;j++)
		{
			p1=&group[j-1];
			p2=&group[j];
			if(p1->cost > p2->cost) //����ֵ���������
			{
				exchange(p1, p2);
			}
		}
	} 
}

/************************************************************************/
/* ���������Ⱥ�е�ÿ������                                             */
/************************************************************************/
void printPath(Individual group[],int generation)
{
	PIndividual p;

	cout<<"��ǰ�� "<<generation<<" �� ��";
	for(int i=0; i<=CITYNUMBER-1; i++)  
		cout<<group[0].path[i]<<" ";
	cout<<"  ·������Ϊ: "<<group[0].cost<<endl;

// 	cout<<"��ǰ�� "<<generation<<" ����"<<endl;
// 	for(int i=0;i<=POPULATIONSCALE-1;i++)
// 	{
// 		cout<<"�� "<<generation<<" �������� "<<i<<" ��";
// 		p=&group[i];
// 		for(int j=0;j<=CITYNUMBER-1;j++)  
// 			cout<<p->path[j]<<" ";
// 
// 		cout<<"  ����ֵΪ��"<<p->cost<<endl;
// 	}
}

/************************************************************************/
/*���cityNum�Ƿ���son[CITYNUMBER]���ѳ��ֹ�                            */
/************************************************************************/
bool alreadySearch(int son[],int cityNum)
{
	int i;
	for(i=0;i<=CITYNUMBER-1;i++)
	{
		if(son[i]==cityNum) 
			return false;
	}
	return true;
}

/************************************************************************/
/*  ����                                                                */
/************************************************************************/
void cross(PIndividual p1, PIndividual p2)
{
	int i,j;
	int son1[CITYNUMBER],son2[CITYNUMBER];

	for(i=0;i<=CITYNUMBER-1;i++)                 //��ʼ���Ӵ�son1��son2
	{
		son1[i]=-1;
		son2[i]=-1;
	}
	int crossPoint=getRandomNum(1,CITYNUMBER-1); //����λ�������

	
	for(i=0;i<=crossPoint-1;i++)                //�Ӵ�1ǰ�벿��ֱ�ӴӸ�������
	{
		son1[i]=p1->path[i];
	}
	for(i=crossPoint;i<=CITYNUMBER-1;i++)       //p1��ȫ��벿��
	{
		for(j=0;j<=CITYNUMBER-1;j++)          
		{
			if(alreadySearch(son1,p2->path[j]))
			{ 
				son1[i]=p2->path[j];
				break; 
			}
		}
	}
	
	for(i=crossPoint;i<=CITYNUMBER-1;i++)   //�Ӵ�2��벿��ֱ�ӴӸ�������
	{
		son2[i]=p2->path[i];
	}

	for(i=0;i<=crossPoint-1;i++)            //p2��ȫǰ�벿��
	{
		for(j=0;j<=CITYNUMBER-1;j++)
		{
			if(alreadySearch(son2,p1->path[j]))
			{ 
				son2[i]=p1->path[j]; 
				break; 
			}
		}
	}

	for(i=0;i<=CITYNUMBER-1;i++)
	{
		p1->path[i]=son1[i];
		p2->path[i]=son2[i];
	}
	calculateCost(p1); //�����Ӵ�p1�Ĵ���
	calculateCost(p2); //�����Ӵ�p2�Ĵ���
}

/************************************************************************/
/*������Ⱥ�е�p1��p2��                                                  */
/************************************************************************/
void copy(PIndividual p1, PIndividual p2)
{
	int i;
	for(i=0;i<=CITYNUMBER-1;i++)  p2->path[i]=p1->path[i];
	p2->cost=p1->cost;
}

/************************************************************************/
/*����                                                                  */
/************************************************************************/
void varation(Individual group[],int curGeneration)
{
	int generation=getRandomNum(1,POPULATIONSCALE);
	if(generation <= (curGeneration>100) ? (5*POPULATIONSCALE*VARIATIONPROBILITY):(POPULATIONSCALE*VARIATIONPROBILITY))   //�ڽ������ڣ�����������
	{
		int i = getRandomNum(0, POPULATIONSCALE-1);      //����ĸ���
		int j = getRandomNum(0, CITYNUMBER-1);           //�����λ��
		int k = getRandomNum(0, CITYNUMBER-1);
		PIndividual p = &group[i];                             //����
		int cityNum = p->path[j];
		p->path[j] = p->path[k];
		p->path[k] = cityNum;
		calculateCost(p);                                //��������·���Ĵ���
	}
}

/************************************************************************/
/*��Ⱥ����������������MAXGENERATION����                                 */
/************************************************************************/
void evolution(Individual group[])
{
	int generation;
	int crossNum = POPULATIONSCALE * CROSSPROBILITY / 2;
	int crossFront = POPULATIONSCALE * ( 1 - CROSSPROBILITY );
	int crossLast = POPULATIONSCALE * ( 1 - CROSSPROBILITY / 2 );
	int copyNum = POPULATIONSCALE * ( 1 - RETAINPROBILITY );
	int retainNum = POPULATIONSCALE * RETAINPROBILITY;

	for( generation=1 ; generation <= MAXGENERATION; generation++)
	{
		sort(group);
		printPath(group, generation-1);        //�������(��i-1��)��Ⱥ

		for(int j=0; j <= copyNum - 1; j++ )   //ѡ��
		{ 
			copy(&group[j], &group[j+retainNum]); 
		}
		
		for(int k=0; k <= crossNum-1; k+=2)    //����
		{
			cross(&group[crossFront+k], &group[crossLast+k]);
		}
		
		varation(group, generation);           //����
	}
	sort(group);
	printPath(group,generation-1);             //�������(��i-1��)��Ⱥ
}

/************************************************************************/
/* ������                                                               */
/************************************************************************/
int main()
{
	Individual group[POPULATIONSCALE];   //��Ⱥ����group
	readPosition();
	calculateDistance();                 //���ļ��ж���ص�֮��ľ�������
	srand((int)time(NULL));        //��ʼ�������������
	initial(group);                //��ʼ����Ⱥ
	evolution(group);              //������ѡ�񡢽��桢����
	return 0;
}
