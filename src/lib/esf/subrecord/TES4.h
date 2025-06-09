/*
 * TES4.h
 *
 *  Created on: Mar 23, 2020
 *      Author: talgat
 */

#ifndef LIB_ESF_SUBRECORD_TES4_H_
#define LIB_ESF_SUBRECORD_TES4_H_

#include "common.h"

namespace esf::sub::tes4 {


	class HEDR : public SubRecord {

		const uint32_t DATA_SIZE = 12;

	public:
		float version = 1;
		uint32_t NumOfRecords = 0;
		uint32_t nextObjectID = 16777216;//2048;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "HEDR"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};


	class CNAM : public SubRecordUnknown {
	public:
		static const std::string& GET_NAME() { const static std::string blockName = "CNAM"; return blockName; }
	};



	class MAST : public STRING {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "MAST"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};



	class DATA : public SubRecord {

	public:
		std::vector<char> data;

	public:
		DATA() {
			data.resize(8);
			std::fill(data.begin(), data.end(), 0);
		}
		static const std::string& GET_NAME() { const static std::string blockName = "DATA"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

	class ONAM : public SubRecordUnknown {
	public:
		static const std::string& GET_NAME() { const static std::string blockName = "ONAM"; return blockName; }
	};

	class INTV : public SubRecordUnknown {
	public:
		static const std::string& GET_NAME() { const static std::string blockName = "INTV"; return blockName; }
	};



}

#endif /* LIB_ESF_BASE_SUBRECORD_TES4_H_ */
