/*
 * CELL.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: User
 */

#include "CELL.h"

namespace esf::sub::cell {}


namespace esf::sub::cell::fo3 {

	void DATA::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(flag);

	}

	void DATA::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(flag);

	}

	const uint32_t DATA::getDataSize() {
		return DATA_SIZE;
	}




	void XCLL::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(data.data(), size);

	}

	void XCLL::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(data.data(), DATA_SIZE);

	}

	const uint32_t XCLL::getDataSize() {
		return DATA_SIZE;
	}

}

namespace esf::sub::cell::fo4 {

	void DATA::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(flag);

	}

	void DATA::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(flag);

	}

	const uint32_t DATA::getDataSize() {
		return DATA_SIZE;
	}



	void XCLL::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(data.data(), size);

	}

	void XCLL::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(data.data(), DATA_SIZE);

	}

	const uint32_t XCLL::getDataSize() {
		return DATA_SIZE;
	}



}
