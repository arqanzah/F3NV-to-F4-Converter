/*
 * ESFile.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */


#include "ESFile.h"


namespace esf {

	ESFile::ESFile(const std::string& fileName) {
		load(fileName);
	}


	Group* ESFile::createGroup() {

		std::shared_ptr<Group> group = std::make_unique<Group>(this, nullptr);
		Group* _group = group.get();
		groups.push_back(std::move(group));

		return _group;
	}


	Record* ESFile::findRecord(const uint32_t formId) {

		for (std::vector<std::shared_ptr<esf::Group>>::iterator it = groups.begin(); it != groups.end(); ++it) {
			if (Record* record = it->get()->findRecord(formId)) {
				return record;
			}
		}
		return nullptr;

	}

	void ESFile::getRecords(std::vector<Record*>& out) {
		for (std::vector<std::shared_ptr<esf::Group>>::iterator it = groups.begin(); it != groups.end(); ++it) {
			it->get()->getRecords(out);
		}
	};


	Group* ESFile::getGroup(GROUP_TYPE type) {
		std::vector<std::shared_ptr<Group>>::iterator it = std::find_if(groups.begin(), groups.end(), [&](const std::shared_ptr<Group>& o) {
			return o->groupType == type;
		});

		return (it != groups.end()) ? static_cast<Group*>(it->get()) : nullptr;

	}

	const std::vector<Group*> ESFile::getGroups() {
		std::vector<Group*> _groups;
		for (std::vector<std::shared_ptr<esf::Group>>::iterator it = groups.begin(); it != groups.end(); ++it) {
			_groups.push_back(it->get());
		}
		return _groups;
	}
















	void ESFile::load(const std::string& fileName) {


		std::fstream fstream(fileName, std::fstream::in | std::fstream::binary);

		if (fstream.is_open()) {


			fstream.ignore(std::numeric_limits<std::streamsize>::max());
			std::streamsize file_size = fstream.gcount();
			fstream.clear();
			fstream.seekg( 0, std::ios_base::beg );


			header.read(fstream);

			groups.clear();

			while (!fstream.eof() && fstream.tellg() < file_size) {
				std::shared_ptr<Group> group = std::make_shared<Group>(this, nullptr);
				group->read(fstream);
				groups.push_back(group);
			}


		}

	}

	void ESFile::save(const std::string& fileName) {



		esf::sub::tes4::HEDR* hedr = header.getSubrecord<esf::sub::tes4::HEDR>();

		if (hedr) {
			uint32_t totalRecords = groups.size();
			for (auto& group : groups ) {
				totalRecords += group->getRecordCount();
			}
			hedr->NumOfRecords = totalRecords;
		}


		//if (header.hedr.get()) {
		//	uint32_t totalRecords = groups.size();
		//	for (auto& group : groups ) {
		//		totalRecords += group->getRecordCount();
		//	}
		//	header.hedr.get()->NumOfRecords = totalRecords;
		//}


		std::fstream fstream(fileName, std::fstream::out | std::fstream::binary);

		if (fstream.is_open()) {

			header.write(fstream);

			for (auto& group : groups ) {
				group->write(fstream);
			}

		}

	}






	/*
	Group* ESFile::addGroup(Group* parent) {



		std::shared_ptr<Group> group = std::make_shared<Group>();
		group->groupType = 1129531725;
		group->lableType = 0;
		group->versionInfo = 0;
		group->unknown = 0;

		if (parent) {
			parent->groupables.push_back(group);
		} else {
			groups.push_back(group);
		}

		return group.get();

	};


	Record* ESFile::addRecord(const std::string& name, Group* group) {

		std::shared_ptr<Record> record = std::make_shared<Record>();

		esf::sub::tes4::HEDR* hedr = header.getSubrecord<esf::sub::tes4::HEDR>();

		record->formId = hedr->nextObjectID;
		hedr->nextObjectID++;

		Record* ret = record.get();
		group->groupables.push_back(record);

		return ret;
	}*/
























}
