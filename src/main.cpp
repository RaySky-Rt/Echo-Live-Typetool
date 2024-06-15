#include <iostream>
#include "funcs.h"
#include <nlohmann/json.hpp>
#include <locale.h>

using json = nlohmann::ordered_json;
using namespace std;

int main() {
    setlocale(LC_ALL, "");
    initialize();

    current_config_name=default_config_name; // 获取默认配置的名称
    current_config=configs[current_config_name]; // 读取当前的用户配置 (相当于从config里拷贝了用户配置的副本出来
    switch_to_config(current_config); // 切换到当前的用户配置(副本)
    
    ifstream iFile("../../start.js");
    
    if (!iFile.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        palse();
        return 1;
    }
    
    // // 检查文件是否为空 //似乎不需要
    // if (iFile.peek() == ifstream::traits_type::eof()) {
    //     cerr << "文件 start.js 为空" << endl;
    // }
    printw("[%s]\n", current_config_name.c_str());
    int cursor_pos = 0; // 初始化光标位置

    while((userchar = getch()) != 27) { // Esc键退出

        if(!userInput.empty() && userInput[0] == '/' && userchar == '\t'){// 当识别到指令的时候按下Tab键触发自动补全
            string completed = autoComplete(getcommand(userInput));
            userInput += completed;
            cursor_pos = userInput.length();
            move(getcury(stdscr), 0);
            clrtoeol();
            printw("%s", userInput.c_str());
        }else if(userchar == '\n'){
            if(!userInput.empty() && userInput[0] == '/'){
                command_execute(userInput);
                userInput="";
            }else if(!userInput.empty()){
                output(userInput);
                userInput="";
            }
            cursor_pos = 0;
            move(getcury(stdscr), 0);
            clrtoeol();
        }else if(userchar == '\b' || userchar == KEY_BACKSPACE || userchar == 127){
            if (cursor_pos > 0) {
                userInput.erase(cursor_pos - 1, 1);
                cursor_pos--;
                move(getcury(stdscr), 0);
                clrtoeol();
                printw("%s", userInput.c_str());
                move(getcury(stdscr), cursor_pos);
            }
        }else if(userchar == KEY_LEFT){
            if (cursor_pos > 0) {
                cursor_pos--;
                move(getcury(stdscr), cursor_pos);
            }
        }else if(userchar == KEY_RIGHT){
            if (cursor_pos < userInput.length()) {
                cursor_pos++;
                move(getcury(stdscr), cursor_pos);
            }
        }else{
            userInput.insert(cursor_pos, 1, static_cast<char>(userchar));
            cursor_pos++;
            move(getcury(stdscr), 0);
            clrtoeol();
            printw("%s", userInput.c_str());
            move(getcury(stdscr), cursor_pos);
        }
        refresh();  // 刷新屏幕显示

    }

    endwin();  // 结束pdcurses屏幕

    iFile.close();
    return 0;
}

