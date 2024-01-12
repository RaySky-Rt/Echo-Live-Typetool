#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

void refreshConsole(); //清屏
void command_execute(string command); //执行指令
void read_config(); //读取配置文件
void show_commandlist(); //输出指令列表
string getcommand(string a); //解析指令

//上述写好的几个函数暂未正式投入使用（
string username;
int main() {
    string commandlist[101],userInput;
    ofstream file("start.js", ios::out);

    if (!file.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    cout<<"欢迎使用！请输入想要显示的用户名~"<<endl;
    getline(cin, username);

    while (true) {
        userInput=""; //清空userInput

        cout << "请输入文本...？ (输入exit退出程序): ";

        getline(cin, userInput);

        if (userInput=="exit") {

            break;

        }else if(userInput[0]=='/'){//指令

            command_execute(userInput);

        }else{
        file.open("start.js", ios::out | ios::trunc);
        file << "echolive.send({\n"
             "    \"username\": \"" << username << "\", \n"
             "    \"messages\": [\n"
             "        {\n"
             "            \"message\": \"" << userInput << "\",\n"
             "            \"data\": {\n"
             "                \"printSpeed\": \"30\"\n"
             "            }\n"
             "        }\n"
             "    ]\n"
             "});\n";
        file.close();
        cout << "文本消息发送成功！\n";
        }
    }
    
    file.close();
    return 0;
}

void refreshConsole(){
    system("cls"); //控制台清屏（Windows平台）
}

void command_execute(string userInput){
    string command;
    command=getcommand(userInput);
    if(command=="name"){
        string input;
        input=userInput.substr(6);
        username=input;
        cout<<"已将说话人名称改为"<<username<<endl;
        return;
    }else if(command=="clear"){
        refreshConsole();
        return;
    }
    return;
}

void read_config(){

}

void show_commandlist(){

}

string getcommand(string userInput){
    string command;
    size_t input_size;
    size_t spacePos = userInput.find(' ', 1); //找到指令后第一个空格的位置
    input_size=userInput.size();
    if (spacePos != string::npos) {
        command = userInput.substr(1, spacePos-1);
            return command;
        }else{
            command = userInput.substr(1);
            return command; //没检测到指令的参数，斜杠后的文本即为指令，直接返回
        }
    return command;
}
