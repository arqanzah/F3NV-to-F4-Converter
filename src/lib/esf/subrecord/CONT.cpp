/*
 * CONT.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: User
 */




#include "CONT.h"

namespace esf::sub::cont {


	void CNTO::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(item);
		reader.read(count);

	}

	void CNTO::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(item);
		writer.write(count);

	}

	const uint32_t CNTO::getDataSize() {
		return DATA_SIZE;
	}

}
