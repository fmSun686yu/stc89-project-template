# 工程文件夹命名的含义与目的

|文件夹     |全称含义|在工程中的角色|
|:---------:|:---:|:---:|
|app		|Application Layer			   |应用层，负责主程序、业务逻辑|
|bsp		|Board Support Package         |板级支持包，负责外设引脚映射、板级初始化和模块封装|
|hal		|Hardware Abstraction Layer    |硬件抽象层（驱动层），屏蔽底层复杂硬件细节|
|core		|System Core Layer			   |系统核心层（中断、时钟、延时、系统初始化）|
|config		|Configuration				   |全局配置（宏定义、参数设置、类型定义）|
|startup    |Startup Code				   |启动文件（汇编启动代码、向量表）|
|listings   |Listings                      |用于存放列表文件（.lst文件）（编译过程的详细输出记录），对程序调试和优化非常有帮助|
|output		|Output Files				   |工程编译生成的 `.hex`、`.bin`、`.lst` 等文件|
|docs       |Documentation                 |存放工程的所有文档资料|