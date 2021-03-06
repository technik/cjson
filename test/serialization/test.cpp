//----------------------------------------------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015 Carmelo J. Fern�ndez-Ag�era Tortosa
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
	Json j;
	assert(j.isNull());
	assert(j.serialize() == "null"); // An empty Json is null type

	// ----- Basic types -----
	j = true;
	assert(j.isBool());
	assert(j.serialize() == "true");
	j = false;
	assert(j.isBool());
	assert(j.serialize() == "false");
	j = 3;
	assert(j.isNumber());
	assert(j.serialize() == "3");
	j = "3";
	assert(j.isString());
	assert(j.serialize() == "\"3\"");
	stringstream ss;
	j.serialize(ss);
	assert(ss.str() == j.serialize());
	
	Json j2(""); // Note this is not an empty Json, it is a String Json with an empty string
	assert(j2.isString());
	assert(j2.serialize() == "\"\"");

	Json twoLevel;
	twoLevel["on"] = true;
	std::string serial = twoLevel.serialize();
	assert(serial == R"({
	"on": true
})");
}