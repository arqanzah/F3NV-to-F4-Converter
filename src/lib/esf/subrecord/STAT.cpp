/*
 * STAT.cpp
 *
 *  Created on: Apr 6, 2020
 *      Author: User
 */

#include "STAT.h"

namespace esf::sub::stat {}

namespace esf::sub::stat::fo4 {

	void MNAM::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(&lod0[0], sizeof(lod0));
		reader.read(&lod1[0], sizeof(lod1));
		reader.read(&lod2[0], sizeof(lod2));
		reader.read(&lod3[0], sizeof(lod3));

	}

	void MNAM::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(&lod0[0], sizeof(lod0));
		writer.write(&lod1[0], sizeof(lod1));
		writer.write(&lod2[0], sizeof(lod2));
		writer.write(&lod3[0], sizeof(lod3));

	}

	const uint32_t MNAM::getDataSize() {
		return DATA_SIZE;
	}


}
