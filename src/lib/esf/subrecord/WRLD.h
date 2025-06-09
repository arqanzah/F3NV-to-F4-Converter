/*
 * WRLD.h
 *
 *  Created on: Apr 5, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_WRLD_H_
#define LIB_ESF_SUBRECORD_WRLD_H_

#include "common.h"

namespace esf::sub::wrld {

	class DATA : public BYTE {

		public:
			static const std::string& GET_NAME() { const static std::string blockName = "DATA"; return blockName; }
			virtual const std::string& getName() const override { return GET_NAME(); }
		};


}

#endif //#LIB_ESF_SUBRECORD_WRLD_H_
