#include <algorithm>
#include <stdlib.h>
#include "AbstractMachine.h"

void createAccount(BankAccount **p){
  *p=malloc(sizeof(BankAccount));
}
void DeleteAccount (BankAccount *p){
  free(p);
}
// Link two nodes
void AssignAccount(BankAccount *p ,BankAccount *q){
  p->nextBAcc=q;
}
// Link the account with the head of the transaction list
void AssignListToBank(BankAccount *p , Transaction *q){
    p->transactionList=q;
}
// Get the address of the Next bankaccount
BankAccount *next_Account(BankAccount *p){
  return p->nextBAcc;
}
// Get the address of the next Transaction
Transaction *next_Transaction(Transaction *p){
  return p->nextTransaction;
}
// Create a new Transaction node
void CreateNewTran(Transaction **p){
  *p=malloc(sizeof(Transaction ));
}

// In this function we can't copy the elemets of an array into another
// therefore we create the function CopyArray
int *CopyArray(int n, int *A, int *B){
  int i;
  // n is the last index for (i=0; i<=n; i++){
    // copy the elements of the array b into the array a
    A[i] = B[i];
  }
  return A;
}
void Ass_Date(Transaction *p ,Date D){
  CopyArray(4, p->Date.Year, D.Year);
  CopyArray(2, p->Date.Month, D.Month);
  CopyArray(2, p->Date.Day, D.Day);
} // assign the date directly we do not need this

// Assign Data of a BankAccount(Edit)
void AssignAccData(BankAccount *p, int N, int C, Name Na, float B){
  p->Number = N;
  p->Code = C;
  p->Balance = B;
  p->Name = Na;
}

char *CopyCharArray(char *A, char *B){
  int i=0;
  while (B[i] != '\0'){
    A[i] = B[i];
    ++i;
  }
  A[i] = '\0';
  return A;
}
void AssignTranData(BankAccount *q ,Transaction *p,Date D,char o, float B){
  p ->Balance = B;
  p ->Date = D;
  p ->opcode = o;
} // changed we assign directly the leter to the transaction type 
void AssignTranList(Transaction *p , Transaction *q ){
 p -> nextTransaction = q ; 
}
