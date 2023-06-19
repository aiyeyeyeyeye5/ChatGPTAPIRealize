#pragma once
#include<string>
#include "curl/curl.h"
#include"iconv.h"
std::string u2g(std::string input) {
    iconv_t cd = iconv_open("GBK", "UTF-8"); 
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; 
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); 
        }
        delete[] outbuf;
        iconv_close(cd); 
    }
    return input;
}
std::string g2u(std::string input) {
    iconv_t cd = iconv_open("UTF-8", "GBK"); 
    if (cd != (iconv_t)-1) {
        char* inbuf = const_cast<char*>(input.c_str());
        size_t inbytesleft = input.length();
        size_t outbytesleft = inbytesleft * 3; 
        char* outbuf = new char[outbytesleft];
        char* outptr = outbuf;
        if (iconv(cd, &inbuf, &inbytesleft, &outptr, &outbytesleft) != (size_t)-1) {
            size_t outlen = outptr - outbuf;
            input.assign(outbuf, outlen); 
        }
        delete[] outbuf;
        iconv_close(cd); 
    }
    return input;
}
void zhuanyi(std::string& s) {
    for(int i=0;i<s.size();i++){
        if(s[i]=='\\'|| s[i] == '\?' || s[i] == '\'' || s[i] == '\"' ) s.insert(i,1,'\\'),i++;
    }
}