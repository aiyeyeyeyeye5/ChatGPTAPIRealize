#pragma once
static size_t write_callback_chat(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    }
    catch (std::bad_alloc& e) {
        return 0;
    }
    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
    return size * nmemb;
}
