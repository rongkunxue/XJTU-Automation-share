/*无向图的查找*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define NO_OPRERATED 0
#define OPERATED 1
#define MaxVex 50
#define MOSTMAX 10000
#define NUMBER_VEX 13

typedef char* STRING;
typedef int SHORTSHORTPATH[MaxVex];
typedef int SHORTPATH[MaxVex];

typedef struct {
	int vexs[MaxVex];
	int arc[MaxVex][MaxVex];
	int NumberVertexs;
}Mgraph;/*图的结构，其中我们储存节点，边的权值，点数*/

/*
* 规定每个地名在程序中的数字标志
* 北门          0
* 饮水思源		1
* 传动门3		2
* 腾飞塔		3
* 传送门1		4
* 图书馆		5
* 传送门2		6
* 传送门4		7
* 教学主楼		8
* 宪梓堂		9
* 活动中心		10
* 西迁馆		11
* 南门			12
*/

//此函数用于初始化一个图
int CREATIVE_MAP(Mgraph& G) {
	int i = 0, j = 0;
	G.NumberVertexs = NUMBER_VEX;
	
	for (i = 0; i < G.NumberVertexs; i++) {
		for (j = 0; j < G.NumberVertexs; j++) {
			G.arc[i][j] =MOSTMAX;
		}
	}/*将所有有关系的边先都赋予最大值*/

	for (i = 0; i < G.NumberVertexs; i++) {
		G.vexs[i] = i;
	}/*依次按顺序赋予节点值0-12*/
	//按照图中关系赋值
	G.arc[0][2] = 22; 
	G.arc[0][1] = 18;
	G.arc[1][3] = 19;
	G.arc[1][4] = 27;
	G.arc[3][2] = 4;
	G.arc[4][5] = 4;
	G.arc[3][5] = 23;
	G.arc[5][6] = 4;
	G.arc[3][7] = 32;
	G.arc[5][8] = 15;
	G.arc[7][9] = 4;
	G.arc[9][8] = 8;
	G.arc[8][10] = 21;
	G.arc[10][12] = 30;
	G.arc[9][12] = 14;
	G.arc[12][6] = 21;
	G.arc[6][11] = 43;
	G.arc[11][12] = 20;
	G.arc[2][0] = 22;
	G.arc[1][0] = 18;
	G.arc[3][1] = 19;
	G.arc[4][1] = 27;
	G.arc[2][3] = 4;
	G.arc[5][4] = 4;
	G.arc[5][3] = 23;
	G.arc[6][5] = 4;
	G.arc[7][3] = 32;
	G.arc[8][5] = 15;
	G.arc[9][7] = 4;
	G.arc[8][9] = 8;
	G.arc[10][8] = 21;
	G.arc[12][10] = 30;
	G.arc[12][9] = 14;
	G.arc[6][12] = 21;
	G.arc[11][6] = 43;
	G.arc[12][11] = 20;

	for (i = 0; i < G.NumberVertexs; i++) {
		G.arc[i][i] = 0;
	}/*规定点与自身的权值为0*/
	return OK;
}
//用于在图中寻找以vo作为源点到其它点的距离，并且存储在DisTance中
void shortest_DIJ(Mgraph G,int v0,SHORTPATH &Path,SHORTSHORTPATH &DisTance) {
	int Final_DIG[MaxVex];//用于存储，如果找到则为OPERATED，未找到最短路径则为NO_OPRERATED
	int V_Min_path_V0 = 0,V_TMP = 0; //V_Min_path_V0指的是距离V0源点最近的点
	int i = 0;
	int Min_path = 0;//最短的长度值

	for (V_Min_path_V0 = 0; V_Min_path_V0 < G.NumberVertexs; V_Min_path_V0++)
	{
		Final_DIG[V_Min_path_V0] = NO_OPRERATED;
		DisTance[V_Min_path_V0] = G.arc[v0][V_Min_path_V0];
		Path[V_Min_path_V0] = 0;
	}//初始化PATH路径，和DIATANCE
	DisTance[v0] = 0; Final_DIG[v0] = OPERATED;

	for (i = 1; i < G.NumberVertexs; i++) {
		Min_path = MOSTMAX; //重新将min_path调回原来的值

		for (V_TMP = 0; V_TMP < G.NumberVertexs; V_TMP++) {
			if (!Final_DIG[V_TMP]) {
				if (DisTance[V_TMP] < Min_path) {
					V_Min_path_V0 = V_TMP; Min_path = DisTance[V_TMP];
				}/*寻找距离V0最近的点，也就是寻找DISTANCE[W]的最小数*/
			}
		}//找到DisTance[V_TMP]中的最小值,该点的arc是V_Min_path_V0
		Final_DIG[V_Min_path_V0] = OPERATED;

		for (V_TMP = 0; V_TMP < G.NumberVertexs; V_TMP++) {
			if (!Final_DIG[V_TMP]) {
				if (Min_path + G.arc[V_Min_path_V0][V_TMP] < DisTance[V_TMP]) {
					DisTance[V_TMP] = Min_path + G.arc[V_Min_path_V0][V_TMP];
					Path[V_TMP] = V_Min_path_V0;
				}
			}
		}//寻找离新找到的W附近的点，更新他们的DisTance[W]；
	}
}


int Translate(STRING str) {
	if (!strcmp(str, "北门")) return 0;
	else  if (!strcmp(str, "饮水思源")) return 1;
	else if (!strcmp(str, "传动门3")) return 2;
	else if (!strcmp(str, "腾飞塔")) return 3;
	else if (!strcmp(str, "传送门1")) return 4;
	else if (!strcmp(str, "图书馆")) return 5;
	else if (!strcmp(str, "传送门2")) return 6;
	else if (!strcmp(str, "传送门4")) return 7;
	else if (!strcmp(str, "教学主楼")) return 8;
	else if (!strcmp(str, "宪梓堂")) return 9;
	else if (!strcmp(str, "活动中心")) return 10;
	else if (!strcmp(str, "西迁馆")) return 11;
	else if (!strcmp(str, "南门")) return 12;
	else return -1;
}

//输出对应数字所代表的地名
void PRINTF_INT_STR(int PosiTion_Number) {
	switch(PosiTion_Number) {
	case 0:printf("北门");
		break;
	case 1:printf("饮水思源");
		break;
	case 2:printf("传动门3");
		break;
	case 3:printf("腾飞塔");
		break;
	case 4:printf("传送门1");
		break;
	case 5:printf("图书馆");
		break;
	case 6:printf("传送门2");
		break;
	case 7:printf("传送门4");
		break;
	case 8:printf("教学主楼");
		break;
	case 9:printf("宪梓堂");
		break;
	case 10:printf("活动中心");
		break;
	case 11:printf("西迁馆");
		break;
	case 12:printf("南门");
		break;
	}
}

//回溯路径，并且按照顺序输出来
void Feed_back_PATH(SHORTPATH& path,int go,int end) {
	int i = end, j = 1;
	SHORTPATH path_new;
	while (i != go) {
		path_new[j++] = i;
		i = path[i];
	}
	path_new[j] = i;
	path_new[0] = j;
	for (; j >= 2; j--) {
		PRINTF_INT_STR(path_new[j]); printf("->");
	}
	PRINTF_INT_STR(path_new[1]);
	printf("\n");
}

int main(int argc, char*argv[]) {
	if (argc != 3) {
		printf("ERROR_01");
		return -1;
	}//检查参数
	Mgraph ScoolMap;
	CREATIVE_MAP(ScoolMap);
	int GO = 0, END = 0;
	GO = Translate(argv[1]);
	END = Translate(argv[2]);
	if (GO == -1 || END == -1) {
		printf("ERROR_02");
		return -2;
	}//输入地点是否正常
	int path[MaxVex] = { 0 };
	int distance[MaxVex] = { 0 };
	shortest_DIJ(ScoolMap, GO,path, distance);
	//Feed_back_PATH(path, GO, END);
	printf("%d", distance[END]);
	return 0;
}