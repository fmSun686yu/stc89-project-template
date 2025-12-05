# startup 文件夹 ——— Startup Code（启动文件（Keil自动生成））

## 发什么内容？
> startup
   └─ startup.a51     // 汇编启动代码

- 单片机上电后执行的第一个程序。
- 负责初始化栈、设置中断入口等。
- 对于51，不需要修改，Keil会自动管理。

## 理解：
startup 是程序的“启动引擎”。