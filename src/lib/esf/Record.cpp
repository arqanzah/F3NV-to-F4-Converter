/*
 * Record.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */


#include "Record.h"

namespace esf {



	void Record::read(std::iostream& stream) {

		StreamReader reader(stream);

		std::vector<char> data;
		uint32_t dataSize = 0;

		std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);


		reader.read(name, 4);

		reader.read(dataSize);

		reader.read(flags);

		reader.read(formId);

		reader.read(versionControlInfo);

		reader.read(formVersion);

		reader.read(versionControlInfo2);



		if (isCompressed()) {

			uint32_t UNCOMPRESSED_SIZE = 0;
			reader.read(UNCOMPRESSED_SIZE);

			data.resize( dataSize - 4 );
			reader.read(data.data(), dataSize - 4);

			std::vector<char> decompressedData;
			decompressedData.resize(UNCOMPRESSED_SIZE);

			uLong uncomp_size = UNCOMPRESSED_SIZE;
			uncompress((Bytef *)&decompressedData[0], &uncomp_size, (Bytef *)&data[0], data.size());
			assert(uncomp_size == UNCOMPRESSED_SIZE);

			ss.write(&decompressedData[0], decompressedData.size());

			dataSize = UNCOMPRESSED_SIZE;


		 } else {

			data.resize(dataSize);
			reader.read(data.data(), dataSize);

			ss.write(&data[0], dataSize);
		 }


		//std::unordered_map<std::string, std::unique_ptr<SubRecordUnknown>> unknownSubRecords;

		subrecords.clear();

		while (!ss.eof() && ss.tellg() < dataSize) {
			std::unique_ptr<SubRecordUnknown> sub = std::make_unique<SubRecordUnknown>();
			sub->read(ss);
			subrecords.push_back(std::move(sub));
			//unknownSubRecords[sub->getName()] = std::move(sub);
		}

		//readData(unknownSubRecords);

	};


	void Record::write(std::iostream& stream) {

		StreamWriter writer(stream);

		std::vector<char> data;
		uint32_t uncompressedDataSize = getDataSize();
		uint32_t dataSize = uncompressedDataSize;


		std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);

		for (auto& subRecord : subrecords) {
			subRecord->write(ss);
		}

		//writeData(ss);


		data.resize(dataSize);
		ss.read(&data[0], dataSize);

		if (isCompressed()) {

			uLong compSize = compressBound(data.size());


			std::vector<char> compressedData;
			compressedData.resize(compSize);

			compress((Bytef *)&compressedData[0], &compSize, (Bytef *)&data[0], data.size());
			compressedData.resize(compSize); //resize to actual compressed size returned by compress

			data.clear();
			data = compressedData;

			dataSize = compSize + 4; //actual compressed size + original uncompressed size (int) by getDataSize()

		}

		writer.write(name);

		writer.write(dataSize);

		//flags &= ~(1 << 18); //remove compressed

		writer.write(flags);

		writer.write(formId);

		writer.write(versionControlInfo);

		writer.write(formVersion);

		writer.write(versionControlInfo2);


		if (isCompressed()) {
			//unsigned int dtSize = getDataSize();
			writer.write(uncompressedDataSize);
		}

		writer.write(data.data(), data.size());

	};




	/*
		void RecordUnknown::read(std::iostream& stream) {

			StreamReader reader(stream);

			uint32_t dataSize = 0;

			reader.read(name, 4);

			reader.read(dataSize);

			dataSize += RESIDUAL_HEADER_SIZE;

			data.resize(dataSize);
			reader.read(data.data(), dataSize);

		};

		void RecordUnknown::write(std::iostream& stream) {

			StreamWriter writer(stream);

			uint32_t dataSize = data.size();

			writer.write(name);

			writer.write(dataSize - RESIDUAL_HEADER_SIZE);

			writer.write(data.data(), dataSize);

		};
	*/



}
