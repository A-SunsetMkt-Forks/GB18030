#include <iostream>
#include "GbString.hpp"

using namespace std;
using namespace gb18030::v2022;

#define TEST_BEG cout << __FUNCTION__ << "\n";
#define TEST_END cout << "\n\n";

void printGbBytes(GbChar ch)
{
	auto size = ch.size();
	auto bytes = ch.toBytes();
	for (size_t i = 0; i < size; ++i)
		cout << hex << int(bytes[i]);
}

void printGbBytes(const GbString& s)
{
	for (auto ch : s)
	{
		printGbBytes(ch);
		cout << " ";
	}
}

void testGbCharBytes()
{
	TEST_BEG

	GbChar c = GbChar::fromBytes("\xB0\xA1", 2);
	cout << "GB char B0A1 hex: " << hex << c.value() << " bytes: ";
	printGbBytes(c);

	TEST_END
}

void testGbCharUnicode()
{
	TEST_BEG

	GbChar c1 = GbChar::fromUnicode(U'汉');
	cout << "Unicode to GB bytes: ";
	printGbBytes(c1);

	GbChar c2 = GbChar::fromBytes("\xBA\xBA", 2);
	auto uc = c2.toUnicode();
	cout << "GB to unicode hex: " << hex << uc << "\n";

	TEST_END
}

void testGbCharBmpSmp()
{
	TEST_BEG

	char32_t u1 = 0x0250;
	GbChar c1 = GbChar::fromUnicode(u1);  //BMP-ext
	cout << "Unicode(0x250) to GB size: " << dec << c1.size() << " bytes: ";
	printGbBytes(c1);

	cout << "\n";

	char32_t u2 = 0x10011;
	GbChar c2 = GbChar::fromUnicode(u2);  //SMP
	cout << "Unicode(0x10011) to GB size: " << dec << c2.size() << " bytes: ";
	printGbBytes(c2);

	TEST_END;
}

void testGbCharFromLiteral()
{
	TEST_BEG

	GbChar c = GbChar::fromBytes("\xBA\xBA");
	cout << "GB bytes: ";
	printGbBytes(c);
	cout << "\n";

	TEST_END
}

void testGbStringBasic()
{
	TEST_BEG

	GbString s;
	s.push_back(GbChar::fromUnicode(U'中'));
	s.push_back(GbChar::fromUnicode(U'文'));

	cout << "GB string length: " << s.length() << " bytes: ";
	printGbBytes(s);
	cout << "\n";

	TEST_END
}

void testGbStringUnicode()
{
	TEST_BEG

	GbString s1 = GbString::fromUnicode(U"中国中文汉字", 6);
	cout << "GB string length: " << s1.length() << " bytes: ";
	printGbBytes(s1);
	cout << "\n";

	GbString s2 = GbString::fromBytes("\xd6\xd0\xb9\xfa\xd6\xd0\xce\xc4\xba\xba\xd7\xd6", 12);
	u32string u32 = s2.toUnicode();
	cout << "Unicode length: " << dec << u32.size() << " bytes: ";
	for (auto c : u32)
		cout << hex << c << " ";
	cout << "\n";

	TEST_END
}

void testGbStringBytes()
{
	TEST_BEG

	GbString s = GbString::fromBytes("\xD6\xD0\xB9\xFA\xD6\xD0\xCE\xC4\xBA\xBA\xD7\xD6 abc", 16);
	cout << "GB string length: " << dec << s.length() << " bytes: ";
	printGbBytes(s);
	cout << "\n";

	TEST_END
}

void testGbStringFromLiteral()
{
	TEST_BEG

	GbString s1 = GbString::fromUnicode(U"中国中文汉字");
	cout << "GB length: " << dec << s1.length() << " bytes: ";
	printGbBytes(s1);
	cout << "\n";

	GbString s2 = GbString::fromBytes("\xd6\xd0\xb9\xfa\xd6\xd0\xce\xc4\xba\xba\xd7\xd6");
	u32string u32 = s2.toUnicode();
	cout << "Unicode length: " << dec << u32.size() << " bytes: ";
	for (auto c : u32)
		cout << hex << c << " ";
	cout << "\n";

	TEST_END
}

void example()
{

}

int main()
{
	testGbCharBytes();
	testGbCharUnicode();
	testGbCharBmpSmp();
	testGbCharFromLiteral();

	testGbStringBasic();
	testGbStringUnicode();
	testGbStringBytes();
	testGbStringFromLiteral();
	return 0;
}