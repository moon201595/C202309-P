#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculateTotal(struct Account_Book expenses[],  // Ư�� ���� �ҵ�� ���� ���� ��� �Լ� ����
                    struct Account_Book incomes[],
                    int expense_count, int income_count, int year, int month);

void decideCurrent(  // ������ ����, �ҵ� �Է� ��¥�� ���� ��¥�� �ν��ϴ� �Լ�                    
    struct Account_Book expenses[], struct Account_Book incomes[],
    int expense_count, int income_count, int *currentYear, int *currentMonth);

 
void saveAccount(struct Account_Book expenses[], // ������ account_list �޸��忡 �����ϴ� �Լ� ���� 
                 int expense_count,  struct Account_Book incomes[], int income_count);

void loadAccounts(struct Account_Book expenses[], // ���� �ҷ����� �Լ� ����
                  struct Account_Book incomes[],  
                  int *expense_count, int *income_count, const char *fileName);

