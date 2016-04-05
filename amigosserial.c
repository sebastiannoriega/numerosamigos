#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encontrarAmigos(int ini, int fin);

int main(int argc,char *argv[])
{
	clock_t start, stop;
	int inicio= atoi(argv[1]);
	int fin= atoi(argv[2]);

	start= clock();

	encontrarAmigos(inicio, fin);	
	
	stop= clock();
	
	printf("Estos son los numeros amigos del rango de %i a %i en %1.6f s \n",inicio,fin,(float)(stop-start)/CLOCKS_PER_SEC);

	return 0;
}

void encontrarAmigos(int ini, int fin)
{	
	int i, j;

	//crear contadores
	int *q = (int *) malloc(sizeof(int) * (fin + 1));

	//encontrar la sumatoria de los factores de cada numero en el rango
	for(i=ini ; i<=fin ; i++)
	{
		for(j=1; j<i ; j++)
		{
			if(i%j==0)
			{
				q[i]+=j;
			}
		}
	}


	//ya que se tiene la suma de los factores en cada contador, se comparan a ver si son amigos
	for(i=ini; i<=fin; i++)
	{
		for(j=i+1; j<=fin; j++)
		{
			if(q[i]!=1 && q[j]!=1 && q[i]==j && q[j]==i)
			{
				printf("%i y %i son numeros amigos\n", i, j);
				printf("%i y %i son numeros amigos\n", j, i);
			}
		}
	}	
	
}
