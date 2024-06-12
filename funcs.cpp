#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>
#include "funcs.h"
using json = nlohmann::ordered_json;

std::string userInput;
std::string username="",prefix="",suffix="",printSpeed="30",current_config_name="",default_config_name="";
json configs,start,current_config; 

void refreshConsole(){
    system("cls"); // 控制台清屏（仅限Windows平台）
}

void initialize(){
    
}

void output(std::string userInput){
    std::ofstream oFile("start.js");

    if(current_theme()=="terminal_like"){ //terminal_like主题
        start["username"]=username;
        start["message"]=prefix+userInput+suffix;
        start["printSpeed"]=printSpeed;
        start["message"]=userInput;
        current_config["loop_mode"]=="true";

        oFile << "const data = " << start.dump(4) << ";" << std::endl;

        std::cout << "文本消息发送成功！\n";
    }else{ //默认主题
        start["username"]=username;
        start["message"]=prefix+userInput+suffix;
        start["printSpeed"]=printSpeed;
        start["message"]=userInput;
        current_config["loop_mode"]=="false";

        oFile << "const data = " << start.dump(4) << ";" << std::endl;

        std::cout << "文本消息发送成功！\n";
    }

    oFile.close();
}

void command_execute(std::string userInput){
    std::string command;
    command=getcommand(userInput);
    
    if(command=="name"){
        std::string input;
        if(userInput.size()<=6){
            input.clear();
            username=input;
            std::cout<<"已设置为无说话人"<<std::endl;
        }else{
            input=userInput.substr(6);
            username=input;
            std::cout<<"已将说话人名称改为"<<username<<std::endl;
        }
        write_config(current_config);
        read_configs();
        return;
    }else if(command=="clear"){
        refreshConsole();
        return;
    }else if(command=="prefix"){
        std::string input;
        if(userInput.size()<=8){
            input.clear();
            prefix=input;
            std::cout<<"已清除前引用符号"<<std::endl;
        }else{
            input=userInput.substr(8);
            if(input=="\""){
                prefix="\\\"";
                std::cout<<"已将前引用符号改为"<<"\""<<std::endl;
            }else{
                prefix=input;
                std::cout<<"已将前引用符号改为"<<prefix<<std::endl;
            }
        }
        write_config(current_config);
        read_configs();
    }else if(command=="suffix"){
        std::string input;
        if(userInput.size()<=8){
            input.clear();
            suffix=input;
            std::cout<<"已清除后引用符号"<<std::endl;
        }else{
            input=userInput.substr(8);
            if(input=="\""){
                suffix="\\\"";
                std::cout<<"已将后引用符号改为"<<"\""<<std::endl;
            }else{
                suffix=input;
                std::cout<<"已将后引用符号改为"<<suffix<<std::endl;
            }
        }
        write_config(current_config);
        read_configs();
    }else if(command=="printspeed"){
        std::string input;
        if(userInput.size()<=12){
            std::cout<<"参数不存在，请重试"<<std::endl;
        }else{
            input=userInput.substr(12);
            printSpeed=input;
            std::cout<<"已将打印速度设置为"<<printSpeed<<std::endl;
        }
        write_config(current_config);
        read_configs();
    }else if(command=="readconfig"){
        if(userInput.size()<=12){
            read_configs();
            std::cout<<"配置文件读取成功!"<<std::endl;
        }else{
            std::string input;
            input=userInput.substr(12);
            if (configs.contains(input) && configs[input].is_object()){ // 判断要切换到的用户配置名称是否存在
                current_config_name=input;

                current_config=configs[current_config_name];
                switch_to_config(current_config);

                std::cout<<"配置文件成功切换至 "<<current_config_name<<" !"<<std::endl;
            }else{
                std::cerr<<"未找到名为"<<input<<"的用户配置，请重试"<<std::endl;
            }
            
        }
        
        return;
    }else{
        std::cerr<<"无效指令，请重试!"<<std::endl;
        return;
    }

    return;
}

void read_configs(){

    std::ifstream configFile("typetool_config.json");
    if (!configFile.is_open()) {
        std::cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }
    // 读取文件内容到 JSON 对象
    configFile >> configs;
    
    // 读取默认用户配置
    if (configs["default_config"].type() == json::value_t::string) {
        if(configs.contains(configs["default_config"]) && configs[configs["default_config"]].is_object()){
            default_config_name = configs["default_config"];
        }else{
            std::cerr << "不存在名为" << configs["default_config"] << "的默认用户配置，请检查 typetool_config.json 中 default_config 一项是否有误并重启程序" << std::endl;
        }
    }

    // 关闭文件
    configFile.close();

    // 检查是否成功读取配置
    if (configs.empty()) {
        std::cerr << "配置文件为空或格式错误!\n";
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

    std::ofstream configFile("typetool_config.json");

    if (!configFile.is_open()) {
        std::cerr << "无法打开配置文件 typetool_config.json\n";
        return;
    }

    configFile << std::setw(4) << configs << std::endl;
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

std::string current_theme(){ //读取主题配置
    return current_config["theme"];
}

std::string getcommand(std::string userInput){
    std::string command;
    size_t input_size;
    size_t spacePos = userInput.find(' ', 1); //找到指令后第一个空格的位置
    input_size=userInput.size();
    if (spacePos != std::string::npos) {
        command = userInput.substr(1, spacePos-1);
            return command;
        }else{
            command = userInput.substr(1);
            return command; //没检测到指令的参数，斜杠后的文本即为指令，直接返回
        }
    return command;
}

