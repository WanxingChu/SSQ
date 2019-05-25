#include   "stdio.h"
#include   "math.h"
#include    "time.h"
#include	<stdlib.h>
void	knn(float x,float A[])
{
	int i,j,t,k=9;
	for(i=0;i<k;i++)
		for(j=i+1;j<k+1;j++)
			if(fabs(x-A[i])>fabs(x-A[j]))
			{   
				t=A[i];
				A[i]=A[j];
				A[j]=t;
			} 
}
int	compare(float A[],float B[10])
{
	int i,j,t=0;
	for(i=0;i<10;i++)
	{
		for(j=0;j<9;j++)
		{
			if(B[i]==A[j])
			{
				t++;
				break;
			}
		}
	}
	return(t);
}

void  main()
{
	float A[100],B[100],C[10],D[10],x,t,m,d,f;//A[]存放空间中的坐标，
	int  flag,i,j,n=100,k=9,u;//k为近邻数
	srand((int)time(0));
	for(i=0;i<n;i++)
	{
		while(1)
		{ 
			u=rand();
			A[i]=(u-56.82)/3;
			if((A[i]<50)&&(A[i]>(-50)))
			{
				printf("%6.2f",A[i]);
				if((i+1)%10==0)
				{
					printf("\n");
				}
				break;
			}
			else
				continue;
		}
	}
	for (i=1;i<=10;i++)
	{
		switch(i)
		{
		case 1:
			printf("第1-10个数为A1类:\n");
			break;
		case 2:
			printf("第11-20个数为A2类:\n");
			break;
		case 3:
			printf("第21-30个数为A3类:\n");
			break;
		case 4:
			printf("第31-40个数为A4类:\n");
			break;
		case 5:
			printf("第41-50个数为A5类:\n");
			break;
		case 6:
			printf("第51-60个数为A6类:\n");
			break;
		case 7:
			printf("第61-70个数为A7类:\n");
			break;
		case 8:
			printf("第71-80个数为A8类:\n");
			break;
		case 9:
			printf("第81-90个数为A9类:\n");
			break;
		case 10:
			printf("第91-100个数为A10类:\n");
			break;
others:
			break;
		}
	}
	for(i=0;i<100;i++)
	{
		B[i]=A[i];
	}
	while(1)
	{ 
		x= rand()-9.16;
		if((x<50)&&(x>(-10)))
		{
			printf("测试样本x=%f\n",x);
			break;
		}
		else
			continue;
	}

	
	knn(x,A); //按照相似性，对前10个样本排序
	for(i=k;i<n;i++)
	{
		f=fabs(x-A[k-1]);
		d=fabs(x-A[i]);
		if(d<f)
		{
			t=A[k-1];
			A[k-1]=A[i];
			A[i]=t;
		}
		knn(x,A);
	}//选出最相似的10个样本，排在前A[0]-A[9]
	printf("x的9个近邻数为:\n");
	for(i=0;i<k;i++)
	{
		printf("%6.2f",A[i]);
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			C[j]=B[i*10+j];
		}
		D[i]=compare(A,C);
	}
	printf("\n");
	for(i=0;i<10;i++)
	{ 
		m=D[i];
		for(j=0;j<10;j++)
		{
			if(m>=D[j])
			{ 
				flag=1;
				continue;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			printf("x属于A%d类",(i+1));
		}
	}

}

