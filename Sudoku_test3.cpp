#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
int a[10][10]={0};
int flag=0; //test fill() success or not
void delete_all(int m) //for next loop
{
	int i,j;
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++)
			a[i][j]=0;
}
int test_only(int m,int i,int j,int test)
{
	int x,y;
	
	y=j; //test col
	for(x=1;x<=m;x++)
	{
		if(a[x][y]==test) return 0;
	}
	
	x=i; //test rol
	for(y=1;y<=m;y++)
	{
		if(a[x][y]==test) return 0;
	}
	
	if(m!=3&&m!=5&&m!=7) //test every cube
	{
		int p,q,r,s; //p=cube_up q=cube_left +r,s==range
		if(m==4)
		{
			if(i%2==0) p=i-1;
			else p=i;
			if(j%2==0) q=j-1;
			else q=j;
			r=s=1;
		}
		else if(m==6)
		{
			if(i%2==0) p=i-1;
			else p=i;
			if(j%3==0) q=j-2;
			else if(j%3==2) q=j-1;
			else q=j;
			r=1;
			s=2;
		}
		else if(m==8)
		{
			if(i%4==0) p=i-3;
			else if(i%4==3) p=i-2;
			else if(i%4==2) p=i-1;
			else p=i;
			if(j%2==0) q=j-1;
			else q=j;
			r=3;
			s=1;
		}
		else if(m==9)
		{
			if(i%3==0) p=i-2;
			else if(i%3==2) p=i-1;
			else p=i;
			if(j%3==0) q=j-2;
			else if(j%3==2) q=j-1;
			else q=j;
			r=s=2;
		}
		for(x=p;x<=p+r;x++)
			for(y=q;y<=q+s;y++)
			{
				if(a[x][y]==test) return 0;
			}
	}
	
	return 1;
}
int fill(int m,int finished)
{
	int all=m*m; //need to fill
	if(finished>=all)
	{
		flag=1;
		return 0; //all successed
	}
	
	int i,j;
	i=finished/m+1;
	j=finished%m+1; //a[1][1],a[1][2]¡­a[m][m]
	
	int x;
	if(a[i][j]==0)
	{
		for(x=1;x<=m;x++)
		{
			if(test_only(m,i,j,x)==1)
			{
				a[i][j]=x;
				fill(m,finished+1); //continue
				
				if(flag==1)	return 0;
				
				a[i][j]=0; //unsuccessed
			}
		}
	}
	else
	{
		fill(m,finished+1); //continue
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
					cout<<"Error: Data error!"<<endl;
					exit(1);
				}
			}
		
		fill(m,0);
		
		flag=0; //for next loop
		
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
