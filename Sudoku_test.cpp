#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
int a[10][10]={0};
void delete_all(int m) //for next loop
{
	int i,j;
	for(i=0;i<=m;i++)
		for(j=0;j<=m;j++)
			a[i][j]=0;
}
void sudoku_3()
{
	int blank=9;
	int i,j;
	int rol[4]={0};
	int col[4]={0};
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)	
		{
			if(a[i][j]!=0)
			{
				a[i][0]=a[i][0]+a[i][j]; //rol_sum
				a[0][j]=a[0][j]+a[i][j]; //col_sum
				rol[i]++; //rol_i finished sum
				col[j]++; //col_j finished sum
				blank--;
			}
		}
	}

	int blank_0; //in case many answers
	while(blank>0)
	{
		
		blank_0=blank;
		
		for(i=1;i<=3;i++)
		{	
			if(rol[i]==2) //only 1 blank
			{
				rol[i]=3;
				blank--;
				for(j=1;j<=3;j++)
				{
					if(a[i][j]==0)
					{
						a[i][j]=6-a[i][0];
						if(a[i][j]<=0)
						{
							cout<<"Error2: Data error!"<<endl;
							exit(1);
						}
						a[0][j]=a[0][j]+a[i][j];
						col[j]++;
						break; 
					}
				}
			}
		}
		for(j=1;j<=3;j++)
		{
			if(col[j]==2)
			{
				col[j]=3;
				blank--;
				for(i=1;i<=3;i++)
				{
					if(a[i][j]==0)
					{
						a[i][j]=6-a[0][j];
						if(a[i][j]<=0)
						{
							cout<<"Error3: Data error!"<<endl;
							exit(1);
						}	
						a[i][0]=a[i][0]+a[i][j];
						rol[i]++;
						break;
					}
				}
			}
		}
		
		if(blank_0==blank)
		{
			cout<<"Error4: Many answers!"<<endl;
			exit(1);
		}
	}
}
int main(int argc,char *argv[])
{
	int m,n;
	m=atoi(argv[2]);
	n=atoi(argv[4]);
	
	ifstream file(argv[6]);
	ofstream f(argv[8]);
	
	int i,j;
	
	while(n--)
	{
		for(i=1;i<=m;i++)
			for(j=1;j<=m;j++)
			{ 
				file>>a[i][j];
				if(a[i][j]<0||a[i][j]>m)
				{
					cout<<"Error1: Data error!"<<endl;
					exit(1);
				}
			}
		
		if(m==3) sudoku_3();

		for(i=1;i<=m;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(j<m) f<<a[i][j]<<" ";
				else  f<<a[i][j]<<endl;
			}
			f<<endl;
		}

		delete_all(m);
	}
	file.close();
	
	return 0;
}
