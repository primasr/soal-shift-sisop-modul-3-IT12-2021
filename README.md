# soal-shift-sisop-modul-3-IT12-2021
Soal Shift Modul 3


Kelompok IT 12 yang beranggotakan:

- Prima Secondary Ramadhan  (05311940000001)
- Shavica Ihya Qurata Ayun L . (05311940000013)
- Sri Puspita Dewi (05311940000045)

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
// Include library yang diperlukan
#define MAX_SIZE 24
#define SIZE_A 4
#define SIZE_B 3
#define SIZE_C 6
```

Kemudian kita menginisiasi masing-masing nilai ukuran Matrix A dan Matrix B yang nantinya akan kita operasikan dalam perkalian Matrix
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
// Fungsi perkailan matrix
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
## Soal 2.b
