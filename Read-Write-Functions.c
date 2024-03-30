#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AbstractMachine.h"
#include "Read-Write-Functions.h"
#include "Funcs.h"


void readAccountInfo(const char *file_name){
  FILE *file = fopen(file_name, "r");
  if (file == NULL){
    printf("Error Accessing file\n");
    return;
  }
}
