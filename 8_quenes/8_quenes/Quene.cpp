# include <stdio.h>
# include <math.h>
int a[8]={-1};
int number = 0;
int canplace(int i,int m)
{
	int row;
	for(row = 0 ;row < i ; row++)
	{
		if(a[row] == m || abs(i - row) == abs(m - a[row]))
			return 0;
	}
	return 1;
}
void print()
{
	int i,j;
	printf("No %d:\n",number);
	for(i = 0;i < 8; i++)
	{
		for(j = 0;j < 8; j++)
		{
			if(j == a[i])
				printf("A");
			else
				printf(".");
		}
		printf("\n");
	}
}
void eightqueen(int i)
{
	int m;
	if(i >= 8)
	{
		number++;
		print();
	}
	else
	{
		for(m = 0;m < 8; m++)
		{
			if(canplace(i,m))
			{
				a[i] = m;
				eightqueen(i+1);
				a[i] = -1;
			}
		}

	}
}
void main()
{
	eightqueen(0);
}
