#include "AbstractMachine.h"
#include "Read-Write-Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 256
static const char *file_name = "Accounts.txt";
static const char *transactionsfile = "Transactions.txt";
BankAccount *createBankAccountNode(int accountNumber, char *accountHolder,
                                   float balance) {
  BankAccount *newNode = (BankAccount *)malloc(sizeof(BankAccount));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->Number = accountNumber;
  strcpy(newNode->Name.First, accountHolder);
  newNode->Balance = balance;
  newNode->transactionList = NULL;
  newNode->nextBAcc = NULL;

  return newNode;
}
Transaction *createTransactionNode(Date date, char opcode, float amount) {
  Transaction *newNode = (Transaction *)malloc(sizeof(Transaction));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->Date = date;
  newNode->opcode = opcode;
  newNode->Balance = amount;
  newNode->nextTransaction = NULL;
  return newNode;
}
void addTransaction(BankAccount *account, Date date, char opcode,
                    float amount) {
  Transaction *newTransaction = createTransactionNode(date, opcode, amount);
  newTransaction->nextTransaction = account->transactionList;
  account->transactionList = newTransaction;
}
BankAccount *findAccountByNumber(BankAccount *head, int accountNumber) {
  BankAccount *current = head;
  while (current != NULL) {
    if (current->Number == accountNumber) {
      return current;
    }
    current = current->nextBAcc;
  }
  return NULL; // Account not found
}
int main(void) {
  BankAccount *head = NULL;
  head = readAccountInfo(file_name, head);

  // Read Accounts.txt file and populate bank account linked list
  FILE *accountsFile = fopen("Accounts.txt", "r");
  if (accountsFile == NULL) {
    perror("Error opening Accounts.txt");
    exit(EXIT_FAILURE);
  }
  char line[100];
  while (fgets(line, sizeof(line), accountsFile) != NULL) {
    if (strncmp(line, "AccountNumber:", 14) == 0) {
      int accountNumber;
      char accountHolder[50];
      float Balance;

      // Parse account number and account holder directly from the line
      sscanf(line, "AccountNumber: %d %s %f", &accountNumber, accountHolder,
             &Balance);

      BankAccount *newAccount =
          createBankAccountNode(accountNumber, accountHolder, Balance);
      newAccount->nextBAcc = head;
      head = newAccount;
    }
  }
  fclose(accountsFile);
  FILE *transactionsFile = fopen("Transactions.txt", "r");
  if (transactionsFile == NULL) {
    perror("Error opening Transactions.txt");
    exit(EXIT_FAILURE);
  }

  BankAccount *currentAccount = NULL;
  while (fgets(line, sizeof(line), transactionsFile) != NULL) {
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
      fgets(line, sizeof(line), transactionsFile);
      while (fgets(line, sizeof(line), transactionsFile) != NULL &&
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
  fclose(transactionsFile);
  BankAccount *current = head;
  while (current != NULL) {
    printf("Account Number: %d\n", current->Number);
    printf("Account Holder: %s\n", current->Name.First);
    printf("Balance: %f\n", current->Balance);
    printf("Transactions:\n");
    Transaction *currentTransaction = current->transactionList;
    while (currentTransaction != NULL) {
      printf("Date: %d-%d-%d, Opcode: %c, Amount: %.2f\n",
             currentTransaction->Date.Year, currentTransaction->Date.Month,
             currentTransaction->Date.Day, currentTransaction->opcode,
             currentTransaction->Balance);
      currentTransaction = currentTransaction->nextTransaction;
    }
    printf("\n");
    current = current->nextBAcc;
  }
  current = head;
  while (current != NULL) {
    Transaction *tempTransaction = current->transactionList;
    while (tempTransaction != NULL) {
      Transaction *nextTransaction = tempTransaction->nextTransaction;
      free(tempTransaction);
      tempTransaction = nextTransaction;
    }
    BankAccount *nextAccount = current->nextBAcc;
    free(current);
    current = nextAccount;
  }
  return 0;
}
