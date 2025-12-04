#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include "des_algo_handler.h"
#include <direct.h> // _getcwd
#include <io.h>     // _access, _findfirst, _findnext, _findclose
#include <cstdlib>  // _fullpath
#include <cstdio>
#include <format>
#include <string>
#include <iostream>
#include "ConsoleApplication1.h"

int Decode(const std::string& filename, bool& retFlag);

int main()
{
    const std::string folder = "./";
    const std::string pattern = folder + "\\*.php";

    struct _finddata_t findData;
    intptr_t handle = _findfirst(pattern.c_str(), &findData);
    if (handle == -1) {
        std::cerr << "未找到目录或匹配的 .php 文件: " << folder << std::endl;
        return 1;
    }

    do {
        std::string filepath = folder + "\\" + findData.name;
        bool retFlag = true;
        int retVal = Decode(filepath, retFlag);
        std::cout << "处理文件: " << filepath << " -> 返回值: " << retVal
                  << ", retFlag: " << (retFlag ? "true" : "false") << std::endl;
    } while (_findnext(handle, &findData) == 0);

    _findclose(handle);
    return 0;
}

int Decode(const std::string& filename, bool& retFlag)
{
	retFlag = true;

	// 使用 VC++ 安全函数 fopen_s以二进制模式打开文件并读取到 char 数组中
	FILE* fp = nullptr;
	errno_t ferr = fopen_s(&fp, filename.c_str(), "rb");
	if (ferr != 0 || !fp) {
		std::cerr << "无法打开文件: " << filename << std::endl;
		return 1;
	}

	if (fseek(fp, 0, SEEK_END) != 0) {
		std::cerr << "无法定位文件末尾: " << filename << std::endl;
		fclose(fp);
		return 1;
	}

	long size = ftell(fp);
	if (size < 0) {
		std::cerr << "无法获取文件大小: " << filename << std::endl;
		fclose(fp);
		return 1;
	}

	rewind(fp);

	char* cipher = nullptr;
	if (size > 0) {
		cipher = new char[size];
		size_t read = fread(cipher, 1, static_cast<size_t>(size), fp);
		if (read != static_cast<size_t>(size)) {
			std::cerr << "读取文件数据失败: " << filename << std::endl;
			delete[] cipher;
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);

	int cipher_len = static_cast<int>(size);
	char* in_buf = cipher; // 输入缓冲
	char* out_buf = nullptr;
	int out_len = 0;


	// 安全地打印前最多 20 字节（如果文件小于20字节则只打印实际字节数）
	size_t to_print = std::min<size_t>(20, static_cast<size_t>(cipher_len));
	for (size_t i = 0; i < to_print; i++)
	{
		printf("c1 -> %#02x\n", static_cast<unsigned char>(in_buf[i]));
	}

	// 按要求：排除 in_buf 前 20 位，并将 cipher_len 减 20
	if (cipher_len <= 20) {
		std::cerr << "密文长度不足（<=20），无法跳过前20字节并解密。" << std::endl;
		delete[] in_buf;
		return 1;
	}

	char* data_ptr = in_buf + 20;
	int data_len = cipher_len - 20;

	des_decrypt_handler(data_ptr, data_len, &out_buf, &out_len);




	if (out_buf == nullptr || out_len <= 0) {
		std::cerr << "解密失败或无输出" << std::endl;
		delete[] in_buf; // 或 free(in_buf) 取决于你如何分配
		return 1;
	}

	// 将解密结果放入 std::string（可以包含 '\0'）
	std::string plain_text(out_buf, static_cast<size_t>(out_len));

	//将plain_text写入到原始文件中，替换文件原有内容
	FILE* out_fp = nullptr;
	errno_t oferr = fopen_s(&out_fp, filename.c_str(), "wb");
	if (oferr != 0 || !out_fp) {
		std::cerr << "无法打开文件进行写入: " << filename << std::endl;
		des_free_handler(out_buf);
		delete[] in_buf;
		return 1;
	}
	size_t written = fwrite(plain_text.data(), 1, plain_text.size(), out_fp);
	if (written != plain_text.size()) {
		std::cerr << "写入解密数据失败: " << filename << std::endl;
		fclose(out_fp);
		des_free_handler(out_buf);
		delete[] in_buf;
		return 1;
	}
    // 关闭写入文件句柄并释放缓冲
    fclose(out_fp);
	des_free_handler(out_buf);
	delete[] in_buf;

	retFlag = false;
	return 0;
}
