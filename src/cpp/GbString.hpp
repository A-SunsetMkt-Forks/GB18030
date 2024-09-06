#pragma once

#include <array>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace gb18030
{
	inline namespace v2022
	{
		// GB18030字符
		class GbChar
		{
		public:
			// 初始化为空字符
			GbChar() noexcept
				: char_(0)
			{}

			// 从GB18030编码数值得到GB18030字符
			GbChar(uint32_t gbCharValue) noexcept
				: char_(gbCharValue)
			{}

			~GbChar() noexcept = default;

			GbChar(const GbChar& other) noexcept = default;
			GbChar& operator=(const GbChar& right) noexcept = default;

			GbChar(GbChar&& other) noexcept = default;
			GbChar& operator=(GbChar&& right) noexcept = default;

			// 判断是否空字符
			bool isNul() const noexcept
			{
				return char_ == 0;
			}

			// 获取字符字节大小
			size_t size() const noexcept;

			// 从Unicode字符得到GB18030字符
			static GbChar fromUnicode(char32_t u32) noexcept;

			// 转换到Unicode字符
			char32_t toUnicode() const noexcept;

			// 从字节流获取字符
			//
			// 仅获取第一个字符
			static GbChar fromBytes(const char* data, size_t len) noexcept;

			// 获取字符字节
			std::array<uint8_t, 4> toBytes() const noexcept;

			// 获取数值
			uint32_t value() const noexcept
			{
				return char_;
			}
			
		private:
			uint32_t char_;
		};


		// GB18030字符串
		//
		// GB18030是1、2、4变长字符编码 这里为了方便编辑采用固定4字节存储
		// fromBytes和toBytes都是变长字节流
		class GbString
		{
		public:
			// 适配容器接口
			using Data = std::vector<GbChar>;
			using size_type = Data::size_type;
			using value_type = Data::value_type;
			using reference = Data::reference;
			using const_reference = Data::const_reference;
			using iterator = Data::iterator;
			using const_iterator = Data::const_iterator;
			using reverse_iterator = Data::reverse_iterator;
			using const_reverse_iterator = Data::const_reverse_iterator;

			// 空字符串
			GbString() noexcept = default;

			GbString(const GbString& other) = default;
			GbString& operator=(const GbString& right) = default;

			GbString(GbString&& other) noexcept = default;
			GbString& operator=(GbString&& right) = default;

			void swap(GbString& other) noexcept
			{
				data_.swap(other.data_);
			}

			// 检查字符串是否为空
			bool empty() const noexcept
			{
				return data_.empty();
			}

			// 获取字符串长度
			//
			// 字符串的字符数量
			size_type length() const noexcept
			{
				return data_.size();
			}

			// 获取指定位置字符
			reference at(size_type index)
			{
				return data_.at(index);
			}

			// 获取指定位置字符
			const_reference at(size_type index) const
			{
				return data_.at(index);
			}

			// 获取指定位置字符
			reference operator[](size_type index) noexcept
			{
				return data_[index];
			}

			// 获取指定位置字符
			const_reference operator[](size_type index) const noexcept
			{
				return data_[index];
			}

			// 从Unicode字符串获取GB18030字符串
			static GbString fromUnicode(const char32_t* data, size_t len);

			// 转换到Unicode字符串
			std::u32string toUnicode() const;

			// 从字节流获取GB18030字符串
			static GbString fromBytes(const char* data, size_t len);

			// 转换到GB18030字节流
			std::string toBytes() const;

		private:
			Data data_;
		};
	}
}