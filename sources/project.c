#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define GOODS 200             // 산 물건
#define PRICE 200             // 물건의 가격
#define EARN 100              // 얻은 돈
#define YEAR 5                // 년도
#define MONTH 12              // 월
#define DAY 31                // 일
#define INCOME_CATEGORIES 4   // 소득 항목
#define EXPENSE_CATEGORIES 6  // 소비 항목


// 만들어야 할 기능!!!!
//--------------------------------------------------------------------------------------------
// 지출 입력, 소득 입력, 내역 수정, 원하는 월의 소비, 소득 확인 (함수화)
// 종료 시 소비 평가(이번 달 지출 및소득 합계, 저번 달과 비교, 최근 3달 평균과 비교) 
// 메모장에 입력한 값 모두 저장 및 프로그램 시작 시 메모장에 있는 값 불러오기
//--------------------------------------------------------------------------------------------


char account_book[3];  // 가계부

float calendar[YEAR][MONTH][DAY];  // 날짜 저장하는 배열

char income_types[INCOME_CATEGORIES][20] =  // 소득항목을 저장하는 배열
    {"일반", "술자리", "커피", "외식 및 배달"};

char expense_types[EXPENSE_CATEGORIES][20] =  // 소비항목을 저장하는 배열
    {"술자리", "담배", "커피", "외식 및 배달", "생활용품", "옷"};


float incomes[GOODS][EARN];    // 소득내역
float expenses[GOODS][PRICE];  // 지출내역
int year, month, day;          // 년, 월, 일 저장 변수



void input_Expense(float expenses[GOODS][PRICE],  // 지출 입력을 위한 함수 선언
                   char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],  // 소득 입력을 위한 함수 선언
                  char income_types[INCOME_CATEGORIES][20]);


// 지출 및 소득 수정을 위한 함수 선언
// 이 함수가 호출될 때 아래의 두 함수가 이 함수 안에서 호출될 예정
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],  // 지출 수정을 위한 함수 선언
                    char expense_types[EXPENSE_CATEGORIES][20]);

void modify_Income(float incomes[GOODS][EARN],  // 소득 수정을 위한 함수 선언
                   char income_types[INCOME_CATEGORIES][20]);

// 특정 월의 소득과 지출 내역을 출력하는 함수 선언
void display_list(int year, int month);  


void initialize_calendar(float calendar[YEAR][MONTH][DAY]);


//------------------------------main 함수--------------------------------------


int main() {
  int choice = -1;  // 사용자 입력 메뉴를 저장하기 위한 변수,
                    // 동작이 안됐을 때를 확인하기 위해 해놓은것(동작할 때의값과
                    // 전혀 다른 값으로)

  int terminate = 0;  // 종료를 위한 변수

  initialize_calendar(calendar);  // 캘린더 초기화

  while (!terminate) {

    // 사용자에게 메뉴를 출력하고, 메뉴를 입력받기
    printf("------------------\n");
    printf("메뉴를 입력해주세요.\n");
    printf("1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 내역 수정\n4." 
        "특정 월소득 및 지출 확인\n5. 종료\n");
    printf("------------------\n");

    scanf("%d", &choice);

    //사용자 입력에 따른 기능 수행
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

      case 5:  //종료
        terminate = 1;
        break;

      default:
        printf("올바른 메뉴를 선택해주세요.\n");
        break;
    }

    if (terminate == 1) {
      printf("종료를 선택하셨습니다. 프로그램을 종료합니다.\n");
      break;
    }
  }
  return 0;
}

//-------------------------함수 정의----------------------------------------------

void initialize_calendar(float calendar[YEAR][MONTH][DAY]) { //달력 초기화
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
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year >= 0 && input_year < YEAR && input_month >= 0 &&
      input_month < MONTH && input_day >= 0 && input_day < DAY) {
    calendar[input_year][input_month][input_day] = 1.0;

    // 전역 변수에 날짜 저장
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("유효하지 않은 날짜입니다.\n");
    return;
  }

  int count = 0;  // 입력한 개수 저장 변수

  for (int i = 0; i < GOODS; i++) {
    printf("지출 항목을 입력하세요(1 입력 시 종료): ");
    scanf("%s", expense_types[i]);

    if (expense_types[i][0] == '1') {
      printf("'1'을 입력하셨습니다. 지출 입력을 종료합니다.\n");
      break;
    }

    printf("지출 내역을 입력하세요: ");
    scanf("%f", expenses[i][0]);  

    printf("해당 내역의 금액을 입력하세요: ");
    scanf("%f", &expenses[i][1]);

    count++;
  }
  printf("%d년 %d월 %d일에 %d개의 내용이 저장되었습니다.\n", year, month, day,
         count);
}


void input_Income(float incomes[GOODS][EARN],  //소득 입력을 위한 함수 정의
                  char income_types[INCOME_CATEGORIES][20]) {

  int input_year, input_month, input_day;
  printf("저장할 날짜를 입력하세요(년 월 일): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year >= 0 && input_year < YEAR && input_month >= 0 &&
      input_month < MONTH && input_day >= 0 && input_day < DAY) {
    calendar[input_year][input_month][input_day] = 1.0;

    //전역 변수에 날짜 저장
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("유효하지 않은 날짜입니다.\n");
    return;
  }

  int count = 0; // 입력한 개수 저장 변수

  for (int i = 0; i < GOODS; i++) {
    printf("소득 항목을 입력하세요(1 입력 시 종료): ");
    scanf("%s", income_types[i]);

    if (income_types[i][0] == '1') {
      printf("'1'을 입력하셨습니다. 소득 입력을 종료합니다.\n");
      break;
    }

    printf("소득 내역을 입력하세요: ");
    scanf("%s", incomes[i][0]);

    printf("해당 내역의 금액을 입력하세요: ");
    scanf("%f", &incomes[i][1]);

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
  scanf("%d", &choice);

  switch (choice) {
    case 1:  // 지출을 수정
      modify_Expense(expenses, expense_types); 
      break;
    case 2:  //소득을 수정
      modify_Income(incomes, income_types);
      break;
    case 3:
      printf("돌아갑니다.\n");
      break;
    default:
      printf("올바른 메뉴를 선택하세요.\n");
      break;
  }
}


void modify_Expense(float expenses[GOODS][PRICE], //지출 수정 함수 정의
                    char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("수정할 날짜를 입력하세요(년 월 일): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year][input_month][input_day] == 1.0) {

    int modify_index; //수정을 위한 변수

    printf("수정할 지출 항목을 선택하세요 (0부터 시작): ");
    scanf("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("수정할 지출 항목을 입력하세요: ");
      scanf("%s", expense_types[modify_index]);

      printf("수정할 지출 내역을 입력하세요: ");
      scanf("%s", expenses[modify_index][0]);

      printf("수정할 내역의 금액을 입력하세요: ");
      scanf("%f", &expenses[modify_index][1]);

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
  scanf("%d %d %d", &input_year, &input_month, &input_day);

 if (calendar[input_year][input_month][input_day] == 1.0) {

    int modify_index;  // 수정을 위한 변수

    printf("수정할 지출 항목을 선택하세요 (0부터 시작): ");
    scanf("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("수정할 지출 항목을 입력하세요: ");
      scanf("%s", income_types[modify_index]);

      printf("수정할 지출 내역을 입력하세요: ");
      scanf("%s", incomes[modify_index][0]);

      printf("수정할 내역의 금액을 입력하세요: ");
      scanf("%f", &incomes[modify_index][1]);

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


void display_list(int year, int month) { //특정 월 소득, 지출 내역 확인 함수 정의
  printf("%d년 %d월의 내역을 출력합니다.\n", year, month);

  printf("지출 내역:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year][month][i] == 1.0) {
      printf("%s: %.2f원\n", expenses[i][0], expenses[i][1]);
    }
  }

  printf("소득 내역:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year][month][i] == 1.0) {
      printf("%s: %.2f원\n", incomes[i][0], incomes[i][1]);
    }
  }
}