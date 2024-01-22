#include <iostream>
#include <fstream>
#include <conio.h>
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

void refreshConsole(); // 清屏
void command_execute(string command); // 执行指令
void read_configs(); // 读取配置文件 (包含所有的用户配置)
void write_config(json current_config); // 写入当前用户配置
void switch_to_config(json current_config); // 切换用户配置
void show_commandlist(); // 输出指令列表 (没写，但是占个位
string getcommand(string a); // 解析指令

// 一些全局变量↓
string username="",prefix="",suffix="",printSpeed="30";
string current_config_name="",default_config_name=""; // 当前用户配置的名称   默认用户配置的名称  (现在看来default_config_name似乎有点冗余了，在考虑要不要删掉
json configs; // 完整的配置文件，其中包含所有的用户配置
json current_config; // 当前用户配置
int main() {

    refreshConsole(); // 启动之后先清个屏 (

    string userInput;

    read_configs();

    current_config_name=default_config_name;

    current_config=configs[current_config_name]; // 读取当前的用户配置 (相当于从config里拷贝了用户配置的副本出来
                                                
    switch_to_config(current_config); // 切换到当前的用户配置(副本)

    ofstream file("../../start.js", ios::out);
    if (!file.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    while (true) {
        userInput=""; // 清空userInput

        cout << '[' << current_config_name << ']' << "请输入文本...?: " ;

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
        write_config(current_config);
        read_configs();
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
        write_config(current_config);
        read_configs();
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
        write_config(current_config);
        read_configs();
    }else if(command=="printspeed"){
        string input;
        if(userInput.size()<=12){
            cout<<"参数不存在，请重试"<<endl;
        }else{
            input=userInput.substr(12);
            printSpeed=input;
            cout<<"已将打印速度设置为"<<printSpeed<<endl;
        }
        write_config(current_config);
        read_configs();
    }else if(command=="readconfig"){
        if(userInput.size()<=12){
            read_configs();
            cout<<"配置文件读取成功!"<<endl;
        }else{
            string input;
            input=userInput.substr(12);
            if (configs.contains(input) && configs[input].is_object()){ // 判断要切换到的用户配置名称是否存在
                current_config_name=input;

                current_config=configs[current_config_name];
                switch_to_config(current_config);

                cout<<"配置文件成功切换至 "<<current_config_name<<" !"<<endl;
            }else{
                cerr<<"未找到名为"<<input<<"的用户配置，请重试"<<endl;
            }
            
        }
        
        return;
    }else{
        cerr<<"无效指令，请重试!"<<endl;
        return;
    }

    return;
}

void read_configs(){

    ifstream configFile("typetool_config.json");
    if (!configFile.is_open()) {
        cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }
    // 读取文件内容到 JSON 对象
    configFile >> configs;
    
    // 读取默认用户配置
    if (configs["default_config"].type() == json::value_t::string) {
        if(configs.contains(configs["default_config"]) && configs[configs["default_config"]].is_object()){
            default_config_name = configs["default_config"];
        }else{
            cerr << "不存在名为" << configs["default_config"] << "的默认用户配置，请检查 typetool_config.json 中 default_config 一项是否有误并重启程序" << endl;
        }
    }

    // 关闭文件
    configFile.close();

    // 检查是否成功读取配置
    if (configs.empty()) {
        cerr << "配置文件为空或格式错误!\n";
        return;
    }

    return;
}

void write_config(json current_config){ // 这个函数写的太屎山了，回头一定要改(

    json& write=configs[current_config_name]; // write是对config中当前用户配置的引用，方便直接修改写入

    current_config["username"] = username; // 先进行一遍读取
    current_config["prefix"] = prefix;
    current_config["suffix"] = suffix;
    current_config["printSpeed"] = printSpeed;

    write=current_config; // 相当于直接修改了config里对应的用户配置

    ofstream configFile("typetool_config.json");

    if (!configFile.is_open()) {
        cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }

    configFile << setw(4) << configs << endl;
    configFile.close();

    return;
}

void switch_to_config(json current_config){

    if (current_config["username"].type() == json::value_t::string) {
        username = current_config["username"];
    }
    if (current_config["prefix"].type() == json::value_t::string) {
        prefix = current_config["prefix"];
    }
    if (current_config["suffix"].type() == json::value_t::string) {
        suffix = current_config["suffix"];
    }
    if (current_config["printSpeed"].type() == json::value_t::string) {
        printSpeed = current_config["printSpeed"];
    }
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
