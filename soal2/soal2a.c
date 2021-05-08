// Include library yang diperlukan
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

// Define ukuran matriks
#define MAX_SIZE 24
#define SIZE_A 4
#define SIZE_B 3
#define SIZE_C 6

// Inisiasi matrix A dan matrix B
// Matrix A 	= 4x3
// Matrix B 	= 3x6
// Matrix Hasil = 4x6
int matrix_A[SIZE_A][SIZE_B] = 
{
	{1,1,2},
	{0,2,1},
	{1,1,1},
	{3,1,2}
};
int matrix_B[SIZE_B][SIZE_C] = 
{
	{2,1,3,1,0,1},
	{1,1,1,4,1,1},
	{1,5,1,0,1,2}
};

/*
Formula perkalian matrix
a b x | e f
c d y | g h
      | i j

a*e + b*g + x*i | a*f + b*h + x*j
dst...
*/

// Fungsi perkalian matrix
void perkalianMatrix(int arr[SIZE_A][SIZE_C], int r, int c)
{
	int i,j,k;
	//for i -> untuk baris
	//for j -> untuk kolom
	//for k -> untuk iterasi sebanyak kolom untuk, 
	//melakukan penjumlahan antar cell
	//Dari baris dan kolom, dapat posisi i,j	
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			arr[i][j]=0;    
			for(k=0;k<c;k++)    
			{    
				arr[i][j]+=matrix_A[i][k]*matrix_B[k][j];    
			}    
		}    
	}    	
}

// Fungsi menampilkan matrix A
void displayMatrixA(int r, int c){
	int i,j;
	//for i -> untuk baris
	//for j -> untuk kolom
	//Dari baris dan kolom, dapat posisi i,j	
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d ",matrix_A[i][j]);    
		}    
		printf("\n");    
	}    	
}

// Fungsi menampilkan matrix B
void displayMatrixB(int r, int c){
	int i,j;
	//for i -> untuk baris
	//for j -> untuk kolom
	//Dari baris dan kolom, dapat posisi i,j	
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d ",matrix_B[i][j]);    
		}    
		printf("\n");    
	}    	
}

// Fungsi menampilkan matrix Hasil
void displayMatrix(int arr[SIZE_A][SIZE_C], int r, int c){
	int i,j;
	//for i -> untuk baris
	//for j -> untuk kolom
	//Dari baris dan kolom, dapat posisi i,j	
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d ",arr[i][j]);    
		}    
		printf("\n");    
	}    	
}

int main () {

	// Keperluan shared memory
    key_t key = 1234;
    int (*matrix_Hasil)[SIZE_C];
    int shmid = shmget(key, sizeof(int[SIZE_A][SIZE_C]), IPC_CREAT | 0666);
    matrix_Hasil = shmat(shmid, NULL, 0);   

    // Display matrix A dan B
		printf("\nDisplay Matrix A:\n");
	displayMatrixA(SIZE_A, SIZE_B);
		printf("\nDisplay Matrix B:\n");
	displayMatrixB(SIZE_B, SIZE_C);		

	// Call perkalian matrix
	perkalianMatrix(matrix_Hasil,SIZE_A, SIZE_C);

	// Display matrix Hasil
		printf("\nDisplay Matrix Hasil:\n");
	displayMatrix(matrix_Hasil,SIZE_A, SIZE_C);

	// Perlu di sleep. Agar proses shared memory memiliki,
	// waktu cukup untuk menggunakan memory tersebut
	sleep(30);

	// Keperluan shared memory
    shmdt(matrix_Hasil);
    shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
