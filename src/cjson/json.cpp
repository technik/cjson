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
#include "parser.h"
#include "serializer.h"
#include <cassert>
#include <new> // Placement new
#include <sstream>

namespace cjson {

	//------------------------------------------------------------------------------------------------------------------
	bool Json::parse(const char* _code) {
		Parser p;
		if(p.parse(_code, *this))
			return true;
		setNull(); // Something went wrong, reset.
		return false;
	}

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
	Json::Json(bool _b)
		: mType(DataType::boolean)
	{
		mNumber.b = _b;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(int _i)
		: mType(DataType::integer)
	{
		mNumber.i = _i;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(unsigned _u)
		: mType(DataType::integer)
	{
		mNumber.i = int(_u);
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(float _f)
		: mType(DataType::real)
	{
		mNumber.f = _f;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(const char* _s)
		: mText(_s)
		, mType(DataType::text)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(const std::string& _s)
		: mText(_s)
		, mType(DataType::text)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::Json(std::string&& _s)
		: mText(std::move(_s))
		, mType(DataType::text)
	{
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(bool _b) {
		clear();
		new(this)Json(_b);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(int _i) {
		clear();
		new(this)Json(_i);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(unsigned _u) {
		return this->operator=(int(_u));
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(float _f) {
		clear();
		new(this)Json(_f);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator=(const char* _s) {
		clear();
		new(this)Json(_s);
		return *this;
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
	Json::operator bool() const {
		assert(mType == DataType::boolean || mType == DataType::integer);
		return mNumber.b;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::operator int() const {
		assert(mType == DataType::integer);
		return mNumber.i;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::operator float() const {
		assert(mType == DataType::real);
		return mNumber.f;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json::operator std::string() const {
		assert(mType == DataType::text);
		return mText;
	}

	//------------------------------------------------------------------------------------------------------------------
	const Json& Json::operator()(size_t _n) const {
		assert(mType == DataType::array);
		return *mArray[_n];
	}

	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator()(size_t _n) {
		assert(mType == DataType::array);
		return *mArray[_n];
	}
	
	//------------------------------------------------------------------------------------------------------------------
	const Json& Json::operator[](const char* _key) const {
		assert(mType == DataType::object);
		return *mObject.find(_key)->second;
	}
	
	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator[](const char* _key) {
		if(mType != DataType::object) {
			clear();
			mType = DataType::object;
		}
		Json*& objRef = mObject[_key];
		if(objRef == nullptr)
			objRef = new Json();
		return *objRef;
	}
	
	//------------------------------------------------------------------------------------------------------------------
	const Json& Json::operator[](const std::string& _key) const {
		assert(mType == DataType::object);
		return *mObject.find(_key)->second;
	}
	
	//------------------------------------------------------------------------------------------------------------------
	Json& Json::operator[](const std::string& _key) {
		if(mType != DataType::object) {
			clear();
			mType = DataType::object;
		}
		Json*& objRef = mObject[_key];
		if(objRef == nullptr)
			objRef = new Json();
		return *objRef;
	}

	//------------------------------------------------------------------------------------------------------------------
	size_t Json::size() const {
		assert(mType == DataType::array || mType == DataType::object || mType == DataType::text);
		switch (mType)
		{
		case cjson::Json::DataType::text:
			return mText.size();
		case cjson::Json::DataType::array:
			return mArray.size();
		case cjson::Json::DataType::object:
			return mObject.size();
		default:
			assert(false);
			return size_t(-1);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Json::contains(const std::string& _key) const {
		assert(mType == DataType::object);
		return mObject.find(_key) != mObject.end();
	}

	//------------------------------------------------------------------------------------------------------------------
	void Json::clear() {
		// Clear internal elements if necessary
		switch(mType) {
		case DataType::array:
			for(const auto& element : mArray)
				delete element;
			mArray.clear();
			break;
		case DataType::object:
			for(const auto& element : mObject)
				delete element.second;
			mObject.clear();
			break;
		default:
			break;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	JsonIterator Json::begin(){
		return JsonIterator(*this, 0);
	}


	//------------------------------------------------------------------------------------------------------------------
	JsonIterator Json::end(){
		return JsonIterator(*this, size());
	}

	//------------------------------------------------------------------------------------------------------------------
	// Iterator class definition
	JsonIterator::JsonIterator(Json &_json, int _pos){
		mIsArray = _json.isArray();
		if (mIsArray){
			mIterArray =  _json.mArray.begin() + _pos;
		}
		else{
			mIterObject = _json.mObject.begin() ;

			while (_pos-- < 0){
				mIterObject--;
			}
		}
	}


	//------------------------------------------------------------------------------------------------------------------
	Json JsonIterator::operator*(){
		if (mIsArray){
			return *mIterArray;
		}
		else{
			mIterObject->second;
		}
		
	}

	//------------------------------------------------------------------------------------------------------------------
	JsonIterator& JsonIterator::operator++(){
		if (mIsArray){
			mIterArray++;
		}
		else{
			mIterObject++;
		}

		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	Json* JsonIterator::operator->(){
		if (mIsArray){
			return *mIterArray;
		}
		else{
			return mIterObject->second;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	std::string JsonIterator::key(){
		assert(!mIsArray);

		return mIterObject->first;
	}

	//------------------------------------------------------------------------------------------------------------------
}	// namespace cjson