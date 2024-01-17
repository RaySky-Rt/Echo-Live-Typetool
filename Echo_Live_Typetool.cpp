#include <iostream>
#include <fstream>
#include <conio.h>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

void refreshConsole(); // 清屏
void command_execute(string command); // 执行指令
void read_config(); // 读取配置文件
void write_config(); // 写入配置文件
void show_commandlist(); // 输出指令列表
string getcommand(string a); // 解析指令

//一些全局变量↓
string username="",prefix="",suffix="",printSpeed="30";
json config;


int main() {
    string userInput;

    read_config();

    ofstream file("../../start.js", ios::out);
    if (!file.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    while (true) {
        userInput=""; // 清空userInput

        cout << "请输入文本...？: ";

        getline(cin, userInput);

        if(userInput[0]=='/'){// 指令
            if(userInput=="/exit"){
                break;
            }else{
                command_execute(userInput);
            }

        }else{
        file.open("../../start.js", ios::out | ios::trunc);
        file << "echolive.send({\n"
             "    \"username\": \"" << username << "\", \n"
             "    \"messages\": [\n"
             "        {\n"
             "            \"message\": \"" << prefix << userInput << suffix << "\",\n"
             "            \"data\": {\n"
             "                \"printSpeed\": \"" << printSpeed << "\"\n"
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
    system("cls"); // 控制台清屏（仅限Windows平台）
}

void command_execute(string userInput){
    string command;
    command=getcommand(userInput);
    
    if(command=="name"){
        string input;
        if(userInput.size()<=6){
            input.clear();
            username=input;
            cout<<"已设置为无说话人"<<endl;
        }else{
            input=userInput.substr(6);
            username=input;
            cout<<"已将说话人名称改为"<<username<<endl;
        }
        write_config();
        read_config();
        return;
    }else if(command=="clear"){
        refreshConsole();
        return;
    }else if(command=="prefix"){
        string input;
        if(userInput.size()<=8){
            input.clear();
            prefix=input;
            cout<<"已清除前引用符号"<<endl;
        }else{
            input=userInput.substr(8);
            if(input=="\""){
                prefix="\\\"";
                cout<<"已将前引用符号改为"<<"\""<<endl;
            }else{
                prefix=input;
                cout<<"已将前引用符号改为"<<prefix<<endl;
            }
        }
        write_config();
        read_config();
    }else if(command=="suffix"){
        string input;
        if(userInput.size()<=8){
            input.clear();
            suffix=input;
            cout<<"已清除后引用符号"<<endl;
        }else{
            input=userInput.substr(8);
            if(input=="\""){
                suffix="\\\"";
                cout<<"已将后引用符号改为"<<"\""<<endl;
            }else{
                suffix=input;
                cout<<"已将后引用符号改为"<<suffix<<endl;
            }
        }
        write_config();
        read_config();
    }else if(command=="printspeed"){
        string input;
        if(userInput.size()<=12){
            cout<<"参数不存在，请重试"<<endl;
        }else{
            input=userInput.substr(12);
            printSpeed=input;
            cout<<"已将打印速度设置为"<<printSpeed<<endl;
        }
        write_config();
        read_config();
    }else if(command=="readconfig"){
        read_config();
        cout<<"配置文件读取成功！"<<endl;
        return;
    }else{
        cout<<"无效指令，请重试！"<<endl;
        return;
    }

    return;
}

void read_config(){

    ifstream configFile("typetool_config.json");
    if (!configFile.is_open()) {
        cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }
    // 读取文件内容到 JSON 对象
    configFile >> config;
    // 关闭文件
    configFile.close();
    // 检查是否成功读取配置
    if (config.empty()) {
        cerr << "配置文件为空或格式错误\n";
        return;
    }

    if (config["username"].type() == json::value_t::string) {
        username = config["username"];
    }
    if (config["prefix"].type() == json::value_t::string) {
        prefix = config["prefix"];
    }
    if (config["suffix"].type() == json::value_t::string) {
        suffix = config["suffix"];
    }
    if (config["printSpeed"].type() == json::value_t::string) {
        printSpeed = config["printSpeed"];
    }

    return;
}

void write_config(){

    config["username"] = username;
    config["prefix"] = prefix;
    config["suffix"] = suffix;
    config["printSpeed"] = printSpeed;

    ofstream configFile("typetool_config.json");

    if (!configFile.is_open()) {
        cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }

    configFile << setw(4) << config << endl;
    configFile.close();

    return;
}

void show_commandlist(){
    // 还没写，这个函数真的用得上吗（
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
