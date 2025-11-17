typedef struct {
    char *ch;       // 按串长分配存储区，ch指向串的基地址
    int length;     // 当前串长
} HString;

// 赋值
Status StrAssign(HString *S, const char *chars) {
    int len = strlen(chars);
    if (S->ch) free(S->ch);
    S->ch = (char*)malloc((len+1)*sizeof(char));
    if (!S->ch) return ERROR;
    strcpy(S->ch, chars);
    S->length = len;
    return OK;
}