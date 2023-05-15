#include<string>
#include"iconv.h"

std::string u2g(std::string input) {
    iconv_t cd = iconv_open("GBK", "UTF-8"); // ����iconvת�����
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; // UTF-8������ַ����ܱ�GBK������ַ��࣬������ҪԤ���㹻�Ŀռ�
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); // ��ת������ַ������浽utf8str��
        }
        delete[] outbuf;
        iconv_close(cd); // �ر�iconvת�����
    }
    return input;
}
std::string g2u(std::string input) {
    iconv_t cd = iconv_open("UTF-8", "GBK"); // ����iconvת�����
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; // UTF-8������ַ����ܱ�GBK������ַ��࣬������ҪԤ���㹻�Ŀռ�
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); // ��ת������ַ������浽utf8str��
        }
        delete[] outbuf;
        iconv_close(cd); // �ر�iconvת�����
    }
    return input;
}