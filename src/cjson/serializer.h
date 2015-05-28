//----------------------------------------------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015 Carmelo J. Fernández-Agüera Tortosa
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//----------------------------------------------------------------------------------------------------------------------
// Simple Json C++ library
//----------------------------------------------------------------------------------------------------------------------
#ifndef _CJSON_SERIALIZER_H_
#define _CJSON_SERIALIZER_H_

#include <string>
#include <sstream>
#include "json.h"

namespace cjson {

	class Serializer {
	public:
		std::string serialize(const Json&);

	private:
		bool push(const Json&, std::stringstream& _dst, size_t _tab = 0);
		bool push(bool, std::stringstream& _dst, size_t _tab = 0);
		bool push(int, std::stringstream& _dst, size_t _tab = 0);
		bool push(float, std::stringstream& _dst, size_t _tab = 0);
		bool push(const std::string&, std::stringstream& _dst, size_t _tab = 0);
		bool push(const Json::Array&, std::stringstream& _dst, size_t _tab = 0);
		bool push(const Json::Dictionary&, std::stringstream& _dst, size_t _tab = 0);

		void tabify(std::stringstream& _dst, size_t _tab);
	};

}	// namespace cjson

#endif // _CJSON_SERIALIZER_H_