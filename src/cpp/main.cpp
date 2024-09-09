#include <iostream>
#include "GbString.hpp"

using namespace std;
using namespace gb18030::v2022;

#define TEST_BEG cout << __FUNCTION__ << "\n";
#define TEST_END cout << "\n\n";

void testGbCharBytes()
{
	TEST_BEG

	GbChar c = GbChar::fromBytes("\xB0\xA1", 2);
	cout << "gb char B0A1 hex: " << hex << c.value() << "\n";
	auto bs = c.toBytes();
	cout << "to bytes: ";
	for (size_t i = 0; i < c.size(); ++i)
		cout << hex << (int)bs[i] << " ";
	
	TEST_END
}

void testGbCharUnicode()
{
	TEST_BEG

	GbChar c1 = GbChar::fromUnicode(U'汉');
	cout << "unicode to gb hex: " << hex << c1.value() << "\n";

	GbChar c2 = GbChar::fromBytes("\xBA\xBA", 2);
	auto uc = c2.toUnicode();
	cout << "gb to unicode hex: " << hex << uc << "\n";

	TEST_END
}

void testGbStringBasic()
{
	TEST_BEG

	GbString s;
	s.push_back(GbChar::fromUnicode(U'中'));
	s.push_back(GbChar::fromUnicode(U'文'));

	cout << "length: " << s.length() << " bytes: ";

	for (auto ch : s)
	{
		auto size = ch.size();
		auto bytes = ch.toBytes();
		for (size_t i = 0; i < size; ++i)
			cout << hex << int(bytes[i]);
		cout << " ";
	}

	TEST_END
}

void testGbStringUnicode()
{
	TEST_BEG

	GbString s = GbString::fromUnicode(U"中国中文汉字", 6);
	cout << "length: " << s.length() << " bytes: ";

	for (auto ch : s)
	{
		auto size = ch.size();
		auto bytes = ch.toBytes();
		for (size_t i = 0; i < size; ++i)
			cout << hex << int(bytes[i]);
		cout << " ";
	}

	TEST_END
}

void testGbStringBytes()
{
	TEST_BEG

	GbString s = GbString::fromBytes("\xD6\xD0\xB9\xFA\xD6\xD0\xCE\xC4\xBA\xBA\xD7\xD6 abc", 16);
	cout << "length: " << dec << s.length() << " bytes: ";

	for (auto ch : s)
	{
		auto size = ch.size();
		auto bytes = ch.toBytes();
		for (size_t i = 0; i < size; ++i)
			cout << hex << int(bytes[i]);
		cout << " ";
	}

	TEST_END
}

void example()
{

}

int main()
{
	testGbCharBytes();
	testGbCharUnicode();
	testGbStringBasic();
	testGbStringUnicode();
	testGbStringBytes();
	return 0;
}