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
#define WORD_LENGTH 100         // 单词最大长度
#define WORD_OF_PROGRAM 1000    // 最多单词数
#define KEYWORD_NUMBER 5        // 关键词个数
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
    CHAR,
    IF,
    ELSE,
    EQ,             //  ==
    ASSIGN,         //  =
    LP,             //  {
    RP,             //  }
    SEMI,           //  ;
    COMMA,          //  ,
    LB,             //  (
    RB,             //  )
} word_kind;

char* rwtab[KEYWORD_NUMBER] = {"int","float","char","if","else"};
char ch;
int syn = 0;                    // 单词种别码
int row = 1;                // 行数计数器
int p = 0;                  // 字符计数器
int m = 0;
char token[WORD_LENGTH] = {};    // 单词字符串
char prog[WORD_LENGTH*WORD_OF_PROGRAM] = "int main() { int a = 32768; float b = 3.14; if(a == b); }";    // 程序字符串
double sum;                 // 整数或小数值


void scanner()
{
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
        case '\0':
            syn = 0;
    }

}

void Debug()
{
    do
    {
        scanner();
        switch(syn)
        {
            case INT_CONST: printf("(%d,%d)\n",syn,(int)sum); break;
            case FLOAT_CONST: printf("(%d,%f)\n",syn,sum); break;
            case ERROR_TOKEN: printf("(error!)\n"); break;
            case 0: break;
            default: printf("(%d,%s)\n",syn,token); break;
        }
    }while(syn != 0);
}
