/*
 * TES4.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_RECORD_TES4_H_
#define LIB_ESF_RECORD_TES4_H_

#include "../Record.h"
#include "../subrecord/TES4.h"

namespace esf::rec {
/*
	class TES4 : public Record {

	public:
		SubRecordProperty<sub::tes4::HEDR> hedr;
		SubRecordProperty<sub::tes4::CNAM> cnam;
		SubRecordProperty<sub::tes4::MAST> mast;
		SubRecordProperty<sub::tes4::DATA> data;
		SubRecordProperty<sub::tes4::ONAM> onam;
		SubRecordProperty<sub::tes4::INTV> intv;

	public:


		virtual const uint32_t getDataSize() override {

			uint32_t sz = 0;

			sz += hedr.getSize();
			sz += cnam.getSize();
			sz += mast.getSize();
			sz += data.getSize();
			sz += onam.getSize();
			sz += intv.getSize();

			return sz;
		}

		virtual void readData(std::unordered_map<std::string, std::unique_ptr<SubRecordUnknown>>& subs) override {

			hedr.read(subs);
			cnam.read(subs);
			mast.read(subs);
			data.read(subs);
			onam.read(subs);
			intv.read(subs);

		};
		virtual void writeData(std::iostream& stream) override {

			hedr.write(stream);
			cnam.write(stream);
			mast.write(stream);
			data.write(stream);
			onam.write(stream);
			intv.write(stream);

		};

	};
*/
}

#endif /* LIB_ESF_FO4_RECORD_TES4_H_ */
