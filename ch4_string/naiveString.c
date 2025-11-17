// 返回子串T在主串S中第pos个字符之后第一次出现的位置，没找到返回0
int Index(String S, String T, int pos) {
    int i = pos - 1;           // S的下标从0开始
    int j = 0;
    int slen = strlen(S), tlen = strlen(T);
    while (i < slen && j < tlen) {
        if (S[i] == T[j]) { i++; j++; }
        else { i = i - j + 1; j = 0; }   // i回溯
    }
    if (j >= tlen) return i - tlen + 1;  // 逻辑位序（从1开始）
    return 0;
}