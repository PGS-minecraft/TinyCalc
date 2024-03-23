#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
void print_result(double result)
{
    cout<<result<<endl<<"--------"<<endl; //输出计算结果和分隔线
}
int main()
{
    string input; //用户输入的字符串
    while(true)
    {
        getline(cin, input); //从标准输入获取一行字符串
        if(input=="end") //如果用户输入"end"，则退出循环
            break;
        size_t pos=input.find_first_of("+-*/"); //查找输入字符串中的第一个运算符
        if(pos==string::npos) //如果没有找到运算符，则提示用户重新输入
        {
            cout<<"未知运算符，请重新输入"<<endl<<"--------"<<endl; //输出提示和分隔线
            continue; //继续下一轮循环，等待用户重新输入正确的运算表达式
        }
        try //分割输入字符串，提取运算数和运算符
        {
            double num1=stod(input.substr(0, pos));
            char cal=input[pos];
            double num2=stod(input.substr(pos+1));
            if(cal=='/' && num2==0) //对于除法，将会检查除数是否为0
            {
                cout<<"除数不能为零"<<endl<<"--------"<<endl; //输出提示和分隔线
                continue; //继续下一轮循环，等待用户重新输入正确的运算表达式
            }
            switch(cal) //根据运算符进行相应的计算并打印结果
            {
                case '+':
                    print_result(num1+num2); //计算加法结果
                    break;
                case '-':
                    print_result(num1-num2); //计算减法结果
                    break;
                case '*':
                    print_result(num1*num2); //计算乘法结果
                    break;
                case '/':
                    print_result(num1/num2); //计算除法结果
                    break;
            }
        }
        catch (const std::invalid_argument& e) //处理转换字符串到double时的异常
        {
            cout<<"未知字符，请重新输入"<<endl<<"--------"<<endl; //输出提示和分隔线
            continue; //继续下一轮循环，等待用户重新输入正确的运算表达式
        }
        catch (const std::out_of_range& e) //处理转换字符串到double时的范围错误异常
        {
            cout<<"格式错误，请重新输入"<<endl<<"--------"<<endl; //输出提示和分隔线
            continue; //继续下一轮循环，等待用户重新输入正确的运算表达式
        }
    }
    return 0;
}