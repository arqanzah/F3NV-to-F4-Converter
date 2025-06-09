/*
 * SCOL.h
 *
 *  Created on: Mar 30, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_SCOL_H_
#define LIB_ESF_SUBRECORD_SCOL_H_

#include "common.h"

namespace esf::sub::scol {


	class ONAM : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "ONAM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

}

#endif /* LIB_ESF_SUBRECORD_SCOL_H_ */
