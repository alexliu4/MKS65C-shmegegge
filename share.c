#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main(){

  key_t key;
  int shmid;
  char *data;

  //fork to key
  key = ftok("file", 'R');

  //int shmget(key_t key, size_t size, int shmflg);
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  printf("%d\n", shmid);

  //void *shmat(int shmid, void *shmaddr, int shmflg);
  data = shmat(shmid, (void *)0, 0);
  // checks error
  if (data == (char *)(-1))
    perror("shmat");
  // printf("%s\n", data);

  if (!data[0]){
    printf("Just created\n");}
  else{
    printf("Displaying contents: %s\n", data);
  }

  printf("Would you like to change the data in the segment?\n");
  char * answer = malloc (200);
  fgets(answer, 200, stdin);

  if(strcmp(answer,"yes\n")==0){
    printf("Enter new string\n");
    fgets(answer, 200, stdin);
    strncpy(data,answer,200);
    answer[strlen(answer) - 1] = 0;
    strncpy(data, answer, 200);
    printf("The data in the shared memory segment is now: %s\n", data);
  }

  printf("Would you like to delete the segment?\n");
  char * answer1 = malloc (5);
  fgets(answer1, 5, stdin);
  if(strcmp(answer1,"yes\n")==0){
    printf("Deleting segment\n");
    shmctl(shmid, IPC_RMID, NULL);
  }
  return 0;
}
