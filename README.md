# soal-shift-sisop-modul-3-IT12-2021
Soal Shift Modul 3


Kelompok IT 12 yang beranggotakan:

- Prima Secondary Ramadhan  (05311940000001)
- Shavica Ihya Qurata Ayun L . (05311940000013)
- Puspita Dewi

## Soal 2.a

### Include Library
Pertama, kita include library yang dibutuhkan terlebih dahulu
```sh
// Include library yang diperlukan
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
```

Selanjutnya kita mendefine ukuran matriks yang diperlukan dalam soal yakni membuat program hasil perkalian matrix (4x3 dengan 3x6)
```sh
// Define ukuran matriks
#define MAX_SIZE 24
#define SIZE_A 4
#define SIZE_B 3
#define SIZE_C 6
```

Kemudian kita menginisiasi masing-masing nilai ukuran ```matrix_A``` dan ```matrix_B``` yang nantinya akan kita operasikan dalam program perkalian Matrix ini
```sh
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
```

Lalu, kita memasukkan fungsi yang sesuai dengan formula perkalian matriks menggunakan perulangan ```for``` loop
```sh
// Fungsi perkalian matrix
void perkalianMatrix(int arr[SIZE_A][SIZE_C], int r, int c)
{
	int i,j,k;	
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
```

Kemudian kita membuat fungsi yang nantinya digunakan untuk menampilkan nilai dari ```matrix_A``` dan ```matrix_B``` yakni dengan ```void``` ```displayMatrixA``` dan ```displayMatrixB``` menggunakan ```for``` loop i untuk baris dan j untuk kolom
```sh
void displayMatrixA(int r, int c){
	int i,j;	
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
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d ",matrix_B[i][j]);    
		}    
		printf("\n");    
	}    	
}

```

Berikutnya kita membuat fungsi yang digunakan untuk menampilkan hasil dari perkalian Matriks nantinya menggunakan ```void``` ```displayMatrix```
```sh
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
```

Terakhir kita buat fungsi ```main``` dengan berisikan ragam fungsi yang digunakan untuk keperluan shared memory seperti ```key_t key```,```shmid```,```shmat```,```shmdt```,```shmctl```. Nantinya dalam fungsi ```main``` terdapat fungsi yang berguna untuk memprint/menampilkan nilai dari ```displayMatrixA``` dan ```displayMatrixB```. Selanjutnya akan dipanggil fungsi ```perkalianMatrix``` sehingga nanti akan ditampilkan nilai hasil dari ```matrix_Hasil``` menggunakan ```displayMatrix```. Program juga memerlukan ```sleep(30)``` agar proses shared memory memiliki waktu yang cukup dalam menjalankan program tersebut. Terakhir kita memberi ```return (0)``` yang menandakan program telah selesai dijalankan.
```sh
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
```

## Soal 2.c

### Include Library
Pertama, kita include library yang dibutuhkan terlebih dahulu
```sh
// Include library yang diperlukan
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
```

Disini kita mendeclare fungsi untuk ps aux sesuai perintah soal
```sh
// Diclare fungsi untuk ps aux
void fungsi_ps(){
	char *argv[] = {"ps","aux", NULL};
	execv("/bin/ps", argv);	
}
```

Disini kita mendeclare fungsi untuk sort -nrk 3,3 sesuai perintah soal
```sh
// Diclare fungsi untuk sort -nrk 3,3
void fungsi_sort(){
    char *argv[] = {"sort","-nrk","3,3", NULL};
    execv("/usr/bin/sort", argv);
}
```

Disini kita mendeclare fungsi untuk head -5 sesuai perintah soal
```sh
// Diclare fungsi untuk head -5
void fungsi_head(){
    char *argv[] = {"head", "-5", NULL};
    execv("/usr/bin/head", argv);	
}
```

Kemudian kita menginisiasi masing-masing nilai ukuran ```matrix_A``` dan ```matrix_B``` yang nantinya akan kita operasikan dalam program perkalian Matrix ini
```sh
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
```

Lalu, kita memasukkan fungsi yang sesuai dengan formula perkalian matriks menggunakan perulangan ```for``` loop
```sh
// Fungsi perkalian matrix
void perkalianMatrix(int arr[SIZE_A][SIZE_C], int r, int c)
{
	int i,j,k;	
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
```

Kemudian kita membuat fungsi yang nantinya digunakan untuk menampilkan nilai dari ```matrix_A``` dan ```matrix_B``` yakni dengan ```void``` ```displayMatrixA``` dan ```displayMatrixB``` menggunakan ```for``` loop i untuk baris dan j untuk kolom
```sh
void displayMatrixA(int r, int c){
	int i,j;	
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
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d ",matrix_B[i][j]);    
		}    
		printf("\n");    
	}    	
}

```

Berikutnya kita membuat fungsi yang digunakan untuk menampilkan hasil dari perkalian Matriks nantinya menggunakan ```void``` ```displayMatrix```
```sh
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
```

Terakhir kita buat fungsi ```main``` dengan berisikan ragam fungsi yang digunakan untuk keperluan shared memory seperti ```key_t key```,```shmid```,```shmat```,```shmdt```,```shmctl```. Nantinya dalam fungsi ```main``` terdapat fungsi yang berguna untuk memprint/menampilkan nilai dari ```displayMatrixA``` dan ```displayMatrixB```. Selanjutnya akan dipanggil fungsi ```perkalianMatrix``` sehingga nanti akan ditampilkan nilai hasil dari ```matrix_Hasil``` menggunakan ```displayMatrix```. Program juga memerlukan ```sleep(30)``` agar proses shared memory memiliki waktu yang cukup dalam menjalankan program tersebut. Terakhir kita memberi ```return (0)``` yang menandakan program telah selesai dijalankan.
```sh
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
```

