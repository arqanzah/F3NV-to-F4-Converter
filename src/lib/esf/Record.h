/*
 * Record.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_RECORD_RECORD_H_
#define LIB_ESF_RECORD_RECORD_H_


#include "types.h"
#include "../zlib-1.2.11/zlib.h"
#include "Groupable.h"
#include "SubRecord.h"



namespace esf {

	class RecordInterface : public Groupable {

	public:
		const unsigned int HEADER_SIZE = 24;

	protected:
		RecordInterface() {}

	public:
		RecordInterface(ESFile* file, Group* parent) : Groupable(file, parent) {}
		virtual ~RecordInterface() {};

		virtual void read(std::iostream& stream) = 0;
		virtual void write(std::iostream& stream) = 0;

	};



	class Record : public RecordInterface {

	public:
		std::string name;
		uint32_t flags = 0;
		uint32_t formId = 0;
		uint32_t versionControlInfo = 0;
		uint16_t formVersion = 0;
		uint16_t versionControlInfo2 = 0;


		std::vector<std::unique_ptr<SubRecord>> subrecords;

	protected:
		Record() {}

	public:
		Record(ESFile* file, Group* parent) : RecordInterface(file, parent) {}
		virtual void read(std::iostream& stream) override final;
		virtual void write(std::iostream& stream) override final;

		inline bool isCompressed() const {
			  return (flags & 0x00040000) != 0;
		}


		//virtual void readData(std::unordered_map<std::string, std::unique_ptr<SubRecordUnknown>>& subs) = 0;
		//virtual void writeData(std::iostream& stream) = 0;

		//virtual const uint32_t getDataSize() = 0;


		virtual void readData(std::unordered_map<std::string, std::unique_ptr<SubRecordUnknown>>& subs) {};
		virtual void writeData(std::iostream& stream) {};

		virtual const uint32_t getDataSize() {

			uint32_t dataSize = 0;

			for (auto& subRecord : subrecords) {
				dataSize += subRecord->getSize();
			}

			return dataSize;
		}



		template<typename T>
		T* addSubRecord() {
			std::unique_ptr<T> sub = std::make_unique<T>();
			T* ret = sub.get();
			subrecords.push_back(std::move(sub));
			return ret;
		}


		template<typename T>
		T* getSubrecord() {

			for (auto& subrecord : subrecords) {
				if (T::GET_NAME() == subrecord->getName()) {

					if (SubRecordUnknown* unknown = dynamic_cast<SubRecordUnknown*>(subrecord.get())) {

						std::unique_ptr<T> sub = std::make_unique<T>();
						std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
						ss.write(unknown->data.data(), unknown->data.size());
						sub->readData(ss, unknown->name, unknown->data.size());

						subrecord = std::move(sub);

					}
					return  dynamic_cast<T*>(subrecord.get());
				}
			}
			return nullptr;
		}

	};



}








/*

class RecordUnknown : public Record {

	const unsigned int RESIDUAL_HEADER_SIZE = 16; //header size without name (int 4) and size (int 4)

	std::string name;
	std::vector<char> data;

public:
	virtual void read(std::iostream& stream) override;
	virtual void write(std::iostream& stream) override;
};





template<typename T>
class SubRecordProperty {
	std::unique_ptr<T> subRecord;

public:
	~SubRecordProperty() {}
	void write(std::iostream& stream) {
		if (subRecord) { subRecord->write(stream); }
	}
	const uint32_t getSize() {
		if (subRecord) { return subRecord->getSize(); }
		return 0;
	}
	void read(std::unordered_map<std::string, std::unique_ptr<SubRecordUnknown>>& subs) {
		auto got = subs.find(T::GET_NAME());
		if (got != subs.end()) {
			subRecord = std::unique_ptr<T>(got->second->template createRecord<T>());
			subs.erase(got);
		}
	}
	T* get() {
		return subRecord.get();
	}

};
*/

















#endif /* LIB_ESF_BASE_RECORD_RECORD_H_ */
