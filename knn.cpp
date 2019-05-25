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
	float A[100],B[100],C[10],D[10],x,t,m,d,f;//A[]��ſռ��е����꣬
	int  flag,i,j,n=100,k=9,u;//kΪ������
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
			printf("��1-10����ΪA1��:\n");
			break;
		case 2:
			printf("��11-20����ΪA2��:\n");
			break;
		case 3:
			printf("��21-30����ΪA3��:\n");
			break;
		case 4:
			printf("��31-40����ΪA4��:\n");
			break;
		case 5:
			printf("��41-50����ΪA5��:\n");
			break;
		case 6:
			printf("��51-60����ΪA6��:\n");
			break;
		case 7:
			printf("��61-70����ΪA7��:\n");
			break;
		case 8:
			printf("��71-80����ΪA8��:\n");
			break;
		case 9:
			printf("��81-90����ΪA9��:\n");
			break;
		case 10:
			printf("��91-100����ΪA10��:\n");
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
			printf("��������x=%f\n",x);
			break;
		}
		else
			continue;
	}

	
	knn(x,A); //���������ԣ���ǰ10����������
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
	}//ѡ�������Ƶ�10������������ǰA[0]-A[9]
	printf("x��9��������Ϊ:\n");
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
			printf("x����A%d��",(i+1));
		}
	}

}

