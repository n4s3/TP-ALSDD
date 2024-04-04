#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "AbstractMachine.h"
#include <stdbool.h>
void TransferAmount(BankAccount *h , int N1,int N2, float Amount,Date D);
float CheckAmount(BankAccount *h , int Number );
void CheckHistory(BankAccount *h,int Number ,  Date D);
void CheckHistoryV2(BankAccount *Account,  Date D);
void Deposit( BankAccount * h , int Number , float De , Date D ) ;
char *Printdate(Transaction *A);
bool isAdmin();
void EditCodeAndOrCustomer(BankAccount *h, int Number, int x);
void printBankAccounts(BankAccount *h);
void Withdrawal(BankAccount *h, int Number, float Amount,
                Date D);
Date readDate();
#endif
