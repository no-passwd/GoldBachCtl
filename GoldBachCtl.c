#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
char Goldbach(unsigned long long int n) {
    if (n <= 1) return 0;
    for (unsigned long long int i = 2; i * i <= n; i++) {
    if (n % i == 0) return 0;
    }
    return 1;
}
int usage(char *ag){
	printf("%s start\n",ag);
	printf("%s stop\n",ag);
	printf("%s suspend\n",ag);
	printf("%s resume\n",ag);
	printf("%s status\n",ag);
	printf("%s config\n",ag);
	printf("%s --help\n\n",ag);
	printf("Limit cpu usage under 20% -> \"cpulimit --limit 20 -- %s start\" \n",ag);
	return 0;
}
int status(){
	FILE *fp;
	char ch;
	fp = fopen("/tmp/tm_gbdhsignal", "r");
    if (fp == NULL) {
    perror("Error signal");
    return -1;
    }
	while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
    }
	fclose(fp);
	return 0;
}
int Config() {
	unsigned long long int max;
    printf("Please Enter Memory upper limit, the default is: 18446744073709551418: ");
    scanf("%llu", &max);
	int overwrite = 1;
	const char *gbdh_max = "gbdh_max";
	char value[256] = "256";
	if (max > 5) {
    sprintf(value,"%llu",max);
    if (setenv(gbdh_max, value, overwrite) != 0) {
    perror("config max failed");
    return 1;
    }
    }
	int debug=0;
    printf("Turn on debug mode (foreground running mode)?, default 0, Enter 1 to Enable:");
    scanf("%d", &debug);
	const char *gbdh_debug = "gbdh_debug";
	if (debug == 1){
	if (setenv(gbdh_debug, "1", overwrite) != 0) {
    perror("config debug failed");
    return 1;
	}
	}
	execl("/bin/bash","bash",(char *)0);
    return 0;
}
int gbdh() {
	unsigned long long int MAX=0;
	const char *gbdh_max = "gbdh_max";
	char debug=0;
	const char *gbdh_debug = "gbdh_debug";
    char *max_var = getenv(gbdh_max);
	char *debug_var = getenv(gbdh_debug);
    if (max_var) {
    int num = atoi(max_var);
    if (num > 4){
    MAX = num;} 
	else {
    MAX=~MAX;
    MAX-=32; 
    }} 
	else {
    MAX=~MAX;
	MAX-=32; 
    }
	printf("Maximum Num %llu.\n",MAX);
	if (debug_var) {
	if (strcmp("0",debug_var)){}
    debug=1;
    printf("Debug mode is turned on.\n");
	}
	if (!debug) {    
    if (fork() > 0) {
    exit(EXIT_FAILURE);
    }
	if (setsid() < 0) {
    exit(EXIT_FAILURE);
    }
	for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
    close(x);
    }}
	FILE *fp;
	fp = fopen("/tmp/tm_gbdhsignal", "w+");
    if (fp == NULL) {
    perror("Error signal");
    return -1;
    }
    for (unsigned long long int i = 4; i <= MAX; i += 2) {
    char found = 0;
    for (unsigned long long int j = 2; j <= i / 2; j++) {
    if (Goldbach(j) && Goldbach(i - j)) { 
    if (debug) {printf("%llu = %llu + %llu\n", i, j, i - j);}
    if ((j&255) > 128){
    fprintf(fp, "Verified to: %llu = %llu + %llu                              \n", i, j, i - j);
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
    }
    found = 1;
    break;
    }
    }
    if (!found) {
    if (debug) {printf("You proved Goldbach's conjecture that the numbers Of %llu CANNOT be decomposed!\n", i);}
    else {
    fprintf(fp, "You proved Goldbach's conjecture that the numbers Of %llu CANNOT be decomposed!\n", i);
    fflush(fp);
    }
    return 1; 
    }
    }
    if (debug) {printf("Goldbach's conjecture was successfully verified below %llu.\n",MAX);}
    else {
    fprintf(fp, "Goldbach's conjecture was successfully verified below %llu.\n",MAX);
    }
	fclose(fp);
	if (debug) {remove("/tmp/tm_gbdhsignal");
	}
    return 0;
}
int main(int len,char** config) {
	if (len < 2){
    return usage(config[0]);
	}
	if (!strcmp("--help",config[1])){
    int usg = usage(config[0]);
    if (usg !=-1){
    printf("If has any bugs,contact me with snow@netsh.cc\n");
    return usg;
    }
    else {
    return -1;
    }
	}
	if (!strcmp("config",config[1])){
    return Config();
	}
	if (!strcmp("start",config[1])){
    return gbdh();
	}
	if (!strcmp("status",config[1])){
    return status();
	}
	if (!strcmp("suspend",config[1])){
	int pd=getpid();
	char sysbuf[256];
	printf("Worker was ");
	fflush(stdout);
    sprintf(sysbuf,"kill %d &&sleep 1 &&killall -SIGSTOP %s &&echo Process has suspend",pd,config[0]);
    system(sysbuf);
    return 0;
	}
	if (!strcmp("resume",config[1])){
    char sysbuf[256];
	printf("Resumed\n");
    sprintf(sysbuf,"killall -SIGCONT %s",config[0]);
    system(sysbuf);
    return 0;
	}
	if (!strcmp("stop",config[1])){
    char sysbuf[256];
    sprintf(sysbuf,"killall %s",config[0]);
    remove("/tmp/tm_gbdhsignal");
    system(sysbuf);
	}
	return 0;
}
