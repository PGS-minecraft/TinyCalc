#include<iostream>
#include<string>
#include<cstring>
using namespace std;
static double last_result=0.0, operation_count=0.0, error_operation_count=0.0; //声明三个静态全局变量，用于保存上次计算结果、正确计算次数和错误操作次数
void print_result(double result) //定义一个函数来打印计算结果
{
    cout<<result<<endl<<"------"<<endl;
}
void process_expression(const string &input) //定义一个函数来处理计算逻辑
{
    bool consecutive_operators=false; //检查输入字符串中是否存在连续运算符
    for(size_t i=0; i<input.size()-1; i++) //遍历输入字符串
    {
        if(strchr("+-*/", input[i]) && strchr("+-*/", input[i+1])) //如果找到连续运算符，则设置标志为true
        {
            consecutive_operators=true;
            break;
        }
    }
    size_t pos=input.find_first_of("+-*/#"); //查找输入字符串中的运算符
    double num1, num2; //定义double类型的变量
    char ops; //定义char类型的变量
    if((pos==string::npos || input.size()<=pos+1) || (input[pos]=='#' && (input.size()<=pos+2 || !strchr("+-*/", input[pos+1]) || input[0]!='#')) || consecutive_operators) //如果未找到运算符或无法构成合法的表达式，或者'#'无法包含完整的后续运算符和数字，或者后面紧跟着的不是四则运算符，或者有连续的运算符，则输出错误提示
    {
        cout<<"未知字符 或 格式错误，请重新输入"<<endl<<"--------"<<endl; //输出错误提示和分隔线
        error_operation_count++; //错误操作次数+1
        return;
    }
    else if(input[pos]=='#') //如果找到了"#"，并且格式正确，那么将引用上一次的结果
    {
        num1=last_result; //将上一次计算结果赋值给num1
        ops=input[pos+1]; //获取运算符
        num2=stod(input.substr(pos+2)); //从后两位开始，将字符串转换为double类型并赋值给num2
    }
    else //如果没有找到"#"，那么将进行正常运算
    {
        num1=stod(input.substr(0, pos)); //从输入的字符串中提取第一个数字
        ops=input[pos]; //从输入的字符串中提取运算符
        num2=stod(input.substr(pos+1)); //从输入的字符串中提取第二个数字
    }
    switch(ops) //根据运算符进行相应的计算
    {
        case '+':
            last_result=num1+num2; //计算加法结果并赋值给静态全局变量
            operation_count++; //正确计算次数+1
            break;
        case '-':
            last_result=num1-num2; //计算减法结果并赋值给静态全局变量
            operation_count++; //正确计算次数+1
            break;
        case '*':
            last_result=num1*num2; //计算乘法结果并赋值给静态全局变量
            operation_count++; //正确计算次数+1
            break;
        case '/':
            if(num2==0) //如果除数是零，则输出错误提示
            {
                cout<<"除数不能为零，请重新输入"<<endl<<"--------"<<endl;
                error_operation_count++; //错误操作次数+1
                return;
            }
            else
            {
                last_result=num1/num2; //计算除法结果并赋值给静态全局变量
                operation_count++; //正确计算次数+1
            }
            break;
    }
    print_result(last_result);
}
void full_out()
{
    double num1, num2;
    char ops;
    cin>>num1>>ops>>num2;
    switch(ops) //根据运算符进行相应的计算
    {
        case '+':
            printf("%lf", num1+num2); //输出加法结果
            operation_count++; //正确计算次数+1
            break;
        case '-':
            printf("%lf", num1-num2); //输出减法结果
            operation_count++; //正确计算次数+1
            break;
        case '*':
            printf("%lf", num1*num2); //输出乘法结果
            operation_count++; //正确计算次数+1
            break;
        case '/':
            if(num2==0) //如果除数是零，则输出错误提示
            {
                cout<<"除数不能为零，请重新输入"<<endl<<"--------"<<endl;
                error_operation_count++; //错误操作次数+1
                return;
            }
            else
            {
                printf("%lf", num1/num2); //输出除法结果
                operation_count++; //正确计算次数+1
            }
            break;
    }
    cout<<endl<<"--------"<<endl;
}
int main()
{
    string input; //用户输入的字符串
    while(true)
    {
        getline(cin, input); //从标准输入获取一行字符串
        if(input.empty()) //如果用户输入空字符串，则提示用户进行输入
        {
            if(operation_count==0.0) //如果计算次数为零，则清空屏幕再进行输出，避免多次输出
                system("cls");
            cout<<
            "请输入一个算术表达式[或命令]\n"
            "你也可以输入“help”查看帮助信息\n"
            "--------\n";
            continue;
        }
        if(input=="/check" || input=="/clear" || input=="/help" || input=="/full" || input=="/end" || input=="/exit")
        {
            if(input=="/check") //如果用户输入"/check"，则输出上次计算结果
            {
                if(operation_count==0.0)
                {
                    cout<<"你还未进行任何计算"<<endl<<"--------"<<endl; //如果上次计算结果为零，则输出提示
                    continue;
                }
                else
                {
                    cout<<"上次计算结果为 ["<<last_result<<"]"<<endl;
                    cout<<"正确计算次数为 ["<<operation_count<<"]"<<endl;
                    cout<<"错误操作次数为 ["<<error_operation_count<<"]"<<endl<<"--------"<<endl;
                    continue;
                }
            }
            else if(input=="/clear") //如果用户输入"/clear"，则清空输入记录和屏幕
            {
                system("cls");
                last_result=0.0, operation_count=0.0;
                continue;
            }
            else if(input=="/full") //如果用户输入"/full"，则输出完整计算结果
            {
                cout<<"请输入一个算术表达式"<<endl;
                full_out();
                continue;
            }
            else if(input=="/help") //如果用户输入"/help"，则输出帮助信息
            {
                cout<<
                    "输入“[第1串数字][运算符号][第2串数字]”以开始运算，可输入“#”连续运算\n"
                    "\n"
                    "TinyCalc 所有可用命令[区分大小写]\n"
                    "[/check] 输出上次计算结果\n"
                    "[/clear] 清除所有输入记录\n"
                    "[/full] 可使较大数完整输出，但此模式不支持连续运算\n"
                    "[/help] 查看帮助信息\n"
                    "[/end] 或 [/exit] 结束并退出程序\n"
                    "--------\n";
                continue;
            }
            else if(input=="/end" || input=="/exit") //如果用户输入"/end"或"/exit"，则退出循环
                break;
        }
        try
        {
            process_expression(input);
        }
        catch (const invalid_argument& e) //处理转换字符串到double时的异常
        {
            cout<<"未知字符 或 格式错误，请重新输入"<<endl<<"--------"<<endl; //输出错误提示和分隔线
            error_operation_count++; //错误操作次数+1
        }
    }
    return 0;
}