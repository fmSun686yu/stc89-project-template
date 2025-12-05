# bsp 文件夹 ——— Board Support Package（板级支持包）

## 目的：
让软件适配你使用的具体电路板（硬件平台）。

## 放什么内容？
|内容            |示例文件|
|:-------------:|:------:|
|引脚定义        |`pin_config.h`|
|时钟配置        |`clock.c` <br> `clock.h`|
|GPIO初始化      |`gpio.c`|
|芯片型号相关配置 |`stc15_config.h`|			