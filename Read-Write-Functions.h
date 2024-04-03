#include "AbstractMachine.h"
#ifndef RWFUNCTIONS_H_INCLUDED
#define RWFUNCTIONS_H_INCLUDED

BankAccount *readAccountInfo(const char *file_name, BankAccount *head);
void writeAccountInfo(const char *file_name, BankAccount *head);
BankAccount *searchAccountByNumber(const char *file_name, int ToLookForNumber);
void readTransactionList(BankAccount *head,const char *DateFile, const char *OpCodeFile, const char *BalanceOfEachTransaction);// This function goes to the text file Opcode.txt Date.txt BalanceOfEachTransaction.txt and takes the data of each transaction and link it with the last transaction

#endif
