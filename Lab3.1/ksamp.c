/*
Lab 3.1
Project 2

Copyright Colson Sutton 2018
	DO NOT COPY



Lab 3.1 takes a single command, ksamp, that will produce information based on 
the arguments following the command. When typing solely ksamp, the CPU type, Kernel
Version, and time since last reboot will be displayed to the user. 

When typing "ksamp -s" the user will be presented with more information, such
as the output from ksamp (without parameters) along with the time the CPU has spent
in 'user' mode, 'system' mode , and idle along with number of disk read/write request made by 
the system, the number of context switches the kernel has performed, the time 
at which the system last booted, and the number of procs that have been created
since the system was booted. 

The third and final option, ksamp -l [SAMPLE TIME] [AVERAGE OBSERVATION], will 
present the user with all the of the same information from the second command, 
the amount of memory configured, amount of memory available, and a list
of load averages, each averaged over the [AVERAGE OBSERVATION] flag, based on the 
[SAMPLE TIME] flag, which is how often the sample is taken from the kernel. 


To start the program, once can you use ./ksamp and it will present the information
from the first option. Otherwise, using ./ksamp -s will provide the output for the 
second option, and ./ksamp -l 2 60 will provide the output for the third option. 


*/

#include "ksamp.h"


void getTimeInCPUModes(){
	//location = /proc/stats
	/*
		Interpreting the file... 
		look at CPU. There should be 7 columns
		1 - User mode
		2 - niced (see nice processes)
		3 - System mode (kernel mode)
		4 - idle 
		5 - iowait 
		6 - irq - interrupts
		7 - softirq (servicing softirqs)
		
	*/
	
	fp = fopen("/proc/stat","r");
	if(fp == NULL){
		printf("File cannot be opened!");
		return;
	}

    char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
		if(strstr(line, "cpu ")){
			parseSpace(line, splitString);
			break;
		}
	}
	printf("Grabbing CPU Times..."); 
	printf("\nUser Mode: %s\nKernel Mode: %s\nIdle Time: %s\n",splitString[2], splitString[4], splitString[5]);
	fclose(fp);
  
  
 
	
}

void getReadWrites(){
	
	/*
		 /proc/diskstats
		 Based on columns: 
		     1 - major number
         2 - minor mumber
         3 - device name
         4 - reads completed successfully
         5 - reads merged
         6 - sectors read
         7 - time spent reading (ms)
         8 - writes completed
         9 - writes merged
        10 - sectors written
        11 - time spent writing (ms)
        12 - I/Os currently in progress
        13 - time spent doing I/Os (ms)
        14 - weighted time spent doing I/Os (ms)

		Showing: 4,7,8,11 to user
	*/
	printf("Disk Read Write Stats:\n\n");
  
	fp = fopen("/proc/diskstats","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }


	char line[LINE_LENGTH];
  int foundDisk = 0;
  int index = 0;
  while (fgets(line, sizeof(line), fp)) {
    int elements= 0;
	index++;
	if(index > 9){ //the initial disk location 

      char * splitSpace[MAX_SPLIT_LENGTH * 2];
    
  parseSpace(line, splitSpace);
    printf("\n");
    printf("Disk Name: %s\n",splitSpace[11]);
    printf("Disk Reads: %s\n",splitSpace[12]);
    printf("Disk Writes: %s\n",splitSpace[15]);
    printf("Disk Time Spent Reading: %s\n",splitSpace[16]);
    printf("Disk Time Spent Writing: %s\n",splitSpace[19]);
    printf("\n");
    }
		
	}
  fclose(fp);
  
  
  
}

void getMem(){
  // location = /proc/meminfo
  printf("Memory Info: \n\n");
   fp = fopen("/proc/meminfo","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }


    char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
		if(strstr(line, "MemTotal")){
			printf("%s\n",line);
		}
    if(strstr(line, "MemFree")){
			printf("%s\n",line);
			break;
		}
	}
  
  fclose(fp);
}



void getContextSwitches(){
  // location = /proc/stat
  fp = fopen("/proc/stat","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }
  

  char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
		if(strstr(line, "ctxt ")){
			parseSpace(line, splitString);
      printf("Context Switches: %s\n", splitString[1]);
			break;
		}
	}
  
  fclose(fp);
}


void getProcs(){
  //location = /proc/stat
  fp = fopen("/proc/stat","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }



    char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
		if(strstr(line, "processes")){
			parseSpace(line, splitString);
      printf("\nProcesses Created Since Reboot: %s\n", splitString[1]);
    
			break;
		}
	}
  fclose(fp);
  
}

void parseSpace(char * stringToSplit, char * splitSpace[MAX_SPLIT_LENGTH]){
    int  elements = 0;
    char * buffer;
    while((splitSpace[elements] = strsep(&stringToSplit, WHITESPACE)) != NULL){
        elements++;
    }
}




void grabCPUInfo(const char * cpu){
  // location = /proc/cpuinfo
	printf("CPU Information:\n");
  
	fp = fopen(cpu,"r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }




         char line[256];

    while (fgets(line, sizeof(line), fp)) {
	if(strstr(line, "model name")){
		printf("%s",line);
	}
	if(strstr(line, "vendor_id")){
		printf("%s",line);
	}
	if(strstr(line, "cpu_MHz")){
                printf("%s",line);
        }
	if(strstr(line, "cache size")){
                printf("%s",line);
        }
	if(strstr(line, "model")){
                printf("%s",line);
      }
	if(strstr(line, "cpu cores")){
                printf("%s",line);
    }

        
    }
    fclose(fp);
}

float getTimeSinceLastReboot(){
  // location = /proc/uptime
	fp = fopen("/proc/uptime","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return 0;
        }


	char line[LINE_LENGTH];
	char * splitSpace[MAX_SPLIT_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
		parseSpace(line, splitSpace);
	}
	printf("Time (seconds) since last reboot: %s\n",splitSpace[0]);
  fclose(fp);
  return atof(splitSpace[0]);
}


void getTimeOfLastReboot(float timeOfReboot){
  time_t timeNow;
  time_t timeThen;
  struct tm* time_info;
  time(&timeNow);
  time_info = localtime(&timeNow);
  char timeStr[LINE_LENGTH];
  timeThen = timeNow - timeOfReboot;
  timeNow -= timeOfReboot;
  time_info = localtime(&timeNow);
  strftime(timeStr, sizeof(timeStr), "%a %Y-%m-%d %H:%M:%S %Z", time_info);
  printf("\nTime Of Last Boot: %s\n", timeStr);
}


void grabKernelVersion(){
  // location = /proc/stat
	fp = fopen("/proc/stat","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }


    char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
      if(strstr(line, "processes")){
        parseSpace(line, splitString);
        printf("\nProcesses Created Since Reboot: %s\n", splitString[1]);
        break;
      }
    }
    fclose(fp);
}

void grabLoadAvg(){
  
  /*
  
  The /proc/loadavg file will show loadAverages from the past one, five, and ten minute periods along 
  with number of processes and the total number of created processes. So, to account for the sample time, 
  we will only show the ONE minute period slot EVERY sample time for the AVERAGE OBSERVATION time. 
  
  */
  
  
  fp = fopen("/proc/loadavg","r");
	if(fp == NULL){
                printf("File cannot be opened!");
                return;
        }


    char line[LINE_LENGTH];
    char * splitString[MAX_SPLIT_LENGTH];
	
    while (fgets(line, sizeof(line), fp)){
			parseSpace(line, splitString);
      printf("%s\n",splitString[0]);     
			break;
		}
	
   fclose(fp);
  
}



void runPart1(){
  //When no options are supplied; ./ksamp
		printf("\n");
		grabCPUInfo(CPU_INFO_LOC);
		printf("\n");
		grabKernelVersion();
		printf("\n");
		getTimeSinceLastReboot();
		printf("\n");
}

void runPart2(){
  // when -s option is applied
         printf("\n");
				 getTimeInCPUModes();
         printf("\n");
				 getReadWrites();
         getContextSwitches();
         float timeOfReboot = getTimeSinceLastReboot();
         getTimeOfLastReboot(timeOfReboot);
         getProcs();
}


void runPart3(int sampleTime, int obTime){
  // when -l and two arguments are supplied
  getMem();
  if(sampleTime > 0 && obTime > 0){
  printf("Load Averages\n");
  printf("Sampling every %d seconds for %d seconds\n",sampleTime,obTime);
  time_t start, end;
   double elapsed;  // seconds
   start = time(NULL);
   int terminate = 0;
   while (!terminate) {
     end = time(NULL);
     elapsed = difftime(end, start);
     if (elapsed >= obTime /* seconds */)
       terminate = 1;
     else{
       sleep(sampleTime);
       grabLoadAvg();
     }
   }
  }
else{
	printf("Please enter positive numbers!\n");
}
    
  
  
}



int main(int argc, char ** argv){
	
	//No argument = CPU type, Kernel Version, Time Since Last Reboot. 
	// -s = see above
	// -l = see above
	int option = 0;
  
  
	if(argc > 1){
   while ((option = getopt(argc, argv,":sl:")) != -1) {
        switch (option) {
             case 's' : 
                 runPart1();
                 runPart2();
                 break;
             case 'l' : ; 
                 
                 int averageTime = atoi(optarg);
                 if (optind < argc && *argv[optind] != '-'){
                    int sampleTime = atoi(argv[optind]);
                    optind++;
                    runPart1();
                    runPart2();
                    runPart3(averageTime, sampleTime);
                    break;
                 } 
 
                 else {
                    fprintf(stderr, "\n-l option requires two arguments <SAMPLE TIME> <TIME LENGTH>\n\n");
                    break;
                 }
                 
		         case '?':
                 printf("-%c is an unknown character!!\n",optopt);
                 return EXIT_FAILURE;
             
        }
    }
	}
	else{
		runPart1();
	}
  
  
  

}
