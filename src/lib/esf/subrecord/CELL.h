/*
 * CELL.h
 *
 *  Created on: Mar 30, 2020
 *      Author: User
 */

#ifndef LIB_ESF_SUBRECORD_CELL_H_
#define LIB_ESF_SUBRECORD_CELL_H_

#include "common.h"

namespace esf::sub::cell {

	class LTMP : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "LTMP"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class XCLR : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XCLR"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};


	class XCIM : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XCIM"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class XEZN : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XEZN"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};


	class XCWT : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XCWT"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class XCAS : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XCAS"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};

	class XCMO : public INTEGER {

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "XCMO"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }
	};


}



namespace esf::sub::cell::fo3 {

	class DATA : public SubRecord {

		const uint32_t DATA_SIZE = 1;

	public:
		uint8_t flag = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "DATA"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};


	class XCLL : public SubRecord {

		const uint32_t DATA_SIZE = 40;

	public:
		std::vector<char> data;
		/*
		uint8_t ambientColor[4];
		uint8_t directionalColor[4];
		uint8_t fogColor[4];
		float fogNear = 0;
		float fogFar = 0;
		uint32_t directionalRotationXY = 0;
		uint32_t directionalRotationY = 0;
		float directionalFade = 0;
		float fogClipDist = 0;
		float fogPower = 0;
		 */

	public:
		XCLL() {
			data.resize(DATA_SIZE);
			std::fill(data.begin(), data.end(), 0);
		}
		static const std::string& GET_NAME() { const static std::string blockName = "XCLL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};






}

namespace esf::sub::cell::fo4 {

	class DATA : public SubRecord {

		const uint32_t DATA_SIZE = 2;

	public:
		uint16_t flag = 0;

	public:
		static const std::string& GET_NAME() { const static std::string blockName = "DATA"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};



	class XCLL : public SubRecord {

		const uint32_t DATA_SIZE = 136; //92

	public:
		std::vector<char> data;
		/*
		uint8_t ambientColor[4];
		uint8_t directionalColor[4];
		uint8_t fogColor[4];
		float fogNear = 0;
		float fogFar = 0;
		uint32_t directionalRotationXY = 0;
		uint32_t directionalRotationY = 0;
		float directionalFade = 0;
		float fogClipDist = 0;
		float fogPower = 0;


		uint8_t ambientColorsDirectional[24];
		uint8_t ambientColorsSpecular[4];
		float ambientColorsScale = 0;

		uint8_t fogColorFar[4];

		float FogMax = 0;
		float LightFadeBegin = 0;
		float ightFadeEnd = 0;

		uint32_t Inherits = 0;

		float NearHeightMid = 0;
		float NearHeightRange = 0;
		uint8_t FogColorHighNear[4];
		uint8_t FogColorHighFar[4];
		float HighDensityScale = 0;
		float FogNearScale = 0;
		float FogFarScale = 0;
		float FogHighNearScale = 0;
		float FogHighFarScale = 0;
		float FarHeightMid = 0;
		float FarHeightRange = 0;
		 */

	public:
		XCLL() {
			data.resize(DATA_SIZE);
			std::fill(data.begin(), data.end(), 0);
		}
		static const std::string& GET_NAME() { const static std::string blockName = "XCLL"; return blockName; }
		virtual const std::string& getName() const override { return GET_NAME(); }

		virtual const uint32_t getDataSize() override;

		virtual void readData(std::iostream& stream, const std::string& name, const uint32_t& size) override;
		virtual void writeData(std::iostream& stream) override;

	};







}










#endif /* LIB_ESF_SUBRECORD_CELL_H_ */
