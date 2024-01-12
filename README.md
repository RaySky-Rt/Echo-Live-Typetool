# Echo-Live-Typetool

使用C++编写的一个输入工具，适用于[Echo-Live](https://github.com/sheep-realms/Echo-Live)

>~~Echo-Live 1.2.1 更新后可以直接使用Echo-Live自带的编辑器发送并刷新消息，本工具将停止更新，并且不再适用于最新版本的Echo-Live（~~ 

>或许还可以在直播姬上用...总之还是继续更新吧（



## 这是什么？

Echo-Live-Typetool是一个使用C++编写的控制台程序，你可以在此程序里直接输入你想要在Echo-Live里显示的文本，而不必自己每次手动更改start.js，相对更加方便（大概？


## 如何使用？

- ### 首先确保你的Echo-Live设置正确：

    在Echo-Live的config.js中

    将 **启用广播** 这项设置为 **关闭**

    `broadcast_enable: false`

    然后把 **消息轮询** 这项设置为 **开启**

    `messages_polling_enable: true`

- ### 运行程序

    将Echo-Live-Typetool.exe复制到start.js的同一目录下，在cmd或者powershell等终端中使用命令行来启动此控制台程序

    `./Echo-Live-Typetool.exe`

## 注意事项

### **1.**

请确保你的终端编码为UTF-8，否则在输入中文时可能会出现乱码或者导致未知错误

### **2.**
关于指令系统

输入时以斜杠`/`开头，程序就会将其识别成一段指令

~~有点类似mc的指令~~

详细信息请参见[指令列表](https://github.com/RaySky-Rt/Echo-Live-Typetool/blob/master/COMMANDS.md)

### **3.**

Echo-Live-Typetool现在只支持纯文本，暂不支持富文本输入

## 有其他问题或者建议？

请直接在项目中提issue，作为一位在校大学新牲我会及时查看并协助你解决问题，或者采纳建议（
