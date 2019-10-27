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
int cmp(char letter); //연산자 사이의 우위비교 함수
int change(char letter);	//문자를 정수로 만들어줄 함수

node* top = NULL;
char postfix_ex[50];	//후위표기로 변환된 수식을 담을 변수
int position;  //현재까지 처리된 수식의 인덱스를 담을 변수

int main() {
	char user_ex[50];  //사용자로부터 입력담을 수식을 보관할 변수 
	printf("--------------------------------------------------\n");
	printf("식 입력 : ");
	scanf_s("%s", user_ex, 50);

	printf("\n중위->후위\n");
	for (int i = 0; user_ex[i]; ++i) {
		printf("string : %s\n", user_ex + i + 1);
		printf("position : %c\n", user_ex[i]);
		check(user_ex[i]);
		s_Dis();
		printf("현재 : %s\n\n", postfix_ex);
	}
	while (top_node() != '\0') {	//후위표기가 끝나고 stack에 남아있는 연산자들 pop 
		postfix_ex[position] = pop();
		position++;
	}

	for (int j = 0; postfix_ex[j]; ++j) {
		cal(postfix_ex[j]);
	}

	printf("입력된 식의 후위표기 식은 %s입니다.\n", postfix_ex);
	printf("입력된 식의 답은 %d입니다.\n", pop());
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

void check(char letter) {	//해당 문자가 숫자인지 연산자인지 확인하여 맞는 파트로 보내주는 함수
	if (letter == '+' || letter == '-' || letter == '*' || letter == '/' || letter == '(' || letter == ')') {
		//자신보다 낮은 우선순위의 연산자가 있는지 확인
		if (letter == ')') {
			while (top_node()!='(') {
				postfix_ex[position] = pop();
				position++;
			}
			pop();//괄호 제거
			return; //')'가 스택에 추가 되지 않도록 리턴
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