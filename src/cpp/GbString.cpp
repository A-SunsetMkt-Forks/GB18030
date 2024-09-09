#include "GbString.hpp"

namespace gb18030
{
	namespace v2022
	{
		namespace internal
		{
			extern uint32_t ucsToGbBmp[65536];
			extern char32_t gbToUcsBmp[65536];
			extern char32_t gbToUcsBmpExt[4][10][126][11];

			using CharBytes = std::array<uint8_t, 4>;

			//获取字节数组
			inline CharBytes getCharBytes(uint32_t value) noexcept
			{
				//TODO: 默认小端 考虑大端？
				return *reinterpret_cast<CharBytes*>(&value);
			}

			//字节数组转字符
			inline uint32_t fromCharBytes(const uint8_t* data, size_t len) noexcept
			{
				//TODO: 默认小端 考虑大端？
				if (len != 0)
				{
					if (len == 4)
						return *reinterpret_cast<const uint32_t*>(data);

					CharBytes bytes = getCharBytes(0);
					bytes[0] = data[0];
					
					if (len > 1)
						bytes[1] = data[1];
					if (len > 2)
						bytes[2] = data[2];
					
					return *reinterpret_cast<uint32_t*>(&bytes);
				}
				return 0;
			}

			//获取GB18030字符占用字节数
			inline size_t getGbCharSize(uint32_t c) noexcept
			{
				if (c <= 0x7F)
					return 1;
				else if (c <= 0xFFFF)
					return 2;
				return 4;
			}

			//获取GB18030字符边界
			inline size_t getGbCharBound(const uint8_t* data, size_t len) noexcept
			{
				if (len != 0)
				{
					if (data[0] <= 0x7F)
					{
						return 1;
					}
					else if (0x7F < data[1] || 0x40 <= data[1] && data[1] <= 0x7E)
					{
						return 2;
					}
					else if (0x30 <= data[1] && data[1] <= 0x39 && 0x7F < data[2] && 0x30 <= data[3] && data[3] <= 0x39)
					{
						return 4;
					}
				}
				return 0;
			}

			inline uint32_t unicodeToGb(char32_t c) noexcept
			{
				if (c <= 0x7F)  //单字节区 等同
					return (uint32_t)c;

				if (c <= 0xFFFF)  //双字节区 BMP
					return ucsToGbBmp[c];

				if (c <= 0x10FFFF)  //四字节区 SMP
				{
					uint32_t u = c - 65536;
					uint32_t n1 = u % 12600;
					uint32_t m1 = u / 12600;
					uint32_t m2 = n1 / 1260;
					uint32_t n2 = n1 % 1260;
					uint32_t m3 = n2 / 10;
					uint32_t n3 = n2 % 10;

					CharBytes bytes{ 0x90+m1, 0x30+m2, 0x81+m3, 0x30+n3 };
					return fromCharBytes(bytes.data(), bytes.size());
				}

				return 0;  //非法字符
			}

			inline char32_t gbToUnicode(uint32_t c) noexcept
			{
				auto size = getGbCharSize(c);
				if (size == 1)  //单字节区 等同
					return (char32_t)c;

				if (size == 2)  //双字节区 BMP
					return gbToUcsBmp[c];

				if (size == 4)  //四字节区
				{
					auto bytes = getCharBytes(c);
					if (0x81 <= bytes[0] && bytes[0] <= 0x84 &&
						0x30 <= bytes[1] && bytes[1] <= 0x39 &&
						0x81 <= bytes[2] && bytes[2] <= 0xFE &&
						0x30 <= bytes[3] && bytes[3] <= 0x39)
					{
						//BMP-EXT
						auto index = getCharBytes(c % 0x30813081);
						return gbToUcsBmpExt[index[0]][index[1]][index[2]][index[3]];
					}

					//SMP
					uint32_t m1 = bytes[0]-0x90;
					uint32_t m2 = bytes[1]-0x30;
					uint32_t m3 = bytes[2]-0x81;
					uint32_t n3 = bytes[3]-0x30;
					
					uint32_t u = m1 * 12600 + m2 * 1260 + m3 * 10 + n3 + 65536;
					return u;
				}

				return 0;  //非法字符
			}
		}

		size_t GbChar::size() const noexcept
		{
			return internal::getGbCharSize(char_);
		}

		GbChar GbChar::fromUnicode(char32_t u32) noexcept
		{
			return GbChar{ internal::unicodeToGb(u32) };
		}

		char32_t GbChar::toUnicode() const noexcept
		{
			return internal::gbToUnicode(char_);
		}

		GbChar GbChar::fromBytes(const char* data, size_t len) noexcept
		{
			auto bound = internal::getGbCharBound((const uint8_t*)data, len);
			return GbChar{ internal::fromCharBytes((const uint8_t*)data, bound) };
		}

		std::array<uint8_t, 4> GbChar::toBytes() const noexcept
		{
			return internal::getCharBytes(char_);
		}

		GbString GbString::fromUnicode(const char32_t* data, size_t len)
		{
			GbString s;
			s.reserve(len);

			for (size_t i = 0; i < len; ++i)
			{
				auto ch = GbChar::fromUnicode(data[i]);
				if (ch.isNul())
					break;

				s.push_back(ch);
			}

			return s;
		}

		std::u32string GbString::toUnicode() const
		{
			if (length())
			{
				std::u32string s;
				s.reserve(length());

				for (auto ch : *this)
					s.push_back(ch.toUnicode());

				return s;
			}
			return {};
		}

		GbString GbString::fromBytes(const char* data, size_t len)
		{
			GbString s;
			s.reserve(len / 2);

			while (len)
			{
				auto ch = GbChar::fromBytes(data, len);
				if (ch.isNul())
					break;

				s.push_back(ch);

				auto sz = ch.size();
				data += sz;
				len -= sz;
			}

			return s;
		}

		std::string GbString::toBytes() const
		{
			if (length())
			{
				std::string s;
				s.reserve(length() * 2);

				for (auto ch : *this)
				{
					auto bytes = ch.toBytes();
					s.append((const char*)bytes.data(), ch.size());
				}

				return s;
			}
			return {};
		}
	}
}