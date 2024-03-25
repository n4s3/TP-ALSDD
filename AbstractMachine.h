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
  char opcode[1]; // T:Transfer D:Deposit W:Withdrawal
  Date Date;
  float Balance;
 struct Transaction *nextTransaction;
};
typedef struct Transaction Transaction;

struct BankAccount {
  int Number;
  int Code;
  Name Name;
  float Balance;
  struct BankAccount *nextBAcc;
  struct Transaction *transactionList;
};
typedef struct BankAccount BankAccount;
// The AbstarctMachineFunctions
void createAccount(BankAccount **p);
void DeleteAccount (BankAccount *p);
void AssignAccount(BankAccount *p ,BankAccount *q);
void AssignList(BankAccount *p , Transaction *q);// to the Account 
void AssignList ( Transaction *p , Transaction *q); // like assign_adr(p,q);between the nodes of transactions 
BankAccount *next_Account(BankAccount *p);
Transaction *next_Transaction(Transaction *p);
// miskate here
// void AssignData(BankAccount *p , Transaction *q , int N , int c , Name Na , int b);
void CreateNewTran(Transaction **p);
void Ass_Date(Transaction *p ,Date D);
void TransferAmount(BankAccount *A, BankAccount *B, float Amount);
void AssignTranData(BankAccount *q,Transaction *p, char o, Date D, float B); // modified 
void AssignAccData(BankAccount *p, int N, int C, Name Na, float B); // modified
#endif
