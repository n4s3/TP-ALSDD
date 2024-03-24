#include <stdlib.h>
#include "AbstractMachine.h"


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

