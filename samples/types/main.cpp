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
#include <cjson/json.h>
#include <iostream>
#include <vector>

using namespace cjson;

int main(int, const char**)
{
	Json vectorJson = std::vector<int>({1, 1, 2, 3, 5, 8});
	std::cout << "vectorJson:\n" << vectorJson.serialize() << std::endl;

	Json listVector { "yep", "foo", "bar" };
	std::cout << "vectorJson:\n" << vectorJson.serialize() << std::endl;

	Json complexList {Json{"a", "b", "c"}, Json{"a", "b", "c"}};
	std::cout << "complex Json:\n" << vectorJson.serialize() << std::endl;

	return 0;
}