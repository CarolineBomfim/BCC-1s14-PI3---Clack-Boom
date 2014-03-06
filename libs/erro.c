#include <stdio.h>
#include <stdlib.h>
#include "ArquivoLog.h"

void erro(char *msg){
	printf("%s\n", msg);
	ArquivoLog(msg);
	exit(EXIT_FAILURE);
}
