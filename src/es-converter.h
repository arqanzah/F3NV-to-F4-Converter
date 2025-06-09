//============================================================================
// Name        : ESConverter-gcc.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <experimental/filesystem>
#include "lib/esf/ESFile.h"
#include "lib/esf/subrecord/include.h"

namespace esf {

	const std::string EDID_PREFIX = "xxx";
	const uint32_t FORM_ID_OFFSET = 16777216;



	void convert_cont(ESFile& fo4File, Group* group) {


		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {
			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;


				sub::cont::COCT* coct = nullptr;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" ||
							subRecord->getName() == "MODL" || subRecord->getName() == "DATA") {



							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						} else if (subRecord->getName() == "CNTO") {

							if (!coct) {
								std::unique_ptr<sub::cont::COCT> _cont = std::make_unique<sub::cont::COCT>();
								coct = _cont.get();
								newRecord->subrecords.push_back(std::move(_cont));
							}
							coct->value++;

							std::unique_ptr<sub::cont::CNTO> cnto(subRecord->createRecord<sub::cont::CNTO>());
							cnto->item = cnto->item + FORM_ID_OFFSET;
							newRecord->subrecords.push_back(std::move(cnto));

						}



					}

				}

			}

		}

	}


	void convert_door(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {
			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" ||
							subRecord->getName() == "MODL" || subRecord->getName() == "FNAM") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}

					}

				}

			}

		}

	}

	void convert_furn(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {
			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" ||
							subRecord->getName() == "MODL") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}

					}

				}

			}

		}

	}

	void convert_gras(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {
			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" ||
							subRecord->getName() == "MODL" || subRecord->getName() == "DATA") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}

					}

				}

			}

		}

	}

	void convert_txst(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "OBND" || subRecord->getName() == "DNAM" ||
							subRecord->getName() == "TX00" || subRecord->getName() == "TX01") { //|| subRecord->getName() == "TX05"

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						} else if (subRecord->getName() == "TX02") { //environment different in fo4

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = "TX05";
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "TX03" || subRecord->getName() == "TX04") { //insert before TX05

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;

							std::vector<std::unique_ptr<SubRecord>>::iterator it = std::find_if(newRecord->subrecords.begin(), newRecord->subrecords.end(), [&](const std::unique_ptr<SubRecord>& o) {
								return o->getName() == "TX05";
							});


							if (it != newRecord->subrecords.end()) {
								newRecord->subrecords.insert(it, std::move(newSubRecord));
							} else {
								newRecord->subrecords.push_back(std::move(newSubRecord));
							}

						}

					}

				}

			}

		}

	}

	void convert_ltex(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "SNAM") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						} else if (subRecord->getName() == "HNAM" ) {


							std::unique_ptr<sub::ltex::fo3::HNAM> hnamFo3(subRecord->createRecord<sub::ltex::fo3::HNAM>());
							std::unique_ptr<sub::ltex::fo4::HNAM> hnamFo4 = std::make_unique<sub::ltex::fo4::HNAM>();

							hnamFo4->friction = hnamFo3->friction;
							hnamFo4->restitution = hnamFo3->restitution;

							newRecord->subrecords.push_back(std::move(hnamFo4));

						} else if (subRecord->getName() == "TNAM" ) {

							std::unique_ptr<sub::ltex::TNAM> tnam(subRecord->createRecord<sub::ltex::TNAM>());
							tnam->value = tnam->value + FORM_ID_OFFSET;
							newRecord->subrecords.push_back(std::move(tnam));

						} else if (subRecord->getName() == "GNAM" ) {

							std::unique_ptr<sub::ltex::GNAM> gnam(subRecord->createRecord<sub::ltex::GNAM>());
							gnam->value = gnam->value + FORM_ID_OFFSET;
							newRecord->subrecords.push_back(std::move(gnam));

						}

					}

				}

			}

		}


	}

	void convert_misc(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				//newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" || subRecord->getName() == "MODL" ||
							subRecord->getName() == "ICON" || subRecord->getName() == "DATA") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}

					}

				}

			}

		}


	}





	void set_lod(Record* record, bool fullLod = false) {

		if (sub::stat::MODL* modl = record->getSubrecord<sub::stat::MODL>()) {

			std::string fileName = modl->value;

			std::size_t extenstion_pos = fileName.find(".nif");
			if (extenstion_pos != std::string::npos) {
				fileName.insert(extenstion_pos, "_lod");
			}

			if (!fileName.empty()) {

				sub::stat::fo4::MNAM* mnam = record->getSubrecord<sub::stat::fo4::MNAM>();
				if (!mnam) {

					std::unique_ptr<sub::stat::fo4::MNAM> temp(new sub::stat::fo4::MNAM());
					mnam = temp.get();
					record->subrecords.push_back(std::move(temp));

				}
				strcpy(mnam->lod0 , fileName.c_str());
				if (fullLod) {
					strcpy(mnam->lod1 , fileName.c_str());
				}


			}
		}

	}



	void convert_stat(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;


				if ((record->flags & (1 << 5)) != 0) { newRecord->flags |= (1 << 5); }
				if ((record->flags & (1 << 6)) != 0) { newRecord->flags |= (1 << 6); }
				if ((record->flags & (1 << 15)) != 0) { newRecord->flags |= (1 << 15); } //visible when distant
				if ((record->flags & (1 << 18)) != 0) { newRecord->flags |= (1 << 18); }
				if ((record->flags & (1 << 25)) != 0) { newRecord->flags |= (1 << 25); }
				if ((record->flags & (1 << 26)) != 0) { newRecord->flags |= (1 << 26); }
				if ((record->flags & (1 << 30)) != 0) { newRecord->flags |= (1 << 20); }


				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "OBND" || subRecord->getName() == "MODL") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						} //else if (subRecord->getName() == "MODL" ) {
						//	std::unique_ptr<sub::stat::MODL> modl(subRecord->createRecord<sub::stat::MODL>());
						//	newRecord->subrecords.push_back(std::move(modl));
						//}


					}

				}

				if (record->flags & (1 << 15)) {
					set_lod(newRecord);
				}


			}

		}


	}

	void convert_mstt(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

						if (subRecord->getName() == "FULL" || subRecord->getName() == "OBND" || subRecord->getName() == "MODL") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}

					}

				}

			}

		}


	}

	void convert_scol(ESFile& fo4File, Group* group) {

		Group* newGroup = fo4File.createGroup();
		newGroup->groupType = group->groupType;
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Record* record = dynamic_cast<Record*>(_record)) {

				Record* newRecord = newGroup->createRecord();

				newRecord->name = record->name;
				newRecord->flags = record->flags;
				newRecord->formId = record->formId + FORM_ID_OFFSET;
				newRecord->versionControlInfo = record->versionControlInfo;
				newRecord->formVersion = 131;
				newRecord->versionControlInfo2 = record->versionControlInfo2;

				for (auto& _subRecord : record->subrecords) {

					if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {


						if (subRecord->getName() == "DATA") {

							std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
							newSubRecord->name = subRecord->name;
							newSubRecord->data = subRecord->data;
							newRecord->subrecords.push_back(std::move(newSubRecord));

						} else if (subRecord->getName() == "EDID" ) {

							std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
							edid->value = EDID_PREFIX + edid->value;
							newRecord->subrecords.push_back(std::move(edid));

						}  else if (subRecord->getName() == "MODL" ) {

							std::unique_ptr<sub::MODL> modl(subRecord->createRecord<sub::MODL>());
							newRecord->subrecords.push_back(std::move(modl));

						} else if (subRecord->getName() == "ONAM" ) {

							std::unique_ptr<sub::scol::ONAM> onam(subRecord->createRecord<sub::scol::ONAM>());
							onam->value = onam->value + FORM_ID_OFFSET;
							newRecord->subrecords.push_back(std::move(onam));

						}

					}

				}

			}

		}

	}



	void convert_ref(Group* group, Record* record) {

		Record* newRecord = group->createRecord();

		newRecord->name = record->name;
		newRecord->flags = record->flags;
		newRecord->formId = record->formId + FORM_ID_OFFSET;
		newRecord->versionControlInfo = record->versionControlInfo;
		newRecord->formVersion = 131;
		newRecord->versionControlInfo2 = record->versionControlInfo2;

		for (auto& _subRecord : record->subrecords) {

			if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

				if (subRecord->getName() == "EDID" ) {

					std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
					edid->value = EDID_PREFIX + edid->value;
					newRecord->subrecords.push_back(std::move(edid));

				} else if (subRecord->getName() == "NAME" ) {

					std::unique_ptr<sub::refr::NAME> name(subRecord->createRecord<sub::refr::NAME>());
					name->value = name->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(name));

				} else if (subRecord->getName() == "XTEL" ) {

					std::unique_ptr<sub::refr::fo3::XTEL> xtelFo3(subRecord->createRecord<sub::refr::fo3::XTEL>());
					std::unique_ptr<sub::refr::fo4::XTEL> xtelFo4 = std::make_unique<sub::refr::fo4::XTEL>();
					xtelFo4->door = xtelFo3->door + FORM_ID_OFFSET;
					xtelFo4->position = xtelFo3->position;
					xtelFo4->rotation = xtelFo3->rotation;
					xtelFo4->flags = xtelFo3->flags;
					newRecord->subrecords.push_back(std::move(xtelFo4));

				}


				//-------------------------------------- other ---------------------------------------------------
				/*
				 //  !!!!!! this
				 else {
					std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
					newSubRecord->name = subRecord->name;
					newSubRecord->data = subRecord->data;
					newRecord->subrecords.push_back(std::move(newSubRecord));
				}
				 //  !!!!!! this
				*/

				 // !!!!!! or this
				 else if (subRecord->getName() == "XOWN" ) {

					std::unique_ptr<sub::fo3::XOWN> xownFo3(subRecord->createRecord<sub::fo3::XOWN>());
					std::unique_ptr<sub::fo4::XOWN> xownFo4 = std::make_unique<sub::fo4::XOWN>();
					xownFo4->owner = xownFo3->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xownFo4));

				} else if (subRecord->getName() == "XLOC" ) {

					std::unique_ptr<sub::refr::XLOC> xloc(subRecord->createRecord<sub::refr::XLOC>());
					xloc->key = xloc->key + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xloc));

				} else if (subRecord->getName() == "XRGD" || subRecord->getName() == "XRGB" ||
						subRecord->getName() == "XPRM" || subRecord->getName() == "XTRI" ||
						subRecord->getName() == "XMBP" || subRecord->getName() == "XMBO" ||
						subRecord->getName() == "XLCM" || subRecord->getName() == "XRNK" ||
						subRecord->getName() == "XCNT" || subRecord->getName() == "XRDS" ||
						subRecord->getName() == "XAPD" || subRecord->getName() == "XAPR" ||
						subRecord->getName() == "XESP" || subRecord->getName() == "XEMI" ||
						subRecord->getName() == "XMBR" || subRecord->getName() == "XACT" ||
						subRecord->getName() == "ONAM" || subRecord->getName() == "XNDP" ||
						subRecord->getName() == "XPOD" || subRecord->getName() == "XPTL" ||
						subRecord->getName() == "XOCP" || subRecord->getName() == "XLOD" ||
						subRecord->getName() == "XSCL" || subRecord->getName() == "DATA" ) {

					std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
					newSubRecord->name = subRecord->name;
					newSubRecord->data = subRecord->data;
					newRecord->subrecords.push_back(std::move(newSubRecord));
				}
				// !!!!!! or this

				//-------------------------------------- /other ---------------------------------------------------


			}

		}


		bool visibleWhenDistant = ((record->flags & (1 << 15)) != 0);
		if (visibleWhenDistant) {

			bool highPriorityLOD = ((record->flags & (1 << 16)) != 0);

			if (sub::refr::NAME* nm = newRecord->getSubrecord<sub::refr::NAME>()) {

				if (Record* rec = newRecord->getFile()->findRecord(nm->value)) {

					rec->flags |= (1 << 15);
					if (highPriorityLOD) {
						set_lod(rec, true);
					} else {
						set_lod(rec);
					}

				}

			}

		}


	}


	void convert_cell(Group* group, Record* record) {

		Record* newRecord = group->createRecord();

		newRecord->name = record->name;
		newRecord->flags = record->flags;
		newRecord->formId = record->formId + FORM_ID_OFFSET;
		newRecord->versionControlInfo = record->versionControlInfo;
		newRecord->formVersion = 131;
		newRecord->versionControlInfo2 = record->versionControlInfo2;

		for (auto& _subRecord : record->subrecords) {

			if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

				if (subRecord->getName() == "EDID" ) {

					std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
					edid->value = EDID_PREFIX + edid->value;
					newRecord->subrecords.push_back(std::move(edid));

				} else /*if (subRecord->getName() == "DATA" ) {

					std::unique_ptr<sub::cell::fo3::DATA> dataFo3(subRecord->createRecord<sub::cell::fo3::DATA>());
					std::unique_ptr<sub::cell::fo4::DATA> dataFo4 = std::make_unique<sub::cell::fo4::DATA>();

					dataFo4->flag = dataFo3->flag;

					newRecord->subrecords.push_back(std::move(dataFo4));

				} else if (subRecord->getName() == "XCLL" ) {

					std::unique_ptr<sub::cell::fo3::XCLL> xcllFo3(subRecord->createRecord<sub::cell::fo3::XCLL>());
					std::unique_ptr<sub::cell::fo4::XCLL> xcllFo4 = std::make_unique<sub::cell::fo4::XCLL>();

					std::copy(xcllFo3->data.begin(), xcllFo3->data.end(), xcllFo4->data.begin());

					newRecord->subrecords.push_back(std::move(xcllFo4));

				} else if (subRecord->getName() == "LTMP" ) {

					std::unique_ptr<sub::cell::LTMP> ltmp(subRecord->createRecord<sub::cell::LTMP>());
					ltmp->value = ltmp->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(ltmp));

				} else if (subRecord->getName() == "XCLR" ) {

					std::unique_ptr<sub::cell::XCLR> xclr(subRecord->createRecord<sub::cell::XCLR>());
					xclr->value = xclr->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xclr));

				} else if (subRecord->getName() == "XCIM" ) {

					std::unique_ptr<sub::cell::XCIM> xcim(subRecord->createRecord<sub::cell::XCIM>());
					xcim->value = xcim->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xcim));

				} else if (subRecord->getName() == "XEZN" ) {

					std::unique_ptr<sub::cell::XEZN> xezn(subRecord->createRecord<sub::cell::XEZN>());
					xezn->value = xezn->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xezn));

				} else if (subRecord->getName() == "XCWT" ) {

					std::unique_ptr<sub::cell::XCWT> xcwt(subRecord->createRecord<sub::cell::XCWT>());
					xcwt->value = xcwt->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xcwt));

				} else if (subRecord->getName() == "XOWN" ) {

					std::unique_ptr<sub::cell::fo3::XOWN> xownFo3(subRecord->createRecord<sub::cell::fo3::XOWN>());
					std::unique_ptr<sub::cell::fo4::XOWN> xownFo4 = std::make_unique<sub::cell::fo4::XOWN>();
					xownFo4->owner = xownFo3->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xownFo4));

				} else if (subRecord->getName() == "XCAS" ) {

					std::unique_ptr<sub::cell::XCAS> xcas(subRecord->createRecord<sub::cell::XCAS>());
					xcas->value = xcas->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xcas));

				} else if (subRecord->getName() == "XCMO" ) {

					std::unique_ptr<sub::cell::XCMO> xcmo(subRecord->createRecord<sub::cell::XCMO>());
					xcmo->value = xcmo->value + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(xcmo));

				} else if (subRecord->getName() == "XCLC" || subRecord->getName() == "XCLW" || subRecord->getName() == "XRNK") */{

					std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
					newSubRecord->name = subRecord->name;
					newSubRecord->data = subRecord->data;
					newRecord->subrecords.push_back(std::move(newSubRecord));

				}

			}

		}

	}


	void convert_wrld(Group* group, Record* record) {

		Record* newRecord = group->createRecord();

		newRecord->name = record->name;
		newRecord->flags = record->flags;
		newRecord->formId = record->formId + FORM_ID_OFFSET;
		newRecord->versionControlInfo = record->versionControlInfo;
		newRecord->formVersion = 131;
		newRecord->versionControlInfo2 = record->versionControlInfo2;

		for (auto& _subRecord : record->subrecords) {

			if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

				if (subRecord->getName() == "EDID" ) {

					std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
					edid->value = EDID_PREFIX + edid->value;
					newRecord->subrecords.push_back(std::move(edid));

				} else if (subRecord->getName() == "DATA" ) {

					std::unique_ptr<sub::wrld::DATA> dataFo3(subRecord->createRecord<sub::wrld::DATA>());
					std::unique_ptr<sub::wrld::DATA> dataFo4 = std::make_unique<sub::wrld::DATA>();

					if ((dataFo3->value & (1 << 0)) != 0) {
						dataFo4->value |= (1 << 0);
					}
					if ((dataFo3->value & (1 << 1)) != 0) {
						dataFo4->value |= (1 << 1);
					}

					if ((dataFo3->value & (1 << 4)) != 0) {
						dataFo4->value |= (1 << 3);
					}


					newRecord->subrecords.push_back(std::move(dataFo4));

				} else {
					std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
					newSubRecord->name = subRecord->name;
					newSubRecord->data = subRecord->data;
					newRecord->subrecords.push_back(std::move(newSubRecord));
				}

			}

		}

	}

	void convert_land(Group* group, Record* record) {

		Record* newRecord = group->createRecord();

		newRecord->name = record->name;
		newRecord->flags = record->flags;
		newRecord->formId = record->formId + FORM_ID_OFFSET;
		newRecord->versionControlInfo = record->versionControlInfo;
		newRecord->formVersion = 131;
		newRecord->versionControlInfo2 = record->versionControlInfo2;

		for (auto& _subRecord : record->subrecords) {

			if (SubRecordUnknown* subRecord = dynamic_cast<SubRecordUnknown*>(_subRecord.get())) {

				if (subRecord->getName() == "EDID" ) {

					std::unique_ptr<sub::EDID> edid(subRecord->createRecord<sub::EDID>());
					edid->value = EDID_PREFIX + edid->value;
					newRecord->subrecords.push_back(std::move(edid));

				} else if (subRecord->getName() == "BTXT" ) {

					std::unique_ptr<sub::land::BTXT> btx(subRecord->createRecord<sub::land::BTXT>());
					btx->texture = btx->texture + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(btx));

				} else if (subRecord->getName() == "ATXT" ) {

					std::unique_ptr<sub::land::ATXT> atxt(subRecord->createRecord<sub::land::ATXT>());
					atxt->texture = atxt->texture + FORM_ID_OFFSET;
					newRecord->subrecords.push_back(std::move(atxt));

				} else {
					std::unique_ptr<SubRecordUnknown> newSubRecord = std::make_unique<SubRecordUnknown>();
					newSubRecord->name = subRecord->name;
					newSubRecord->data = subRecord->data;
					newRecord->subrecords.push_back(std::move(newSubRecord));
				}

			}

		}

	}



	void convert_cells(Group* group, Group* newGroup) {


		if (group->lableType == GroupLabel::CellTemporatyChildren ||
			group->lableType == GroupLabel::CellPersistentChildren ||
			group->lableType == GroupLabel::CellChildren ||
			group->lableType == GroupLabel::CellVisibleDistandChildren ||
			group->lableType == GroupLabel::WorldChildren) {
			newGroup->groupType = group->groupType + FORM_ID_OFFSET;
		} else {
			newGroup->groupType = group->groupType;
		}
		newGroup->lableType = group->lableType;
		newGroup->versionInfo = group->versionInfo;
		newGroup->unknown = group->unknown;

		for (auto _record : group->getGroupables()) {

			if (Group* subGroup = dynamic_cast<Group*>(_record)) {

				 Group* _newGroup = newGroup->createGroup();
				 convert_cells(subGroup, _newGroup);

			} else if (Record* record = dynamic_cast<Record*>(_record)) {

				if (record->name == "NAVM") {
					continue;
				}

				if (record->name == "WRLD") {
					convert_wrld(newGroup, record) ;
				}

				if (record->name == "CELL") {
					convert_cell(newGroup, record) ;
				}

				if (record->name == "REFR") {
					convert_ref(newGroup, record) ;
				}

				if (record->name == "LAND") {
					convert_land(newGroup, record) ;
				}



			}

		}

	}






	// ------------------------------------------- delete orphan references -------------------------------------------


	void delete_orphan_refs(Group* group, std::unordered_map<uint32_t, Record*>& records) {

		for (auto groupable : group->getGroupables()) {


			if (Record* record = dynamic_cast<Record*>(groupable)) {

				if (record->name == "REFR") {
					if (sub::refr::NAME* nameSubrecord = record->getSubrecord<sub::refr::NAME>()) {

						if (records.find(nameSubrecord->value) == records.end()) {
							group->remove(record);
						}

					}
				}


			} else if (Group* subGroup = dynamic_cast<Group*>(groupable)) {
				delete_orphan_refs(subGroup, records);
			}

		}

	}


	void clear(ESFile& file) {

		std::unordered_map<uint32_t, Record*> records;
		std::vector<Record*> _records;
		file.getRecords(_records);

		for (auto record : _records) {
			records.emplace(record->formId, record);
		}

		for (auto& group : file.getGroups()) {
			if (group->groupType == GROUP_TYPE::CELL || group->groupType == GROUP_TYPE::WRLD) {
				delete_orphan_refs(group, records);
			}
		}

	}

	// ------------------------------------------- /delete orphan references ------------------------------------------



	void calcLodCoordiate(const int& x, const int& y, const int& level, int& resultX, int& resultY) {

		const int dumper = 32768;

		resultX = ((x + dumper) - ((x + dumper) % level)) - dumper;
		resultY = ((y + dumper) - ((y + dumper) % level)) - dumper;
	}



	void rename_scol_files(ESFile& file, const std::string& outDataFolder, const std::string& pluginName, const std::string& pluginExtention) {


		if (!std::experimental::filesystem::exists(outDataFolder + "\\Meshes\\SCOL\\" + pluginName + pluginExtention)) {
			std::experimental::filesystem::create_directories(outDataFolder + "\\Meshes\\SCOL\\" + pluginName + pluginExtention);
		}

		Group* scolGroup = file.getGroup(GROUP_TYPE::SCOL);

		std::vector<Record*> records;
		scolGroup->getRecords(records);

		for (Record* scol : records) {

			if (sub::MODL* modl = scol->getSubrecord<sub::MODL>()) {

				const std::string old_file_name = outDataFolder + "\\MESHES\\" + modl->value;

				std::stringstream stream;
				stream << std::setfill('0') << std::setw(8) << std::right << std::hex << scol->formId - FORM_ID_OFFSET; //original record id instead of newRecord id because needs original form id without FORM_ID_OFFSET (01xxxxxx)
				std::string new_file_name = outDataFolder + "\\MESHES\\SCOL\\" + pluginName + pluginExtention + "\\CM" +  stream.str() + ".nif";
				std::transform(new_file_name.begin(), new_file_name.end(),new_file_name.begin(), ::toupper);


				if (std::experimental::filesystem::exists(old_file_name)) {
					if (std::experimental::filesystem::exists(new_file_name)) { std::experimental::filesystem::remove(new_file_name); }
					std::experimental::filesystem::copy(old_file_name, new_file_name); //, fs::copy_options::overwrite_existing - does not work
					modl->value = "SCOL\\" + pluginName + pluginExtention + "\\CM" +  stream.str() + ".nif";
					std::transform(modl->value.begin(), modl->value.end(),modl->value.begin(), ::toupper);
				}


			}

		}

	}




	void convert_lodsettings_files(const std::string& inDataFolder, const std::string& outDataFolder) {


		std::string in = inDataFolder + "\\lodsettings";
		std::string out = outDataFolder + "\\LODSettings";


		if (!std::experimental::filesystem::exists(out)) {
			std::experimental::filesystem::create_directories(out);
		}



		for (auto& p : std::experimental::filesystem::directory_iterator(in)) {

			if (std::experimental::filesystem::is_regular_file(p.status()) && p.path().extension() == ".dlodsettings") {


				uint16_t swCell = 0;
				uint16_t neCell = 0;
				uint32_t stride = 0;
				uint32_t lodLevelMin = 0;
				uint32_t lodLevelMax = 0;


				std::string _out(out);
				_out.append("\\");
				_out.append(EDID_PREFIX);
				_out.append(p.path().stem().u8string().c_str());
				_out.append(".LOD");


				try {

					std::fstream inStream(p.path().u8string().c_str(), std::fstream::in | std::fstream::binary);
					if (inStream.is_open()) {

						StreamReader reader(inStream);
						reader.read(lodLevelMin);
						reader.read(lodLevelMax);
						reader.read(stride);
						reader.read(swCell);
						reader.read(neCell);



						std::fstream outStream(_out.c_str(), std::fstream::out | std::fstream::binary);
						if (outStream.is_open()) {

							StreamWriter writer(outStream);
							writer.write(swCell);
							writer.write(neCell);
							writer.write(stride);
							writer.write(lodLevelMin);
							writer.write(lodLevelMax);

							outStream.close();
						}

						inStream.close();
					}

				}
				catch (...) {
					std::cout << "Failed to convert: " << p.path().u8string().c_str() << std::endl;
					std::ofstream file("onverter_errors.txt", std::ios_base::app);
					file << "Failed to convert: " << p.path().u8string().c_str() << std::endl;
					file.close();
				}

			}

		}

	}


	void convert(const std::string& PLUGIN_NAME, const std::string& PLUGIN_EXTENSION, const std::string& IN_DATA_FOLDER, const std::string& OUT_DATA_FOLDER) {


		std::string inFile = IN_DATA_FOLDER + "\\" + PLUGIN_NAME + ".esm";
		std::string outFile = OUT_DATA_FOLDER + "\\" + PLUGIN_NAME + PLUGIN_EXTENSION;

		std::cout << PLUGIN_NAME << ": converting plugin..." << std::endl;
		ESFile fo3File(inFile);


		ESFile fo4File;

		fo4File.header.name = "TES4";
		//fileF4.header.flags |= (1 << 0); //set master
		fo4File.header.formVersion = 131;

		fo4File.header.addSubRecord<sub::tes4::HEDR>();
		sub::tes4::MAST* mast = fo4File.header.addSubRecord<sub::tes4::MAST>();
		mast->value = "Fallout4.esm";
		sub::tes4::DATA* data = fo4File.header.addSubRecord<sub::tes4::DATA>();
		data->data.resize(8);

		std::cout << PLUGIN_NAME << ": converting records..." << std::endl;

		for (auto& group : fo3File.getGroups()) {

			if (group->groupType == GROUP_TYPE::CONT) {
				convert_cont(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::DOOR) {
				convert_door(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::FURN) {
				convert_furn(fo4File, group);
			}

			// --------------------------- important: DATA for GRAS is slightly different in fo4, take a look later ---------------------------------------
			if (group->groupType == GROUP_TYPE::GRAS) {
				convert_gras(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::TXST) {
				convert_txst(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::LTEX) {
				convert_ltex(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::MISC) {
				convert_misc(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::STAT) {
				convert_stat(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::MSTT) {
				convert_mstt(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::SCOL) {
				convert_scol(fo4File, group);
			}

			if (group->groupType == GROUP_TYPE::CELL || group->groupType == GROUP_TYPE::WRLD) {

				 Group* newGroup = fo4File.createGroup();
				 convert_cells(group, newGroup);

			}

		}

		std::cout << PLUGIN_NAME << ": renaming SCOLs..." << std::endl;

		rename_scol_files(fo4File, OUT_DATA_FOLDER, PLUGIN_NAME, PLUGIN_EXTENSION);

		std::cout << PLUGIN_NAME << ": removing orphan references..." << std::endl;

		clear(fo4File);

		std::cout << PLUGIN_NAME << ": saving..." << std::endl;

		fo4File.save(outFile);

		std::cout << PLUGIN_NAME << ": converting LOD settings files..." << std::endl;

		convert_lodsettings_files(IN_DATA_FOLDER, OUT_DATA_FOLDER);

		std::cout << PLUGIN_NAME << ": done converting plugin..." << std::endl;




	}

}




