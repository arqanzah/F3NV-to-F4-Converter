


#ifndef LIB_NIF_FO3_NIFFILE_H_
#define LIB_NIF_FO3_NIFFILE_H_

#include "NiObjectFactory.h"

namespace nif::fo3 {

	class NiFile {

		std::vector<int> blocksToDelete;

	public:
		NiFile();
		NiFile(const std::string& fileName);
		virtual ~NiFile();

		void load(const std::string& fileName);
		void save(std::string fileName);

		NiNode* getRootNode();

		//blocks marked for deletion, will be deleted on save
		void markForDeletion(int ref) {
			blocksToDelete.push_back(ref);
		}

		const int addString(const std::string& str) {
			strings.push_back(NiString<unsigned int>(str));
			return strings.size() - 1;
		}


	public:

		std::string sourceFileName;

		std::string version_str;
		int version = 0;
		NiEndian endian = NiEndian::ENDIAN_LITTLE;
		unsigned int userVersion = 0;
		unsigned int userVersion2 = 0;

		NiStringNull<unsigned char> exportInfoAuthor;
		NiStringNull<unsigned char> exportInfoProcessScript;
		NiStringNull<unsigned char> exportInfoExportScript;


		std::vector<NiString<unsigned int>> strings;
		unsigned int numGroups = 0;
		std::vector<unsigned int> groups;

		std::vector<std::unique_ptr<NiObject>> blocks;

		NiStringNull<unsigned char> maxFilePath; //<fo4>




	};


}


#endif /* LIB_NIF_FO3_NIFFILE_H_ */

