/*
 * NiObjectFactory.h
 *
 *  Created on: Feb 24, 2020
 *      Author: User
 */

#ifndef LIB_NIF_FO3_NIOBJECTFACTORY_H_
#define LIB_NIF_FO3_NIOBJECTFACTORY_H_

#include "objects.h"

namespace nif::fo3 {

	class NiObjectFactoryTemplate {

	public:
		virtual ~NiObjectFactoryTemplate() {}
		virtual std::unique_ptr<NiObject> create() = 0;
		virtual std::unique_ptr<NiObject> create(NiStream& stream) = 0;
	};


	template<class T>
	class NiObjectFactoryTemplateImp : public NiObjectFactoryTemplate {

	public:
		virtual ~NiObjectFactoryTemplateImp() {}
		virtual std::unique_ptr<NiObject> create() override {
			return std::move(std::make_unique<T>());
		};

		virtual std::unique_ptr<NiObject> create(NiStream& stream) override {
			auto _template = std::make_unique<T>();
			_template->read(stream);
			return std::move(_template);
		};
	};


	class NiObjectFactory {

		std::unordered_map<std::string, std::shared_ptr<NiObjectFactoryTemplate>> templates;

	public:
		virtual ~NiObjectFactory() {};

		static NiObjectFactory& getInstance() {
			static NiObjectFactory instance;
			return instance;
		}

		template<class T> void registerTemplate() {
				templates.emplace(T::GET_BLOCK_NAME(), std::make_shared<NiObjectFactoryTemplateImp<T>>());
		}

		std::shared_ptr<NiObjectFactoryTemplate> getTemplate(const std::string& name) {
			auto it = templates.find(name);
			if (it != templates.end()) {
				return it->second;
			}
			return nullptr;
		}

	protected:
		NiObjectFactory() {

			//registerTemplate<NiExtraData>();
			//registerTemplate<NiIntegerExtraData>();
			//registerTemplate<NiStringExtraData>();
			//registerTemplate<BSXFlags>();

			registerTemplate<NiNode>();
			registerTemplate<BSFadeNode>();
			registerTemplate<BSMultiBoundNode>();
			registerTemplate<NiBillboardNode>();
			registerTemplate<BSOrderedNode>();


			registerTemplate<BSValueNode>();
			registerTemplate<BSDamageStage>();
			registerTemplate<BSBlastNode>();
			registerTemplate<BSDebrisNode>();




			registerTemplate<bhkNiCollisionObject>();
			registerTemplate<bhkCollisionObject>();
			registerTemplate<bhkPCollisionObject>();
			registerTemplate<bhkSPCollisionObject>();




			registerTemplate<bhkRigidBody>();
			registerTemplate<bhkRigidBodyT>();
			registerTemplate<bhkSimpleShapePhantom>();


			registerTemplate<bhkBoxShape>();
			registerTemplate<bhkMoppBvTreeShape>();

			registerTemplate<bhkSphereShape>();
			registerTemplate<bhkCapsuleShape>();

			registerTemplate<bhkTransformShape>();
			registerTemplate<bhkConvexTransformShape>();
			registerTemplate<bhkListShape>();
			registerTemplate<bhkConvexListShape>();
			registerTemplate<bhkConvexVerticesShape>();

			registerTemplate<NiAlphaProperty>();

			registerTemplate<NiStencilProperty>();

			registerTemplate<NiMaterialProperty>();

			registerTemplate<NiTexturingProperty>();
			registerTemplate<NiSourceTexture>();

			registerTemplate<BSShaderTextureSet>();

			registerTemplate<BSShaderPPLightingProperty>();
			registerTemplate<Lighting30ShaderProperty>();
			registerTemplate<BSShaderNoLightingProperty>();
			registerTemplate<TallGrassShaderProperty>();
			registerTemplate<WaterShaderProperty>();
			registerTemplate<SkyShaderProperty>();

			registerTemplate<TileShaderProperty>();

			registerTemplate<BSWaterShaderProperty>();
			registerTemplate<BSSkyShaderProperty>();





			registerTemplate<NiTriShape>();
			registerTemplate<NiTriShapeData>();

			registerTemplate<BSSegmentedTriShape>();

			registerTemplate<NiTriStrips>();
			registerTemplate<NiTriStripsData>();

			registerTemplate<bhkPackedNiTriStripsShape>();
			registerTemplate<bhkPackedNiTriStripsData>();


			registerTemplate<BSMasterParticleSystem>();
			registerTemplate<NiParticleSystem>();
			registerTemplate<BSStripParticleSystem>();
			registerTemplate<NiPSysData>();
			registerTemplate<BSStripPSysData>();



			registerTemplate<NiAlphaController>();

			registerTemplate<BSEffectShaderPropertyFloatController>();
			registerTemplate<BSEffectShaderPropertyColorController>();

			registerTemplate<NiMaterialColorController>();

			registerTemplate<BSLightingShaderPropertyFloatController>();
			registerTemplate<BSLightingShaderPropertyColorController>();

			registerTemplate<NiTextureTransformController>();
			registerTemplate<BSMaterialEmittanceMultController>();
			registerTemplate<BSRefractionStrengthController>();





			registerTemplate<NiAmbientLight>();
			registerTemplate<NiPointLight>();
			registerTemplate<NiSpotLight>();



			registerTemplate<NiSequence>();
			registerTemplate<NiControllerSequence>();




			registerTemplate<NiSkinInstance>();
			registerTemplate<BSDismemberSkinInstance>();
			registerTemplate<NiSkinData>();
			registerTemplate<NiSkinPartition>();














		/*
		 	registerTemplate<NiNode>();
			registerTemplate<BSTriShape>();
			registerTemplate<BSMeshLODTriShape>();
			registerTemplate<BSLightingShaderProperty>();
			registerTemplate<BSEffectShaderProperty>();
			registerTemplate<BSSubIndexTriShape>();
			registerTemplate<NiExtraData>();
			registerTemplate<BSSkyShaderProperty>();
			registerTemplate<BSWaterShaderProperty>();
			registerTemplate<NiParticleSystem>();
			registerTemplate<BSPSysSimpleColorModifier>();
			registerTemplate<NiPSysRotationModifier>();
			registerTemplate<NiPSysData>();
		*/
		};

	};





}
#endif /* LIB_NIF_FO3_NIOBJECTFACTORY_H_ */
