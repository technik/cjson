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
#include <vector>

using namespace cjson;
using namespace std;

void forwardIteratorSpecsTest(std::string _raw);

void foreachTest(std::string _raw, std::vector<int> _vals);

void specificDictTest();

int main(int, const char**)
{
	// Test if iterators accomplish cpp forward iterator specs.
	forwardIteratorSpecsTest("[1, 2, 3, 4]" );
	forwardIteratorSpecsTest("{\"key1\":1, \"key2\":2, \"key3\":3, \"key4\":4}" );

	// Generic usage.
	foreachTest("[3, 65, 98]", { 3, 65, 98 });
	foreachTest("{\"key1\":77, \"key2\":125}", { 77, 125 });

	// Test specific dictionary iterator
	specificDictTest();
}

//---------------------------------------------------------------------------------------------------------------------
void forwardIteratorSpecsTest(std::string _raw){
	Json json;
	json.parse(_raw.c_str());

	// Test if iterators accomplish cpp specs. http://www.cplusplus.com/reference/iterator/ForwardIterator/
	// Is default-constructible, copy-constructible, copy-assignable and destructible.
	Json::iterator a;
	Json::iterator b(json.begin());
	a = b;

	// Can be compared.
	assert(a == b);
	assert(!(a != b));

	// Can be derreferenced as rvalue.
	auto c = json.begin();
	assert(*c == 1);
	assert(c->isNumber());

	// Can be dereferenced as lvalue
	Json::iterator d;
	*c = 3;
	assert(*json.begin() == 3);
	
	//Can be incremented.
	++c;
	c++;
	*c++;
	assert(*c == 4);

	// LValues are swappable.
	swap(c, d);
	assert(*d == 4);
}

//---------------------------------------------------------------------------------------------------------------------
void foreachTest(std::string _raw, std::vector<int> _vals){
	Json json;
	json.parse(_raw.c_str());

	int index = 0;
	for (auto elem : json){
		assert(int(elem) == _vals[index]);
		index++;
	}
}

//---------------------------------------------------------------------------------------------------------------------
void specificDictTest(){
	Json jDictionary;
	jDictionary.parse((R""({"key1":56, "key2":658})""));
	Json::iterator iterDict = jDictionary.begin();

	assert(jDictionary[iterDict.key()] == 56);
	++iterDict;
	++iterDict;
	assert(iterDict == jDictionary.end());
}
