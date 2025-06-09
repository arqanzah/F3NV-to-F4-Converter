#include "lib/nif/fo3/NiFile.h"
#include <experimental/filesystem>
#include <cstring>


namespace nif {

	template<typename T>
	void convert_controller(nif::fo3::NiFile& file, int controllerRef, int targetRef) {

		static_assert(std::is_same<nif::fo3::BSLightingShaderProperty, T>::value || std::is_same<nif::fo3::BSEffectShaderProperty, T>::value, "only unsigned [BSEffectShaderProperty and BSLightingShaderProperty] allowed");

		if (auto controller = dynamic_cast<nif::fo3::NiFloatInterpController*>(file.blocks[controllerRef].get())) {


			if (controller->nextControllerRef >= 0) {
				convert_controller<T>(file,  controller->nextControllerRef, targetRef);
			}

			nif::fo3::NiFloatInterpController* newController = nullptr;

			if (dynamic_cast<nif::fo3::NiAlphaController*>(controller)) {

				if (std::is_same<nif::fo3::BSLightingShaderProperty, T>::value) {
					newController = new nif::fo3::BSLightingShaderPropertyFloatController();
				} else {
					newController = new nif::fo3::BSEffectShaderPropertyFloatController();
				}
				static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 5;

			} else if (auto textureTransformController = dynamic_cast<nif::fo3::NiTextureTransformController*>(controller)) {

				if (std::is_same<nif::fo3::BSLightingShaderProperty, T>::value) {
					newController = new nif::fo3::BSLightingShaderPropertyFloatController();
				} else {
					newController = new nif::fo3::BSEffectShaderPropertyFloatController();
				}

				if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_TRANSLATE_U) {
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 6;
				} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_TRANSLATE_V) {
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 8;
				} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_SCALE_U) {
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 7;
				} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_SCALE_V) {
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 9;
				} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_ROTATE) {
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 6; // no rotate option in FloatController
				}

			} else if (dynamic_cast<nif::fo3::NiMaterialColorController*>(controller)) {

				if (std::is_same<nif::fo3::BSLightingShaderProperty, T>::value) {
					newController = new nif::fo3::BSLightingShaderPropertyColorController();
				} else {
					newController = new nif::fo3::BSEffectShaderPropertyColorController();
				}

				static_cast<nif::fo3::ColorController*>(newController)->typeOfControlledColor = 0;

			} else if (dynamic_cast<nif::fo3::BSMaterialEmittanceMultController*>(controller)) {

				if (std::is_same<nif::fo3::BSLightingShaderProperty, T>::value) {
					newController = new nif::fo3::BSLightingShaderPropertyFloatController();
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 4;
				} else {
					newController = new nif::fo3::BSEffectShaderPropertyFloatController();
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 0;
				}

			} else if (dynamic_cast<nif::fo3::BSRefractionStrengthController*>(controller)) {

				if (std::is_same<nif::fo3::BSLightingShaderProperty, T>::value) {
					newController = new nif::fo3::BSLightingShaderPropertyFloatController();
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 0;
				} else {
					newController = new nif::fo3::BSEffectShaderPropertyFloatController();
					static_cast<nif::fo3::FloatController*>(newController)->typeOfControlledVariable = 0;  //BSEffectShaderPropertyFloatController does not have refraction so set to 0
				}

			}

			if (newController) {

				newController->nextControllerRef = controller->nextControllerRef;
				newController->flags = controller->flags;
				newController->frequency = controller->frequency;
				newController->phase = controller->phase;
				newController->startTime =controller->startTime;
				newController->stopTime = controller->stopTime;
				newController->targetRef = targetRef;
				newController->interpolatorRef = controller->interpolatorRef;

				file.blocks[controllerRef] = std::unique_ptr<nif::fo3::NiObject>(newController);
			}

		}

	}



	void convert_shape_properties(nif::fo3::NiFile& file, nif::fo3::NiGeometry3* shape, nif::fo3::NiGeometry4* bsTriShape) {

		nif::fo3::NiAlphaProperty* alpha = nullptr;
		nif::fo3::NiMaterialProperty* material = nullptr;
		nif::fo3::NiStencilProperty* stencil = nullptr;
		nif::fo3::NiTexturingProperty* texturing = nullptr;
		//nif::fo3::NiSourceTexture* sourceTexture = nullptr;


		int shaderIndex = 0xFFFFFFFF;
		nif::fo3::NiShaderProperty* shader = nullptr;


		for (auto& prop: shape->properties) {

			//if (file.blocks[prop]->getBlockName() == nif::fo3::NiAlphaProperty::GET_BLOCK_NAME()) {}
			if (auto _alpha = dynamic_cast<nif::fo3::NiAlphaProperty*>(file.blocks[prop].get())) {

				alpha = _alpha;
				bsTriShape->alphaPropertyRef = prop;

				alpha->threshold = 0;

				alpha->flags &= ~( 1 << 0 ); //disable bleding, otherwise not showing in FO4, for example if flags is 4845, sets to 4844


			} else if (auto _material = dynamic_cast<nif::fo3::NiMaterialProperty*>(file.blocks[prop].get())) {
				material = _material;
			} else if (auto _texturing = dynamic_cast<nif::fo3::NiTexturingProperty*>(file.blocks[prop].get())) {
				texturing = _texturing;
			} else if (auto _stencil = dynamic_cast<nif::fo3::NiStencilProperty*>(file.blocks[prop].get())) {
				stencil = _stencil;
			//} else if (auto _sourceTexture = dynamic_cast<nif::fo3::NiSourceTexture*>(file.blocks[prop].get())) {
				//sourceTexture = _sourceTexture;
			} else if (auto _shader = dynamic_cast<nif::fo3::NiShaderProperty*>(file.blocks[prop].get())) {
				shader = _shader;
				shaderIndex = prop;
			}

		}

		if (shader) {
			if (auto shaderPPLightingProperty = dynamic_cast<nif::fo3::BSShaderPPLightingProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSLightingShaderProperty> bsLightingShaderProperty = std::make_unique<nif::fo3::BSLightingShaderProperty>();

				bsLightingShaderProperty->textureSetRef = shaderPPLightingProperty->textureSetRef;

				if (shaderPPLightingProperty->shaderFlags1 & (1 << 1)) {
					bsLightingShaderProperty->shaderFlags1 |= (1 << 1); //skinned
				}

				if (material) {
					bsLightingShaderProperty->specularColor = material->specularColor;
					bsLightingShaderProperty->emissiveColor = material->emissiveColor;
					bsLightingShaderProperty->smoothness = material->glossiness;
					bsLightingShaderProperty->alpha = material->alpha;
					bsLightingShaderProperty->emissiveMultiple = material->emissiveMult;

					if (material->controllerRef >= 0) {
						convert_controller<nif::fo3::BSLightingShaderProperty>(file, material->controllerRef, shaderIndex);
						bsLightingShaderProperty->controllerRef = material->controllerRef;
					}

				}

				if (texturing) {
					if (texturing->controllerRef >= 0) {
						convert_controller<nif::fo3::BSLightingShaderProperty>(file, texturing->controllerRef, shaderIndex);
						bsLightingShaderProperty->controllerRef = texturing->controllerRef;
					}
				}

				if (stencil) {
					bsLightingShaderProperty->shaderFlags2 |= (1 << 4); //set double sided
				}


				if (shaderPPLightingProperty->controllerRef >= 0) {
					convert_controller<nif::fo3::BSLightingShaderProperty>(file, shaderPPLightingProperty->controllerRef, shaderIndex);
					bsLightingShaderProperty->controllerRef = shaderPPLightingProperty->controllerRef;
				}


				file.blocks[shaderIndex] = std::move(bsLightingShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;


			} else if (auto shaderNoLightingProperty = dynamic_cast<nif::fo3::BSShaderNoLightingProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSEffectShaderProperty> bsEffectShaderProperty = std::make_unique<nif::fo3::BSEffectShaderProperty>();

				bsEffectShaderProperty->textureClampMode = shaderNoLightingProperty->textureClampMode;
				bsEffectShaderProperty->falloffStartAngle = shaderNoLightingProperty->falloffStartAngle;
				bsEffectShaderProperty->falloffStartOpacity = shaderNoLightingProperty->falloffStartOpacity;
				bsEffectShaderProperty->falloffStopAngle = shaderNoLightingProperty->falloffStopAngle;
				bsEffectShaderProperty->falloffStopOpacity = shaderNoLightingProperty->falloffStopOpacity;

				if (material) {
					bsEffectShaderProperty->emissiveColor.x = material->emissiveColor.x;
					bsEffectShaderProperty->emissiveColor.y = material->emissiveColor.y;
					bsEffectShaderProperty->emissiveColor.z = material->emissiveColor.z;
					bsEffectShaderProperty->emissiveMultiple = material->emissiveMult;

					if (material->controllerRef >= 0) {
						convert_controller<nif::fo3::BSEffectShaderProperty>(file, material->controllerRef, shaderIndex);
						bsEffectShaderProperty->controllerRef = material->controllerRef;
					}

				}

				if (texturing) {
					if (texturing->controllerRef >= 0) {
						convert_controller<nif::fo3::BSEffectShaderProperty>(file, texturing->controllerRef, shaderIndex);
						bsEffectShaderProperty->controllerRef = texturing->controllerRef;
					}
				}


				if (stencil) {
					bsEffectShaderProperty->shaderFlags2 |= (1 << 4); //set double sided
				}



				if (shaderNoLightingProperty->controllerRef >= 0) {
					convert_controller<nif::fo3::BSEffectShaderProperty>(file, shaderNoLightingProperty->controllerRef, shaderIndex);
					bsEffectShaderProperty->controllerRef = shaderNoLightingProperty->controllerRef;
				}

				file.blocks[shaderIndex] = std::move(bsEffectShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;

			} else if (auto tallGrassShaderProperty = dynamic_cast<nif::fo3::TallGrassShaderProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSLightingShaderProperty> bsLightingShaderProperty = std::make_unique<nif::fo3::BSLightingShaderProperty>();

				std::unique_ptr<nif::fo3::BSShaderTextureSet> bsShaderTextureSet = std::make_unique<nif::fo3::BSShaderTextureSet>();
				bsShaderTextureSet->textures[0].set(tallGrassShaderProperty->fileName.get());
				file.blocks.push_back(std::move(bsShaderTextureSet));
				bsLightingShaderProperty->textureSetRef = file.blocks.size() - 1;

				if (stencil) {
					bsLightingShaderProperty->shaderFlags2 |= (1 << 4); //set double sided
				}

				file.blocks[shaderIndex] = std::move(bsLightingShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;


			} else if (auto tileShaderProperty = dynamic_cast<nif::fo3::TileShaderProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSLightingShaderProperty> bsLightingShaderProperty = std::make_unique<nif::fo3::BSLightingShaderProperty>();

				std::unique_ptr<nif::fo3::BSShaderTextureSet> bsShaderTextureSet = std::make_unique<nif::fo3::BSShaderTextureSet>();
				bsShaderTextureSet->textures[0].set(tileShaderProperty->fileName.get());
				file.blocks.push_back(std::move(bsShaderTextureSet));
				bsLightingShaderProperty->textureSetRef = file.blocks.size() - 1;

				if (stencil) {
					bsLightingShaderProperty->shaderFlags2 |= (1 << 4); //set double sided
				}

				file.blocks[shaderIndex] = std::move(bsLightingShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;


			} else if (dynamic_cast<nif::fo3::WaterShaderProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSWaterShaderProperty> bsWaterShaderProperty = std::make_unique<nif::fo3::BSWaterShaderProperty>();

				file.blocks[shaderIndex] = std::move(bsWaterShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;


			} else if (auto skyShaderProperty = dynamic_cast<nif::fo3::SkyShaderProperty*>(shader)) {

				std::unique_ptr<nif::fo3::BSSkyShaderProperty> bsSkyShaderProperty = std::make_unique<nif::fo3::BSSkyShaderProperty>();

				bsSkyShaderProperty->baseTexture.set(skyShaderProperty->fileName.get());

				file.blocks[shaderIndex] = std::move(bsSkyShaderProperty);
				bsTriShape->shaderPropertyRef = shaderIndex;


			}

		}

	}



	void convert_shapes(nif::fo3::NiFile& file) {

		for (size_t blocIdx = 0; blocIdx < file.blocks.size(); blocIdx++) {

			if (auto shape = dynamic_cast<nif::fo3::NiGeometry3*>(file.blocks[blocIdx].get())) {

				if (auto particleSystem = dynamic_cast<nif::fo3::NiParticleSystem*>(shape)) {

					convert_shape_properties(file, particleSystem, particleSystem);

				} else {

					if (auto data = dynamic_cast<nif::fo3::NiGeometryData*>(file.blocks[shape->dataRef].get())) {

						std::vector<nif::fo3::Vector3>& vertices = data->vertices;

						std::vector<nif::fo3::Vector3>& normals = data->normals;

						std::vector<nif::fo3::Vector4>& vertexColors = data->vertexColors;

						std::vector<nif::fo3::Vector2>* uvSets = nullptr;

						if (!data->uvSets.empty()) {
							uvSets = &data->uvSets[0];
						}

						std::unique_ptr<std::vector<nif::fo3::Triangle>> triangles = data->getTriangles();

						/**/

						nif::fo3::BSTriShape* bsTriShape = nullptr;
						auto bsSegmentShape = dynamic_cast<nif::fo3::BSSegmentedTriShape*>(shape);

						if (bsSegmentShape) {
							bsTriShape = new nif::fo3::BSSubIndexTriShape();
						} else {
							bsTriShape = new nif::fo3::BSTriShape();
						}




						bsTriShape->nameRef = shape->nameRef;
						bsTriShape->controllerRef = shape->controllerRef;
						bsTriShape->skinRef = shape->skinRef;
						bsTriShape->collisionRef = shape->collisionRef;

						bsTriShape->extraDataListCount = shape->extraDataListCount;
						bsTriShape->extraDataList = shape->extraDataList;

						bsTriShape->translation = shape->translation;
						bsTriShape->rotation = shape->rotation;
						bsTriShape->scale = shape->scale;



						convert_shape_properties(file, shape, bsTriShape);


						//----------------------------------------------

						unsigned short maxVerticesIndex = std::numeric_limits<unsigned short>().max(); // @suppress("Ambiguous problem")
						size_t verticesCount = vertices.size();
						if (verticesCount > maxVerticesIndex) {
							bsTriShape->numVertices = 0;
						} else {
							bsTriShape->numVertices = (unsigned short)(verticesCount);
						}

						unsigned int maxTrianglesIndex = std::numeric_limits<unsigned int>().max(); // @suppress("Ambiguous problem")
						size_t trianglesCount = triangles->size();
						if (trianglesCount > maxTrianglesIndex || bsTriShape->numVertices == 0) {
							bsTriShape->numTriangles = 0;
						} else {
							bsTriShape->numTriangles = (unsigned int)(trianglesCount);
						}

						if (uvSets && uvSets->size() != bsTriShape->numVertices) {
							bsTriShape->vertexDesc.setUvs(false);
						}


						bsTriShape->vertexData.resize(bsTriShape->numVertices);


						for (int i = 0; i < bsTriShape->numVertices; i++) {

							auto& vertex = bsTriShape->vertexData[i];
							vertex.vertex = vertices[i];

							if (uvSets && uvSets->size() == bsTriShape->numVertices) {
								vertex.uv = (*uvSets)[i];
							}

							vertex.bitangentX = 0.0f;
							vertex.bitangentY = 0;
							vertex.bitangentZ = 0;
							vertex.normal[0] = vertex.normal[1] = vertex.normal[2] = 0;
							std::memset(vertex.vertexColors, 255, 4);
							std::memset(vertex.boneWeights, 0, sizeof(float) * 4);
							std::memset(vertex.boneIndices, 0, 4);
							vertex.eyeData = 0.0f;

						}

						bsTriShape->triangles.resize(bsTriShape->numTriangles);
						for (unsigned int i = 0; i < bsTriShape->numTriangles; i++) {
							bsTriShape->triangles[i] = (*triangles)[i];
						}



						if (normals.size() == bsTriShape->numVertices) {

							bsTriShape->vertexDesc.setNormals(true);
							for (int i = 0; i < bsTriShape->numVertices; i++) {
								bsTriShape->vertexData[i].normal[0] = (unsigned char)round((((normals[i].x + 1.0f) / 2.0f) * 255.0f));
								bsTriShape->vertexData[i].normal[1] = (unsigned char)round((((normals[i].y + 1.0f) / 2.0f) * 255.0f));
								bsTriShape->vertexData[i].normal[2] = (unsigned char)round((((normals[i].z + 1.0f) / 2.0f) * 255.0f));
							}



							bsTriShape->vertexDesc.setTangents(true);

							//------------------------ calc tangents ----------------------

							if (bsTriShape->vertexDesc.hasNormals() && bsTriShape->vertexDesc.hasUVs()) {

								std::vector<nif::fo3::Vector3> rawNormals;
								rawNormals.resize(bsTriShape->numVertices);
								for (int i = 0; i < bsTriShape->numVertices; i++) {
									float q1 = (((float)bsTriShape->vertexData[i].normal[0]) / 255.0f) * 2.0f - 1.0f;
									float q2 = (((float)bsTriShape->vertexData[i].normal[1]) / 255.0f) * 2.0f - 1.0f;
									float q3 = (((float)bsTriShape->vertexData[i].normal[2]) / 255.0f) * 2.0f - 1.0f;

									float x = q1;
									float y = q2;
									float z = q3;

									rawNormals[i].x = x;
									rawNormals[i].z = z;
									rawNormals[i].y = y;

								}


								std::vector<nif::fo3::Vector3> tan1;
								std::vector<nif::fo3::Vector3> tan2;
								tan1.resize(bsTriShape->numVertices);
								tan2.resize(bsTriShape->numVertices);

								for (std::size_t i = 0; i < bsTriShape->triangles.size(); i++) {
									int i1 = bsTriShape->triangles[i].p1;
									int i2 = bsTriShape->triangles[i].p2;
									int i3 = bsTriShape->triangles[i].p3;

									if (i1 >= bsTriShape->numVertices || i2 >= bsTriShape->numVertices || i3 >= bsTriShape->numVertices)
										continue;

									nif::fo3::Vector3 v1 = bsTriShape->vertexData[i1].vertex;
									nif::fo3::Vector3 v2 = bsTriShape->vertexData[i2].vertex;
									nif::fo3::Vector3 v3 = bsTriShape->vertexData[i3].vertex;

									nif::fo3::Vector2 w1 = bsTriShape->vertexData[i1].uv;
									nif::fo3::Vector2 w2 = bsTriShape->vertexData[i2].uv;
									nif::fo3::Vector2 w3 = bsTriShape->vertexData[i3].uv;

									float x1 = v2.x - v1.x;
									float x2 = v3.x - v1.x;
									float y1 = v2.y - v1.y;
									float y2 = v3.y - v1.y;
									float z1 = v2.z - v1.z;
									float z2 = v3.z - v1.z;

									float s1 = w2.u - w1.u;
									float s2 = w3.u - w1.u;
									float t1 = w2.v - w1.v;
									float t2 = w3.v - w1.v;

									float r = (s1 * t2 - s2 * t1);
									r = (r >= 0.0f ? +1.0f : -1.0f);

									nif::fo3::Vector3 sdir = nif::fo3::Vector3((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
									nif::fo3::Vector3 tdir = nif::fo3::Vector3((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

									sdir.normalize();
									tdir.normalize();

									tan1[i1] += tdir;
									tan1[i2] += tdir;
									tan1[i3] += tdir;

									tan2[i1] += sdir;
									tan2[i2] += sdir;
									tan2[i3] += sdir;
								}


								std::vector<nif::fo3::Vector3> rawTangents;
								std::vector<nif::fo3::Vector3> rawBitangents;

								rawTangents.resize(bsTriShape->numVertices);
								rawBitangents.resize(bsTriShape->numVertices);


								for (int i = 0; i < bsTriShape->numVertices; i++) {
									rawTangents[i] = tan1[i];
									rawBitangents[i] = tan2[i];

									if (rawTangents[i].isZero() || rawBitangents[i].isZero()) {
										rawTangents[i].x = rawNormals[i].y;
										rawTangents[i].y = rawNormals[i].z;
										rawTangents[i].z = rawNormals[i].x;
										rawBitangents[i] = rawNormals[i].cross(rawTangents[i]);
									}
									else {
										rawTangents[i].normalize();
										rawTangents[i] = (rawTangents[i] - rawNormals[i] * rawNormals[i].dot(rawTangents[i]));
										rawTangents[i].normalize();

										rawBitangents[i].normalize();

										rawBitangents[i] = (rawBitangents[i] - rawNormals[i] * rawNormals[i].dot(rawBitangents[i]));
										rawBitangents[i] = (rawBitangents[i] - rawTangents[i] * rawTangents[i].dot(rawBitangents[i]));

										rawBitangents[i].normalize();
									}

									bsTriShape->vertexData[i].tangent[0] = (unsigned char)round((((rawTangents[i].x + 1.0f) / 2.0f) * 255.0f));
									bsTriShape->vertexData[i].tangent[1] = (unsigned char)round((((rawTangents[i].y + 1.0f) / 2.0f) * 255.0f));
									bsTriShape->vertexData[i].tangent[2] = (unsigned char)round((((rawTangents[i].z + 1.0f) / 2.0f) * 255.0f));

									bsTriShape->vertexData[i].bitangentX = rawBitangents[i].x;
									bsTriShape->vertexData[i].bitangentY = (unsigned char)round((((rawBitangents[i].y + 1.0f) / 2.0f) * 255.0f));
									bsTriShape->vertexData[i].bitangentZ = (unsigned char)round((((rawBitangents[i].z + 1.0f) / 2.0f) * 255.0f));
								}

							}





							//------------------------ calc tangents ----------------------


						} else {
							bsTriShape->vertexDesc.setNormals(false);
							bsTriShape->vertexDesc.setTangents(false);
						}

						//----------------------------------------------



						//bsTriShape->flags = 14;
						bsTriShape->flags = shape->flags;

						if (shape->skinRef == int(0xFFFFFFFF)) {
							bsTriShape->boundingSphereCenter = data->center;
							bsTriShape->boundingSphereRadius = data->radius;
						}


						if (bsSegmentShape) {

							//process segments

						}




						if (bsTriShape->numVertices > 0) {

							bool removeColors = true;
							nif::fo3::Vector4 blank(1.0f, 1.0f, 1.0f, 1.0f);
							for (auto& color : vertexColors) {
								if (color != blank) {
									removeColors = false;
									break;
								}
							}

							if (!removeColors && vertexColors.size() > 0) {

								if (!bsTriShape->vertexDesc.hasVertexColors()) {
									for (auto &v : bsTriShape->vertexData) {
										v.vertexColors[0] = 255;
										v.vertexColors[1] = 255;
										v.vertexColors[2] = 255;
										v.vertexColors[3] = 255;
									}
								}
								bsTriShape->vertexDesc.setVertexColors(true);

								for (int i = 0; i < bsTriShape->numVertices; i++) {
									auto& vertex = bsTriShape->vertexData[i];

									float f = std::max(0.0f, std::min(1.0f, vertexColors[i].x));
									vertex.vertexColors[0] = (unsigned char)std::floor(f == 1.0f ? 255 : f * 256.0);

									f = std::max(0.0f, std::min(1.0f, vertexColors[i].y));
									vertex.vertexColors[1] = (unsigned char)std::floor(f == 1.0f ? 255 : f * 256.0);

									f = std::max(0.0f, std::min(1.0f, vertexColors[i].z));
									vertex.vertexColors[2] = (unsigned char)std::floor(f == 1.0f ? 255 : f * 256.0);

									f = std::max(0.0f, std::min(1.0f, vertexColors[i].w));
									vertex.vertexColors[3] = (unsigned char)std::floor(f == 1.0f ? 255 : f * 256.0);
								}
							}



						}

						// ============================== skin ===============================================


						if (bsTriShape->numVertices > 0 && shape->skinRef >= 0) {

							bsTriShape->vertexDesc.setSkinned(true);

							if (auto skinInstance = dynamic_cast<nif::fo3::NiSkinInstance*>(file.blocks[shape->skinRef].get())) {

								if (skinInstance->dataRef >= 0) {

									auto skinData = dynamic_cast<nif::fo3::NiSkinData*>(file.blocks[skinInstance->dataRef].get());

									if (skinData) {
										std::unique_ptr<nif::fo3::BSSkinBoneData> bsSkinBoneData = std::make_unique<nif::fo3::BSSkinBoneData>();

										bsSkinBoneData->numBones = skinData->numBones;
										bsSkinBoneData->boneData.resize(skinData->numBones);

										for (unsigned int i = 0; i < skinData->numBones; i++) {

											bsSkinBoneData->boneData[i].center = skinData->bones[i].center;
											bsSkinBoneData->boneData[i].radius = skinData->bones[i].radius;
											bsSkinBoneData->boneData[i].boneTransform = skinData->bones[i].boneTransform;

										}

										//bsTriShape->translation = bsTriShape->translation + skinData->skinTransform.translation;
										//bsTriShape->rotation = bsTriShape->rotation + skinData->skinTransform.rotation;

										file.blocks[skinInstance->dataRef] = std::move(bsSkinBoneData);
									}


								}

								if (skinInstance->skinPartitionRef >= 0) {

									auto skinPartition = dynamic_cast<nif::fo3::NiSkinPartition*>(file.blocks[skinInstance->skinPartitionRef].get());

									for (unsigned int i = 0; i < skinPartition->numPartitions; i++) {

										auto& partBlock = skinPartition->partitions[i];

										for (unsigned short j = 0; j < partBlock.numVertices; j++) {

											const unsigned short map = partBlock.vertexMap[j];

											if (bsTriShape->vertexData.size() > map) {


												if (partBlock.hasVertexWeights) {
													bsTriShape->vertexData[map].boneWeights[0] = partBlock.vertexWeights[j].w1;
													bsTriShape->vertexData[map].boneWeights[1] = partBlock.vertexWeights[j].w2;
													bsTriShape->vertexData[map].boneWeights[2] = partBlock.vertexWeights[j].w3;
													bsTriShape->vertexData[map].boneWeights[3] = partBlock.vertexWeights[j].w4;
												}

												if (partBlock.hasBoneIndices) {
													auto& boneIndices = partBlock.boneIndices[j];
													bsTriShape->vertexData[map].boneIndices[0] = partBlock.bones[boneIndices.i1];
													bsTriShape->vertexData[map].boneIndices[1] = partBlock.bones[boneIndices.i2];
													bsTriShape->vertexData[map].boneIndices[2] = partBlock.bones[boneIndices.i3];
													bsTriShape->vertexData[map].boneIndices[3] = partBlock.bones[boneIndices.i4];
												}
											}
										}
									}

									file.markForDeletion(skinInstance->skinPartitionRef);
								}

								std::unique_ptr<nif::fo3::BSSkinInstance> bsSkinInstance = std::make_unique<nif::fo3::BSSkinInstance>();

								bsSkinInstance->skeletonRoot = skinInstance->skeletonRoot;
								bsSkinInstance->dataRef = skinInstance->dataRef;
								bsSkinInstance->numBones = skinInstance->numBones;
								bsSkinInstance->boneRefs = skinInstance->boneRefs;

								file.blocks[shape->skinRef] = std::move(bsSkinInstance);

							}

						} else {
							bsTriShape->vertexDesc.setSkinned(false);
						}


						// ============================== /skin ===============================================


						//------------------------ segements ----------------------
						if (bsSegmentShape) {

							nif::fo3::BSSubIndexTriShape* bsSubIndexTriShape = dynamic_cast<nif::fo3::BSSubIndexTriShape*>(bsTriShape);

							bsSubIndexTriShape->numPrimitives = bsSubIndexTriShape->numTriangles;
							bsSubIndexTriShape->numSegments = bsSegmentShape->numSegments;
							bsSubIndexTriShape->totalSegments = bsSegmentShape->numSegments;

							for( auto& segement : bsSegmentShape->segments) {

								nif::fo3::BSSubIndexTriShape::Segment triShapeSegment;
								triShapeSegment.startIndex = segement.index;
								triShapeSegment.numPrimitives = segement.numTrisInSegnent;
								bsSubIndexTriShape->segments.push_back(triShapeSegment);

							}


						}


						//------------------------ calc data ----------------------


						unsigned int vertexSize = 0;
						bsTriShape->dataSize = 0;

						nif::fo3::VertexFlags originalFlags = bsTriShape->vertexDesc.getFlags();
						bsTriShape->vertexDesc.clearAttributeOffsets();

						unsigned int attributeSizes[nif::fo3::VertexAttribute::VA_COUNT] = {};

						if (bsTriShape->vertexDesc.hasVertices()) {
							if (bsTriShape->vertexDesc.isFullPrecision())
								attributeSizes[nif::fo3::VertexAttribute::VA_POSITION] = 4;
							else
								attributeSizes[nif::fo3::VertexAttribute::VA_POSITION] = 2;
						}

						if (bsTriShape->vertexDesc.hasUVs())
							attributeSizes[nif::fo3::VertexAttribute::VA_TEXCOORD0] = 1;

						if (bsTriShape->vertexDesc.hasUVs2())
							attributeSizes[nif::fo3::VertexAttribute::VA_TEXCOORD1] = 1;

						if (bsTriShape->vertexDesc.hasNormals()) {
							attributeSizes[nif::fo3::VertexAttribute::VA_NORMAL] = 1;

							if (bsTriShape->vertexDesc.hasTangents())
								attributeSizes[nif::fo3::VertexAttribute::VA_BINORMAL] = 1;
						}

						if (bsTriShape->vertexDesc.hasVertexColors())
							attributeSizes[nif::fo3::VertexAttribute::VA_COLOR] = 1;

						if (bsTriShape->vertexDesc.isSkinned())
							attributeSizes[nif::fo3::VertexAttribute::VA_SKINNING] = 3;

						if (bsTriShape->vertexDesc.hasEyeData())
							attributeSizes[nif::fo3::VertexAttribute::VA_EYEDATA] = 1;

						for (int va = 0; va < nif::fo3::VertexAttribute::VA_COUNT; va++) {
							if (attributeSizes[va] != 0) {
								bsTriShape->vertexDesc.setAttributeOffset(nif::fo3::VertexAttribute(va), vertexSize);
								vertexSize += attributeSizes[va] * 4;
							}
						}

						bsTriShape->vertexDesc.setSize(vertexSize);
						bsTriShape->vertexDesc.setFlags(originalFlags);



						if (dynamic_cast<nif::fo3::BSDynamicTriShape*>(bsTriShape))
							bsTriShape->vertexDesc.setDynamic();

						bsTriShape->dataSize = vertexSize * bsTriShape->numVertices + 6 * bsTriShape->numTriangles;


						//------------------------ calc data ----------------------

						file.markForDeletion(shape->dataRef);

						auto swap = std::unique_ptr<nif::fo3::NiObject>(bsTriShape);

						file.blocks[blocIdx].swap(swap);


					}


				}


			}
		}

	}




	void convert_collision_shape(nif::fo3::NiFile& file,  nif::fo3::bhkShape* shape, int shapeRef, std::vector<int> &alreadyScaledShapes) {

		const float scale = 0.1f;

		bool isShapeAlreadyScaled = std::find(alreadyScaledShapes.begin(), alreadyScaledShapes.end(), shapeRef) != alreadyScaledShapes.end();

		if (auto moppBvTreeShape = dynamic_cast<nif::fo3::bhkMoppBvTreeShape*>(shape)) {

			int childShapeRef = moppBvTreeShape->shapeRef;
			auto childShape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[childShapeRef].get());
			convert_collision_shape(file, childShape, childShapeRef, alreadyScaledShapes);

		} else if (auto packedNiTriStripsShape = dynamic_cast<nif::fo3::bhkPackedNiTriStripsShape*>(shape)) {


			int packedNiTriStripsDataRef = packedNiTriStripsShape->dataRef;
			auto packedNiTriStripsData = dynamic_cast<nif::fo3::bhkPackedNiTriStripsData*>(file.blocks[packedNiTriStripsDataRef].get());

			std::vector<nif::fo3::TriangleData> triData = packedNiTriStripsData->triangleData;
			std::vector<nif::fo3::Vector3> vertData = packedNiTriStripsData->vertices;



			std::unique_ptr<nif::fo3::NiTriStripsData> triStripsData = std::make_unique<nif::fo3::NiTriStripsData>();
			triStripsData->numVertices = packedNiTriStripsData->vertices.size();


			triStripsData->hasVertices = 1;
			for (size_t i = 0; i < vertData.size(); i++) {
				nif::fo3::Vector3 v3;
				v3.x = vertData.at(i).x * 7;
				v3.y = vertData.at(i).y * 7;
				v3.z = vertData.at(i).z * 7;
				triStripsData->vertices.push_back(v3);
			}


			//-------------------------------------------------------copy triangles--------------------------------------------------------------

			for (size_t i = 0; i < triData.size(); i++) {
				triStripsData->stripLengths.push_back(3);
				std::vector<unsigned short> points;

				points.push_back(triData.at(i).triangle.p1);
				points.push_back(triData.at(i).triangle.p2);
				points.push_back(triData.at(i).triangle.p3);

				triStripsData->points.push_back(points);
			}

			triStripsData->hasPoints = 1;
			triStripsData->numStrips = triStripsData->points.size();
			triStripsData->numTriangles = triStripsData->points.size();

			//-------------------------------------------------------copy triangles--------------------------------------------------------------


			std::unique_ptr<nif::fo3::bhkNiTriStripsShape> triStripsShape = std::make_unique<nif::fo3::bhkNiTriStripsShape>();
			nif::fo3::HavokFilter f;


			// -------------- <temporary fix for reversed triangle faces of collision object> -------------------------
			// second NiTriStripsData is created, reverses faces of triangles and added to shape parts
			std::unique_ptr<nif::fo3::NiTriStripsData> collisionFixTriStripsData(new nif::fo3::NiTriStripsData(*(triStripsData.get())));

			for (std::vector<unsigned short> &tri : collisionFixTriStripsData->points) {
				unsigned short buffer = tri.at(0);
				tri.at(0) = tri.at(1);
				tri.at(1) = buffer;
			}

			file.blocks.push_back(std::move(collisionFixTriStripsData));
			int collisionFixtriStripsDataRef = file.blocks.size() - 1;

			triStripsShape->partRefs.push_back(collisionFixtriStripsDataRef);
			triStripsShape->numParts++;

			triStripsShape->filters.push_back(f);
			triStripsShape->numFilters++;

			// -------------- </temporary fix for reversed triangle faces of collision object> -------------------------



			//add new data to blocks
			file.blocks.push_back(std::move(triStripsData));
			int triStripsDataRef = file.blocks.size() - 1;

			//connect data to shape
			triStripsShape->partRefs.push_back(triStripsDataRef);
			triStripsShape->numParts++;


			triStripsShape->filters.push_back(f);
			triStripsShape->numFilters++;


			//replace shape
			file.markForDeletion(packedNiTriStripsDataRef);
			file.blocks[shapeRef] = std::move(triStripsShape);



		} else if (auto convexVerticesShape = dynamic_cast<nif::fo3::bhkConvexVerticesShape*>(shape)) {

			if (!isShapeAlreadyScaled) {
				alreadyScaledShapes.push_back(shapeRef);

				for (size_t i = 0; i < convexVerticesShape->vertices.size(); i++) {
					convexVerticesShape->vertices.at(i).x *= scale;
					convexVerticesShape->vertices.at(i).y *= scale;
					convexVerticesShape->vertices.at(i).z *= scale;
				}

				for (size_t i = 0; i < convexVerticesShape->normals.size(); i++) {
					convexVerticesShape->normals.at(i).w *= scale;
				}

				convexVerticesShape->radius *= scale;

			}

		} else if (auto boxShape = dynamic_cast<nif::fo3::bhkBoxShape*>(shape)) {

			if (!isShapeAlreadyScaled) {
				alreadyScaledShapes.push_back(shapeRef);
				boxShape->dimensions.x *= scale;
				boxShape->dimensions.y *= scale;
				boxShape->dimensions.z *= scale;

				//boxShape->radius *= scale;
			}

		} else if (auto sphereShape = dynamic_cast<nif::fo3::bhkSphereShape*>(shape)) {

			if (!isShapeAlreadyScaled) {
				alreadyScaledShapes.push_back(shapeRef);
				sphereShape->radius *= scale;
			}

		} else if (auto capsuleShape = dynamic_cast<nif::fo3::bhkCapsuleShape*>(shape)) {

			if (!isShapeAlreadyScaled) {
				alreadyScaledShapes.push_back(shapeRef);
				capsuleShape->radius *= scale;
				capsuleShape->radius1 *= scale;
				capsuleShape->radius2 *= scale;
				capsuleShape->point1.x *= scale;
				capsuleShape->point1.y *= scale;
				capsuleShape->point1.z *= scale;
				capsuleShape->point2.x *= scale;
				capsuleShape->point2.y *= scale;
				capsuleShape->point2.z *= scale;
			}

		} else if (auto transformShape = dynamic_cast<nif::fo3::bhkTransformShape*>(shape)) {

			// NEEDS Attention!!!!!!!!!!!!!!  implement corectly

			nif::fo3::Vector3 dim;
			transformShape->transform.getRow(3, dim);
			dim.x *= scale;
			dim.y *= scale;
			dim.z *= scale;
			transformShape->transform.setRow(3, dim);

			//process subshape
			int childShapeRef = transformShape->shapeRef;
			auto childShape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[childShapeRef].get());
			convert_collision_shape(file, childShape, childShapeRef, alreadyScaledShapes);

		} else if (auto listShape = dynamic_cast<nif::fo3::bhkListShape*>(shape)) {

			for (size_t i = 0; i < listShape->subShapeRefs.size(); i++) {
				int childShapeRef = listShape->subShapeRefs[i];
				auto childShape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[childShapeRef].get());
				convert_collision_shape(file, childShape, childShapeRef, alreadyScaledShapes);
			}

		} else if (auto convexListShape = dynamic_cast<nif::fo3::bhkConvexListShape*>(shape)) {

			for (size_t i = 0; i < convexListShape->shapeRefs.size(); i++) {
				int childShapeRef = convexListShape->shapeRefs[i];
				auto childShape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[childShapeRef].get());
				convert_collision_shape(file, childShape, childShapeRef, alreadyScaledShapes);
			}

			nif::fo3::bhkListShape* newListShape = new nif::fo3::bhkListShape();

			newListShape->numSubShapeRefs = convexListShape->numShapeRefs;
			newListShape->subShapeRefs = convexListShape->shapeRefs;
			newListShape->material = convexListShape->material;
			newListShape->childShapeProperty = convexListShape->childShapeProp;

			auto swap = std::unique_ptr<nif::fo3::NiObject>(newListShape);
			file.blocks[shapeRef].swap(swap);

		}

	}


	void convert_collision(nif::fo3::NiFile& file) {

		const float scale = 0.1f;
		std::vector<int> alreadyScaledShapes;

		for (size_t blocIdx = 0; blocIdx < file.blocks.size(); blocIdx++) {

			if (auto node = dynamic_cast<nif::fo3::NiNode*>(file.blocks[blocIdx].get())) {

				int collisionRef = node->collisionRef;
				if (collisionRef >= 0 ) {
					if (auto collision = dynamic_cast<nif::fo3::bhkNiCollisionObject*>(file.blocks[collisionRef].get())) {


						int bodyRef = collision->bodyRef;
						if (auto body = dynamic_cast<nif::fo3::bhkRigidBody*>(file.blocks[bodyRef].get())) {


							int shapeRef = body->shapeRef;
							auto shape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[shapeRef].get());

							convert_collision_shape(file, shape, shapeRef, alreadyScaledShapes);

							body->translation.x = body->translation.x * scale;
							body->translation.y = body->translation.y * scale;
							body->translation.z = body->translation.z * scale;

							body->center.x = body->center.x * scale;
							body->center.y = body->center.y * scale;
							body->center.z = body->center.z * scale;



							std::fill(body->bhkWorldObject_unknown1, body->bhkWorldObject_unknown1 + 4, 0);
							std::fill(body->bhkWorldObject_unknown2, body->bhkWorldObject_unknown2 + 3, 0);

							body->bhkRigidBody_unknown1 = 0;
							std::fill(body->bhkRigidBody_unknown2, body->bhkRigidBody_unknown2 + 4, 0);
							std::fill(body->bhkRigidBody_unknown3, body->bhkRigidBody_unknown3 + 4, 0);
							body->bhkRigidBody_unknown4 = 0;
							std::fill(body->bhkRigidBody_unknown5, body->bhkRigidBody_unknown5 + 4, 0);
							std::fill(body->bhkRigidBody_unknown6, body->bhkRigidBody_unknown6 + 12, 0);


							/*if (newRigidBody->collisionFilter.layer == 1 || body->motionSystem == 7) { //static
												newRigidBody->motionSystem = 0;

							} else if (newRigidBody->collisionFilter.layer == 2 && body->motionSystem == 6) { //animated static: doors, dumster
								newRigidBody->motionSystem = 4;
							} else {
								newRigidBody->motionSystem = body->motionSystem;
							}*/

							if (body->motionSystem == 7) { //motionSystem fixed: buildings, etc
								body->motionSystem = 0;
							}
							else if (body->motionSystem == 6) { //motionSystem keyframed: doors, dumster
								body->motionSystem = 4;
							}
							else {
								//body->motionSystem = body->motionSystem;
							}

							if (body->deactivatorType != 0) {
								body->enableDeactivation = true;
							}




							/*

							std::unique_ptr<nif::fo3::bhkRigidBody> newRigidBody = nullptr;

							if (dynamic_cast<nif::fo3::bhkRigidBodyT*>(body)) {
								newRigidBody = std::make_unique<nif::fo3::bhkRigidBodyT>();
							}
							else {
								newRigidBody = std::make_unique<nif::fo3::bhkRigidBody>();
							}


							newRigidBody->rotation = body->rotation;

							newRigidBody->translation.x = body->translation.x * scale;
							newRigidBody->translation.y = body->translation.y * scale;
							newRigidBody->translation.z = body->translation.z * scale;

							newRigidBody->center.x = body->center.x * scale;
							newRigidBody->center.y = body->center.y * scale;
							newRigidBody->center.z = body->center.z * scale;


							newRigidBody->shapeRef = body->shapeRef;


							newRigidBody->filter = body->filter;
							newRigidBody->broadPhaseType = body->broadPhaseType;
							newRigidBody->cInfoProperty = body->cInfoProperty;

							newRigidBody->collisionResponse = body->collisionResponse;
							newRigidBody->processContactCallbackDelay = body->processContactCallbackDelay;
							newRigidBody->filterCopy = body->filterCopy;

							newRigidBody->linearVelocity = body->linearVelocity;
							newRigidBody->angularVelocity = body->angularVelocity;
							newRigidBody->mass = body->mass;
							newRigidBody->linearDamping = body->linearDamping;
							newRigidBody->angularDamping = body->angularDamping;
							newRigidBody->timeFactor = body->timeFactor;
							newRigidBody->gravityFactor = body->gravityFactor;
							newRigidBody->friction = body->friction;

							newRigidBody->rollingFrictionMult = body->rollingFrictionMult;
							newRigidBody->restitution = body->restitution;
							newRigidBody->maxLinearVelocity = body->maxLinearVelocity;
							newRigidBody->maxAngularVelocity = body->maxAngularVelocity;
							newRigidBody->penetrationDepth = body->penetrationDepth;

							//if (newRigidBody->collisionFilter.layer == 1 || body->motionSystem == 7) { //static
							//	newRigidBody->motionSystem = 0;

							//} else if (newRigidBody->collisionFilter.layer == 2 && body->motionSystem == 6) { //animated static: doors, dumster
							//	newRigidBody->motionSystem = 4;
							//} else {
							//	newRigidBody->motionSystem = body->motionSystem;
							///

							if (body->motionSystem == 7) { //motionSystem fixed: buildings, etc
								newRigidBody->motionSystem = 0;
							}
							else if (body->motionSystem == 6) { //motionSystem keyframed: doors, dumster
								newRigidBody->motionSystem = 4;
							}
							else {
								newRigidBody->motionSystem = body->motionSystem;
							}

							newRigidBody->deactivatorType = body->deactivatorType;
							newRigidBody->solverDeactivation = body->solverDeactivation;
							newRigidBody->qualityType = body->qualityType;
							//newRigidBody->autoRemoveLevel = body->autoRemoveLevel;
							//newRigidBody->responseModifierFlag = body->responseModifierFlag;
							//newRigidBody->numShapeKeysInContactPointProps = body->numShapeKeysInContactPointProps;
							//newRigidBody->forceCollideOntoPpu = body->forceCollideOntoPpu;

							newRigidBody->numConstraints = body->numConstraints;
							newRigidBody->constraints = body->constraints;

							if (newRigidBody->deactivatorType != 0) {
								newRigidBody->enableDeactivation = true;
							}


							file.deleteBlock(bodyRef);


							file.blocks.push_back(std::move(newRigidBody));
							int newRigidBodyRef = file.blocks.size() - 1;

							collision->bodyRef = newRigidBodyRef;
						*/

						} else if (auto simpleShapePhantom = dynamic_cast<nif::fo3::bhkSimpleShapePhantom*>(file.blocks[bodyRef].get())) {

							int childShapeRef = simpleShapePhantom->shapeRef;
							auto childShape = dynamic_cast<nif::fo3::bhkShape*>(file.blocks[childShapeRef].get());
							convert_collision_shape(file, childShape, childShapeRef, alreadyScaledShapes);

						}


					}
				}
			}

		}


	}



	template<typename T_CONTROLLER, typename T_PROPERTY>
	void fix_controller_sequences_controller_block(nif::fo3::NiFile& file, nif::fo3::NiSequence::ControllerBlock &controlledBlock ) {


		if (dynamic_cast<T_CONTROLLER*>(file.blocks[controlledBlock.controllerRef].get())) {

				if (file.strings[controlledBlock.controllerType].get() != T_CONTROLLER::GET_BLOCK_NAME()) {

					std::vector<nif::fo3::NiString<unsigned int>>::iterator controllerTypeIt = std::find_if(file.strings.begin(), file.strings.end(), [&](const nif::fo3::NiString<unsigned int>& str) {
						return str.get() == T_CONTROLLER::GET_BLOCK_NAME();
					});

					if (controllerTypeIt == file.strings.end()) {
						controlledBlock.controllerType = file.addString(T_CONTROLLER::GET_BLOCK_NAME());
					} else {
						controlledBlock.controllerType = std::distance(file.strings.begin(), controllerTypeIt);
					}

					std::vector<nif::fo3::NiString<unsigned int>>::iterator propertyTypeIt = std::find_if(file.strings.begin(), file.strings.end(), [&](const nif::fo3::NiString<unsigned int>& str) {
						return str.get() == T_PROPERTY::GET_BLOCK_NAME();
					});

					if (propertyTypeIt == file.strings.end()) {
						controlledBlock.propType =file. addString(T_PROPERTY::GET_BLOCK_NAME());
					} else {
						controlledBlock.propType = std::distance(file.strings.begin(), propertyTypeIt);
					}

				}

			}

	}


	void fix_controller_sequences(nif::fo3::NiFile& file) {

			for (size_t blocIdx = 0; blocIdx < file.blocks.size(); blocIdx++) {
				if (auto sequence = dynamic_cast<nif::fo3::NiControllerSequence*>(file.blocks[blocIdx].get())) {
					for (auto& controlledBlock : sequence->controlledBlocks) {

						fix_controller_sequences_controller_block<nif::fo3::BSLightingShaderPropertyFloatController, nif::fo3::BSLightingShaderProperty>(file, controlledBlock);
						fix_controller_sequences_controller_block<nif::fo3::BSLightingShaderPropertyColorController, nif::fo3::BSLightingShaderProperty>(file, controlledBlock);

						fix_controller_sequences_controller_block<nif::fo3::BSEffectShaderPropertyFloatController, nif::fo3::BSEffectShaderProperty>(file, controlledBlock);
						fix_controller_sequences_controller_block<nif::fo3::BSEffectShaderPropertyColorController, nif::fo3::BSEffectShaderProperty>(file, controlledBlock);

					}
				}
			}

	}









	void clear(nif::fo3::NiFile& file) {

			for (size_t i = 0; i < file.blocks.size(); i++) {


				if (file.blocks[i]->getBlockName() == nif::fo3::NiTexturingProperty::GET_BLOCK_NAME()) {
					file.markForDeletion(i);
					continue;
				}

				if (file.blocks[i]->getBlockName() == nif::fo3::NiMaterialProperty::GET_BLOCK_NAME()) {
					file.markForDeletion(i);
					continue;
				}

				if (file.blocks[i]->getBlockName() == nif::fo3::NiStencilProperty::GET_BLOCK_NAME()) {
					file.markForDeletion(i);
					continue;
				}

				if (file.blocks[i]->getBlockName() == nif::fo3::NiSourceTexture::GET_BLOCK_NAME()) {
					file.markForDeletion(i);
					continue;
				}

				if (file.blocks[i]->getBlockName() == "BSFurnitureMarker") {// temp fix later
					file.markForDeletion(i);
					continue;
				}

				if (file.blocks[i]->getBlockName() == "BSDecalPlacementVectorExtraData") {// temp fix later
					file.markForDeletion(i);
					continue;
				}

			}

	}







	void processNif(const char* iFilename, const char* oFilename) {


		nif::fo3::NiFile nifFile(iFilename);
		nifFile.userVersion = 12;
		nifFile.userVersion2 = 130;


		convert_shapes(nifFile);
		fix_controller_sequences(nifFile);
		convert_collision(nifFile);

		//generate_material_files(nifFile, iFilename);

		clear(nifFile);

		nifFile.save(oFilename);


	}



	void processFolders(const char* in, const char* out) {

		for (auto& p : std::experimental::filesystem::directory_iterator(in)) {
			if (std::experimental::filesystem::is_directory(p.status())) {

				std::string _out(out);
				_out.append("\\");
				_out.append(p.path().filename().u8string().c_str());
				std::experimental::filesystem::create_directories(_out);

				processFolders(p.path().u8string().c_str(), _out.c_str());

			}
			else if (std::experimental::filesystem::is_regular_file(p.status()) && p.path().extension() == ".nif") {


				std::string _out(out);
				_out.append("\\");
				_out.append(p.path().filename().u8string().c_str());

				std::cout << "Converting: " << p.path().u8string().c_str() << std::endl;


				try {
					processNif(p.path().u8string().c_str(), _out.c_str());
				}
				catch (...) {
					std::cout << "Failed to convert: " << p.path().u8string().c_str() << std::endl;
					std::ofstream file("nif_converter_errors.txt", std::ios_base::app);
					file << "Failed to convert: " << p.path().u8string().c_str() << std::endl;
					file.close();
				}

			}
		}

	}

}






















/*

void generate_material_files(nif::fo3::NiFile& file, const std::string& _fileName) {



	for (size_t blocIdx = 0; blocIdx < file.blocks.size(); blocIdx++) {
		if (auto shape = dynamic_cast<nif::fo3::NiGeometry4*>(file.blocks[blocIdx].get())) {



			nif::fo3::BSLightingShaderProperty* shader = nullptr;
			nif::fo3::BSShaderTextureSet * textureSet = nullptr;
			nif::fo3::NiAlphaProperty* alpha = nullptr;

			if (shape->shaderPropertyRef >= 0) {

				shader = dynamic_cast<nif::fo3::BSLightingShaderProperty*>(file.blocks[shape->shaderPropertyRef].get());

				if (shader && shader->textureSetRef >= 0) {
					textureSet = dynamic_cast<nif::fo3::BSShaderTextureSet*>(file.blocks[shader->textureSetRef].get());
				}

			}


			if (shape->alphaPropertyRef >= 0) {
				alpha = dynamic_cast<nif::fo3::NiAlphaProperty*>(file.blocks[shape->alphaPropertyRef].get());
			}


			if (shader && textureSet) {

				std::string fileName = textureSet->textures.at(0).get();
				//std::string fileName = _fileName;

				if (!fileName.empty()) {

					transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
					fileName.replace(fileName.find("textures"), 8, "materials");
					if (alpha) {
						fileName.replace(fileName.find(".dds"), 4, "_alpha.bgsm");
					}
					else {
						fileName.replace(fileName.find(".dds"), 4, ".bgsm");
					}


					BGSM mf;

					//if (!fs::exists(fileName)) {
					if (!fs::exists("C:\\Games\\Steam\\steamapps\\common\\Fallout 4\\Data\\" + fileName)) {
						std::string dir = fileName.substr(0, fileName.find_last_of("\\/"));
						//fs::create_directories(dir);
						fs::create_directories("C:\\Games\\Steam\\steamapps\\common\\Fallout 4\\Data\\" + dir);
					}
					else {
						//mf.load(fileName);
						mf.load("C:\\Games\\Steam\\steamapps\\common\\Fallout 4\\Data\\" + fileName);
					}

					mf.getDiffuseTexture() = textureSet->textures.at(0).get();
					mf.getNormalTexture() = textureSet->textures.at(1).get();
					mf.getSmoothSpecTexture() = textureSet->textures.at(2).get();
					mf.getGreyscaleTexture() = textureSet->textures.at(3).get();
					mf.getEnvmapTexture() = textureSet->textures.at(4).get();
					mf.getGlowTexture() = textureSet->textures.at(5).get();
					//mf.getInnerLayerTexture() = textureSet->textures.at(6).get();
					//mf.getWrinklesTexture() = textureSet->textures.at(7).get();
					//mf.getDisplacementTexture() = textureSet->textures.at(8).get();


					if (alpha) {
						bool alphaBlend = alpha->flags & 1;
						if (alphaBlend) {
							mf.getDecald() = true;
						}

						bool alphaTest = alpha->flags & (1 << 9);
						if (alphaTest) {
							mf.getAphaTestRef() = alpha->threshold;
							mf.getAlphaTest() = true;
						}
					}


					if ((shader->shaderFlags2) & (1 << 4))  { //set double sided
						mf.getTwoSided() = true;
					}



					//mf.save(fileName);
					mf.save("C:\\Games\\Steam\\steamapps\\common\\Fallout 4\\Data\\" + fileName);

					if (shader->nameRef >=0) {
						file.strings[shader->nameRef].set(fileName);
					} else {
						shader->nameRef = file.addString(fileName);
					}

				}


			}

		}
	}

}
*/





/*





	if (auto alphaController = dynamic_cast<nif::fo3::NiAlphaController*>(file.blocks[controllerRef].get())) {

		if (alphaController->nextControllerRef >= 0) {
			convert_controller(file,  alphaController->nextControllerRef, targetRef);
		}

		std::unique_ptr<nif::fo3::BSEffectShaderPropertyFloatController> bsEffectShaderPropertyFloatController = std::make_unique<nif::fo3::BSEffectShaderPropertyFloatController>();

		bsEffectShaderPropertyFloatController->nextControllerRef = alphaController->nextControllerRef;
		bsEffectShaderPropertyFloatController->flags = alphaController->flags;
		bsEffectShaderPropertyFloatController->frequency = alphaController->frequency;
		bsEffectShaderPropertyFloatController->phase = alphaController->phase;
		bsEffectShaderPropertyFloatController->startTime =alphaController->startTime;
		bsEffectShaderPropertyFloatController->stopTime = alphaController->stopTime;
		bsEffectShaderPropertyFloatController->targetRef = targetRef;
		bsEffectShaderPropertyFloatController->interpolatorRef = alphaController->interpolatorRef;
		bsEffectShaderPropertyFloatController->typeOfControlledVariable = 5;

		file.blocks[controllerRef] = std::move(bsEffectShaderPropertyFloatController);



	} else if (auto textureTransformController = dynamic_cast<nif::fo3::NiTextureTransformController*>(file.blocks[controllerRef].get())) {

		if (textureTransformController->nextControllerRef >= 0) {
			convert_controller(file,  textureTransformController->nextControllerRef, targetRef);
		}

		std::unique_ptr<nif::fo3::BSEffectShaderPropertyFloatController> bsEffectShaderPropertyFloatController = std::make_unique<nif::fo3::BSEffectShaderPropertyFloatController>();

		bsEffectShaderPropertyFloatController->nextControllerRef = textureTransformController->nextControllerRef;
		bsEffectShaderPropertyFloatController->flags = textureTransformController->flags;
		bsEffectShaderPropertyFloatController->frequency = textureTransformController->frequency;
		bsEffectShaderPropertyFloatController->phase = textureTransformController->phase;
		bsEffectShaderPropertyFloatController->startTime =textureTransformController->startTime;
		bsEffectShaderPropertyFloatController->stopTime = textureTransformController->stopTime;
		bsEffectShaderPropertyFloatController->targetRef = targetRef;
		bsEffectShaderPropertyFloatController->interpolatorRef = textureTransformController->interpolatorRef;

		if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_TRANSLATE_U) {
			bsEffectShaderPropertyFloatController->typeOfControlledVariable = 6;
		} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_TRANSLATE_V) {
			bsEffectShaderPropertyFloatController->typeOfControlledVariable = 8;
		} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_SCALE_U) {
			bsEffectShaderPropertyFloatController->typeOfControlledVariable = 7;
		} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_SCALE_V) {
			bsEffectShaderPropertyFloatController->typeOfControlledVariable = 9;
		} else if (textureTransformController->operation == nif::fo3::NiTextureTransformController::TransformType::TT_ROTATE) {
			bsEffectShaderPropertyFloatController->typeOfControlledVariable = 0;
		}

		file.blocks[controllerRef] = std::move(bsEffectShaderPropertyFloatController);

	} else if (auto materialColorController = dynamic_cast<nif::fo3::NiMaterialColorController*>(file.blocks[controllerRef].get())) {

		if (materialColorController->nextControllerRef >= 0) {
			convert_controller(file,  materialColorController->nextControllerRef, targetRef);
		}

		std::unique_ptr<nif::fo3::BSLightingShaderPropertyColorController> lightingShaderPropertyColorController = std::make_unique<nif::fo3::BSLightingShaderPropertyColorController>();

		lightingShaderPropertyColorController->nextControllerRef = materialColorController->nextControllerRef;
		lightingShaderPropertyColorController->flags = materialColorController->flags;
		lightingShaderPropertyColorController->frequency = materialColorController->frequency;
		lightingShaderPropertyColorController->phase = materialColorController->phase;
		lightingShaderPropertyColorController->startTime =materialColorController->startTime;
		lightingShaderPropertyColorController->stopTime = materialColorController->stopTime;
		lightingShaderPropertyColorController->targetRef = targetRef;
		lightingShaderPropertyColorController->interpolatorRef = materialColorController->interpolatorRef;
		lightingShaderPropertyColorController->typeOfControlledColor = 0;

		file.blocks[controllerRef] = std::move(lightingShaderPropertyColorController);

	}*/
