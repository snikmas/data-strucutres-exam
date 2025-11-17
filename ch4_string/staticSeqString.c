#include <stdio.h>
#include <string.h>
#define MAXSTRLEN 255               // 王道/教材标准长度
typedef char String[MAXSTRLEN+1];   // 多开一个位置放 '\0'

// 1. 赋值（生成一个串）
Status StrAssign(String S, const char *chars) {
    int len = strlen(chars);
    if (len > MAXSTRLEN) return ERROR;
    strcpy(S, chars);
    S[len] = '\0';                  // 保证以 '\0' 结尾
    return OK;
}

// 2. 求串长
int StrLength(String S) {
    return strlen(S);
}

// 3. 串比较
int StrCompare(String S1, String S2) {
    int i = 0;
    while (S1[i] && S2[i] && S1[i] == S2[i]) i++;
    return S1[i] - S2[i];           // <0: S1<S2  =0:相等  >0:S1>S2
}

// 4. 串连接（S = S1 + S2）
Status StrConcat(String S, String S1, String S2) {
    int len1 = strlen(S1), len2 = strlen(S2);
    if (len1 + len2 > MAXSTRLEN) return ERROR;
    strcpy(S, S1);
    strcat(S, S2);
    return OK;
}

// 5. 子串（从第pos个字符开始，长度为len的子串）
Status SubString(String Sub, String S, int pos, int len) {
    int i, slen = strlen(S);
    if (pos < 1 || pos > slen || len < 0 || pos+len-1 > slen) return ERROR;
    for (i = 0; i < len; i++) {
        Sub[i] = S[pos+i-1];
    }
    Sub[i] = '\0';
    return OK;
}