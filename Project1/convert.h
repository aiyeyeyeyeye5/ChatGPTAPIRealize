#include<string>
#include"iconv.h"

std::string u2g(std::string input) {
    iconv_t cd = iconv_open("GBK", "UTF-8"); // 创建iconv转换句柄
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; // UTF-8编码的字符可能比GBK编码的字符多，所以需要预留足够的空间
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); // 将转换后的字符串保存到utf8str中
        }
        delete[] outbuf;
        iconv_close(cd); // 关闭iconv转换句柄
    }
    return input;
}
std::string g2u(std::string input) {
    iconv_t cd = iconv_open("UTF-8", "GBK"); // 创建iconv转换句柄
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; // UTF-8编码的字符可能比GBK编码的字符多，所以需要预留足够的空间
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); // 将转换后的字符串保存到utf8str中
        }
        delete[] outbuf;
        iconv_close(cd); // 关闭iconv转换句柄
    }
    return input;
}