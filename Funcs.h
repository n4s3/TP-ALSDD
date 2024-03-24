#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "AbstractMachine.h"
// transfer amount from bankaccount a to bankaccount b
void TransferAmount(BankAccount *A, BankAccount *B, float Amount);
int CheckAmount(BankAccount *A);
char CheckHistory(BankAccount *A);
#endif
