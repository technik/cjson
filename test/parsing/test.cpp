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
// Hello world sample
#include <cassert>
#include <cjson/json.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace cjson;
using namespace std;

int main(int, const char**)
{
	// ----- Empty Json -----
	Json j; // Init with empty string gives
	assert(!j.parse("")); // Should give an error. This is no valid Json.
	assert(j.isNull());

	// ----- Basic types -----
	assert(j.parse("true"));
	assert(j.isBool());
	assert(bool(j));
	assert(j.parse("false"));
	assert(j.isBool());
	assert(bool(j) == false);
	assert(j.parse("3"));
	assert(j.isNumber());
	assert(int(j) == 3);
	assert(j.parse("\"3\""));
	assert(j.isString());
	assert(string(j) == "3");

	j.setNull();
	assert(j.isNull());

	// ---- Array and object types ----
	assert(j.parse("[]"));
	assert(j.isArray());
	assert(j.size() == 0);
	j.push_back(3);
	assert(int(j[0u]) == 3);
	assert(j.size() == 1);
	std::string serializedData = 
		"["
		"	3"
		"]";
	assert(j.serialize() == serializedData);
	j = { 2, 3, 4 };
	Json parsed;
	assert(parsed.parse(j.serialize().c_str()));
	assert(int(j[0u]) == 2);
	assert(int(j[1]) == 3);
	assert(int(j[2]) == 4);
}