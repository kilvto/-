#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char input[666];
int locate = 0;   // 解析位置
char pack(int n) {
	return input[n];
}
double suan1();//最低优先级运算
double suan2();//次等优先级运算
double suan3();//最高优先级运算（打括号，负值，数字转化）
int main(int argc, char *argv[]) {
	double result = 0, memory = 0;
	while (1) {
		printf("输入表达式（或命令 exit/C/MS/MR/MC/M+/M-）：");
		fgets(input, sizeof(input), stdin);//编译器说gets()is always unsafe，让我换成fgets
		for (int i = 0; i < 666; i++) {
			if (input[i] == '\n') {
				input[i] = '\0';
				break;
			}
		}  // 去掉换行符,可能不太合适，别无他法

		if (strcmp(input, "exit") == 0) break;
		if (strcmp(input, "C") == 0) {
			result = 0;
			printf("结果已清零\n");
			continue;
		}
		if (strcmp(input, "MS") == 0) {
			memory = result;
			printf("记忆已存储: %.7f\n", memory);
			continue;
		}
		if (strcmp(input, "MR") == 0) {
			result = memory;
			printf("记忆已调用: %.7f\n", result);
			continue;
		}
		if (strcmp(input, "MC") == 0) {
			memory = 0;
			printf("记忆已清除\n");
			continue;
		}
		if (strcmp(input, "M+") == 0) {
			memory += result;
			printf("记忆值: %.7f\n", memory);
			continue;
		}
		if (strcmp(input, "M-") == 0) {
			memory -= result;
			printf("记忆值: %.7f\n", memory);
			continue;
		}
		locate = 0;
		result = suan1();
		printf("结果: %.7f\n", result);
	}
	return 0;
}
double suan3() {
	double result;
	if (pack(locate) == '(') {
		locate++;
		result = suan1(); //从括号里面开始递归
		if (pack(locate) != ')') {
			printf("错误：缺少右括号 ')'\n");
			exit(1);
		}//括号完整性检查
		locate++;  // 跳过 ')'
		return result;
	} else if (pack(locate) == '-') {
		locate++;
		result = -suan3(); //从负号后开始递归
		return result;
	} else if (isdigit(pack(locate))) {
		char* end;
		result = strtod(input + locate, &end);//字符—>double
		locate = end - input; //纠正解析位置
		return result;
	} else {
		printf("错误：请输入正确字符");
		exit(1);
	}
}
double suan2() {
	double result = suan3();
	while (pack(locate) == '*' || pack(locate) == '/') {
		char op = pack(locate);
		locate++;
		result = (op == '*') ? result * suan3() : result / suan3();
	}
	return result;
}
double suan1() {
	double result = suan2();
	while (pack(locate) == '+' || pack(locate) == '-') {
		char op = pack(locate);
		locate++;
		result = (op == '+') ? result + suan2() : result - suan2();
	}
	return result;
}
