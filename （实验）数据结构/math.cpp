#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define error 0
#define ok 1
#define stack_init_size 100
#define charnumber 7
#pragma warning(disable:4996)
#pragma warning(disable:c26451)

typedef struct
{
	char* base;
	char* top;
	int stacksize;
}sqstack1;  //定义一个运算符栈

typedef struct
{
	double* base;
	double* top;
	int stacksize;
}sqstack2; //定义一个运算栈

int initstack1(sqstack1* s)
{
	s->base = (char*)malloc(stack_init_size * sizeof(char));
	if (!s->base) return error;
	s->top = s->base;
	s->stacksize = stack_init_size;
	return ok;
}  //初始化一个栈
int initstack2(sqstack2* s)
{
	s->base = (double*)malloc(stack_init_size * sizeof(double));
	if (!s->base) return error;
	s->top = s->base;
	s->stacksize = stack_init_size;
	return ok;
}  //初始化
int stackempty1(sqstack1 s)
{
	if (s.base == s.top)
		return ok;
	else return error;
}
int stackempty2(sqstack2 s)
{
	if (s.base == s.top)
		return ok;
	else return error;
}
int pop1(sqstack1* S, char* e)//删除运算符元素e
{
	if (S->top == S->base)
		return error;//栈空
	*e = *--S->top;//让栈顶指针减一再赋值
	return ok;
}
int pop2(sqstack2& S, double& e)//删除运算数元素e
{
	if (S.top == S.base)
		return error;//栈空
	e = *--S.top;//让栈顶指针减一再赋值
	return ok;
}
int push1(sqstack1* s, char e)
{
	*s->top = e;
	s->top++;
	return ok;
}
int push2(sqstack2* s, double e)
{
	*s->top = e;
	s->top++;
	return ok;
}
char gettop1(sqstack1* s)
{
	char e;
	if (s->base == s->top)
	{
		printf("ERROR_03");
		return error;
	}
	e = *(s->top - 1);
	return e;
}
double gettop2(sqstack2* s)
{
	double e;
	if (s->base == s->top)
	{
		printf("ERROR_03");
		return error;
	}
	e = *(s->top - 1);
	return e;
}
double operate(double x, char z, double y) {
	if (z == '+') return x + y;
	else if (z == '-') return x - y;
	else if (z == '*') return x * y;
	else if (z == '^') return pow(x, y);
	else if (z == '/') {
		if (y == 0) {
			printf("ERROR_03");
			return error;
		}
		else return (x / y);
	}
	else return error;
}
char precede(char x, char y)//定义了算符间的优先关系，1表示大于，-1表示小于，0表示相等，2表示不存在
{
	int i = 0, j = 0;
	int form[charnumber][charnumber] =
	{
		{1,1,-1,-1,-1,1,1},
		{1,1,-1,-1,-1,1,1},
		{1,1,1,1,-1,1,1},
		{1,1,1,1,-1,1,1},
		{-1,-1,-1,-1,-1,0,2},
		{1,1,1,1,2,1,1},
		{-1,-1,-1,-1,-1,2,0}
	};
	switch (x)
	{
	case'+':i = 0;
		break;
	case'-':i = 1;
		break;
	case'*':i = 2;
		break;
	case'^':i = 2;
		break;
	case'/':i = 3;
		break;
	case'(':i = 4;
		break;
	case'[':i = 4;
		break;
	case'{':i = 4;
		break;
	case')':i = 5;
		break;
	case']':i = 5;
		break;
	case'}':i = 5;
		break;
	case'#':i = 6;
		break;
	}//定义数组对应位置
	switch (y)
	{
	case'+':j = 0;
		break;
	case'-':j = 1;
		break;
	case'*':j = 2;
		break;
	case'^':j = 2;
		break;
	case'/':j = 3;
		break;
	case'(':j = 4;
		break;
	case'[':j = 4;
		break;
	case'{':j = 4;
		break;
	case')':j = 5;
		break;
	case']':j = 5;
		break;
	case'}':j = 5;
		break;
	case'#':j = 6;
		break;
	}//定义数组对应位置
	if (form[i][j] == 1)
		return '>';
	else if (form[i][j] == -1)
		return '<';
	else
		return '=';
}


int inspect(char* a)
{
	sqstack1 s;
	int i, j, count;
	char e1, e2;

	initstack1(&s);
	i = j = count = 0;
	e1 = e2 = '0';

	for (i = 0; a[i] != '\0'; i++) {
		count++;
	}
	//printf("%d",count);
	for (i = 0; i < count; i++) {
		e1 = a[i];

		if ((e1 == '(') || (e1 == '[') || (e1 == '{'))
		{
			push1(&s, e1);
		}

		else if ((e1 == ')') || (e1 == ']') || (e1 == '}')) {
			if ((pop1(&s, &e2) == error) || (e1 == ')' && e2 != '(') || (e1 == ']' && e2 != '[') || (e1 == '}' && e2 != '{'))
			{
				printf("ERROR_02");
				return error;
			}
		}
	}
	if (!stackempty1(s))
	{
		printf("ERROR_02");
		return error;
	}

	for (i = 0; i < count; i++)
	{
		if ((a[i] >= 40 && a[i] <= 57) || (a[i] >= 91 && a[i] <= 94) || (a[i] >= 123 && a[i] <= 125))
			continue;
		else
		{
			printf("ERROR_02");
			return error;
		}
	}
	for (i = 0, j = 1; j < count; i++, j++)//两个相邻的元素
	{
		if (a[i] < 48 && a[i]>41)
			if (a[j] < 48 && a[j]>41)
			{
				printf("ERROR_02");
				return error;
			}
	}
	return ok;
}

double math_core(char a[])
{
	sqstack1 OPTR;//运算符栈
	initstack1(&OPTR);
	sqstack2  OPND;//运算数栈
	initstack2(&OPND);
	push1(&OPTR, '#');//以#为开始标志
	int i = 0, j = 0, cou = 0;
	double m = 0, x = 0, y = 0;
	char c = '0', s = '0', symbol = '0';
	c = a[0];


	while (c != '#' || gettop1(&OPTR) != '#')//若不是#开头
	{
		if (c >= 48 && c <= 57)//ASCII表中1~9
		{
			j = i + 1;
			if (a[j] == 46)
			{
				m = (a[j + 1] - '0');
				m = m / 10;
				m = m + (a[i] - '0');
				push2(&OPND, m);
				i = i + 3;
				c = a[i];
			}
			else if (a[j] >= 48 && a[j] <= 57)
			{
				int m1 = j + 1, n1 = 2;
				m = (a[i] - '0') * 10 + (a[j] - '0');
				while (a[m1] >= 48 && a[m1] <= 57)
				{
					n1++;
					m = m * 10 + a[m1] - '0';
					m1++;
				}
				push2(&OPND, m);
				i = i + n1;
				c = a[i];
			}
			else
			{
				m = a[i] - '0';
				push2(&OPND, m);
				i++;
				c = a[i];
			}
		}
		else
			switch (precede(gettop1(&OPTR), c))
			{
			case'<':
				push1(&OPTR, c);
				i++;
				c = a[i];
				break;
			case'=':
				pop1(&OPTR, &s);
				i++;
				c = a[i];
				break;
			case'>':
				pop1(&OPTR, &symbol);
				pop2(OPND, y);
				pop2(OPND, x);
				push2(&OPND, operate(x, symbol, y));
				break;
			}
	}
	return gettop2(&OPND);
}

int main(int argc,char *argv[])
{
	if (argc != 2)
	{
		printf("ERROR_01");
		return 0;
	}

	double answer = 0;
	int a = 1, i = 0, j = 0;
	a = inspect(argv[1]);
	if (a == 0) {
		return 0;
	}
	for (i = 0; argv[1][i] != '\0'; i++);
	char word_geting[100] = { '\0' };
	for (j = 0; j < i; j++)
		word_geting[j] = argv[1][j];
	word_geting[j] = '#';

	if (math_core(word_geting) == 0)
		return 0;
	answer = math_core(word_geting);
	printf("%g", answer);


}

