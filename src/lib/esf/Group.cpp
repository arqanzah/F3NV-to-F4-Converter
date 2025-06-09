/*
 * Group.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */


#include "Group.h"

namespace esf {


	Group* Group::createGroup() {

		std::shared_ptr<Group> group = std::make_unique<Group>(this->file, this);
		Group* _group = group.get();
		groupables.push_back(std::move(group));

		return _group;
	}

	Record* Group::createRecord() {
		std::shared_ptr<Record> record = std::make_unique<Record>(this->file, this);
		Record* _record = record.get();
		groupables.push_back(std::move(record));

		return _record;
	}



	Record* Group::findRecord(const uint32_t formId) {

		for (std::vector<std::shared_ptr<esf::Groupable>>::iterator it = groupables.begin(); it != groupables.end(); ++it) {

			if (esf::Group* subGroup = dynamic_cast<esf::Group*>(it->get())) {

				if (Record* record = subGroup->findRecord(formId)) {
					return record;
				}

			} else if (esf::Record* record = dynamic_cast<esf::Record*>(it->get())) {
				if (record->formId == formId) {
					return record;
				}
			}

		}

		return nullptr;
	}

	void Group::getRecords(std::vector<Record*>& out) {
		for (std::vector<std::shared_ptr<esf::Groupable>>::iterator it = groupables.begin(); it != groupables.end(); ++it) {

			if (esf::Group* subGroup = dynamic_cast<esf::Group*>(it->get())) {
				subGroup->getRecords(out);
			} else if (esf::Record* record = dynamic_cast<esf::Record*>(it->get())) {
				out.push_back(record);
			}

		}
	};



	const std::vector<Groupable*> Group::getGroupables() {
		std::vector<Groupable*> _groupables;
		for (std::vector<std::shared_ptr<esf::Groupable>>::iterator it = groupables.begin(); it != groupables.end(); ++it) {
			_groupables.push_back(it->get());
		}
		return _groupables;
	}


	void Group::remove(Groupable* groupable) {

		std::vector<std::shared_ptr<Groupable>>::iterator it = std::find_if(groupables.begin(), groupables.end(), [&](const std::shared_ptr<Groupable>& o) {
			return groupable == o.get();
		});
		if (it != groupables.end()) {
			groupables.erase(it);
			//std::cout << "Record " << " removed." << std::endl;
		}

	}







	const uint32_t Group::getRecordCount() const {
		unsigned int totalRecords = groupables.size();
		for (auto& groupable : groupables) {
			if (auto group = dynamic_cast<Group*>(groupable.get())) {
				totalRecords += group->getRecordCount();
			}
		}
		return totalRecords;
	}


	void Group::read(std::iostream& stream) {

		uint32_t size = 0;
		std::vector<char> data;
		uint32_t dataSize = 0;


		StreamReader reader(stream);

		stream.ignore(4); //reader.read(name, 4);

		reader.read(size);

		reader.read(groupType);

		reader.read(lableType);

		reader.read(versionInfo);

		reader.read(unknown);


		dataSize = size - HEADER_SIZE;
		data.resize(dataSize);

		reader.read(data.data(), dataSize);

		//if (groupType != "CELL" && groupType != "WRLD" && groupType != "QUST") {
			std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
			ss.write(data.data(), dataSize);

			groupables.clear();

			while (!ss.eof() && ss.tellg() < dataSize) {

				std::string _name(4, '\0');
				ss.read(&_name[0], 4);
				ss.seekg(-4, std::ios_base::cur);


				if (_name == GRUP_NAME) {//(_group == 0x50555247) { //"GRUP"
					std::shared_ptr<Group> group = std::make_shared<Group>(this->file, this);
					group->read(ss);
					groupables.push_back(std::move(group));

				} else {
					//std::shared_ptr<Record> record = RecordFactory::getInstance().get(_name);
					std::shared_ptr<RecordInterface> record = std::make_shared<Record>(this->file, this);
					record->read(ss);
					groupables.push_back(std::move(record));
				}


			}
		//}

	}



	void Group::write(std::iostream& stream) {

		std::stringstream ss(std::stringstream::binary | std::stringstream::in | std::stringstream::out);

		for (auto& groupable : groupables) {
			groupable->write(ss);
		}

		std::string data = ss.str();
		uint32_t dataSize = data.length();

		StreamWriter writer(stream);

		writer.write(GRUP_NAME);//writer.write(name);

		writer.write(HEADER_SIZE + dataSize);

		writer.write(groupType);

		writer.write(lableType);

		writer.write(versionInfo);

		writer.write(unknown);

		writer.write(data);

		//for (auto& groupable : groupables) {
		//	groupable->write(stream);
		//}

	}















}
