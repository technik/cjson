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
#include <cassert>
#include <cjson/json.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace cjson;
using namespace std;

//----------------------------------------------------------------------------------------------------------------------
// Manage global news and deletes
size_t gNewCount = 0;
size_t gDeleteCount = 0;
void* operator new(size_t _count){
	++gNewCount;
	return malloc(_count);
}

void* operator new[](size_t _count){
	gNewCount;
	return malloc(_count);
}

void operator delete(void* _ptr) {
	--gDeleteCount;
	return free(_ptr);
}

void operator delete[](void* _ptr) {
	--gDeleteCount;
	return free(_ptr);
}

bool isMemoryBalanced() {
	return gNewCount == gDeleteCount;
}
//----------------------------------------------------------------------------------------------------------------------

int main(int, const char**)
{
	// Force creation and destruction by making a local scope
	{
		Json j;
		j.parse(R"({
					"NVDA": {
						"c63": "-0.04",
						"g53": "28.35",
						"h53": "28.76",
						"l84": "28.41",
						"v53": "6,383,264"
					}
				})");
	}
	assert(isMemoryBalanced());
}