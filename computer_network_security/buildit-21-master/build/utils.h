#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <regex.h>
#include <stdbool.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#ifndef __GRADEBOOK_UTILS_H
#define __GRADEBOOK_UTILS_H

#define BOOL int
#define TRUE 1
#define FALSE 0
#define ADMIN_FILE "data/administration.txt"

#define VT_MODE 1
#define VT_ID 2
#define VT_PASSWORD 3

#define TEACHER_STUDENT 414
#define NAME 426
#define PASS 2019
#define TEACHER 131
#define STUDENT 132
#define ADMIN 21

char* prompt(const char* format);
char* prompt_until_valid(int type, const char* format);
BOOL is_valid(int type, const char* input);
bool name_is_valid(const char* name);
bool pass_is_valid(const char* name);
bool create_is_valid(const char* input);
bool open_is_valid(const char* input);
bool code_is_valid(const char* input);
bool id_is_valid(const char* input);
bool close_is_valid(const char* input);
bool add_is_valid(const char* input);
bool grade_is_valid(const char *input);
bool check_is_valid(const char *input);
bool classes_is_valid(const char *input);
bool students_is_valid(const char *input);
bool student_is_valid(const char* input);

bool cred_is_valid(const char* input);
void enc(char *path, char *out);
void dec(char *path, char *out);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
void handleErrors(void);

#endif