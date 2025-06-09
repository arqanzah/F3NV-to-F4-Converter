/*
 * objects.cpp
 *
 *  Created on: Feb 24, 2020
 *      Author: User
 */

#include "objects.h"


namespace nif::fo3 {


	void NiExtraData::read(NiStream& stream) {
		stream >> nameRef;
	}

	void NiExtraData::write(NiStream& stream) {
		stream << nameRef;
	}

	void NiIntegerExtraData::read(NiStream& stream) {
		NiExtraData::read(stream);
		stream >> integerData;
	}

	void NiIntegerExtraData::write(NiStream& stream) {
		NiExtraData::write(stream);
		stream << integerData;
	}

	void NiStringExtraData::read(NiStream& stream) {
		NiExtraData::read(stream);
		stream >> stringData;
	}

	void NiStringExtraData::write(NiStream& stream) {
		NiExtraData::write(stream);
		stream << stringData;
	}


	void NiObjectNet::read(NiStream& stream) {

		stream >> nameRef;

		stream >> extraDataListCount;

		extraDataList.resize(extraDataListCount);
		for (unsigned int i = 0; i < extraDataListCount; i++) {
			stream >> extraDataList[i];
		}

		stream >> controllerRef;

	}

	void NiObjectNet::write(NiStream& stream) {

		stream << nameRef;

		stream << extraDataListCount;

		for (unsigned int i = 0; i < extraDataListCount; i++) {
			stream << extraDataList[i];
		}

		stream << controllerRef;

	}

	void NiAvObject::read(NiStream& stream) {

		NiObjectNet::read(stream);

		stream >> flags;

		stream >> translation;

		stream >> rotation;

		stream >> scale;

		stream >> numProperties;

		properties.resize(numProperties);
		for (unsigned int i = 0; i < numProperties; i++) {
			stream >> properties[i];
		}

		stream >> collisionRef;

	}

	void NiAvObject::write(NiStream& stream) {

		NiObjectNet::write(stream);

		stream << flags;

		stream << translation;

		stream << rotation;

		stream << scale;

		//stream << numProperties;

		//for (unsigned int i = 0; i < numProperties; i++) {
		//	stream << properties[i];
		//}

		stream << collisionRef;

	}

	void NiNode::read(NiStream& stream) {

		NiAvObject::read(stream);

		stream >> numChildren;

		children.resize(numChildren);
		for (unsigned int i = 0; i < numChildren; i++) {
			stream >> children[i];
		}

		stream >> numEffects;

		effects.resize(numEffects);
		for (unsigned int i = 0; i < numEffects; i++) {
			stream >> effects[i];
		}

	}

	void NiNode::write(NiStream& stream) {

		NiAvObject::write(stream);

		stream << numChildren;

		for (unsigned int i = 0; i < numChildren; i++) {
			stream << children[i];
		}

		//stream << numEffects;

		//for (unsigned int i = 0; i < numEffects; i++) {
		//	stream << effects[i];
		//}

	}



	void BSMultiBoundNode::read(NiStream& stream) {

		NiNode::read(stream);
		stream >> multiBoundRef;
	}

	void BSMultiBoundNode::write(NiStream& stream) {

		NiNode::write(stream);
		stream << multiBoundRef;
		stream << cullingMode;
	}

	void NiBillboardNode::read(NiStream& stream) {

		NiNode::read(stream);
		stream >> billboardMode;
	}

	void NiBillboardNode::write(NiStream& stream) {

		NiNode::write(stream);
		stream << billboardMode;
	}



	void BSOrderedNode::read(NiStream& stream) {

		NiNode::read(stream);
		stream >> alphaSortBound;
		stream >> staticBound;
	}

	void BSOrderedNode::write(NiStream& stream) {

		NiNode::write(stream);
		stream << alphaSortBound;
		stream << staticBound;
	}



	void BSValueNode::read(NiStream& stream) {

		NiNode::read(stream);
		stream >> value;
		stream >> valueNodeFlags;
	}

	void BSValueNode::write(NiStream& stream) {

		NiNode::write(stream);
		stream << value;
		stream << valueNodeFlags;
	}

	void BSRangeNode::read(NiStream& stream) {

		NiNode::read(stream);
		stream >> min;
		stream >> max;
		stream >> current;
	}

	void BSRangeNode::write(NiStream& stream) {

		NiNode::write(stream);
		stream << min;
		stream << max;
		stream << current;
	}




	void bhkNiCollisionObject::read(NiStream& stream) {
		stream >> targetRef;
		stream >> flags;
		stream >> bodyRef;
	}

	void bhkNiCollisionObject::write(NiStream& stream) {
		stream << targetRef;
		stream << flags;
		stream << bodyRef;
	}



	void bhkWorldObject::read(NiStream& stream) {
		stream >> shapeRef;
		stream >> filter;
		stream >> bhkWorldObject_unknown1;
		stream >> broadPhaseType;
		stream >> bhkWorldObject_unknown2;
		stream >> cInfoProperty;
	}

	void bhkWorldObject::write(NiStream& stream) {
		stream << shapeRef;
		stream << filter;
		stream << bhkWorldObject_unknown1;
		stream << broadPhaseType;
		stream << bhkWorldObject_unknown2;
		stream << cInfoProperty;
	}


	void bhkRigidBody::read(NiStream& stream) {
		bhkWorldObject::read(stream);

		stream >> collisionResponse;
		stream >> bhkRigidBody_unknown1;
		stream >> processContactCallbackDelay;
		stream >> bhkRigidBody_unknown2;
		stream >> filterCopy;
		stream >> bhkRigidBody_unknown3;
		stream >> collisionResponse2;
		stream >> bhkRigidBody_unknown4;
		stream >> processContactCallbackDelay2;
		stream >> bhkRigidBody_unknown5;
		stream >> translation;
		stream >> rotation;
		stream >> linearVelocity;
		stream >> angularVelocity;
		stream >> inertiaTensor;
		stream >> center;
		stream >> mass;
		stream >> linearDamping;
		stream >> angularDamping;
		stream >> friction;
		stream >> restitution;
		stream >> maxLinearVelocity;
		stream >> maxAngularVelocity;
		stream >> penetrationDepth;
		stream >> motionSystem;
		stream >> deactivatorType;
		stream >> solverDeactivation;
		stream >> qualityType;
		stream >> bhkRigidBody_unknown6;
		stream >> numConstraints;
		constraints.resize(numConstraints);
		for (unsigned int i = 0; i < numConstraints; i++) {
			stream >> constraints[i];
		}
		stream >> bodyFlags;
	}

	void bhkRigidBody::write(NiStream& stream) {
		bhkWorldObject::write(stream);

		stream << collisionResponse;
		stream << bhkRigidBody_unknown1;
		stream << processContactCallbackDelay;
		stream << bhkRigidBody_unknown2;
		stream << filterCopy;
		stream << bhkRigidBody_unknown3;
		stream << collisionResponse2;
		stream << bhkRigidBody_unknown4;
		stream << processContactCallbackDelay2;
		stream << bhkRigidBody_unknown5;
		stream << translation;
		stream << rotation;
		stream << linearVelocity;
		stream << angularVelocity;
		stream << inertiaTensor;
		stream << center;
		stream << mass;
		stream << linearDamping;
		stream << angularDamping;

		stream << timeFactor; // f4

		stream << friction;

		stream << rollingFrictionMult;

		stream << restitution;
		stream << maxLinearVelocity;
		stream << maxAngularVelocity;
		//stream << penetrationDepth;
		stream << motionSystem;

		stream << enableDeactivation;

		//stream << deactivatorType;
		stream << solverDeactivation;
		stream << qualityType;

		stream << penetrationDepth; //moved

		stream << gravityFactor;

		stream << bhkRigidBody_unknown6;

		stream << bhkRigidBody_unknown7;

		stream << numConstraints;
		for (unsigned int i = 0; i < numConstraints; i++) {
			stream << constraints[i];
		}
		//stream << bodyFlags; not in f4

		stream << bhkRigidBody_unknown8;

	}




	void bhkSimpleShapePhantom::read(NiStream& stream) {

		bhkPhantom::read(stream);

		stream >> bhkSimpleShapePhantom_unknown1;
		stream >> transform;
	}

	void bhkSimpleShapePhantom::write(NiStream& stream) {

		bhkPhantom::write(stream);

		stream << bhkSimpleShapePhantom_unknown1;
		stream << transform;
	}






	void bhkMoppBvTreeShape::read(NiStream& stream) {

		stream >> shapeRef;
		stream >> bhkMoppBvTreeShape_unknown1;
		stream >> shapeScale;
		stream >> moppDataSize;
		stream >> origin;
		stream >> scale;

		moppData.resize(moppDataSize);
		for (unsigned int i = 0; i < moppDataSize; i++) {
			stream >> moppData[i];
		}

	}

	void bhkMoppBvTreeShape::write(NiStream& stream) {

		stream << shapeRef;
		stream << bhkMoppBvTreeShape_unknown1;
		stream << shapeScale;
		stream << moppDataSize;
		stream << origin;
		stream << scale;

		stream << buildType; //fo4

		for (unsigned int i = 0; i < moppDataSize; i++) {
			stream << moppData[i];
		}

	}



	void bhkSphereRepShape::read(NiStream& stream) {

		stream >> material;
		stream >> radius;
	}

	void bhkSphereRepShape::write(NiStream& stream) {

		stream << material;
		stream << radius;
	}


	void bhkBoxShape::read(NiStream& stream) {

		bhkConvexShape::read(stream);

		stream >> bhkBoxShape_unknown1;
		stream >> dimensions;
		stream >> bhkBoxShape_unknown2;
	}

	void bhkBoxShape::write(NiStream& stream) {

		bhkConvexShape::write(stream);

		stream << bhkBoxShape_unknown1;
		stream << dimensions;
		stream << bhkBoxShape_unknown2;
	}


	void bhkCapsuleShape::read(NiStream& stream) {

		bhkConvexShape::read(stream);

		stream >> bhkCapsuleShape_unknown1;
		stream >> point1;
		stream >> radius1;
		stream >> point2;
		stream >> radius2;
	}

	void bhkCapsuleShape::write(NiStream& stream) {

		bhkConvexShape::write(stream);

		stream << bhkCapsuleShape_unknown1;
		stream << point1;
		stream << radius1;
		stream << point2;
		stream << radius2;
	}



	void bhkTransformShape::read(NiStream& stream) {

		stream >> shapeRef;

		bhkConvexShape::read(stream);

		stream >> bhkTransformShape_unknown1;

		stream >> transform;

	}

	void bhkTransformShape::write(NiStream& stream) {

		stream << shapeRef;

		bhkConvexShape::write(stream);

		stream << bhkTransformShape_unknown1;

		stream << transform;

	}


	void bhkListShape::read(NiStream& stream) {

		stream >> numSubShapeRefs;

		subShapeRefs.resize(numSubShapeRefs);
		for (unsigned int i = 0; i < numSubShapeRefs; i++) {
			stream >> subShapeRefs[i];
		}

		stream >> material;

		stream >> childShapeProperty;
		stream >> childFilterProperty;

		stream >> num_bhkListShape_unknown1;

		bhkListShape_unknown1.resize(num_bhkListShape_unknown1);
		for (unsigned int i = 0; i < num_bhkListShape_unknown1; i++) {
			stream >> bhkListShape_unknown1[i];
		}



	}

	void bhkListShape::write(NiStream& stream) {

		stream << numSubShapeRefs;

		for (unsigned int i = 0; i < numSubShapeRefs; i++) {
			stream << subShapeRefs[i];
		}

		stream << material;

		stream << childShapeProperty;
		stream << childFilterProperty;

		stream << num_bhkListShape_unknown1;

		for (unsigned int i = 0; i < num_bhkListShape_unknown1; i++) {
			stream << bhkListShape_unknown1[i];
		}

	}


	void bhkConvexListShape::read(NiStream& stream) {

		stream >> numShapeRefs;

		shapeRefs.resize(numShapeRefs);
		for (unsigned int i = 0; i < numShapeRefs; i++) {
			stream >> shapeRefs[i];
		}

		stream >> material;
		stream >> radius;
		stream >> bhkConvexListShape_unknown1;
		stream >> bhkConvexListShape_unknown2;
		stream >> childShapeProp;
		stream >> bhkConvexListShape_unknown3;
		stream >> bhkConvexListShape_unknown4;
	}

	void bhkConvexListShape::write(NiStream& stream) {

		stream << numShapeRefs;

		for (unsigned int i = 0; i < numShapeRefs; i++) {
			stream << shapeRefs[i];
		}

		stream << material;
		stream << radius;
		stream << bhkConvexListShape_unknown1;
		stream << bhkConvexListShape_unknown2;
		stream << childShapeProp;
		stream << bhkConvexListShape_unknown3;
		stream << bhkConvexListShape_unknown4;
	}

	void bhkConvexVerticesShape::read(NiStream& stream) {

		bhkConvexShape::read(stream);

		stream >> verticesProperty;
		stream >> normalsProperty;

		stream >> numVerts;
		vertices.resize(numVerts);
		for (unsigned int i = 0; i < numVerts; i++) {
			stream >> vertices[i];
		}

		stream >> numNormals;
		normals.resize(numNormals);
		for (unsigned int i = 0; i < numNormals; i++) {
			stream >> normals[i];
		}

	}

	void bhkConvexVerticesShape::write(NiStream& stream) {

		bhkConvexShape::write(stream);

		stream << verticesProperty;
		stream << normalsProperty;

		stream << numVerts;
		for (unsigned int i = 0; i < numVerts; i++) {
			stream << vertices[i];
		}


		stream << numNormals;
		for (unsigned int i = 0; i < numNormals; i++) {
			stream << normals[i];
		}

	}



	void NiGeometry3::read(NiStream& stream) {

		NiAvObject::read(stream);

		stream >> dataRef;
		stream >> skinRef;
		stream >> numMaterials;
		materialNameRefs.resize(numMaterials);
		materialExtraData.resize(numMaterials);
		for (unsigned int i = 0; i < numMaterials; i++) {
			stream >> materialNameRefs[i];
			stream >> materialExtraData[i];
		}
		stream >> activeMaterial;
		stream >> materialNeedsUpdate;
	}

	void NiGeometry3::write(NiStream& stream) {
		/*
		NiAvObject::write(stream);

		stream << dataRef;
		stream << skinRef;
		stream << numMaterials;

		for (unsigned int i = 0; i < numMaterials; i++) {
			stream << materialNameRefs[i];
			stream << materialExtraData[i];
		}
		stream << activeMaterial;
		stream << materialNeedsUpdate;

		stream << shaderPropertyRef;
		stream << alphaPropertyRef;
		 */
	}



	void BSSegmentedTriShape::read(NiStream& stream) {

		NiTriShape::read(stream);

		stream >> numSegments;

		segments.resize(numSegments);
		for (auto& segment : segments) {
			stream >> segment.flags;
			stream >> segment.index;
			stream >> segment.numTrisInSegnent;
		}


	}

	// #not-tested!!!
	void BSSegmentedTriShape::write(NiStream& stream) {
		/*
		NiTriShape::write(stream);

		stream << numSegments;

		for (auto& segment : segments) {
			stream << segment.flags;
			stream << segment.index;
			stream << segment.numTrisInSegnent;
		}

		 */
	}




	void NiAlphaProperty::read(NiStream& stream) {

		NiProperty::read(stream);

		stream >> flags;
		stream >> threshold;

	}

	void NiAlphaProperty::write(NiStream& stream) {

		NiProperty::write(stream);

		stream << flags;
		stream << threshold;

	}


	void NiStencilProperty::read(NiStream& stream) {

		NiProperty::read(stream);

		stream >> flags;
		stream >> stenscilRef;
		stream >> stenscilMask;
	}

	//#not-tested!!!
	void NiStencilProperty::write(NiStream& stream) {

		NiProperty::write(stream);

		stream << flags;
		stream << stenscilRef;
		stream << stenscilMask;

	}


	void NiMaterialProperty::read(NiStream& stream) {

		NiProperty::read(stream);

		stream >> specularColor;
		stream >> emissiveColor;
		stream >> glossiness;
		stream >> alpha;
		stream >> emissiveMult;


	}

	void NiMaterialProperty::write(NiStream& stream) {

		NiProperty::write(stream);

		stream << specularColor;
		stream << emissiveColor;
		stream << glossiness;
		stream << alpha;
		stream << emissiveMult;
	}


	void BSShaderTextureSet::read(NiStream& stream) {

		stream >> numTextures;
		textures.resize(numTextures);

		for (unsigned int i = 0; i < numTextures; i++) {
			//stream >> textures[i];
			textures[i].read(stream);
		}

	}

	void BSShaderTextureSet::write(NiStream& stream) {

		stream << numTextures;

		for (unsigned int i = 0; i < numTextures; i++) {
			//stream << textures[i];
			textures[i].write(stream);
		}

	}


	void NiSourceTexture::read(NiStream& stream) {

		NiObjectNet::read(stream);

		stream >> useExternal;
		stream >> fileName;
		stream >> dataRef;
		stream >> pixelLayout;
		stream >> mipMapFormat;
		stream >> alphaFormat;
		stream >> isStatic;
		stream >> directRender;
		stream >> persistentRenderData;

	}
	//#not-tested!!!
	void NiSourceTexture::write(NiStream& stream) {
		/*
		NiObjectNet::write(stream);

		stream << useExternal;
		stream << fileName;
		stream << dataRef;
		stream << pixelLayout;
		stream << mipMapFormat;
		stream << alphaFormat;
		stream << isStatic;
		stream << directRender;
		stream << persistentRenderData;
		*/
	}


	void NiTexturingProperty::read(NiStream& stream) {

		NiProperty::read(stream);

		stream >> flags;
		stream >> textureCount;

		if (textureCount > 0) {
			stream >> hasBaseTex;
			if (hasBaseTex) {
				baseTex.read(stream);
			}
		}

		if (textureCount > 1) {
			stream >> hasDarkTex;
			if (hasDarkTex) {
				darkTex.read(stream);
			}
		}

		if (textureCount > 2) {
			stream >> hasDetailTex;
			if (hasDetailTex) {
				detailTex.read(stream);
			}
		}

		if (textureCount > 3) {
			stream >> hasGlossTex;
			if (hasGlossTex) {
				glossTex.read(stream);
			}
		}

		if (textureCount > 4) {
			stream >> hasGlowTex;
			if (hasGlowTex) {
				glowTex.read(stream);
			}
		}

		if (textureCount > 5) {
			stream >> hasBumpTex;
			if (hasBumpTex) {
				bumpTex.read(stream);
				stream >> lumaScale;
				stream >> lumaOffset;
				stream >> bumpMatrix;
			}
		}

		if (textureCount > 6) {
			stream >> hasNormalTex;
			if (hasNormalTex) {
				normalTex.read(stream);
			}
		}

		if (textureCount > 7) {
			stream >> hasParallaxTex;
			if (hasParallaxTex) {
				parallaxTex.read(stream);
				stream >> parallaxFloat;
			}
		}

		if (textureCount > 8) {
			stream >> hasDecalTex0;
			if (hasDecalTex0) {
				decalTex0.read(stream);
			}
		}

		if (textureCount > 9) {
			stream >> hasDecalTex1;
			if (hasDecalTex1) {
				decalTex1.read(stream);
			}
		}

		if (textureCount > 10) {
			stream >> hasDecalTex2;
			if (hasDecalTex2) {
				decalTex2.read(stream);
			}
		}

		if (textureCount > 11) {
			stream >> hasDecalTex3;
			if (hasDecalTex3) {
				decalTex3.read(stream);
			}
		}

		stream >> numShaderTex;
		shaderTex.resize(numShaderTex);
		for (unsigned int i = 0; i < numShaderTex; i++) {
			shaderTex[i].read(stream);
		}

	}

	void NiTexturingProperty::write(NiStream& stream) {}








	void BSShaderProperty::read(NiStream& stream) {

		NiShaderProperty::read(stream);

		stream >> flags;
		stream >> shaderType;
		stream >> shaderFlags1;
		stream >> shaderFlags2;
		stream >> environmentMapScale;
	}

	void BSShaderProperty::write(NiStream& stream) {

		NiShaderProperty::write(stream);

		stream << shaderFlags1;
		stream << shaderFlags2;
		stream << uvOffset;
		stream << uvScale;

	}


	void BSShaderLightingProperty::read(NiStream& stream) {

		BSShaderProperty::read(stream);

		stream >> textureClampMode;
	}

	void BSShaderLightingProperty::write(NiStream& stream) {

		BSShaderProperty::write(stream);

		stream << textureClampMode;
	}



	void BSShaderPPLightingProperty::read(NiStream& stream) {

		BSShaderLightingProperty::read(stream);

		stream >> textureSetRef;
		stream >> refractionStrength;
		stream >> refractionFirePeriod;
		stream >> parallaxMaxPasses;
		stream >> parallaxScale;
	}

	void BSShaderPPLightingProperty::write(NiStream& stream) {

		BSShaderLightingProperty::write(stream);

		stream << textureSetRef;
		stream << refractionStrength;
		stream << refractionFirePeriod;
		stream << parallaxMaxPasses;
		stream << parallaxScale;
	}


	void BSShaderNoLightingProperty::read(NiStream& stream) {

		BSShaderLightingProperty::read(stream);

		baseTexture.read(stream);

		stream >> falloffStartAngle;
		stream >> falloffStopAngle;
		stream >> falloffStartOpacity;
		stream >> falloffStopOpacity;

	}

	void BSShaderNoLightingProperty::write(NiStream& stream) {

		BSShaderLightingProperty::write(stream);

		baseTexture.write(stream);

		stream << falloffStartAngle;
		stream << falloffStopAngle;
		stream << falloffStartOpacity;
		stream << falloffStopOpacity;

	}


	void TallGrassShaderProperty::read(NiStream& stream) {

		BSShaderProperty::read(stream);

		fileName.read(stream);
	}

	//#not-tested!!!
	void TallGrassShaderProperty::write(NiStream& stream) {

		BSShaderProperty::write(stream);

		fileName.write(stream);
	}


	void SkyShaderProperty::read(NiStream& stream) {

		BSShaderLightingProperty::read(stream);

		fileName.read(stream);
		stream >> skyObjectType;

	}

	//#not-tested!!!
	void SkyShaderProperty::write(NiStream& stream) {

		BSShaderLightingProperty::write(stream);

		fileName.write(stream);
		stream << skyObjectType;
	}


	void TileShaderProperty::read(NiStream& stream) {

		BSShaderLightingProperty::read(stream);

		fileName.read(stream);

	}

	//#not-tested!!!
	void TileShaderProperty::write(NiStream& stream) {

		BSShaderLightingProperty::write(stream);

		fileName.write(stream);
	}


	void NiGeometryData::read(NiStream& stream) {

		stream >> groupID;
		stream >> numVertices;
		stream >> keepFlags;
		stream >> compressFlags;
		stream >> hasVertices;

		if (hasVertices) {
			vertices.resize(numVertices);
			for (unsigned int i = 0; i < numVertices; i++) {
				stream >> vertices[i];
			}
		}

		stream >> bsVectorFlags;

		stream >> hasNormals;

		if (hasNormals) {

			normals.resize(numVertices);
			for (unsigned int i = 0; i < numVertices; i++) {
				stream >> normals[i];
			}

			unsigned short hasTangents = bsVectorFlags & 0xF000; //if last 4 bits (F) has any value, means has tangents

			if (hasTangents) {

				tangents.resize(numVertices);
				for (unsigned int i = 0; i < numVertices; i++) {
					stream >> tangents[i];
				}

				bitangents.resize(numVertices);
				for (unsigned int i = 0; i < numVertices; i++) {
					stream >> bitangents[i];
				}
			}

		}

		stream >> center;
		stream >> radius;

		stream >> hasVertexColors;
		if (hasVertexColors) {
			vertexColors.resize(numVertices);
			for (unsigned int i = 0; i < numVertices; i++) {
				stream >> vertexColors[i];
			}
		}

		unsigned char numUvSets = bsVectorFlags & 0x1;


		if (numUvSets > 0) {
			uvSets.resize(numUvSets);
			for (unsigned int i = 0; i < numUvSets; i++) {
				uvSets[i].resize(numVertices);
				for (unsigned int j = 0; j < numVertices; j++) {
					stream >> uvSets[i][j];
				}
			}
		}

		stream >> consistencyFlags;
		stream >> additionalDataRef;

	}

	void NiGeometryData::write(NiStream& stream) {


		stream << groupID;
		stream << numVertices;
		stream << keepFlags;
		stream << compressFlags;
		stream << hasVertices;

		if (hasVertices) {
			for (unsigned int i = 0; i < numVertices; i++) {
				stream << vertices[i];
			}
		}

		stream << bsVectorFlags;

		stream << materialCRC;

		stream << hasNormals;

		if (hasNormals) {

			for (unsigned int i = 0; i < numVertices; i++) {
				stream << normals[i];
			}

			unsigned short hasTangents = bsVectorFlags & 0xF000; //if last 4 bits (F) has any value, means has tangents

			if (hasTangents) {

				for (unsigned int i = 0; i < numVertices; i++) {
					stream << tangents[i];
				}

				for (unsigned int i = 0; i < numVertices; i++) {
					stream << bitangents[i];
				}
			}

		}

		stream << center;
		stream << radius;

		stream << hasVertexColors;
		if (hasVertexColors) {

			for (unsigned int i = 0; i < numVertices; i++) {
				stream << vertexColors[i];
			}
		}

		unsigned char numTextureSets = bsVectorFlags & 0x1;


		if (numTextureSets > 0) {
			for (unsigned int i = 0; i < numTextureSets; i++) {
				for (unsigned int j = 0; j < numVertices; j++) {
					stream << uvSets[i][j];
				}
			}
		}

		stream << consistencyFlags;
		stream << additionalDataRef;

	}

	void NiTriBasedGeometryData::read(NiStream& stream) {

		NiGeometryData::read(stream);

		stream >> numTriangles;

	}

	void NiTriBasedGeometryData::write(NiStream& stream) {

		NiGeometryData::write(stream);

		stream << numTriangles;

	}


	void NiTriShapeData::read(NiStream& stream) {

		NiTriBasedGeometryData::read(stream);

		stream >> numTrianglePoints;
		stream >> hasTriangles;

		if (hasTriangles) {
			triangles.resize(numTriangles);
			for (int i = 0; i < numTriangles; i++) {
				stream >> triangles[i];
			}
		}
		stream >> numMatchGroups;

		matchGroups.resize(numMatchGroups);
		MatchGroup group;
		for (int i = 0; i < numMatchGroups; i++) {
			stream >> group.numVertices;
			group.vertexIndices.resize(group.numVertices);
			for (int j = 0; j < group.numVertices; j++) {
				stream >> group.vertexIndices[j];
			}
			matchGroups[i] = group;
		}



	}

	// #not-tested!!!
	void NiTriShapeData::write(NiStream& stream) {

		NiTriBasedGeometryData::write(stream);

		stream << numTrianglePoints;
		stream << hasTriangles;

		if (hasTriangles) {
			for (int i = 0; i < numTriangles; i++) {
				stream << triangles[i];
			}
		}

		stream << numMatchGroups;
		for (int i = 0; i < numMatchGroups; i++) {
			stream << matchGroups[i].numVertices;
			for (int j = 0; j < matchGroups[i].numVertices; j++) {
				stream <<  matchGroups[i].vertexIndices[j];
			}
		}
	}


	std::unique_ptr<std::vector<Triangle>> NiTriShapeData::getTriangles() const {

		std::unique_ptr<std::vector<Triangle>> _triangles = std::make_unique<std::vector<Triangle>>();

		for (auto triangle : triangles) {
			_triangles->push_back(triangle);
		}

		return _triangles;
	}




	void NiTriStripsData::read(NiStream& stream) {

		NiTriBasedGeometryData::read(stream);

		stream >> numStrips;

		stripLengths.resize(numStrips);
		for (unsigned int i = 0; i < numStrips; i++) {
			stream >> stripLengths[i];
		}

		stream >> hasPoints;
		if (hasPoints) {
			points.resize(numStrips);
			for (unsigned int i = 0; i < numStrips; i++) {
				points[i].resize(stripLengths[i]);
				for (unsigned int j = 0; j < stripLengths[i]; j++) {
					stream >> points[i][j];
				}
			}
		}

	}

	void NiTriStripsData::write(NiStream& stream) {

		NiTriBasedGeometryData::write(stream);

		stream << numStrips;

		for (unsigned int i = 0; i < numStrips; i++) {
			stream << stripLengths[i];
		}

		stream << hasPoints;
		if (hasPoints) {
			for (unsigned int i = 0; i < numStrips; i++) {
				for (unsigned int j = 0; j < stripLengths[i]; j++) {
					stream << points[i][j];
				}
			}
		}

	}

	std::unique_ptr<std::vector<Triangle>> NiTriStripsData::getTriangles() const {

		std::unique_ptr<std::vector<Triangle>> triangles = std::make_unique<std::vector<Triangle>>();

		Triangle triangle;

		for (int i = 0; i < numStrips; i++) {
			for (int j = 0; j < stripLengths[i] - 2; j++) {
				if (j & 1) {
					triangle.p1 = points[i][j];
					triangle.p2 = points[i][j + 2];
					triangle.p3 = points[i][j + 1];
				} else {
					triangle.p1 = points[i][j];
					triangle.p2 = points[i][j + 1];
					triangle.p3 = points[i][j + 2];
				}

				if (triangle.p1 == triangle.p2 || triangle.p2 == triangle.p3 || triangle.p3 == triangle.p1) {
					continue;
				}

				triangles->push_back(triangle);
			}
		}



		return triangles;
	}


	void bhkPackedNiTriStripsShape::read(NiStream& stream) {

		stream >> userData;
		stream >> bhkPackedNiTriStripsShape_unknown1;
		stream >> radius;
		stream >> bhkPackedNiTriStripsShape_unknown2;
		stream >> scale;
		stream >> radius2;
		stream >> scale2;
		stream >> dataRef;
	}

	void bhkPackedNiTriStripsShape::write(NiStream& stream) {

		stream << userData;
		stream << bhkPackedNiTriStripsShape_unknown1;
		stream << radius;
		stream << bhkPackedNiTriStripsShape_unknown2;
		stream << scale;
		stream << radius2;
		stream << scale2;
		stream << dataRef;
	}


	void bhkPackedNiTriStripsData::read(NiStream& stream) {

		stream >> numTriangles;

		triangleData.resize(numTriangles);
		for (unsigned int i = 0; i < numTriangles; i++) {
			stream >> triangleData[i];
		}

		stream >> numVertices;
		stream >> hkPackedNiTriStripsData_unknown1;

		vertices.resize(numVertices);
		for (unsigned int i = 0; i < numVertices; i++) {
			stream >> vertices[i];
		}

		stream >> numSubShapes;

		subShapes.resize(numSubShapes);
		for (unsigned int i = 0; i < numSubShapes; i++) {
			stream >> subShapes[i];
		}

	}

	void bhkPackedNiTriStripsData::write(NiStream& stream) {

		stream << numTriangles;

		for (unsigned int i = 0; i < numTriangles; i++) {
			stream << triangleData[i];
		}

		stream << numVertices;
		stream << hkPackedNiTriStripsData_unknown1;

		for (unsigned int i = 0; i < numVertices; i++) {
			stream << vertices[i];
		}

		stream << numSubShapes;

		for (unsigned int i = 0; i < numSubShapes; i++) {
			stream << subShapes[i];
		}

	}


	//#not-tested!!!
	void bhkNiTriStripsShape::read(NiStream& stream) {

		stream >> material;
		stream >> radius;
		stream >> bhkNiTriStripsShape_unknown1;
		stream >> growBy;
		stream >> scale;

		stream >> numParts;
		partRefs.resize(numParts);
		for (unsigned int i = 0; i < numParts; i++) {
			stream >> partRefs[i];
		}

		stream >> numFilters;
		filters.resize(numFilters);
		for (unsigned int i = 0; i < numFilters; i++) {
			stream >> filters[i];
		}
	}

	void bhkNiTriStripsShape::write(NiStream& stream) {

		stream << material;
		stream << radius;
		stream << bhkNiTriStripsShape_unknown1;
		stream << growBy;
		stream << scale;

		stream << numParts;
		for (unsigned int i = 0; i < numParts; i++) {
			stream << partRefs[i];
		}

		stream << numFilters;
		for (unsigned int i = 0; i < numFilters; i++) {
			stream << filters[i];
		}

	}






	void NiGeometry4::read(NiStream& stream) {}

	void NiGeometry4::write(NiStream& stream) {

		NiAvObject::write(stream);

		stream << boundingSphereCenter;

		stream << boundingSphereRadius;

		stream << skinRef;

		stream << shaderPropertyRef;

		stream << alphaPropertyRef;

		stream << vertexDesc.get();

	}



	void BSTriShape::read(NiStream& stream) {}

	void BSTriShape::write(NiStream& stream) {

		NiGeometry4::write(stream);

		stream << numTriangles;

		stream << numVertices;

		stream << dataSize;

		if (dataSize > 0) {

			half_float::half half;

			for (int i = 0; i < numVertices; i++) {

				auto& vertex = vertexData[i];

				if (vertexDesc.hasVertices()) {

					if (vertexDesc.isFullPrecision()) {

						stream << vertex.vertex;
						stream << vertex.bitangentX;

					} else {

						half = vertex.vertex.x;
						stream.write((char*)&half, 2);
						half = vertex.vertex.y;
						stream.write((char*)&half, 2);
						half = vertex.vertex.z;
						stream.write((char*)&half, 2);
						half = vertex.bitangentX;
						stream.write((char*)&half, 2);

					}
				}

				if (vertexDesc.hasUVs()) {

					half = vertex.uv.u;
					stream.write((char*)&half, 2);
					half = vertex.uv.v;
					stream.write((char*)&half, 2);

				}

				if (vertexDesc.hasNormals()) {

					for (int j = 0; j < 3; j++) {
						stream << vertex.normal[j];
					}

					stream << vertex.bitangentY;

					if (vertexDesc.hasTangents()) {

						for (int j = 0; j < 3; j++) {
							stream << vertex.tangent[j];
						}

						stream << vertex.bitangentZ;

					}
				}

				if (vertexDesc.hasVertexColors()) {

					for (int j = 0; j < 4; j++) {
						stream << vertex.vertexColors[j];
					}

				}


				if (vertexDesc.isSkinned()) {

					for (int j = 0; j < 4; j++) {

						half = vertex.boneWeights[j];
						stream.write((char*)&half, 2);

					}

					for (int j = 0; j < 4; j++) {
						stream << vertex.boneIndices[j];
					}

				}

				if (vertexDesc.hasEyeData()) {
					stream << vertex.eyeData;
				}

			}
		}

		if (dataSize > 0) {
			for (unsigned int i = 0; i < numTriangles; i++) {
				stream << triangles[i];
			}

		}



	}




	void BSSubIndexTriShape::read(NiStream& stream) {}

	void BSSubIndexTriShape::write(NiStream& stream) {

		BSTriShape::write(stream);

		if (dataSize > 0) {
			stream << numPrimitives;
			stream << numSegments;
			stream << totalSegments;

			for (auto &segment : segments) {
				stream << segment.startIndex;
				stream << segment.numPrimitives;
				stream << segment.parentArrayIndex;
				stream << segment.numSubSegments;

				for (auto &subSegment : segment.subSegments) {
					stream << subSegment.startIndex;
					stream << subSegment.numPrimitives;
					stream << subSegment.arrayIndex;
					stream << subSegment.unused;
				}
			}

			if (numSegments < totalSegments) {
				stream << segmentData.numSegments;
				stream << segmentData.totalSegments;

				for (auto &arrayIndex : segmentData.arrayIndices)
					stream << arrayIndex;

				for (auto &perSegmentData : segmentData.arrayPerSegmentData) {
					stream << perSegmentData.userIndex;
					stream << perSegmentData.boneID;
					stream << perSegmentData.numCutOffsets;

					for (auto &cutOffset : perSegmentData.cutOffsets)
						stream << cutOffset;
				}
				segmentData.ssfFile.write(stream);
			}
		}


	}



	void BSLightingShaderProperty::read(NiStream& stream) {}

	void BSLightingShaderProperty::write(NiStream& stream) {



		stream << shaderType;

		BSShaderProperty::write(stream);

		stream << textureSetRef;

		stream << emissiveColor;

		stream << emissiveMultiple;

		stream << wetMaterialNameRef;

		stream << textureClampMode;

		stream << alpha;

		stream << refractionStrength;

		stream << smoothness;

		stream << specularColor;

		stream << specularStrength;

		stream << subsurfaceRolloff;

		stream << rimlightPower;

		stream << backlightPower;

		stream << grayscaleToPaletteScale;

		stream << fresnelPower;

		stream << wetnessSpecScale;

		stream << wetnessSpecPower;

		stream << wetnessMinVar;

		stream << wetnessEnvmapScale;

		stream << wetnessFresnelPower;

		stream << wetnessMetalness;

		switch (shaderType) {
		case 1:
			stream << environmentMapScale;
			stream << unkEnvmapShort;
			break;
		case 5:
			stream << skinTintColor;
			stream << unknownSkinTintInt;
			break;
		case 6:
			stream << hairTintColor;
			break;
		case 7:
			stream << maxPasses;
			stream << scale;
			break;
		case 11:
			stream << parallaxInnerLayerThickness;
			stream << parallaxRefractionScale;
			stream << parallaxInnerLayerTextureScale;
			stream << parallaxEnvmapStrength;
			break;
		case 14:
			stream << sparkleParameters;
			break;
		case 16:
			stream << eyeCubemapScale;
			stream << eyeLeftReflectionCenter;
			stream << eyeRightReflectionCenter;
			break;
		}

	}

	void BSEffectShaderProperty::read(NiStream& stream) {}

	void BSEffectShaderProperty::write(NiStream& stream) {

		BSShaderProperty::write(stream);

		sourceTexture.write(stream);

		stream << textureClampMode;

		stream << lightingInfluence;

		stream << envMapMinLOD;

		stream << unknownByte;

		stream << falloffStartAngle;

		stream << falloffStopAngle;

		stream << falloffStartOpacity;

		stream << falloffStopOpacity;

		stream << emissiveColor;

		stream << emissiveMultiple;

		stream << softFalloffDepth;

		greyscaleTexture.write(stream);

		envMapTexture.write(stream);

		normalTexture.write(stream);

		envMaskTexture.write(stream);

		stream << envMapScale;

	}

	void BSWaterShaderProperty::read(NiStream& stream) {}

	void BSWaterShaderProperty::write(NiStream& stream) {

		BSShaderProperty::write(stream);

		stream << waterFlags;

	}

	void BSSkyShaderProperty::read(NiStream& stream) {}

	void BSSkyShaderProperty::write(NiStream& stream) {

		BSShaderProperty::write(stream);

		baseTexture.write(stream);
		stream << skyFlags;

	}



	void BSMasterParticleSystem::read(NiStream& stream) {

		NiNode::read(stream);

		stream >> maxEmitterObjects;

		stream >> numParticleSysRefs;

		particleSysRefs.resize(numParticleSysRefs);
		for (unsigned int i = 0; i < numParticleSysRefs; i++) {
			stream >> particleSysRefs[i];
		}
	}


	void BSMasterParticleSystem::write(NiStream& stream) {

		NiNode::write(stream);

		stream << maxEmitterObjects;

		stream << numParticleSysRefs;

		for (unsigned int i = 0; i < numParticleSysRefs; i++) {
			stream << particleSysRefs[i];
		}
	}


	void NiParticleSystem::read(NiStream& stream) {

		NiGeometry3::read(stream);

		stream >> worldSpace;

		stream >> numModifiers;

		modifiers.resize(numModifiers);
		for (unsigned int i = 0; i < numModifiers; i++) {
			stream >> modifiers[i];
		}

	}


	void NiParticleSystem::write(NiStream& stream) {

		NiGeometry4::write(stream);

		stream << farBegin;
		stream << farEnd;
		stream << nearBegin;
		stream << nearEnd;

		stream << dataRef;

		stream << worldSpace;

		stream << numModifiers;

		for (unsigned int i = 0; i < numModifiers; i++) {
			stream << modifiers[i];
		}

	}





	void NiPSysData::read(NiStream& stream) {

		stream >> groupID;
		stream >> numVertices;
		stream >> keepFlags;
		stream >> compressFlags;
		stream >> hasVertices;

		stream >> bsVectorFlags;

		stream >> hasNormals;

		stream >> center;
		stream >> radius;

		stream >> hasVertexColors;

		stream >> consistencyFlags;
		stream >> additionalDataRef;

		stream >> hasRadii;
		stream >> numActive;
		stream >> hasSizes;
		stream >> hasRotations;
		stream >> hasRotationAngles;
		stream >> hasRotationAxes;
		stream >> hasTextureIndices;

		unsigned char numOffsets = 0;
		stream >> numOffsets;
		numSubtexOffsets = numOffsets;

		subtexOffsets.resize(numSubtexOffsets);
		for (unsigned int i = 0; i < numSubtexOffsets; i++) {
			stream >> subtexOffsets[i];
		}

		stream >> hasRotationSpeeds;

	}


	void NiPSysData::write(NiStream& stream) {

		stream << groupID;
		stream << numVertices;
		stream << keepFlags;
		stream << compressFlags;
		stream << hasVertices;

		stream << bsVectorFlags;

		stream << materialCRC;

		stream << hasNormals;

		stream << center;
		stream << radius;

		stream << hasVertexColors;

		stream << consistencyFlags;
		stream << additionalDataRef;

		stream << hasRadii;
		stream << numActive;
		stream << hasSizes;
		stream << hasRotations;
		stream << hasRotationAngles;
		stream << hasRotationAxes;
		stream << hasTextureIndices;

		stream << numSubtexOffsets;


		for (unsigned int i = 0; i < numSubtexOffsets; i++) {
			stream << subtexOffsets[i];
		}

		stream << aspectRatio;
		stream << aspectFlags;
		stream << speedToAspectAspect2;
		stream << speedToAspectSpeed1;
		stream << speedToAspectSpeed2;

		stream << hasRotationSpeeds;

	}

	void BSStripPSysData::read(NiStream& stream) {

		NiPSysData::read(stream);

		stream >> maxPointCount;
		stream >> startCapSize;
		stream >> endCapSize;
		stream >> doZPrepass;
	}

	void BSStripPSysData::write(NiStream& stream) {

		NiPSysData::write(stream);

		stream << maxPointCount;
		stream << startCapSize;
		stream << endCapSize;
		stream << doZPrepass;
	}




	void NiFloatInterpController::read(NiStream& stream) {

		stream >> nextControllerRef;
		stream >> flags;
		stream >> frequency;
		stream >> phase;
		stream >> startTime;
		stream >> stopTime;
		stream >> targetRef;
		stream >> interpolatorRef;
	}


	void NiFloatInterpController::write(NiStream& stream) {

		stream << nextControllerRef;
		stream << flags;
		stream << frequency;
		stream << phase;
		stream << startTime;
		stream << stopTime;
		stream << targetRef;
		stream << interpolatorRef;
	}


	void FloatController::read(NiStream& stream) {

		NiFloatInterpController::read(stream);

		stream >> typeOfControlledVariable;
	}


	void FloatController::write(NiStream& stream) {

		NiFloatInterpController::write(stream);

		stream << typeOfControlledVariable;
	}

	void ColorController::read(NiStream& stream) {

		NiFloatInterpController::read(stream);

		stream >> typeOfControlledColor;
	}


	void ColorController::write(NiStream& stream) {

		NiFloatInterpController::write(stream);

		stream << typeOfControlledColor;
	}


	void NiMaterialColorController::read(NiStream& stream) {

		NiFloatInterpController::read(stream);

		stream >> targetColor;
	}


	void NiMaterialColorController::write(NiStream& stream) {

		NiFloatInterpController::write(stream);

		stream << targetColor;
	}


	void NiTextureTransformController::read(NiStream& stream) {

		NiFloatInterpController::read(stream);

		stream >> shaderMap;
		stream >> textureSlot;
		stream >> operation;
	}


	void NiTextureTransformController::write(NiStream& stream) {

		NiFloatInterpController::write(stream);

		stream << shaderMap;
		stream << textureSlot;
		stream << operation;
	}




	void NiDynamicEffect::read(NiStream& stream) {

		NiAvObject::read(stream);

		stream >> switchState;

		stream >> numAffectedNodes;

		affectedNodes.resize(numAffectedNodes);
		for (unsigned int i = 0; i < numAffectedNodes; i++) {
			stream >> affectedNodes[i];
		}

	}

	void NiDynamicEffect::write(NiStream& stream) {

		NiAvObject::write(stream);

	}


	void NiLight::read(NiStream& stream) {

		NiDynamicEffect::read(stream);

		stream >> dimmer;
		stream >> ambientColor;
		stream >> diffuseColor;
		stream >> specularColor;

	}

	void NiLight::write(NiStream& stream) {

		NiDynamicEffect::write(stream);

		stream << dimmer;
		stream << ambientColor;
		stream << diffuseColor;
		stream << specularColor;

	}



	void NiPointLight::read(NiStream& stream) {

		NiLight::read(stream);

		stream >> constantAttenuation;
		stream >> linearAttenuation;
		stream >> quadraticAttenuation;

	}

	void NiPointLight::write(NiStream& stream) {

		NiLight::write(stream);

		stream << constantAttenuation;
		stream << linearAttenuation;
		stream << quadraticAttenuation;

	}


	void NiSpotLight::read(NiStream& stream) {

		NiPointLight::read(stream);

		stream >> cutoffAngle;
		stream >> unkFloat;
		stream >> exponent;
	}

	void NiSpotLight::write(NiStream& stream) {

		NiPointLight::write(stream);

		stream << cutoffAngle;
		stream << unkFloat;
		stream << exponent;
	}




	void NiSequence::read(NiStream& stream) {

		stream >> nameRef;

		stream >> numControlledBlocks;

		stream >> arrayGrowBy;

		controlledBlocks.resize(numControlledBlocks);
		for (unsigned int i = 0; i < numControlledBlocks; i++) {
			//stream >> controlledBlocks[i];
			stream >> controlledBlocks[i].interpolatorRef;
			stream >> controlledBlocks[i].controllerRef;
			stream >> controlledBlocks[i].priority;
			stream >> controlledBlocks[i].nodeName;
			stream >> controlledBlocks[i].propType;
			stream >> controlledBlocks[i].controllerType;
			stream >> controlledBlocks[i].controllerID;
			stream >> controlledBlocks[i].interpolatorID;
		}
	}

	void NiSequence::write(NiStream& stream) {

		stream << nameRef;

		stream << numControlledBlocks;

		stream << arrayGrowBy;

		for (unsigned int i = 0; i < numControlledBlocks; i++) {
			//stream << controlledBlocks[i];
			stream << controlledBlocks[i].interpolatorRef;
			stream << controlledBlocks[i].controllerRef;
			stream << controlledBlocks[i].priority;
			stream << controlledBlocks[i].nodeName;
			stream << controlledBlocks[i].propType;
			stream << controlledBlocks[i].controllerType;
			stream << controlledBlocks[i].controllerID;
			stream << controlledBlocks[i].interpolatorID;
		}

	}



	void NiControllerSequence::read(NiStream& stream) {

		NiSequence::read(stream);

		stream >> weight;
		stream >> textKeyRef;
		stream >> cycleType;
		stream >> frequency;
		stream >> startTime;
		stream >> stopTime;
		stream >> managerRef;
		stream >> accumRootName;

		stream >> numAnimNoteRefs;

		animNoteRefs.resize(numAnimNoteRefs);
		for (unsigned int i = 0; i < numAnimNoteRefs; i++) {
			stream >> animNoteRefs[i];
		}

	}

	void NiControllerSequence::write(NiStream& stream) {

		NiSequence::write(stream);

		stream << weight;
		stream << textKeyRef;
		stream << cycleType;
		stream << frequency;
		stream << startTime;
		stream << stopTime;
		stream << managerRef;
		stream << accumRootName;

		stream << numAnimNoteRefs;

		for (unsigned int i = 0; i < numAnimNoteRefs; i++) {
			stream << animNoteRefs[i];
		}
	}









	void NiSkinInstance::read(NiStream& stream) {

		stream >> dataRef;
		stream >> skinPartitionRef;
		stream >> skeletonRoot;

		stream >> numBones;

		boneRefs.resize(numBones);
		for (unsigned int i = 0; i < numBones; i++) {
			stream >> boneRefs[i];
		}

	}

	void NiSkinInstance::write(NiStream& stream) {}



	void BSDismemberSkinInstance::read(NiStream& stream) {

		NiSkinInstance::read(stream);

		stream >> numPartitions;

		partitions.resize(numPartitions);
		for (unsigned int i = 0; i < numPartitions; i++) {
			stream >> partitions[i];
		}
	}

	void BSDismemberSkinInstance::write(NiStream& stream) {}





	void NiSkinData::read(NiStream& stream) {

		stream >> skinTransform.rotation;
		stream >> skinTransform.translation;
		stream >> skinTransform.scale;
		stream >> numBones;
		stream >> hasVertexWeights;

		if (hasVertexWeights > 1)
			hasVertexWeights = 1;

		bones.resize(numBones);
		for (unsigned int i = 0; i < numBones; i++) {
			BoneData boneData;
			stream >> boneData.boneTransform.rotation;
			stream >> boneData.boneTransform.translation;
			stream >> boneData.boneTransform.scale;
			stream >> boneData.center;
			stream >> boneData.radius;
			stream >> boneData.numVertices;

			if (hasVertexWeights) {
				boneData.vertexWeights.resize(boneData.numVertices);

				for (int j = 0; j < boneData.numVertices; j++) {
					stream >> boneData.vertexWeights[j].index;
					stream >> boneData.vertexWeights[j].weight;
				}
			}
			else
				boneData.numVertices = 0;

			bones[i] = std::move(boneData);
		}


	}

	void NiSkinData::write(NiStream& stream) {}







	void NiSkinPartition::read(NiStream& stream) {

		stream >> numPartitions;
		partitions.resize(numPartitions);

		for (unsigned int p = 0; p < numPartitions; p++) {

			PartitionBlock partition;
			stream >> partition.numVertices;
			stream >> partition.numTriangles;
			stream >> partition.numBones;
			stream >> partition.numStrips;
			stream >> partition.numWeightsPerVertex;

			partition.bones.resize(partition.numBones);
			for (int i = 0; i < partition.numBones; i++)
				stream >> partition.bones[i];

			stream >> partition.hasVertexMap;
			if (partition.hasVertexMap) {
				partition.vertexMap.resize(partition.numVertices);
				for (int i = 0; i < partition.numVertices; i++)
					stream >> partition.vertexMap[i];
			}

			stream >> partition.hasVertexWeights;
			if (partition.hasVertexWeights) {
				partition.vertexWeights.resize(partition.numVertices);
				for (int i = 0; i < partition.numVertices; i++)
					stream >> partition.vertexWeights[i];
			}

			partition.stripLengths.resize(partition.numStrips);
			for (int i = 0; i < partition.numStrips; i++)
				stream >> partition.stripLengths[i];

			stream >> partition.hasFaces;
			if (partition.hasFaces) {
				partition.strips.resize(partition.numStrips);
				for (int i = 0; i < partition.numStrips; i++) {
					partition.strips[i].resize(partition.stripLengths[i]);
					for (int j = 0; j < partition.stripLengths[i]; j++)
						stream >> partition.strips[i][j];
				}
			}

			if (partition.numStrips == 0 && partition.hasFaces) {
				partition.triangles.resize(partition.numTriangles);
				for (int i = 0; i < partition.numTriangles; i++)
					stream >> partition.triangles[i];
			}

			stream >> partition.hasBoneIndices;
			if (partition.hasBoneIndices) {
				partition.boneIndices.resize(partition.numVertices);
				for (int i = 0; i < partition.numVertices; i++)
					stream >> partition.boneIndices[i];
			}

			partitions[p] = partition;
		}


	}

	void NiSkinPartition::write(NiStream& stream) {}







	void BSSkinInstance::read(NiStream& stream) {}

	void BSSkinInstance::write(NiStream& stream) {

		stream << skeletonRoot;
		stream << dataRef;

		stream << numBones;

		for (unsigned int i = 0; i < numBones; i++) {
			stream << boneRefs[i];
		}

		stream << num_BSSkinInstance_Unknown;

		for (unsigned int i = 0; i < num_BSSkinInstance_Unknown; i++) {
			stream << BSSkinInstance_Unknown[i];
		}

	}

	void BSSkinBoneData::read(NiStream& stream) {}

	void BSSkinBoneData::write(NiStream& stream) {

		stream << numBones;

		for (unsigned int i = 0; i < numBones; i++) {
			stream << boneData[i].center;
			stream << boneData[i].radius;
			stream << boneData[i].boneTransform.rotation;
			stream << boneData[i].boneTransform.translation;
			stream << boneData[i].boneTransform.scale;
		}

	}




}
