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
#ifndef _CJSON_JSON_H_
#define _CJSON_JSON_H_

#include <string>
#include <vector>
#include <map>

namespace cjson {

	/// \class Json
	/// \brief Encapsulates all the functionality to operate with json objects.
	class Json {
	private:
		typedef std::map<std::string, Json*>	Dictionary;
		typedef std::vector<Json*>			Array;

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
		bool parse	(const char* _code);
		/// generate a string with the formated content of the json object
		std::string serialize() const;

		// ----- Useful methods -----
		void setNull	(); ///< Reset object to default construction state

		bool isNull		() const;
		bool isBool		() const;
		bool isNumber	() const;
		bool isString	() const;
		bool isArray	() const;
		bool isObject	() const;

		// ----- Construction from base types -----
		Json(bool);
		Json(int);
		Json(unsigned);
		Json(float);
		Json(const char*);
		Json(const std::string&);
		Json(std::string&&);
		// Array constructors
		template<class T_>
		Json(std::initializer_list<T_>); ///< Construct from an arbitrary initializer list
		template<class T_>
		Json(const std::vector<T_>&); ///< Construct from any type that can be traversed as a vector
		// Dictionary constructors
		template<template<class, class> class Map_, class T_>
		Json(const Map_<std::string,T_>&); ///< Construct from any type that can be traversed as a map

		// ----- Assignment from base types -----
		Json& operator=(bool);
		Json& operator=(int);
		Json& operator=(unsigned);
		Json& operator=(float);
		Json& operator=(const char*);
		Json& operator=(const std::string&);
		Json& operator=(std::string&&);
		// Array assignments
		template<class T_>
		Json& operator=(std::initializer_list<T_>); ///< Assign an arbitrary initializer list

		// ----- Equaliy operators -----
		bool operator==(const Json&) const;
		bool operator==(bool _b) const;
		bool operator==(int _i) const;
		bool operator==(unsigned) const;
		bool operator==(float) const;
		bool operator==(const char*) const;
		bool operator==(const std::string&) const;

		// ----- Conversion to base types -----
		/// Cast to boolean
		/// This will produce different results depending on the actual type of data stored in the json.
		/// A boolean type (true or false), will be retrieved as such.
		/// A number will return \c false for 0 and \c true otherwise.
		/// A null element will always return \c false.
		/// An array or object will return \c false if empty, \c true otherwise.
		/// \return the value of this json as a boolean element.
		explicit operator bool			() const;
				 operator int			() const;
				 operator float			() const;
				 operator std::string	() const;

		// ----- Vector like access -----
		const Json&		operator()	(size_t) const;
			  Json&		operator()	(size_t);
		template<typename T_>
		void			push_back	(const T_&);

		// ----- Map like access -----
		const Json&		operator[]	(const char*) const;
			  Json&		operator[]	(const char*);
		const Json&		operator[]	(const std::string&) const;
			  Json&		operator[]	(const std::string&);
		bool			contains	(const std::string&) const;

		Json::Dictionary::iterator	begin();
		Json::Dictionary::iterator	end();

		// ----- Common methods for array and object -----
		size_t			size	() const;

	private:
		void clear();

	private:
		/// Possible types of data
		enum class DataType {
			null,
			boolean,
			integer,
			real,
			text,
			array,
			object,
		} mType;

		/// Internal representation of data
		union Number {
			int i;
			float f;
			bool b;
		}	mNumber;
		std::string	mText;
		Array		mArray;
		Dictionary	mObject;

		friend class Parser;
		friend class Serializer;
	};

}	// namespace cjson

#include "json.inl"

#endif // _CJSON_JSON_H_