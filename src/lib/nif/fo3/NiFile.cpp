#include "NiFile.h"


namespace nif::fo3 {



	NiFile::NiFile() {}
	NiFile::~NiFile() {}

	NiFile::NiFile(const std::string& fileName) : NiFile() {
		load(fileName);
	}


	NiNode* NiFile::getRootNode() {

		for (size_t i = 0; i < blocks.size(); i++) {
			if (auto niNode = dynamic_cast<NiNode*>(blocks[i].get())) {
				return niNode;
			}
		}

		return nullptr;
	}


	void NiFile::load(const std::string& fileName) {

		sourceFileName = fileName;

		std::fstream fStream(fileName.c_str(), std::ios::in | std::ios::binary);

		if (fStream.is_open()) {

			unsigned int numBlocks = 0;
			unsigned short numBlockTypes = 0;
			std::vector<NiString<unsigned int>> blockTypes;
			std::vector<unsigned short> blockTypeIndices;
			std::vector<unsigned int> blockSizes;
			unsigned int numStrings = 0;
			unsigned int maxStringLength = 0;

			NiStream stream(&fStream);

			stream.getLine(version_str);
			stream >> version;
			stream >> endian;
			stream >> userVersion;
			stream >> numBlocks;
			stream >> userVersion2;
			exportInfoAuthor.read(stream);
			exportInfoProcessScript.read(stream);
			exportInfoExportScript.read(stream);


			stream >> numBlockTypes;
			blockTypes.resize(numBlockTypes);
			for (unsigned int i = 0; i < numBlockTypes; i++) {
				blockTypes[i].read(stream);
			}

			blockTypeIndices.resize(numBlocks);
			for (unsigned int i = 0; i < numBlocks; i++) {
				stream >> blockTypeIndices[i];
			}

			blockSizes.resize(numBlocks);
			for (unsigned int i = 0; i < numBlocks; i++) {
				stream >> blockSizes[i];
			}

			stream >> numStrings;
			stream >> maxStringLength;
			strings.resize(numStrings);
			for (unsigned int i = 0; i < numStrings; i++) {
				strings[i].read(stream);
			}

			stream >> numGroups;
			groups.resize(numGroups);
			for (unsigned int i = 0; i < numGroups; i++) {
				stream >> groups[i];
			}

			NiObjectFactory& factory = NiObjectFactory::getInstance();

			blocks.resize(numBlocks);
			for (unsigned int i = 0; i < numBlocks; i++) {

				std::string name = blockTypes[blockTypeIndices[i]].get();
				auto factory_template = factory.getTemplate(name);

				if (factory_template) {

					//if (name == "NiParticleSystem") {
					//	std::streampos pos = stream.tellp();
					//	printf("Reading: %d\n", (int)pos); //
					//}

					std::vector<char> buff;
					buff.resize(blockSizes[i]);
					stream.read(buff.data(), blockSizes[i]);
					std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
					ss.write(buff.data(), blockSizes[i]);

					NiStream _stream(&ss);

					blocks[i] = factory_template->create(_stream);
				}
				else {
					blocks[i] = std::make_unique<NiUnknow>(stream, name, blockSizes[i]);
					//printf("Warning! Unknown block: %s\n", name.c_str());
				}

			}

			fStream.close();
		}
		else {
			printf("Can not open file %s\n", fileName.c_str());
		}

	}

	void NiFile::save(std::string fileName) {

		std::fstream fStream(fileName.c_str(), std::ios::out | std::ios::binary);

		if (fStream.is_open()) {

			// "delete" marked for deletion blocks before saving
			if (nif::fo3::NiNode* rootNode = getRootNode()) {
				for (int& del : blocksToDelete) {
					blocks[del] = std::make_unique<nif::fo3::NiExtraData>();
					rootNode->extraDataListCount++;
					rootNode->extraDataList.push_back(del);
				}
				blocksToDelete.clear();
			}



			std::vector<NiString<unsigned int>> blockTypes;
			std::vector<unsigned short> blockTypeIndices;
			blockTypeIndices.resize(blocks.size());
			std::vector<unsigned int> blockSizes;
			blockSizes.resize(blocks.size());
			unsigned int numStrings = 0;
			unsigned int maxStringLength = 0;

			NiStream stream(&fStream);

			stream.writeLine(version_str.c_str(), version_str.size());

			stream << version;
			stream << endian;
			stream << userVersion;
			stream << (unsigned int)blocks.size();//stream << numBlocks;
			stream << userVersion2;
			exportInfoAuthor.write(stream);
			exportInfoProcessScript.write(stream);
			exportInfoExportScript.write(stream);

			maxFilePath.write(stream);

			for (unsigned int i = 0; i < blocks.size(); i++) {

				std::vector<NiString<unsigned int>>::iterator it = std::find_if(blockTypes.begin(), blockTypes.end(), [&](const NiString<unsigned int>& blockType) {
					return blockType.get() == blocks[i]->getBlockName();
				});

				if (it == blockTypes.end()) {
					blockTypes.push_back(NiString<unsigned int>(blocks[i]->getBlockName()));
					blockTypeIndices[i] = blockTypes.size() - 1;
				} else {
					blockTypeIndices[i] = std::distance(blockTypes.begin(), it);
				}

				blockSizes[i] = 0;
			}

			stream << (unsigned short)blockTypes.size();
			for (unsigned int i = 0; i < blockTypes.size(); i++) {
				blockTypes[i].write(stream);

			}

			for (unsigned int i = 0; i < blockTypeIndices.size(); i++) {
				stream << blockTypeIndices[i];
			}

			std::streampos blockSizesPos = stream.tellp(); // save block sizes position
			for (unsigned int i = 0; i < blockSizes.size(); i++) {
				stream << blockSizes[i];
			}


			numStrings = strings.size();
			maxStringLength = 0;
			for (auto &s : strings) {
				if (maxStringLength < s.length()) {
					maxStringLength = s.length();
				}
			}


			stream << numStrings;
			stream << maxStringLength;
			for (unsigned int i = 0; i < numStrings; i++) {
				strings[i].write(stream);
			}

			stream << numGroups;
			for (unsigned int i = 0; i < numGroups; i++) {
				stream << groups[i];
			}

			blockSizes.clear(); // reset block sizes
			blockSizes.resize(blocks.size());
			stream.resetBlockSize();

			for (unsigned int i = 0; i < blocks.size(); i++) {
				blocks[i]->write(stream);
				blockSizes[i] = stream.getBlockSize(); // get new block sizes
				stream.resetBlockSize();
			}


			unsigned int endFile = 1;
			stream << endFile;
			endFile = 0;
			stream << endFile;

			// update block sizes
			if (blockSizesPos != std::streampos()) {
				stream.seekg(blockSizesPos);
				for (unsigned int i = 0; i < blockSizes.size(); i++) {
					stream << blockSizes[i];
				}
			}

			fStream.close();
		}
		else {
			printf("Can not open file %s\n", fileName.c_str());
		}

	}



}
