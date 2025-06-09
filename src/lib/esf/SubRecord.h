/*
 * SubRecord.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_SUBRECORD_H_
#define LIB_ESF_SUBRECORD_SUBRECORD_H_

#include "types.h"

namespace esf {


	class SubRecord {

			const uint32_t XXXX_TOTAL_SIZE = 10;

			const uint32_t NAME_SIZE = 4;
			const uint32_t SIZE_SIZE = 2;

		protected:



		public:
			SubRecord() {};
			virtual ~SubRecord() {};

			virtual const std::string& getName() const = 0;
			virtual const unsigned int getDataSize() = 0;

			virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) = 0;
			virtual void writeData(std::iostream& stream) = 0;

			virtual void read(std::iostream& stream) final;
			virtual void write(std::iostream& stream) final;

			virtual uint32_t getSize() final;
			virtual bool isXXXX() final;

		};


		class SubRecordUnknown : public SubRecord  {

		public:
			std::string name;
			std::vector<char> data;

		protected:
			virtual const unsigned int getDataSize() override;

		public:
			virtual const std::string& getName() const {
				return name;
			}

			virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
			virtual void writeData(std::iostream& stream) override;

			template<typename T>
			T* createRecord() {
				if (T::GET_NAME() == name) {
					T* rec = new T();
					std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
					ss.write(data.data(), data.size());
					rec->readData(ss,name, data.size());
					return rec;
				}
				return nullptr;
			}

		};










}
#endif
