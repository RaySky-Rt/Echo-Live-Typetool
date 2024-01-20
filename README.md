# Echo-Live-Typetool

使用C++编写的一个输入工具，适用于[Echo-Live](https://github.com/sheep-realms/Echo-Live)

>~~由于Echo-Live 1.2.1 更新后可以直接使用Echo-Live自带的编辑器发送并刷新消息，本工具将停止更新，并且不再适用于最新版本的Echo-Live（~~ 

>或许还可以在B站直播姬上用...总之还是继续更新吧（



## 这是什么？

Echo-Live-Typetool是一个使用C++编写的控制台程序，你可以在此程序里直接输入你想要在Echo-Live里显示的文本，而不必自己每次手动更改start.js，相对更加方便（大概？


## 如何使用？

- ### 首先...确保你的Echo-Live设置正确！

    在Echo-Live的config.js中

    将 **启用广播** 这项设置为 **关闭**

    `broadcast_enable: false`

    然后把 **消息轮询** 这项设置为 **开启**

    `messages_polling_enable: true`

- ### 然后...安装它！

    将 `Echo-Live-Typetool.zip` 解压到 `echo-live-x.x.x/extentions/` 目录下，安装就此完成 ~~（很简单对吧，反正这也不是什么正经插件，所以不用正经导入（划掉）~~

- ### 最后就是...运行程序！
    #### 方法一：使用launch.bat启动（推荐）

    切换到解压好的 `Echo-Live-Typetool/` 目录下，双击launch.bat来运行程序

    #### 方法2：使用命令行启动（备选）

    一般情况下推荐使用launch.bat启动程序，不过当你启动或是使用出现问题时，也可以尝试直接使用命令行启动程序 ~~虽然这两者本质上应该没什么区别~~

    在CMD或PowerShell中切换到Echo-Live-Typetool.exe所在的目录，然后输入以下命令

    `.\Echo-Live-Typetool.exe`

    #### 方法3：直接双击启动Echo-Live-Typetool.exe (¿)

    ~~我们没有这种方法~~ 
    
    好吧如果你头铁的话可以试一试，不过大概率会出现显示乱码或者什么别的奇怪错误 
    
    **不要直接双击运行，会出大问题的（**

## 注意事项

### **1.** 检查你的终端编码

如果使用命令行启动，请确保你的终端编码为UTF-8，否则在输入中文时可能会出现乱码或者导致未知错误

### **2.** 关于指令系统


输入时以斜杠`/`开头，程序就会将其识别成一段指令

~~有点类似mc的指令~~

详细信息请参见[指令列表](https://github.com/RaySky-Rt/Echo-Live-Typetool/blob/master/COMMANDS.md)

### **3.** 富文本输入

Echo-Live-Typetool现在只支持纯文本，暂不支持富文本输入

## 有其他问题或者建议？

请先在已有的issue中查找，看看能否找到解决方法

如果没有，请创建一个新Issue，作为一位在校大学新牲我会及时查看并协助你解决问题，或者采纳建议（

( P.S. Issue模板施工中... ... )
