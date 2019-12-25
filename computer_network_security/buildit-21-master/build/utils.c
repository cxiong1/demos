//////////////////////////////////////////////////////////////////////////////////////////////////////////utils.c////////////////////////////////////////////////////////////
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#define TEACHER_STUDENT 414
#define NAME 426
#define PASS 2019
#define TEACHER 131

// NOTE: You MUST read through the code if you decide to use it
//       The provided code is NOT bug-free

// Prompt user input, va_list version
char *vprompt(const char *format)
{
    char *buf = calloc(106, sizeof(char));
    int length;
    int start;
    int end;

    printf("%s", format);

    if (fgets(buf, 105, stdin) == NULL)
    {
        // Exit when EOF or error
        exit(0);
    }

    // trim spaces
    length = strlen(buf);
    for (start = 0; start < length; start += 1)
    {
        if (buf[start] > 0x20 && buf[start] < 0x7f)
        {
            break;
        }
    }
    for (end = length; end > start; end -= 1)
    {
        if (buf[end - 1] > 0x20 && buf[end - 1] < 0x7f)
        {
            break;
        }
    }
    length = end - start;
    for (int i = 0; i < length; i += 1)
    {
        buf[i] = buf[start + i];
    }
    buf[length] = 0;

    return buf;
}

char *prompt(const char *format)
{
    char *buf;
    buf = vprompt(format);
    return buf;
}

// Prompt until valid
char *prompt_until_valid(int type, const char *format)
{
    char *input = NULL;
    do
    {
        free(input);
        input = vprompt(format);
    } while (!is_valid(type, input));

    return input;
}

// Check whether an input is valid
BOOL is_valid(int type, const char *input)
{
    BOOL valid = FALSE;
    switch (type)
    {
    case ADMIN:
        valid = cred_is_valid(input);
        break;
    case VT_MODE: // login or signup
        valid = strncmp(input, "login", 5) == 0 || strncmp(input, "signup", 6) == 0;
        break;
    case TEACHER_STUDENT: // teacher or student
        valid = strncmp(input, "teacher", 7) == 0 || strncmp(input, "student", 7) == 0;
        break;
    case NAME:
        valid = name_is_valid(input);
        break;
    case PASS:
        valid = pass_is_valid(input);
        break;
    case VT_ID:
        valid = id_is_valid(input);
        break;
    case VT_PASSWORD:
        valid = pass_is_valid(input);
        break;
    case TEACHER:
        //printf("case teacher\n");
        //printf("input %s\n",input);
        if (create_is_valid(input) || open_is_valid(input) || close_is_valid(input) ||
            add_is_valid(input) || grade_is_valid(input) || check_is_valid(input) || classes_is_valid(input) ||
            students_is_valid(input))
        {
            valid = true;
        }
        else
        {
            printf("Unrecognized command\n");
            return false;
        }
        break;
    case STUDENT:
        if (student_is_valid(input) || strncmp(input, "classes", 7) == 0 || strncmp(input, "enrolled", 8) == 0 ||
            strncmp(input, "check", 5) == 0)
        {
            valid = true;
        }
        else
        {
            printf("Unrecognized command\n");
            return false;
        }
        break;
    }

    if (!valid)
    {
        printf("Invalid input\n");
    }

    return valid;
}

bool name_is_valid(const char* name) {
  if (strlen(name) > 100) {
    return false;
  }

  int match = 0;

  for (int i = 0; i < strlen(name); i++) {
    if ((name[i] == 0x20) || (name[i] >= 0x41 && name[i] <= 0x5a) || (name[i] >= 0x61 && name[i] <= 0x7a)) {
      match++;
    }
  }

  if (match == strlen(name)) {
    return true;
  }

  return false;
}

bool pass_is_valid(const char* name) {
  if (strlen(name) < 6 || strlen(name) > 32) {
    return false;
  }

  int match = 0;

  for (int i = 0; i < strlen(name); i++) {
    if ((name[i] == 0x21) || (name[i] == 0x40) || (name[i] == 0x23) ||
        (name[i] >= 0x41 && name[i] <= 0x5a) || (name[i] >= 0x61 && name[i] <= 0x7a) ||
        (name[i] >= 0x30 && name[i] <= 0x39)) {
      match++;
    }
  }

  if (match == strlen(name)) {
    return true;
  }

  return false;
}

bool create_is_valid(const char* input) {
  if (strlen(input) < 6 || strlen(input) > 116) {
    return false;
  }

  int match = 0;

  if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' && input[3] == 'a' && input[4] == 't' && input[5] == 'e'
      && input[6] == 0x20) {
    match += 7;
  }

  for (int i = match; i < strlen(input); i++) {
    if ((input[i] == 0x20) || (input[i] >= 0x41 && input[i] <= 0x5a) || (input[i] >= 0x61 && input[i] <= 0x7a)
        || (input[i] >= 0x30 && input[i] <= 0x39)) {
      match++;
    }
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}

bool open_is_valid(const char* input) {

  int match = 0;
	
  if (input[0] == 'o' && input[1] == 'p' && input[2] == 'e' && input[3] == 'n') {
    match += 4;
  }
  else{
    return false;
  }

  for (int i = match; i < strlen(input); i++) {
    if ((input[i] == 0x20) || (input[i] >= 0x41 && input[i] <= 0x5a) || (input[i] >= 0x61 && input[i] <= 0x7a)) {
      match++;
    }
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}

bool code_is_valid(const char* input) {
  if (strlen(input) != 7) {
    return false;
  }

  int match = 0;
  
  if (input[0] == 'C' && input[1] == 'M' && input[2] == 'S' && input[3] == 'C') {
    match += 4;
  }

  if ((input[4] >= 0x30 && input[4] <= 0x39) && (input[5] >= 0x30 && input[5] <= 0x39) && (input[6] >= 0x30 && input[6] <= 0x39)) {
    match += 3;
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}

bool id_is_valid(const char* input) {
  if (strlen(input) != 6) {
    return false;
  }

  int match = 0;

  for (int i = 0; i < 6; i++) {
    if ((input[i] >= 0 && input[i] <= 9) || (input[i] >= 0x30 && input[i] <= 0x39)) {
      match++;;
    }
  }

  if (match == 6) {
    return true;
  }

  return false;
}

bool close_is_valid(const char* input) {
  if (strlen(input) != 5) {
    return false;
  }
  int match = 0;
  if (input[0] == 'c' && input[1] == 'l' && input[2] == 'o' && input[3] == 's' && input[4] == 'e') {
    match += 5;
  }
  if (match == strlen(input)) {
    return true;
  }
  return false;
}

bool add_is_valid(const char* input) {
  if (strlen(input) < 3) {
    return false;
  }

  int match = 0;

  if (input[0] == 'a' && input[1] == 'd' && input[2] == 'd') {
    match += 3;
  }

  for (int i = match; i < strlen(input); i++) {
    if ((input[i] == 0x20) || (input[i] >= 0x30 && input[i] <= 0x39)) {
      match++;
    }
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}
bool grade_is_valid(const char* input) {

  int match = 0;

  if (input[0] == 'g' && input[1] == 'r' && input[2] == 'a' && input[3] == 'd' && input[4] == 'e') {
    match += 5;
  }

  if ((match == 5 && input[5] == ' ') || (match == 5 && strlen(input) == 5)) {
    for (int i = match; i < strlen(input); i++) {
      if ((input[i] == 0x20) || (input[i] >= 0x30 && input[i] <= 0x39)) {
        match++;
      }
    }

    if (match == strlen(input)) {
      return true;
    }
  }

  return false;
}
bool check_is_valid(const char* input) {

  int match = 0;

  if (input[0] == 'c' && input[1] == 'h' && input[2] == 'e' && input[3] == 'c' && input[4] == 'k') {
    match += 5;
  }

  for (int i = match; i < strlen(input); i++) {
    if ((input[i] == 0x20) || (input[i] >= 0x30 && input[i] <= 0x39)) {
      match++;
    }
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}

bool classes_is_valid(const char* input) {
  if (strlen(input) != 7) {
    return false;
  }

  if (strncmp(input, "classes", 7)) {
    return true;
  }

  return false;
}


bool students_is_valid(const char* input) {
  if (strlen(input) != 8) {
    return false;
  }

  if (strncmp(input, "students", 8)) {
    return true;
  }

  return false;
}

bool student_is_valid(const char* input) {
  if (strlen(input) != 13) {
    return false;
  }
  
  int match = 0;
	
  if (input[0] == 'c' && input[1] == 'h' && input[2] == 'e' && input[3] == 'c' && input[4] == 'k'
      && input[5] == ' ') {
    match += 5;
  }

  for (int i = match; i < strlen(input); i++) {
    if ((input[i] == 0x20) || (input[i] >= 0x41 && input[i] <= 0x5a) || (input[i] >= 0x61 && input[i] <= 0x7a) ||
        (input[i] >= 0x30 && input[i] <= 0x39)) {
      match++;
    }
  }

  if (match == strlen(input)) {
    return true;
  }

  return false;
}

bool cred_is_valid(const char* input){
  if(strlen(input) != 32){
    return false;
  }

  return true;
}

void enc(char *path, char *out) {
  char keyStr[100] = {0}, ivStr[100] = {0};
  char buffer[5000] = {0}, line[1000] = {0};

  FILE *fp = fopen("data/private/keys.txt", "r");
  FILE *fd = fopen(path, "r");
  FILE *fw = fopen(out, "w");

  fgets(keyStr, 100, fp);
  fgets(ivStr, 100, fp);

  while (fgets(line, 1000, fd) != NULL) {
    strncat(buffer, line, strlen(line));
    strncat(buffer, "\n", sizeof(char));
    for (int i = 0; i < 1000; i++) {
      line[i] = '\0';
    }
  }

  unsigned char *plaintext = (unsigned char *)buffer;

  unsigned char ciphertext[5000] = {0};

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[5000] = {0};

  int decryptedtext_len, ciphertext_len;

  /* Encrypt the plaintext */
  ciphertext_len = encrypt(buffer, strlen(buffer), keyStr, ivStr, ciphertext);

  FILE *fl = fopen("data/private/cipherLen.txt", "w");
  char *format1 = "%s", *format2 = "%d";

  /* Do something useful with the ciphertext here */
  fprintf(fw, format1, ciphertext);
  fprintf(fl, format2, ciphertext_len);

  fclose(fl);
  fclose(fp);
  fclose(fd);
  fclose(fw);
}

void dec(char *path, char *out) {
  char keyStr[100] = {0}, ivStr[100] = {0}, keyLengthStr[100] = {0}, ivLengthStr[100] = {0};
  char ciphertext[5000] = {0}, line[1000] = {0};

  FILE *fp = fopen("data/private/keys.txt", "r"), *fd = fopen(path, "r"), *fw = fopen(out, "w");
  FILE *fl = fopen("data/private/cipherLen.txt", "r");

  fgets(keyStr, 100, fp);
  fgets(ivStr, 100, fp);

  int keyLength = strlen(keyStr), ivLength = strlen(ivStr), key, iv;
  key = atoi(keyStr);
  iv = atoi(ivStr);
  fclose(fp);

  while (fgets(line, 1000, fd) != NULL) {
    strncat(ciphertext, line, strlen(line));
    for (int i = 0; i < 1000; i++) {
      line[i] = '\0';
    }
  }

  unsigned char decryptedtext[5000];
  char num[1000] = {0};
  fgets(num, 1000, fl);
  int decryptedtext_len, ciphertext_len = atoi(num);

  /* Decrypt the ciphertext */
  decryptedtext_len = decrypt(ciphertext, ciphertext_len, keyStr, ivStr, decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  char *format1 = "%s";
  fprintf(fw, format1, decryptedtext);

  fclose(fd);
  fclose(fw);
  fclose(fl);
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  if (!(ctx = EVP_CIPHER_CTX_new())) {
    handleErrors();
  }

  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    handleErrors();
  }

  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
    handleErrors();
  }
  
  ciphertext_len = len;

  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
    handleErrors();
  }
  
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  if (!(ctx = EVP_CIPHER_CTX_new())) {
    handleErrors();
  }

  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    handleErrors();
  }

  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
    handleErrors();
  }
  
  plaintext_len = len;

  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
    handleErrors();
  }
  
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}