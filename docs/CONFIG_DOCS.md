# 关于配置文件

Echo-Live-Typetool 支持创建多个相互独立且可以随时切换的用户配置，配置文件名称为 `typetool_config.json` ，使用 json 格式

目前可以调整的配置还很有限，以后的版本中将添加更多的可配置项，调整配置的方式也会尽可能优化的更友好一些，如果您有什么想法或建议，欢迎在项目中提Issue拷打我（

## 示例

下面是一个配置文件的示例：
```json
{
    "default_config": "cfg1",
    "cfg1": {
        "username": "user1",
        "prefix": "-",
        "suffix": "-",
        "printSpeed": "30"
    },
    "cfg2": {
        "username": "user2",
        "prefix": "+",
        "suffix": "+",
        "printSpeed": "40"
    }
}
```

这个配置文件中包含两个用户配置，分别为 `cfg1` 和 `cfg2` ，其中 `default_config` 为程序启动时加载的默认配置，它的键值必须是一个已有的用户配置名，在上面的示例中，它必须是 `cfg1` 或者 `cfg2` 两者中的一个

你也可以根据需要来添加更多的用户配置，示例如下：

```json
{
    "default_config": "cfg1",
    "cfg1": {
        "username": "user1",
        "prefix": "-",
        "suffix": "-",
        "printSpeed": "30"
    },
    "cfg2": {
        "username": "user2",
        "prefix": "+",
        "suffix": "+",
        "printSpeed": "40"
    }, 
    "newconfig": {
        "username": "newuser",
        "prefix": "*",
        "suffix": "*",
        "printSpeed": "50"
    }
}
```

这个示例中我们添加了一个叫 `newconfig` 的用户配置，接下来是对这个用户配置中各个关键字含义的解释

```json
"newconfig": { //用户配置的名称，示例中为newconfig
        "username": "newuser", //Echo-Live中显示的讲述人名字，示例中为newuser，可以为空
        "prefix": "*", //文本开头的引用符号（也可以是一段文本），示例中为 * ，可以为空
        "suffix": "*", //文本末尾的引用符号（也可以是一段文本），示例中为 * ，可以为空
        "printSpeed": "50" //文本打印速度（默认为30），不可为空
    }
```

## 切换用户配置

使用指令 `/readconfig <配置名称>` 来切换当前的用户配置

详细用法及示例请见 [指令列表](https://github.com/RaySky-Rt/Echo-Live-Typetool/blob/master/COMMANDS.md) 