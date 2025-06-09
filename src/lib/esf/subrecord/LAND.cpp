/*
 * LAND.cpp
 *
 *  Created on: Mar 31, 2020
 *      Author: User
 */

#include "LAND.h"


namespace esf::sub::land {

	void BTXT::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(texture);
		reader.read(quadrant);
		reader.read(unused);
		reader.read(layer);

	}

	void BTXT::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(texture);
		writer.write(quadrant);
		writer.write(unused);
		writer.write(layer);

	}

	const uint32_t BTXT::getDataSize() {
		return DATA_SIZE;
	}

}

