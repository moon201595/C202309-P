#include <stdio.h>
#define GOODS 200 // 산 물건
#define PRICE 200 // 물건의 가격
#define EARN  100 // 얻은 돈
#define YEAR  5 // 년도
#define MONTH 12 // 월
#define DAY   31 // 일
#define INCOME_CATEGORIES 4 // 소득 항목
#define EXPENSE_CATEGORIES 6  //소비 항목


// 만들어야 할 기능!!!!
//--------------------------------------------------------------------------------------------
// 지출 입력, 소득 입력, 내역 수정, 원하는 월 소비, 소득 확인 (함수화)
// 프로그램 종료 시 소비 평가(이번 달 지출 및 소득 합계, 저번 달과 비교, 최근 3달 평균과 비교)
// 메모장에 입력한 값 모두 저장 및 프로그램 시작 시 메모장에 있는 값 불러오기
//--------------------------------------------------------------------------------------------

void input_Expense(float expenses[GOODS][PRICE],               //지출 입력을 위한 함수 선언
                  char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],                  //소득 입력을 위한 함수 선언
                 char income_types[INCOME_CATEGORIES][20]);


// main--------------------------------------------------------------------------------------------

int main() 
  {
    char account_book[3]; // 가계부
    
     float calendar[YEAR][MONTH][DAY]; // 날짜 저장하는 배열
    
    char income_types[INCOME_CATEGORIES][20] =   // 소득항목을 저장하는 배열
    {   "일반", "술자리", "커피", "외식 및 배달"};  
    
    char expense_types[EXPENSE_CATEGORIES][20] = // 소비항목을 저장하는 배열
    {   "술자리", "담배", "커피",
        "외식 및 배달", "생활용품", "옷"}; 
    

    float incomes[GOODS][EARN]; //소득내역
    float expenses[GOODS][PRICE]; //지출내역
    
    int choice = -1;  // 사용자 입력 메뉴를 저장하기 위한 변수,
                      // 동작이 안됐을 때를 확인하기 위해 해놓은것(동작할 때의값과 전혀 다른 값으로)
    
    int terminate = 0;  // 종료를 위한 변수
    
    //while문----------------------------------------------------------------------------------------

	while (!terminate) {
       // 사용자에게 메뉴를 출력하고, 메뉴를 입력받기
      printf("------------------\n");
      printf("메뉴를 입력해주세요.\n");
      printf("1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 내역 수정\n4. 특정 월 소득 및 소비 확인\n");
      // 수정: 메뉴 선택이 아닌 프로그램을 종료할 때 자동으로 이번 달 소비 평가 출력
      // -> 지출 및 소득 합계, 저번 달과 비교, 최근 3달 평균과 비교


      printf("------------------\n");
      scanf_s("%d", &choice);

      // switch문---------------------------------------------------------------------------------------
      
      // 사용자의 입력에 따른 기능 수행
      switch (choice) {
        case 1:  // 지출 입력 및 저장
          input_Expense(expenses, expense_types);
          break;

        case 2:  // 소득 입력 및 저장
          input_Income(incomes, income_types);
          break;

        case 3:
          // 수정
          break;

        case 4:
          // 수정
          break;

        default:
          printf("올바른 메뉴를 선택해주세요.\n");
          break;
      }
    }
}

// 함수-------------------------------------------------------------------------------------------


void input_Expense(float expenses[GOODS][PRICE],             //지출 입력을 위한 함수
                  char expense_types[EXPENSE_CATEGORIES][20]) {
    printf("저장할 날짜를 입력하세요(년 월 일): ");
    int year;
    int month;
    int day;
    scanf_s("%d %d %d", &year, &month, &day);

    for (int i = 0; i < GOODS; i++) {
      printf("지출 항목을 입력하세요(1 입력 시 종료): ");
      scanf_s("%s", expense_types[i], 20);

      if (expense_types[i][0] == '1') {
        printf("'1'을 입력하셨습니다. 지출 입력을 종료합니다.\n");
        break;
      }

      printf("지출 내역을 입력하세요: ");
      scanf_s("%s", (char)expenses[i][0]);

      printf("해당 내역의 금액을 입력하세요: ");
      scanf_s("%f", &expenses[0][i]);
    }

    printf("내용이 저장되었습니다.\n");
}

void input_Income(float incomes[GOODS][EARN],              //소득 입력을 위한 함수
                 char income_types[INCOME_CATEGORIES][20]) {
    printf("저장할 날짜를 입력하세요(년 월 일): ");
    int year;
    int month;
    int day;
    scanf_s("%d %d %d", &year, &month, &day);

    for (int i = 0; i < GOODS; i++) {
      printf("소득 항목을 입력하세요(1 입력 시 종료): ");
      scanf_s("%s", income_types[i], 20);

      if (income_types[i][0] == '1') {
        printf("'1'을 입력하셨습니다. 소득 입력을 종료합니다.\n");
        break;
      }

      printf("소득 내역을 입력하세요: ");
      scanf_s("%s", (char)incomes[i][0]);

      printf("해당 내역의 금액을 입력하세요: ");
      scanf_s("%f", &incomes[0][i]);
    }

    printf("내용이 저장되었습니다.\n");
}