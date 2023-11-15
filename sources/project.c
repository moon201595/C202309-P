#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define GOODS 200             // �� ����
#define PRICE 200             // ������ ����
#define EARN 100              // ���� ��
#define YEAR 5                // �⵵
#define MONTH 12              // ��
#define DAY 31                // ��
#define INCOME_CATEGORIES 4   // �ҵ� �׸�
#define EXPENSE_CATEGORIES 6  // �Һ� �׸�


// ������ �� ���!!!!
//--------------------------------------------------------------------------------------------
// ���� �Է�, �ҵ� �Է�, ���� ����, ���ϴ� ���� �Һ�, �ҵ� Ȯ�� (�Լ�ȭ)
// ���� �� �Һ� ��(�̹� �� ���� �׼ҵ� �հ�, ���� �ް� ��, �ֱ� 3�� ��հ� ��) 
// �޸��忡 �Է��� �� ��� ���� �� ���α׷� ���� �� �޸��忡 �ִ� �� �ҷ�����
//--------------------------------------------------------------------------------------------


char account_book[3];  // �����

float calendar[YEAR][MONTH][DAY];  // ��¥ �����ϴ� �迭

char income_types[INCOME_CATEGORIES][20] =  // �ҵ��׸��� �����ϴ� �迭
    {"�Ϲ�", "���ڸ�", "Ŀ��", "�ܽ� �� ���"};

char expense_types[EXPENSE_CATEGORIES][20] =  // �Һ��׸��� �����ϴ� �迭
    {"���ڸ�", "���", "Ŀ��", "�ܽ� �� ���", "��Ȱ��ǰ", "��"};


float incomes[GOODS][EARN];    // �ҵ泻��
float expenses[GOODS][PRICE];  // ���⳻��
int year, month, day;          // ��, ��, �� ���� ����



void input_Expense(float expenses[GOODS][PRICE],  // ���� �Է��� ���� �Լ� ����
                   char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],  // �ҵ� �Է��� ���� �Լ� ����
                  char income_types[INCOME_CATEGORIES][20]);


// ���� �� �ҵ� ������ ���� �Լ� ����
// �� �Լ��� ȣ��� �� �Ʒ��� �� �Լ��� �� �Լ� �ȿ��� ȣ��� ����
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],  // ���� ������ ���� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]);

void modify_Income(float incomes[GOODS][EARN],  // �ҵ� ������ ���� �Լ� ����
                   char income_types[INCOME_CATEGORIES][20]);

// Ư�� ���� �ҵ�� ���� ������ ����ϴ� �Լ� ����
void display_list(int year, int month);  


void initialize_calendar(float calendar[YEAR][MONTH][DAY]);


//------------------------------main �Լ�--------------------------------------


int main() {
  int choice = -1;  // ����� �Է� �޴��� �����ϱ� ���� ����,
                    // ������ �ȵ��� ���� Ȯ���ϱ� ���� �س�����(������ ���ǰ���
                    // ���� �ٸ� ������)

  int terminate = 0;  // ���Ḧ ���� ����

  initialize_calendar(calendar);  // Ķ���� �ʱ�ȭ

  while (!terminate) {

    // ����ڿ��� �޴��� ����ϰ�, �޴��� �Է¹ޱ�
    printf("------------------\n");
    printf("�޴��� �Է����ּ���.\n");
    printf("1. ���� �Է�\n2. �ҵ� �Է�\n3. ���� �� �ҵ� ���� ����\n4." 
        "Ư�� ���ҵ� �� ���� Ȯ��\n5. ����\n");
    printf("------------------\n");

    scanf("%d", &choice);

    //����� �Է¿� ���� ��� ����
    switch (choice) {  
      case 1:  // ���� �Է� �� ����
        input_Expense(expenses, expense_types);  
        break;

      case 2:  // �ҵ� �Է� �� ����
        input_Income(incomes, income_types);
        break;

      case 3:  // ���� �� �ҵ泻���� ����
        modify_list(expenses, incomes, expense_types, income_types);
        break;

      case 4:  //Ư�� ���ҵ� �� ���� Ȯ��
        display_list(year, month);
        break;

      case 5:  //����
        terminate = 1;
        break;

      default:
        printf("�ùٸ� �޴��� �������ּ���.\n");
        break;
    }

    if (terminate == 1) {
      printf("���Ḧ �����ϼ̽��ϴ�. ���α׷��� �����մϴ�.\n");
      break;
    }
  }
  return 0;
}

//-------------------------�Լ� ����----------------------------------------------

void initialize_calendar(float calendar[YEAR][MONTH][DAY]) { //�޷� �ʱ�ȭ
  for (int y = 0; y < YEAR; y++) {
    for (int m = 0; m < MONTH; m++) {
      for (int d = 0; d < DAY; d++) {
        calendar[y][m][d] = 0.0;  // 0���� �ʱ�ȭ
      }
    }
  }
}


void input_Expense(float expenses[GOODS][PRICE],   //���� �Է��� ���� �Լ�����
                   char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year >= 0 && input_year < YEAR && input_month >= 0 &&
      input_month < MONTH && input_day >= 0 && input_day < DAY) {
    calendar[input_year][input_month][input_day] = 1.0;

    // ���� ������ ��¥ ����
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("��ȿ���� ���� ��¥�Դϴ�.\n");
    return;
  }

  int count = 0;  // �Է��� ���� ���� ����

  for (int i = 0; i < GOODS; i++) {
    printf("���� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
    scanf("%s", expense_types[i]);

    if (expense_types[i][0] == '1') {
      printf("'1'�� �Է��ϼ̽��ϴ�. ���� �Է��� �����մϴ�.\n");
      break;
    }

    printf("���� ������ �Է��ϼ���: ");
    scanf("%f", expenses[i][0]);  

    printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
    scanf("%f", &expenses[i][1]);

    count++;
  }
  printf("%d�� %d�� %d�Ͽ� %d���� ������ ����Ǿ����ϴ�.\n", year, month, day,
         count);
}


void input_Income(float incomes[GOODS][EARN],  //�ҵ� �Է��� ���� �Լ� ����
                  char income_types[INCOME_CATEGORIES][20]) {

  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year >= 0 && input_year < YEAR && input_month >= 0 &&
      input_month < MONTH && input_day >= 0 && input_day < DAY) {
    calendar[input_year][input_month][input_day] = 1.0;

    //���� ������ ��¥ ����
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("��ȿ���� ���� ��¥�Դϴ�.\n");
    return;
  }

  int count = 0; // �Է��� ���� ���� ����

  for (int i = 0; i < GOODS; i++) {
    printf("�ҵ� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
    scanf("%s", income_types[i]);

    if (income_types[i][0] == '1') {
      printf("'1'�� �Է��ϼ̽��ϴ�. �ҵ� �Է��� �����մϴ�.\n");
      break;
    }

    printf("�ҵ� ������ �Է��ϼ���: ");
    scanf("%s", incomes[i][0]);

    printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
    scanf("%f", &incomes[i][1]);

    count++;
  }

  printf("%d�� %d�� %d�Ͽ� %d���� ������ ����Ǿ����ϴ�.\n", year, month, day,
         count);
}

// ���� , �ҵ� ���� ���� �Լ� ����
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN], 
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]) {
  printf("������ ������ �����ϼ���:\n");
  printf("1. ���� ���� ����\n");
  printf("2. �ҵ� ���� ����\n");
  printf("3. ���ư���\n");

  int choice;
  scanf("%d", &choice);

  switch (choice) {
    case 1:  // ������ ����
      modify_Expense(expenses, expense_types); 
      break;
    case 2:  //�ҵ��� ����
      modify_Income(incomes, income_types);
      break;
    case 3:
      printf("���ư��ϴ�.\n");
      break;
    default:
      printf("�ùٸ� �޴��� �����ϼ���.\n");
      break;
  }
}


void modify_Expense(float expenses[GOODS][PRICE], //���� ���� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year][input_month][input_day] == 1.0) {

    int modify_index; //������ ���� ����

    printf("������ ���� �׸��� �����ϼ��� (0���� ����): ");
    scanf("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("������ ���� �׸��� �Է��ϼ���: ");
      scanf("%s", expense_types[modify_index]);

      printf("������ ���� ������ �Է��ϼ���: ");
      scanf("%s", expenses[modify_index][0]);

      printf("������ ������ �ݾ��� �Է��ϼ���: ");
      scanf("%f", &expenses[modify_index][1]);

      printf("%d�� %d�� %d���� ������ �����Ǿ����ϴ�.\n", input_year,
             input_month, input_day);
      return;
    } else {
      printf("�ùٸ� ���� �׸� �ε����� �����ϼ���.\n");
    }
  } else {
    printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", input_year,
           input_month, input_day);
  }
}


void modify_Income(float incomes[GOODS][EARN],  //�ҵ� ���� �Լ� ����
                   char income_types[INCOME_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf("%d %d %d", &input_year, &input_month, &input_day);

 if (calendar[input_year][input_month][input_day] == 1.0) {

    int modify_index;  // ������ ���� ����

    printf("������ ���� �׸��� �����ϼ��� (0���� ����): ");
    scanf("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("������ ���� �׸��� �Է��ϼ���: ");
      scanf("%s", income_types[modify_index]);

      printf("������ ���� ������ �Է��ϼ���: ");
      scanf("%s", incomes[modify_index][0]);

      printf("������ ������ �ݾ��� �Է��ϼ���: ");
      scanf("%f", &incomes[modify_index][1]);

      printf("%d�� %d�� %d���� ������ �����Ǿ����ϴ�.\n", input_year,
             input_month, input_day);
      return;
    } else {
      printf("�ùٸ� ���� �׸� �ε����� �����ϼ���.\n");
    }
  } else {
    printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", input_year,
           input_month, input_day);
  }
}


void display_list(int year, int month) { //Ư�� �� �ҵ�, ���� ���� Ȯ�� �Լ� ����
  printf("%d�� %d���� ������ ����մϴ�.\n", year, month);

  printf("���� ����:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year][month][i] == 1.0) {
      printf("%s: %.2f��\n", expenses[i][0], expenses[i][1]);
    }
  }

  printf("�ҵ� ����:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year][month][i] == 1.0) {
      printf("%s: %.2f��\n", incomes[i][0], incomes[i][1]);
    }
  }
}