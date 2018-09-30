//
//  lexicalAnalyzer.h
//  A-Simple-Lexical-Analyzer
//
//  Created by 王啸川 on 2018/9/30.
//  Copyright © 2018年 王啸川. All rights reserved.
//
#include <string.h>
#ifndef lexicalAnalyzer_h
#define lexicalAnalyzer_h


#endif /* lexicalAnalyzer_h */
void Debug();
void Scanner();
void sourceReader();
#define WORD_LENGTH 100         // 单词最大长度
#define WORD_OF_PROGRAM 1000    // 最多单词数
#define KEYWORD_NUMBER 16        // 关键词个数
// 标识符
// 关键字
// 常量
// 运算符
// 定界符
enum token_kind
{
    ERROR_TOKEN = 1,    //  错误
    INENT,          //  标识符
    INT_CONST,      //  整型常数
    FLOAT_CONST,    //  浮点型常数
    CHAR_CONST,     //  字符型常量
    INT,            //  关键字
    FLOAT,
    DOUBLE,
    VOID,
    CHAR,
    IF = 11,
    ELSE,
    DO,
    WHILE,
    SWITCH,
    CASE,
    FOR,
    GOTO,
    CONTINUE,
    BREAK,
    RETURN = 21,
    EQ,             //  ==
    ASSIGN,         //  =
    LP,             //  {
    RP,             //  }
    SEMI,           //  ;
    COMMA,          //  ,
    LB,             //  (
    RB,             //  )
    PLUS,           //  +
    PLUSPLUS = 31,       //  ++
    SUB,            //  -
    SUBSUB,         //  --
    MULT,           //  *
    DIV,            //  /
    PERCENT,        //  %
    ENTER,          //  \n
    NOT,            //  !
    NOTEQ,          //  !=
    MORETHAN,       //  >
    LESSTHAN,       //  <
    MOREEQ,         //  >=
    LESSEQ,         //  <=
} word_kind;

char* rwtab[KEYWORD_NUMBER] = { "int","float","double",
                                "void","char","if",
                                "else","do","while",
                                "switch","case","for",
                                "goto","continue","break",
                                "return"};
char ch;
int syn = 0;                // 单词种别码
int row = 1;                // 行数计数器
int p = 0;                  // 字符计数器
int m = 0;
char token[WORD_LENGTH] = {};    // 单词字符串
char prog[WORD_LENGTH*WORD_OF_PROGRAM];
//= "int main() { int a = 32767; float b = 3.14; if(a == b) do{ switch(a){case,break;}}; }";    // 程序字符串
double sum;                 // 整数或小数值


void Scanner()
{
    syn = 0;
    for(int i = 0; i<WORD_LENGTH; i++)
        token[i] = NULL;
    ch = prog[p++];         // 读入程序
    while (ch == ' ')
    {
        ch = prog[p++];     // 屏蔽空格
    }
    
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') )
    {// 标识符与关键字检查
        m = 0;
        while ((ch >= '0' && ch <= '9')||(ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {// 拼标识符串
            token[m++] = ch;
            ch = prog[p++];
        }
        token[m++] = '\0';
        p--;    // 将多移动的计数器退回
        syn = INENT;
        for(int n = 0; n<KEYWORD_NUMBER; n++)
        {// 关键字检查
            if(strcmp(token,rwtab[n]) == 0)
            {
                syn = syn+4+n;  // 枚举定义区关键字与常量的距离为4
                break;
            }
        }
    }
    
    else if((ch >= '0' && ch <= '9'))
    {// 整数与小数检查
        sum = 0;
        while ((ch >= '0' && ch <= '9'))
        {
            sum = sum*10 + ch-'0';  // 存放数字
            ch = prog[p++];
        }
        syn = INT_CONST;
        
        if(ch == '.')
        {// 小数检查
            ch = prog[p++];
            double flag = 0.1;
            while((ch >= '0' && ch <= '9'))
            {
                sum = sum + (ch - '0')*flag;
                flag = flag*0.1;
                ch = prog[p++];
            }
            syn = FLOAT_CONST;
        }
        p--;
        
        if(syn == INT_CONST)
        {// 整数越界检查
            if(sum > 32767) syn = ERROR_TOKEN;
        }
    }
    
    /*else if(ch == '\"')
    {// 字符串检查
        syn = CHAR_CONST;
        m = 0;
        token[m++] = ch;
        while((ch = prog[p++])!='\"')
        {
            token[m++] = ch;
        }
        涉及到诸如 char a[] = "\"test";这种转义字符里的对应字符串，暂时先跳过
    }*/

    else switch(ch)
    {
        case '=':
            m = 0;
            token[m++] = ch;
            syn = ASSIGN;
            if((ch = prog[p++]) == '=')
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = EQ;
            }
            else p--;
            break;
        case '{':
            m = 0;
            token[m] = ch;
            syn = LP;
            break;
        case '}':
            m = 0;
            token[m] = ch;
            syn = RP;
            break;
        case ';':
            m = 0;
            token[m] = ch;
            syn = SEMI;
            break;
        case ',':
            m = 0;
            token[m] = ch;
            syn = COMMA;
            break;
        case '(':
            m = 0;
            token[m] = ch;
            syn = LB;
            break;        
        case ')':
            m = 0;
            token[m] = ch;
            syn = RB;
            break;
        case '+':
            m = 0;
            token[m++] = ch;
            syn = PLUS;
            if((ch = prog[p++] == '+'))
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = PLUSPLUS;
            }
            else p--;
            break;
        case '-':
            m = 0;
            token[m++] = ch;
            syn = SUB;
            if((ch = prog[p++] == '-'))
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = SUBSUB;
            }
            else p--;
            break;
        case '*':
            m = 0;
            token[m] = ch;
            syn = MULT;
            break;
        case '/':
            m = 0;
            token[m] = ch;
            syn = DIV;
            break;
        case '%':
            m = 0;
            token[m] = ch;
            syn = PERCENT;
            break;
        case '\n':
            syn = ENTER;
            break;
        case '!':
            m = 0;
            token[m++] = ch;
            syn = NOT;
            if((ch = prog[p++]) == '=')
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = NOTEQ;
            }
            else p--;
            break;
        case '>':
            m = 0;
            token[m++] = ch;
            syn = MORETHAN;
            if((ch = prog[p++]) == '=')
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = MOREEQ;
            }
            else p--;
            break;
        case '<':
            m = 0;
            token[m++] = ch;
            syn = LESSTHAN;
            if((ch = prog[p++]) == '=')
            {
                token[m++] = ch;
                token[m] = '\0';
                syn = LESSEQ;
            }
            else p--;
            break;
        case '\0':
            syn = 0;
            break;
        default:
            syn = ERROR_TOKEN;
            break;
    }
}

void Debug()
{
    do
    {
        Scanner();
        switch(syn)
        {
            case INT_CONST: printf("(%d,%d)\n",syn,(int)sum); break;
            case FLOAT_CONST: printf("(%d,%f)\n",syn,sum); break;
            case ERROR_TOKEN: printf("(error!)\n"); break;
            case ENTER: break;
            case 0: break;
            default: printf("(%d,%s)\n",syn,token); break;
        }
    }while(syn != 0);
}

void sourceReader()
{
    FILE *fp;
    if((fp = fopen("sourceFile.txt", "rb")) == NULL)
    {
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int fileLen = ftell(fp);
    char *tmp = (char*) malloc(sizeof(char)* fileLen);
    fseek(fp, 0, SEEK_SET);
    fread(tmp, fileLen, sizeof(char), fp);
    fclose(fp);
    
    for(int i = 0; i<fileLen; ++i)
    {
        prog[i] = tmp[i];
    }
        
}


