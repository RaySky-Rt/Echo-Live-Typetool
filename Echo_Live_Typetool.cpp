#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

void refreshConsole(); //清屏
void command_execute(string command); //执行指令
void read_config(); //读取配置文件
void show_commandlist(); //输出指令列表
string getcommand(string a); //接收指令

//上述写好的几个函数暂未正式投入使用（

int main() {
    string commandlist[101],userInput,username;
    ofstream file("start.js", ios::out);

    if (!file.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    cout<<"欢迎使用————请输入想要显示的用户名称吧！";
    
    cin>>username;

    while (true) {
        userInput=""; //清空userInput

        cout << "请输入文本...？ (输入exit退出程序): ";

        getline(cin, userInput);

        if (userInput=="exit") {

            break;

        }/*else if(userInput[0]=='/'){//指令

            command_execute(getcommand(userInput));

        }*/else{
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
        cout << "文本更新完成！\n";
        }
    }
    
    file.close();
    return 0;
}

void refreshConsole(){
    system("cls"); //控制台清屏（Windows平台）
}

void command_execute(string command){
    // if(command=="name"){
    //     string input;
    //     cin>>input;
    //     username=input;
    //     cout<<"显示名称更改成功！"<<endl;
    //     return;
    // }
    return;
}

void read_config(){

}

void show_commandlist(){

}

string getcommand(string userInput){
    string command;
    int input_size;
    input_size=userInput.size();
    for(int i=0;i<input_size;i++){
        command[i]=userInput[i+1];
    }
    return command;
}
