# STC89C51RC/RD+ 系列单片机模块化工程文件及程序模板说明文档
> 本 README 文档用于介绍本工程模板的整体架构、使用方法、目录结构以及开发说明，适用于以 STC89C51RC/RD+ 系列（8051 内核）为核心的模块化软件开发项目。本工程遵循清晰、可维护、可扩展的设计原则，方便长期迭代与团队协作。

## 1. 工程简介
本工程为 STC89C516RD+ 单片机的软件开发模板，采用**模块化 + 分层**结构设计，将核心文件、外设驱动、应用层代码与文档管理进行严格划分，提供统一接口与规范命名方式。本工程文件采用 Visual Studio Code 编写代码 + Keil uVision 5 编译与调试 + STC-ISP 烧录程序的方法进行51单片机软件开发。
### 模板包含：
- 工程目录组织规范
- 常用外设驱动示例（定时器、串口、I2C等）
- 可复用的代码结构与头文件管理模式
- 文档模板与注释规范

### 模板目标：
- 便于代码复用
- 便于多人协作
- 便于项目升级和功能扩展
- 便于系统学习 51 单片机工程结构

### 本工程模板适合：
- 课程设计 / 毕业设计
- 电子竞赛项目
- 工业开发前期工程化模板搭建

## 2. 硬件特性
| 参数                | 规格                                    |
| :-----------------: | :------------------------------------: |
| **内核**            | 增强型8051内核（6T/12T可选）             |
| **工作频率**        | 0-48MHz @12T模式，0-24MHz @6T模式        |
| **Flash程序存储器** | 64KB（可在线编程ISP/IAP）                 |
| **数据存储器**      | 1280字节片内RAM                          |
| **I/O口**           | 39个通用I/O口（P0-P3, P4口）             |
| **定时器**          | 3个16位定时器/计数器（T0/T1/T2）          |
| **串口**            | 增强型UART，支持帧错误检测、地址识别       |
| **中断源**          | 8个中断向量，4级优先级                    |
| **工作电压**        | 5.5V ~ 3.3V（STC89C系列）                |
| **工作温度**        | -40℃ ~ +85℃（工业级）                  |
| **封装**            | PDIP-40, PLCC-44, LQFP-44               |
| **其他特性**        | 双数据指针(DPTR)、看门狗定时器、低功耗模式 |


## 3. 工程目录结构
> STC89C51RC_RD+_Series_Project_Files_and_Program_Template <br>
>  ├── app      // Application, 应用层 <br>
>  ├── bsp      // Board Support Package, 板级支持包 <br>
>  ├── hal      // Hardware Abstraction Layer, 硬件抽象层（驱动层） <br>
>  ├── core     // System Core, 系统核心层 <br>
>  ├── config   // Configuratio, 全局配置 <br>
>  ├── startup  // Startup Code, 启动文件 <br>
>  ├── listings // Listings 文件夹，用于存放列表文件（.lst文件），这些文件是编译过程的详细输出记录，对程序调试和优化非常有帮助 <br>
>  ├── output   // Output Files, 工程编译生成的相关文件 <br>
>  ├── docs     // Documentation, 存放工程的所有文档资料 <br>
>  └──.vscode   // Visual Studio Code 配置文件 <br>

## 4. 核心模块说明
### 延时模块 (delay.h/c)

### 定时器模块 (timer.h/c)

### 中断管理模块 (interrupt.h/c)

### EEPROM 操作模块 (eeprom.h/c)

### 串口通信模块 (uart.h/c)

### I2C 通信模块 (iic.h/c)


## 5. 环境与工具要求
- 开发环境：Visual Studio Code 1.106.3 和 Keil uVision 5
- 芯片型号：STC89C516RD+ (兼容STC89C51RC/RD+ Series)
- 编译器：Keil C51
- 下载工具：STC ISP Programmer
- 硬件模块：USB转TTL串口模块（用于程序下载）
- 文档编辑：Markdown（推荐 VSCode）

## 6. 快速上手
### 步骤 1：打开工程模板
进入 Project/ 目录，双击：`template.uvproj`
### 步骤 2：检查工程配置
- 目标芯片：选择 `STC89C51RC/RD+ Series`
- 晶振频率：根据硬件设置（常见 11.0592MHz），本模板中的程序均以 11.0592MHz 晶振频率编写，若更改晶振频率，需要修改模板程序中的相关代码
### 步骤 3：选择需要的模块
根据需要启用/禁用模块（在 project.h 中）
### 步骤 4: 开始开发你的应用程序
在相关文件夹中添加和设计自己的功能模块，并在 `main.c` 中调用。
### 步骤 5：编译工程
在 Keil 中：
> Project → Rebuild All Target Files
### 步骤 6：下载程序
使用 STC-ISP 软件，将 HEX 文件下载至单片机。

## 7. 代码组织规范
### （1）文件命名规则
- 驱动：xxx.c / xxx.h
- 应用模块：app_xxx.c
- 配置：config.h
### （2）注释规范
- 文件头：功能描述 / 作者 / 时间
- 函数头：功能说明 / 参数 / 返回值

## 8. 常用功能模块列表
本工程模板已经包含如下模块：

本工程模板未来可扩展如下模块：
- delay.c：毫秒/微秒级软件延时
- uart.c：串口初始化与收发
- timer.c：定时器初始化、时间片调度
- gpio.c：GPIO 输入/输出
- key.c：独立键盘扫描
- seg.c：数码管驱动
- iic.c：I2C 软件模拟
- spi.c：SPI 软件模拟

## 9. 文档说明
所有工程说明文档位于：
DOCS/
例如：
- 工程结构说明：project_template_guide.md
- 模块 API 文档（可选）
- 模块使用手册（可选）

## 10. 版本历史（Changelog）
v1.0.0 — 2025-12-03
- 创建工程模板
- 添加模块化目录结构
- 创建 README.md
- 生成第一版项目文档

## 11. 许可证 (License)
本工程模板遵循 GNU General Public License v3.0。

## 12. 联系与支持
> 电子邮箱：celeryhr166@gmail.com

如果有任何技术问题，可以通过邮件联系我，我看到会及时回复。
如果有错误或不恰当的地方，也欢迎通过邮件联系我并指出，我会积极学习并及时修改。

**最后更新: 2025年12月6日 <br>
版本: v1.0.0 <br>
维护者: ForeverMySunyu <br>
邮箱: celeryhr166@gmail.com**