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
#ifndef _CJSON_JSON_H_
#define _CJSON_JSON_H_

#include <string>
#include <vector>
#include <map>

namespace cjson {

	/// Json object
	/// Encapsulates all the functionality to operate with json objects.
	class Json {
	public:
		// ----- Basic construction and destruction -----
		Json(); ///< Default constructor. Creates an empty json.
		Json(const Json&); ///< Copy constructor. Performs a deep copy.
		Json(Json&&); ///< Move constructor.
		Json& operator=(const Json&); ///< Deep copy assignment.
		Json& operator=(Json&&); ///< Move asignment.
		~Json(); ///< Destructor

		// ----- Parsing and generation -----
		/// param _code a string containing a formated json.
		void parse	(const char* _code);
		/// generate a string with the formated content of the json object
		std::string serialize() const;

		// ----- Useful methods -----
		void setNull	() const; ///< Reset object to default construction state

		bool isNull		() const;
		bool isNumber	() const;
		bool isString	() const;
		bool isArray	() const;
		bool isObject	() const;

		// ----- Construction from base types -----
		Json(bool);
		Json(int);
		Json(float);
		Json(const char*);
		Json(const std::string&);
		template<typename T_, template<typename> List_>
		Json(const List_<T_>& _list); ///< Construct from any type that can be traversed as a vector
		template<typename Val_, template<typename,typename> Map_, typename Key_ = std::string> ///< Construct from any type that can be traversed as a map
		Json(const Map_<Key_,Val_>&);

		// ----- Assignment from base types -----
		Json& operator=(bool);
		Json& operator=(int);
		Json& operator=(float);
		Json& operator=(const char*);
		Json& operator=(const std::string&);
		template<typename T_, template<typename> List_>
		Json& operator=(const List_<T_>& _list); ///< Assign any type that can be traversed as a vector
		template<typename Val_, template<typename,typename> Map_, typename Key_ = std::string> ///< Assign any type that can be traversed as a map
		Json& operator=(const Map_<Key_,Val_>&);

		// ----- Conversion to base types -----
		/// Return the value of this json as a boolean element.
		/// This will produce different results depending on the actual type of data stored in the json.
		/// A boolean type (true or false), will be retrieved as such.
		/// A number will return \c false for 0 and \c true otherwise.

		operator bool	() const;
		operator int	() const;
		operator float	() const;

		// ----- Vector like access -----
		const Json&		operator[]	(size_t) const;
			  Json&		operator[]	(size_t);

		// ----- Map like access -----
		const Json&		operator[]	(const std::string&) const;
			  Json&		operator[]	(const std::string&);
		bool			contains	(const std::string&) const;

	private:
		/// Possible types of data
		enum class DataType {
			null,
			boolean,
			number,
			text,
			array,
			object,
		} mType;

		/// Internal representation of data
		int							mInteger;
		float						mReal;
		std::string					mText;
		std::vector<Json*>			mArray;
		std::map<std::string,Json*>	mObject;
	};

}	// namespace cjson

#endif // _CJSON_JSON_H_