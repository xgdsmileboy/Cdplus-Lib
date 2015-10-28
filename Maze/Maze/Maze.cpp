# include <stdio.h>
# include <iostream>
using namespace std;
char a[50][50];
int flag[50][50];
int m,n;
int x2,y2,x3,y3;
int result=0;
int main()
{
	void judge(int row,int col);
	int i,j;
	scanf("%d",&m);
	scanf("%d",&n);
	scanf("%d %d %d %d",&x2,&y2,&x3,&y3);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			flag[i][j]=0;
			cin>>a[i][j];
		}
	judge(x2,y2);
	if(result==1)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
void judge(int row,int col)
{
	int canplace(int row,int col);
	int r,c;
	if(row == x3&&col == y3)
		result=1;
	a[row][col]=1;
	r=row;//left
	c=col-1;
	if(canplace(r,c))
	{
		flag[row][col]++;
		judge(r,c);
	}
	r=row+1;//down
	c=col;
	if(canplace(r,c))
	{
		flag[row][col]++;
		judge(r,c);
	}
	r=row;//right	
	c=col+1;
	if(canplace(r,c))
	{
		flag[row][col]++;
		judge(r,c);
	}
	r=row-1;//up
	c=col;
	if(canplace(r,c))
	{
		flag[row][col]++;
		judge(r,c);
	}
}
int canplace(int row,int col)
{
	if(row>=0&&row<m&&col>=0&&col<n&& a[row][col]=='.'&&flag[row][col]<3)
		return 1;//can place
	else
		return 0;//can not place
}
