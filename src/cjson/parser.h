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
#ifndef _CJSON_PARSER_H_
#define _CJSON_PARSER_H_

namespace cjson {

	class Json;

	///\ class Parser
	///\ brief Parse strings of characters into Json objects
	class Parser {
	public:
		/// Process the input string to replace the content a Json object
		///\ param _code the string to parse. It must contain a well-formed serialized Json.
		///\ param _dst a Json object into which parse results will be stored
		///\ return \c true if able to parse the input string, \c false on error
		bool parse(const char* _code, Json& _dst);

	private:
		bool parseJson(Json& _dst);
		bool parseNull(Json& _dst);
		bool parseFalse(Json& _dst);
		bool parseTrue(Json& _dst);
		bool parseNumber(Json& _dst);
		bool parseString(Json& _dst);
		bool parseArray(Json& _dst);
		bool parseObject(Json& _dst);
		bool parseInt(Json& _dst);
		bool parseFloat(Json& _dst);
		bool parseObjectEntry(std::string& _key, Json& _value);

		char readCh(); ///< Returns the next character in the input stream, and advances the reading cursor
		char tellCh(); ///< Returns the next character in the input stream, but do not advance the reading cursor

		void skipWhiteSpace();

		size_t mCursor;
		const char* mInput;
	};

}	// namespace cjson

#endif // _CJSON_PARSER_H_