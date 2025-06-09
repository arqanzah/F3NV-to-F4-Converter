/*
 * ESFile.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_ESFILE_H_
#define LIB_ESF_ESFILE_H_


#include "Group.h"
#include "subrecord/include.h"

namespace esf {

	class ESFile {

		std::vector<std::shared_ptr<Group>> groups;

	public:
		Record header = Record(this, nullptr);

	public:
		ESFile() {};
		virtual ~ESFile() {};

		ESFile(const std::string& fileName);

		Group* createGroup();

		Record* findRecord(const uint32_t formId);
		void getRecords(std::vector<Record*>& out);

		Group* getGroup(GROUP_TYPE type);
		const std::vector<Group*> getGroups();


		void load(const std::string& fileName);
		void save(const std::string& fileName);




		//Group* addGroup(Group* parent);
		//Record* addRecord(const std::string& name, Group* group);


	};


}

#endif /* LIB_ESF_BASE_ESFILE_H_ */
