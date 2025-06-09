/*
 * TES4.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: talgat
 */

#include "TES4.h"

namespace esf::sub::tes4 {


	void HEDR::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		reader.read(version);
		reader.read(NumOfRecords);
		reader.read(nextObjectID);

	}

	void HEDR::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(version);
		writer.write(NumOfRecords);
		writer.write(nextObjectID);

	}

	const uint32_t HEDR::getDataSize() {
		return DATA_SIZE;
	}




	void DATA::readData(std::iostream& stream, const std::string& name, const uint32_t& size) {

		StreamReader reader(stream);

		data.resize(size);

		reader.read(data.data(), size);
	}

	void DATA::writeData(std::iostream& stream) {

		StreamWriter writer(stream);

		writer.write(data.data(), data.size());

	}

	const uint32_t DATA::getDataSize() {
		return data.size();
	}



} /* namespace esf */
