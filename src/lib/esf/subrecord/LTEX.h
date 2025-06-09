/*
 * LTEX.h
 *
 *  Created on: Mar 29, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_LTEX_H_
#define LIB_ESF_SUBRECORD_LTEX_H_

#include "common.h"

namespace esf::sub::ltex {

	class TNAM : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "TNAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class GNAM : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "GNAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

}



namespace esf::sub::ltex::fo3 {

	class HNAM : public SubRecord {

		const uint32_t DATA_SIZE = 3;

	public:
		uint8_t materialType = 0;
		uint8_t friction = 0;
		uint8_t restitution = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "HNAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

}

namespace esf::sub::ltex::fo4 {

	class HNAM : public SubRecord {

		const uint32_t DATA_SIZE = 2;

	public:
		uint8_t friction = 0;
		uint8_t restitution = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "HNAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

}

#endif /* LIB_ESF_SUBRECORD_LTEX_H_ */
