#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>
#include "funcs.h"

using json = nlohmann::ordered_json;
using namespace std;

int main() {

    refreshConsole(); // 启动之后先清个屏 (
    read_configs(); //读取一下配置文件

    current_config_name=default_config_name;
    current_config=configs[current_config_name]; // 读取当前的用户配置 (相当于从config里拷贝了用户配置的副本出来
    switch_to_config(current_config); // 切换到当前的用户配置(副本)
    
    ifstream iFile("start.js");
    
    if (!iFile.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    iFile >> start;

    while (true) {
        userInput=""; // 清空userInput

        cout << '[' << current_config_name << ']' << "请输入文本...?: " ;

        getline(cin, userInput);

        if(userInput[0]=='/'){// 指令
            if(userInput=="/exit"){
                break;
            }else if(userInput[0]=='/'&&userInput[1]=='/'){ //如果输入是两个斜杠就转义为一个斜杠，不执行指令
                userInput=userInput.substr(1);
            }else{
                command_execute(userInput);
            }
        }else{
            output(userInput);
            if(current_config["loop_mode"]=="true"){
                printSpeed="10086";
                do{
                    userInput.push_back('_');
                    this_thread::sleep_for(chrono::milliseconds(500));
                    output(userInput);
                    userInput.pop_back();
                }while(getline(cin, userInput));
            }
        }
    }
    
    iFile.close();
    return 0;
}

