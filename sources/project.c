#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define GOODS 100             // 산 물건
#define PRICE 100             // 물건의 가격
#define EARN 100              // 얻은 돈
#define YEAR 30                // 년도
#define MONTH 12              // 월
#define DAY 31                // 일
#define INCOME_CATEGORIES 4   // 소득 항목
#define EXPENSE_CATEGORIES 6  // 소비 항목

char account_book[3];  // 가계부

float calendar[YEAR][MONTH][DAY];  // 날짜 저장하는 배열

char income_types[INCOME_CATEGORIES][20] =  // 소득항목을 저장하는 배열
    {"일반", "술자리", "커피", "외식 및 배달"};

char expense_types[EXPENSE_CATEGORIES][20] =  // 소비항목을 저장하는 배열
    {"술자리", "담배", "커피", "외식 및 배달", "생활용품", "옷"};

float incomes[GOODS][EARN];    // 소득내역
float expenses[GOODS][PRICE];  // 지출내역
int year, month, day;          // 년, 월, 일 저장 변수

void input_Expense(float expenses[GOODS][PRICE], // 지출 입력을 위한 함수 선언
                   char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],    // 소득 입력을 위한 함수 선언
                  char income_types[INCOME_CATEGORIES][20]);


// 지출 및 소득 수정을 위한 함수 선언
// 이 함수가 호출될 때 아래의 두 함수가 이 함수 안에서 호출될 예정
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],   // 지출 수정을 위한 함수 선언
                    char expense_types[EXPENSE_CATEGORIES][20]);

void modify_Income(float incomes[GOODS][EARN],      // 소득 수정을 위한 함수 선언
                   char income_types[INCOME_CATEGORIES][20]);

void display_list(int year, int month);  // 특정 월의 소득과 지출 내역을 출력하는 함수 선언

void initialize_calendar(float calendar[YEAR][MONTH][DAY]);

void printSummary(
    float expenses[GOODS][PRICE],  // 종료 시 이번 달 지출, 소득 총합 함수 선언
    float incomes[GOODS][EARN], int currentYear, int currentMonth);

int main() {
  int choice = -1;  // 사용자 입력 메뉴를 저장하기 위한 변수
  int terminate = 0;
  float totalExpenses = 0.0; // 소비총합 저장 변수
  float totalIncomes = 0.0; // 소득 총합 저장 변수

  initialize_calendar(calendar);  // 캘린더 초기화

  while (!terminate) {
    printf("------------------\n");
    printf("메뉴를 입력해주세요.\n");
    printf(
        "1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 내역 수정\n4."
        " 특정 월소득 및 지출 확인\n5. 종료\n");
    printf("------------------\n");

    scanf_s("%d", &choice);

    switch (choice) {
      case 1:  // 지출 입력 및 저장
        input_Expense(expenses, expense_types);
        break;
      case 2:  // 소득 입력 및 저장
        input_Income(incomes, income_types);
        break;
      case 3:  // 지출 및 소득내역을 수정
        modify_list(expenses, incomes, expense_types, income_types);
        break;
      case 4:  //특정 월소득 및 지출 확인
        display_list(year, month);
        break;
      case 5:  //종료 및 소비평가 출력
        terminate = 1;
        break;

      default:
        printf("올바른 메뉴를 선택해주세요.\n");
        break;
    }

    if (terminate == 1) { //종료시 이번 달 지출, 소비 총합 출력
      printSummary(expenses, incomes, year, month);
      printf("종료를 선택하셨습니다. 프로그램을 종료합니다.\n");
      break;
     
    }
  }
  return 0;
}

void initialize_calendar(float calendar[YEAR][MONTH][DAY]) {  //달력 초기화 함수 정의
  for (int y = 0; y < YEAR; y++) {
    for (int m = 0; m < MONTH; m++) {
      for (int d = 0; d < DAY; d++) {
        calendar[y][m][d] = 0.0;  // 0으로 초기화
      }
    }
  }
}

void input_Expense(float expenses[GOODS][PRICE],   //지출 입력을 위한 함수정의
                   char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("저장할 날짜를 입력하세요(년 월 일): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year > 0 && input_year <= YEAR && input_month > 0 &&
      input_month <= MONTH && input_day > 0 && input_day <= DAY) {
    calendar[input_year - 1][input_month - 1][input_day - 1] = 1.0;

    // 전역 변수에 날짜 저장
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("유효하지 않은 날짜입니다.\n");
    return;
  }

  int count = 0;  // 입력한 개수 저장 변수

  char temp_expenses[20]; //문자열을 배열에 저장하기 위한 임시 변수

  for (int i = 0; i < GOODS; i++) {
    printf("지출 항목을 입력하세요(1 입력 시 종료): ");
    scanf_s("%19s", expense_types[i], 20);

    if (expense_types[i][0] == '1') {
      printf("'1'을 입력하셨습니다. 지출 입력을 종료합니다.\n");
      break;
    }

    printf("지출 내역을 입력하세요: ");
    scanf_s("%19s", temp_expenses, 20);  // 문자열을 임시 배열에 저장

    strcpy_s(expense_types[i], sizeof(expense_types[i]), temp_expenses);

    printf("해당 내역의 금액을 입력하세요: ");
    scanf_s("%f", &expenses[i][1]);

    count++;
  }
  printf("%d년 %d월 %d일에 %d개의 내용이 저장되었습니다.\n", year, month, day,
         count);
}


void input_Income(float incomes[GOODS][EARN],   //소득 입력을 위한 함수 정의
                  char income_types[INCOME_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("저장할 날짜를 입력하세요(년 월 일): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year > 0 && input_year <= YEAR && input_month > 0 &&
      input_month <= MONTH && input_day > 0 && input_day <= DAY) {
    calendar[input_year - 1][input_month - 1][input_day - 1] = 1.0;

    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("유효하지 않은 날짜입니다.\n");
    return;
  }

  char temp_incomes[20];  // 문자열을 배열에 저장하기 위한 임시 변수

  int count = 0;
  for (int i = 0; i < GOODS; i++) {
    printf("소득 항목을 입력하세요(1 입력 시 종료): ");
    scanf_s("%19s", income_types[i], 20);

    if (income_types[i][0] == '1') {
      printf("'1'을 입력하셨습니다. 소득 입력을 종료합니다.\n");
      break;
    }

    printf("소득 내역을 입력하세요: ");
    scanf_s("%19s", temp_incomes, 20);  // 문자열을 임시 배열에 저장

    strcpy_s(income_types[i], sizeof(income_types[i]), temp_incomes);  

    printf("해당 내역의 금액을 입력하세요: ");
    scanf_s("%f", &incomes[i][1]);

    count++;
  }

  printf("%d년 %d월 %d일에 %d개의 내용이 저장되었습니다.\n", year, month, day,
         count);
}

// 지출 , 소득 내역 수정 함수 정의
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]) {
  printf("수정할 내역을 선택하세요:\n");
  printf("1. 지출 내역 수정\n");
  printf("2. 소득 내역 수정\n");
  printf("3. 돌아가기\n");

  int choice;
  scanf_s("%d", &choice);

  switch (choice) {
    case 1:
      modify_Expense(expenses, expense_types); // 지출을 수정
      break;
    case 2:
      modify_Income(incomes, income_types);   //소득을 수정
      break;
    case 3:
      printf("돌아갑니다.\n");
      break;
    default:
      printf("올바른 메뉴를 선택하세요.\n");
      break;
  }
}

void modify_Expense(float expenses[GOODS][PRICE],  //지출 수정 함수 정의
                    char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("수정할 날짜를 입력하세요(년 월 일): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year - 1][input_month - 1][input_day - 1] == 1.0) {
    int modify_index;
    printf("수정할 지출 항목을 선택하세요 (0부터 시작): ");
    scanf_s("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("수정할 지출 항목을 입력하세요: ");
      scanf_s("%s", expense_types[modify_index], 20);

      printf("수정할 지출 내역을 입력하세요: ");
      scanf_s("%s", expenses[modify_index][0], 20);

      printf("수정할 내역의 금액을 입력하세요: ");
      scanf_s("%f", &expenses[modify_index][1]);

      printf("%d년 %d월 %d일의 내용이 수정되었습니다.\n", input_year,
             input_month, input_day);
      return;
    } else {
      printf("올바른 지출 항목 인덱스를 선택하세요.\n");
    }
  } else {
    printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", input_year,
           input_month, input_day);
  }
}

void modify_Income(float incomes[GOODS][EARN],  //소득 수정 함수 정의
                   char income_types[INCOME_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("수정할 날짜를 입력하세요(년 월 일): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year - 1][input_month - 1][input_day - 1] == 1.0) {
    int modify_index;
    printf("수정할 소득 항목을 선택하세요 (0부터 시작): ");
    scanf_s("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("수정할 소득 항목을 입력하세요: ");
      scanf_s("%s", income_types[modify_index], 20);

      printf("수정할 소득 내역을 입력하세요: ");
      scanf_s("%s", incomes[modify_index][0], 20);

      printf("수정할 내역의 금액을 입력하세요: ");
      scanf_s("%f", &incomes[modify_index][1]);

      printf("%d년 %d월 %d일의 내용이 수정되었습니다.\n", input_year,
             input_month, input_day);
      return;
    } else {
      printf("올바른 소득 항목 인덱스를 선택하세요.\n");
    }
  } else {
    printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", input_year,
           input_month, input_day);
  }
}

void display_list(int year, int month) {  //특정 월 소득, 지출 내역 확인 함수 정의
  printf("%d년 %d월의 내역을 출력합니다.\n", year, month);

  printf("지출 내역:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year - 1][month - 1][i] == 1.0) {
      char temp_show[20];  // 문자열을 저장할 배열
      sprintf(temp_show, "%.2f",expenses[i][0]);  
      printf("%s: %.2f원\n", temp_show, expenses[i][1]);

    }
  }

  printf("소득 내역:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year - 1][month - 1][i] == 1.0) {
      char temp_show[20];  // 문자열을 저장할 배열
      sprintf(temp_show, "%.2f", incomes[i][0]);
      printf("%s: %.2f원\n", temp_show, incomes[i][1]);
    }
  }
}

void printSummary(float expenses[GOODS][PRICE], //종료 시 이번 달 지출 및 소득 총합 출력 함수 정의
                             float incomes[GOODS][EARN], int currentYear,
                             int currentMonth) {
  float currentMonthExpense = 0.0, currentMonthIncome = 0.0;

  // 현재 달의 지출과 소득 총합 구하기
  for (int i = 0; i < GOODS; i++) {
    if (calendar[currentYear - 1][currentMonth - 1][i] == 1.0) {
      currentMonthExpense += expenses[i][1];
      currentMonthIncome += incomes[i][1];
    }
  }

  printf("%d년 %d월의 지출 합: %.2f원\n", currentYear, currentMonth,
         currentMonthExpense);
  printf("%d년 %d월의 소득 합: %.2f원\n", currentYear, currentMonth,
         currentMonthIncome);
}
