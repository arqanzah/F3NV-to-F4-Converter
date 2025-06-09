/*
 * types.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_BASE_TYPES_H_
#define LIB_ESF_BASE_TYPES_H_



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <string.h>


namespace esf {



	class StreamReader {

		std::iostream* stream = nullptr;

	private:
		StreamReader() {}

	public:
		StreamReader(std::iostream& stream) : stream(&stream) {}


		~StreamReader() {}

		void read(char* ptr, std::streamsize size) {
			stream->read(ptr, size);
		}


		template<typename T>
		void read(T& t) {

			static_assert(!std::is_same<std::string, T>::value, "can't be std::string");

			this->read((char*)&t, sizeof(T));
		}


		void read(std::string& t, std::streamsize size = 0) {

			std::unique_ptr<char> s(new char[size + 1]);
			this->read(s.get(), size);
			s.get()[size] = 0;
			t = s.get();

		}


	};


	class StreamWriter {

		std::iostream* stream = nullptr;

	private:
		StreamWriter() {}

	public:
		StreamWriter(std::iostream& stream) : stream(&stream) {}
		~StreamWriter() {}

		void write(const char* str, std::streamsize size) {
			stream->write(str, size);
		}

		template<typename T>
		void write(const T& t) {

			static_assert(!std::is_same<std::string, T>::value, "can't be std::string");

			this->write((const char*)&t, sizeof(T));
		}

		void write(const std::string& t, bool null = false) {


			this->write(t.c_str(), t.length());
			if (null) {
				unsigned char nullTermination = 0;
				this->write(nullTermination);
			}

		}


	};


	struct Vector3 {

		float x;
		float y;
		float z;

		Vector3() {
			x = y = z = 0.0f;
		}

		Vector3(float X, float Y, float Z) {
			x = X;
			y = Y;
			z = Z;
		}

		void zero() {
			x = y = z = 0.0f;
		}

	};


}


#endif /* LIB_ESF_BASE_TYPES_H_ */
