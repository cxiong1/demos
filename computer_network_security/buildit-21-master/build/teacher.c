///////////////////////////////////////////////////////////////////////////////////////////////////////////teacher.c/////////////////////////////////////////////////////////
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TEACHER 131

int get_max_id();
void move_back();
void printname(char* theid);
bool is_teacher(char* givenId);

void teacher_loop(char *name, char *id)
{
    bool opened = false;
    char t_code[8] = {0};

    while (1)
    {
        char t_path[120] = {0};
        strncat(t_path, name, strlen(name));
        strncat(t_path, " (teacher)", 12);
        //check if opened
        //append tcode to the thing aswell.
        if (opened)
        {
            strncat(t_path, " [", 2);
            strncat(t_path, t_code, strlen(t_code));
            strncat(t_path, "]", 1);
        }

        strncat(t_path, ": ", 2);
        //printf("%s", t_path);

        char *input = prompt_until_valid(TEACHER, t_path);
        char buf[130] = {0};
        strncpy(buf, input, strlen(input));
        char *cmd = strtok(buf, " ");
        //Create------------------------------------------------------------------------------------------------Create
        //Create------------------------------------------------------------------------------------------------Create
        
        //if (access("data/classes.bin", F_OK) == 0 && access("data/login.bin", F_OK) == 0) {
          //  dec("data/classes.bin","data/private/courses.txt");
            //dec("data/login.bin","data/private/login_all_id.txt");
        //}
                
        if (strncmp(cmd, "create", 6) == 0 || strlen(cmd) == 6)
        {
            char *usage = "Usage: create <code> <name>";
            char *invalid = "Invalid input";

            char *code = strtok(NULL, " ");

            if (code == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            char *classname = strtok(NULL, " ");

            if (classname == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            if (!code_is_valid(code))
            {
                printf("%s\n", invalid);
                continue;
            }

            if (!name_is_valid(classname))
            {
                printf("%s\n", invalid);
                continue;
            }

            char realclass[101] = {0};
            
            strcat(realclass,classname);
            while(classname = strtok(NULL," ")){
                strcat(realclass," ");
                strcat(realclass,classname);
            }

            //printf("%s",classname);

            FILE *courses;

            bool realflag = false;
            char bigbuff[150] = {0};
            char tempcode[8] = {0};
            if ((courses = fopen("data/private/courses.txt", "r")) != NULL)
            {
                while (fgets(bigbuff, 140, courses) != NULL)
                {
                    strncpy(tempcode, bigbuff, 7);
                    if (strncmp(tempcode, code, 7) == 0)
                    {
                        realflag = true;
                        break;
                    }
                }
            }

            if (realflag)
            {
                char *inuse = "Code is already in use\n";
                printf("%s", inuse);
                continue;
            }

            char *zero = "%s 0\n";
            char *form = "%s %s %s,\n";

            if ((courses = fopen("data/private/courses.txt", "a")) == NULL)
            {
                courses = fopen("data/private/courses.txt", "w");
            }

            fprintf(courses, zero, code);
            fprintf(courses, form, code, id, realclass);

            fclose(courses);
            printf("Success\n");

            if (opened)
            {
                opened = false;
                for (int i = 0; i < 8; i++)
                {
                    t_code[i] = '\0';
                }
            }
        }
        //Open---------------------------------------------------------------------------------------------------Open
        //Open---------------------------------------------------------------------------------------------------Open
        else if (strncmp(cmd, "open", 4) == 0)
        {
            char *usage = "Usage: open <code>";
            char *invalid = "Invalid input";

            char *code = strtok(NULL, " ");
            if (code == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            //checking if code exists in file
            //if it does, then check the teacher id.
            //after that's done, then we can open it
            //e.g. setting t_code to the code and setting opened to true;
            //otherwise
            FILE *courses;

            bool realflag = false;
            char smolbuff[20] = {0};
            char bigbuff[5000] = {0};
            char tempcode[8] = {0};

            if ((courses = fopen("data/private/courses.txt", "r")) != NULL)
            {
                while (fgets(smolbuff, 20, courses) != NULL)
                {
                    fgets(bigbuff, 4950, courses);
                    strncpy(tempcode, bigbuff, 7);
                    //printf("code, %s\n",code);
                    //printf("tempcode, %s\n",tempcode);
                    if (strncmp(tempcode, code, 7) == 0)
                    {
                        realflag = true;
                        break;
                    }
                }
                //If it gets to this point, that means that the code wasn't found
                //inside the file so we print wrong code and break

                if (realflag == false)
                {
                    printf("Wrong code\n");
                    continue;
                }
            }

            char fileId[8] = {0};
            if (realflag)
            {
                //This means that the code was found inside the database;
                //Check the teacher id.
                strncpy(fileId, bigbuff + 8, 6);
                if (strncmp(fileId, id, 6) == 0)
                {
                    //This means that the current id and fileId matches
                    //printf("matched\n");
                    opened = true;
                    strncpy(t_code, code, 7);
                }
                else{
                    printf("Not authorized\n");
                }
            }
        }

        //Close-------------------------------------------------------------------------------------------------Close
        //Close-------------------------------------------------------------------------------------------------Close
        else if (strncmp(cmd, "close", 5) == 0)
        {
            if (opened)
            {
                opened = false;
            }
            else
            {
                printf("No opened class\n");
            }
        }
        //Add-------------------------------------------------------------------------------------------------Add
        //Add-------------------------------------------------------------------------------------------------Add
        else if (strncmp(cmd, "add", 3) == 0)
        {
            char *usage = "Usage: add <id>";
            char *stu_id = strtok(NULL, " ");

            if (stu_id == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            if (opened == false)
            {
                printf("No opened class\n");
                continue;
            }

            //This part is broken, if I have time, I will come back to fix it
            //Basically the teacher could try and add another teacher
            //which is not a student, so this should also break and print wrong id.
            int max = get_max_id();
            int idNum = atoi(stu_id);
            //printf("idNum %d max %d\n",idNum, max);
            if (idNum > max)
            {
                printf("Wrong id\n");
                continue;
            }

            FILE *fp;
            FILE *f2;
            fp = fopen("data/private/courses.txt", "r+");
            f2 = fopen("data/private/second.txt", "w");
            char smolbuff[20] = {0};

            while (fgets(smolbuff, 14, fp))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);

                char tempcode[8] = {0};
                strncpy(tempcode, smolbuff, 7);

                if (strncmp(tempcode, t_code, 7) == 0)
                {
                    //printf("We matched %s\n",tempcode);

                    //Need to check if stu_id is teacher
                    if(is_teacher(stu_id)){
                        printf("Wrong id\n");
                        fprintf(f2, "%s", smolbuff);
                        fprintf(f2, "%s", bigbuff);
                        continue;
                    }

                    if (strstr(bigbuff, stu_id) != NULL)
                    {
                        printf("Already in class\n");
                        fprintf(f2, "%s", smolbuff);
                        fprintf(f2, "%s", bigbuff);
                        continue;
                    }

                    int numStudents = atoi(smolbuff + 8);
                    numStudents++;
                    sprintf(smolbuff + 8, "%d", numStudents);

                    size_t ln = strlen(bigbuff) - 1;
                    if (*bigbuff && bigbuff[ln] == '\n')
                    {
                        bigbuff[ln] = '\0';
                    }

                    char newEntry[12] = "0 ";
                    strcat(newEntry, stu_id);
                    strcat(bigbuff, newEntry);
                    //printf("%s\n",bigbuff);

                    //fprintf(fp,"%s\n",smolbuff);
                    //fprintf(fp,"%s\n",bigbuff);

                    fprintf(f2, "%s\n", smolbuff);
                    fprintf(f2, "%s,\n", bigbuff);
                    //fgets(smolbuff,20,fp);
                    //fprintf(f2,"%s",smolbuff);
                    printf("Success\n");
                    continue;
                }

                fprintf(f2, "%s", smolbuff);
                fprintf(f2, "%s", bigbuff);
            }
            fclose(fp);
            fclose(f2);

            //This part is used to write f2 back to the original file
            fp = fopen("data/private/courses.txt", "w");
            f2 = fopen("data/private/second.txt", "r");

            while (fgets(smolbuff, 14, f2))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);

                fprintf(fp, "%s", smolbuff);
                fprintf(fp, "%s", bigbuff);
            }
            fclose(fp);
            fclose(f2);

        }
        //Grade-------------------------------------------------------------------------------------------------Grade
        //Grade-------------------------------------------------------------------------------------------------Grade
        else if (strncmp(cmd, "grade", 5) == 0)
        {
            char *usage = "Usage: grade <id> <grade>";
            char *stu_id = strtok(NULL, " ");

            if (stu_id == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            char *grade = strtok(NULL, " ");

            if (grade == NULL)
            {
                printf("%s\n", usage);
                continue;
            }

            if (opened == false)
            {
                printf("No opened class\n");
                continue;
            }

            int maxId = get_max_id();
            int suppliedId = atoi(stu_id);
            if (suppliedId > maxId)
            {
                printf("Wrong id\n");
                continue;
            }

            FILE *fp;
            FILE *f2;
            fp = fopen("data/private/courses.txt", "r+");
            f2 = fopen("data/private/second.txt", "w");
            char smolbuff[20] = {0};

            while (fgets(smolbuff, 14, fp))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);

                char tempcode[8] = {0};
                strncpy(tempcode, smolbuff, 7);

                if (strncmp(tempcode, t_code, 7) == 0)
                {

                    char *thestudent;
                    if ((thestudent = strstr(bigbuff, stu_id)) == NULL)
                    {
                        printf("Not in class\n");
                        break;
                    }

                    //printf("index %d\n",(int) (thestudent - bigbuff));
                    char two = *(thestudent - 2);
                    char three = *(thestudent - 3);
                    char four = *(thestudent - 4);
                    char five = *(thestudent - 5);
                    //printf("%c%c%c%c\n",five,four,three,two);
                    int away = 0;
                    if (five == ',')
                    {
                        away = 4;
                    }
                    if (four == ',')
                    {
                        away = 3;
                    }
                    if (three == ',')
                    {
                        away = 2;
                    }

                    //printf("away %d\n", away);

                    //printf("length %d\n", strlen(thestudent));

                    char *newEntry = calloc(strlen(thestudent) + 10, 1);
                    strncpy(newEntry, grade, strlen(grade));
                    //printf("%s\n", newEntry);
                    strncat(newEntry, " ", 1);
                    //printf("%s\n", newEntry);
                    strncat(newEntry, thestudent, strlen(thestudent));
                    //printf("%s\n", newEntry);

                    strncpy(thestudent - away, newEntry, strlen(newEntry));
                    *(thestudent + strlen(newEntry) - away) = '\0';
                    //*(thestudent + strlen(newEntry)) = '\0';
                    //printf("%s", bigbuff);

                    fprintf(f2, "%s", smolbuff);
                    fprintf(f2, "%s", bigbuff);
                    continue;
                }

                fprintf(f2, "%s", smolbuff);
                fprintf(f2, "%s", bigbuff);
            }
            fclose(fp);
            fclose(f2);

            //This part is used to write f2 back to the original file
            move_back();

            printf("Success\n");
        }
        //Check-------------------------------------------------------------------------------------------------Check
        //Check-------------------------------------------------------------------------------------------------Check
        else if (strncmp(cmd, "check", 5) == 0)
        {
            if (opened == false)
            {
                printf("No opened class\n");
                continue;
            }

            char *stu_id = strtok(NULL, " ");
            if (stu_id != NULL)
            {
                int maxId = get_max_id();
                int suppliedId = atoi(stu_id);
                if (suppliedId > maxId)
                {
                    printf("Wrong id\n");
                    continue;
                }
            }

            FILE *fp;
            fp = fopen("data/private/courses.txt", "r");
            char smolbuff[20] = {0};

            while (fgets(smolbuff, 14, fp))
            {
                int size = atoi(smolbuff + 8);
                char *bigbuff = calloc(124 + (12 * size), 1);
                fgets(bigbuff, 120 + (12 * (size + 1)), fp);

                char tempcode[8] = {0};
                strncpy(tempcode, smolbuff, 7);

                if (strncmp(tempcode, t_code, 7) == 0)
                {
                    //This is the current correct class opened and its stored in bigbuff
                    //Here we handle if we print only one or if we iterate through the entire.
                    char idString[7] = {0};
                    if (stu_id != NULL)
                    {
                        char *thestudent = strstr(bigbuff, stu_id);
                        if (thestudent == NULL)
                        {
                            printf("Not in class\n");
                            break;
                        }

                        strncpy(idString, thestudent, 6);
                        printname(stu_id);
                        printf("(%s): ", stu_id);
                        char two = *(thestudent - 2);
                        char three = *(thestudent - 3);
                        char four = *(thestudent - 4);
                        char five = *(thestudent - 5);

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
                    }
                    else
                    {
                        char s[2] = ",";
                        char *tok = strtok(bigbuff, s);

                        while (tok = strtok(NULL, s))
                        {

                            char temp[12] = {0};
                            strncpy(temp, tok, 11);
                            //printf("%s\n", temp);

                            char grd[4] = {0};
                            char iden[7] = {0};

                            //printname(temp);
                            if (temp[1] == ' ')
                            {
                                printname(temp+2);
                                printf("(%s): %c\n", temp + 2, temp[0]);
                            }
                            else if (temp[2] == ' ')
                            {
                                printname(temp+3);
                                printf("(%s): %c%c\n", temp + 3, temp[0], temp[1]);
                            }
                            else if (temp[3] == ' ')
                            {
                                printname(temp+4);
                                printf("(%s): %c%c%c\n", temp + 4, temp[0], temp[1], temp[2]);
                            }
                        }
                        break;
                    }

                    continue;
                }
            }
        }
        //classes-----------------------------------------------------------------------------------------------classes
        //classes-----------------------------------------------------------------------------------------------classes
        else if (strncmp(cmd, "classes", 7) == 0)
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
        //students--------------------------------------------------------------------------------------------students
        //students--------------------------------------------------------------------------------------------students
        else if (strncmp(cmd, "students", 8) == 0)
        {
            FILE *fp;
            if (fp = fopen("data/private/login_all_id.txt", "r"))
            {
                char smolbuff[160] = {0};
                char *tok;
                char s[2] = ",";

                char id[8] = {0};
                char stuname[101] = {0};
                char type[2] = {0};

                while (fgets(smolbuff, 150, fp))
                {
                    tok = strtok(smolbuff, s);
                    strncpy(id,tok,6);
                    tok = strtok(NULL, s);
                    strncpy(stuname,tok,strlen(tok));
                    //printf("%s",tok);
                    tok = strtok(NULL, s);
                    tok = strtok(NULL, s);
                    strncpy(type,tok,1);

                    if(strcmp(type,"1") == 0){
                        printf("%s: %s\n",id,stuname);
                    }
                }
            }
        }
        else
        {
            char *msg = "Unrecognized command";
            printf("%s\n", msg);
        }


        //if (access("data/private/courses.txt", F_OK) == 0 && access("data/private/login_all_id.txt", F_OK) == 0) {
           // printf("encrypted\n");
          //  enc("data/private/courses.txt","data/classes.bin");
            //enc("data/private/login_all_id.txt","data/login.bin");
        //}

    }
}

int get_max_id()
{
    char buff[8] = {0};
    FILE *fp;
    if ((fp = fopen("data/private/login_last_id.txt", "r")) != NULL)
    {
        fgets(buff, 7, fp);
        return atoi(buff);
    }
    return 0;
}

void move_back()
{
    //This part is used to write f2 back to the original file
    FILE *fp;
    FILE *f2;
    fp = fopen("data/private/courses.txt", "w");
    f2 = fopen("data/private/second.txt", "r");
    char smolbuff[20];

    while (fgets(smolbuff, 14, f2))
    {
        int size = atoi(smolbuff + 8);
        char *bigbuff = calloc(124 + (12 * size), 1);
        fgets(bigbuff, 120 + (12 * (size + 1)), fp);

        fprintf(fp, "%s", smolbuff);
        fprintf(fp, "%s", bigbuff);
    }
    fclose(fp);
    fclose(f2);
}

void printname(char* theid){
    FILE *fp;
    fp = fopen("data/private/login_all_id.txt", "r");
    char smolbuff[160];

    //printf("theid %s\n",theid);
    while (fgets(smolbuff, 150, fp))
    {
        //printf("%s",smolbuff);
        //printf("%s\n",theid);
        if(strncmp(smolbuff,theid,6) == 0){
            char* startname = smolbuff+7;
            while(*startname != ','){
                printf("%c",*startname);
                startname++;
            }
            return;
        }
    }
    fclose(fp);
}

bool is_teacher(char* givenId){
    FILE *fp;
    fp = fopen("data/private/login_all_id.txt", "r");
    char smolbuff[160];

    while (fgets(smolbuff, 150, fp))
    {
        //printf("%d\n",strlen(smolbuff));
        if(strncmp(smolbuff,givenId,6)==0){
            int typeindex = strlen(smolbuff) - 3;
            //printf("%c\n",*(smolbuff+typeindex));
            if(*(smolbuff+typeindex) == '2'){
                return true;
            }
        }
    }
    fclose(fp);

    return false;

}