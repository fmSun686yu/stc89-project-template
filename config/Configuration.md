# config 文件夹 ——— Configuration（系统配置与全局定义文件）

## 放什么内容？
> config
   ├─ config.h      		  // 系统参数宏定义，如频率
   ├─ typedef.h      		 // 数据类型定义
   └─ project_config.h	     // 工程管理相关配置（可选）

- 定义晶振频率、系统参数、全局变量。
- 定义自定义的数据类型 uint8, int16 等。
- 集中管理全局宏，提高可读性。

<br>

- config 就像工程的“说明书 + 规则手册”。