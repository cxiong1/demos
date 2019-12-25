#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void student_loop(char *name, char *id)
{
    char c_code[8] = {0};

    while (1)
    {
        char c_path[120] = {0};
        strncat(c_path, name, strlen(name));
        strncat(c_path, " (student)", 12);

        strncat(c_path, ": ", 2);
        //printf("%s", c_path);

        char *input = prompt_until_valid(STUDENT, c_path);
        char buf[130] = {0};
        strncpy(buf, input, strlen(input));
        char *cmd = strtok(buf, " ");

       // if (access("data/classes.bin", F_OK) == 0 && access("data/login.bin", F_OK) == 0) {
         //   dec("data/classes.bin","data/private/courses.txt");
           // dec("data/login.bin","data/private/login_all_id.txt");
        //}

        if (strncmp(cmd, "check", 5) == 0)
        {
            char *usage = "Usage: check <code>";
            char *wrong = "Wrong Code";

            char *code = strtok(NULL, " ");

            if (code == NULL)
            {
                printf("%s\n", usage);
                continue;
            }
            else
            {
                FILE *courses;
                char smolbuff[150] = {0};
                char tempcode[8] = {0};
              	bool exists = false; 

                if ((courses = fopen("data/private/courses.txt", "r")) != NULL)
                {

                    while (fgets(smolbuff, 140, courses) != NULL)
                    {
                        
                        int size = atoi(smolbuff + 8);
                        char *bigbuff = calloc(124 + (12 * size), 1);
                        fgets(bigbuff, 120 + (12 * (size + 1)), courses);

                        strncpy(tempcode, smolbuff, 7);
                        if (strncmp(tempcode, code, 7) == 0)
                        {   
                            //We matched the class
                            exists = true;

                            char* thestudent;
                            //printf("%s",bigbuff);
                            //printf("%s",id);

                            if(thestudent = strstr(bigbuff,id)){
                                //printf("we found your grade\n");

                                char two = *(thestudent - 2);
                                char three = *(thestudent - 3);
                                char four = *(thestudent - 4);
                                char five = *(thestudent - 5);
                                printf("Your grade in ");
                                char *start = bigbuff + 15;
                                while(*start != ','){
                                    printf("%c",*start);
                                    start++;
                                }
                                printf(":");

                                if (five == ',')
                                {
                                    //away = 4;
                                    printf("%c%c%c\n", *(thestudent - 4), *(thestudent - 3), *(thestudent - 2));
                                }
                                if (four == ',')
                                {
                                    //away = 3;
                                    printf("%c%c\n", *(thestudent - 3), *(thestudent - 2));
                                }
                                if (three == ',')
                                {
                                    //away = 2;
                                    printf("%c\n", *(thestudent - 2));
                                }
                                break;
                            }
                            else{char *not_enr = "Not Enrolled";
                                printf("%s\n", not_enr);
                                break;
                            }

                            fclose(courses);
                            break;
                        }
                    }
                    
                        if(!exists) {
                            printf("%s\n", wrong);
                            continue;
                        }
                }
                // Wrong class code
                else
                {
                    printf("%s\n", wrong);
                    continue;
                }
            }
        }
        // print all classes code:name
        else if (strncmp(input, "classes", 7) == 0)
        {

            FILE *fp;
            fp = fopen("data/private/courses.txt", "r");
            char smolbuff[20] = {0};
            char *tok;
            char s[2] = ",";

            while (fgets(smolbuff, 14, fp))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);

                tok = strtok(bigbuff, s);

                char code[8] = {0};
                char class[101] = {0};
                strncpy(code, tok, 7);
                strcpy(class, tok + 15);

                printf("%s: %s\n", code, class);
            }
        }
        // print all classes student is enrolled in
        else if (strncmp(input, "enrolled", 8) == 0)
        {
            FILE *fp;
            fp = fopen("data/private/courses.txt", "r");
            char smolbuff[20] = {0};
            char *tok;
            char s[2] = ",";
            char *line;
            

            while (fgets(smolbuff, 14, fp))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);
                bool actualflag = false;

                if (strstr(bigbuff, id)){
                    actualflag = true;
                }

                tok = strtok(bigbuff, s);

                char code[8] = {0};
                char class[101] = {0};
                strncpy(code, tok, 7);
                strcpy(class, tok + 15);

                //printf("here\n");

                if (actualflag)
                    printf("%s: %s\n", code, class);
            }
        }

        else
        {
            char *msg = "Unrecognized command";
            printf("%s\n", msg);
        }

       // if (access("data/private/courses.txt", F_OK) == 0 && access("data/private/login_all_id.txt", F_OK) == 0) {
        //    enc("data/private/courses.txt","data/classes.bin");
        //    enc("data/private/login_all_id.txt","data/login.bin");
       // }
    }
}