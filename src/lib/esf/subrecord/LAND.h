/*
 * LAND.h
 *
 *  Created on: Mar 31, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_LAND_H_
#define LIB_ESF_SUBRECORD_LAND_H_

#include "common.h"

namespace esf::sub::land {


	class BTXT : public SubRecord {

		const uint32_t DATA_SIZE = 8;

	public:
		uint32_t texture = 0;
		uint8_t quadrant = 0;
		uint8_t unused = 0;
		uint16_t layer = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "BTXT"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};

	class ATXT : public BTXT {

		public:
			static const std::string& GET_NAME() { const static std::string blockName = "ATXT"; return blockName; }
			virtual const std::string& getName() const override { return GET_NAME(); }

		};

}

#endif /* LIB_ESF_SUBRECORD_LAND_H_ */
