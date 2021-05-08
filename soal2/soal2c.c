// Include library yang diperlukan
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Diclare fungsi untuk ps aux
void fungsi_ps(){
	char *argv[] = {"ps","aux", NULL};
	execv("/bin/ps", argv);	
}

// Diclare fungsi untuk sort -nrk 3,3
void fungsi_sort(){
    char *argv[] = {"sort","-nrk","3,3", NULL};
    execv("/usr/bin/sort", argv);
}

// Diclare fungsi untuk head -5
void fungsi_head(){
    char *argv[] = {"head", "-5", NULL};
    execv("/usr/bin/head", argv);	
}
 
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
