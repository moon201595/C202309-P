#include <stdio.h>
#include <stdlib.h>
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
// ���� �Է�, �ҵ� �Է�, ���� ����, ���ϴ� ���� �Һ�, �ҵ� Ȯ�� (�Լ�ȭ) <<�Ϸ�>> -> scanf_s�� ����!!!!!!!!
// ���α׷� ���� �� �Һ� ��(�̹� �� ���� �� �ҵ� �հ�, ���� �ް� ��, �ֱ� 3�� ��հ� ��)
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

void input_Expense(float expenses[GOODS][PRICE],               //���� �Է��� ���� �Լ� ����
                  char expense_types[EXPENSE_CATEGORIES][20]);

void input_Income(float incomes[GOODS][EARN],                  //�ҵ� �Է��� ���� �Լ� ����
                 char income_types[INCOME_CATEGORIES][20]);


// ���� �� �ҵ� ������ ���� �Լ� ����
// �� �Լ��� ȣ��� �� �Ʒ��� �� �Լ��� �� �Լ� �ȿ��� ȣ��� ����
void modify_list(float expenses[GOODS][PRICE], float incomes[GOODS][EARN],
                    char expense_types[EXPENSE_CATEGORIES][20],
                    char income_types[INCOME_CATEGORIES][20]);

void modify_Expense(float expenses[GOODS][PRICE],                 // ���� ������ ���� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]);


void modify_Income(float incomes[GOODS][EARN],                    // �ҵ� ������ ���� �Լ� ����
                   char income_types[INCOME_CATEGORIES][20]);

void display_list(int year, int month);                 // Ư�� ���� �ҵ�� ���� ������ ����ϴ� �Լ� ����




//main--------------------------------------------------------------------------------------------

int main() 
  {
    
    int choice = -1;  // ����� �Է� �޴��� �����ϱ� ���� ����,
                      // ������ �ȵ��� ���� Ȯ���ϱ� ���� �س�����(������ ���ǰ��� ���� �ٸ� ������)
    
    int terminate = 0;  // ���Ḧ ���� ����

	while (!terminate) {
       // ����ڿ��� �޴��� ����ϰ�, �޴��� �Է¹ޱ�
      printf("------------------\n");
      printf("�޴��� �Է����ּ���.\n");
      printf("1. ���� �Է�\n2. �ҵ� �Է�\n3. ���� �� �ҵ� ���� ����\n4. Ư�� �� �ҵ� �� ���� Ȯ��\n5. ����\n");
      // ����: �޴� ������ �ƴ� ���α׷��� ������ �� �ڵ����� �̹� �� �Һ� �� ���
      // -> ���� �� �ҵ� �հ�, ���� �ް� ��, �ֱ� 3�� ��հ� ��

      printf("------------------\n");
      scanf_s("%d", &choice);

      // ������� �Է¿� ���� ��� ����
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
          

        case 4:  //Ư�� �� ���� �� �ҵ� Ȯ��
          display_list(year, month); 
          break;
        
        case 5: 
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

//----------------------------------------�Լ� ����-------------------------------------------------------


void input_Expense(float expenses[GOODS][PRICE],             //���� �Է��� ���� �Լ�����
                  char expense_types[EXPENSE_CATEGORIES][20]) {
    printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
    scanf_s("%d %d %d", &year, &month, &day); 
    calendar[year][month][day] = 1.0;

    for (int i = 0; i < GOODS; i++) {
      printf("���� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
      scanf_s("%s", expense_types[i], 20);

      if (expense_types[i][0] == '1') {
        printf("'1'�� �Է��ϼ̽��ϴ�. ���� �Է��� �����մϴ�.\n");
        break;
      }

      printf("���� ������ �Է��ϼ���: ");
      scanf_s("%s", (char)expenses[i][0], 20);  // ������??

      printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &expenses[i][1]);
    }
    printf("%d�� %d�� %d�Ͽ� ������ ����Ǿ����ϴ�.\n", year, month, day);
}



void input_Income(float incomes[GOODS][EARN],              //�ҵ� �Է��� ���� �Լ� ����
                 char income_types[INCOME_CATEGORIES][20]) {
    printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
    scanf_s("%d %d %d", &year, &month, &day);        
    calendar[year][month][day] = 1.0;


    for (int i = 0; i < GOODS; i++) {
      printf("�ҵ� �׸��� �Է��ϼ���(1 �Է� �� ����): ");
      scanf_s("%s", income_types[i], 20);

      if (income_types[i][0] == '1') {
        printf("'1'�� �Է��ϼ̽��ϴ�. �ҵ� �Է��� �����մϴ�.\n");
        break;
      }

      printf("�ҵ� ������ �Է��ϼ���: ");
      scanf_s("%s", (char)incomes[i][0], 20);        

      printf("�ش� ������ �ݾ��� �Է��ϼ���: ");
      scanf_s("%f", &incomes[i][1]);
    }

     printf("%d�� %d�� %d�Ͽ� ������ ����Ǿ����ϴ�.\n", year, month, day);
}



// �ҵ� �� ���� ���� ���� �Լ� ����
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
        modify_Expense(expenses, expense_types);  //���⳻�� �����ϴ� �Լ� ȣ��
        break;
      case 2:
        modify_Income(incomes, income_types);    //�ҵ泻�� �����ϴ� �Լ� ȣ��
        break;
      case 3:
        printf("���ư��ϴ�.\n");
        break;
      default:
        printf("�ùٸ� �޴��� �����ϼ���.\n");
        break;
     }
}




void modify_Expense(float expenses[GOODS][PRICE],  //���⳻�� �����ϴ� �Լ� ����
                    char expense_types[EXPENSE_CATEGORIES][20]) {
    
     printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
     scanf_s("%d %d %d", &year, &month, &day);

     // �ش� ��¥�� ������ ã�� ����
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][day] == 1.0) {
        printf("������ ���� �׸��� �Է��ϼ���: ");
        scanf_s("%s", expense_types[i], 20);

        printf("������ ���� ������ �Է��ϼ���: ");
        scanf_s("%s", (char)expenses[i][0], 20);

        printf("������ ������ �ݾ��� �Է��ϼ���: ");
        scanf_s("%f", &expenses[i][1]);

        printf("%d�� %d�� %d���� ������ �����Ǿ����ϴ�.\n", year, month, day);
        return;
      }
     }
     printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", year, month, day);
}

void modify_Income(float incomes[GOODS][EARN],   //�ҵ泻�� �����ϴ� �Լ� ����
                   char income_types[INCOME_CATEGORIES][20]) {
     
     printf("������ ��¥�� �Է��ϼ���(�� �� ��): ");
     scanf_s("%d %d %d", &year, &month, &day);

     // �ش� ��¥�� ������ ã�� ����
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][day] == 1.0) {
        printf("������ �ҵ� �׸��� �Է��ϼ���: ");
        scanf_s("%s", income_types[i], 20);

        printf("������ �ҵ� ������ �Է��ϼ���: ");
        scanf_s("%s", (char)incomes[i][0], 20);

        printf("������ ������ �ݾ��� �Է��ϼ���: ");
        scanf_s("%f", &incomes[i][1]);

        printf("%d�� %d�� %d���� ������ �����Ǿ����ϴ�.\n", year, month, day);
        return;
      }
     }
     printf("%d�� %d�� %d�Ͽ� ����� ������ �����ϴ�.\n", year, month, day);
}

void display_list(int year, int month) {   //Ư�� ���� ����� �ҵ� ���� ��� �Լ� ����
     
     printf("%d�� %d���� ������ ����մϴ�.\n", year, month);

     // �ش� ���� ���� ���� ���
     printf("���� ����:\n");
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][i] == 1.0) {
        printf("%s: %.2f��\n", (char)expenses[i][0], expenses[i][1]);
      }
     }

     // �ش� ���� �ҵ� ���� ���
     printf("�ҵ� ����:\n");
     for (int i = 0; i < GOODS; i++) {
      if (calendar[year][month][i] == 1.0) {
        printf("%s: %.2f��\n", (char)incomes[i][0], incomes[i][1]);
      }
     }
}