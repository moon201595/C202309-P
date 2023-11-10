#include <stdio.h>
#define GOODS 200 // �� ����
#define PRICE 200 // ������ ����
#define EARN  100 // ���� ��
#define YEAR  5 // �⵵
#define MONTH 12 // ��
#define DAY   31 // ��
#define INCOME_CATEGORIES 4 // �ҵ� �׸�
#define EXPENSE_CATEGORIES 6  //�Һ� �׸�


// ������ �� ���!!!!
//--------------------------------------------------------------------------------------------
// ���� �Է�, �ҵ� �Է�, ���� ����, ���ϴ� �� �Һ�, �ҵ� Ȯ�� (�Լ�ȭ)
// ���α׷� ���� �� �Һ� ��(�̹� �� ���� �� �ҵ� �հ�, ���� �ް� ��, �ֱ� 3�� ��հ� ��)
// �޸��忡 �Է��� �� ��� ���� �� ���α׷� ���� �� �޸��忡 �ִ� �� �ҷ�����
//--------------------------------------------------------------------------------------------

void input_Expense(float expenses[GOODS][PRICE],               //���� �Է��� ���� �Լ� ����
                  char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],                  //�ҵ� �Է��� ���� �Լ� ����
                 char income_types[INCOME_CATEGORIES][20]);


// main--------------------------------------------------------------------------------------------

int main() 
  {
    char account_book[3]; // �����
    
     float calendar[YEAR][MONTH][DAY]; // ��¥ �����ϴ� �迭
    
    char income_types[INCOME_CATEGORIES][20] =   // �ҵ��׸��� �����ϴ� �迭
    {   "�Ϲ�", "���ڸ�", "Ŀ��", "�ܽ� �� ���"};  
    
    char expense_types[EXPENSE_CATEGORIES][20] = // �Һ��׸��� �����ϴ� �迭
    {   "���ڸ�", "���", "Ŀ��",
        "�ܽ� �� ���", "��Ȱ��ǰ", "��"}; 
    

    float incomes[GOODS][EARN]; //�ҵ泻��
    float expenses[GOODS][PRICE]; //���⳻��
    
    int choice = -1;  // ����� �Է� �޴��� �����ϱ� ���� ����,
                      // ������ �ȵ��� ���� Ȯ���ϱ� ���� �س�����(������ ���ǰ��� ���� �ٸ� ������)
    
    int terminate = 0;  // ���Ḧ ���� ����
    
    //while��----------------------------------------------------------------------------------------

	while (!terminate) {
       // ����ڿ��� �޴��� ����ϰ�, �޴��� �Է¹ޱ�
      printf("------------------\n");
      printf("�޴��� �Է����ּ���.\n");
      printf("1. ���� �Է�\n2. �ҵ� �Է�\n3. ���� �� �ҵ� ���� ����\n4. Ư�� �� �ҵ� �� �Һ� Ȯ��\n");
      // ����: �޴� ������ �ƴ� ���α׷��� ������ �� �ڵ����� �̹� �� �Һ� �� ���
      // -> ���� �� �ҵ� �հ�, ���� �ް� ��, �ֱ� 3�� ��հ� ��


      printf("------------------\n");
      scanf_s("%d", &choice);

      // switch��---------------------------------------------------------------------------------------
      
      // ������� �Է¿� ���� ��� ����
      switch (choice) {
        case 1:  // ���� �Է� �� ����
          input_Expense(expenses, expense_types);
          break;

        case 2:  // �ҵ� �Է� �� ����
          input_Income(incomes, income_types);
          break;

        case 3:
          // ����
          break;

        case 4:
          // ����
          break;

        default:
          printf("�ùٸ� �޴��� �������ּ���.\n");
          break;
      }
    }
}

// �Լ�-------------------------------------------------------------------------------------------


void input_Expense(float expenses[GOODS][PRICE],             //���� �Է��� ���� �Լ�
                  char expense_types[EXPENSE_CATEGORIES][20]) {
    printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
    int year;
    int month;
    int day;
    scanf_s("%d %d %d", &year, &month, &day);

    for (int i = 0; i < GOODS; i++) {
      printf("���� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
      scanf_s("%s", expense_types[i], 20);

      if (expense_types[i][0] == '1') {
        printf("'1'�� �Է��ϼ̽��ϴ�. ���� �Է��� �����մϴ�.\n");
        break;
      }

      printf("���� ������ �Է��ϼ���: ");
      scanf_s("%s", (char)expenses[i][0]);

      printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &expenses[0][i]);
    }

    printf("������ ����Ǿ����ϴ�.\n");
}

void input_Income(float incomes[GOODS][EARN],              //�ҵ� �Է��� ���� �Լ�
                 char income_types[INCOME_CATEGORIES][20]) {
    printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
    int year;
    int month;
    int day;
    scanf_s("%d %d %d", &year, &month, &day);

    for (int i = 0; i < GOODS; i++) {
      printf("�ҵ� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
      scanf_s("%s", income_types[i], 20);

      if (income_types[i][0] == '1') {
        printf("'1'�� �Է��ϼ̽��ϴ�. �ҵ� �Է��� �����մϴ�.\n");
        break;
      }

      printf("�ҵ� ������ �Է��ϼ���: ");
      scanf_s("%s", (char)incomes[i][0]);

      printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &incomes[0][i]);
    }

    printf("������ ����Ǿ����ϴ�.\n");
}