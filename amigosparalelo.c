#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc,char *argv[])
{		
	clock_t start, stop;
	int ini= atoi(argv[1]);
	int fin= atoi(argv[2]);
	int rank;
	int i, j;
	int startloop, stoploop;
	int global_sum [fin + 1];

	start= clock();
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	//crear contadores locales
	int q [fin + 1];
	
	if(rank==1)
	{
		startloop= ini;
		stoploop= (fin-ini)/4;
		printf("soy el proceso %i", rank);
	}
	else if(rank==2)
	{
		startloop= (fin-ini)/4 + 1;
		stoploop= (fin-ini)/4 * 2;
		printf("soy el proceso %i", rank);
	}
	else if(rank==3)
	{
		startloop= (fin-ini)/4 * 2 + 1;
		stoploop= (fin-ini)/4 * 3;
		printf("soy el proceso %i", rank);
	}
	else if(rank==4)
	{
		startloop= (fin-ini)/4 * 3 + 1;
		stoploop= (fin-ini)/4 * 4;
		printf("soy el proceso %i", rank);
	}

	//encontrar la sumatoria de los factores de cada numero en el rango
	for(i=startloop ; i<=stoploop ; i++)
	{
		for(j=1; j<i ; j++)
		{
			if(i%j==0)
			{
				q[i]+=j;
			}
		}
	}

	//se espera a que todos terminen de calcular factores antes de hacer comparaciones
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank==0)
	MPI_Reduce(q, global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		

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
		
	stop= clock();
	
	printf("Estos son los numeros amigos del rango de %i a %i en %1.6f s \n",ini,fin,(float)(stop-start)/CLOCKS_PER_SEC);
	
	MPI_Finalize();

	return 0;
}


