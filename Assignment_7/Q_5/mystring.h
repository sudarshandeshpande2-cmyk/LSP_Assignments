#ifndef MYSTRING_H
#define MYSTRING_H

int MyStrlen(const char *);
void MyStrcpy(char *, const char *);
void MyStrncpy(char *, const char *, int);
void MyStrcat(char *, const char *);
int MyStrcmp(const char *, const char *);
int MyStrncmp(const char *, const char *,int);
void MyStrrev(char *);
char *MyStrchr(const char *, char);

#endif