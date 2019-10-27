#include<stdio.h>
#include<malloc.h>


typedef struct Node{
	char op;
	struct Node* link;
}node;

void s_Dis();
void check(char letter);
void cal(char letter);
void push(int p_OP);
int pop();
char top_node();
int cmp(char letter); //������ ������ ������ �Լ�
int change(char letter);	//���ڸ� ������ ������� �Լ�

node* top = NULL;
char postfix_ex[50];	//����ǥ��� ��ȯ�� ������ ���� ����
int position;  //������� ó���� ������ �ε����� ���� ����

int main() {
	char user_ex[50];  //����ڷκ��� �Է´��� ������ ������ ���� 
	printf("--------------------------------------------------\n");
	printf("�� �Է� : ");
	scanf_s("%s", user_ex, 50);

	printf("\n����->����\n");
	for (int i = 0; user_ex[i]; ++i) {
		printf("string : %s\n", user_ex + i + 1);
		printf("position : %c\n", user_ex[i]);
		check(user_ex[i]);
		s_Dis();
		printf("���� : %s\n\n", postfix_ex);
	}
	while (top_node() != '\0') {	//����ǥ�Ⱑ ������ stack�� �����ִ� �����ڵ� pop 
		postfix_ex[position] = pop();
		position++;
	}

	for (int j = 0; postfix_ex[j]; ++j) {
		cal(postfix_ex[j]);
	}

	printf("�Էµ� ���� ����ǥ�� ���� %s�Դϴ�.\n", postfix_ex);
	printf("�Էµ� ���� ���� %d�Դϴ�.\n", pop());
	return 0;
}

void s_Dis() {
	printf("stack : ");
	node* t;
	for (t = top; t; t=t->link) {
		printf("%c ", t->op);
	}
	printf("\n");
}

int change(char letter) {
	int num = letter - '0';
	return num;
}

void cal(char letter) {
	int push_data=change(letter);
	int tmpA, tmpB;
	if (letter == '+' || letter == '-' || letter == '*' || letter == '/') {
		tmpB = pop();
		tmpA = pop();
		if (letter == '+')
			push_data = tmpA + tmpB;
		else if (letter == '-')
			push_data = tmpA - tmpB;
		else if (letter == '*')
			push_data = tmpA * tmpB;
		else if (letter == '/')
			push_data = tmpA / tmpB;
	}
	push(push_data);
}

void check(char letter) {	//�ش� ���ڰ� �������� ���������� Ȯ���Ͽ� �´� ��Ʈ�� �����ִ� �Լ�
	if (letter == '+' || letter == '-' || letter == '*' || letter == '/' || letter == '(' || letter == ')') {
		//�ڽź��� ���� �켱������ �����ڰ� �ִ��� Ȯ��
		if (letter == ')') {
			while (top_node()!='(') {
				postfix_ex[position] = pop();
				position++;
			}
			pop();//��ȣ ����
			return; //')'�� ���ÿ� �߰� ���� �ʵ��� ����
		}
		else if (letter == '+' || letter == '-') {
			while (top_node() == '*' || top_node() == '/' || top_node() == '-' || top_node() == '+') {
				postfix_ex[position] = pop();
				position++;
			}
		}
		else if (letter == '*' || letter == '/') {
			while (top_node() == '*' || top_node() == '/') {
				postfix_ex[position] = pop();
				position++;
			}
		}
		push(letter);
	}
	else {
		postfix_ex[position] = letter;
		position++;
	}
	
}


void push(int p_OP) {
	node * new_op = (node*)malloc(sizeof(node));
	if (top == NULL) {
		new_op->link = NULL;
		new_op->op = p_OP;
		top = new_op;
	}
	else {
		new_op->link = top;
		new_op->op = p_OP;
		top = new_op;
	}
}

int pop() { 
	int tmp = top->op;
	node* del = top;
	top = top->link;
	free(del);
	return tmp;
}

char top_node() {
	if (top == NULL) {
		return '\0';
	}
	return top->op;
}