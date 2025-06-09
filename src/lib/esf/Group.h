/*
 * Group.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_GROUP_GROUP_H_
#define LIB_ESF_GROUP_GROUP_H_


#include "Record.h"

namespace esf {

	enum GROUP_TYPE : uint32_t {

		CONT = 1414418243,
		DOOR = 1380929348,
		FURN = 1314018630,
		GRAS = 1396789831,
		LTEX = 1480938572,
		MISC = 1129531725,

		TXST = 1414748244,

		STAT = 1413567571,
		SCOL = 1280262995,
		MSTT = 1414812493,

		CELL = 1280066883,
		WRLD = 1145852503,

	};

	enum GroupLabel : uint32_t
    {
        TopGroup = 0,
        WorldChildren = 1,
        InteriorCellBlock = 2,
        InteriorCellSubBlock = 3,
        ExteriorCellBlock = 4,
        ExteriorCellSubBlock = 5,
        CellChildren = 6,
        TopicChildren = 7,
        CellPersistentChildren = 8,
        CellTemporatyChildren = 9,
        CellVisibleDistandChildren = 10
    };

	class Group : public Groupable {

		const uint32_t HEADER_SIZE = 24;
		const std::string GRUP_NAME = "GRUP";

		std::vector<std::shared_ptr<Groupable>> groupables;

	public:
		//std::string name;

		uint32_t groupType = 0;

		uint32_t lableType = 0;

		uint32_t versionInfo = 0;
		uint32_t unknown = 0;


	protected:
		Group() {}

	public:
		Group(ESFile* file, Group* parent) : Groupable(file, parent) {}
		virtual ~Group() {};

		Group* createGroup();
		Record* createRecord();

		Record* findRecord(const uint32_t formId);
		void getRecords(std::vector<Record*>& out);

		const std::vector<Groupable*> getGroupables();


		void remove(Groupable* groupable);

		const uint32_t getRecordCount() const;

		virtual void read(std::iostream& stream) override;
		virtual void write(std::iostream& stream) override;






	};



}

#endif /* LIB_ESF_BASE_GROUP_GROUP_H_ */
