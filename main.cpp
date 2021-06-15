#include <iostream>
#include <cstdio>

using namespace std;
char Data[20][20];                    //算符优先关系
char stack[100];                          //模拟符号栈s
char TerminatorLabel[20];                       //文法终极符集
char input[100];                      //文法输入符号串
char In_str[20][10];                  //用于输入串的分析
int stack_top;
char a, q;
int r;                                //文法规则个数
int r1;                               //转化后文法规则个数
char st[10][30];                      //用来存储文法规则
char first[10][10];                   //文法非终结符FIRSTVT集
char last[10][10];                    //文法非终结符LASTVT集
int fflag[10] = {0};                //标志第i个非终结符的FIRSTVT集是否已求出
int lflag[10] = {0};                //标志第i个非终结符的LASTVT集是否已求出
int deal();                          //对输入串的分析
int Terminator(char c);                //判断字符c是否是终极符
int getIndex(char c);                 //求字符c在算符优先关系表中的下标
void out(int j, int k, char *s);       //打印s栈
void firstvt(char c);                //求非终结符c的FIRSTVT集
void lastvt(char c);                 //求非终结符c的LASTVT集
void table();                        //创建文法优先关系表
int main() {
    int i, j, k = 0;
    printf("请输入文法规则数：");
    cin >> r;
    printf("请输入文法规则：\n");
    for (i = 0; i < r; i++) {
        cin >> st[i];                //存储文法规则，初始化FIRSTVT集和LASTVT集*/
        first[i][0] = 0;            /*first[i][0]和last[i][0]分别表示st[i][0]非终极
									符的FIRSTVT集和LASTVT集中元素的个数*/
        last[i][0] = 0;
    }
    for (i = 0; i < r; i++)
    {//判断文法是否合法
        for (j = 0; st[i][j] != '\0'; j++) {
            if (st[i][0] < 'A' || st[i][0] > 'Z') {
                printf("不是算符文法!\n");
                exit(-1);
            }
            if (st[i][j] >= 'A' && st[i][j] <= 'Z') {
                if (st[i][j + 1] >= 'A' && st[i][j + 1] <= 'Z')//两非终结符不能相邻
                {
                    printf("不是算符文法!\n");
                    exit(-1);
                }
            }
        }
    }
    for (i = 0; i < r; i++) {
        for (j = 0; st[i][j] != '\0'; j++) {
            if ((st[i][j] < 'A' || st[i][j] > 'Z') && st[i][j] != '-' && st[i][j] != '>' && st[i][j] != '|')
                TerminatorLabel[k++] = st[i][j];
        }
    }
    TerminatorLabel[k] = '#';//把井号终结符加入到终结符集合里面
    TerminatorLabel[k + 1] = '\0';
    table();

    printf("每个非终结符的FIRSTVT集为：\n");    //输出每个非终结符的FIRSTVT集
    for (i = 0; i < r; i++) {
        printf("%c: ", st[i][0]);
        for (j = 0; j < first[i][0]; j++) {
            printf("%c ", first[i][j + 1]);
        }
        printf("\n");
    }
    printf("每个非终结符的LASTVT集为：\n");    //输出每个非终结符的LASTVT集
    for (i = 0; i < r; i++) {
        printf("%c: ", st[i][0]);
        for (j = 0; j < last[i][0]; j++) {
            printf("%c ", last[i][j + 1]);
        }
        printf("\n");
    }
    printf("算符优先分析表如下:\n");
    for (i = 0; TerminatorLabel[i] != '\0'; i++)
        printf("\t%c", TerminatorLabel[i]);
    printf("\n");
    for (i = 0; i < k + 1; i++) {
        printf("%c\t", TerminatorLabel[i]);
        for (j = 0; j < k + 1; j++) {
            printf("%c\t", Data[i][j]);
        }
        printf("\n");
    }
    printf("请输入文法输入符号串以#结束:");
    while (cin >> input && input != string("exit")) {
        deal();
        printf("请输入文法输入符号串以#结束:");
    }

    system("pause");
}

void table() {
    char text[20][10];
    int i, j, k, t, l, x, y = 0;
    int m, n;
    x = 0;
    //求firstvt集和lastvt集
    for (i = 0; i < r; i++) {
        firstvt(st[i][0]);
        lastvt(st[i][0]);
    }
    //转化文法，化为单候选式文法
    for (i = 0; i < r; i++) {
        text[x][y] = st[i][0];
        y++;
        for (j = 1; st[i][j] != '\0'; j++) {
            if (st[i][j] == '|') {
                text[x][y] = '\0';
                x++;
                y = 0;
                text[x][y] = st[i][0];
                y++;
                text[x][y++] = '-';
                text[x][y++] = '>';
            } else {
                text[x][y] = st[i][j];
                y++;
            }
        }
        text[x][y] = '\0';
        x++;
        y = 0;
    }
    r1 = x;//更改转换后文法的数目
    printf("转化后的文法为:\n");
    for (i = 0; i < x; i++)
    {//输出转化后的文法规则串
        printf("%s\n", text[i]);
    }
    /*求每个终结符的推导结果(去掉"->"
    后的转化文法，用于最后的规约)*/
    for (i = 0; i < x; i++) {
        In_str[i][0] = text[i][0];
        for (j = 3, l = 1; text[i][j] != '\0'; j++, l++)
            In_str[i][l] = text[i][j];
        In_str[i][l] = '\0';
    }

    //利用书上算法构造算符优先分析表
    //firstvt[0][0]第一位为firstvt集元素数目
    //lastvt集也一样
    for (i = 0; i < x; i++) {
        for (j = 1; text[i][j + 1] != '\0'; j++) {
            if (Terminator(text[i][j]) && Terminator(text[i][j + 1])) {
                m = getIndex(text[i][j]);
                n = getIndex(text[i][j + 1]);
                Data[m][n] = '=';
            }
            if (text[i][j + 2] != '\0' && Terminator(text[i][j]) && Terminator(text[i][j + 2]) &&
                !Terminator(text[i][j + 1])) {
                m = getIndex(text[i][j]);
                n = getIndex(text[i][j + 2]);
                Data[m][n] = '=';
            }
            if (Terminator(text[i][j]) && !Terminator(text[i][j + 1])) {
                for (k = 0; k < r; k++) {
                    if (st[k][0] == text[i][j + 1])
                        break;
                }
                m = getIndex(text[i][j]);
                for (t = 0; t < first[k][0]; t++) {
                    n = getIndex(first[k][t + 1]);
                    Data[m][n] = '<';
                }
            }
            if (!Terminator(text[i][j]) && Terminator(text[i][j + 1])) {
                for (k = 0; k < r; k++) {
                    if (st[k][0] == text[i][j])
                        break;
                }
                n = getIndex(text[i][j + 1]);
                for (t = 0; t < last[k][0]; t++) {
                    m = getIndex(last[k][t + 1]);
                    Data[m][n] = '>';
                }
            }
        }
    }
    //将#E#开始文法也加上去求出其对应的firstvt和lastvt集。
    m = getIndex('#');
    for (t = 0; t < first[0][0]; t++) {
        n = getIndex(first[0][t + 1]);
        Data[m][n] = '<';
    }
    n = getIndex('#');
    for (t = 0; t < last[0][0]; t++) {
        m = getIndex(last[0][t + 1]);
        Data[m][n] = '>';
    }
    Data[n][n] = '=';
}

void firstvt(char c)
{//求FIRSTVT集
    int i, j, k, m, n;
    for (i = 0; i < r; i++) {
        if (st[i][0] == c)
            break;
    }
    if (fflag[i] == 0) {
        n = first[i][0] + 1;
        m = 0;
        do {
            if (m == 2 || st[i][m] == '|') {
                if (Terminator(st[i][m + 1])) {
                    first[i][n] = st[i][m + 1];
                    n++;
                } else {
                    if (Terminator(st[i][m + 2])) {
                        first[i][n] = st[i][m + 2];
                        n++;
                    }
                    if (st[i][m + 1] != c) {
                        firstvt(st[i][m + 1]);
                        for (j = 0; j < r; j++) {
                            if (st[j][0] == st[i][m + 1])
                                break;
                        }
                        for (k = 0; k < first[j][0]; k++) {
                            int t;
                            for (t = 0; t < n; t++) {
                                if (first[i][t] == first[j][k + 1])
                                    break;
                            }
                            if (t == n) {
                                first[i][n] = first[j][k + 1];
                                n++;
                            }
                        }
                    }
                }
            }
            m++;
        } while (st[i][m] != '\0');
        first[i][n] = '\0';
        first[i][0] = (char) --n;//第一位值存firstvt集中元素的个数（字符形式）
        fflag[i] = 1;//表明该非终极符的firstvt集求出来了
    }
}

void lastvt(char c)
{ //求LASTVT集
    int i, j, k, m, n;
    for (i = 0; i < r; i++) {
        if (st[i][0] == c)
            break;
    }
    if (lflag[i] == 0) {
        n = last[i][0] + 1;
        m = 0;
        do {
            if (st[i][m + 1] == '\0' || st[i][m + 1] == '|') {
                if (Terminator(st[i][m])) {
                    last[i][n] = st[i][m];
                    n++;
                } else {
                    if (Terminator(st[i][m - 1])) {
                        last[i][n] = st[i][m - 1];
                        n++;
                    }
                    if (st[i][m] != c) {
                        lastvt(st[i][m]);
                        for (j = 0; j < r; j++) {
                            if (st[j][0] == st[i][m])
                                break;
                        }
                        for (k = 0; k < last[j][0]; k++) {
                            int t;
                            for (t = 0; t < n; t++) {
                                if (last[i][t] == last[j][k + 1])
                                    break;
                            }
                            if (t == n) {
                                last[i][n] = last[j][k + 1];
                                n++;
                            }
                        }
                    }
                }
            }
            m++;
        } while (st[i][m] != '\0');
        last[i][n] = '\0';
        last[i][0] = (char) --n;
        lflag[i] = 1;
    }
}

int deal() {
    int i, j;
    int x, y;
    int z;                                 //输入串的长度
    stack_top = 1;
    stack[stack_top] = '#';                            //栈置初值
    for (i = 0; input[i] != '\0'; i++);    //计算输入串的长度
    z = i;
    i = 0;
    while ((a = input[i]) != '\0') {
        //j指向最接近栈顶的终极符
        if (Terminator(stack[stack_top]))
            j = stack_top;
        else
            j = stack_top - 1;
        x = getIndex(stack[j]);//获取最接近栈顶的终极符在终极符表中位置
        y = getIndex(a);//获取第一个输入符号在终极符表中位置
        if (Data[x][y] == '>')
        {//归约
            out(1, stack_top, stack);
            printf("%c", a);
            out(i + 1, z, input);
            printf("规约\n");
            do {
                q = stack[j];
                if (Terminator(stack[j - 1]))
                    j = j - 1;
                else j = j - 2;
                x = getIndex(stack[j]);
                y = getIndex(q);
            } while (Data[x][y] != '<');
            int m, n, N;
            for (m = j + 1; m <= stack_top; m++) {
                for (N = 0; N < r1; N++)
                    for (n = 1; In_str[N][n] != '\0'; n++) {
                        if (!Terminator(stack[m]) && !Terminator(In_str[N][n])) {
                            if (Terminator(stack[m + 1]) && Terminator(In_str[N][n + 1])
                                && stack[m + 1] == In_str[N][n + 1]) {
                                stack[j + 1] = In_str[N][0];
                                break;
                            }
                        } else if (Terminator(stack[m]))
                            if (stack[m] == In_str[N][n]) {
                                stack[j + 1] = In_str[N][0];
                                break;
                            }
                    }
            }
            stack_top = j + 1;
            if (stack_top == 2 && a == '#') {
                out(1, stack_top, stack);
                printf("%c", a);
                out(i + 1, z, input);
                printf("结束\n");
                printf("\n输入串符合文法的定义！\n");
                return 1;//输入串符合文法的定义
            }
        } else if (Data[x][y] == '<' || Data[x][y] == '=') {//移进
            out(1, stack_top, stack);
            printf("%c", a);
            out(i + 1, z, input);
            printf("移进\n");
            stack_top++;
            stack[stack_top] = a;
            i++;
        } else {
            printf("\n输入串不符合文法的定义！\n");
            return 0;
        }
    }
    printf("\n输入串不符合文法的定义！\n");
    return 0;
}

void out(int j, int k, char *s) {
    int n = 0;
    for (int i = j; i <= k; i++) {
        printf("%c", s[i]);
        n++;
    }
    for (; n < 15; n++) {
        printf(" ");
    }
}

int getIndex(char c) { //求字符c在文法终极符表中的下标
    for (int i = 0; TerminatorLabel[i] != '\0'; i++) {
        if (c == TerminatorLabel[i])
            return i;
    }
    return -1;
}

int Terminator(char c) {//判断字符c是否是终极符
    for (int i = 0; TerminatorLabel[i] != '\0'; i++) {
        if (c == TerminatorLabel[i])
            return 1;
    }
    return 0;
}

/*
S->S+T|S-T|T
T->T*P|T/P|P
P->(S)|i

 * */