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

MAT matrix_multiple(MAT ma, MAT mb)
{
	MAT mc;
	mc.row = ma.row;
	mc.column = mb.column;
	mc.matrix = matrix_setting(mc);

	for (int i = 0; i < mc.row; i++)
	{
		for (int j = 0; j < mc.column; j++)
		{
			for (int l = 0; l < mb.row; l++)
			{
				mc.matrix[i][j] += ma.matrix[i][l] * mb.matrix[l][j];
			}
		}
	}

	return mc;
}

MAT matrix_sum(MAT ma, MAT mb, int minus)
{
	MAT mc;
	mc.row = ma.row;
	mc.column = mb.column;
	mc.matrix = matrix_setting(mc);

	for (int i = 0; i < mc.row; i++)
	{
		for (int j = 0; j < mc.column; j++)
		{
			if (minus == 1)
			{
				mc.matrix[i][j] = ma.matrix[i][j] - mb.matrix[i][j];
			}
			else
			{
				mc.matrix[i][j] = ma.matrix[i][j] + mb.matrix[i][j];
			}
		}
	}

	return mc;
}

int** matrix_scala(MAT mx, int n)
{
	for (int i = 0; i < mx.row; i++)
	{
		for (int j = 0; j < mx.column; j++)
		{
			mx.matrix[i][j] *= n;//TODO 분수를 곱하기 : %d/%d로 받아서 전자는 행렬에 곱하고 후자는 /%d로 표현
		}//TODO mx를 바꾸지 않고 값만 계산하여 새로운 행렬로 반환
	}

	return mx.matrix;
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

MM create_matrix(MAT ma, MAT mb)
{
	MM result;
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
	char trash[50];

	while (sw)
	{
		printf("EdelKatze 행렬 연산 프로그램 ver.1 _____ 개발 일자 2022.05.20\n\n\n\n\n");
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
		printf("\n[2]행렬 곱 연산\n[3]행렬 합차 연산\n\n");
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

			system("pause");

			break;
			/*case 4:
				printf("\n\n어떤 행렬에 스칼라를 곱하시겠습니까?\n\n[1]행렬 A\n[2]행렬 B\n\n\n입력 : ");
				scanf_s("%d", &sw);
				int reply = 0;
				printf("\n\n어떤 스칼라를 곱하시겠습니까?(ver.1 : 스칼라는 정수 범위에서 정의)\n\n입력 : ");
				scanf_s("%d", &reply);
				switch (sw)
				{
				case 1:
					mc.matrix = matrix_scala(ma, reply);
					matrix_print(ma, 'A');
					printf("\n\n스칼라 : %d\n\n계산 결과", reply);
					matrix_print(mc, 'C');
					break;
				case 2:
					mc.matrix = matrix_scala(mb, reply);
					matrix_print(mb, 'B');
					printf("\n\n스칼라 : %d\n\n계산 결과", reply);
					matrix_print(mc, 'C');
					break;
				}

				printf("\n\n메인으로 돌아가려면 아무거나 입력하십시오.\n\n");
				scanf_s("%s", trash, sizeof(trash));*/
		}
		system("cls");
	}

	for (int i = 0; i < ma.row; i++) { free(ma.matrix[i]); }
	for (int i = 0; i < mb.row; i++) { free(mb.matrix[i]); }
	free(ma.matrix);
	free(mb.matrix);
}