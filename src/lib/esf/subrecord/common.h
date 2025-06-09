/*
 * common.h
 *
 *  Created on: Mar 28, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_COMMON_H_
#define LIB_ESF_SUBRECORD_COMMON_H_

#include "../SubRecord.h"

namespace esf::sub {


	class STRING : public SubRecord {

	public:
		std::string value;

	public:
		virtual const uint32_t getDataSize() override;
		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

	class BYTE : public SubRecord {
		const uint32_t DATA_SIZE = 1;
	public:
		uint8_t value = 0;

	public:
		virtual const uint32_t getDataSize() override;
		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

	class INTEGER : public SubRecord {
		const uint32_t DATA_SIZE = 4;
	public:
		uint32_t value = 0;

	public:
		virtual const uint32_t getDataSize() override;
		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};



	class EDID : public STRING {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "EDID"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class MODL : public STRING {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "MODL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

}

namespace esf::sub::fo3 {

	class XOWN : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XOWN"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};


}

namespace esf::sub::fo4 {

	class XOWN : public SubRecord {

		const uint32_t DATA_SIZE = 12;

	public:
		uint32_t owner = 0;
		uint32_t unknown = 0;
		uint32_t flags = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XOWN"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

}






#endif /* LIB_ESF_SUBRECORD_COMMON_H_ */
