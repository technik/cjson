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

void specificArrayTest();
void specificDictTest();

int main(int, const char**)
{
	// Test if iterators accomplish cpp forward iterator specs.
	forwardIteratorSpecsTest("[1, 2, 3, 4]" );
	forwardIteratorSpecsTest("{\"key1\":1, \"key2\":2, \"key3\":3, \"key4\":4}" );

	// Generic usage.
	foreachTest("[3, 65, 98]", { 3, 65, 98 });
	foreachTest("{\"key1\":77, \"key2\":125}", { 77, 125 });

	// Test Array iterators
	specificArrayTest();
	
	// Test Dictionary iterator
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
	assert(int(*c) == 1);
	assert(c->isNumber());

	// Can be dereferenced as lvalue
	Json::iterator d;
	*d = 3;

	//Can be incremented.
	++c;
	c++;
	*c++;

	// LValues are swappable.
	swap(c, d);
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
void specificArrayTest(){
	Json jArray;
	jArray.parse("[1, 2, 3]");
	Json::iterator iterArray = jArray.begin();
	assert(*iterArray == 1);

	assert(iterArray->serialize() == "1");
	++iterArray;
	assert(iterArray->serialize() == "2");
	++iterArray;
	assert(iterArray->serialize() == "3");
	++iterArray;
	assert(iterArray == jArray.end());
}

//---------------------------------------------------------------------------------------------------------------------
void specificDictTest(){
	Json jDictionary;
	jDictionary.parse((R""({"key1":56, "key2":658})""));
	Json::iterator iterDict = jDictionary.begin();

	assert(*iterDict == 56);

	assert(jDictionary[iterDict.key()] == 56);
	++iterDict;
	assert(jDictionary[iterDict.key()] == 658);
	++iterDict;
	assert(iterDict == jDictionary.end());
}
