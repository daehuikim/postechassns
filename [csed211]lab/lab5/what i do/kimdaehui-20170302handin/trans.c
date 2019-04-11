//andrea0119
/*
* trans.c - Matrix transpose B = A^T
*
* Each transpose function must have a prototype of the form:
* void trans(int M, int N, int A[N][M], int B[M][N]);
*
* A transpose function is evaluated by counting the number of misses
* on a 1KB direct mapped cache with a block size of 32 bytes.
*/
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_32_32(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]);
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]);

/*
* transpose_submit - This is the solution transpose function that you
*     will be graded on for Part B of the assignment. Do not change
*     the description string "Transpose submission", as the driver
*     searches for that string to identify the transpose function to
*     be graded.
*/
char transpose_submit_desc[] = "Transpose submission";

//test case���� ���ǹ����� ����
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
	switch (M) {
	case 32:
		transpose_32_32(M, N, A, B);
		break;
	case 64:
		transpose_64_64(M, N, A, B);
		break;
	case 61:
		transpose_61_67(M, N, A, B);
		break;
	}
}

/*
* You can define additional transpose functions below. We've defined
* a simple one below to help you get started.
*/
char transpose_32_32_desc[] = "Transpose the 32 x 32 matrix";
void transpose_32_32(int M, int N, int A[N][M], int B[M][N]) {
	
	int BLOCK_SIZE;
	int rowIndex;
	int colIndex;
	int blockedRowIndex; 
	int blockedColIndex; 
	int eBlockDiagl; 
	int iBlockDiagl; 
	BLOCK_SIZE = 8;
	//32 32�ε� int�� 4byte�̹Ƿ� block size��8�� line�̿��� �Ѵ�.
	for (colIndex = 0; colIndex < M; colIndex += BLOCK_SIZE) {
		for (rowIndex = 0; rowIndex < N; rowIndex += BLOCK_SIZE) {
			//transpose�� �ش���ġ�� �µ��� ���ش�.
			for (blockedRowIndex = rowIndex; blockedRowIndex < rowIndex +
				BLOCK_SIZE; ++blockedRowIndex) {
				for (blockedColIndex = colIndex; blockedColIndex < colIndex
					+ BLOCK_SIZE; ++blockedColIndex) {
					if (blockedRowIndex != blockedColIndex) {
						B[blockedColIndex][blockedRowIndex] =
							A[blockedRowIndex][blockedColIndex];
					}
					else {
						eBlockDiagl = A[blockedRowIndex][blockedColIndex];
						iBlockDiagl = blockedRowIndex;
					}
				}
				//diagonal�� element�� ���� ó��
				if (colIndex == rowIndex) {
					B[iBlockDiagl][iBlockDiagl] = eBlockDiagl;
				}
			}
		}
	}
}

char transpose_64_64_desc[] = "Transpose the 64 x 64 matrix";
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]) {
	int rowIndex, colIndex;
	int reg1, reg2, reg3, reg4, reg5, reg6, reg7, reg8;
	//64 64�� ��������(�����δ¸޸����� �������ͷ� �����ϴ� ��)�� ���� ������ �� �� ���� ���ϵ����Ѵ�.
	int ct; 
	for (rowIndex = 0; rowIndex < N; rowIndex += 8) {
		for (colIndex = 0; colIndex < M; colIndex += 8) {
			//8�������� �������͸� ����ϱ� ������ index�� 8�� �������ش�.
			for (ct = 0; ct < 8; ct++) {
				reg1 = A[colIndex + ct][rowIndex];
				reg2 = A[colIndex + ct][rowIndex + 1];
				reg3 = A[colIndex + ct][rowIndex + 2];
				reg4 = A[colIndex + ct][rowIndex + 3];
				//ct���� �̿��Ͽ� ù miss���� ��������
				if (0 == ct) {
					reg5 = A[colIndex + ct][rowIndex + 4];
					reg6 = A[colIndex + ct][rowIndex + 5];
					reg7 = A[colIndex + ct][rowIndex + 6];
					reg8 = A[colIndex + ct][rowIndex + 7];
				}
				B[rowIndex][colIndex + ct] = reg1;
				B[rowIndex][colIndex + ct + 64] = reg2;
				B[rowIndex][colIndex + ct + 128] = reg3;
				B[rowIndex][colIndex + ct + 192] = reg4;
			}
			for (ct = 7; ct > 0; ct--) {
				//������ ���鿡 ���� ó��
				reg1 = A[colIndex + ct][rowIndex + 4];
				reg2 = A[colIndex + ct][rowIndex + 5];
				reg3 = A[colIndex + ct][rowIndex + 6];
				reg4 = A[colIndex + ct][rowIndex + 7];
				B[rowIndex + 4][colIndex + ct] = reg1;
				B[rowIndex + 4][colIndex + ct + 64] = reg2;
				B[rowIndex + 4][colIndex + ct + 128] = reg3;
				B[rowIndex + 4][colIndex + ct + 192] = reg4;
			}
			B[rowIndex + 4][colIndex] = reg5;
			B[rowIndex + 4][colIndex + 64] = reg6;
			B[rowIndex + 4][colIndex + 128] = reg7;
			B[rowIndex + 4][colIndex + 192] = reg8;
		}
	}
}

char transpose_61_67_desc[] = "Transpose the 61 x 67 matrix";
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]) {
	int rowIndex, colIndex;
	int blockedRowIndex, blockedColIndex; 
	int temp;
	//�� ���� m=61�� case�̱� ������ 32x32�� ���� �����Ѵ�.(�� 67�� �����ϱ� ������ blocksize=16������)
	for (rowIndex = 0; rowIndex < N; rowIndex += 16) {
		for (colIndex = 0; colIndex < M; colIndex += 4) {
			for (blockedRowIndex = rowIndex; (blockedRowIndex < rowIndex + 16) &&
				(blockedRowIndex < N); ++blockedRowIndex) {
				for (blockedColIndex = colIndex; (blockedColIndex < colIndex + 4)
					&& (blockedColIndex < M); ++blockedColIndex) {
					if (blockedRowIndex - rowIndex ==
						blockedColIndex - colIndex) {
						temp = A[blockedRowIndex][blockedColIndex];
					}
					else { 
						B[blockedColIndex][blockedRowIndex] =
							A[blockedRowIndex][blockedColIndex];
					}
				}
				for (blockedColIndex = colIndex; (blockedColIndex <
					colIndex + 4) && (blockedColIndex < M); ++blockedColIndex) {
					if (blockedRowIndex - rowIndex ==
						blockedColIndex - colIndex) {
						B[blockedColIndex][blockedRowIndex] = temp;
					}
				}
			}
		}
	}
}

/*
* trans - A simple baseline transpose function, not optimized for the cache.
*/
char trans_desc[] = "Simple r w-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N]) {
	int i, j, tmp;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			tmp = A[i][j];
			B[j][i] = tmp;
		}
	}
}

/*
* registerFunctions - This function registers your transpose
*     functions with the driver.  At runtime, the driver will
*     evaluate each of the registered functions and summarize their
*     performance. This is a handy way to experiment with different
*     transpose strategies.
*/
void registerFunctions() {
	/* Register your solution function */
	registerTransFunction(transpose_submit, transpose_submit_desc);
	/* Register any additional transpose functions */
	//  registerTransFunction(trans, trans_desc); 
}

/*
* is_transpose - This helper function checks if B is the transpose of
*     A. You can check the correctness of your transpose by calling
*     it before returning from the transpose function.
*/
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; ++j) {
			if (A[i][j] != B[j][i]) {
				return 0;
			}
		}
	}
	return 1;
}
