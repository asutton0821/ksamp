/*


Header File for project2.c 


*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>



#define MAX_SPLIT_LENGTH 64
#define LINE_LENGTH 1000
#define WHITESPACE      " \t"
#define CPU_INFO_LOC "/proc/cpuinfo"



FILE * fp;





void grabCPUInfo(const char *);
void parseSpace(char * , char *[]);
void grabKernelVersion(void);
float getTimeSinceLastReboot(void);
void getTimeInCPUModes(void);
void getReadWrites(void);
void printCharStarArray(char *[], int );
void parseDynSpace(char * , char ** , int );
void getContextSwitches(void);
void getTimeOfLastReboot(float );
void grabLoadAvg(void);
void getMem(void);
void getProcs(void);
void runPart1(void);
void runPart2(void);
void runPart3(int, int);
int main(int, char **); 
