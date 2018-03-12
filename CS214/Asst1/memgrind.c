#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "mymalloc.h"


	double A(){

		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;
		void *testArray[1000];
		int i;

		gettimeofday(&t1, NULL);
		
		for (i = 0; i < 1000; i++){
			testArray[i] = malloc(1);
		}

		for(i = 999; i >=0; i--){
			free(testArray[i]);
			}

		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;

		return sumTime;

	}

	double B(){

		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;
		int i;
		char *temp;

		gettimeofday(&t1, NULL);

		for (i = 0; i <1000; i++){
			temp = malloc(1);
			free(temp);
		}

		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;
		return sumTime;

	}


	double C(){

		int randomGenerator[] = {1,0};
		int random = randomGenerator[rand()%2];
		void *testArray[1000];
		int numMalloc = 0;
		int goodMalloc = 0;
		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;
		int randomFree;

		gettimeofday(&t1, NULL);

			while(numMalloc < 1000){
				if(random == 0 || goodMalloc == 0){
					testArray[goodMalloc] = malloc(1);
					numMalloc++;
					goodMalloc++;
				}
				else{

					randomFree = rand() % 1000;
					free(testArray[randomFree]);
					goodMalloc--;
				}

				while (goodMalloc > 0){
					free(testArray[goodMalloc - 1]);
					goodMalloc--;
				}
			}

		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;
		return sumTime;
	}

	double D(){

		int randomGenerator[] = {1,0};
		int random = randomGenerator[rand()%2];
		void *testArray[1000];
		int numMalloc = 0;
		int goodMalloc = 0;
		int randomMalloc = 0;
		int randomFree = 0;
		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;

		while(numMalloc < 1000){
			if(random == 0 || goodMalloc == 0){
				randomMalloc = rand() % 1000;
				testArray[goodMalloc] = malloc(randomMalloc);
				numMalloc++;
				goodMalloc++;
			}

			else{
				randomFree = rand() % 1000;
				free(testArray[randomFree]);
				goodMalloc--;

			}

			while(goodMalloc > 0){
				free(testArray[goodMalloc - 1]);
				goodMalloc--;
			}
		}


		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;
		return sumTime;
	}

	//This test is just like C, but with an array of 10,000 instead of 1,000
	double E(){

		int randomGenerator[] = {1,0};
		int random = randomGenerator[rand()%2];
		void *testArray[10000];
		int numMalloc = 0;
		int goodMalloc = 0;
		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;
		int randomFree;

		gettimeofday(&t1, NULL);

			while(numMalloc < 10000){
				if(random == 0 || goodMalloc == 0){
					testArray[goodMalloc] = malloc(1);
					numMalloc++;
					goodMalloc++;
				}
				else{

					randomFree = rand() % 10000;
					free(testArray[randomFree]);
					goodMalloc--;
				}

				while (goodMalloc > 0){
					free(testArray[goodMalloc - 1]);
					goodMalloc--;
				}
			}

		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;
		return sumTime;


	}

	//this test is just like D, but with an array of 10,000 instead of 1,000
	double F(){

		int randomGenerator[] = {1,0};
		int random = randomGenerator[rand()%2];
		void *testArray[10000];
		int numMalloc = 0;
		int goodMalloc = 0;
		int randomMalloc = 0;
		int randomFree = 0;
		struct timeval t1, t2;
		float totalTime = 0;
		float sumTime = 0;

		while(numMalloc < 1000){
			if(random == 0 || goodMalloc == 0){
				randomMalloc = rand() % 10000;
				testArray[goodMalloc] = malloc(randomMalloc);
				numMalloc++;
				goodMalloc++;
			}

			else{
				randomFree = rand() % 10000;
				free(testArray[randomFree]);
				goodMalloc--;

			}

			while(goodMalloc > 0){
				free(testArray[goodMalloc - 1]);
				goodMalloc--;
			}
		}


		gettimeofday(&t2, NULL);

		totalTime = (t2.tv_sec - t1.tv_sec) * 100.0;
		totalTime += (t2.tv_sec - t1.tv_sec) / 100.0;
		sumTime = sumTime + totalTime;
		return sumTime;
	}

	int main(){

		int i;
		double totalA = 0;
		double totalB = 0;
		double totalC = 0;
		double totalD = 0;
		double totalE = 0;
		double totalF = 0;

		for(i = 0; i < 100; i++){
			totalA += A();
			totalB += B();
			totalC += C();
			totalD += D();
			totalE += E();
			totalF += F();
		}

		printf("Workload A had an average time of %lf seconds \n", (totalA / 100));
		printf("Workload B had an average time of %lf seconds \n", (totalB / 100));
		printf("Workload C had an average time of %lf seconds \n", (totalC / 100));
		printf("Workload D had an average time of %lf seconds \n", (totalD / 100));
		printf("Workload E had an average time of %lf seconds \n", (totalE / 100));
		printf("Workload F had an average time of %lf seconds \n", (totalF / 100));

		return 0;
}