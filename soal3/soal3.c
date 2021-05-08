// Include library yang dibutuhkan
#include <pthread.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

// define max size
#define MAX_SIZE 256

// define global variable
char cwd[MAX_SIZE];
int check;
int iter = 0;
int once = 0;

// DEKLARASI FUNGSI

// Fungsi untuk mengecek apakah,
// yang di cek berupa Direktori atau bukan
int isDirectory(const char *myPath);

// Fungsi memindah file
void *pindahFile(void *filename);

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
