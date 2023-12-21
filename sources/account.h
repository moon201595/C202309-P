#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculateTotal(struct Account_Book expenses[],  // 특정 월의 소득과 지출 총합 출력 함수 선언
                    struct Account_Book incomes[],
                    int expense_count, int income_count, int year, int month);

void decideCurrent(  // 마지막 지출, 소득 입력 날짜를 현재 날짜로 인식하는 함수                    
    struct Account_Book expenses[], struct Account_Book incomes[],
    int expense_count, int income_count, int *currentYear, int *currentMonth);

 
void saveAccount(struct Account_Book expenses[], // 파일을 account_list 메모장에 저장하는 함수 선언 
                 int expense_count,  struct Account_Book incomes[], int income_count);

void loadAccounts(struct Account_Book expenses[], // 파일 불러오는 함수 선언
                  struct Account_Book incomes[],  
                  int *expense_count, int *income_count, const char *fileName);

