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
	assert(j.parse("-3"));
	assert(j.isNumber());
	assert(int(j) == -3);
	assert(j.parse("-3.0"));
	assert(j.isNumber());
	assert(float(j) == -3.f);
	assert(j.parse("-3.4"));
	assert(float(j) == -3.4f);

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
	assert(j(0) == 3);
	assert(j.size() == 1);
	std::string serializedData = 
		"[\n"
		"	3\n"
		"]";
	assert(j.serialize() == serializedData);
	j = { 2, 3, 4 };
	Json parsed;
	assert(parsed.parse(j.serialize().c_str()));
	assert(parsed.size() == 3);
	assert(parsed(0) == 2);
	assert(parsed(1) == 3);
	assert(parsed(2) == 4);

	// ---- Object tests ----
	assert(j.parse("{}"));
	assert(j.isObject());
	assert(j.size() == 0);
	j["key"] = "value";
	assert(j.size() == 1);
	assert(j.contains("key"));
	assert(string(j["key"]) == "value");
	assert(j.parse(R""(	 {		"foo"	:		"bar \""	 } )"")); // Spaced test
	assert(!j.parse(R"({ "bar" :")")); // Incomplete test
	j["key"] = Json("value");	// Assignation of Json of of type Text.
	assert(string(j["key"]) == "value");

	Json js;
	js.parse(R"({"type":"dummy", "data":{"state":true}})");
	assert(js.isObject());
	assert(js.size() == 2);
	assert(js.contains("type"));
	assert(js["type"].isString());
	assert(js["type"] == "dummy");
	assert(js.contains("data"));
	assert(js["data"].isObject());
	assert(js["data"].size() == 1);
	assert(js["data"].contains("state"));
	assert(bool(js["data"]["state"]) == true);

	// --- Cumulative dictionary testing
	Json cumulative;
	cumulative.parse(R"({"x":{"x1":1, "x2":2}, "y":{"y1":4, "y2":5}})");
	assert(cumulative.size() == 2);
	assert(cumulative["x"].size() == 2);
	assert(cumulative["y"].size() == 2);
}