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
#include "parser.h"
#include <cstring>
#include <sstream>
#include <string>
#include "json.h"

namespace cjson {

	//------------------------------------------------------------------------------------------------------------------
	Parser::Parser(std::istream& _s)
		:mIn(&_s)
		,mOwnStream(false)
	{
		// Intentionally blank
	}

	//------------------------------------------------------------------------------------------------------------------
	Parser::Parser(const char* _s)
		:mOwnStream(true)
	{
		mIn = new std::stringstream(std::string(_s));
	}

	//------------------------------------------------------------------------------------------------------------------
	Parser::~Parser()
	{
		if(mOwnStream)
			delete mIn;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parse(Json& _dst)
	{
		skipWhiteSpace();
		char c = mIn->peek();
		switch (c)
		{
		case 'n': return parseNull(_dst);
		case 't': return parseTrue(_dst);
		case 'f': return parseFalse(_dst);
		case '\"': return parseString(_dst);
		case '[': return parseArray(_dst);
		case '{': return parseObject(_dst);
		default:
			// Is it a number?
			if(c >= '0' && c <= '9' || c == '+' || c == '-')
				return parseNumber(_dst);
			// Unsupported, return parsing error
			return false;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseNull(Json& _dst) {
		char buff[4];
		mIn->read(buff,4);
		return 0 == strncmp("null",buff,4);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseTrue(Json& _dst) {
		if(!strncmp("true",mInput,4)) {
			_dst = true;
			mInput += 4;
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseFalse(Json& _dst) {
		if(!strncmp("false",mInput,5)) {
			_dst = false;
			mInput += 5;
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseNumber(Json& _dst) {
		const char* lastN = mInput+1;
		bool isInt = true;
		const std::string digits("0123456789");
		while(digits.find(*lastN) != std::string::npos)
			++lastN; // Skip digits
		if(*lastN == '.') // Float number
			return parseFloat(_dst);
		else
			return parseInt(_dst);
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseString(Json& _dst) {
		readCh(); // Skip opening quotes
		const char* start = mInput; // Save current position
		bool escaped = false;
		char c = readCh();
		while(escaped || c != '"') {
			if(c == '\0')
				return false; // Unterminated string
			if(escaped || c == '\\')
				escaped ^= 1; // Negace escape state
			c = readCh();
		}
		_dst = std::string(start, mInput-1); // Do not include the quote we just read.
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseArray(Json& _dst) {
		_dst.mType = Json::DataType::array;
		readCh(); // Skip [
		skipWhiteSpace();
		Json element;
		while(tellCh() != ']') {
			// Parse element
			if(!parseJson(element))
				return false;
			_dst.push_back(element);
			// Read upto the next element
			skipWhiteSpace();
			if(tellCh() == ',') {
				readCh();
				skipWhiteSpace();
			}
		}
		readCh(); // Skip ]
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseObject(Json& _dst) {
		_dst.mType = Json::DataType::object;
		readCh(); // Skip {
		skipWhiteSpace();
		Json value;
		std::string key;
		while(tellCh() != '}') {
			// Parse element
			if(!parseObjectEntry(key,value))
				return false;
			_dst[key] = value;
			// Read upto the next element
			skipWhiteSpace();
			if(tellCh() == ',') {
				readCh();
				skipWhiteSpace();
			}
		}
		readCh(); // Skip }
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseInt(Json& _dst) {
		const char* start = mInput;
		char* end;
		_dst = (int)strtol(start, &end, 10);
		mInput = end;
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseFloat(Json& _dst) {
		const char* start = mInput;
		char* end;
		_dst = strtof(start, &end);
		mInput = end;
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	bool Parser::parseObjectEntry(std::string& _oKey, Json& _dst) {
		skipWhiteSpace();
		Json key;
		if(!parseString(key)) // Key 
			return false;
		_oKey = std::string(key);
		skipWhiteSpace();
		if(readCh() != ':')
			return false;
		parseJson(_dst); // Value
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	char Parser::readCh() {
		return *mInput++; // Advance cursor to the next position
	}

	//------------------------------------------------------------------------------------------------------------------
	char Parser::tellCh() {
		return *mInput;
	}

	//------------------------------------------------------------------------------------------------------------------
	void Parser::skipWhiteSpace() {
		const std::string spacers = " \t\n\r";
		while(spacers.find(tellCh()) != std::string::npos)
			readCh();
	}

}	// namespace cjson