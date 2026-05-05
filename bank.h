#ifndef BANK_H
#define BANK_H

#include <stdio.h>

// Structure definition
struct account {
    int id;
    int pin;
    double balance;
};

// Function prototypes
void menu(double *pBalance, FILE *pF, struct account bankUsers[], int totalUsers, int userIdx);
void depo(double *pBalance, FILE *pF);
void with(double *pBalance, FILE *pF);
void printBalance(double *pBalance);
void transfer(struct account bankUsers[], int totalUsers, int userIdx, FILE *pF);
int auth(struct account bankUsers[], int totalUsers);
void printStatement(FILE *pF);
void saveAccounts(struct account bankUsers[], int totalUsers);
int loadAccounts(struct account bankUsers[]);

#endif
