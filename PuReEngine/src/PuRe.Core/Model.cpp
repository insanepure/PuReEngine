#define _CRT_SECURE_NO_WARNINGS
#include "include/PuReEngine/Model.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fbxsdk.h>

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        CModel::CModel(IGraphics* a_pGraphics, std::string a_Path) : m_pGraphics(a_pGraphics), m_ppMeshes(NULL), m_Meshcount(0)
        {
            this->m_Path = a_Path;
            //Clear our bounding box
            int stride = sizeof(SVertex);
            this->m_pBoundingVertices = this->m_pGraphics->CreateVertexBuffer(stride * 36, stride); //9 Floats (3 Position, 2 UV,4 Color) * 36 Vertices
            this->m_BoundingBox = CBoundingBox();

            //Create our local Scene
            this->m_pScene = new SScene();
            //Set Threadsafe Variables
            this->m_Ready = false;
            this->m_Loaded = false;
            //Load a Box as start
            int32 size = 36;
            SVertex* pData = new SVertex[size];
            Box::GetVertices(pData);
            //Set Mesh
            this->m_Meshcount = 1;
            this->m_ppMeshes = new CMesh*[1];
            this->m_ppMeshes[0] = new CMesh();
            this->m_ppMeshes[0]->SetGraphic(this->m_pGraphics);
            this->m_ppMeshes[0]->SetVertexBuffer(pData, size);
            this->m_ppMeshes[0]->SetTexture("");
            //Delete Box
            SAFE_DELETE(pData);

            if (a_Path.substr(a_Path.find_last_of(".") + 1) == "FBX")
            {
                this->m_LoadThread = std::thread(&CModel::LoadFBX, this);
            }
            else
            {
                this->m_LoadThread = std::thread(&CModel::LoadAssimp, this);
                //if (this->m_LoadThread.joinable())
                //    this->m_LoadThread.join();
                //this->LoadAssimp(a_pPath);
            }

        }

        // **************************************************************************
        // **************************************************************************

        CModel::~CModel()
        {
            this->JoinThread();
            SAFE_DELETE(this->m_pBoundingVertices);
            for (int32 i = 0; i < this->m_Meshcount; i++)
                SAFE_DELETE(this->m_ppMeshes[i]);
            SAFE_DELETE_ARRAY(this->m_ppMeshes);
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::LoadFBX()
        {
            //create fbx sdk manager
            FbxManager* g_pFbxSdkManager = FbxManager::Create();

            //set manager settings
            FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT);
            g_pFbxSdkManager->SetIOSettings(pIOsettings);

            //create fbx importer and scene
            FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager, "");
            FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager, "");

            //initialize the importer
            bool bSuccess = pImporter->Initialize(this->m_Path.c_str(), -1, g_pFbxSdkManager->GetIOSettings());
            if (!bSuccess)
            {
                printf("There was an error importing the fbx!\n");
            }

            //import the scene
            bSuccess = pImporter->Import(pFbxScene);
            if (!bSuccess)
            {
                printf("There was an error importing the fbx!\n");
            }

            //delete the importer
            pImporter->Destroy();

            //read the scene
            FbxAxisSystem SceneAxisSystem = pFbxScene->GetGlobalSettings().GetAxisSystem();

            //convert right handed to left handed
            int upSign = 0;
            bool bLeftHanded = SceneAxisSystem.GetCoorSystem() == FbxAxisSystem::eLeftHanded;
            float32 fSign = upSign < 0 ? -1.0f : 1.0f;
            float32 zScale = bLeftHanded ? -1.0f : 1.0f;

            Matrix<float32> LeftHandedX = Matrix<float32>(0, fSign, 0, 0, -fSign, 0, 0, 0, 0, 0, zScale, 0, 0, 0, 0, 1);
            Matrix<float32> LeftHandedY = Matrix<float32>(1, 0, 0, 0, 0, fSign, 0, 0, 0, 0, fSign*zScale, 0, 0, 0, 0, 1);
            Matrix<float32> LeftHandedZ = Matrix<float32>(1, 0, 0, 0, 0, 0, -fSign*zScale, 0, 0, fSign, 0, 0, 0, 0, 0, 1);

            FbxNode* pFbxRootNode = pFbxScene->GetRootNode();

            if (pFbxRootNode)
            {
                //create vertex array
                this->m_pScene->ppTexturePath = new std::string[pFbxRootNode->GetChildCount()];
                this->m_pScene->pVertexCount = new int32[pFbxRootNode->GetChildCount()];
                this->m_pScene->ppVertexArray = new SVertex*[pFbxRootNode->GetChildCount()];
                this->m_pScene->MeshCount = pFbxRootNode->GetChildCount();

                //go through each mesh
                for (int32 i = 0; i < pFbxRootNode->GetChildCount(); i++)
                {

                    //Error handling, only handle meshes
                    FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);
                    if (pFbxChildNode->GetNodeAttribute() == NULL)
                        continue;
                    FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();
                    if (AttributeType != FbxNodeAttribute::eMesh)
                        continue;

                    //Get the Mesh
                    FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

                    //calculate size
                    int32 PolygonCount = pMesh->GetPolygonCount();
                    this->m_pScene->pVertexCount[i] = PolygonCount * 3;
                    this->m_pScene->ppVertexArray[i] = new SVertex[this->m_pScene->pVertexCount[i]];

                    //Get the Vertices
                    FbxVector4* pVertices = pMesh->GetControlPoints();
                    //Get the UV
                    FbxLayerElementUV* fbxLayerUV = pMesh->GetLayer(0)->GetUVs();
                    //Get the Normals
                    FbxGeometryElementNormal* vertexNormal = pMesh->GetElementNormal(0);
                    //Go through the model
                    for (int32 j = 0; j < PolygonCount; j++)
                    {
                        int32 iNumVertices = pMesh->GetPolygonSize(j);
                        assert(iNumVertices == 3);
                        //go through each triangle
                        for (int32 k = 0; k < iNumVertices; k++)
                        {
                            SVertex vertex;
                            //set Position
                            int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

                            vertex.Position[0] = (float32)pVertices[iControlPointIndex].mData[0];
                            vertex.Position[1] = (float32)pVertices[iControlPointIndex].mData[1];
                            vertex.Position[2] = (float32)pVertices[iControlPointIndex].mData[2];
                            vertex.Position = vertex.Position * LeftHandedX * LeftHandedY * LeftHandedZ;

                            //set UV
                            int fbxUVIndex = pMesh->GetTextureUVIndex(j, k);

                            vertex.UV[0] = (float32)fbxLayerUV->GetDirectArray().GetAt(fbxUVIndex).mData[0];
                            vertex.UV[1] = (float32)fbxLayerUV->GetDirectArray().GetAt(fbxUVIndex).mData[1];
                            // flipped y axis for left handed
                            vertex.UV[1] = 1.0f - vertex.UV[1];

                            //set Normal
                            vertex.Normal[0] = static_cast<float32>(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[0]);
                            vertex.Normal[1] = static_cast<float32>(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[1]);
                            vertex.Normal[2] = static_cast<float32>(vertexNormal->GetDirectArray().GetAt(iControlPointIndex).mData[2]);

                            //insert into array
                            int32 index = (j * 3) + k;
                            this->m_pScene->ppVertexArray[i][index] = vertex;
                        }
                    }

                    //Get Texture
                    int32 mc = pFbxChildNode->GetMaterialCount();

                    std::string file;
                    for (int index = 0; index < mc; index++)
                    {
                        FbxSurfaceMaterial* material = pFbxChildNode->GetMaterial(index);

                        if (material != NULL)
                        {
                            // This only gets the material of type sDiffuse, you probably need to traverse all Standard Material Property by its name to get all possible textures.
                            FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

                            // Check if it's layeredtextures
                            int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

                            if (layeredTextureCount > 0)
                            {
                                for (int j = 0; j < layeredTextureCount; j++)
                                {
                                    FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
                                    int lcount = layered_texture->GetSrcObjectCount<FbxTexture>();

                                    for (int k = 0; k < lcount; k++)
                                    {
                                        FbxTexture* texture = FbxCast<FbxTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
                                        // Then, you can get all the properties of the texture, include its name
                                        file = texture->GetName();
                                    }
                                }
                            }
                            else
                            {
                                // Directly get textures
                                int textureCount = prop.GetSrcObjectCount<FbxTexture>();
                                for (int j = 0; j < textureCount; j++)
                                {
                                    FbxFileTexture * texture = FbxCast<FbxFileTexture >(prop.GetSrcObject<FbxTexture>(j));
                                    file = texture->GetRelativeFileName();
                                }
                            }
                        }
                    }

                    //Geht es auch ohne das??
                    if (file.length() > 1)
                    {
                        std::string finalpath = this->m_Path.substr(0, this->m_Path.find_last_of("/"));

                        finalpath = finalpath + "/" + file;
                        size_t start_pos = 0;
                        while ((start_pos = finalpath.find("\\", start_pos)) != std::string::npos) {
                            finalpath.replace(start_pos, 1, "/");
                            start_pos += 1;
                        }

                        this->m_pScene->ppTexturePath[i] = finalpath;
                    }
                    else
                        this->m_pScene->ppTexturePath[i] = "";

                }
                this->m_Loaded = true;

            }
            else
                printf("File %s not found!\n", this->m_Path.c_str());
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::LoadAssimp()
        {
            // Create an instance of the Importer class
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(this->m_Path.c_str(), aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);
            if (scene != NULL)
            {
                std::string text;
                //create vertex array
                this->m_pScene->ppTexturePath = new std::string[scene->mNumMeshes];
                this->m_pScene->pVertexCount = new int32[scene->mNumMeshes];
                this->m_pScene->ppVertexArray = new SVertex*[scene->mNumMeshes];
                this->m_pScene->MeshCount = scene->mNumMeshes;

                //go through each mesh and load it
                for (uint32 m = 0; m < scene->mNumMeshes; m++)
                {
                    aiMesh *mesh = scene->mMeshes[m];
                    //Set VertexArray for this Mesh
                    this->m_pScene->pVertexCount[m] = mesh->mNumFaces*3;
                    this->m_pScene->ppVertexArray[m] = new SVertex[this->m_pScene->pVertexCount[m]];
                    //Fill VertexArray
                    for (uint32 i = 0; i < mesh->mNumFaces; i++)
                    {
                        const aiFace& face = mesh->mFaces[i];
                        for (uint32 j = 0; j < face.mNumIndices; j++)
                        {
                            SVertex vertex;
                            if (mesh->HasTextureCoords(0) != NULL)
                            {
                                aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
                                vertex.UV.X = uv.x;
                                vertex.UV.Y = uv.y;
                            }
                            else
                            {
                                vertex.UV.X = 0.0f;
                                vertex.UV.Y = 0.0f;
                            }

                            if (mesh->HasNormals() != NULL)
                            {
                                aiVector3D normal = mesh->mNormals[face.mIndices[j]];
                                vertex.Normal.X = normal.x;
                                vertex.Normal.Y = normal.y;
                                vertex.Normal.Z = normal.z;
                                //Do normal here
                            }

                            if (mesh->HasVertexColors(0) != NULL)
                            {
                                aiColor4D color = mesh->mColors[0][face.mIndices[j]];
                                vertex.Color.X = color.r;
                                vertex.Color.Y = color.g;
                                vertex.Color.Z = color.b;
                            }
                            else
                            {
                                vertex.Color.X = 1.0f;
                                vertex.Color.Y = 0.0f;
                                vertex.Color.Z = 0.0f;
                            }

                            aiVector3D pos = mesh->mVertices[face.mIndices[j]];

                            vertex.Position.X = pos.x;
                            vertex.Position.Y = pos.y;
                            vertex.Position.Z = pos.z;

                            int32 index = (i * 3) + j;
                            this->m_pScene->ppVertexArray[m][index] = vertex;

                            //Calculate the bounding box based on the vertices

                            //Min
                            if (vertex.Position.X < this->m_BoundingBox.m_Position.X)
                                this->m_BoundingBox.m_Position.X = vertex.Position.X;
                            if (vertex.Position.Y < this->m_BoundingBox.m_Position.Y)
                                this->m_BoundingBox.m_Position.Y = vertex.Position.Y;
                            if (vertex.Position.Z < this->m_BoundingBox.m_Position.Z)
                                this->m_BoundingBox.m_Position.Z = vertex.Position.Z;
                            //Max
                            if (vertex.Position.X > this->m_BoundingBox.m_Size.X)
                                this->m_BoundingBox.m_Size.X = vertex.Position.X;
                            if (vertex.Position.Y > this->m_BoundingBox.m_Size.Y)
                                this->m_BoundingBox.m_Size.Y = vertex.Position.Y;
                            if (vertex.Position.Z > this->m_BoundingBox.m_Size.Z)
                                this->m_BoundingBox.m_Size.Z = vertex.Position.Z;


                            //text += "a_pVertex[count].Position = Vector3<float32>("+std::to_string(vertex.Position.X)+","+std::to_string(vertex.Position.Y)+","+std::to_string(vertex.Position.Z)+");\r\n";
                            //text += "a_pVertex[count].Color = Vector3<float32>(" + std::to_string(vertex.Color.X) + "," + std::to_string(vertex.Color.Y) + "," + std::to_string(vertex.Color.Z) + ");\r\n";
                            //text += "a_pVertex[count].UV = Vector2<float32>(" + std::to_string(vertex.UV.X) + "," + std::to_string(vertex.UV.Y) + ");\r\n";
                            //text += "a_pVertex[count].Normal = Vector3<float32>(" + std::to_string(vertex.Normal.X) + "," + std::to_string(vertex.Normal.Y) + "," + std::to_string(vertex.Normal.Z) + ");\r\n";
                            //text += "count++;\r\n";

                        }
                    }

                    //Get Diffuse Path
                    aiString texturepath;
                    int texIndex = 0;
                    scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, texIndex, &texturepath);

                    //Geht es auch ohne das??
                    if (strlen(texturepath.data) != 0)
                    {
                        std::string finalpath = this->m_Path.substr(0, this->m_Path.find_last_of("/"));

                        finalpath = finalpath + "/" + texturepath.data;
                        size_t start_pos = 0;
                        while ((start_pos = finalpath.find("\\", start_pos)) != std::string::npos) {
                            finalpath.replace(start_pos, 1, "/");
                            start_pos += 1;
                        }
                        this->m_pScene->ppTexturePath[m] = finalpath;
                    }
                    else
                        this->m_pScene->ppTexturePath[m] = "";

                }
                //Calculate Boundings
                //this->CalculateBounding();
                //free scene
                importer.FreeScene();
                this->m_Loaded = true;
            }
            else
                printf("File %s not found!\n", this->m_Path.c_str());
        }
        // **************************************************************************
        // **************************************************************************
        void CModel::JoinThread()
        {
            if (this->m_LoadThread.joinable())
                this->m_LoadThread.join();
        }
        // **************************************************************************
        // **************************************************************************

        IVertexBuffer* CModel::GetVertices(int32 a_Mesh)
        {
            this->Update();
            if (a_Mesh < this->m_Meshcount)
                return this->m_ppMeshes[a_Mesh]->GetVertices();
            return nullptr;
        }
        // **************************************************************************
        // **************************************************************************

        int CModel::GetMeshes()
        {
            this->Update();
            return this->m_Meshcount;
        }

        // **************************************************************************
        // **************************************************************************

        ITexture2D* CModel::GetTexture(int32 a_Mesh)
        {
            this->Update();
            if (a_Mesh < this->m_Meshcount)
                return this->m_ppMeshes[a_Mesh]->GetTexture();
            return nullptr;
        }

        // **************************************************************************
        // **************************************************************************

        CBoundingBox CModel::GetBoundingBox()
        {
            return this->m_BoundingBox;
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::CalculateBounding()
        {
            int32 count = 0;
            SVertex* pdata = (SVertex*)this->m_pBoundingVertices->Lock();
            /* TRIANGLE 1 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.999110f, 0.498923f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            /* TRIANGLE 2 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.999455f, 0.249620f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.999110f, 0.498923f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            /* TRIANGLE 3 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.001085f, 0.249620f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.249682f, 0.250323f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            /* TRIANGLE 4 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.001517f, 0.500006f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.001085f, 0.249620f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            /* TRIANGLE 5 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            /* TRIANGLE 6 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.249682f, 0.250323f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000001f, 0.000000f, -1.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            /* TRIANGLE 7 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            /* TRIANGLE 8 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, 0.000000f, -0.000001f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            /* TRIANGLE 9 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748355f, 0.001770f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            /* TRIANGLE 10 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.500193f, 0.001272f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Size.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748355f, 0.001770f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            /* TRIANGLE 11 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.498993f, 0.749585f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            /* TRIANGLE 12 */
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.748953f, 0.749080f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Position.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Position.Z);
            pdata[count].UV = Vector2<float32>(0.498993f, 0.749585f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            pdata[count].Position = Vector3<float32>(this->m_BoundingBox.m_Size.X, this->m_BoundingBox.m_Position.Y, this->m_BoundingBox.m_Size.Z);
            pdata[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            pdata[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            pdata[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            //unlock it
            this->m_pBoundingVertices->Unlock();
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::Update()
        {
            if (!this->m_Ready&&this->m_Loaded)
            {
                //Delete Box
                SAFE_DELETE(this->m_ppMeshes[0]);
                SAFE_DELETE_ARRAY(this->m_ppMeshes);
                this->m_Meshcount = this->m_pScene->MeshCount;

                this->m_ppMeshes = new CMesh*[this->m_Meshcount];
                for (int32 m = 0; m < this->m_Meshcount; m++)
                {
                    this->m_ppMeshes[m] = new CMesh();
                    this->m_ppMeshes[m]->SetGraphic(this->m_pGraphics);
                    this->m_ppMeshes[m]->SetVertexBuffer(this->m_pScene->ppVertexArray[m], this->m_pScene->pVertexCount[m]);
                    this->m_ppMeshes[m]->SetTexture(this->m_pScene->ppTexturePath[m].c_str());
                    SAFE_DELETE(this->m_pScene->ppVertexArray[m]);
                }
                SAFE_DELETE(this->m_pScene->pVertexCount);
                SAFE_DELETE(this->m_pScene);
                this->m_Ready = true;
            }
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::DrawInstanced(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, IInstanceBuffer* a_pInstanceBuffer)
        {
            this->Update();
            for (int32 i = 0; i < this->m_Meshcount; i++)
                this->m_ppMeshes[i]->DrawInstanced(a_pCam, a_pMaterial, a_Primitive, a_pInstanceBuffer);

            //if (this->m_Ready)
            //{
            //    this->m_pMaterial->Apply();
            //    a_pCam->Apply(this->m_pMaterial);
            //    this->m_pGraphics->SetInstanceBuffer(this->m_pBoundingVertices, a_pInstanceBuffer);
            //    this->m_pMaterial->Apply();
            //    this->m_pGraphics->DrawInstanced(EPrimitive::Lines, this->m_pBoundingVertices->GetSize(), a_pInstanceBuffer->GetSize());
            //}
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Vector3<float32> a_Size, Vector3<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            this->Update();
            for (int32 i = 0; i < this->m_Meshcount; i++)
                this->m_ppMeshes[i]->Draw(a_pCam, a_pMaterial, a_Primitive, a_Position, a_Size, a_Rotation, a_Center,a_Color);
        }

        // **************************************************************************
        // **************************************************************************

        void CModel::Draw(CCamera* a_pCam, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Vector3<float32> a_Size, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Color a_Color)
        {
            this->Update();
            for (int32 i = 0; i < this->m_Meshcount; i++)
                this->m_ppMeshes[i]->Draw(a_pCam, a_pMaterial, a_Primitive, a_Position, a_Size, a_Rotation, a_Center,a_Color);
        }

    }
}