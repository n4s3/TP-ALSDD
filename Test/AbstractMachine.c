#include "AbstractMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createAccount(BankAccount **p) {
  *p = (BankAccount *)malloc(sizeof(BankAccount));
  if (p == NULL) {
    printf("Memory Allocation failed");
  }
}
void DeleteAccount(BankAccount *p) { free(p); }
// Link two nodes
void AssignAccount(BankAccount *p, BankAccount *q) { p->nextBAcc = q; }
// Link the account with the head of the transaction list
void AssignListToBank(BankAccount *p, Transaction *q) {
  p->transactionList = q;
}
// Get the address of the Next bankaccount
BankAccount *next_Account(BankAccount *p) { return p->nextBAcc; }
// Get the address of the next Transaction
Transaction *next_Transaction(Transaction *p) { return p->nextTransaction; }
// Create a new Transaction node
void CreateNewTran(Transaction **p) {
  *p = (Transaction *)(sizeof(Transaction));
}

// In this function we can't copy the elemets of an array into another
// therefore we create the function CopyArray
int *CopyArray(int n, int *A, int *B) {
  int i;
  // n is the last index for (i=0; i<=n; i++){
  // copy the elements of the array b into the array a
  for (i = 0; i < n; i++) {
    A[i] = B[i];
  }
  return A;
}

// Assign Data of a BankAccount(Edit)
void AssignAccData(BankAccount *p, int N, int C, Name Na, float B) {
  p->Number = N;
  p->Code = C;
  p->Balance = B;
  p->Name = Na;
}

char *CopyCharArray(char *A, char *B) {
  int i = 0;
  while (B[i] != '\0') {
    A[i] = B[i];
    ++i;
  }
  A[i] = '\0';
  return A;
}
void AssignTranData(Transaction *p, Date D, char o, float B) {
  p->Balance = B;
  p->Date = D;
  p->opcode = o;
} // changed we assign directly the leter to the transaction type
void AssignTranList(Transaction *p, Transaction *q) { p->nextTransaction = q; }
void DeleteTran(Transaction *p) { free(p); }

void addAccountToList(BankAccount **head, char FirstName[15], char LastName[15],
                      int Number, int Code, float Balance) {
  BankAccount *new_account;
  createAccount(&new_account);
  strcpy(new_account->Name.First, FirstName);
  strcpy(new_account->Name.Last, LastName);
  new_account->Number = Number;
  new_account->Code = Code;
  new_account->Balance = Balance;
  if (*head == NULL) {
    *head = new_account;
  } else {
    BankAccount *current = *head;
    while (current->nextBAcc != NULL) {
      current = next_Account(current);
    }
    current->nextBAcc = new_account;
    new_account->nextBAcc = NULL;
  }
}
void addTransactionToList(Transaction **head, char opcode, Date date,
                          float balance) {
  Transaction *newTransaction = NULL;
  CreateNewTran(&newTransaction);
  AssignTranData(newTransaction, date, opcode, balance);
  if (*head == NULL) {
    *head = newTransaction;
  } else {
    Transaction *current = *head;
    while (current->nextTransaction != NULL) {
      current = current->nextTransaction;
    }
    current->nextTransaction = newTransaction;
  }
}
