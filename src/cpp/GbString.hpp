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
		// GB18030�ַ�
		class GbChar
		{
		public:
			// ��ʼ��Ϊ���ַ�
			GbChar() noexcept
				: char_(0)
			{}

			// ��GB18030������ֵ�õ�GB18030�ַ�
			GbChar(uint32_t gbCharValue) noexcept
				: char_(gbCharValue)
			{}

			~GbChar() noexcept = default;

			GbChar(const GbChar& other) noexcept = default;
			GbChar& operator=(const GbChar& right) noexcept = default;

			GbChar(GbChar&& other) noexcept = default;
			GbChar& operator=(GbChar&& right) noexcept = default;

			// �ж��Ƿ���ַ�
			bool isNul() const noexcept
			{
				return char_ == 0;
			}

			// ��ȡ�ַ��ֽڴ�С
			size_t size() const noexcept;

			// ��Unicode�ַ��õ�GB18030�ַ�
			static GbChar fromUnicode(char32_t u32) noexcept;

			// ת����Unicode�ַ�
			char32_t toUnicode() const noexcept;

			// ���ַ�����������ȡ�ַ�
			//
			// �� "\xBA\xBA"
			template <size_t N>
			static GbChar fromBytes(const char(&literal)[N]) noexcept
			{
				return fromBytes(literal, N-1);
			}

			// ���ֽ�����ȡ�ַ�
			//
			// ����ȡ��һ���ַ�
			static GbChar fromBytes(const char* data, size_t len) noexcept;

			// ��ȡ�ַ��ֽ�
			std::array<uint8_t, 4> toBytes() const noexcept;

			// ��ȡ��ֵ
			uint32_t value() const noexcept
			{
				return char_;
			}
			
		private:
			uint32_t char_;
		};


		// GB18030�ַ���
		//
		// GB18030��1��2��4�䳤�ַ����� ����Ϊ�˷���༭���ù̶�4�ֽڴ洢
		// fromBytes��toBytes���Ǳ䳤�ֽ���
		class GbString
		{
		public:
			// ���������ӿ�
			using Data = std::vector<GbChar>;
			using size_type = Data::size_type;
			using value_type = Data::value_type;
			using reference = Data::reference;
			using const_reference = Data::const_reference;
			using iterator = Data::iterator;
			using const_iterator = Data::const_iterator;
			using reverse_iterator = Data::reverse_iterator;
			using const_reverse_iterator = Data::const_reverse_iterator;

			// ���ַ���
			GbString() noexcept = default;

			GbString(const GbString& other) = default;
			GbString& operator=(const GbString& right) = default;

			GbString(GbString&& other) noexcept = default;
			GbString& operator=(GbString&& right) = default;

			void swap(GbString& other) noexcept
			{
				data_.swap(other.data_);
			}

			// ����ַ����Ƿ�Ϊ��
			bool empty() const noexcept
			{
				return data_.empty();
			}

			// ��ȡ�ַ�������
			//
			// �ַ������ַ�����
			size_type length() const noexcept
			{
				return data_.size();
			}

			// ����ָ����С�ռ�
			void reserve(size_t len)
			{
				data_.reserve(len);
			}

			// �����ַ�
			//
			// ����STL�����ӿ�
			void push_back(GbChar c)
			{
				data_.push_back(c);
			}

			// ��ȡָ��λ���ַ�
			reference at(size_type index)
			{
				return data_.at(index);
			}

			// ��ȡָ��λ���ַ�
			const_reference at(size_type index) const
			{
				return data_.at(index);
			}

			// ��ȡָ��λ���ַ�
			reference operator[](size_type index) noexcept
			{
				return data_[index];
			}

			// ��ȡָ��λ���ַ�
			const_reference operator[](size_type index) const noexcept
			{
				return data_[index];
			}

			// ��ʼ������
			//
			// ����STL�����ӿ�
			iterator begin() noexcept
			{
				return data_.begin();
			}

			// ��ֹ������
			//
			// ����STL�����ӿ�
			iterator end() noexcept
			{
				return data_.end();
			}

			// ֻ����ʼ������
			//
			// ����STL�����ӿ�
			const_iterator begin() const noexcept
			{
				return data_.begin();
			}

			// ֻ����ֹ������
			//
			// ����STL�����ӿ�
			const_iterator end() const noexcept
			{
				return data_.end();
			}

			// ������ʼ������
			//
			// ����STL�����ӿ�
			reverse_iterator rbegin() noexcept
			{
				return data_.rbegin();
			}

			// �������������
			//
			// ����STL�����ӿ�
			reverse_iterator rend() noexcept
			{
				return data_.rend();
			}

			// ֻ��������ʼ������
			//
			// ����STL�����ӿ�
			const_reverse_iterator rbegin() const noexcept
			{
				return data_.rbegin();
			}

			// ֻ���������������
			//
			// ����STL�����ӿ�
			const_reverse_iterator rend() const noexcept
			{
				return data_.rend();
			}

			// ��Unicode�ַ�����������ȡGB18030�ַ���
			//
			// �� U"�й����ĺ���"
			template <size_t N>
			static GbString fromUnicode(const char32_t(&literal)[N])
			{
				return fromUnicode(literal, N-1);
			}

			// ��Unicode�ַ�����ȡGB18030�ַ���
			static GbString fromUnicode(const char32_t* data, size_t len);

			// ת����Unicode�ַ���
			std::u32string toUnicode() const;

			// ���ַ�����������ȡGB18030�ַ���
			//
			// �� "\xd6\xd0\xb9\xfa\xd6\xd0\xce\xc4\xba\xba\xd7\xd6"
			template <size_t N>
			static GbString fromBytes(const char(&literal)[N])
			{
				return fromBytes(literal, N-1);
			}

			// ���ֽ�����ȡGB18030�ַ���
			static GbString fromBytes(const char* data, size_t len);

			// ת����GB18030�ֽ���
			std::string toBytes() const;

		private:
			Data data_;
		};
	}
}