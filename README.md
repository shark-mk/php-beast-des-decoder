# PHP Beast DES 解密工具 / PHP Beast DES Decoder

[中文](#中文文档) | [English](#english-documentation)

---

## 中文文档

### 📝 项目简介

这是一个用于解密 PHP Beast 扩展 DES 加密模式的工具。PHP Beast 是一个 PHP 源码加密扩展，本工具专门用于解密使用默认 DES 密钥加密的 PHP 文件。

### ✨ 功能特性

- ✅ 支持批量解密 PHP Beast DES 加密文件
- ✅ 自动扫描目录下所有 .php 文件
- ✅ 支持自定义 DES 解密密钥
- ✅ 原地解密，直接替换加密文件
- ✅ 详细的处理日志输出

### 📋 系统要求

- **操作系统**: Windows (Windows 10/11 推荐)
- **开发环境**: Microsoft Visual Studio 2022 或更高版本
- **编译器**: MSVC (支持 C++20 标准)
- **平台**: x64 或 x86

### 🔧 安装与编译

#### 方法一：使用 Visual Studio IDE

1. **克隆仓库**
   ```bash
   git clone https://github.com/shark-mk/php-beast-des-decoder.git
   cd php-beast-des-decoder
   ```

2. **打开解决方案**
   - 双击打开 `php-beast-des-decoder.sln` 文件
   - 或在 Visual Studio 中选择 "文件" → "打开" → "项目/解决方案"

3. **选择编译配置**
   - Debug 模式：用于调试，包含调试符号
   - Release 模式：用于生产，优化性能
   - 平台选择：x64 (推荐) 或 x86

4. **编译项目**
   - 点击菜单栏 "生成" → "生成解决方案"
   - 或按快捷键 `Ctrl + Shift + B`
   - 编译成功后，可执行文件位于：
     - Debug 版本: `x64/Debug/ConsoleApplication1.exe`
     - Release 版本: `x64/Release/ConsoleApplication1.exe`

#### 方法二：使用 MSBuild 命令行

```bash
# 打开 Visual Studio Developer Command Prompt
# 编译 Release x64 版本
msbuild php-beast-des-decoder.sln /p:Configuration=Release /p:Platform=x64

# 编译 Debug x64 版本
msbuild php-beast-des-decoder.sln /p:Configuration=Debug /p:Platform=x64
```

### 🚀 使用方法

#### 基本使用（默认密钥）

1. **准备加密文件**
   - 将需要解密的 .php 文件放到程序所在目录

2. **运行解密工具**
   ```bash
   # 方式1: 直接运行可执行文件
   ConsoleApplication1.exe
   
   # 方式2: 在 Visual Studio 中按 F5 运行
   ```

3. **查看结果**
   - 程序会自动扫描当前目录下所有 .php 文件
   - 解密成功的文件会被直接替换为明文 PHP 代码
   - 控制台会显示每个文件的处理结果

#### 输出示例

```
处理文件: .\test.php -> 返回值: 0, retFlag: false
处理文件: .\index.php -> 返回值: 0, retFlag: false
```

- **返回值 0**: 解密成功
- **返回值 1**: 解密失败（文件格式错误、密钥不匹配等）
- **retFlag false**: 文件已成功处理

### ⚙️ 自定义配置

#### 修改 DES 解密密钥

如果你的 PHP Beast 加密文件使用了自定义密钥，需要修改源码中的密钥配置：

1. **找到密钥定义位置**
   - 打开文件: `ConsoleApplication1/des_algo_handler.h`
   - 或在源码中搜索 `static char key[8]`

2. **修改密钥数组**
   ```c
   static char key[8] = {
       0x01, 0x1f, 0x01, 0x1f,  // 前4字节
       0x01, 0x0e, 0x01, 0x0e,  // 后4字节
   };
   ```
   - 将密钥修改为你的加密密钥（8字节十六进制值）
   - 密钥必须与加密时使用的密钥完全一致

3. **重新编译**
   - 修改密钥后，需要重新编译项目
   - 按照上述"安装与编译"步骤重新生成可执行文件

#### 密钥格式说明

- DES 密钥长度固定为 **8 字节**
- 使用十六进制表示，格式：`0xXX`
- 示例密钥：`{0x01, 0x1f, 0x01, 0x1f, 0x01, 0x0e, 0x01, 0x0e}`

### 🔍 工作原理

1. **文件扫描**: 程序扫描当前目录下的所有 .php 文件
2. **读取文件**: 以二进制模式读取加密的 PHP 文件
3. **跳过文件头**: PHP Beast 加密文件前 20 字节为文件头，跳过该部分
4. **DES 解密**: 使用配置的密钥对剩余数据进行 DES 解密
5. **写回文件**: 将解密后的明文内容写回原文件

### 📁 项目结构

```
php-beast-des-decoder/
├── ConsoleApplication1/           # 主程序目录
│   ├── ConsoleApplication1.cpp    # 主程序入口和解密逻辑
│   ├── ConsoleApplication1.h      # 函数声明
│   ├── des_algo_handler.h         # DES 加密解密处理头文件
│   └── ConsoleApplication1.vcxproj # 项目配置文件
├── php-beast-des-decoder.sln      # Visual Studio 解决方案文件
└── README.md                      # 项目说明文档
```

### ⚠️ 注意事项

1. **备份重要文件**: 解密操作会直接替换原文件，建议先备份
2. **密钥匹配**: 确保解密密钥与加密密钥完全一致
3. **文件格式**: 仅支持 PHP Beast DES 加密模式的文件
4. **文件大小**: 加密文件至少要大于 20 字节（包含文件头）
5. **Windows 专用**: 当前版本仅支持 Windows 平台

### 🐛 故障排除

#### 问题：无法打开文件

**原因**: 文件不存在或权限不足

**解决方案**:
- 确认 .php 文件确实存在于程序目录
- 检查文件是否被其他程序占用
- 以管理员权限运行程序

#### 问题：解密失败（返回值 1）

**原因**: 可能的原因包括：
- 密钥不匹配
- 文件不是 PHP Beast 加密文件
- 文件已损坏

**解决方案**:
- 确认文件确实是 PHP Beast DES 加密的
- 检查并确认使用正确的解密密钥
- 尝试使用原始备份文件

#### 问题：密文长度不足（<=20）

**原因**: 文件大小小于或等于 20 字节

**解决方案**:
- 检查文件是否完整
- 确认文件未被截断或损坏

### 📄 许可证

本项目为开源项目，具体许可证信息请查看仓库。

### 🤝 贡献

欢迎提交 Issue 和 Pull Request！

如有问题或建议，请在 GitHub Issues 中提出。

---

## English Documentation

### 📝 Project Overview

A decryption tool for PHP files encrypted by PHP Beast extension using DES encryption mode. PHP Beast is a PHP source code encryption extension, and this tool is specifically designed to decrypt PHP files encrypted with the default DES key.

### ✨ Features

- ✅ Batch decryption of PHP Beast DES encrypted files
- ✅ Automatic scanning of all .php files in directory
- ✅ Custom DES decryption key support
- ✅ In-place decryption, directly replaces encrypted files
- ✅ Detailed processing logs

### 📋 Requirements

- **Operating System**: Windows (Windows 10/11 recommended)
- **Development Environment**: Microsoft Visual Studio 2022 or higher
- **Compiler**: MSVC (C++20 support required)
- **Platform**: x64 or x86

### 🔧 Installation & Building

#### Method 1: Using Visual Studio IDE

1. **Clone the repository**
   ```bash
   git clone https://github.com/shark-mk/php-beast-des-decoder.git
   cd php-beast-des-decoder
   ```

2. **Open the solution**
   - Double-click `php-beast-des-decoder.sln`
   - Or in Visual Studio: File → Open → Project/Solution

3. **Select build configuration**
   - Debug mode: For debugging with symbols
   - Release mode: For production with optimizations
   - Platform: x64 (recommended) or x86

4. **Build the project**
   - Menu: Build → Build Solution
   - Or press `Ctrl + Shift + B`
   - Executable location after build:
     - Debug version: `x64/Debug/ConsoleApplication1.exe`
     - Release version: `x64/Release/ConsoleApplication1.exe`

#### Method 2: Using MSBuild Command Line

```bash
# Open Visual Studio Developer Command Prompt
# Build Release x64 version
msbuild php-beast-des-decoder.sln /p:Configuration=Release /p:Platform=x64

# Build Debug x64 version
msbuild php-beast-des-decoder.sln /p:Configuration=Debug /p:Platform=x64
```

### 🚀 Usage

#### Basic Usage (Default Key)

1. **Prepare encrypted files**
   - Place .php files to be decrypted in the program directory

2. **Run the decoder**
   ```bash
   # Method 1: Run executable directly
   ConsoleApplication1.exe
   
   # Method 2: Press F5 in Visual Studio
   ```

3. **Check results**
   - Program automatically scans all .php files in current directory
   - Successfully decrypted files are replaced with plaintext PHP code
   - Console displays processing results for each file

#### Output Example

```
处理文件: .\test.php -> 返回值: 0, retFlag: false
处理文件: .\index.php -> 返回值: 0, retFlag: false
```

- **Return value 0**: Decryption successful
- **Return value 1**: Decryption failed (format error, key mismatch, etc.)
- **retFlag false**: File processed successfully

### ⚙️ Configuration

#### Modifying DES Decryption Key

If your PHP Beast encrypted files use a custom key, you need to modify the key in source code:

1. **Locate key definition**
   - Open file: `ConsoleApplication1/des_algo_handler.h`
   - Or search for `static char key[8]` in source code

2. **Modify key array**
   ```c
   static char key[8] = {
       0x01, 0x1f, 0x01, 0x1f,  // First 4 bytes
       0x01, 0x0e, 0x01, 0x0e,  // Last 4 bytes
   };
   ```
   - Replace with your encryption key (8-byte hexadecimal values)
   - Key must exactly match the one used during encryption

3. **Rebuild**
   - After modifying the key, rebuild the project
   - Follow "Installation & Building" steps to regenerate executable

#### Key Format

- DES key length is fixed at **8 bytes**
- Use hexadecimal notation: `0xXX`
- Example key: `{0x01, 0x1f, 0x01, 0x1f, 0x01, 0x0e, 0x01, 0x0e}`

### 🔍 How It Works

1. **File Scanning**: Program scans all .php files in current directory
2. **File Reading**: Reads encrypted PHP file in binary mode
3. **Skip Header**: PHP Beast encrypted files have 20-byte header, which is skipped
4. **DES Decryption**: Decrypts remaining data using configured key
5. **Write Back**: Writes decrypted plaintext back to original file

### 📁 Project Structure

```
php-beast-des-decoder/
├── ConsoleApplication1/           # Main program directory
│   ├── ConsoleApplication1.cpp    # Main entry and decryption logic
│   ├── ConsoleApplication1.h      # Function declarations
│   ├── des_algo_handler.h         # DES encryption/decryption handler
│   └── ConsoleApplication1.vcxproj # Project configuration
├── php-beast-des-decoder.sln      # Visual Studio solution file
└── README.md                      # Project documentation
```

### ⚠️ Important Notes

1. **Backup Important Files**: Decryption replaces original files, backup first
2. **Key Matching**: Ensure decryption key exactly matches encryption key
3. **File Format**: Only supports PHP Beast DES encryption mode
4. **File Size**: Encrypted file must be larger than 20 bytes (including header)
5. **Windows Only**: Current version supports Windows platform only

### 🐛 Troubleshooting

#### Issue: Cannot open file

**Cause**: File doesn't exist or insufficient permissions

**Solution**:
- Verify .php file exists in program directory
- Check if file is locked by another program
- Run program with administrator privileges

#### Issue: Decryption failed (return value 1)

**Cause**: Possible reasons:
- Key mismatch
- File is not PHP Beast encrypted
- File is corrupted

**Solution**:
- Confirm file is PHP Beast DES encrypted
- Verify correct decryption key is being used
- Try using original backup file

#### Issue: Cipher length insufficient (<=20)

**Cause**: File size is 20 bytes or less

**Solution**:
- Check if file is complete
- Verify file hasn't been truncated or corrupted

### 📄 License

This project is open source. Please check the repository for license information.

### 🤝 Contributing

Issues and Pull Requests are welcome!

For questions or suggestions, please open an issue on GitHub.

---

**Project Repository**: https://github.com/shark-mk/php-beast-des-decoder
