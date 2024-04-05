
#include "AbstractMachine.h"
#include "Read-Write-Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define file_name "Accounts.txt"
#define transactionfile "Transactions.txt"

#define MAX_LEN 256

// Function to create a new bank account node
BankAccount *createBankAccountNode(int accountNumber, char *accountHolder,
                                   float balance) {
  BankAccount *newNode = (BankAccount *)malloc(sizeof(BankAccount));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->Number = accountNumber;
  strncpy(newNode->Name.First, accountHolder,
          MAX_LEN); // Use strncpy to prevent buffer overflow
  newNode->Balance = balance;
  newNode->transactionList = NULL; // Initialize transaction linked list to NULL
  newNode->nextBAcc = NULL;
  return newNode;
}

// Function to create a new transaction node
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

// Function to add a transaction to the transaction list of a bank account
void addTransaction(BankAccount *account, Date date, char opcode,
                    float amount) {
  Transaction *newTransaction = createTransactionNode(date, opcode, amount);
  newTransaction->nextTransaction = account->transactionList;
  account->transactionList = newTransaction;
}

// Function to find a bank account by account number
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

// Function to read account information from file
BankAccount *readAccountInfo(const char *fileName, BankAccount *head) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char line[MAX_LEN];
  int accountNumber;
  char accountHolder[MAX_LEN];
  float balance;
  while (fgets(line, sizeof(line), file) != NULL) {
    if (sscanf(line, "AccountNumber: %d %s %f", &accountNumber, accountHolder,
               &balance) == 3) {
      BankAccount *newAccount =
          createBankAccountNode(accountNumber, accountHolder, balance);
      newAccount->nextBAcc = head;
      head = newAccount;
    }
  }

  fclose(file);
  return head;
}

// Function to read transactions and associate with respective bank accounts
void readTransactions(const char *fileName, BankAccount *head) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  char line[MAX_LEN];
  BankAccount *currentAccount = NULL;
  while (fgets(line, sizeof(line), file) != NULL) {
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
      while (fgets(line, sizeof(line), file) != NULL &&
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

  fclose(file);
}

// Function to print bank account details and associated transactions
void printBankAccounts(BankAccount *head) {
  BankAccount *current = head;
  while (current != NULL) {
    printf("Account Number: %d\n", current->Number);
    printf("Account Holder: %s\n", current->Name.First);
    printf("Balance: %.2f\n", current->Balance);
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
}

// Function to free memory allocated for linked lists
void freeMemory(BankAccount *head) {
  BankAccount *current = head;
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
}

int main(void) {
  BankAccount *head = NULL;
  head = readAccountInfo(file_name, head);
  readTransactions(transactionsfile, head);
  printBankAccounts(head);
  freeMemory(head);
  return 0;
}
