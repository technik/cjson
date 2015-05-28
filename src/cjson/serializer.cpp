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
#include "serializer.h"
#include "json.h"

#include <cassert>

using namespace std;

namespace cjson {
	//------------------------------------------------------------------------------------------------------------------
	string Serializer::serialize(const Json& _j) {
		stringstream oStream;
		if(push(_j, oStream))
			return oStream.str();
		else
			return ""; // Some error occurred
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Serializer::push(const Json& _j, stringstream& _oStream, size_t _tab) {
		switch (_j.mType)
		{
		case Json::DataType::null:
			tabify(_oStream, _tab);
			_oStream << "null";
			return true;
		case Json::DataType::boolean:
			return push(_j.mNumber.b, _oStream, _tab);
		case Json::DataType::integer:
			return push(_j.mNumber.i, _oStream, _tab);
		case Json::DataType::real:
			return push(_j.mNumber.f, _oStream, _tab);
		case Json::DataType::text:
			return push(_j.mText, _oStream, _tab);
		case Json::DataType::array:
			return push(_j.mArray, _oStream, _tab);
		case Json::DataType::object:
			return push(_j.mObject, _oStream, _tab);
		default:
			return false; // Error data type
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	bool 
}	// namespace cjson