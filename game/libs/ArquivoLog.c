#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArquivoLog.h"

void ArquivoLog(char *msg) {
	FILE *ArquivoLog;
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	int dia = t->tm_mday;
	int mes = t->tm_mon + 1;
	int ano = t->tm_year + 1900;
	int hora = t->tm_hour;
	int minuto = t->tm_min;
	int segundo = t->tm_sec;

	ArquivoLog = fopen("LogInterno.log", "a");
		
		fprintf(ArquivoLog, "%d:%d:%d %d/%d/%d - \"%s\"\n", hora, minuto, segundo, dia, mes, ano, msg);
		fprintf(ArquivoLog, "--\n");

	fclose(ArquivoLog);
}

void erro(char *msg){
	printf("%s\n", msg);
	ArquivoLog(msg);
	exit(EXIT_FAILURE);
}

void saveInfo(int *nInfo) {
	FILE *Info;
	int count = 0;
	Info = fopen("info.tmp", "w");
	while(count < 2) {
		fprintf(Info, "%d\n", nInfo[count]);
		count++;
	}
	fclose(Info);
}

void getInfo( int *info, int max ) {
	FILE *Info;
	int aux;
	int count = 0;
	Info = fopen("info.tmp", "r");
	while(count < max) {
		fscanf(Info, "%d", &aux);
		info[count] = aux;
		count++;
	}
	fclose(Info);
}
