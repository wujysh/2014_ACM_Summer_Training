#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>
using namespace std;

const int BUFSIZE = 1000;  // 标示符长度

map<string, int> vars;  // 变量存储

// ==========================================
// 词法分析程序
enum token_type {
    NUMBER, IDENT, OPERATOR, SEPARATOR, UNKOWN
};

struct Token {
    int type;
    union {
        int val;    // 数值
        char *name; // 标识符名字
        int op;     // 运算符、分隔符，以及其他单个字符
    } u;
} next_token; // 下一个未处理的token

int get_num(char c);
char *get_ident(char c);

void lex() {
    int c;
    while ((c = getchar()) != EOF && (c == ' ' || c == ';'));
    if (isdigit(c)) {  // 识别实数
        next_token.type = NUMBER;
        next_token.u.val = get_num(c);
        return;
    } else if (isalpha(c) || c == '_') {  // 识别标识符
        char *name = get_ident(c);
        //name = lookup(name)->name;

        next_token.type = IDENT;
        next_token.u.name = name;
        return;
    }
    if (c == '\n') c = ';';  //行尾；可忽略

    // 其他
    next_token.u.op = c;
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
            next_token.type = OPERATOR;
            break;
        case '(':
        case ')':
        case ';':
            next_token.type = SEPARATOR;
            break;
        default:
            next_token.type = UNKOWN;
    }
}

int get_num(char c) {  // 识别数字
    int val;
    val = c - '0';
    while (isdigit(c = getchar()))
        val = val * 10 + c - '0';
    int n = 0;
    if (c == '.') {
        while (isdigit(c = getchar())) {
            n++;
            val = val * 10 + c - '0';
        }
    }
    ungetc(c, stdin);
    return (val / pow(10.0, (int)n));
}

char *get_ident(char c) {  // 识别标示符
    static	char buf[BUFSIZE];
    int bufp = 0;

    buf[bufp++] = c;
    while (isalnum(c = getchar()) || c == '_')
        buf[bufp++] = c;
    ungetc(c, stdin);
    buf[bufp] = '\0';
    return buf;
}

// ==========================================
// 语法分析程序
int expr();
int term();
int factor();

// <expr> -> <term> { (+ | -) <term> }
int expr() {
    int val;
    val = term();
    while (next_token.type == OPERATOR &&
            (next_token.u.op == '+' || next_token.u.op == '-')) {
        int op = next_token.u.op;
        lex();

        if (op == '+')
            val += term();
        else if (op == '-')
            val -= term();
    }
    return val;
}

// <term> -> <factor> { (* | /) <factor> }
int term() {
    int val;
    val = factor();
    while (next_token.type == OPERATOR &&
            (next_token.u.op == '*'  || next_token.u.op == '/')) {
        int op = next_token.u.op;
        lex();

        if (op == '*') {
            val *= factor();
        } else if (op == '/') {
            int tmp;
            tmp = factor();
            //if (fabs(tmp) < 1e-6) {
            //fprintf(stderr, "除0");
            //exit(1);
            //} else {
            val /= tmp;
            //}
        }
    }
    return val;
}

// <factor> -> (<expr>) | num | ident | ident = <expr> | - <expr>
int factor() {
    int val;
    if (next_token.type == OPERATOR && next_token.u.op == '-') {
        lex();
        val = -1 * factor();
    } else if (next_token.type == SEPARATOR && next_token.u.op == '(') {
        lex();
        val = expr();
        if (next_token.type == SEPARATOR && next_token.u.op == ')') {
            lex();
        } else {
            //fprintf(stderr, "括号不匹配\n");
            //exit(1);
        }
    } else if (next_token.type == NUMBER) {
        val = next_token.u.val;
        lex();
    } else if (next_token.type == IDENT) {
        //HashNode *ptr = lookup(next_token.u.name);
        string var_name = next_token.u.name;
        lex();
        if (next_token.type == OPERATOR && next_token.u.op == '=') {
            // 赋值操作
            lex();
            val = expr();
            //ptr->value = val;
            vars[var_name] = val;
        } else {
            //val = ptr->value;
            val = vars[var_name];
        }
    } else { // 既不是数字也不是'(', 也不是标识符
        //fprintf(stderr, "unkown charactor: %c\n", next_token.u.op);
        //exit(1);
    }
    return val;
}

int main() {
    while (true) {
        lex();
        if (next_token.type == UNKOWN && next_token.u.op == EOF) break;

        printf("%d\n", expr());

        //if (next_token.type != SEPARATOR || next_token.u.op != ';' ) {
        //    fprintf(stderr, "未以\';\'结尾\n");
        //    break;
        //}
    }
    return 0;
}
