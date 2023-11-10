#include <stdio.h>
#include <string.h>
#include <Windows.h>
int main() { 
	char years[10]; // 년도를 저장하는 배열
	char months[12][10] = {"1월", "2월", "3월", "4월",  "5월",  "6월",  //월을 저장
	  "7월", "8월", "9월", "10월", "11월", "12월"};

	
	char accounts; //소득과 소비를 저장하는 통장 역할 변수

	char incometypes[4][20] = {"일반", "술자리", "커피", "외식 및 배달"}; //소득항목을 저장하는 배열
    char expensetypes[6][20]= {"술자리","담배","커피","외식 및 배달", "생활용품", "옷"}; //소비항목을 저장하는 배열
    
    strcpy(accounts[incometypes,expensetypes]); // 항목을 통장 배열에 저장....
   
    float incomes; //소비내역
    float expenses; //지출내역
     
	while (1) {
                int choice = -1;  // 사용자 입력 메뉴를 저장하기 위한 변수,
                                  // 동작이 안됐을 때를 확인하기 위해 해놓은것(동작할 때의 값과 전혀 다른 값으로)
                                  
                // 사용자에게 메뉴를 출력하고, 메뉴를 입력받기
                printf("------------------\n");
                printf("메뉴를 입력해주세요.\n");
                printf( "1. 지출 입력\n2. 소득 입력\n3. 지출 및 소득 내역 수정\n4. 지출 및 잔액 확인\n5. 이번 달 소비 평가\n");
                printf("------------------\n");
                scanf_s("%d", &choice);




}


