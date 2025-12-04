# php-beast的des加密模式的默认密码解密工具，把加密php文件放到根目录运行即可
## 如果需要自定义解密密码，修改des_algo_handler.c的


static char key[8] = {
    0x01, 0x1f, 0x01, 0x1f,
    0x01, 0x0e, 0x01, 0x0e,
};
