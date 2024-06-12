#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

//functions

void refreshConsole(); // 清屏（目前仅Windows
void palse(); //暂停程序
void initialize(); //初始化
void output(std::string userInput); // 这个函数用于将json start中的数据写入start.json
void command_execute(std::string userInput); // 执行指令
void read_configs(); // 读取配置文件 (包含所有的用户配置)
void write_config(json current_config); // 写入当前用户配置
void switch_to_config(json current_config); // 切换用户配置
void show_commandlist(); // 输出指令列表 (没写，但是占个位
void prefill(); // 预填充start 防止意外
std::string gettheme(); //读取主题配置（没写完但是占个位
std::string getcommand(std::string a); // 解析指令


//global variables

extern std::string userInput;
//(现在看来default_config_name似乎有点冗余了，在考虑要不要删掉
extern std::string username, prefix, suffix, printSpeed, current_theme_name, default_theme_name, loop_mode, current_config_name, default_config_name; 
//configs:完整的配置文件，其中包含所有的用户配置 | current_config:当前用户配置
extern json configs, start, current_config;


#endif // FUNCS_H