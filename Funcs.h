#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "AbstractMachine.h"
void TransferAmount(BankAccount *h , int N1,int N2, float Amount,Date D);
int CheckAmount(BankAccount *h , int Number );
void CheckHistory(BankAccount *h,int Number ,  Date D);
void Deposit( BankAccount * h , int Number , float De , Date D ) ;
char *Printdate(Transaction *A);
void EditCodeAndOrCustumer( BankAccount * h , int Number );
#endif
