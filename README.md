# GB18030 中文编码字符集

## 说明
GB18030是中华人民共和国《中文编码字符集》国家标准，最新版本为GB18030-2022。
本项目收录了GB18030-2022标准规范(PDF)、GB18030-2022编码到UCS编码转换表等文档，同时还有编程语言实现，可方便的处理、转换GB18030-2022字符串。


## 用法

C++语言：

``` C++
//将src/cpp/GbString.hpp头文件加入包含目录，GbString.cpp加入构建目录。
#include "GbString.hpp"

int main()
{
    using namespace std;
    using namespace gb18030::v2022;

    // Unicode转GB18030
    GbString s = GbString::fromUnicode(U"中国中文");
    
    // 获取字符串长度
    cout << "GB string length: " << dec << s.length() << "\n";

    // 获取GB18030字符
    cout << "GB string[0] bytes: ";
    for (size_t i = 0; i < s[0].size(); ++i)
        cout << hex << (int)s[0].toBytes()[i];
    cout << "\n";

    // 获取对应Unicode字符值
    cout << "GB string[0] to Unicode: " << hex << s[0].toUnicode() << "\n";

    // 修改字符串
    s[2] = 0xBABA;  //汉
    s[3] = GbChar::fromUnicode(U'字');

    // 遍历GB18030字符
    cout << "GB string sizes: ";
    for (auto c : s)
        cout << dec << c.size() << " ";
    cout << "\n";

    // GB18030转Unicode
    u32string u32 = s.toUnicode();
    cout << "GB string to Unicode string length: " << u32.length() << " bytes: ";
    for (auto u : u32)
        cout << hex << u << " ";
    cout << "\n";

    // GB18030转字节流
    string bytes = s.toBytes();
    for (auto b : bytes)
        printf("%02x ", (unsigned char)b);
}
```


## 许可证
MIT License

Copyright(C) 2024 xuges@qq.com