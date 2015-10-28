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
/* 定义个体信息结构定义                                                 */
/************************************************************************/
typedef struct individual
{
	int path[CITYNUMBER];  //个体的路径信息
	double cost;              //个体代价值
}Individual,*PIndividual;

/************************************************************************/
/*保存各地点之间的距离信息                                              */
/************************************************************************/
double pathCost[CITYNUMBER][CITYNUMBER];

/************************************************************************/
/* 保存个地点的位置坐标                                                 */
/************************************************************************/
int cityPosition[CITYNUMBER][3];

/************************************************************************/
/* 读入路径数据                                                         */
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
/* 读入城市坐标位置                                                     */
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
/* 生成一个介于两整型数之间的随机整数                                   */
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
/*计算某个路径的代价值                                                  */
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
/* 初始化种群                                                           */
/************************************************************************/
void initial(Individual group[])
{
	int i,j,k;
	PIndividual p;
	for(i=0;i<=POPULATIONSCALE-1;i++)                     //初始化种群里的100个个体
	{
		p=&group[i];                                      //p指向种群的第i个个体
		for(j=0;j<=CITYNUMBER-1;j++)                      //生成10个城市间的一个随机路径
		{
			k=0;
			if(j==0)  p->path[j]=getRandomNum(0,CITYNUMBER-1);
			else
			{
				p->path[j]=getRandomNum(0,CITYNUMBER-1);
				while(k<j)
				{
					if(p->path[j]==p->path[k])            //与之前城市重复，重新生成一个城市
					{
						p->path[j]=getRandomNum(0,CITYNUMBER-1);
						k=0;
					}
					else k++;
				}
			}
		}
		calculateCost(p);                                 //计算该路径的代价值
	}
}

/************************************************************************/
/*交换种群中的p1和p2                                                    */
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
/*将种群中个体按代价从小到大排序                                        */
/************************************************************************/
void sort(Individual group[])
{
	PIndividual p1,p2;
	for(int i=1;i<=POPULATIONSCALE-1;i++) //排序总共需进行N-1轮
	{
		for(int j=1;j<=POPULATIONSCALE-1;j++)
		{
			p1=&group[j-1];
			p2=&group[j];
			if(p1->cost > p2->cost) //代价值大的往后排
			{
				exchange(p1, p2);
			}
		}
	} 
}

/************************************************************************/
/* 输出当代种群中的每个个体                                             */
/************************************************************************/
void printPath(Individual group[],int generation)
{
	PIndividual p;

	cout<<"当前第 "<<generation<<" 代 ：";
	for(int i=0; i<=CITYNUMBER-1; i++)  
		cout<<group[0].path[i]<<" ";
	cout<<"  路径长度为: "<<group[0].cost<<endl;

// 	cout<<"当前第 "<<generation<<" 代："<<endl;
// 	for(int i=0;i<=POPULATIONSCALE-1;i++)
// 	{
// 		cout<<"第 "<<generation<<" 代，个体 "<<i<<" ：";
// 		p=&group[i];
// 		for(int j=0;j<=CITYNUMBER-1;j++)  
// 			cout<<p->path[j]<<" ";
// 
// 		cout<<"  代价值为："<<p->cost<<endl;
// 	}
}

/************************************************************************/
/*检查cityNum是否在son[CITYNUMBER]中已出现过                            */
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
/*  交叉                                                                */
/************************************************************************/
void cross(PIndividual p1, PIndividual p2)
{
	int i,j;
	int son1[CITYNUMBER],son2[CITYNUMBER];

	for(i=0;i<=CITYNUMBER-1;i++)                 //初始化子代son1、son2
	{
		son1[i]=-1;
		son2[i]=-1;
	}
	int crossPoint=getRandomNum(1,CITYNUMBER-1); //交叉位随机生成

	
	for(i=0;i<=crossPoint-1;i++)                //子代1前半部分直接从父代复制
	{
		son1[i]=p1->path[i];
	}
	for(i=crossPoint;i<=CITYNUMBER-1;i++)       //p1补全后半部分
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
	
	for(i=crossPoint;i<=CITYNUMBER-1;i++)   //子代2后半部分直接从父代复制
	{
		son2[i]=p2->path[i];
	}

	for(i=0;i<=crossPoint-1;i++)            //p2补全前半部分
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
	calculateCost(p1); //计算子代p1的代价
	calculateCost(p2); //计算子代p2的代价
}

/************************************************************************/
/*复制种群中的p1到p2中                                                  */
/************************************************************************/
void copy(PIndividual p1, PIndividual p2)
{
	int i;
	for(i=0;i<=CITYNUMBER-1;i++)  p2->path[i]=p1->path[i];
	p2->cost=p1->cost;
}

/************************************************************************/
/*变异                                                                  */
/************************************************************************/
void varation(Individual group[],int curGeneration)
{
	int generation=getRandomNum(1,POPULATIONSCALE);
	if(generation <= (curGeneration>100) ? (5*POPULATIONSCALE*VARIATIONPROBILITY):(POPULATIONSCALE*VARIATIONPROBILITY))   //在进化后期，增大变异概率
	{
		int i = getRandomNum(0, POPULATIONSCALE-1);      //变异的个体
		int j = getRandomNum(0, CITYNUMBER-1);           //变异的位置
		int k = getRandomNum(0, CITYNUMBER-1);
		PIndividual p = &group[i];                             //变异
		int cityNum = p->path[j];
		p->path[j] = p->path[k];
		p->path[k] = cityNum;
		calculateCost(p);                                //计算变异后路径的代价
	}
}

/************************************************************************/
/*种群进化，进化代数由MAXGENERATION决定                                 */
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
		printPath(group, generation-1);        //输出当代(第i-1代)种群

		for(int j=0; j <= copyNum - 1; j++ )   //选择
		{ 
			copy(&group[j], &group[j+retainNum]); 
		}
		
		for(int k=0; k <= crossNum-1; k+=2)    //交叉
		{
			cross(&group[crossFront+k], &group[crossLast+k]);
		}
		
		varation(group, generation);           //变异
	}
	sort(group);
	printPath(group,generation-1);             //输出当代(第i-1代)种群
}

/************************************************************************/
/* 主函数                                                               */
/************************************************************************/
int main()
{
	Individual group[POPULATIONSCALE];   //种群变量group
	readPosition();
	calculateDistance();                 //从文件中读入地点之间的距离数据
	srand((int)time(NULL));        //初始化随机数发生器
	initial(group);                //初始化种群
	evolution(group);              //进化：选择、交叉、变异
	return 0;
}
