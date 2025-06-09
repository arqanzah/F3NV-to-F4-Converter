/*
 * REFR.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: User
 */

#include "REFR.h"

namespace esf::sub::refr {


	void XLOC::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(level);
		reader.read(key);
		reader.read(flags);
		reader.read(unknown);

	}

	void XLOC::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(level);
		writer.write(key);
		writer.write(flags);
		writer.write(unknown);

	}

	const uint32_t XLOC::getDataSize() {
		return DATA_SIZE;
	}

}

namespace esf::sub::refr::fo3 {

	void XTEL::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(door);
		reader.read(position);
		reader.read(rotation);
		reader.read(flags);

	}

	void XTEL::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(door);
		writer.write(position);
		writer.write(rotation);
		writer.write(flags);

	}

	const uint32_t XTEL::getDataSize() {
		return DATA_SIZE;
	}

}



namespace esf::sub::refr::fo4 {

	void XTEL::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(door);
		reader.read(position);
		reader.read(rotation);
		reader.read(flags);
		reader.read(transitionInterior);

	}

	void XTEL::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(door);
		writer.write(position);
		writer.write(rotation);
		writer.write(flags);
		writer.write(transitionInterior);

	}

	const uint32_t XTEL::getDataSize() {
		return DATA_SIZE;
	}



}
