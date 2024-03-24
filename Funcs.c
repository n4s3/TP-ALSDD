#include <stdlib.h>
#include "AbstractMachine.h"
#include <locale.h>
#inlcude "Funcs.h"


// transfer amount from bankaccount a to bankaccount b
void TransferAmount(BankAccount *A, BankAccount *B, float Amount){
  // transfering 
  B->Balance = B->Balance + Amount;
  A->Balance = A->Balance - Amount;
  // creating the transaction nodes 
  // allocating a temptran
  Transaction **Temp_A;
  CreateNewTran(Temp_A);
  *Temp_A = A->transactionList;

  Transaction **Temp_B;
  CreateNewTran(Temp_B);
  while (Temp_A != NULL) {
    *Temp_A = next_Transaction(*Temp_A);
  }
  Transaction **NewA;
  CreateNewTran(NewA);
  (*Temp_A)->nextTransaction = *NewA;
  // This date is going to be changed of course 
  Date Date;
  AssignTranData(*NewA, 'T', Date, Amount);

  *Temp_B = B->transactionList;
  while (Temp_B != NULL) {
    *Temp_B = next_Transaction(*Temp_B);
  }

  Transaction **NewB;
  CreateNewTran(NewB);
  (*Temp_B)->nextTransaction = *NewB;
  AssignTranData(*NewB, 'D', Date, Amount);
}

int CheckAmount(BankAccount *A){
  return A->Balance;
}


// here we define a function to printout the date
static void Printdate(BankAccount *A){
  Date Date;
  int i;
  char Date_str[9] = {0};// to store the characters of the date arrays 
  // initialized with null terminator
  int n = 0;
  // we will use a function called sprintf to "convert" our array of integers into an array 
  // of characters 
  for (i=0; i<=4; ++i){
    n += sprintf (&Date_str[n], "%d.", A->transactionList->Date.Year[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], "%d.", A->transactionList->Date.Month[i]);
  }
  i = 0;
  for (i=0; i<=2; i++) {
    n += sprintf (&Date_str[n], "%d", A->transactionList->Date.Day[i]);
  }
}
void CheckHistory(BankAccount *A){
  Transaction **Temp;
  CreateNewTran(Temp);
  *Temp = A->transactionList;
  while(Temp != NULL){
    Printdate(A);
    *Temp = next_Transaction(*Temp);
  }
}


