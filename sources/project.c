#include <stdio.h>
#include <stdlib.h>
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
// 지출 입력, 소득 입력, 내역 수정, 원하는 월의 소비, 소득 확인 (함수화) <<완료>> -> scanf_s는 수정!!!!!!!!
// 프로그램 종료 시 소비 평가(이번 달 지출 및 소득 합계, 저번 달과 비교, 최근 3달 평균과 비교)
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

void input_Expense(float expenses[GOODS][PRICE],               //지출 입력을 위한 함수 선언
                  char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],                  //소득 입력을 위한 함수 선언
                 char income_types[INCOME_CATEGORIES][20]);


// 지출 및 소득 수정을 위한 함수 선언
// 이 함수가 호출될 때 아래의 두 함수가 이 함수 안에서 호출될 예정
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                    char expense_types[EXPENSE_CATEGORIES][20],
                    char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],                 // 지출 수정을 위한 함수 선언
                    char expense_types[EXPENSE_CATEGORIES][20]);


void modify_Income(float incomes[GOODS][EARN],                    // 소득 수정을 위한 함수 선언
                   char income_types[INCOME_CATEGORIES][20]);

void display_list(int year, int month);                 // 특정 월의 소득과 지출 내역을 출력하는 함수 선언




//main--------------------------------------------------------------------------------------------

int main() 
  {
    
    int choice = -1;  // 사용자 입력 메뉴를 저장하기 위한 변수,
                      // 동작이 안됐을 때를 확인하기 위해 해놓은것(동작할 때의값과 전혀 다른 값으로)
    
    int terminate = 0;  // 종료를 위한 변수

	while (!terminate) {
       // 사용자에게 메뉴를 출력하고, 메뉴를 입력받기
      printf("------------------\n");
      printf("메뉴를 입력해주세요.\n");
      printf("1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 내역 수정\n4. 특정 월 소득 및 지출 확인\n5. 종료\n");
      // 수정: 메뉴 선택이 아닌 프로그램을 종료할 때 자동으로 이번 달 소비 평가 출력
      // -> 지출 및 소득 합계, 저번 달과 비교, 최근 3달 평균과 비교

      printf("------------------\n");
      scanf_s("%d", &choice);

      // 사용자의 입력에 따른 기능 수행
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
          

        case 4:  //특정 월 지출 및 소득 확인
          display_list(year, month); 
          break;
        
        case 5: 
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

//----------------------------------------함수 정의-------------------------------------------------------


void input_Expense(float expenses[GOODS][PRICE],             //지출 입력을 위한 함수정의
                  char expense_types[EXPENSE_CATEGORIES][20]) {
    printf("저장할 날짜를 입력하세요(년 월 일): ");
    scanf_s("%d %d %d", &year, &month, &day); 
    calendar[year][month][day] = 1.0;

    for (int i = 0; i < GOODS; i++) {
      printf("지출 항목을 입력하세요(1 입력 시 종료): ");
      scanf_s("%s", expense_types[i], 20);

      if (expense_types[i][0] == '1') {
        printf("'1'을 입력하셨습니다. 지출 입력을 종료합니다.\n");
        break;
      }

      printf("지출 내역을 입력하세요: ");
      scanf_s("%s", (char)expenses[i][0], 20);  // 포인터??

      printf("해당 내역의 금액을 입력하세요: ");
      scanf_s("%f", &expenses[i][1]);
    }
    printf("%d년 %d월 %d일에 내용이 저장되었습니다.\n", year, month, day);
}



void input_Income(float incomes[GOODS][EARN],              //소득 입력을 위한 함수 정의
                 char income_types[INCOME_CATEGORIES][20]) {
    printf("저장할 날짜를 입력하세요(년 월 일): ");
    scanf_s("%d %d %d", &year, &month, &day);        
    calendar[year][month][day] = 1.0;


    for (int i = 0; i < GOODS; i++) {
      printf("소득 항목을 입력하세요(1 입력 시 종료): ");
      scanf_s("%s", income_types[i], 20);

      if (income_types[i][0] == '1') {
        printf("'1'을 입력하셨습니다. 소득 입력을 종료합니다.\n");
        break;
      }

      printf("소득 내역을 입력하세요: ");
      scanf_s("%s", (char)incomes[i][0], 20);        

      printf("해당 내역의 금액을 입력하세요: ");
      scanf_s("%f", &incomes[i][1]);
    }

     printf("%d년 %d월 %d일에 내용이 저장되었습니다.\n", year, month, day);
}



// 소득 및 지출 내역 수정 함수 정의
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
        modify_Expense(expenses, expense_types);  //지출내역 수정하는 함수 호출
        break;
      case 2:
        modify_Income(incomes, income_types);    //소득내역 수정하는 함수 호출
        break;
      case 3:
        printf("돌아갑니다.\n");
        break;
      default:
        printf("올바른 메뉴를 선택하세요.\n");
        break;
     }
}




void modify_Expense(float expenses[GOODS][PRICE],  //지출내역 수정하는 함수 정의
                    char expense_types[EXPENSE_CATEGORIES][20]) {
    
     printf("수정할 날짜를 입력하세요(년 월 일): ");
     scanf_s("%d %d %d", &year, &month, &day);

     // 해당 날짜의 내역을 찾아 수정
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][day] == 1.0) {
        printf("수정할 지출 항목을 입력하세요: ");
        scanf_s("%s", expense_types[i], 20);

        printf("수정할 지출 내역을 입력하세요: ");
        scanf_s("%s", (char)expenses[i][0], 20);

        printf("수정할 내역의 금액을 입력하세요: ");
        scanf_s("%f", &expenses[i][1]);

        printf("%d년 %d월 %d일의 내용이 수정되었습니다.\n", year, month, day);
        return;
      }
     }
     printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", year, month, day);
}

void modify_Income(float incomes[GOODS][EARN],   //소득내역 수정하는 함수 정의
                   char income_types[INCOME_CATEGORIES][20]) {
     
     printf("수정할 날짜를 입력하세요(년 월 일): ");
     scanf_s("%d %d %d", &year, &month, &day);

     // 해당 날짜의 내역을 찾아 수정
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][day] == 1.0) {
        printf("수정할 소득 항목을 입력하세요: ");
        scanf_s("%s", income_types[i], 20);

        printf("수정할 소득 내역을 입력하세요: ");
        scanf_s("%s", (char)incomes[i][0], 20);

        printf("수정할 내역의 금액을 입력하세요: ");
        scanf_s("%f", &incomes[i][1]);

        printf("%d년 %d월 %d일의 내용이 수정되었습니다.\n", year, month, day);
        return;
      }
     }
     printf("%d년 %d월 %d일에 저장된 내역이 없습니다.\n", year, month, day);
}

void display_list(int year, int month) {   //특정 월의 지출과 소득 내역 출력 함수 정의
     
     printf("%d년 %d월의 내역을 출력합니다.\n", year, month);

     // 해당 월의 지출 내역 출력
     printf("지출 내역:\n");
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][i] == 1.0) {
        printf("%s: %.2f원\n", (char)expenses[i][0], expenses[i][1]);
      }
     }

     // 해당 월의 소득 내역 출력
     printf("소득 내역:\n");
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][i] == 1.0) {
        printf("%s: %.2f원\n", (char)incomes[i][0], incomes[i][1]);
      }
     }
}