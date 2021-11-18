#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define D double					//편의
#define SIZE 50						//모집단 크기의 루트
#define SIZE_SQUARED SIZE * SIZE	//모집단의 크기
#define SEED_MIN 1					//seed 최솟값
#define SEED_MAX 100000000					//seed 최댓값
#define NUM_MAX	1000				//변량의 최댓값

double least[2];
double largest[2];

//루트 함수
D root(D num)
{
	int IDV = -1; //Increase Decrease Variable 증감 변수, 0이면 감소, 1이면 증가. 이전에 어느 조건에 들어갔는지 확인한다.
	D m = 1; //a에 뺄 변수
	D a = 1; //제곱근이 될 변수
	D aa; //a의 제곱

	if (num == 0)
	{
		return 0;
	}

	for (int i = 0; i < SIZE_SQUARED; i++)
	{
		aa = a * a;
		if (aa == num)
		{
			break;
		}
		else if (aa > num)
		{
			if (!(IDV == 0))
			{
				m *= 0.1;
			}
			a -= m;
			IDV = 0;
		}
		else if (aa < num)
		{
			if (IDV == 0)
			{
				m *= 0.1;
			}
			a += m;
			IDV = 1;
		}
	}

	return a;
}

//제곱 함수
D squared(D num)
{
	return num * num;
}

//배열의 총합 함수
D sum_arr(D* arr, double size)
{
	D num = 0;

	for (int i = 0; i < (int)size; i++)
	{
		num += arr[i];
	}

	return num;
}

//모집단 생성 함수
D* population(int seed)
{
	D* arr = (D*)malloc(sizeof(D) * (SIZE_SQUARED + 1));//모집단. 마지막 요소는 size
	int a = 0;
	if (arr)
	{
		arr[SIZE_SQUARED] = 0;
	}

	srand(seed);//seed로 초기화

	if (arr)//NULL 체크
	{
		for (int i = 0; i < SIZE_SQUARED; i++)//모집단 변량 생성
		{
			a = rand() % NUM_MAX;
			arr[i] = (double)a;
			arr[SIZE_SQUARED]++;
		}
	}

	return arr;
}

//표준 편차 함수
D standard_deviation(D* arr, double size, int seed)
{
	D m = 0;//평균
	D sigma_squared = 0;//분산
	D sigma = 0;//표준 편차

	m = sum_arr(arr, arr[(int)size]);
	m /= size;

	for (int i = 0; i < size; i++)
	{
		arr[i] -= m;
		arr[i] = squared(arr[i]);
	}

	sigma_squared = sum_arr(arr, arr[(int)size]);
	sigma_squared /= size;

	sigma = root(sigma_squared);

	/*
	printf("Seed : %d\n", seed);
	printf("평균 = %.5lf\n", m);
	printf("분산 = %.5lf\n", sigma_squared);
	printf("표준 편차 = %.5lf\n\n", sigma);
	*/

	if (sigma > largest[0]) { largest[0] = sigma; largest[1] = seed; }
	if (sigma < least[0]) { least[0] = sigma; least[1] = seed; }


	return sigma;
}

//메타 표준 편차 함수
D standard_deviation_s(D* arr, double size)
{
	D m = 0;//평균
	D sigma_squared = 0;//분산
	D sigma = 0;//표준 편차

	m = sum_arr(arr, arr[(int)size]);
	m /= size;

	for (int i = 0; i < size; i++)
	{
		arr[i] -= m;
		arr[i] = squared(arr[i]);
	}

	sigma_squared = sum_arr(arr, arr[(int)size]);
	sigma_squared /= size;

	sigma = root(sigma_squared);

	return sigma;
}


void main()
{
	D* sigma_arr = (D*)malloc(sizeof(D) * (SEED_MAX - SEED_MIN + 2));
	D* arr = NULL;
	D meta_standard_deviation = 0;
	D m_sigma = 0;//표준 편차들의 평균

	least[0] = SIZE_SQUARED;

	if (sigma_arr)
	{
		sigma_arr[SEED_MAX - SEED_MIN + 1] = 0;

		printf("\n\n");
		for (int i = SEED_MIN; i <= SEED_MAX; i++)
		{
			arr = population(i);//모집단 생성
			sigma_arr[i - SEED_MIN] = standard_deviation(arr, arr[SIZE_SQUARED], i);//모집단의 표준 편차
			sigma_arr[SEED_MAX - SEED_MIN + 1]++;
			printf("In progress %d / %d\r", i - SEED_MIN + 1, SEED_MAX - SEED_MIN + 1);//프로그래스 바
			free(arr);
		}

		system("cls");

		m_sigma = sum_arr(sigma_arr, sigma_arr[SEED_MAX - SEED_MIN + 1]);
		m_sigma /= sigma_arr[SEED_MAX - SEED_MIN + 1];

		meta_standard_deviation = standard_deviation_s(sigma_arr, sigma_arr[SEED_MAX - SEED_MIN + 1]);

		printf("\n\nSeed : %d ~ %d\n", SEED_MIN, SEED_MAX);
		printf("표준 편차의 평균 = %.10lf\n", m_sigma);
		printf("메타 표준 편차 = %.10lf\n", meta_standard_deviation);
		printf("표준 편차의 최솟값 = %.10lf, Seed : %.lf\n", least[0], least[1]);
		printf("표준 편차의 최댓값 = %.10lf, Seed : %.lf\n", largest[0], largest[1]);
	}

	free(sigma_arr);
}
