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
#include "json.h"
#include "serializer.h"
#include <sstream>
#include <new> // Placement new

namespace cjson {

	//------------------------------------------------------------------------------------------------------------------
	std::string Json::serialize() const {
		Serializer s;
		return s.serialize(*this);
	}

	//------------------------------------------------------------------------------------------------------------------
	void Json::setNull() {
		clear(); // Clear internal elements if necessary (must be done before changing type)
		mType = DataType::null; // Reset type
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(const std::string& _s)
		: mText(_s)
	{
		mType = DataType::text;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(std::string&& _s)
		: mText(std::move(_s))
	{
		mType = DataType::text;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(const std::string& _s) {
		clear();
		new(this)Json(_s);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(std::string&& _s) {
		clear();
		new(this)Json(std::move(_s));
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Json::clear() {
		// Clear internal elements if necessary
		switch(mType) {
		case DataType::array:
			for(const auto& element : mArray)
				delete element;
			break;
		case DataType::object:
			for(const auto& element : mObject)
				delete element.second;
			break;
		default:
			break;
		}
	}

}	// namespace cjson