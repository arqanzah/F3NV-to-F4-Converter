/*
 * Groupable.h
 *
 *  Created on: Mar 23, 2020
 *      Author: User
 */

#ifndef LIB_ESF_GROUPABLE_H_
#define LIB_ESF_GROUPABLE_H_


namespace esf {

	class ESFile;
	class Group;

	class Groupable {

	protected:
		ESFile* file = nullptr;
		Group* parent = nullptr;


	protected:
		Groupable() {}

	public:

		Groupable(ESFile* file, Group* parent) : file(file), parent(parent) {}

		virtual void read(std::iostream& stream) = 0;
		virtual void write(std::iostream& stream) = 0;

		ESFile* getFile() const {
			return file;
		}

		Group* getParent() const {
			return parent;
		}

		virtual ~Groupable() {}
	};

}


#endif
