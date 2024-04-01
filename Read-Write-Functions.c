#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AbstractMachine.h"
#include "Read-Write-Functions.h"
#define max_len 256
const char *file_name = "Accounts.txt";

void addAccountToList(BankAccount **head, char FirstName[15], char LastName[15], int Number, int Code, float Balance){
  BankAccount *new_account;
  createAccount(&new_account);
  strcpy(new_account->Name.First, FirstName);
  strcpy(new_account->Name.First, FirstName);
  new_account->Number = Number;
  new_account->Code = Code;
  new_account->Balance = Balance;
  if (*head == NULL){
    *head = new_account;
  } else {
    BankAccount *current = *head;
    while (current->nextBAcc != NULL){
      current = next_Account(current);
    }
    current->nextBAcc = new_account;
    new_account->nextBAcc = NULL;
  }
}
void readAccountInfo(const char *file_name, BankAccount **head){
  // we used fopen from stdio.h with parameter r to open the .txt file
  // and return a pointer if successful
  FILE *file = fopen(file_name, "r");
  if (file == NULL){
    printf("Error Accessing file\n");
    return;
  }

  char line[max_len];
  while (fgets(line, sizeof(line), file)) {
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;
    if (sscanf(line, "%s %s %d %d %f", FirstName, LastName, &Number, &Code, &Balance) == 5) {
      addAccountToList(head, FirstName, LastName, Number, Code, Balance);
    } else {
      printf("You Have Entered Wrong The wrong type\n");
    }
  }
  fclose(file);
}
