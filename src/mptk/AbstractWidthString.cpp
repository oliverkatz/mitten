/******************************************************************************
 *                                 _ _   _                                    *
 *                           /\/\ (_) |_| |_ ___ _ __                         *
 *                          /    \| | __| __/ _ \ '_ \                        *
 *                         / /\/\ \ | |_| ||  __/ | | |                       *
 *                         \/    \/_|\__|\__\___|_| |_|                       *
 *                                                                            *
 ******************************************************************************/

/*
 * Copyright (c) 2014, Oliver Katz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "AbstractWidthString.h"

using namespace std;

namespace mitten
{
	void AbstractWidthString::release()
	{
		if (_capacity != 0)
		{
			if (_width == 1)
			{
				delete[] (char *)_data;
			}
			else if (_width == 2)
			{
				delete[] (char16_t *)_data;
			}
			else if (_width == 4)
			{
				delete[] (char32_t *)_data;
			}
			else
			{
				throw runtime_error("invalid character width");
			}
		}

		_data = NULL;
		_size = 0;
		_capacity = 0;
	}

	const float AbstractWidthString::defaultFac = 1.5f;
	const int AbstractWidthString::defaultOff = 1024;
	const size_t AbstractWidthString::npos = (size_t)-1;

	AbstractWidthString::~AbstractWidthString()
	{
		release();
	}

	AbstractWidthString AbstractWidthString::fromCString8(const char *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s, rtn._size);
		rtn._capacity = rtn._size;
		rtn._width = 1;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromCString16(const char16_t *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char16_t[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s, rtn._size*2);
		rtn._capacity = rtn._size*2;
		rtn._width = 2;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromCString32(const char32_t *s)
	{
		AbstractWidthString rtn;
		rtn._size = 0;
		while (s[rtn._size] != 0)
			rtn._size++;
		rtn._data = (void *)new char32_t[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s, rtn._size*4);
		rtn._capacity = rtn._size*4;
		rtn._width = 4;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString8(string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s.data(), rtn._size);
		rtn._capacity = rtn._size;
		rtn._width = 1;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString16(u16string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char16_t[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s.data(), rtn._size*2);
		rtn._capacity = rtn._size*2;
		rtn._width = 2;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::fromString32(u32string s)
	{
		AbstractWidthString rtn;
		rtn._size = s.size();
		rtn._data = (void *)new char32_t[rtn._size];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, s.data(), rtn._size*4);
		rtn._capacity = rtn._size*4;
		rtn._width = 4;
		return rtn;
	}

	bool AbstractWidthString::isResource()
	{
		return (_capacity > 0);
	}

	bool AbstractWidthString::isSlice()
	{
		return (_capacity == 0);
	}

	AbstractWidthString AbstractWidthString::copy()
	{
		AbstractWidthString rtn;
		rtn._size = _size;
		rtn._data = (void *)new char[rtn._size*_width];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		memcpy(rtn._data, _data, rtn._size*_width);
		rtn._capacity = rtn._size*_width;
		rtn._width = _width;
		return rtn;
	}

	AbstractWidthString AbstractWidthString::castToWidth(unsigned char w)
	{
		AbstractWidthString rtn;
		rtn._size = _size;
		rtn._data = (void *)new char[rtn._size*w];
		if (rtn._data == NULL)
			throw runtime_error("unable to allocate");
		
		if (_width == 1)
		{
			char *src = (char *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}
		else if (_width == 2)
		{
			char16_t *src = (char16_t *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}
		else if (_width == 4)
		{
			char32_t *src = (char32_t *)_data;
			if (w == 1)
			{
				char *dst = (char *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char)src[i];
			}
			else if (w == 2)
			{
				char16_t *dst = (char16_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char16_t)src[i];
			}
			else if (w == 4)
			{
				char32_t *dst = (char32_t *)rtn._data;
				for (int i = 0; i < _size; i++)
					dst[i] = (char32_t)src[i];
			}
		}
		else
		{
			throw runtime_error("invalid string width");
		}

		rtn._capacity = rtn._size*w;
		rtn._width = w;
		return rtn;
	}

	const char *AbstractWidthString::toCString8()
	{
		char *dst = new char[_size];
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst[i] = (char)this->operator [] (i);
		}
		return dst;
	}

	const char16_t *AbstractWidthString::toCString16()
	{
		char16_t *dst = new char16_t[_size];
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst[i] = (char16_t)this->operator [] (i);
		}
		return dst;
	}

	const char32_t *AbstractWidthString::toCString32()
	{
		char32_t *dst = new char32_t[_size];
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst[i] = (char32_t)this->operator [] (i);
		}
		return dst;
	}

	std::string AbstractWidthString::toString8()
	{
		std::string dst;
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst.push_back((char)this->operator [] (i));
		}
		return dst;
	}

	std::u16string AbstractWidthString::toString16()
	{
		std::u16string dst;
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst.push_back((char16_t)this->operator [] (i));
		}
		return dst;
	}

	std::u32string AbstractWidthString::toString32()
	{
		std::u32string dst;
		for (int i = 0; i < _size; i++)
		{
			if (this->operator [] (i) == 0)
				break;
			dst.push_back((char32_t)this->operator [] (i));
		}
		return dst;
	}

	const void *AbstractWidthString::data()
	{
		return _data;
	}

	size_t AbstractWidthString::size()
	{
		return _size;
	}

	size_t AbstractWidthString::width()
	{
		return _width;
	}

	size_t AbstractWidthString::memsize()
	{
		return _size*_width;
	}

	size_t AbstractWidthString::capacity()
	{
		return (_capacity == 0 ? (size_t)-1 : _capacity);
	}

	size_t AbstractWidthString::memcapacity()
	{
		return (_capacity == 0 ? (size_t)-1 : _capacity*_width);
	}

	void AbstractWidthString::reallocate(size_t s)
	{
		if (_capacity == 0)
		{
			throw runtime_error("cannot reallocate slice");
		}

		if (s == 0)
		{
			throw runtime_error("cannot allocate no space for string");
		}

		if (_width == 1)
		{
			void *tmp = (void *)new char[s];
			if (tmp == NULL)
				throw runtime_error("unable to allocate");

			memcpy(tmp, _data, s);
			if (s > _size)
				memset((char *)tmp+_size, 0, s-_size);
			else
				_size = s;
			delete[] (char *)_data;
			_data = tmp;
			_capacity = s;
		}
		else if (_width == 2)
		{
			void *tmp = (void *)new char16_t[s];
			if (tmp == NULL)
				throw runtime_error("unable to allocate");

			memcpy(tmp, _data, s);
			if (s > _size)
				memset((char16_t *)tmp+_size, 0, s-_size);
			else
				_size = s;
			delete[] (char16_t *)_data;
			_data = tmp;
			_capacity = s;
		}
		else if (_width == 4)
		{
			void *tmp = (void *)new char32_t[s];
			if (tmp == NULL)
				throw runtime_error("unable to allocate");

			memcpy(tmp, _data, s);
			if (s > _size)
				memset((char32_t *)tmp+_size, 0, s-_size);
			else
				_size = s;
			delete[] (char32_t *)_data;
			_data = tmp;
			_capacity = s;
		}
		else
		{
			throw runtime_error("invalid string width");
		}
	}

	void AbstractWidthString::resize(size_t s)
	{
		if (_capacity == 0)
		{
			if (s > _size)
				throw runtime_error("cannot resize slice outside of boundaries");
			_size = s;
		}
		else
		{
			if (s > _capacity)
				throw runtime_error("cannot resize resource outside of memory space");
			else if (s > _size)
			{
				while (s > _size)
				{
					if (this->operator [] (_size) == 0)
						break;
					_size++;
				}
			}
			else
			{
				_size = s;
			}
		}
	}

	char32_t AbstractWidthString::operator [] (int n)
	{
		if (_width == 1)
		{
			return ((char *)_data)[n];
		}
		else if (_width == 2)
		{
			return ((char16_t *)_data)[n];
		}
		else if (_width == 4)
		{
			return ((char32_t *)_data)[n];
		}
	}

	int AbstractWidthString::compare(AbstractWidthString s)
	{
		if (size() < s.size())
		{
			return -1;
		}
		else if (size() > s.size())
		{
			return 1;
		}
		else
		{
			for (size_t i = 0; i < size(); i++)
			{
				char32_t me = this->operator [] ((int)i);
				char32_t them = s[(int)i];

				if (me == 0 || them == 0)
					break;

				if (me < them)
				{
					return -1;
				}
				else if (me > them)
				{
					return 1;
				}
			}
		}

		return 0;
	}

	bool AbstractWidthString::operator == (AbstractWidthString s)
	{
		return (compare(s) == 0);
	}

	bool AbstractWidthString::operator != (AbstractWidthString s)
	{
		return (compare(s) != 0);
	}

	bool AbstractWidthString::operator < (AbstractWidthString s)
	{
		return (compare(s) < 0);
	}

	bool AbstractWidthString::operator <= (AbstractWidthString s)
	{
		return (compare(s) <= 0);
	}

	bool AbstractWidthString::operator > (AbstractWidthString s)
	{
		return (compare(s) > 0);
	}

	bool AbstractWidthString::operator >= (AbstractWidthString s)
	{
		return (compare(s) >= 0);
	}

	AbstractWidthString &AbstractWidthString::append(AbstractWidthString s, float fac, int off)
	{
		if (s._size == 0)
		{
			return *this;
		}

		if (_size == 0)
		{
			*this = s.copy();
		}

		if (fac == 0.0 && off == 0)
		{
			throw runtime_error("cannot have dynamic allocation factor of 0.0 with offset 0 - no increase");
		}

		size_t cap = _capacity;
		while (s.size()+_size > cap)
		{
			cap *= fac;
			cap += off;
		}

		if (_width != s._width)
			s = s.castToWidth(_width);

		reallocate(cap);
		memcpy((char *)_data+(_size*_width), s._data, s._size*_width);
		resize(_size+s._size);

		return *this;
	}

	AbstractWidthString &AbstractWidthString::operator += (AbstractWidthString s)
	{
		return append(s);
	}

	AbstractWidthString &AbstractWidthString::append(char32_t c, float fac, int off)
	{
		if (fac == 0.0 && off == 0)
		{
			throw runtime_error("cannot have dynamic allocation factor of 0.0 with offset 0 - no increase");
		}

		size_t cap = _capacity;
		while (_size+1 > cap)
		{
			cap *= fac;
			cap += off;
		}

		reallocate(cap);
		memcpy((char *)_data+(_size*_width), &c, _width);
		resize(_size+1);

		return *this;
	}

	AbstractWidthString AbstractWidthString::substr(size_t from, size_t len)
	{
		if (from+len >= _size)
			throw runtime_error("out of range substring");

		AbstractWidthString rtn = *this;
		rtn._data = (void *)(((char *)rtn._data)+from*_width);
		if (len == (size_t)-1)
		{
			rtn._size -= from;
		}
		else
		{
			rtn._size = len;
		}

		return rtn;
	}

	AbstractWidthString &AbstractWidthString::insert(size_t pos, AbstractWidthString s, float fac, int off)
	{
		AbstractWidthString me = copy();
		resize(pos);
		append(s);
		append(me.substr(pos));

		return *this;
	}

	AbstractWidthString &AbstractWidthString::erase(size_t from, size_t len)
	{
		AbstractWidthString me = copy();
		resize(from);
		append(me.substr(from+len));

		return *this;
	}

	size_t AbstractWidthString::find(AbstractWidthString s, size_t from)
	{
		for (size_t i = from; i < _size-s._size; i++)
		{
			if (substr(i, s._size).compare(s) == 0)
			{
				return i;
			}
		}

		return npos;
	}

	size_t AbstractWidthString::rfind(AbstractWidthString s, size_t after)
	{
		for (size_t i = _size-s._size-1; i >= after; i--)
		{
			if (substr(i, s._size).compare(s) == 0)
			{
				return i;
			}
		}

		return npos;
	}

	AbstractWidthString AbstractWidthString::evaluateEscapeCodes()
	{
		AbstractWidthString rtn;

		for (int i = 0; i < size(); i++)
		{
			if (this->operator [] (i) == '\\')
			{
				if (i == size()-1)
				{
					throw runtime_error("escape code ended prematurely");
				}
				else
				{
					if (this->operator [] (i+1) == 'a')
					{
						rtn += '\a';
						i++;
					}
					else if (this->operator [] (i+1) == 'b')
					{
						rtn += '\b';
						i++;
					}
					else if (this->operator [] (i+1) == 'f')
					{
						rtn += '\f';
						i++;
					}
					else if (this->operator [] (i+1) == 'n')
					{
						rtn += '\n';
						i++;
					}
					else if (this->operator [] (i+1) == 'r')
					{
						rtn += '\r';
						i++;
					}
					else if (this->operator [] (i+1) == 't')
					{
						rtn += '\t';
						i++;
					}
					else if (this->operator [] (i+1) == 'v')
					{
						rtn += '\v';
						i++;
					}
					else if (this->operator [] (i+1) == '\\')
					{
						rtn += '\\';
						i++;
					}
					else if (this->operator [] (i+1) == '\'')
					{
						rtn += '\'';
						i++;
					}
					else if (this->operator [] (i+1) == '\"')
					{
						rtn += '\"';
						i++;
					}
					else if (this->operator [] (i+1) == '?')
					{
						rtn += '\?';
						i++;
					}
					else if (this->operator [] (i+1) >= '0' && this->operator [] (i+1) <= '7')
					{
						if (i+3 < size())
						{
							char tmp = stoi(substr(i+1, 3).toString8(), NULL, 8);
							rtn += tmp;
							i += 3;
						}
						else
						{
							throw runtime_error("escape code ended prematurely");
						}
					}
					else if (this->operator [] (i+1) == 'x')
					{
						if (i+3 < size())
						{
							char tmp = stoi(substr(i+2, 2).toString8(), NULL, 16);
							rtn += tmp;
							i += 3;
						}
						else
						{
							throw runtime_error("escape code ended prematurely");
						}
					}
					else
					{
						throw runtime_error("unexpected character");
					}
				}
			}
			else
			{
				rtn += this->operator [] (i);
			}
		}

		return rtn;
	}
}
