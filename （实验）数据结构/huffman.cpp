#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define max 100
#define STACKINCREMENT 100
#define STACK_INIT_SIZE 50
#define ERROR 0
#define OK 1

//动态分配数组存储赫夫曼树
typedef struct{
	int weight;
	int parent;
	int lchild;
	int rchild;
} htnode, * huffmantree;

//动态分配数组存储赫夫曼编码表 
typedef char** huffmancode;


typedef struct{
	int* base;
	int* top;
	int stacksize;
}Sqstack;


int Initstack(Sqstack& S){
	S.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!S.base)
	{
		return ERROR;
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}


int StackEmpty(Sqstack& S){
	if (S.base == S.top){
		return OK;
	}
	else{
		return ERROR;
	}
}


//删除栈顶元素
void Pop(Sqstack& S){
	if (S.top == S.base)
	{
		return;
	}
	--S.top;
}

//返回栈顶元素的值
int Gettop(Sqstack& S){
	int e;
	e = *--S.top;
	return e;
}

//用e返回栈顶元素 
void Push(Sqstack& S, int e)
{
	if (S.top - S.base > S.stacksize)
	{
		S.base = (int*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(int));
		if (!S.base)
		{
			return;
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top = e;
	S.top++;
}


void select(huffmantree& ht, int target_length, int min[2], char* Sort)
{
	int i = 1, j = 1;  //初始化i和j,由于我们知道从1开始考虑，所以初始化为1
	while (ht[i].parent != 0) {
		i++;
	}					//找到第一个父母时0的节点，也就是孤立的点
	min[0] = i;			//初始化假设它就是最小的点
	int min1_weight = ht[i].weight;			//那我们假设他的WEIGHT也自然是最小的
	for (i = 1; i <= target_length; i++) {
		if (ht[i].weight < min1_weight && ht[i].parent == 0) {
			min[0] = i;
			min1_weight = ht[i].weight;
		}			//长度排序，如果遇到另外一个孤立节点，而且权重还比较小，那末我们就换
					//关键的就是必须时孤立节点
	}
	//显然新的节点也是孤立的，而且还不能是min1
	while (ht[j].parent != 0 || j == min[0]) {
		j++;
	}
	min[1] = j;
	int min2_weight = ht[j].weight;
	//我们显然知道前面的点都是不符合条件的，那末自然往下排序即可
	for (; j <= target_length; j++) {
		if (j != min[0] && ht[j].weight < min2_weight && ht[j].parent == 0) {
			min[1] = j;
			min2_weight = ht[j].weight;
		}
	}
}


//构造赫夫曼树并求赫夫曼编码
void creative_huffmantree(huffmantree& HT, huffmancode& HC, int* w, int length, char* Sort) {
	int total_lenth = 2 * length - 1;
	int i = 1;
	int min[2] = { 0,0 };
	htnode* ptr;
	HT = (huffmantree)malloc((total_lenth + 1) * sizeof(htnode));

	for (ptr = HT + 1, i = 1; i <= length; ++i, ++ptr, ++w) {
		*ptr = { *w, 0, 0, 0 };
	}
	for (; i <= total_lenth; ++i, ++ptr) {
		*ptr = { 0,0,0,0 };
	}
	for (i = length + 1; i <= total_lenth; ++i) {
		select(HT, i - 1, min, Sort);
		HT[min[0]].parent = i;
		HT[min[1]].parent = i;
		HT[i].lchild = min[0];
		HT[i].rchild = min[1];
		HT[i].weight = HT[min[0]].weight + HT[min[1]].weight;
	}

	int start = 0, newer = 0, older = 0; ;
	char* cd;
	HC = (huffmancode)malloc((total_lenth + 1) * sizeof(char*));
	cd = (char*)malloc(length * sizeof(char));
	cd[length - 1] = '\0';

	for (i = 1; i <= length; ++i) {
		start = length - 1;
		for (newer = i, older = HT[i].parent; older != 0; newer = older, older = HT[older].parent) {
			if (HT[older].lchild == newer) {
				cd[--start] = '0';
			}
			else {
				cd[--start] = '1';
			}
		}
		HC[i] = (char*)malloc((length - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}



//将String中的字符按照先后顺序存储在Target中
void creative_target_w_pos(char* Str, char* Target, int* w, int* pos){
	int SYMBOL = 0;
	int i = 1;
	int j = 0;
	int k = 1;
	//确定长度，以方便后面的运算
	int length_str = 0;
	while (Str[length_str] != 0) {
		length_str++;
	}
	Target[0] = Str[0];

	//如果SYMBOL为1,则说明已经读过，直接跳过即可
	for (i = 1; i < length_str; i++) {
		SYMBOL = 0;
		for (j = 0; j < k; j++) {
			if (Target[j] == Str[i]) {
				SYMBOL = 1;
				break;
			}
		}
		if (SYMBOL == 0) {
			Target[k] = Str[i];
			k++;
		}
	}
	i = 0, j = 0;
	int length_target = strlen(Target);
	int temp = 0;
	for (i = 0; i < length_target; i++)
	{
		for (j = i; j < length_target; j++)
		{
			if (Target[j] < Target[i])
			{
				temp = Target[j];
				Target[j] = Target[i];
				Target[i] = temp;
			}
		}
	}

	i = 0, j = 0;
	while (Target[i] != 0) {
		w[i] = 0;
		j = 0;
		while (Str[j] != 0) {
			if (Str[j] == Target[i]) {
				w[i]++;
			}
			j++;
		}
		i++;
	}

	//将String[i]在sort[]中的位置存在pos[]中 
	i = 0, j = 0;
	//STR因为存在重复的情况，必然会受到影响，所以我们需要找到他们的位置
	while (Str[i] != 0) {
		j = 0;//当每次找到的时候，将位置信息返回
		while (Target[j] != Str[i]) {
			j++;
		}
		pos[i] = j;
		i++;
	}
}



//判断S[]是否为一个字符的编码，若是，输出该字符在sort中的下标 ，若不是，输出-1 
int Exist(huffmancode HC, char* s, int n)     //n为字符个数 
{
	int i = 1;
	for (i = 1; i <= n; i++)
	{
		if (strcmp(HC[i], s) == 0)              //查找到s 
		{
			return i - 1;                     //编码为HC[i]的字符在Sort中下标为i-1 
		}
	}
	return -1;
}

//译码并将其存入trans[],且返回是否翻译成功的状态，返回1，译码失败，返回0，译码成功 
int Translate(char* trans, char* Number, huffmancode HC, char* Sort)
{
	if (!strlen(Number))               //待译码为空，编码失败 
	{
		return 1;
	}
	int i = 0, j = 0, l = 0;
	char temp[100];
	int k = 0;
	temp[0] = '\0';
	while (Number[i])
	{
		while (Number[i] && Exist(HC, temp, strlen(Sort)) == -1)        //函数值为-1，未找到这样编码的字符，temp长度加一
		{
			temp[k] = Number[i];
			temp[k + 1] = '\0';
			k++;
			i++;
		}
		if (Exist(HC, temp, strlen(Sort)) != -1)                        //匹配成功，将字符存入Sort并将temp置0 
		{
			trans[j] = Sort[Exist(HC, temp, strlen(Sort))];
			j++;
			for (l = 0; l < k; l++)
			{
				temp[l] = 0;
			}
			k = 0;
		}
	}
	if (strlen(temp))    // temp未被置0，最后一次匹配不成功，编码失败,flag为1，返回1 
	{
		return 1;
	}

	return 0;
}

void printer(huffmantree& HT, int* level, int i, char* Sort)                   //i为该节点的序号 
{
	int div = 0;                                     //统计节点的度数 
	if (HT[i].parent)
	{
		div++;
	}
	if (HT[i].rchild)
	{
		div++;
	}
	if (HT[i].lchild)
	{
		div++;
	}
	if (i >= 1 && i <= strlen(Sort))         //原有的节点 
	{
		printf("%4c %6d %3d %5d\n", Sort[i - 1], HT[i].weight, div, level[i]);//输出时靠右对齐，Node占4行 
	}                                                                   //weight占6行，div占3行，level占5行 
	else
	{
		printf("NULL %6d %3d %5d\n", HT[i].weight, div, level[i]);
	}
}

//求每个节点的层数，存于数组level[]中 
void Layer(int* level, huffmantree& HT, char* Sort)
{
	int i = 0;
	int flag = 1;                           //flag为标志变量，flag=0表示无双亲 
	for (i = 1; i <= 2 * strlen(Sort) - 1; i++)
	{
		level[i] = 1;
		flag = HT[i].parent;
		while (flag != 0)
		{
			level[i]++;
			flag = HT[flag].parent;
		}
	}
}

//非递归线性遍历
void Traverse(huffmantree& HT, Sqstack& S, char* Sort, int* level)
{
	Initstack(S);
	int p = 2 * strlen(Sort) - 1;      //使p表示根节点的序号 
	Push(S, p);                 //根节点入栈 
	while (!StackEmpty(S))      //栈不空
	{
		p = Gettop(S);           //用p返回栈顶元素序号 
		printer(HT, level, p, Sort);
		if (HT[p].rchild)       //p的右孩子存在，右孩子入栈 
		{
			Push(S, HT[p].rchild);
		}
		if (HT[p].lchild)       //p的左孩子存在，左孩子入栈 
		{
			Push(S, HT[p].lchild);
		}
		else
		{
			if (HT[p].rchild)    //p的右孩子存在，删除p，右孩子入栈 
			{
				Pop(S);
				Push(S, HT[p].rchild);
			}
		}
	}
}

void printresult(huffmancode HC, char* trans, char* result, int* pos, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		strcat(result, HC[pos[i] + 1]);     //字符在pos[]中下标为k，在HC中则为k+1
	}
	printf("%s", result);
	printf(" ");
	printf("%s", trans);
}

int main(int argc, char* argv[])		//					
{
	if (argc != 3) {							//参数数量错误
		printf("ERROR_01");
		return 0;
	}
	if (strlen(argv[1]) < 20) {                   //字符串长度小于20，编码失败 
		printf("ERROR_02");
		return 0;
	}


	char result[max] = { 0 };
	int w[max] = { 0 };
	char Sort[max] = { 0 };
	int pos[max] = { 0 };
	char trans[max] = { 0 };
	int level[max] = { 0 };

	huffmantree HT;
	huffmancode HC;
	Sqstack S;
	int i = 0;
	creative_target_w_pos(argv[1], Sort, w, pos);
	if (strlen(Sort) == 1)
	{
		printf("ERROR_03");
		return 0;
	}
	creative_huffmantree(HT, HC, w, strlen(Sort), Sort);  // strlen(Sort)表示节点个数 
	Layer(level, HT, Sort);
	if (Translate(trans, argv[2], HC, Sort) == 1) {
		printf("ERROR_03");
		return 0;
	}
	printresult(HC, trans, result, pos, strlen(argv[1]));
	free(HT);
	free(HC);
	return 0;
}