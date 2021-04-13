<!-- title: vscode-Cpp-configure -->
# <center> vscode C/C++ 配置 </center>

- [<center> vscode C/C++ 配置 </center>](#center-vscode-cc-配置-center)
  - [事先准备](#事先准备)
  - [配置 `tasks.json`](#配置-tasksjson)
    - [tasks.json 的基本结构](#tasksjson-的基本结构)
    - [task1: "g++ build active file"](#task1-g-build-active-file)
    - [task2: "run"](#task2-run)
  - [配置 `lauch.json`](#配置-lauchjson)
  - [完整配置](#完整配置)
    - [完整的 `tasks.json`](#完整的-tasksjson)
    - [完整的 `launch.json`](#完整的-launchjson)
  - [预定义变量及其解释](#预定义变量及其解释)
  - [文件结构](#文件结构)

> 在 VScode 中配置 C/C++ 编译环境，以下内容只适合的单文件编译，多文件编译需要根据实际情况修改 g++ 编译指令，详见 https://www.jianshu.com/p/ef84efb29c02。
>
> *TIP*：多文件工程推荐使用`cmake`，单文件编译还可以使用插件 `code runer` (注意修改在终端运行，才能支持输入避免中乱码)。

## 事先准备

1. 安装 `MinGW` 编译器和 `VScode`
1. 在`vscode extensions`中查找并安装插件 `C/C++` 和 `C++ Intellisense`
1. 新建文件夹（这里是`CPP-CONFIGURE-DEMO`），`VScode` 打开此文件夹作为工作区
1. 新建文件 `main.cpp`，写些简单的代码如 "hello world!"

## 配置 `tasks.json`

本质上还是调用 `g++` 对文件进行编译的，使用 `tasks.json` 可以简化（自动化）完成这个任务。

### tasks.json 的基本结构

使用快捷键 `shift` + `ctrl` + `B` 可以执行任务。

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            // task 1
        },

        {
            // task 2
        },
        // and so on
    ],
}
```

### task1: "g++ build active file"

编译当前文件

```json
{
   "label": "g++ build active file",
   "type": "shell",
   "command": "D:/app/CodeBlocks/MinGW/bin/g++.exe", // NOTE: g++ 路径
   "args": [ // g++ 参数，g++.exe -g main.cpp -o main.exe -fexec-charset=GBK   
       "-g",
       "${file}",
       "-o",
       "${fileDirname}\\${fileBasenameNoExtension}.exe",
       "-fexec-charset=GBK" // 避免中文乱码
   ],
   "options": {
       "cwd": "D:/app/CodeBlocks/MinGW/bin" // NOTE: 这里是MinGW/bin 的路径
   },
   "problemMatcher": [
       "$gcc"
   ],
   "group": "build"
},
```

### task2: "run"

运行可执行文件

```json
{
   "label": "run",
   "type": "process", // 执行 exe 使用 process 类型 
   "command": "${fileDirname}\\${fileBasenameNoExtension}.exe",
   "group": "build",
   "presentation": {
       "echo": true,
       "reveal": "always",
       "focus": false,
       "panel": "shared",
       "showReuseMessage": true,
       "clear": false
   },
   "options": {
       "cwd": "${fileDirname}"
   },
   "problemMatcher": "$msCompile",
   "dependsOn": [
       "g++ build active file" // run 之前先编译，即依赖任务 g++ build active file
   ]
},
```

## 配置 `lauch.json`

`VScode` 通过`.vscode`目录下的`launch.json`实现对多个平台多种语言的调试支持。如果是第一次，一般点击左侧的 `Run and Debug` 会提示创建 `launch.json` 并自动生成代码（也会对应生成所需要的`tasks.json`），为了灵活推荐自己新建哈。

一般选择的是 `gdb` 调试，下面的代码其实和 `VScode` 生成的代码是大致相同的，`preLaunchTask` 是指启动前先执行的任务，此项需要根据`tasks.json`来设置，这里为了调试必须先进行**编译**的意思。

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe", // NOTE:可执行程序路径
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\app\\CodeBlocks\\MinGW\\bin\\gdb.exe", // NOTE: gdb.exe 的路径
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "g++ build active file" // tasks.json 的任务
        }
    ]
}
```

## 完整配置

### 完整的 `tasks.json`

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "g++ build active file",
            "type": "shell",
            "command": "D:/app/CodeBlocks/MinGW/bin/g++.exe", // NOTE: g++ 路径
            "args": [ // g++ 参数，g++.exe -g main.cpp -o main.exe -fexec-charset=GBK   
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-fexec-charset=GBK" // 避免中文乱码
            ],
            "options": {
                "cwd": "D:/app/CodeBlocks/MinGW/bin" // NOTE: 这里是MinGW/bin 的路径
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": "build"
         },

        {
            "label": "run",
            "type": "process", // 执行 exe 使用 process 类型 
            "command": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared",
                "showReuseMessage": true,
                "clear": false
            },
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": "$msCompile",
            "dependsOn": [
                "g++ build active file" // run 之前先编译，即依赖任务 g++ build active file
            ]
        },
    ]
}
```

### 完整的 `launch.json`

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe", // NOTE:可执行程序路径
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\app\\CodeBlocks\\MinGW\\bin\\gdb.exe", // NOTE: gdb.exe 的路径
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "g++ build active file" // tasks.json 的任务
        }
    ]
}
```

## 预定义变量及其解释

`${workspaceFolder}` : 表示当前workspace文件夹路径，如`C:\Users\admin\Desktop\test`
 
 `${workspaceRootFolderName}` : 表示 workspace 的文件夹名，如test
 
 `${file}` : 文件自身的绝对路径，如`C:\Users\admin\Desktop\test\.vscode\launch.json`

 `${relativeFile}` : 文件在workspace中的路径，如`.vscode\launch.json`
 
`${fileBasenameNoExtension}` : 当前文件的文件名，不带后缀，如`hello/launch`
 
`${fileBasename}` : 当前文件的文件名，如 `hello.cpp/launch.json`等
 
`${fileDirname}` : 文件所在的文件夹路径，也即`C:\Users\admin\Desktop\test\.vscode`
 
`${fileExtname}` : 当前文件的后缀，也即`.json`
 
`${lineNumber}` : 当前文件光标所在的行号
 
`${env:PATH}` : 系统中的环境变量

## 文件结构

```
cpp-configure-demo
├─ .vscode
│  ├─ launch.json
│  └─ tasks.json
├─ main.cpp
├─ main.exe
└─ README.md
```