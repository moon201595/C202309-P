#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOODS 100  // �� ����

struct Account_Book {  // ��¥, ����, �ݾ��� ���� ����ü
  int year;
  int month;
  int day;
  char description[20];  // ����
  float amount;          // �ݾ�
};

struct Account_Book expenses[GOODS];  // ���� ������ ���� ����ü �迭
struct Account_Book incomes[GOODS];  // �ҵ� ������ ���� ����ü �迭
int expense_count = 0;               // �Էµ� ���� ������ ����
int income_count = 0;                // �Էµ� �ҵ� ������ ����

// --------------------------------------�Լ� ����--------------------------------------

void input_Expense(struct Account_Book expenses[]); // ���� �Է��� ���� �Լ� ����
void input_Income(struct Account_Book incomes[]); // �ҵ� �Է��� ���� �Լ� ����


// ���� �� �ҵ� ������ ���� �Լ� ����
// �� �Լ��� ȣ��� �� �Ʒ��� �� �Լ��� �� �Լ� �ȿ��� ȣ��� ����
void modify_list(struct Account_Book expenses[], struct Account_Book incomes[]);
void modify_Expense(struct Account_Book expenses[]); // ���� ������ ���� �Լ� ����
void modify_Income(struct Account_Book incomes[]); // �ҵ� ������ ���� �Լ� ����


void display_list(int year, int month);  // Ư�� ���� �ҵ�� ���� ���� ��� �Լ� ����
void calculateTotal(struct Account_Book expenses[],  // Ư�� ���� �ҵ�� ���� ���� ��� �Լ� ����
                    struct Account_Book incomes[],
                    int expense_count, int income_count, int year, int month);

void decideCurrent(  // ������ ����, �ҵ� �Է� ��¥�� ���� ��¥�� �ν��ϴ� �Լ� ����
                     // �Ʒ� �� �Լ��� ���
    struct Account_Book expenses[],  
    struct Account_Book incomes[], int expense_count, int income_count,
    int *currentYear, int *currentMonth);

// ���� �� �̹� �� ����, �ҵ� ���� �Լ� ����
void printSummary(struct Account_Book expenses[], int expense_count, 
                  struct Account_Book incomes[], int income_count);

// ���� �� �̹� �� ����, �ҵ�� ���� �� ����, �ҵ� ���� ���� ��� �Լ� ����
void compare_last_month(struct Account_Book expenses[],
                        struct Account_Book incomes[], int currentYear,
                           int currentMonth);

// ���� �� �ֱ� 3�� ���� �� �ҵ� �հ� ��� ��� �Լ� ����
void average_last_3_months(struct Account_Book expenses[],
                           struct Account_Book incomes[], int currentYear,
                           int currentMonth);


//-----------------------------------main �Լ�-----------------------------------------
int main() {
  int choice = -1;  // ����� �Է� �޴��� �����ϱ� ���� ����
  int terminate = 0; // ���Ḧ ���� ����

  while (!terminate) {
    printf("------------------\n");
    printf("�޴��� �Է����ּ���.\n");
    printf(
        "1. ���� �Է�\n2. �ҵ� �Է�\n3. ���� �� �ҵ� ����\n4. Ư�� ���� ���� "
        "Ȯ��\n5. ����\n");
    printf("------------------\n");

    scanf_s("%d", &choice);

    switch (choice) {
      case 1:  // ���� �Է� �� ����
        input_Expense(expenses);
        break;
      case 2: // �ҵ� �Է� �� ����
        input_Income(incomes);
        break;
      case 3:  // ���� �� �ҵ泻���� ����
        modify_list(expenses, incomes);
        break;
      case 4:  //Ư�� ���ҵ� �� ���� Ȯ��
        display_list(0, 0);
        break;
      case 5:  //���� �� �Һ��� ���
        printSummary(expenses, expense_count, incomes, income_count);
        compare_last_month(expenses, incomes, expense_count, income_count);
        average_last_3_months(expenses, incomes, expense_count, income_count);
        terminate = 1;
        break;

      default:
        printf("�ùٸ� �޴��� �������ּ���.\n");
        break;
    }
  }

  return 0;
}


//----------------------------------------�Լ� ����-------------------------------------

void input_Expense(struct Account_Book expenses[]) { //���� �Է��� ���� �Լ� ����
  printf("������ ��¥�� �Է��ϼ���(YY MM DD): ");
  scanf_s("%d %d %d", &expenses[expense_count].year,
          &expenses[expense_count].month, &expenses[expense_count].day);

  printf("���� ������ �Է��ϼ���: ");
  scanf_s("%19s", expenses[expense_count].description, 20);

  printf("���� �ݾ��� �Է��ϼ���: ");
  scanf_s("%f", &expenses[expense_count].amount);

  expense_count++;
  printf("%d�� %d�� %d�Ͽ� ������ ����Ǿ����ϴ�.\n",
         expenses[expense_count - 1].year, expenses[expense_count - 1].month,
         expenses[expense_count - 1].day);
}

void input_Income(struct Account_Book incomes[]) {  //�ҵ� �Է��� ���� �Լ� ����
  printf("������ ��¥�� �Է��ϼ���(YY MM DD): ");
  scanf_s("%d %d %d", &incomes[income_count].year, &incomes[income_count].month,
          &incomes[income_count].day);

  printf("�ҵ� ������ �Է��ϼ���: ");
  scanf_s("%19s", incomes[income_count].description, 20);

  printf("�ҵ� �ݾ��� �Է��ϼ���: ");
  scanf_s("%f", &incomes[income_count].amount);

  income_count++;
  printf("%d�� %d�� %d�Ͽ� ������ ����Ǿ����ϴ�.\n",
         incomes[income_count - 1].year, incomes[income_count - 1].month,
         incomes[income_count - 1].day);
}

void modify_list(struct Account_Book expenses[], // ����, �ҵ� ���� ���� �Լ� ����
                 struct Account_Book incomes[]) {
  int choice;
  printf("������ ������ �����ϼ���:\n");
  printf("1. ���� ���� ����\n");
  printf("2. �ҵ� ���� ����\n");
  printf("3. ���ư���\n");

  scanf_s("%d", &choice);

  switch (choice) {
    case 1:
      modify_Expense(expenses); // ������ ����
      break;
    case 2:
      modify_Income(incomes); // �ҵ��� ����
      break;
    case 3:
      printf("���ư��ϴ�.\n");
      break;
    default:
      printf("�ùٸ� �޴��� �����ϼ���.\n");
      break;
  }
}

void modify_Expense(struct Account_Book expenses[]) {  //���� ���� �Լ� ����
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(YY MM DD): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  for (int i = 0; i < expense_count; i++) {
    if (expenses[i].year == input_year && expenses[i].month == input_month &&
        expenses[i].day == input_day) {
      printf("������ ���� ������ �����ϼ���: ");
      printf("%d�� %d�� - %s, %.2f��\n", expenses[i].month, expenses[i].day,
             expenses[i].description, expenses[i].amount);

      printf("���ο� ���� ������ �Է��ϼ���: ");
      scanf_s("%s19", expenses[i].description, sizeof(expenses[i].description));

      printf("������ ���� �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &expenses[i].amount);

      printf("%d�� %d�� %d���� ���� ������ �����Ǿ����ϴ�.\n", input_year,
             input_month, input_day);
      return;
    }
  }
  printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", input_year, input_month,
         input_day);
}

void modify_Income(struct Account_Book incomes[]) {  //�ҵ� ���� �Լ� ����
  int input_year, input_month, input_day;
  printf("������ ��¥�� �Է��ϼ���(YY MM DD): ");
  scanf_s("%d %d %d", &input_year, &input_month, &input_day);

  for (int i = 0; i < income_count; i++) {
    if (incomes[i].year == input_year && incomes[i].month == input_month &&
        incomes[i].day == input_day) {
      printf("������ �ҵ� ������ �����ϼ���: ");
      printf("%d�� %d�� - %s, %.2f��\n", incomes[i].month, incomes[i].day,
             incomes[i].description, incomes[i].amount);

      printf("���ο� �ҵ� ������ �Է��ϼ���: ");
      scanf_s("%s19", incomes[i].description, sizeof(incomes[i].description));

      printf("������ �ҵ� �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &incomes[i].amount);

      printf("%d�� %d�� %d���� �ҵ� ������ �����Ǿ����ϴ�.\n", input_year,
             input_month, input_day);
      return;
    }
  }
  printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", input_year, input_month,
         input_day);
}

void display_list(int year, int month) {  //Ư�� �� �ҵ�, ���� ���� Ȯ�� �Լ� ����
  printf("�⵵�� ���� �Է��ϼ��� (YY MM): ");
  scanf_s("%d %d", &year, &month);
  printf("%d�� %d���� ������ ����մϴ�.\n", year, month);

  printf("���� ����:\n");
  for (int i = 0; i < expense_count; i++) {
    if (expenses[i].year == year && expenses[i].month == month) {
      printf("%d�� %d��: %s - %.2f��\n", expenses[i].month, expenses[i].day,
             expenses[i].description, expenses[i].amount);
    }
  }

  printf("���� ����:\n");
  for (int i = 0; i < income_count; i++) {
    if (incomes[i].year == year && incomes[i].month == month) {
      printf("%d�� %d��: %s - %.2f��\n", incomes[i].month, incomes[i].day,
             incomes[i].description, incomes[i].amount);
    }
  }

  calculateTotal(expenses, incomes, expense_count, income_count, year, month);
}

void calculateTotal(struct Account_Book expenses[], // Ư�� �� ����, �Һ� ���� ��� �Լ� ����
                    struct Account_Book incomes[],
                    int expense_count, int income_count, int year, int month) {
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

  printf("%d�� %d���� �� ����: %.2f��\n", year, month, totalExpenses);
  printf("%d�� %d���� �� ����: %.2f��\n", year, month, totalIncomes);
}

void decideCurrent(struct Account_Book expenses[], //������ ����, �ҵ� �Է� ��¥�� ���� ��¥�� �ν��ϰ� �ϴ� �Լ� ����
                   struct Account_Book incomes[],
                   int expense_count, int income_count, int *currentYear,
                   int *currentMonth) {
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

// ���� �� �̹� �� ���� �� �ҵ� ���� ��� �Լ� ����
void printSummary(struct Account_Book expenses[], int expense_count,
                  struct Account_Book incomes[], int income_count) {
  int currentYear = 0, currentMonth = 0;  // ���� �⵵�� ���� ������ ����

  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth);

  float currentMonthExpense = 0.0, currentMonthIncome = 0.0;

  for (int i = 0; i < expense_count; ++i) {   //���⿡�� �̹� ���� ���
    if (expenses[i].year == currentYear && expenses[i].month == currentMonth) {
      currentMonthExpense += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {  //�ҵ濡�� �̹� ���� ���
    if (incomes[i].year == currentYear && incomes[i].month == currentMonth) {
      currentMonthIncome += incomes[i].amount;
    }
  }

  printf("%d�� %d���� ���� ��: %.f��\n", currentYear, currentMonth,
         currentMonthExpense);
  printf("%d�� %d���� �ҵ� ��: %.f��\n", currentYear, currentMonth,
         currentMonthIncome);
}

// ���� �� �̹� �� ����, �ҵ�� ���� �� ����, �ҵ� ���� ���� ��� �Լ� ����
void compare_last_month(struct Account_Book expenses[],
                        struct Account_Book incomes[], int currentYear,
                        int currentMonth) {

  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth);

  float last_month_expenses = 0, last_month_incomes = 0;
  for (int i = 0; i < expense_count; ++i) { //���⿡�� ���� ���� ���
    if (expenses[i].year == currentYear &&
        expenses[i].month == currentMonth - 1) {
      last_month_expenses += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) {  //�ҵ濡�� ���� ���� ���
    if (incomes[i].year == currentYear &&
        incomes[i].month == currentMonth - 1) {
      last_month_incomes += incomes[i].amount;
    }
  }

  float this_month_expenses = 0, this_month_incomes = 0;
  for (int i = 0; i < expense_count; ++i) {  //���⿡�� �̹� ���� ���
    if (expenses[i].year == currentYear && expenses[i].month == currentMonth) {
      this_month_expenses += expenses[i].amount;
    }
  }

  for (int i = 0; i < income_count; ++i) { //�ҵ濡�� �̹� ���� ���
    if (incomes[i].year == currentYear && incomes[i].month == currentMonth) {
      this_month_incomes += incomes[i].amount;
    }
  }

  float expense_ratio = this_month_expenses / last_month_expenses;
  float income_ratio = this_month_incomes / last_month_incomes;

  printf("���� �޿� ���� ������ %.2f �����߰�, �ҵ��� %.2f �����߽��ϴ�.\n",
         expense_ratio, income_ratio);
}

// ���� �� �ֱ� 3�� ���� �� �ҵ� �հ� ��� ��� �Լ� ����
void average_last_3_months(struct Account_Book expenses[],
                           struct Account_Book incomes[], int currentYear,
                           int currentMonth) {

  decideCurrent(expenses, incomes, expense_count, income_count, &currentYear,
                &currentMonth); // ���� ��¥ ��� 

  float total_expenses = 0, total_incomes = 0;
  int count_expenses = 0, count_incomes = 0;

  for (int i = 0; i < expense_count; ++i) {  // ���⿡�� �ֱ� 3���� ���
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

  for (int i = 0; i < income_count; ++i) {  // �ҵ濡�� �ֱ� 3���� ���
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

  printf("�ֱ� 3���� ��� ����: %.2f, ��� �ҵ�: %.2f\n", avg_expenses,
         avg_incomes);
}