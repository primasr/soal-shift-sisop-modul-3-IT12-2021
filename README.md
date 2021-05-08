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
### Include Library
seperti biasa yang pertama kita include kan library yang kita butuhkan
```sh
// Include library yang diperlukan
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

```
lalu kita mendefine ukuran matrix yang akan digunakan
```sh
// Define ukuran matriks
#define MAX_SIZE 24
#define SIZE_A 4
#define SIZE_B 3
#define SIZE_C 6

```
mendefine ukuran matriks pada matriks B dan Matrix hasilnya
```sh
// Define ukuran matriks
int matrix_B[SIZE_A][SIZE_C];
int matrix_Hasil[SIZE_A][SIZE_C];
```
disini kita menggunaka fungsi void untuk menginput angka matrix yang mana int i sebagai baris di matriks dan int j sebagai kolom di matriks
```sh
// Fungsi input matrix
void inputMatrix(int arr[SIZE_A][SIZE_C], int r, int c){
	int i,j;
	//for i -> untuk baris
	//for j -> untuk kolom
	//Dari baris dan kolom, dapat posisi i,j	
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			scanf("%d",&arr[i][j]);    
		}    
	}    
}
```
disini kita menggunaka fungsi void untuk menampilkan angka matrix sesuai posisi dimana i sebagai baris dan j sebagai kolom
```sh
// Fungsi display matrix
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
sesuai dengan comment disini kita akan membuat struct yang didalamnya ada fungsi int (cell A, cell B, x dan y )
```sh

// Membuat struct untuk menyimpan beberapa variabel,
// yang akan dikirimkan melalui Thread ke fungsi
// Karena pada Thread, itu cuma bisa ngirim 1 variabel
// Jadi harus dibungkus 1, lalu dikirim bareng
struct arg_struct {
    int cell_A;
    int cell_B;
    int x;
    int y;
};

```
lalu disini kita membuat nama struct dengan bantuan typdef kemudian
int faktorial untuk membuat fungsi faktorial reskursif
```sh

// Mempersingkat penamaan struct
typedef struct arg_struct myStruct;

// Fungsi faktorial rekursif
int faktorial(int x) {
	// Jika 0/1 return 1
	// else panggil dirinya sendiri lalu kurangi 1
    if (x == 0 || x == 1) return 1;
    else return x*faktorial(x-1);
}

```
membuat fungsi void untuk fungsi tujuan thread dan penyelesain soal
```sh
// Fungsi tujuan Thread
// Fungsi utama penyelesaian soal
void *fungsiGaul(void *argx){
	
	// Deklarasi struct berdasarkan parameter yang didapatkan
	myStruct *args = (myStruct *)argx;

	// a adalah nilai dari cell A
	// b adalah nilai dari cell B
	// x1 adalah posisi baris
	// y1 adalah posisi kolom
	int a = args -> cell_A;
	int b = args -> cell_B;
	int x1 = args -> x;
	int y1 = args -> y;

	if (a == 0 || b == 0){		
		// Jika salah 1 cell itu 0, maka return 0
		matrix_Hasil[x1][y1] = 0;		
	} else if ( a >= b) {		
		// Jika a >= b, maka return a!/(a-b)!
		matrix_Hasil[x1][y1] = (faktorial(a)/faktorial(a-b));		
	} else if (b > a) {		
		// Jika b < a, maka return a!
		matrix_Hasil[x1][y1] = faktorial(a);			
	}

}


```
int main adalah bagian utamanya
```sh

int main()
{    


	// Keperluan Shared Memory
    key_t key = 1234;
    int (*matrix_A)[SIZE_C];
    int shmid = shmget(key, sizeof(int[SIZE_A][SIZE_C]), IPC_CREAT | 0666);
    matrix_A = shmat(shmid, NULL, 0);	

    // Deklarasi pthread
    pthread_t myThread[MAX_SIZE];
    // Deklarasi struct
    myStruct args;

    // Display matrix yang dikirimkan dari Program lain
    	printf("\nIni matrix A:\n");
    displayMatrix(matrix_A,SIZE_A, SIZE_C);    

    // Input matrix dari User
    	printf("\nInput Matrix B (4x6):\n");
    inputMatrix(matrix_B,SIZE_A,SIZE_C);  

    int i,j;
    int x = 0;
    // Loop sebanyak 4x6
    //for i -> baris
    //for j -> kolom
	for(i=0;i<SIZE_A;i++)    
	{    
		for(j=0;j<SIZE_C;j++)    
		{    
			// Isi struct dengan variabel yang diinginkan
			args.x = i;
			args.y = j;
			args.cell_A = matrix_A[i][j];
			args.cell_B = matrix_B[i][j];  
			// Call pthread_create
	    	if (pthread_create(&myThread[x],NULL, &fungsiGaul, (void *)&args) != 0)
	    	{
	            fprintf(stderr,"Error - pthread_create()\n");
	            exit(EXIT_FAILURE);
	    	}			
	    	// Langsung di join setelah di create
	    	pthread_join(myThread[i], NULL);
	    	x++; 	    	
		}   
	}     

	// Display matrix hasil
    	printf("\nIni matrix Hasil:\n");
    displayMatrix(matrix_Hasil,SIZE_A, SIZE_C); 

    // Keperluan Shared Memory
    shmdt(matrix_A);
    shmctl(shmid, IPC_RMID, NULL);   

    return 0;
}
