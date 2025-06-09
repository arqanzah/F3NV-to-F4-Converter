/*
 * STAT.h
 *
 *  Created on: Apr 6, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_STAT_H_
#define LIB_ESF_SUBRECORD_STAT_H_

#include "common.h"

namespace esf::sub::stat {

	class MODL : public STRING {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "MODL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

}

namespace esf::sub::stat::fo4 {

	class MNAM : public SubRecord {

		const uint32_t DATA_SIZE = 1040;

	public:
		char lod0[260] = {0};
		char lod1[260] = {0};
		char lod2[260] = {0};
		char lod3[260] = {0};

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "MNAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};



}



#endif /* LIB_ESF_SUBRECORD_STAT_H_ */
