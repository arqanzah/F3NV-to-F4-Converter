/*
 * common.cpp
 *
 *  Created on: Mar 28, 2020
 *      Author: User
 */

#include "common.h"

namespace esf::sub {

	void STRING::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(value,size);
	}

	void STRING::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(value, true);
	}

	const uint32_t STRING::getDataSize() {
		return value.length() + 1; // 1 - null termination symbol
	}


	void BYTE::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(value);
	}

	void BYTE::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(value);
	}

	const uint32_t BYTE::getDataSize() {
		return DATA_SIZE;
	}



	void INTEGER::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(value);
	}

	void INTEGER::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(value);
	}

	const uint32_t INTEGER::getDataSize() {
		return DATA_SIZE;
	}



}


namespace esf::sub::fo3 {



}

namespace esf::sub::fo4 {

	void XOWN::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(owner);
		reader.read(unknown);
		reader.read(flags);

	}

	void XOWN::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(owner);
		writer.write(unknown);
		writer.write(flags);

	}

	const uint32_t XOWN::getDataSize() {
		return DATA_SIZE;
	}


}

