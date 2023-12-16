#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream file("start.js", ios::out);

    if (!file.is_open()) {
        cerr << "无法打开start.js，请检查start.js是否被其他程序占用\n";
        return 1;
    }

    while (true) {
        string a;

        cout << "请输入文本...？ (输入\"exit\"来退出程序): ";
        getline(cin, a);

        if (a == "exit") {
            break;
        }
        file.open("start.js", ios::out | ios::trunc);
        file << "const data = {\n"
             "    \"username\": \".\", \n"
             "    \"messages\": [\n"
             "        {\n"
             "            \"message\": \"" << a << "\",\n"
             "            \"data\": {\n"
             "                \"printSpeed\": \"30\"\n"
             "            }\n"
             "        }\n"
             "    ]\n"
             "}\n";
        file.close();
        cout << "文本更新完成！\n";
    }
    
    file.close();
    return 0;
}
