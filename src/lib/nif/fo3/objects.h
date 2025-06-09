/*
 * objects.h
 *
 *  Created on: Feb 24, 2020
 *      Author: User
 */

#ifndef LIB_NIF_FO3_OBJECTS_H_
#define LIB_NIF_FO3_OBJECTS_H_

#include "types.h"
#include "../../half/half.hpp"

namespace nif::fo3 {


	class NiObject {

	public:
		virtual ~NiObject() {}
		virtual void read(NiStream& stream) = 0;
		virtual void write(NiStream& stream) = 0;

		virtual const std::string& getBlockName() const = 0;
	};



	class NiUnknow : public NiObject {

	private:
		std::string blockName;
		std::vector<char> data;
		unsigned int size = 0;

	private:
		NiUnknow() {};
		NiUnknow(const std::string& blockName, const unsigned int size) : blockName(blockName), size(size) {
			data.resize(size);
		};

	public:
		virtual ~NiUnknow() {}

		NiUnknow(NiStream& stream, const std::string& blockName, const unsigned int size) : NiUnknow(blockName, size) {
			read(stream);
		};

		const std::string& getBlockName() const override {
			return blockName;
		}

		const std::vector<char>& getData() const {
			return data;
		}

		const unsigned int& getSize() const {
			return size;
		}

		virtual void read(NiStream& stream) override {
			stream.read(&data[0], size);
		}

		virtual void write(NiStream& stream) override {
			stream.write(&data[0], size);
		}

	};


	class NiExtraData : public NiObject {
	private:
		int nameRef = 0xFFFFFFFF;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiExtraData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiIntegerExtraData : public NiExtraData {
	private:
		unsigned int integerData = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiIntegerExtraData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiStringExtraData : public NiExtraData {
	private:
		int stringData = 0xFFFFFFFF;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiStringExtraData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class BSXFlags : public NiIntegerExtraData {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSXFlags"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};



	class NiObjectNet : public NiObject {

	public:
		int nameRef = 0xFFFFFFFF;
		unsigned int extraDataListCount = 0;
		std::vector<int>  extraDataList;
		int controllerRef = 0xFFFFFFFF;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiAvObject : public NiObjectNet {

	public:
		unsigned int flags = 0;
		Vector3 translation;
		Matrix3 rotation;
		float scale = 1.0f;
		unsigned int numProperties = 0;
		std::vector<int>  properties;
		int collisionRef = 0xFFFFFFFF;


	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};






	class NiNode : public NiAvObject {

	public:
		unsigned int numChildren = 0;
		std::vector<int>  children;
		unsigned int numEffects = 0;
		std::vector<int>  effects;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class BSFadeNode : public NiNode {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSFadeNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class BSMultiBoundNode : public NiNode {

		int multiBoundRef = 0xFFFFFFFF;
		unsigned int cullingMode = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSMultiBoundNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class NiBillboardNode : public NiNode {

		unsigned short billboardMode = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiBillboardNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class BSOrderedNode : public NiNode {
	private:
		Vector4 alphaSortBound;
		unsigned char staticBound = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSOrderedNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSValueNode : public NiNode {
	private:
		int value = 0;
		unsigned char valueNodeFlags = 0x0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSValueNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSRangeNode : public NiNode {
	private:
		unsigned char min = 0;
		unsigned char max = 0;
		unsigned char current = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSRangeNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSBlastNode : public BSRangeNode {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSBlastNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class BSDamageStage : public BSBlastNode {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSDamageStage"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class BSDebrisNode : public BSRangeNode {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSDebrisNode"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};






	class bhkNiCollisionObject : public NiObject {

	public:
		int targetRef = 0xFFFFFFFF;
		unsigned short flags = 1;
		int bodyRef = 0xFFFFFFFF;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkNiCollisionObject"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class bhkCollisionObject : public bhkNiCollisionObject {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkCollisionObject"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class bhkPCollisionObject : public bhkNiCollisionObject {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkPCollisionObject"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class bhkSPCollisionObject : public bhkPCollisionObject {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkSPCollisionObject"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};




	class bhkWorldObject : public NiObject {

	public:
		int shapeRef = 0xFFFFFFFF;
		HavokFilter filter;
		unsigned char bhkWorldObject_unknown1[4];
		BroadPhaseType broadPhaseType = BroadPhaseType::BROAD_PHASE_INVALID;
		unsigned char bhkWorldObject_unknown2[3];
		CInfoProperty cInfoProperty;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class bhkRigidBody : public bhkWorldObject {

	public:
		unsigned char collisionResponse = hkResponseType::RESPONSE_SIMPLE_CONTACT;
		unsigned char bhkRigidBody_unknown1 = 0;
		unsigned short processContactCallbackDelay = 0xFFFF;
		unsigned char bhkRigidBody_unknown2[4];
		HavokFilter filterCopy;
		unsigned char bhkRigidBody_unknown3[4];
		unsigned char collisionResponse2 = hkResponseType::RESPONSE_SIMPLE_CONTACT;
		unsigned char bhkRigidBody_unknown4 = 0;
		unsigned short processContactCallbackDelay2 = 0xFFFF;
		unsigned char bhkRigidBody_unknown5[4];
		Vector4 translation;
		Vector4 rotation;
		Vector4 linearVelocity;
		Vector4 angularVelocity;
		float inertiaTensor[12];
		Vector4 center;
		float mass = 0.0f;
		float linearDamping = 0.0f;
		float angularDamping = 0.0f;
		float friction = 0.0f;
		float restitution = 0.0f;
		float maxLinearVelocity = 0.0f;
		float maxAngularVelocity = 0.0f;
		float penetrationDepth = 0.0f;
		unsigned char motionSystem = hkMotionSystem::MS_DYNAMIC;
		unsigned char deactivatorType = hkDeactivatorType::DEACTIVATOR_NEVER;
		unsigned char solverDeactivation = hkSolverDeactivation::SOLVER_DEACTIVATION_OFF;
		unsigned char qualityType = hkQualityType::QUALITY_FIXED;
		unsigned char bhkRigidBody_unknown6[12];
		unsigned int numConstraints = 0;
		std::vector<int> constraints;
		unsigned int bodyFlags = 0;


		float timeFactor = 1.0f;
		float rollingFrictionMult = 1.0f;
		unsigned char enableDeactivation = 0;
		float gravityFactor = 1.0f;
		unsigned int bhkRigidBody_unknown7 = 0;

		unsigned short bhkRigidBody_unknown8 = 0;




	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkRigidBody"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class bhkRigidBodyT : public bhkRigidBody {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkRigidBodyT"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class bhkPhantom : public bhkWorldObject {};

	class bhkShapePhantom : public bhkPhantom {};

	class bhkSimpleShapePhantom : public bhkShapePhantom {
	private:
		unsigned char bhkSimpleShapePhantom_unknown1[8];
		Matrix4 transform;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkSimpleShapePhantom"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};






	class bhkShape : public NiObject {
	};




	class bhkMoppBvTreeShape : public bhkShape {

	public:
		int shapeRef = 0xFFFFFFFF;
		unsigned char bhkMoppBvTreeShape_unknown1[12];
		float shapeScale = 0.0f;
		unsigned int moppDataSize = 0;
		Vector3 origin;
		float scale = 0.0f;
		std::vector<unsigned char> moppData;

		unsigned char buildType = 2;


	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkMoppBvTreeShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};




	class bhkSphereRepShape : public bhkShape {
	public:
		unsigned int material = 0;
		float radius = 0.0f;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class bhkConvexShape : public bhkSphereRepShape {};


	class bhkBoxShape : public bhkConvexShape {

	public:
		unsigned char bhkBoxShape_unknown1[8];
		Vector3 dimensions;
		float bhkBoxShape_unknown2 = 0.0f;
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkBoxShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class bhkSphereShape : public bhkConvexShape {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkSphereShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class bhkCapsuleShape : public bhkConvexShape {
	public:
		unsigned char bhkCapsuleShape_unknown1[8];
		Vector3 point1;
		float radius1 = 0.0f;
		Vector3 point2;
		float radius2 = 0.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkCapsuleShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};




	class bhkTransformShape : public bhkConvexShape {
	public:
		int shapeRef = 0xFFFFFFFF;
		unsigned char bhkTransformShape_unknown1[8];
		Matrix4 transform;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkTransformShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class bhkConvexTransformShape : public bhkTransformShape {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkConvexTransformShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class bhkListShape : public bhkShape {
	public:
		unsigned int numSubShapeRefs;
		std::vector<int> subShapeRefs;
		unsigned int material = 0;
		CInfoProperty childShapeProperty;
		CInfoProperty childFilterProperty;
		unsigned int num_bhkListShape_unknown1 = 0;
		std::vector<unsigned int> bhkListShape_unknown1;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkListShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class bhkConvexListShape : public bhkShape {
	public:
		unsigned int numShapeRefs;
		std::vector<int> shapeRefs;
		unsigned int material = 0;
		float radius = 0.0f;
		unsigned char bhkConvexListShape_unknown1[4];
		unsigned char bhkConvexListShape_unknown2[4];
		CInfoProperty childShapeProp;
		unsigned char bhkConvexListShape_unknown3 = 0;
		unsigned char bhkConvexListShape_unknown4[4];

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkConvexListShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class bhkConvexVerticesShape : public bhkConvexShape {

	public:

		CInfoProperty verticesProperty;
		CInfoProperty normalsProperty;

		unsigned int numVerts = 0;
		std::vector<Vector4> vertices;
		unsigned int numNormals = 0;
		std::vector<Vector4> normals;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkConvexVerticesShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class bhkPackedNiTriStripsShape : public bhkShape {

	public:
		unsigned int userData = 0;
		unsigned int bhkPackedNiTriStripsShape_unknown1 = 0;
		float radius = 0.0f;
		unsigned int bhkPackedNiTriStripsShape_unknown2 = 0;
		Vector4 scale;
		float radius2 = 0.0f;
		Vector4 scale2;
		int dataRef = 0xFFFFFFFF;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkPackedNiTriStripsShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};





	class bhkPackedNiTriStripsData : public bhkShape {

	struct SubShape {
		HavokFilter filter;
		unsigned int numVertices = 0;
		unsigned int material = 0;
	};

	public:
		unsigned int numTriangles = 0;
		std::vector<TriangleData> triangleData;
		unsigned int numVertices = 0;
		unsigned char hkPackedNiTriStripsData_unknown1 = 0;
		std::vector<Vector3> vertices;
		unsigned short numSubShapes = 0;
		std::vector<SubShape> subShapes;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "hkPackedNiTriStripsData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};




	class bhkNiTriStripsShape : public bhkShape {
	public:

		unsigned int material = 0;
		float radius = 0.1f;
		unsigned int bhkNiTriStripsShape_unknown1[5];
		unsigned int growBy = 1;
		Vector4 scale = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		unsigned int numParts = 0;
		std::vector<int> partRefs;

		unsigned int numFilters = 0;
		std::vector<HavokFilter> filters;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "bhkNiTriStripsShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};





	// ------------------------------------------------------------ <property> -----------------------------------------------------------------------



	class NiProperty : public NiObjectNet {};


	class NiAlphaProperty : public NiProperty {

	public:
		unsigned short flags = 4844;
		unsigned char threshold = 128;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiAlphaProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiStencilProperty : public NiProperty {

	private:
		unsigned short flags = 0;
		unsigned int stenscilRef;
		unsigned int stenscilMask;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiStencilProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

	};

	class NiMaterialProperty : public NiProperty {

	public:
		Vector3 specularColor;
		Vector3 emissiveColor;
		float glossiness = 1.0f;
		float alpha = 1.0f;
		float emissiveMult = 1.0f;
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiMaterialProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSShaderTextureSet : public NiObject {

	public:
		unsigned int numTextures = 10;
		std::vector<NiString<unsigned int>> textures = std::vector<NiString<unsigned int>>(10);


	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSShaderTextureSet"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class NiSourceTexture : public NiObjectNet {
	private:
		unsigned char useExternal = 0;
		int fileName = 0xFFFFFFFF;
		int dataRef = 0xFFFFFFFF;
		unsigned int pixelLayout = 0;
		unsigned int mipMapFormat = 0;
		unsigned int alphaFormat = 0;
		unsigned char isStatic = 0;
		unsigned char directRender = 0;
		unsigned char persistentRenderData = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSourceTexture"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class NiTexturingProperty : public NiProperty {

		struct TextureTransform {
			Vector2 translation;
			Vector2 tiling;
			float wRotation = 0.0f;
			unsigned int transformType = 0;
			Vector2 offset;
		};

		class TextureDescription {
		public:
			int sourceRef = 0xFFFFFFFF;
			unsigned short flags = 0;
			bool hasTexTransform = false;
			TextureTransform transform;

		public:
			void read(NiStream& stream) {
				stream >> sourceRef;
				stream >> flags;
				stream >> hasTexTransform;

				if (hasTexTransform)
					stream >> transform;
			}

			void write(NiStream& stream) {
				stream << sourceRef;
				stream << flags;
				stream << hasTexTransform;

				if (hasTexTransform)
					stream << transform;
			}

		};

		class ShaderTexDesc {
		public:
			bool isUsed = false;
			TextureDescription data;
			unsigned int mapIndex = 0;

		public:
			void read(NiStream& stream) {
				stream >> isUsed;

				if (isUsed) {
					data.read(stream);
					stream >> mapIndex;
				}
			}

			void write(NiStream& stream) {
				stream << isUsed;

				if (isUsed) {
					data.write(stream);
					stream << mapIndex;
				}
			}
		};

	public:
		unsigned short flags = 0;
		unsigned int textureCount = 0;
		unsigned char hasBaseTex = 0;
		TextureDescription baseTex;
		unsigned char hasDarkTex = 0;
		TextureDescription darkTex;
		unsigned char hasDetailTex = 0;
		TextureDescription detailTex;
		unsigned char hasGlossTex = 0;
		TextureDescription glossTex;
		unsigned char hasGlowTex = 0;
		TextureDescription glowTex;
		unsigned char hasBumpTex = 0;
		TextureDescription bumpTex;
		float lumaScale = 1.0f;
		float lumaOffset = 0.0f;
		Vector4 bumpMatrix;
		unsigned char hasNormalTex = 0;
		TextureDescription normalTex;
		unsigned char hasParallaxTex = 0;
		TextureDescription parallaxTex;
		float parallaxFloat = 0.0f;
		unsigned char hasDecalTex0 = 0;
		TextureDescription decalTex0;
		unsigned char hasDecalTex1 = 0;
		TextureDescription decalTex1;
		unsigned char hasDecalTex2 = 0;
		TextureDescription decalTex2;
		unsigned char hasDecalTex3 = 0;
		TextureDescription decalTex3;
		unsigned int numShaderTex = 0;
		std::vector<ShaderTexDesc> shaderTex;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTexturingProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};








	// ------------------------------------------------------------ </property> -----------------------------------------------------------------------





	// ------------------------------------------------------------ <shader> -----------------------------------------------------------------------


	class NiShaderProperty : public NiProperty {};

	class BSShaderProperty : public NiShaderProperty {

	public:
		unsigned short flags = 1;
		ShaderType shaderType = ShaderType::SHADER_DEFAULT;
		unsigned int shaderFlags1 = 0x80400201;
		unsigned int shaderFlags2 = 0x00000021;
		float environmentMapScale = 1.0f;

		Vector2 uvOffset;
		Vector2 uvScale = Vector2(1.0f, 1.0f);

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class BSShaderLightingProperty : public BSShaderProperty {

	public:
		unsigned int textureClampMode = 3;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class BSShaderPPLightingProperty : public BSShaderLightingProperty {

	public:
		int textureSetRef = 0xFFFFFFFF;
		float refractionStrength = 0.0f;
		int refractionFirePeriod = 0;
		float parallaxMaxPasses = 4.0f;
		float parallaxScale = 1.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSShaderPPLightingProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class Lighting30ShaderProperty : public BSShaderPPLightingProperty {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "Lighting30ShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};




	class BSShaderNoLightingProperty : public BSShaderLightingProperty {

	public:
		NiString<unsigned int> baseTexture;
		float falloffStartAngle = 1.0f;
		float falloffStopAngle = 0.0f;
		float falloffStartOpacity = 1.0f;
		float falloffStopOpacity = 0.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSShaderNoLightingProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class TallGrassShaderProperty : public BSShaderProperty {

	public:
		NiString<unsigned int> fileName;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "TallGrassShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class WaterShaderProperty : public BSShaderProperty {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "WaterShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class SkyShaderProperty : public BSShaderLightingProperty {
	public:
		NiString<unsigned int> fileName;
		unsigned int skyObjectType = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "SkyShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class TileShaderProperty : public BSShaderLightingProperty {
	public:
		NiString<unsigned int> fileName;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "TileShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	// ------------------------------------------------------------ </shader> -----------------------------------------------------------------------






	// ------------------------------------------------------------ <geometry> -----------------------------------------------------------------------



	class NiGeometry : public NiAvObject {
	public:
		int skinRef = 0xFFFFFFFF;
	};

	class NiGeometry3 : public virtual NiGeometry {

	public:
		int dataRef = 0xFFFFFFFF;

		unsigned int numMaterials = 0;
		std::vector<int>  materialNameRefs;
		std::vector<int>  materialExtraData;

		int activeMaterial = 0;
		unsigned char materialNeedsUpdate = 0;


	public:

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class NiTriBasedGeom : public NiGeometry3 {};


	class NiTriShape : public NiTriBasedGeom {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTriShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

	};

	class BSSegmentedTriShape : public NiTriShape {

		struct SegmentData {
			unsigned char flags = 0;
			unsigned int index = 0;
			unsigned int numTrisInSegnent = 0;

		};

	public:

		unsigned int numSegments;
		std::vector<SegmentData> segments;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSSegmentedTriShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class NiTriStrips : public NiTriBasedGeom {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTriStrips"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};








	class NiGeometryData : public NiObject {

	public:
		int groupID = 0;
		unsigned short numVertices = 0;
		unsigned char keepFlags = 0;
		unsigned char compressFlags = 0;
		unsigned char hasVertices = 0;
		std::vector<Vector3> vertices;
		unsigned short bsVectorFlags = 0;
		unsigned char hasNormals = 0;
		std::vector<Vector3> normals;
		std::vector<Vector3> tangents;
		std::vector<Vector3> bitangents;
		Vector3 center;
		float radius = 0.0f;
		unsigned char hasVertexColors = 0;
		std::vector<Vector4> vertexColors;
		std::vector<std::vector<Vector2>> uvSets;
		unsigned short consistencyFlags = 0;
		int additionalDataRef = 0xFFFFFFFF;

		unsigned int materialCRC = 0;


	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

		virtual std::unique_ptr<std::vector<Triangle>> getTriangles() const {
			return nullptr;
		}

	};

	class NiTriBasedGeometryData : public NiGeometryData {

	public:
		unsigned short numTriangles = 0;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class NiTriShapeData : public NiTriBasedGeometryData {

		struct MatchGroup {
			unsigned short numVertices = 0;
			std::vector<unsigned short> vertexIndices;
		};

	public:
		unsigned int numTrianglePoints = 0;
		unsigned char hasTriangles = 0;
		std::vector<Triangle> triangles;

		unsigned short numMatchGroups = 0;
		std::vector<MatchGroup> matchGroups;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTriShapeData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

		virtual std::unique_ptr<std::vector<Triangle>> getTriangles() const override ;
	};

	class NiTriStripsData : public NiTriBasedGeometryData {

	public:
		unsigned short numStrips = 0;
		std::vector<unsigned short> stripLengths;
		unsigned char hasPoints = 0;
		std::vector<std::vector<unsigned short>> points;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTriStripsData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

		virtual std::unique_ptr<std::vector<Triangle>> getTriangles() const override;

	};



	// ------------------------------------------------------------ </geometry> -----------------------------------------------------------------------




	class NiGeometry4 : public virtual NiGeometry {

	public:
		Vector3 boundingSphereCenter;
		float boundingSphereRadius = 0.0f;

		int shaderPropertyRef = 0xFFFFFFFF;
		int alphaPropertyRef = 0xFFFFFFFF;

		VertexDesc vertexDesc;

	public:

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class BSTriShape : public NiGeometry4 {


	public:
		unsigned int dataSize = 0;
		unsigned short numVertices = 0;
		std::vector<VertexData> vertexData;

		unsigned int numTriangles = 0;
		std::vector<Triangle> triangles;

	public:

		BSTriShape() {
			vertexDesc.setFlag(VertexFlags::VF_VERTEX);
			vertexDesc.setFlag(VertexFlags::VF_UV);
			vertexDesc.setFlag(VertexFlags::VF_NORMAL);
			vertexDesc.setFlag(VertexFlags::VF_TANGENT);
			//vertexDesc.vertexDesc.SetFlag(VertexFlags::VF_SKINNED);
		}

		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSTriShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

	};



	class BSDynamicTriShape : public BSTriShape {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSDynamicTriShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class BSSubIndexTriShape : public BSTriShape {

	public:
		struct SubSegment {
			unsigned int startIndex = 0;
			unsigned int numPrimitives = 0;
			unsigned int arrayIndex = 0;
			unsigned int unused = 0;
		};

		struct Segment {
			unsigned int startIndex = 0;
			unsigned int numPrimitives = 0;
			unsigned int parentArrayIndex = 0xFFFFFFFF;
			unsigned int numSubSegments = 0;
			std::vector<SubSegment> subSegments;
		};

		struct PerSegmentData {
			unsigned int userIndex = 0;
			unsigned int boneID = 0xFFFFFFFF;
			unsigned int numCutOffsets = 0;
			std::vector<float> cutOffsets;
		};

		struct SegmentData {
			unsigned int numSegments = 0;
			unsigned int totalSegments = 0;
			std::vector<unsigned int> arrayIndices;
			std::vector<PerSegmentData> arrayPerSegmentData;
			NiString<unsigned short> ssfFile;
		};

	public:
		unsigned int numPrimitives = 0;
		unsigned int numSegments = 0;
		unsigned int totalSegments = 0;
		std::vector<Segment> segments;
		SegmentData segmentData;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSSubIndexTriShape"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;


	};



	class BSLightingShaderProperty : public BSShaderProperty {

	public:
			unsigned int shaderType = 0;

			int textureSetRef = 0xFFFFFFFF;
			Vector3 emissiveColor;
			float emissiveMultiple = 1.0f;
			int wetMaterialNameRef = 0xFFFFFFFF;
			unsigned int textureClampMode = 3;
			float alpha = 1.0f;
			float refractionStrength = 0.0f;
			float smoothness = 1.0f;
			Vector3 specularColor = Vector3(1.0f, 1.0f, 1.0f);
			float specularStrength = 1.0f;
			float subsurfaceRolloff = 0.0f;
			float rimlightPower = std::numeric_limits<float>::max();
			float backlightPower = 0.0f;
			float grayscaleToPaletteScale = 1.0f;
			float fresnelPower = 5.0f;
			float wetnessSpecScale = 1.0f;
			float wetnessSpecPower = 1.0f;
			float wetnessMinVar = 0.1f;
			float wetnessEnvmapScale = 1.0f;
			float wetnessFresnelPower = 1.0f;
			float wetnessMetalness = 0.0f;

			float environmentMapScale = 1.0f;
			unsigned short unkEnvmapShort = 0;
			Vector3 skinTintColor = Vector3(1.0f, 1.0f, 1.0f);
			unsigned int unknownSkinTintInt = 0;
			Vector3 hairTintColor = Vector3(1.0f, 1.0f, 1.0f);
			float maxPasses = 1.0f;
			float scale = 1.0f;
			float parallaxInnerLayerThickness = 0.0f;
			float parallaxRefractionScale = 1.0f;
			Vector2 parallaxInnerLayerTextureScale = Vector2(1.0f, 1.0f);
			float parallaxEnvmapStrength = 1.0f;
			Vector4 sparkleParameters;
			float eyeCubemapScale = 1.0f;
			Vector3 eyeLeftReflectionCenter;
			Vector3 eyeRightReflectionCenter;

		public:
			static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSLightingShaderProperty"; return blockName; }
			virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

			virtual void read(NiStream& stream) override;
			virtual void write(NiStream& stream) override;

			BSLightingShaderProperty() {
				//shaderFlags1 = 0x80400203;
				//shaderFlags2 = 0x00000081;
			};

		};


	class BSEffectShaderProperty : public BSShaderProperty {

	public:
		NiString<unsigned int> sourceTexture;
		unsigned char textureClampMode = 3;
		unsigned char lightingInfluence = 0;
		unsigned char envMapMinLOD = 0;
		unsigned char unknownByte = 0;
		float falloffStartAngle = 1.0f;
		float falloffStopAngle = 1.0f;
		float falloffStartOpacity = 0.0f;
		float falloffStopOpacity = 0.0f;
		Vector4 emissiveColor;
		float emissiveMultiple = 0.0f;
		float softFalloffDepth = 0.0f;
		NiString<unsigned int> greyscaleTexture;
		NiString<unsigned int> envMapTexture;
		NiString<unsigned int> normalTexture;
		NiString<unsigned int> envMaskTexture;
		float envMapScale = 1.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSEffectShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSWaterShaderProperty : public BSShaderProperty {
	private:
		unsigned int waterFlags = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSWaterShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class BSSkyShaderProperty : public BSShaderProperty {
	public:
		NiString<unsigned int> baseTexture;
		unsigned int skyFlags = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSSkyShaderProperty"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};







	class BSMasterParticleSystem : public NiNode {
	private:
		unsigned short maxEmitterObjects = 0;
		unsigned int numParticleSysRefs = 0;
		std::vector<int> particleSysRefs;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSMasterParticleSystem"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};







	class NiParticleSystem : public NiGeometry3, public NiGeometry4 {

	public:
		unsigned char worldSpace = 0;
		unsigned int numModifiers = 0;
		std::vector<int> modifiers;

		unsigned short farBegin = 0;
		unsigned short farEnd = 0;
		unsigned short nearBegin = 0;
		unsigned short nearEnd = 0;

	public:
		NiParticleSystem() {
			vertexDesc.setFlag(VertexFlags::VF_UV);
			vertexDesc.setFlag(VertexFlags::VF_FULLPREC);
		}

		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiParticleSystem"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSStripParticleSystem : public NiParticleSystem {
	public:
		BSStripParticleSystem() : NiParticleSystem() {}
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSStripParticleSystem"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};





	class NiPSysData : public NiObject {
	private:
		int groupID = 0;
		unsigned short numVertices = 0;
		unsigned char keepFlags = 0;
		unsigned char compressFlags = 0;
		unsigned char hasVertices = 0;
		std::vector<Vector3> vertices;
		unsigned short bsVectorFlags = 0;
		unsigned char hasNormals = 0;
		std::vector<Vector3> normals;
		std::vector<Vector3> tangents;
		std::vector<Vector3> bitangents;
		Vector3 center;
		float radius = 0.0f;
		unsigned char hasVertexColors = 0;
		std::vector<Vector4> vertexColors;
		std::vector<std::vector<Vector2>> uvSets;
		unsigned short consistencyFlags = 0;
		int additionalDataRef = 0xFFFFFFFF;

		unsigned int materialCRC = 0;

		bool hasRadii = false;
		unsigned short numActive = 0;
		bool hasSizes = false;
		bool hasRotations = false;
		bool hasRotationAngles = false;
		bool hasRotationAxes = false;
		bool hasTextureIndices = false;

		unsigned int numSubtexOffsets = 0;
		std::vector<Vector4> subtexOffsets;

		float aspectRatio;
		unsigned short aspectFlags;
		float speedToAspectAspect2;
		float speedToAspectSpeed1;
		float speedToAspectSpeed2;
		bool hasRotationSpeeds = false;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiPSysData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSStripPSysData : public NiPSysData {
	private:
		unsigned short maxPointCount = 0;
		unsigned int startCapSize = 0;
		unsigned int endCapSize = 0;
		unsigned char doZPrepass = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSStripPSysData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class NiFloatInterpController : public NiObject {

	public:
		int nextControllerRef = 0xFFFFFFFF;
		unsigned short flags = 0;
		float frequency = 1.0f;
		float phase = 0.0f;
		float startTime = 0.0f;
		float stopTime = 0.0f;
		int targetRef = 0xFFFFFFFF;
		int interpolatorRef = 0xFFFFFFFF;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

	};

	class NiAlphaController : public NiFloatInterpController {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiAlphaController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};





	class FloatController : public NiFloatInterpController {
	public:
		unsigned int typeOfControlledVariable = 0;
	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class ColorController : public NiFloatInterpController {
	public:
		unsigned int typeOfControlledColor = 0;
	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};






	class BSEffectShaderPropertyFloatController : public FloatController {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSEffectShaderPropertyFloatController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class BSEffectShaderPropertyColorController : public ColorController {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSEffectShaderPropertyColorController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};



	class NiMaterialColorController : public NiFloatInterpController {

	public:
		unsigned short targetColor = 0;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiMaterialColorController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSLightingShaderPropertyFloatController : public FloatController {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSLightingShaderPropertyFloatController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};

	class BSLightingShaderPropertyColorController : public ColorController {

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSLightingShaderPropertyColorController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class NiTextureTransformController : public NiFloatInterpController {

	public:
		enum TransformType : unsigned int {
			TT_TRANSLATE_U,
			TT_TRANSLATE_V,
			TT_ROTATE,
			TT_SCALE_U,
			TT_SCALE_V
		};

	public:
		unsigned char shaderMap = 0;
		unsigned int textureSlot = 0;
		TransformType operation = TT_TRANSLATE_U;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiTextureTransformController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class BSMaterialEmittanceMultController : public NiFloatInterpController {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSMaterialEmittanceMultController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};



	class BSRefractionStrengthController : public NiFloatInterpController {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSRefractionStrengthController"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};











	class NiDynamicEffect : public NiAvObject {
	public:
		unsigned char switchState = 0;
		unsigned int numAffectedNodes = 0;
		std::vector<int> affectedNodes;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiLight : public NiDynamicEffect {
	private:
		float dimmer = 0.0f;
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;

	public:
		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};


	class NiAmbientLight : public NiLight {
	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiAmbientLight"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }
	};


	class NiPointLight : public NiLight {
	private:
		float constantAttenuation = 0.0f;
		float linearAttenuation = 0.0f;
		float quadraticAttenuation = 0.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiPointLight"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};

	class NiSpotLight : public NiPointLight {
	private:
		float cutoffAngle = 0.0f;
		float unkFloat = 0.0f;
		float exponent = 0.0f;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSpotLight"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};




	class NiSequence : public NiObject {

	public:
		struct ControllerBlock {

			int interpolatorRef = 0xFFFFFFFF;
			int controllerRef = 0xFFFFFFFF;
			unsigned char priority;
			int nodeName = 0xFFFFFFFF;
			int propType = 0xFFFFFFFF;
			int controllerType = 0xFFFFFFFF;
			int controllerID = 0xFFFFFFFF;
			int interpolatorID = 0xFFFFFFFF;
		};

	public:
		int nameRef = 0xFFFFFFFF;
		unsigned int numControlledBlocks = 0;
		unsigned int arrayGrowBy = 0;
		std::vector<ControllerBlock> controlledBlocks;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSequence"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

	};

	class NiControllerSequence : public NiSequence {
	public:
		float weight = 1.0f;
		int textKeyRef = 0xFFFFFFFF;
		unsigned int cycleType = 0;
		float frequency = 0.0f;
		float startTime = 0.0f;
		float stopTime = 0.0f;
		int managerRef = 0xFFFFFFFF;
		int accumRootName = 0xFFFFFFFF;

		unsigned short numAnimNoteRefs = 0;
		std::vector<int> animNoteRefs;


	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiControllerSequence"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};










	class NiBoneContainer : public NiObject {
	public:
		unsigned int numBones = 0;
		std::vector<int> boneRefs;
	};

	class NiSkinInstance : public NiBoneContainer {
	public:
		int dataRef = 0xFFFFFFFF;
		int skinPartitionRef = 0xFFFFFFFF;
		int skeletonRoot = 0xFFFFFFFF;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSkinInstance"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class BSDismemberSkinInstance : public NiSkinInstance {
	public:
		struct PartitionInfo {
			unsigned short flags = 0;
			unsigned short partId;
		};

	public:
		unsigned int numPartitions = 0;
		std::vector<PartitionInfo> partitions;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSDismemberSkinInstance"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};




	class NiSkinData : public NiObject {
	public:

		struct VertexWeight {
			unsigned short index;
			float weight;
		};

		struct BoneData {
			SkinTransform boneTransform;
			Vector3 center;
			float radius = 0.0f;
			unsigned short numVertices = 0;
			std::vector<VertexWeight> vertexWeights;
		};

		SkinTransform skinTransform;
		unsigned int numBones = 0;
		unsigned char hasVertexWeights = 1;
		std::vector<BoneData> bones;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSkinData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class NiSkinPartition : public NiObject {
	public:

		struct BoneIndices {
			unsigned char i1 = 0;
			unsigned char i2 = 0;
			unsigned char i3 = 0;
			unsigned char i4 = 0;
		};

		struct VertexWeight {
			float w1 = 0.0f;
			float w2 = 0.0f;
			float w3 = 0.0f;
			float w4 = 0.0f;
		};

		struct PartitionBlock {
			unsigned short numVertices = 0;
			unsigned short numTriangles = 0;
			unsigned short numBones = 0;
			unsigned short numStrips = 0;
			unsigned short numWeightsPerVertex = 0;
			std::vector<unsigned short> bones;
			unsigned char hasVertexMap = 0;
			std::vector<unsigned short> vertexMap;
			unsigned char hasVertexWeights = 0;
			std::vector<VertexWeight> vertexWeights;
			std::vector<unsigned short> stripLengths;
			unsigned char hasFaces = 0;
			std::vector<std::vector<unsigned short>> strips;
			std::vector<Triangle> triangles;
			unsigned char hasBoneIndices = 0;
			std::vector<BoneIndices> boneIndices;
		};

		unsigned int numPartitions = 0;
		std::vector<PartitionBlock> partitions;


	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "NiSkinPartition"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};














	class BSSkinInstance : public NiBoneContainer {
	public:

		int skeletonRoot = 0xFFFFFFFF;
		int dataRef = 0xFFFFFFFF;

		unsigned int num_BSSkinInstance_Unknown = 0;
		std::vector<Vector3> BSSkinInstance_Unknown;

	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSSkin::Instance"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;
	};



	class BSSkinBoneData : public NiObject {
	public:
		unsigned int numBones = 0;

		struct BoneData {
			Vector3 center;
			float radius = 0.0f;
			SkinTransform boneTransform;
		};

		std::vector<BoneData> boneData;


	public:
		static const std::string& GET_BLOCK_NAME() { const static std::string blockName = "BSSkin::BoneData"; return blockName; }
		virtual const std::string& getBlockName() const override { return GET_BLOCK_NAME(); }

		virtual void read(NiStream& stream) override;
		virtual void write(NiStream& stream) override;

	};

















}

#endif /* LIB_NIF_FO3_OBJECTS_H_ */
