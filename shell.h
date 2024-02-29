#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USEgetLine 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **Environ;


typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list__t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list__t *env;
	list__t *history;
	list__t *alias;
	char **Environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int readfd;
	int histcount;
} info__t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


typedef struct builtin
{
	char *type;
	int (*func)(info__t *);
} builtin_table;



int hsh(info__t *, char **);
int find_builtin(info__t *);
void find_cmd(info__t *);
void fork_cmd(info__t *);


int is__cmd(info__t *, char *);
char *dup__chars(char *, int, int);
char *find__path(info__t *, char *, char *);


int loop_hsh(char **);


void _e__puts(char *);
int _eput_char(char);
int _putfD(char c, int fd);
int ___putSfd(char *str, int fd);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strcpy(char *, char *);
char *_strdup(const char *);
void __puts(char *);
int put_char(char);


char *_strncpy(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);


char **strtow(char *, char *);
char **str_tow2(char *, char);


char *_mem_set(char *, char, unsigned int);
void fFree(char **);
void *_reallocs(void *, unsigned int, unsigned int);


int bFree(void **);


int interact(info__t *);
int isDelim(char, char *);
int isalpha(int);
int atoi(char *);


int erroAtoi(char *);
void printError(info__t *, char *);
int printD(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);


int myexit(info__t *);
int mycd(info__t *);
int myhelp(info__t *);


int _myHistory(info__t *);
int myAlias(info__t *);


ssize_t getInput(info__t *);
int getLine(info__t *, char **, size_t *);
void sigint_handler(int);


void clearInfo(info__t *);
void setInfo(info__t *, char **);
void freeInfo(info__t *, int);


char *getENV(info__t *, const char *);
int myENV(info__t *);
int mySetENV(info__t *);
int myUnSetENV(info__t *);
int populateENVList(info__t *);


char **getEnviron(info__t *);
int unSetENV(info__t *, char *);
int setENV(info__t *, char *, char *);


char *getHistoryFile(info__t *info);
int writeHistory(info__t *info);
int readHistory(info__t *info);
int buildListoryList(info__t *info, char *buf, int linecount);
int reNumberHistory(info__t *info);


list__t *addNode(list__t **, const char *, int);
list__t *addNodeEnd(list__t **, const char *, int);
size_t printListStr(const list__t *);
int deleteNodeAtIndex(list__t **, unsigned int);
void freeList(list__t **);


size_t listLen(const list__t *);
char **listToStrings(list__t *);
size_t printList(const list__t *);
list__t *nodeStartsWith(list__t *, char *, char);
ssize_t getNodeIndex(list__t *, list__t *);


int isChain(info__t *, char *, size_t *);
void checkChain(info__t *, char *, size_t *, size_t, size_t);
int replaceAlias(info__t *);
int replaceVars(info__t *);
int replaceString(char **, char *);

#endif
