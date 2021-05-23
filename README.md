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

## Soal 2.b
### Include Library
seperti biasa yang pertama kita ```include``` kan library yang kita butuhkan
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
mendefine ukuran matriks pada ```matriks B dan Matrix hasilnya```
```sh
// Define ukuran matriks
int matrix_B[SIZE_A][SIZE_C];
int matrix_Hasil[SIZE_A][SIZE_C];
disini kita menggunaka fungsi void untuk menginput angka matrix yang mana int i sebagai baris di matriks dan int j sebagai kolom di matriks
sh
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
sesuai dengan comment disini kita akan membuat struct yang didalamnya ada fungsi ``` int (cell A, cell B, x dan y )```
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

membuat fungsi void untuk fungsi tujuan thread dan penyelesain soal
sh
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
int main adalah bagian utamanya, yang pertama kita lakukan adalah membuat keperluan shared memory nya lalu dibagian ```pthread_t myThread[MAX_SIZE] ``` 
kita mendeklarasikan pthread nya sedangkan  untuk mendeklarasikan fungsi struct kita memanggil nama yg sudah kita buat ```myStruct args```
kemudian menampilkan matrix yang dikirimkan dari Program lain dengan bantuan ```  printf("\nIni matrix A:\n") ```. selanjutnya  untuk mencetak nilai matrix dari user kita menngunakan ``` printf("\nInput Matrix B (4x6):\n") ```
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

Terakhir kita buat fungsi ```main```. Pertama kita mendeklari pid terlebih dahulu yakni ```pid_t cid```, selanjutnya kita mendefinisikan ```status``` yang akan digunakan dalam proses while wait. Kemudian kita mendeklarasikan 2 pipe yakni ```fp1``` dan ```fp2``` yang mana nantinya kita gunakan dalam proses Error handling semisal proses piping terjadi masalah dengan cara menampikan ```printf``` yang berisikan "Gagal Piping". Selanjutnya dimulai proses ```fork``` jika ```cid < 0``` maka ditampilkan "Gagal Forking" dan kemudian akan di ```exit```. Jika ```cid == 0``` maka akan dijalankan proses ```if else``` yakni dalam proses childnya akan memanggil ```fungsi_ps```. Dan jika ```else``` akan menjalankan parentnya menggunakan ```while wait``` yang mana akan dijalankan menunggu proses child selesai terlebih dahulu. Selanjutkan akan dilakukan proses ```fork``` kedua yang mana jika ```cid < 0``` maka akan langsung exit menampilkan "Gagal forking kedua", namun semisal ```cid == 0``` maka program akan dijalankan lagi dengan proses child yang memanggil ```fungsi_sort``` dan bila ```else``` maka akan dijalankan kembali proses parent yang nantinya akan memanggil ```fungsi_head```. Terakhir kita memberi ```return (0)``` yang menandakan program telah selesai dijalankan.
```sh
int main() {
	// Deklarasi pid
	pid_t cid;
	// Status untuk proses while wait
	int status;
	// Deklarasi 2 pipe
	int fp1[2];
	int fp2[2];
	 
	// Error handling semisal proses Piping ada masalah
	if (pipe(fp1) == -1){	  
	  printf("Gagal Piping\n");
	  return 1;
	}
	 
	if (pipe(fp2)== -1){
	  printf("Gagal Piping\n");
	  return 1;
	}
	 
	// Start fork
	cid = fork();
	// Jika < 0, maka gagal forking
	if (cid < 0) {
		printf("Gagal Forking\n");
		exit(EXIT_FAILURE);
	}
	 
	if (cid == 0) {
		// ini child
		close(fp1[0]);
		dup2(fp1[1], STDOUT_FILENO);
		// Call fungsi ps
		fungsi_ps();
	} else {
		// ini parent
		// wait, tunggu anaknya selesai
		while ((wait(&status)) > 0);
		// start forking kedua
		cid = fork();
		// jika gagal, langsung exit
		if (cid < 0) {
			printf("Gagal Forking Kedua\n");
			exit(EXIT_FAILURE);
		}
		if (cid == 0){
			// ini child
			close(fp1[1]);
			dup2(fp1[0], STDIN_FILENO);
			close(fp2[0]);
			dup2(fp2[1], STDOUT_FILENO);
			// Call fungsi sort
			fungsi_sort();
		} else{
			// ini parent
			
			close(fp2[1]);
			close(fp1[1]);    
			// tunggu lagi
			while ((wait(&status)) > 0);
			
			dup2(fp2[0], STDIN_FILENO);
			// call fungsi head
			fungsi_head();
		}
	}
	return 0;
}
```
## Soal 3

[Link Soal](https://docs.google.com/document/d/1ud1JyncoSDAo5hA03wPvjn7QBHPUeUG1eBJ8ETtq2dQ/edit)
[Link Source Code Soal 3](https://github.com/primasr/soal-shift-sisop-modul-3-IT12-2021/blob/main/soal3/soal3.c)

Inti dari soal:

1. Membuat program otomasi untuk melakukan kategorisasi file. Dimana nanti akan dibuat sebuah folder dengan nama sesuai dengan extension yang ada didalamnya
2. Ada 3 mode program:
2.1. Mode Pertama (opsi -f) = Program melakukan kategorisasi pada beberapa file yang diinputkan melalui argument ketika melakukan execute program. Contoh execute: ```./exe -f lagu.mp3 gambar.png```
text.txt
2.2. Mode Kedua (opsi -d) = Program melakukan kategorisasi pada suatu folder lalu hasil kategorisasinya dibawa keluar folder tersebut. Contoh execute: ```./exe -d /path/namafolder ```
2.3. Mode Ketiga (opsi *) = Program melakukan kategorisasi pada folder file execute dijalankan. Contoh execute: ```./exe *```

### Include Library
```sh
// Include library yang dibutuhkan
#include <pthread.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
```
### Define Global Variable
Asumsi ukuran maksimal penamaan adalah 256 karakter.
```check```, ```iter```, dan ```once``` dibutuhkan untuk keperluan menentukan program nantinya
```sh
// define max size
#define MAX_SIZE 256

// define global variable
char cwd[MAX_SIZE];
int check;
int iter = 0;
int once = 0;
```
### Deklarasi Fungsi
```sh
// DEKLARASI FUNGSI

// Fungsi untuk mengecek apakah,
// yang di cek berupa Direktori atau bukan
int isDirectory(const char *myPath);

// Fungsi memindah file
void *pindahFile(void *filename);

```
### Main Program
```sh
#pragma GCC diagnostic ignored "-Wformat-zero-length"
int main(int argc, char **argv) 
{
  // Cek argument. Jika salah langsung exit 
  if (argc < 2)
  {
    puts("Masukan argumen dengan benar (-d / -f / *)");
    return 0;
  }

  getcwd(cwd, sizeof(cwd));

  
  if (strcmp(argv[1], "-f") == 0)
  {
    // Ini program pertama (-f)
    printf("");
    check = 0;
    pthread_t myThreads[argc - 2];
    int i = 2;
    while(i < argc){

      // Jika direktori, maka ga bisa  
      if(isDirectory(argv[i])){
        printf("%s adalah direktori\n", argv[i]);
      }
      else{
        // Create pthread
        pthread_create(&myThreads[i-2], NULL, pindahFile, argv[i]);
      }

      i++;
    }    

    // join pthread
    i = 0;
    while(i < argc-2){
      pthread_join(myThreads[i], NULL);
      i++;
    }

  }
  else if (strcmp(argv[1], "-d") == 0 && argc == 3)
  {
    // Ini program kedua (-d)
    printf("");
    check = 1;
    int banyakFile = 0;
    char files[MAX_SIZE][MAX_SIZE];

    DIR *d;
    struct dirent *dir;
    chdir(argv[2]);
    d = opendir(".");

    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0){
          continue;
        }
        
        // Jika direktori, maka ga bisa  
        if(isDirectory(dir->d_name))
        {
          printf("%s adalah direktori\n", dir->d_name);
        }
        else
        {
          char tmp[100];
          strcpy(tmp, dir->d_name);
          sprintf(files[banyakFile], "%s/%s", argv[2], dir->d_name);
          banyakFile++;                  
        }
      }
      closedir(d);
    }

    chdir(cwd);
    pthread_t myThreads[banyakFile];

    // create pthread
    int i = 0; 
    while(i < banyakFile){
      pthread_create(&myThreads[i], NULL, pindahFile, files[i]);
      i++;
    }

    // join pthread
    i = 0;
    while(i < banyakFile){
      pthread_join(myThreads[i], NULL);
      i++;
    }        

  }
  else if (strcmp(argv[1], "*") == 0 && argc == 2)
  {
    // Ini program ketiga (\*)
    printf("");
    int banyakFile = 0;
    char files[MAX_SIZE][MAX_SIZE];

    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0){
          continue;
        }
          
        // Jika direktori, maka ga bisa  
        if(isDirectory(dir->d_name))
        {
          printf("%s adalah direktori\n", dir->d_name);
        }
        else
        {
          char tmp[100];
          strcpy(tmp, dir->d_name);
          sprintf(files[banyakFile], "%s", dir->d_name);
          banyakFile++;          
        }
      }
      closedir(d);

    }

    pthread_t myThreads[banyakFile];
    int i = 0;
    // create pthread
    while(i < banyakFile){
      pthread_create(&myThreads[i], NULL, pindahFile, files[i]);
      i++;
    }     
      
    // join pthread
    i = 0;
    while(i < banyakFile){
      pthread_join(myThreads[i], NULL);
      i++;
    }    
      
  }
  else{
    puts("Masukan argumen dengan benar (-d / -f / *)");
  }
    
  return 0;
}
#pragma GCC diagnostic warning "-Wformat-zero-length"
```
### Isi dari Fungsi yang telah dibuat
```sh
// Mengecek suatu file itu merupakan direktori atau bukan
int isDirectory(const char *myPath)
{
  struct stat myPath_stat;
  stat(myPath, &myPath_stat);
  return S_ISDIR(myPath_stat.st_mode);
}

// Fungsi memindah file
void *pindahFile(void *filename) 
{
  // Deklarasi nilai sumber
  char *sumber = (char *)filename;
  char sumberBaru[MAX_SIZE];
  strcpy(sumberBaru, sumber);

  // Deklarasi nilai target
  char *target = strrchr(sumberBaru, '/');
  char namaFileBaru[MAX_SIZE];  

  if(target){
    strcpy(namaFileBaru, target + 1);
  }
  else{
    strcpy(namaFileBaru, sumberBaru);
  }

  const char *dot = strrchr(namaFileBaru, '.');
  struct stat st = {0};
  char folder[MAX_SIZE];

  if(!dot || dot == sumberBaru){
    strcpy(folder, "Unknown");
  }    
  else
  {
    strcpy(folder, dot + 1);
    int i = 0;
    while(folder[i]!='\0')
    {
      if(folder[i]>='A' && folder[i]<='Z')
        folder[i] += 32;
      i++;
    }
  }

  // Mulai processing file
  int ch;
  FILE *file1, *file2;

  if(!target){
    target = sumberBaru;
  }
  else{
    target = target + 1;    
  }

  // Deklarasi variabel targetBaru
  char targetBaru[MAX_SIZE];
  sprintf(targetBaru, "%s/%s/%s", cwd, folder, target);

  // untuk cek apakah akses file error
  int x1 = 0,y1 = 0;

  file1 = fopen(sumberBaru, "r");

  if (!file1) 
  {
    printf("Tidak bisa dibuka :( %s!\n", sumberBaru);
    x1 = 1;
    pthread_exit(NULL); 
    return NULL;
  }

  if (stat(folder, &st) == -1)
    mkdir(folder, 0700);

  file2 = fopen(targetBaru, "w");

  if (!file2) 
  {
    printf("Tidak bisa dibuka :( %s!\n", targetBaru);
    y1 = 1;
    pthread_exit(NULL); 
    return NULL;
  }  

  while ((ch = fgetc(file1)) != EOF){
    fputc(ch, file2);
  } 

  // check menandakan dia program pertama (-f) atau kedua (-d) 
  if (check == 0)
  {
    iter++;
    // jika gagal, print gagal
    if (x1 == 1 || y1 == 1) {
      printf("File %d: Sad, gagal :(\n", iter);
    } else {
      printf("File %d: Berhasil Dikategorikan\n", iter);
    }
  } else {
    if (once == 0) {      
      once = 1;
      if (x1 == 1 || y1 == 1) {
        printf("Yah, gagal disimpan :(\n");
      } else {
        printf("Direktori sukses disimpan\n");
      }          
    }
  }

  //close file
  fclose(file1);
  fclose(file2);

  //remove new sumber nya
  remove(sumberBaru);

  //exit pthread
  pthread_exit(NULL); 

}
```
