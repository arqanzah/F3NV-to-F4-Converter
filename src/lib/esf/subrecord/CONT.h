/*
 * CONT.h
 *
 *  Created on: Mar 29, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_CONT_H_
#define LIB_ESF_SUBRECORD_CONT_H_


#include "common.h"

namespace esf::sub::cont {

	class COCT : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "COCT"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};



	class CNTO : public SubRecord {

		const uint32_t DATA_SIZE = 8;

	public:
		uint32_t item = 0;
		uint32_t count = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "CNTO"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};










}


#endif /* LIB_ESF_SUBRECORD_CONT_H_ */
