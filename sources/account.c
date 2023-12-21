#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

#define GOODS 100  // �� ����

struct Account_Book {  // ��¥, ����, �ݾ��� ���� ����ü
  int year;
  int month;
  int day;
  char description[50];  // ����
  float amount;          // �ݾ�
};
struct Account_Book expenses[GOODS];  // ���� ������ ���� ����ü �迭
struct Account_Book incomes[GOODS];  // �ҵ� ������ ���� ����ü �迭


// �� ���� �� �ҵ� ������ִ� �Լ� ����
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

  printf("\n\n%d�� %d���� �� ����: %.f��\n\n", year, month, totalExpenses);
  printf("\n\n%d�� %d���� �� �ҵ�: %.f��\n\n", year, month, totalIncomes);
}


void decideCurrent( // ������ ����, �ҵ� �Է� ��¥�� ���� ��¥�� �ν��ϰ� �ϴ� �Լ� ����      
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

// ������ account_list �޸��忡 �����ϴ� �Լ� ����
void saveAccount(struct Account_Book expenses[], int expense_count,
                 struct Account_Book incomes[], int income_count) {
  FILE *file;
  fopen_s(&file, "account_list.txt", "w");  // ���� ����
  // �ҷ��� ���ϵ��� ���� �� �޸��忡 �ٽ� ����Ǳ� ������ ����� ������� ����

  if (file != NULL) {
    if (expense_count > 0 ||
        income_count > 0) {  // �����̳� �ҵ��� ���� ���� ���Ͽ� ����
      fprintf(file, "Expense list:\n");  // ���� ���� ����
      for (int i = 0; i < expense_count; ++i) {
        fprintf(file, "%d�� %d�� %d�� - %s, %.f��\n", expenses[i].year,
                expenses[i].month, expenses[i].day, expenses[i].description,
                expenses[i].amount);
      }

      fprintf(file, "\nIncome list:\n");  // �ҵ� ���� ����
      for (int i = 0; i < income_count; ++i) {
        fprintf(file, "%d�� %d�� %d�� - %s, %.f��\n", incomes[i].year,
                incomes[i].month, incomes[i].day, incomes[i].description,
                incomes[i].amount);
      }
      printf("\n���Ͽ� �����͸� �߰��� �����߽��ϴ�.\n");
    } else {
      printf("\n�����͸� �Է����� �ʾ� ���Ͽ� ������ �������� �ʽ��ϴ�.\n");
    }
    fclose(file);
  } else {
    printf("������ ������ �� �����ϴ�.\n");
  }
}

// ������ account_list �޸��忡�� �ҷ����� �Լ� ����
void loadAccounts(struct Account_Book expenses[], struct Account_Book incomes[],
                  int *expense_count, int *income_count, const char *fileName) {
  FILE *file;
  fopen_s(&file, fileName, "r");  // ���� ���� (�б� ���)

  if (file != NULL) {
    char buffer[100];
    int is_expense = 0;  // ���Ͽ��� ����� �ҵ��� �����ϱ� ���� ����

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      int year, month, day;
      char description[50];
      float amount;

      if (strstr(buffer, "Expense list:") != NULL) {
        is_expense = 1;  // 'Expense list'�� �߰��ϸ� ����� �ν�
      } else if (strstr(buffer, "Income list:") != NULL) {
        is_expense = 0;  // 'Income list'�� �߰��ϸ� �ҵ����� �ν�
      }

      if (is_expense) {  // ������ ���
        if (sscanf(buffer, "%d�� %d�� %d�� - %49[^,], %f��\n", &year, &month,
                   &day, description, &amount) == 5) {
          expenses[*expense_count].year = year;
          expenses[*expense_count].month = month;
          expenses[*expense_count].day = day;
          strcpy_s(expenses[*expense_count].description,
                   sizeof(expenses[*expense_count].description), description);
          expenses[*expense_count].amount = amount;
          (*expense_count)++;
        }
      } else {  // �ҵ��� ���
        if (sscanf(buffer, "%d�� %d�� %d�� - %49[^,], %f��\n", &year, &month,
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
    printf("������ �� �� �����ϴ�.\n");
  }
}

