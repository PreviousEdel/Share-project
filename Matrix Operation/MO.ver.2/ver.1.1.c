#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


typedef struct matrix {
	int** matrix;
	int row;
	int column;

}MAT;

typedef struct mm {
	MAT ma;
	MAT mb;
}MM;
MAT reseted_m;

int** matrix_setting(MAT mx);

int half_n(int n)
{
	int result = 0;
	if (n % 2 == 0)
	{
		result = n / 2;
	}
	else
	{
		result = (n - 1) / 2;
	}

	return result;
}

void GCD_cal(int* factor, int half, int n)
{
	for (int i = 2; i < half; i++)
	{
		if (n % i == 0)
		{
			factor[i] = 1;
		}
	}
}

int smaller(int a, int b)
{
	int result = 0;

	if (a < b)
	{
		result = a;
	}
	else
	{
		result = b;
	}

	return result;
}

int greatest_common_divisor(int a, int b)
{
	int result = 1, half_a = half_n(a), half_b = half_n(b);
	
	int* factor_a = (int*)malloc(sizeof(int) * half_a);
	int* factor_b = (int*)malloc(sizeof(int) * half_b);

	if(b % a == 0)
	{
		result = a;
	}
	else if (a % b == 0)
	{
		result = b;
	}
	else
	{
		GCD_cal(factor_a, half_a, a);
		GCD_cal(factor_b, half_b, b);

		for (int i = 0; i < smaller(half_a, half_b); i++)
		{
			if (factor_a[i] && factor_b[i])
			{
				result *= factor_a[i];
			}
		}
	}

	return result;
}

MAT matrix_multiple(MAT ma, MAT mb)
{
	MAT mr;
	mr.row = ma.row;
	mr.column = mb.column;
	mr.matrix = matrix_setting(mr);

	for (int i = 0; i < mr.row; i++)
	{
		for (int j = 0; j < mr.column; j++)
		{
			for (int l = 0; l < mb.row; l++)
			{
				mr.matrix[i][j] += ma.matrix[i][l] * mb.matrix[l][j];
			}
		}
	}

	return mr;
}

MAT matrix_sum(MAT ma, MAT mb, int minus)
{
	MAT mr;
	mr.row = ma.row;
	mr.column = mb.column;
	mr.matrix = matrix_setting(mr);

	for (int i = 0; i < mr.row; i++)
	{
		for (int j = 0; j < mr.column; j++)
		{
			if (minus == 1)
			{
				mr.matrix[i][j] = ma.matrix[i][j] - mb.matrix[i][j];
			}
			else
			{
				mr.matrix[i][j] = ma.matrix[i][j] + mb.matrix[i][j];
			}
		}
	}

	return mr;
}

MAT matrix_scala_integer(MAT mx, int n)
{
	MAT mr;
	mr.row = mx.row;
	mr.column = mx.column;
	mr.matrix = matrix_setting(mr);

	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			mr.matrix[i][j] = mx.matrix[i][j];
			mr.matrix[i][j] *= n;
		}
	}

	return mr;
}

MAT matrix_scala_fraction(MAT mx, int n, int m)
{
	MAT mr;
	mr.row = mx.row;
	mr.column = mx.column;
	mr.matrix = matrix_setting(mr);
	int factor = 0;

	if (m == 1)
	{
		factor = n;
	}
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{

		}
	}
	return mr;
}

void matrix_input(MAT mx)
{
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			scanf_s("%d", &mx.matrix[i][j]);
		}
	}
}

void matrix_print(MAT mx, char name)
{
	printf("\n\n\n%c행렬\n", name);
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			printf("%d ", mx.matrix[i][j]);
		}
		printf("\n");
	}
}

int** matrix_setting(MAT mx)
{
	mx.matrix = malloc(sizeof(int*) * mx.row);

	//if (mx) { memset(mx, 0, sizeof(int)*mx.row); }
	if (mx.matrix)
	{
		memset(mx.matrix, 0, sizeof(int*) * mx.row);
		for (int i = 0; i < mx.row; i++)
		{
			*(mx.matrix + i) = malloc(sizeof(int) * mx.column);//TODO *(포인터 + i)와 포인터[i] 비교해보기
			memset(mx.matrix[i], 0, sizeof(int*) * mx.column);
		}
	}
	return mx.matrix;
}

void matrix_free(MAT mx)
{
	if (mx.matrix)
	{
		for (int i = 0; i < mx.row; i++)
		{
			free(*(mx.matrix + i));
		}
		free(mx.matrix);
		
		mx = reseted_m;
	}
}

MM create_matrix(MAT ma, MAT mb)
{
	MM result;
	
	matrix_free(ma);
	matrix_free(mb);

	printf("행렬 A의 행과 열의 개수를 입력하십시오.\n");

	scanf_s("%d %d", &ma.row, &ma.column);

	printf("\n\n행렬 B의 행과 열의 개수를 입력하십시오.\n");


	scanf_s("%d %d", &mb.row, &mb.column);

	ma.matrix = matrix_setting(ma);
	mb.matrix = matrix_setting(mb);

	printf("\n\n행렬 A의 요소를 입력하십시오.\n\n");
	matrix_input(ma);
	printf("\n\n행렬 B의 요소를 입력하십시오.\n\n");
	matrix_input(mb);

	system("cls");

	matrix_print(ma, 'A');
	matrix_print(mb, 'B');

	result.ma = ma;
	result.mb = mb;

	return result;
}

void main()
{
	MAT ma = reseted_m;
	MAT mb = reseted_m;//matrix A, B
	MAT mc = reseted_m;
	MM a;
	int sw = 1;

	while (sw)
	{
		printf("EdelKatze 행렬 연산 프로그램 ver.1.1 _____ 개발 일자 2022.05.22\n\n\n\n\n");
		printf("[프로그램 메인]\n");
		printf("* 행렬 연산을 수행하기 전, 반드시 먼저 행렬을 생성해주십시오.");
		if (ma.matrix)
		{
			printf("(현재 생성됨)\n\n");
		}
		else
		{
			printf("\n\n");
		}

		printf("[0]중지\n[1]행렬 생성");
		if (ma.matrix) { printf("(재생성 가능)"); }
		//printf("\n[2]행렬 곱 연산\n[3]행렬 합차 연산\n[4]행렬 스칼라 곱 연산\n\n");
		printf("\n[2]행렬 곱 연산\n[3]행렬 합차 연산\n[4]행렬 스칼라 곱 연산\n[5]행렬 보기\n\n");
		printf("입력 : ");
		scanf_s("%d", &sw);
		system("cls");
		printf("\n\n\n");
		switch (sw)
		{
		case 1:
			a = create_matrix(ma, mb);
			ma = a.ma;
			mb = a.mb;

			printf("\n\n\n\n");
			system("pause");

			break;
		case 2:
			if (ma.column == mb.row)
			{
				matrix_print(ma, 'A');
				matrix_print(mb, 'B');
				mc = matrix_multiple(ma, mb);
				printf("\n\n계산 결과");
				matrix_print(mc, 'C');
			}
			else
			{
				printf("행렬 곱 연산을 하려면\n첫 번째 행렬의 열의 수와\n두 번째 행렬의 행의 수가 같아야 합니다.");
			}

			printf("\n\n\n\n");
			system("pause");

			break;
		case 3:
			if (ma.column == mb.column && ma.row == mb.row)
			{
				printf("\n\n[1]합\n[2]차\n\n입력 : ");
				scanf_s("%d", &sw);

				switch (sw)
				{
				case 1:
					matrix_print(ma, 'A');
					matrix_print(mb, 'B');
					mc = matrix_sum(ma, mb, 0);
					printf("\n\n계산 결과");
					matrix_print(mc, 'C');
					break;
				case 2:
					matrix_print(ma, 'A');
					matrix_print(mb, 'B');
					mc = matrix_sum(ma, mb, 1);
					printf("\n\n계산 결과");
					matrix_print(mc, 'C');
					break;
				}
			}
			else
			{
				printf("행렬 합차 연산을 하려면\n두 행렬의 행과 열의 수가 같아야 합니다.");
			}
			printf("\n\n\n\n");
			system("pause");

			break;
		case 4:
			printf("\n\n어떤 행렬에 스칼라를 곱하시겠습니까?\n\n[1]행렬 A\n[2]행렬 B\n\n\n입력 : ");
			scanf_s("%d", &sw);
			int reply = 0;
			printf("\n\n어떤 스칼라를 곱하시겠습니까?(ver.1.1 : 스칼라는 정수 범위에서 정의)\n\n입력 : ");
			scanf_s("%d", &reply);
			system("cls");
			switch (sw)
			{
			case 1:
				mc = matrix_scala_integer(ma, reply);
				matrix_print(ma, 'A');
				printf("\n\n스칼라 : %d\n\n\n계산 결과", reply);
				matrix_print(mc, 'C');
				break;
			case 2:
				mc = matrix_scala_integer(mb, reply);
				matrix_print(mb, 'B');
				printf("\n\n스칼라 : %d\n\n\n계산 결과", reply);
				matrix_print(mc, 'C');
				break;
			}
			printf("\n\n\n\n");
			system("pause");
			
			break;
		case 5:
			if (ma.matrix && mb.matrix)
			{
				matrix_print(ma, 'A');
				matrix_print(mb, 'B');
				
			}
			else if (ma.matrix) { matrix_print(ma, 'A'); }
			else if (mb.matrix) { matrix_print(mb, 'B'); }
			else { printf("최소 하나 이상의 행렬이 생성되어 있어야 합니다."); }
			printf("\n\n\n\n");
			system("pause");
			
			break;
		}
		system("cls");
	}

	if (ma.matrix)	matrix_free(ma);
	if (mb.matrix)	matrix_free(mb);
	if (mc.matrix)	matrix_free(mc);
}