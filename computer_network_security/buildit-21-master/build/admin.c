//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////admin.c/////////////////////////////////////////
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void admin_loop()
{
  char *input = NULL;

  // setting up data/administration.txt
  char *fname = "data/administration.txt";
  int attempt_count = 0;

  while (1)
  {
    // protect against brute force attempts
    if (attempt_count == 3)
    {
      //Not Authorized!
      char *cred_change = "Max Admin Login attempts reached\n Please view Admin.txt for new credentials";
      printf("%s\n", cred_change);
      // Changing credentials
      FILE *fd = fopen(ADMIN_FILE, "w");
      if (fd == NULL)
      {
        return;
      }

      srand(time(NULL));
      int i = 0;
      char cred[33] = {0};
      while (i < 32)
      {
        cred[i] = (rand() % 10) + '0';
        i++;
      }

      fprintf(fd, "%s", cred);
      fclose(fd);
      exit(0);
    }

    free(input);
    char credpath[30] = "Credentials: ";
    char *input = prompt_until_valid(ADMIN, credpath);

    FILE *fp = fopen(fname, "r");
    char cred[34] = {0};
    fgets(cred, 33, fp);

    //printf("cred%s\n",cred);
    //printf("input%s\n",input);

    // validating credentials
    if (strncmp(input, cred, 32) == 0)
    {
      // Correct
      fclose(fp);
      return;
    }
    else
    {
      // Incorrect
      char *not_auth = "Not authorized";
      printf("%s\n", not_auth);
      attempt_count++;
    }

    fclose(fp);
  }
}
