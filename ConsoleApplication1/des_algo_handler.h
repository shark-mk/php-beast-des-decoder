/* des_algo_handler.h
 *
 * 为 `des_algo_handler.c` 中的加解密函数提供头文件声明。
 * 设计目标：
 * - 提供 `des_encrypt_handler`、`des_decrypt_handler` 和 `des_free_handler` 的函数原型
 * - 使用 include guard 防止重复包含
 * - 为 C++ 提供 `extern "C"` 兼容性
 * - 在注释中说明内存归属（哪个函数分配，哪个函数释放）
 *
 * 伪代码 / 详细计划：
 * 1. 添加文件注释，说明用途和作者（中文简短说明）。
 * 2. 添加 include guard 宏：`DES_ALGO_HANDLER_H`。
 * 3. 包含必要的标准头（不强制，但包含 <stddef.h> 以表明依赖，保持最小）。
 * 4. 添加 `extern "C"` 包裹以支持 C++ 调用。
 * 5. 声明函数原型：
 *    - `int des_encrypt_handler(char *inbuf, int len, char **outbuf, int *outlen);`
 *      说明：函数为输入数据分配输出缓冲区，调用方须使用 `des_free_handler` 释放。
 *    - `int des_decrypt_handler(char *inbuf, int len, char **outbuf, int *outlen);`
 *      说明同上。
 *    - `void des_free_handler(void *ptr);`
 *      释放由上述加解密函数分配的缓冲区。
 * 6. 结束 `extern "C"` 和 include guard。
 *
 * 注意：
 * - 保持接口与现有 `des_algo_handler.c` 中实现完全匹配。
 * - 不暴露内部静态变量（如 `key`），保持其为实现细节。
 */

#ifndef DES_ALGO_HANDLER_H
#define DES_ALGO_HANDLER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 对 `inbuf` 长度为 `len` 的数据进行 DES 加密。
 * 输出由函数分配，地址通过 `*outbuf` 返回，长度通过 `*outlen` 返回（以字节为单位）。
 * 返回 0 表示成功，非 0 表示失败。
 * 注意：调用方应使用 `des_free_handler` 释放 `*outbuf`。
 */
int des_encrypt_handler(char *inbuf, int len, char **outbuf, int *outlen);

/*
 * 对 `inbuf` 长度为 `len` 的数据进行 DES 解密。
 * 输出由函数分配，地址通过 `*outbuf` 返回，长度通过 `*outlen` 返回（以字节为单位）。
 * 返回 0 表示成功，非 0 表示失败。
 * 注意：调用方应使用 `des_free_handler` 释放 `*outbuf`。
 */
int des_decrypt_handler(char *inbuf, int len, char **outbuf, int *outlen);

/*
 * 释放由 `des_encrypt_handler` / `des_decrypt_handler` 分配的内存。
 */
void des_free_handler(void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* DES_ALGO_HANDLER_H */