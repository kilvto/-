1. 功能设计
1.1 核心功能
四则运算：支持 +, -, *, / 运算。
括号优先级：支持 () 改变运算顺序。
负数运算：支持 - 作为负号（如 -1 + 2）。
记忆功能：支持 MS（存储）、MR（读取）、MC（清除）、M+（累加）、M-（累减）。
清零功能：C 命令清零当前结果。
退出功能：exit 命令退出程序。
1.2 输入格式
支持输入 数学表达式（如 1+2*(3-4)）。
支持输入 命令（如 MS、MR、exit）。
！！！注意：所有字符间均不叫空格，输入运算式后键入回车开始运算。！！！
1.3 输出格式
计算结果：结果: 1.0000000
错误提示：错误：缺少右括号 ')'
2. 详细设计
2.1 程序架构
main()
输入处理（fgets）
命令解析（C/MS/MR/MC/M+/M-/exit）
计算逻辑（suan1/suan2/suan3）
2.2 计算逻辑（递归下降解析器）
suan1() → 处理 +, -
suan2() → 处理 *, /
suan3() → 处理 (), -, 数字
 '(' → 递归 suan1()
 '-' → 递归 suan3()
数字 → strtod() 转换
循环处理 *, /
循环处理 +, -
2.4 关键代码解析
(1) 输入处理
fgets(input, sizeof(input), stdin);  
使用 fgets 防止缓冲区溢出。
for(int i=0;i<666;i++){
			if(input[i]=='\n'){ 
				input[i]='\0';
				break;}}
字符串尾的‘\n’转换为‘\0’，以保证指令（‘C’）能正常被读取。
(2) 命令解析
if (strcmp(input, "C") == 0) {
    result = 0;
    printf("结果已清零\n");
    continue;
}
支持 C（清零）、MS（存储）、MR（读取）等命令。
(3) 计算逻辑
double suan3() {
    if (pack(locate) == '(') {
        locate++;
        double result = suan1();  // 递归计算括号内
        if (pack(locate) != ')') {
            printf("错误：缺少右括号 ')'\n");
            exit(1);
        }
        locate++;
        return result;
    }
    else if (pack(locate) == '-') {
        locate++;
        return -suan3();  // 处理负数
    }
    else if (isdigit(pack(locate))) {
        char *end;
        double result = strtod(input + locate, &end);
        locate = end - input;
        return result;
    }
    else {
        printf("错误：非法字符 '%c'\n", pack(locate));
        exit(1);
    }
}
suan3() 处理 ()、-、数字。
suan2() 处理 *、/（优先级高于 +、-）。
suan1() 处理 +、-（最低优先级）。
