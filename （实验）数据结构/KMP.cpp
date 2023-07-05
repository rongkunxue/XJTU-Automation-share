#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

typedef struct {
	char* ch;
	int length;
}Hstring;		 //建立一个字符堆

int Index(Hstring S, Hstring T, int next[]) {
	int i = 1, j = 1;
	while (i <= S.length && j <= T.length) {
		if (j == 0 || S.ch[i] == T.ch[j]) {
			i++; j++;		//如果匹配到，直接后移动;
		}
		else {
			j = next[j];	//如果失配，则进行跳跃；
		}
	}
	if (j > T.length) {
		return i - T.length; //返回当时的地址
	}
	else {
		return -1;
	}
}

void get_next(Hstring& T, int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T.length) {
		if (j == 0 || T.ch[j] == T.ch[i]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

void change_able(char* s, Hstring& T) {
	int len = 0;
	int i = 0, j = 0;
	while (s[len] != '\0') {
		len++;
	}
	if (!len) {
		T.ch = NULL;
		T.length = 0;
	}
	else {
		T.ch = (char*)malloc(sizeof(char) * (len + 3));  //给一个长度值
		T.length = len;
		for (i = 0, j = 1; i < len; i++, j++) {
			T.ch[j] = s[i];
		}
	}
}

//实现清除的功能
int Clearstring(Hstring S) {
	if (S.ch) {
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return (1);
}

//求长度
int StrLength(Hstring S) {
	return S.length;
}

//字符串的比较
int StrCompare(Hstring S, Hstring T) {
	int i = 0;
	for (i = 0; i < S.length && i < T.length; i++) {
		if (S.ch[i] != T.ch[i])
			return(S.ch[i] - T.ch[i]);
	}
	return(S.length - T.length);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR_01");
		return -1;
	}//检查参数是否正确
	int next[max];
	Hstring MOTHER;
	Hstring SON;
	change_able(argv[1], MOTHER);
	change_able(argv[2], SON);
	get_next(SON, next);
	int result = 0;
	result = Index(MOTHER, SON, next);
	printf("%d", result);
	free(MOTHER.ch);
	free(SON.ch);
	return 0;
}
