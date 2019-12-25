////////////////////////////////////////////////////////////////////////////////////////////////////////////////gradebook.c/////////////////////////////////////////////////////////
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <regex.h>
#include <stdbool.h>
#define TEACHER_STUDENT 414
#define NAME 426
#define PASS 2019
#define TEACHER 131

void student_loop();
void teacher_loop();
void admin_loop();

int login_loop() {
  while(1){
    // defenses against string vulnerabilities
    char *idFormat = "Id: ", *passFormat = "Password: ";
    char *id = prompt_until_valid(VT_ID, idFormat);
    char *password = prompt_until_valid(VT_PASSWORD, passFormat);

    char id_buff[8] = {0};
    int maxId;

    FILE *fd;
    if((fd = fopen("data/private/login_last_id.txt","r")) != NULL){
      fgets(id_buff, 7, fd);
      maxId = atoi(id_buff) + 1;
    } else {
      printf("Not Authorized\n");
      continue;
    }

    int counter = 100001;
    int idNum = atoi(id);

    if(idNum > maxId){
      printf("Not Authorized\n");
      continue;
    }

    FILE *fp;
    fp = fopen("data/private/login_all_id.txt","r");
    char stringBuff[150] = {0};

    while(counter <= idNum){
      fgets(stringBuff, 145, fp);
      counter++;
    }

    char *identity, *name, *pword, *usertype;
    identity = strtok(stringBuff, ",");
    name = strtok(NULL, ",");
    pword = strtok(NULL, ",");
    usertype = strtok(NULL, ",");

    int utype = atoi(usertype);

    if ((strncmp(password, pword, strlen(pword)) == 0) &&
        (strncmp(id, identity, strlen(identity)) == 0)) {

      if (utype == 1) {
        student_loop(name,id);
      } else if (utype == 2) {
        teacher_loop(name,id);
      } else {
        printf("error\n");
      }
    } else {
      printf("Not authorized\n");
    }
  }
}



// Create a directory if it does not exist
int ensure_dir(const char* path) {
  DIR* dir = opendir(path);
  struct stat ss;
  if (stat(path, &ss)) {
    if (errno == ENOENT) {
      return mkdir(path, 0755);
    } else {
      return 1;
    }
  }

  return 0;
}

#define ENSURE_OR_FAIL(d) if (ensure_dir(d)) { printf("failed to ensure %s (%d)\n", d, errno); return 1; }
// Initialize required directories of gradebook
int init_dirs() {
  ENSURE_OR_FAIL("data")
  ENSURE_OR_FAIL("data/private")

  return 0;
}

int init_admin_cred() {
  FILE* fd = fopen(ADMIN_FILE, "r");
  if (fd != NULL) {
    return fclose(fd);
  }

  if (errno == ENOENT) {
    fd = fopen(ADMIN_FILE, "w");
    if (fd == NULL) {
      return 1;
    }

    srand(time(NULL));
    int i = 0;
    char cred[33] = {0};
    while (i < 32) {
      cred[i] = (rand() % 10) + '0';
      i++;
    }

    fprintf(fd,"%s", cred/*"change.this.or.no.points.kidding"*/);
    return fclose(fd);
  }

  return 1;
}

int main() {
  //srand(time(NULL));

  if (init_dirs()) {
    // format string vulnerability defense
    char *failed = "init_dirs() failed\n";
    printf("%s", failed);
    return 1;
  }

  if (init_admin_cred()) {
    // format string vulnerability defense
    char *failed = "init_admin_cred() failed\n";
    printf("%s", failed);
    return 1;
  }

  char* s = "Login or signup: ";
  char* input = prompt_until_valid(VT_MODE, s);
  // strncmp instead of strcmp to defend against buffer overflow
  if (strncmp(input, "login", 5) == 0) {
    login_loop();
  // strncmp instead of strcmp to defend against buffer overflow
  } else if (strncmp(input, "signup", 6) == 0) {
    admin_loop();

    while(1){
      char* s = "Student or teacher: ";
      char* input = prompt_until_valid(TEACHER_STUDENT, s);

      int usertype;
      char* name;

      if (strncmp(input, "student", 7) == 0) {
        //student_loop();
        usertype = 1;
      } else if (strncmp(input, "teacher", 7) == 0) {
        //teacher_loop();
        usertype = 2;
      } else {
        // format string vulnerability defense
        char* invalidInput = "Invalid input\n";
        printf("%s", invalidInput);
      }

      char* nameprompt = "Name: ";
      char* nameinput = prompt_until_valid(NAME, nameprompt);

      char* passprompt = "Password: ";
      char* passinput = prompt_until_valid(PASS, passprompt);

      FILE *fp, *fd;
      char id_buff[7] = {0};
      int id = 100001;

      if ((fd = fopen("data/private/login_last_id.txt", "r")) != NULL) {
        fgets(id_buff, 7, fd);
        id = atoi(id_buff) + 1;
      } else {
        fp = fopen("data/private/login_all_id.txt", "w");
        fclose(fp);
      }

      fd = fopen("data/private/login_last_id.txt", "w");
      fprintf(fd, "%d", id);

      fp = fopen("data/private/login_all_id.txt", "a");
      fprintf(fp, "%d,%s,%s,%d,\n", id, nameinput, passinput, usertype);

      printf("%d\n", id);

      fclose(fp);
      fclose(fd);

      //encrypt all_id -> login.bin
      //overwrite all_id
    }

  } else {
    // format string vulnerability defense
    char* invalidInput = "Invalid input\n";
    printf("%s", invalidInput);
    exit(1);
  }

  return 0;
}


