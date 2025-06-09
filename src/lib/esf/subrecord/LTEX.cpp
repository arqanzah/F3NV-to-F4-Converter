/*
 * LTEX.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: User
 */

#include "LTEX.h"

namespace esf::sub::ltex::fo3 {

	void HNAM::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(materialType);
		reader.read(friction);
		reader.read(restitution);

	}

	void HNAM::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(materialType);
		writer.write(friction);
		writer.write(restitution);

	}

	const uint32_t HNAM::getDataSize() {
		return DATA_SIZE;
	}

}

namespace esf::sub::ltex::fo4 {

	void HNAM::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(friction);
		reader.read(restitution);

	}

	void HNAM::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(friction);
		writer.write(restitution);

	}

	const uint32_t HNAM::getDataSize() {
		return DATA_SIZE;
	}

}
