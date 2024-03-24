#ifndef ABSTRACTMACHINE_H_INCLUDED
#define ABSTRACTMACHINE_H_INCLUDED
typedef struct Name {
  char First[15];
  char Last[15];
} Name;

// The record of the account Node Has a pointer to a next_account and the head of 
// the transactions list
// Date Record
struct Date {
  int Year[4];
  int Month[2];
  int Day[2];
};
typedef struct Date Date;
// The record of the transaction Node points to the next_transaction
struct Transaction {
  char opcode[1];
  Date Date;
  int Balance;
 struct Transaction *adrr;
};
typedef struct Transaction Transaction;

struct BankAccount {
  int Number;
  int Code;
  Name Name;
  int Balance;
  struct BankAccount *adr;
  struct Transaction *addr;
};
typedef struct BankAccount BankAccount;
// The AbstarctMachineFunctions
void createAccount(BankAccount **p);
void DeleteAccount (BankAccount *p);
void ass_adr(BankAccount *p ,BankAccount *q);
void ass_addr(BankAccount *p , Transaction *q);
BankAccount *nextAccount(BankAccount *p);
BankAccount *nextOpp(BankAccount *p);
void ass_data (BankAccount *p , Transaction *q , int N , int c , Name Na , int b);
void allocateopp(Transaction **p);
Transaction *Nextopp(Transaction *p);
void ass_date(Transaction *p ,Date D);
#endif
