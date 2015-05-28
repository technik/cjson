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
#ifndef _CJSON_JSON_INL_
#define _CJSON_JSON_INL_

#include "json.h" // This will actually be ignored due to guards, but works for intellisense.
#include <utility> // std::move

namespace cjson {

	//------------------------------------------------------------------------------------------------------------------
	inline Json::Json() 
		: mType (DataType::null)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	inline Json::Json(const Json& _x)
		: mType (_x.mType)
	{
		switch(mType) {
		case DataType::boolean:
		case DataType::integer:
		case DataType::real:
			mNumber = _x.mNumber;
			break;
		case DataType::array:
			mArray = _x.mArray;
			break;
		case DataType::object:
			mObject = _x.mObject;
			break;
		default: // Do nothing for null
			break;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	inline Json::Json(Json&& _x)
		: mType(_x.mType)
	{
		switch(mType) {
		case DataType::boolean:
		case DataType::integer:
		case DataType::real:
			mNumber = _x.mNumber;
			break;
		case DataType::array:
			mArray = std::move(_x.mArray);
			_x.mType = DataType::null;
			break;
		case DataType::object:
			mObject = std::move(_x.mObject);
			_x.mType = DataType::null;
			break;
		default: // Do nothing for null
			break;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	inline Json& Json::operator=(const Json& _x)
	{
		mType = _x.mType;
		switch(mType) {
		case DataType::boolean:
		case DataType::integer:
		case DataType::real:
			mNumber = _x.mNumber;
			break;
		case DataType::array:
			mArray = _x.mArray;
			break;
		case DataType::object:
			mObject = _x.mObject;
			break;
		default: // Do nothing for null
			break;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	inline Json& Json::operator=(Json&& _x)
	{
		mType = _x.mType;
		switch(mType) {
		case DataType::boolean:
		case DataType::integer:
		case DataType::real:
			mNumber = _x.mNumber;
			break;
		case DataType::array:
			mArray = std::move(_x.mArray);
			_x.mType = DataType::null;
			break;
		case DataType::object:
			mObject = std::move(_x.mObject);
			_x.mType = DataType::null;
			break;
		default: // Do nothing for null
			break;
		}
	}

} // namespace cjson

#endif // _CJSON_JSON_INL_