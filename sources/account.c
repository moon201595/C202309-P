#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

#define GOODS 100  // 산 물건

struct Account_Book {  // 날짜, 내역, 금액을 담은 구조체
  int year;
  int month;
  int day;
  char description[50];  // 내역
  float amount;          // 금액
};
struct Account_Book expenses[GOODS];  // 지출 내역을 담을 구조체 배열
struct Account_Book incomes[GOODS];  // 소득 내역을 담을 구조체 배열


// 총 지출 및 소득 출력해주는 함수 정의
void calculateTotal(struct Account_Book expenses[],
                    struct Account_Book incomes[], int expense_count,
                    int income_count, int year, int month) {
  float totalExpenses = 0.0;
  float totalIncomes = 0.0;

  for (int i = 0; i < expense_count; ++i) {
    if (expenses[i].year == year && expenses[i].month == month) {
      totalExpenses += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {
    if (incomes[i].year == year && incomes[i].month == month) {
      totalIncomes += incomes[i].amount;
    }
  }

  printf("\n\n%d년 %d월의 총 지출: %.f원\n\n", year, month, totalExpenses);
  printf("\n\n%d년 %d월의 총 소득: %.f원\n\n", year, month, totalIncomes);
}


void decideCurrent( // 마지막 지출, 소득 입력 날짜를 현재 날짜로 인식하게 하는 함수 정의      
    struct Account_Book expenses[],  
    struct Account_Book incomes[], int expense_count, int income_count,
    int *currentYear, int *currentMonth) {
  for (int i = 0; i < expense_count; ++i) {
    if (expenses[i].year > *currentYear ||
        (expenses[i].year == *currentYear &&
         expenses[i].month > *currentMonth)) {
      *currentYear = expenses[i].year;
      *currentMonth = expenses[i].month;
    }
  }

  for (int i = 0; i < income_count; ++i) {
    if (incomes[i].year > *currentYear ||
        (incomes[i].year == *currentYear && incomes[i].month > *currentMonth)) {
      *currentYear = incomes[i].year;
      *currentMonth = incomes[i].month;
    }
  }
}

// 파일을 account_list 메모장에 저장하는 함수 정의
void saveAccount(struct Account_Book expenses[], int expense_count,
                 struct Account_Book incomes[], int income_count) {
  FILE *file;
  fopen_s(&file, "account_list.txt", "w");  // 파일 열기
  // 불러온 파일들이 종료 시 메모장에 다시 저장되기 때문에 덮어쓰기 기능으로 선택

  if (file != NULL) {
    if (expense_count > 0 ||
        income_count > 0) {  // 지출이나 소득이 있을 때만 파일에 저장
      fprintf(file, "Expense list:\n");  // 지출 내역 저장
      for (int i = 0; i < expense_count; ++i) {
        fprintf(file, "%d년 %d월 %d일 - %s, %.f원\n", expenses[i].year,
                expenses[i].month, expenses[i].day, expenses[i].description,
                expenses[i].amount);
      }

      fprintf(file, "\nIncome list:\n");  // 소득 내역 저장
      for (int i = 0; i < income_count; ++i) {
        fprintf(file, "%d년 %d월 %d일 - %s, %.f원\n", incomes[i].year,
                incomes[i].month, incomes[i].day, incomes[i].description,
                incomes[i].amount);
      }
      printf("\n파일에 데이터를 추가로 저장했습니다.\n");
    } else {
      printf("\n데이터를 입력하지 않아 파일에 내용을 저장하지 않습니다.\n");
    }
    fclose(file);
  } else {
    printf("파일을 저장할 수 없습니다.\n");
  }
}

// 파일을 account_list 메모장에서 불러오는 함수 정의
void loadAccounts(struct Account_Book expenses[], struct Account_Book incomes[],
                  int *expense_count, int *income_count, const char *fileName) {
  FILE *file;
  fopen_s(&file, fileName, "r");  // 파일 열기 (읽기 모드)

  if (file != NULL) {
    char buffer[100];
    int is_expense = 0;  // 파일에서 지출과 소득을 구별하기 위한 변수

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      int year, month, day;
      char description[50];
      float amount;

      if (strstr(buffer, "Expense list:") != NULL) {
        is_expense = 1;  // 'Expense list'를 발견하면 지출로 인식
      } else if (strstr(buffer, "Income list:") != NULL) {
        is_expense = 0;  // 'Income list'를 발견하면 소득으로 인식
      }

      if (is_expense) {  // 지출인 경우
        if (sscanf(buffer, "%d년 %d월 %d일 - %49[^,], %f원\n", &year, &month,
                   &day, description, &amount) == 5) {
          expenses[*expense_count].year = year;
          expenses[*expense_count].month = month;
          expenses[*expense_count].day = day;
          strcpy_s(expenses[*expense_count].description,
                   sizeof(expenses[*expense_count].description), description);
          expenses[*expense_count].amount = amount;
          (*expense_count)++;
        }
      } else {  // 소득인 경우
        if (sscanf(buffer, "%d년 %d월 %d일 - %49[^,], %f원\n", &year, &month,
                   &day, description, &amount) == 5) {
          incomes[*income_count].year = year;
          incomes[*income_count].month = month;
          incomes[*income_count].day = day;
          strcpy_s(incomes[*income_count].description,
                   sizeof(incomes[*income_count].description), description);
          incomes[*income_count].amount = amount;
          (*income_count)++;
        }
      }
    }
    fclose(file);
  } else {
    printf("파일을 열 수 없습니다.\n");
  }
}

