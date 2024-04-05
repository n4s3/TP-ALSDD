#include "Read-Write-Functions.h"
#include "AbstractMachine.h"
#include "Funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 256
static const char *file_name = "Accounts.txt";
static const char *date_file = "Date.txt";
static const char *op_file = "Opcode.txt";
static const char *transactionsfile = "Transactions.txt";
static const char *bal_file = "BalanceOfEachTransaction.txt";
// in this function we go through all the info that's in the file Account.txt
// and create a linked list of BankAccounts
//
Date parseDate(char *dateStr) {
  Date date;
  sscanf(dateStr, "%d-%d-%d", &date.Year, &date.Month, &date.Day);
  return date;
}
BankAccount *readAccountInfo(const char *file_name, BankAccount *head) {
  // we used fopen from stdio.h with parameter r to open the .txt file
  // and return a pointer if successful
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error Accessing file\n");
    exit(EXIT_FAILURE);
  }
  char line[max_len];
  while (fgets(line, sizeof(line), file) != NULL) {
    char FirstName[15];
    char LastName[15];
    int Number;
    int Code;
    float Balance;
    if (sscanf(line, "%s %s %d %d %f", FirstName, LastName, &Number, &Code,
               &Balance) == 5) {
      // here in the condition we checked if all the data is in the line using
      // sscanf it returns an int of how many variable it had read(basically
      // like scanf)
      addAccountToList(&head, FirstName, LastName, Number, Code, Balance);
    } else {
      printf("You Have Entered Wrong The wrong type\n");
    }
  }
  return head;
  fclose(file);
}

void writeAccountInfo(const char *file_name, BankAccount *AddedAcc) {
  FILE *file = fopen(file_name, "a"); // here we used append mode
  // Instead of write mode which doesn't overwirte the file
  if (file == NULL) {
    printf("Error Accessing file\n");
    return;
  }
  fprintf(file, "%s %s %d %d %f", AddedAcc->Name.First, AddedAcc->Name.Last,
          AddedAcc->Number, AddedAcc->Code, AddedAcc->Balance);
  fclose(file);
}
BankAccount *searchAccountByNumber(const char *file_name, int ToLookForNumber) {
  BankAccount *head = NULL;
  head = readAccountInfo(file_name, head);
  BankAccount *current = head;
  while (current != NULL && current->Number != ToLookForNumber) {
    current = next_Account(current);
    if (current == NULL) {
      printf("This account doesn\'t exist\n");
    }
  }
  return current;
}

// 👉 IMPORTANT : In order to work with this function we have to make sure that
// we already :
// have a linked list of bank accounts then we can associate those transactions
// with their given bank accounts.
void readTransaction(const char *file) {
  FILE *T_FILE = fopen(transactionsfile, "r");
  if (T_FILE == NULL) {
    perror("Error opening Transactions.txt");
    exit(EXIT_FAILURE);
  }
  char line[max_len];
  BankAccount *currentAccount = NULL;
  BankAccount *head = NULL;
  head = readAccountInfo(file_name, head);
  while (fgets(line, sizeof(line), T_FILE) != NULL) {
    if (strncmp(line, "AccountNumber:", 14) == 0) {
      int accountNumber;
      sscanf(line, "AccountNumber: %d", &accountNumber);
      currentAccount = findAccountByNumber(head, accountNumber);
      if (currentAccount == NULL) {
        printf("Account not found for account number %d\n", accountNumber);
        continue;
      }
    } else if (strncmp(line, "Transactions:", 13) == 0) {
      // Skip the "Transactions:" line
      fgets(line, sizeof(line), T_FILE);
      while (fgets(line, sizeof(line), T_FILE) != NULL &&
             strcmp(line, "\n") != 0) {
        Date date;
        char opcode;
        float amount;
        sscanf(line, "%d-%d-%d %c %f", &date.Year, &date.Month, &date.Day,
               &opcode, &amount);
        addTransaction(currentAccount, date, opcode, amount);
      }
    }
  }
  fclose(T_FILE);
}
