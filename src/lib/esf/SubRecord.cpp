/*
 * SubRecord.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#include "SubRecord.h"

namespace esf {




	void SubRecord::read(std::iostream& stream) {


		StreamReader reader(stream);

		std::string name;
		unsigned short dataSize = 0;

		reader.read(name, 4);
		reader.read(dataSize);

		unsigned int subRecDataSize = 0;

		if (name == "XXXX") {
			reader.read(subRecDataSize);

			reader.read(name, 4);
			reader.read(dataSize);

		} else {
			subRecDataSize = (unsigned int)dataSize;
		}


		readData(stream, name, subRecDataSize);


	}

	void SubRecord::write(std::iostream& stream) {

		StreamWriter writer(stream);

		uint16_t size = 0;

		if (isXXXX()) {

			writer.write(std::string("XXXX"));
			writer.write((uint16_t)(4));
			writer.write(getDataSize());

		} else {
			size = (uint16_t)getDataSize();
		}

		writer.write(getName());
		writer.write(size);

		writeData(stream);

	}

	unsigned int SubRecord::getSize() {

		uint32_t xxxxSize = isXXXX() ? XXXX_TOTAL_SIZE : 0;

		uint32_t sz = NAME_SIZE + SIZE_SIZE + getDataSize() + xxxxSize;
		return sz;
	}

	bool SubRecord::isXXXX() {

		uint32_t sz = getDataSize();

		if (sz > std::numeric_limits<uint16_t>::max()) {
			return true;
		} else {
			return false;
		}

	}






	void SubRecordUnknown::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		this->name = name;

		data.resize(size);
		reader.read(data.data(), size);

	}

	void SubRecordUnknown::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(data.data(), data.size());

	}

	const unsigned int SubRecordUnknown::getDataSize() {
		return data.size();
	}






}
