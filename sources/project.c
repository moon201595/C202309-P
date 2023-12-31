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
int expense_count = 0;               // 입력된 지출 내역의 개수
int income_count = 0;                // 입력된 소득 내역의 개수

// --------------------------------------함수선언--------------------------------------
void input_Expense(struct Account_Book expenses[]);  // 지출 입력을 위한 함수 선언
void input_Income(struct Account_Book incomes[]);  // 소득 입력을 위한 함수 선언

// 지출 및 소득 수정을 위한 함수 선언
// 이 함수가 호출될 때 아래의 두 함수가 이 함수 안에서 호출될 예정
void modify_list(struct Account_Book expenses[], struct Account_Book incomes[]);
void modify_Expense(struct Account_Book expenses[]);  // 지출 수정을 위한 함수 선언
void modify_Income(struct Account_Book incomes[]);  // 소득 수정을 위한 함수 선언

void display_list(int *year, int *month, struct Account_Book expenses[],
    struct Account_Book incomes[], int expense_count,
    int income_count);  // 특정 월의 소득과 지출 내역 출력 함수 선언


// 종료 시 이번 달 지출, 소득 총합 함수 선언
void printSummary(struct Account_Book expenses[], int expense_count,
                  struct Account_Book incomes[], int income_count);

// 종료 시 이번 달 지출, 소득과 저번 달 지출, 소득 비율 증감 출력 함수 선언
void compare_last_month(struct Account_Book expenses[], int expense_count,
                        struct Account_Book incomes[], int income_count);

// 종료 시 최근 3달 지출 및 소득 합계 평균 출력 함수 선언
void average_last_3_months(struct Account_Book expenses[], int expense_count,
                           struct Account_Book incomes[], int income_count);



void displayExpenses(struct Account_Book expenses[], int expense_count);  // 지출 내역 출력
void displayIncomes(struct Account_Book incomes[],int income_count);  // 소득 내역 출력
    //-----------------------------------main함수-----------------------------------------
int main() {
  int choice = -1;    // 사용자 입력 메뉴를 저장하기 위한 변수
  int terminate = 0;  // 종료를 위한 변수
  int selected_year = 0;   // 사용자가 입력한 특정 년도
  int selected_month = 0;  // 사용자가 입력한 특정 월
  
  loadAccounts(expenses, incomes, &expense_count, &income_count, //파일 불러오기
               "account_list.txt");
  displayExpenses(expenses,  expense_count); //지출 출력
  displayIncomes(incomes, income_count);    //소득 출력
  while (!terminate) {
    printf("\n\n******가계부******\n");
    printf("------------------\n");
    printf("메뉴를 입력해주세요.\n");
    printf(
        "1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 수정\n4. 특정 달의 내역 "
        "확인\n5. 소비 평가 출력 후 종료\n");
    printf("------------------\n");

    scanf_s("%d", &choice);

    switch (choice) {
      case 1:  // 지출 입력 및 저장
        input_Expense(expenses);
        break;
      case 2:  // 소득 입력 및 저장
        input_Income(incomes);
        break;
      case 3:  // 지출 및 소득내역을 수정
        modify_list(expenses, incomes);
        break;
      case 4:  // 특정 월소득 및 지출 확인
        display_list(&selected_year, &selected_month, expenses, incomes,
                     expense_count, income_count);
        break;
      case 5:  // 종료 및 소비평가 출력
        printSummary(expenses, expense_count, incomes, income_count);
        compare_last_month(expenses, expense_count, incomes, income_count);
        average_last_3_months(expenses, expense_count, incomes, income_count);
        terminate = 1;
        break;

      default:
        printf("올바른 메뉴를 선택해주세요.\n");
        break;
    }
  }
  saveAccount(expenses, expense_count, incomes, income_count);  // 파일 저장
  return 0;
}

//----------------------------------------함수정의-------------------------------------

void input_Expense(struct Account_Book expenses[]) {  // 지출 입력을 위한 함수 정의
  printf("저장할 날짜를 입력하세요(YY MM DD): ");
  scanf_s("%d %d %d", &expenses[expense_count].year,
          &expenses[expense_count].month, &expenses[expense_count].day);

  printf("지출 내역을 입력하세요: ");
  scanf_s("%19s", expenses[expense_count].description, 20);

  printf("지출 금액을 입력하세요: ");
  scanf_s("%f", &expenses[expense_count].amount);

  expense_count++;
  printf("%d년 %d월 %d일에 내역이 저장되었습니다.\n",
         expenses[expense_count - 1].year, expenses[expense_count - 1].month,
         expenses[expense_count - 1].day);
}

void input_Income(struct Account_Book incomes[]) {  // 소득 입력을 위한 함수
                                                    // 정의
  printf("저장할 날짜를 입력하세요(YY MM DD): ");
  scanf_s("%d %d %d", &incomes[income_count].year, &incomes[income_count].month,
          &incomes[income_count].day);

  printf("소득 내역을 입력하세요: ");
  scanf_s("%19s", incomes[income_count].description, 20);

  printf("소득 금액을 입력하세요: ");
  scanf_s("%f", &incomes[income_count].amount);

  income_count++;
  printf("%d년 %d월 %d일에 내역이 저장되었습니다.\n",
         incomes[income_count - 1].year, incomes[income_count - 1].month,
         incomes[income_count - 1].day);
}

void modify_list(struct Account_Book expenses[],  // 지출, 소득 내역 수정 함수 정의
    struct Account_Book incomes[]) {
  int choice;
  printf("수정할 내역을 선택하세요:\n");
  printf("1. 지출 내역 수정\n");
  printf("2. 소득 내역 수정\n");
  printf("3. 돌아가기\n");
  scanf_s("%d", &choice);

  switch (choice) {
    case 1:
      modify_Expense(expenses);  // 지출을 수정
      break;
    case 2:
      modify_Income(incomes);  // 소득을 수정
      break;
    case 3:
      printf("돌아갑니다.\n");
      break;
    default:
      printf("올바른 메뉴를 선택하세요.\n");
      break;
  }
}

void modify_Expense(struct Account_Book expenses[]) {  // 지출 수정 함수 정의
  int input_year, input_month, input_day;
  printf("수정할 날짜를 입력하세요(YY MM DD): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  for (int i = 0; i < expense_count; i++) {
    if (expenses[i].year == input_year && expenses[i].month == input_month &&
        expenses[i].day == input_day) {
      printf("수정할 지출 내역을 선택하세요: ");
      printf("%d월 %d일 - %s, %.f원\n", expenses[i].month, expenses[i].day,
             expenses[i].description, expenses[i].amount);

      printf("새로운 지출 내역을 입력하세요: ");
      scanf_s("%s19", expenses[i].description, sizeof(expenses[i].description));

      printf("수정된 지출 금액을 입력하세요: ");
      scanf_s("%f", &expenses[i].amount);

      printf("%d년 %d월 %d일의 지출 내역이 수정되었습니다.\n", input_year,
             input_month, input_day);
      return;
    }
  }
  printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", input_year, input_month,
         input_day);
}

void modify_Income(struct Account_Book incomes[]) {  // 소득 수정 함수 정의
  int input_year, input_month, input_day;
  printf("수정할 날짜를 입력하세요(YY MM DD): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  for (int i = 0; i < income_count; i++) {
    if (incomes[i].year == input_year && incomes[i].month == input_month &&
        incomes[i].day == input_day) {
      printf("수정할 소득 내역을 선택하세요: ");
      printf("%d월 %d일 - %s, %.f원\n", incomes[i].month, incomes[i].day,
             incomes[i].description, incomes[i].amount);

      printf("새로운 소득 내역을 입력하세요: ");
      scanf_s("%s19", incomes[i].description, sizeof(incomes[i].description));

      printf("수정된 소득 금액을 입력하세요: ");
      scanf_s("%f", &incomes[i].amount);

      printf("%d년 %d월 %d일의 소득 내역이 수정되었습니다.\n", input_year,
             input_month, input_day);
      return;
    }
  }
  printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", input_year, input_month,
         input_day);
}

//특정 달의 지출 및 소득 내역 출력해주는 함수 정의
void display_list(int *year, int *month, struct Account_Book expenses[],
                  struct Account_Book incomes[], int expense_count,
                  int income_count) {
  printf("년도와 월을 입력하세요 (YY MM): ");
  scanf_s("%d %d", year, month);
  printf("%d년 %d월의 내역을 출력합니다.\n", *year, *month);

  printf("\n지출 내역:\n");
  for (int i = 0; i < expense_count; i++) {
    if (expenses[i].year == *year && expenses[i].month == *month) {
      printf("%d월 %d일: %s - %.f원\n", expenses[i].month, expenses[i].day,
             expenses[i].description, expenses[i].amount);
    }
  }

  printf("\n소득 내역:\n");
  for (int i = 0; i < income_count; i++) {
    if (incomes[i].year == *year && incomes[i].month == *month) {
      printf("%d월 %d일: %s - %.f원\n", incomes[i].month, incomes[i].day,
             incomes[i].description, incomes[i].amount);
    }
  }

  calculateTotal(expenses, incomes, expense_count, income_count, *year, *month);
}


// 종료 시 이번 달 지출 및 소득 총합 출력 함수 정의
void printSummary(struct Account_Book expenses[], int expense_count,
                  struct Account_Book incomes[], int income_count) {
  int currentYear = 0, currentMonth = 0;  // 현재 년도와 월을 저장할 변수

  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth);

  float currentMonthExpense = 0.0, currentMonthIncome = 0.0;

  for (int i = 0; i < expense_count; ++i) {  // 지출에서 이번 달을 계산
    if (expenses[i].year == currentYear && expenses[i].month == currentMonth) {
      currentMonthExpense += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {  // 소득에서 이번 달을 계산
    if (incomes[i].year == currentYear && incomes[i].month == currentMonth) {
      currentMonthIncome += incomes[i].amount;
    }
  }

  printf("\n\n%d년 %d월의 지출 합: %.f원\n", currentYear, currentMonth,
         currentMonthExpense);
  printf("\n%d년 %d월의 소득 합: %.f원\n", currentYear, currentMonth,
         currentMonthIncome);
}

// 종료 시 이번 달 지출, 소득과 저번 달 지출, 소득 비율 증감 출력 함수 정의
void compare_last_month(struct Account_Book expenses[], int expense_count,
                        struct Account_Book incomes[], int income_count) {
  int currentYear = 0, currentMonth = 0;  // 현재 년도와 월을 저장할 변수
  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth);

  float last_month_expenses = 0, last_month_incomes = 0;
  for (int i = 0; i < expense_count; ++i) {  // 지출에서 저번 달을 계산
    if (expenses[i].year == currentYear &&
        expenses[i].month == currentMonth - 1) {
      last_month_expenses += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {  // 소득에서 저번 달을 계산
    if (incomes[i].year == currentYear &&
        incomes[i].month == currentMonth - 1) {
      last_month_incomes += incomes[i].amount;
    }
  }

  float this_month_expenses = 0, this_month_incomes = 0;
  for (int i = 0; i < expense_count; ++i) {  // 지출에서 이번 달을 계산
    if (expenses[i].year == currentYear && expenses[i].month == currentMonth) {
      this_month_expenses += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {  // 소득에서 이번 달을 계산
    if (incomes[i].year == currentYear && incomes[i].month == currentMonth) {
      this_month_incomes += incomes[i].amount;
    }
  }

  float expense_ratio = this_month_expenses / last_month_expenses;
  float income_ratio = this_month_incomes / last_month_incomes;

  printf("\n\n저번 달 대비 지출 증감율('1'= 동일): %.2f\n", expense_ratio);
  printf("\n저번 달 대비 소득 증감율('1'= 동일) : %.2f\n", income_ratio);
  printf("\n\n남은 잔액 : %.f\n\n", this_month_incomes - this_month_expenses);
}

// 종료 시 최근 3달 지출 및 소득 합계 평균 출력 함수 선언
void average_last_3_months(struct Account_Book expenses[], int expense_count,
                           struct Account_Book incomes[], int income_count) {
  int currentYear = 0, currentMonth = 0;  // 현재 년도와 월을 저장할 변수
  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth);  // 현재 날짜 계산

  float total_expenses = 0, total_incomes = 0;
  int count_expenses = 0, count_incomes = 0;

  for (int i = 0; i < expense_count; ++i) {  // 지출에서 최근 3달을 계산
    if ((expenses[i].year == currentYear &&
         expenses[i].month == currentMonth - 1) ||
        (expenses[i].year == currentYear &&
         expenses[i].month == currentMonth - 2) ||
        (expenses[i].year == currentYear &&
         expenses[i].month == currentMonth - 3)) {
      total_expenses += expenses[i].amount;
      count_expenses++;
    }
  }

  for (int i = 0; i < income_count; ++i) {  // 소득에서 최근 3달을 계산
    if ((incomes[i].year == currentYear &&
         incomes[i].month == currentMonth - 1) ||
        (incomes[i].year == currentYear &&
         incomes[i].month == currentMonth - 2) ||
        (incomes[i].year == currentYear &&
         incomes[i].month == currentMonth - 3)) {
      total_incomes += incomes[i].amount;
      count_incomes++;
    }
  }

  float avg_expenses = total_expenses / 3;
  float avg_incomes = total_incomes / 3;

  printf("\n최근 3개월 평균 지출: %.f\n", avg_expenses);
  printf("\n최근 3개월 평균 소득: %.f\n", avg_incomes);
}


//불러온 파일 내용 출력하는 함수 선언
void displayExpenses(struct Account_Book expenses[], int expense_count) {
  printf("\n\n지출 내역:\n");
  for (int i = 0; i < expense_count; i++) {
    printf("%d년 %d월 %d일: %s - %.f원\n", expenses[i].year, expenses[i].month,
           expenses[i].day, expenses[i].description, expenses[i].amount);
  }
}
 void displayIncomes(struct Account_Book incomes[], int income_count) {
  printf("\n\n소득 내역:\n");
  for (int i = 0; i < income_count; i++) {
    printf("%d년 %d월 %d일: %s - %.f원\n", incomes[i].year, incomes[i].month,
           incomes[i].day, incomes[i].description, incomes[i].amount);
  }
}
