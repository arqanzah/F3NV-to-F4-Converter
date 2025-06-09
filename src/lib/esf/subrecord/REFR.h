/*
 * REFR.h
 *
 *  Created on: Mar 30, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_REFR_H_
#define LIB_ESF_SUBRECORD_REFR_H_

#include "common.h"

namespace esf::sub::refr {


	class NAME : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "NAME"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class XLOC : public SubRecord {

		const uint32_t DATA_SIZE = 20;

	public:
		uint32_t level = 0;
		uint32_t key = 0;
		uint32_t flags = 0;
		uint64_t unknown = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XLOC"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};


}


namespace esf::sub::refr::fo3 {

	class XTEL : public SubRecord {

		const uint32_t DATA_SIZE = 32;

	public:
		uint32_t door = 0;
		Vector3 position;
		Vector3 rotation;
		uint32_t flags = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XTEL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

}

namespace esf::sub::refr::fo4 {

	class XTEL : public SubRecord {

		const uint32_t DATA_SIZE = 36;

	public:
		uint32_t door = 0;
		Vector3 position;
		Vector3 rotation;
		uint32_t flags = 0;
		uint32_t transitionInterior = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XTEL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};


}

#endif /* LIB_ESF_SUBRECORD_REFR_H_ */
