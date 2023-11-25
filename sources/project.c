#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define GOODS 100             // �� ����
#define PRICE 100             // ������ ����
#define EARN 100              // ���� ��
#define YEAR 30                // �⵵
#define MONTH 12              // ��
#define DAY 31                // ��
#define INCOME_CATEGORIES 4   // �ҵ� �׸�
#define EXPENSE_CATEGORIES 6  // �Һ� �׸�

char account_book[3];  // �����

float calendar[YEAR][MONTH][DAY];  // ��¥ �����ϴ� �迭

char income_types[INCOME_CATEGORIES][20] =  // �ҵ��׸��� �����ϴ� �迭
    {"�Ϲ�", "���ڸ�", "Ŀ��", "�ܽ� �� ���"};

char expense_types[EXPENSE_CATEGORIES][20] =  // �Һ��׸��� �����ϴ� �迭
    {"���ڸ�", "���", "Ŀ��", "�ܽ� �� ���", "��Ȱ��ǰ", "��"};

float incomes[GOODS][EARN];    // �ҵ泻��
float expenses[GOODS][PRICE];  // ���⳻��
int year, month, day;          // ��, ��, �� ���� ����

void input_Expense(float expenses[GOODS][PRICE], // ���� �Է��� ���� �Լ� ����
                   char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],    // �ҵ� �Է��� ���� �Լ� ����
                  char income_types[INCOME_CATEGORIES][20]);


// ���� �� �ҵ� ������ ���� �Լ� ����
// �� �Լ��� ȣ��� �� �Ʒ��� �� �Լ��� �� �Լ� �ȿ��� ȣ��� ����
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                 char expense_types[EXPENSE_CATEGORIES][20],
                 char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],   // ���� ������ ���� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]);

void modify_Income(float incomes[GOODS][EARN],      // �ҵ� ������ ���� �Լ� ����
                   char income_types[INCOME_CATEGORIES][20]);

void display_list(int year, int month);  // Ư�� ���� �ҵ�� ���� ������ ����ϴ� �Լ� ����

void initialize_calendar(float calendar[YEAR][MONTH][DAY]);

void printSummary(
    float expenses[GOODS][PRICE],  // ���� �� �̹� �� ����, �ҵ� ���� �Լ� ����
    float incomes[GOODS][EARN], int currentYear, int currentMonth);

int main() {
  int choice = -1;  // ����� �Է� �޴��� �����ϱ� ���� ����
  int terminate = 0;
  float totalExpenses = 0.0; // �Һ����� ���� ����
  float totalIncomes = 0.0; // �ҵ� ���� ���� ����

  initialize_calendar(calendar);  // Ķ���� �ʱ�ȭ

  while (!terminate) {
    printf("------------------\n");
    printf("�޴��� �Է����ּ���.\n");
    printf(
        "1. ���� �Է�\n2. �ҵ� �Է�\n3. ���� �� �ҵ� ���� ����\n4."
        " Ư�� ���ҵ� �� ���� Ȯ��\n5. ����\n");
    printf("------------------\n");

    scanf_s("%d", &choice);

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
      case 5:  //���� �� �Һ��� ���
        terminate = 1;
        break;

      default:
        printf("�ùٸ� �޴��� �������ּ���.\n");
        break;
    }

    if (terminate == 1) { //����� �̹� �� ����, �Һ� ���� ���
      printSummary(expenses, incomes, year, month);
      printf("���Ḧ �����ϼ̽��ϴ�. ���α׷��� �����մϴ�.\n");
      break;
     
    }
  }
  return 0;
}

void initialize_calendar(float calendar[YEAR][MONTH][DAY]) {  //�޷� �ʱ�ȭ �Լ� ����
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
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year > 0 && input_year <= YEAR && input_month > 0 &&
      input_month <= MONTH && input_day > 0 && input_day <= DAY) {
    calendar[input_year - 1][input_month - 1][input_day - 1] = 1.0;

    // ���� ������ ��¥ ����
    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("��ȿ���� ���� ��¥�Դϴ�.\n");
    return;
  }

  int count = 0;  // �Է��� ���� ���� ����

  char temp_expenses[20]; //���ڿ��� �迭�� �����ϱ� ���� �ӽ� ����

  for (int i = 0; i < GOODS; i++) {
    printf("���� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
    scanf_s("%19s", expense_types[i], 20);

    if (expense_types[i][0] == '1') {
      printf("'1'�� �Է��ϼ̽��ϴ�. ���� �Է��� �����մϴ�.\n");
      break;
    }

    printf("���� ������ �Է��ϼ���: ");
    scanf_s("%19s", temp_expenses, 20);  // ���ڿ��� �ӽ� �迭�� ����

    strcpy_s(expense_types[i], sizeof(expense_types[i]), temp_expenses);

    printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
    scanf_s("%f", &expenses[i][1]);

    count++;
  }
  printf("%d�� %d�� %d�Ͽ� %d���� ������ ����Ǿ����ϴ�.\n", year, month, day,
         count);
}


void input_Income(float incomes[GOODS][EARN],   //�ҵ� �Է��� ���� �Լ� ����
                  char income_types[INCOME_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (input_year > 0 && input_year <= YEAR && input_month > 0 &&
      input_month <= MONTH && input_day > 0 && input_day <= DAY) {
    calendar[input_year - 1][input_month - 1][input_day - 1] = 1.0;

    year = input_year;
    month = input_month;
    day = input_day;
  } else {
    printf("��ȿ���� ���� ��¥�Դϴ�.\n");
    return;
  }

  char temp_incomes[20];  // ���ڿ��� �迭�� �����ϱ� ���� �ӽ� ����

  int count = 0;
  for (int i = 0; i < GOODS; i++) {
    printf("�ҵ� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
    scanf_s("%19s", income_types[i], 20);

    if (income_types[i][0] == '1') {
      printf("'1'�� �Է��ϼ̽��ϴ�. �ҵ� �Է��� �����մϴ�.\n");
      break;
    }

    printf("�ҵ� ������ �Է��ϼ���: ");
    scanf_s("%19s", temp_incomes, 20);  // ���ڿ��� �ӽ� �迭�� ����

    strcpy_s(income_types[i], sizeof(income_types[i]), temp_incomes);  

    printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
    scanf_s("%f", &incomes[i][1]);

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
  scanf_s("%d", &choice);

  switch (choice) {
    case 1:
      modify_Expense(expenses, expense_types); // ������ ����
      break;
    case 2:
      modify_Income(incomes, income_types);   //�ҵ��� ����
      break;
    case 3:
      printf("���ư��ϴ�.\n");
      break;
    default:
      printf("�ùٸ� �޴��� �����ϼ���.\n");
      break;
  }
}

void modify_Expense(float expenses[GOODS][PRICE],  //���� ���� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]) {
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year - 1][input_month - 1][input_day - 1] == 1.0) {
    int modify_index;
    printf("������ ���� �׸��� �����ϼ��� (0���� ����): ");
    scanf_s("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("������ ���� �׸��� �Է��ϼ���: ");
      scanf_s("%s", expense_types[modify_index], 20);

      printf("������ ���� ������ �Է��ϼ���: ");
      scanf_s("%s", expenses[modify_index][0], 20);

      printf("������ ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &expenses[modify_index][1]);

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
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  if (calendar[input_year - 1][input_month - 1][input_day - 1] == 1.0) {
    int modify_index;
    printf("������ �ҵ� �׸��� �����ϼ��� (0���� ����): ");
    scanf_s("%d", &modify_index);

    if (modify_index >= 0 && modify_index < GOODS) {
      printf("������ �ҵ� �׸��� �Է��ϼ���: ");
      scanf_s("%s", income_types[modify_index], 20);

      printf("������ �ҵ� ������ �Է��ϼ���: ");
      scanf_s("%s", incomes[modify_index][0], 20);

      printf("������ ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &incomes[modify_index][1]);

      printf("%d�� %d�� %d���� ������ �����Ǿ����ϴ�.\n", input_year,
             input_month, input_day);
      return;
    } else {
      printf("�ùٸ� �ҵ� �׸� �ε����� �����ϼ���.\n");
    }
  } else {
    printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", input_year,
           input_month, input_day);
  }
}

void display_list(int year, int month) {  //Ư�� �� �ҵ�, ���� ���� Ȯ�� �Լ� ����
  printf("%d�� %d���� ������ ����մϴ�.\n", year, month);

  printf("���� ����:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year - 1][month - 1][i] == 1.0) {
      char temp_show[20];  // ���ڿ��� ������ �迭
      sprintf(temp_show, "%.2f",expenses[i][0]);  
      printf("%s: %.2f��\n", temp_show, expenses[i][1]);

    }
  }

  printf("�ҵ� ����:\n");
  for (int i = 0; i < GOODS; i++) {
    if (calendar[year - 1][month - 1][i] == 1.0) {
      char temp_show[20];  // ���ڿ��� ������ �迭
      sprintf(temp_show, "%.2f", incomes[i][0]);
      printf("%s: %.2f��\n", temp_show, incomes[i][1]);
    }
  }
}

void printSummary(float expenses[GOODS][PRICE], //���� �� �̹� �� ���� �� �ҵ� ���� ��� �Լ� ����
                             float incomes[GOODS][EARN], int currentYear,
                             int currentMonth) {
  float currentMonthExpense = 0.0, currentMonthIncome = 0.0;

  // ���� ���� ����� �ҵ� ���� ���ϱ�
  for (int i = 0; i < GOODS; i++) {
    if (calendar[currentYear - 1][currentMonth - 1][i] == 1.0) {
      currentMonthExpense += expenses[i][1];
      currentMonthIncome += incomes[i][1];
    }
  }

  printf("%d�� %d���� ���� ��: %.2f��\n", currentYear, currentMonth,
         currentMonthExpense);
  printf("%d�� %d���� �ҵ� ��: %.2f��\n", currentYear, currentMonth,
         currentMonthIncome);
}
