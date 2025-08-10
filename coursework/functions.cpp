#include "functions.h"

std::string cp1251_to_utf8(const char* cp1251_str)
{
    iconv_t cd = iconv_open("UTF-8", "IBM866");
    if (cd == (iconv_t)-1) {
        return cp1251_str; // fallback — если iconv не открылся
    }

    size_t in_bytes = strlen(cp1251_str);
    size_t out_bytes = in_bytes * 2 + 1; // UTF-8 может быть больше
    std::string utf8_str(out_bytes, '\0');

    char* in_buf = const_cast<char*>(cp1251_str);
    char* out_buf = utf8_str.data();

    iconv(cd, &in_buf, &in_bytes, &out_buf, &out_bytes);
    iconv_close(cd);

    // обрезаем по фактической длине
    utf8_str.resize(strlen(utf8_str.c_str()));
    return utf8_str;
}
