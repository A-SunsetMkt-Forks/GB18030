#include <iostream>
#include "GbString.hpp"

using namespace std;
using namespace gb18030::v2022;

void testGbCharBytes()
{
	cout << __FUNCTION__ << "\n";

	GbChar c = GbChar::fromBytes("\xB0\xA1", 2);
	cout << "gb char B0A1 hex: " << hex << c.value() << "\n";
	auto bs = c.toBytes();
	cout << "to bytes: ";
	for (size_t i = 0; i < c.size(); ++i)
		cout << hex << (int)bs[i] << " ";
	cout << endl;
}

void testGbCharUnicode()
{
	cout << __FUNCTION__ << "\n";

	GbChar c1 = GbChar::fromUnicode(U'บบ');
	cout << "unicode to gb hex: " << hex << c1.value() << "\n";

	GbChar c2 = GbChar::fromBytes("\xBA\xBA", 2);
	auto uc = c2.toUnicode();
	cout << "gb to unicode hex: " << hex << uc << "\n";
}

void example()
{

}

int main()
{
	testGbCharBytes();
	testGbCharUnicode();
	return 0;
}