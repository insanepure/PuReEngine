#ifndef _RENDERER_H_
#define _RENDERER_H_

// Engine specific includes
#include "Defines.h"
#include "Sprite.h"
#include "Model.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ITexture2D.h"
#include "IRendertarget.h"
#include "Camera.h"
#include "Color.h"
#include "Font.h"
#include "SkyBox.h"
#include "ParticleEmitter.h"
#include <list>


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {
        /// @brief Saved Instances
        ///
        struct SRenderInstance
        {
            Vector3<float32> Position;
            Matrix<float32> Rotation;
            Vector3<float32> Center;
            Vector3<float32> Size;
            Color Color;
        };
        struct SCall
        {
            std::function<void()> calledFunction;
            int32 RenderIndex;
        };
        struct Target
        {
            /// @brief Calls when Set is used
            ///
            std::list<SCall> m_SetCalls;
            /// @brief Calls when rendering the Skybox
            ///
            std::list<SCall> m_SkyBoxCalls;
            /// @brief Our saved Geometry Calls
            ///
            std::list<SCall> m_GeometryCalls;
            /// @brief Our saved Alpha Calls
            ///
            std::list<SCall> m_AlphaCalls;
            /// @brief Our saved Light Calls
            ///
            std::list<SCall> m_LightCalls;
            /// @brief Our active Call used for passing Material Informations
            ///
            std::list<SCall>* m_pActiveCall;
            /// @brief Our Position used to pass Material Information before Drawing
            ///
            std::list<SCall>::iterator m_CallPosition;
            /// @brief Rendertarget to draw to
            ///
            IRendertarget* m_pRenderTarget;
            /// @brief Post Screen Camera
            ///
            CCamera* m_pPostCamera;
            /// @brief Position for the texture in the material, saved temporarily
            ///
            int32 m_TexturePosition;
            /// @brief Noise Texture for SSAO
            ///
            CSprite* m_pNoiseTexture;
            /// @brief SSAO Material
            ///
            IMaterial* m_pSSAOMaterial;
        };
        /// @brief Class for Rendering
        ///
        class CRenderer
        {
        private:
            /// @brief Final Rendertarget
            ///
            IRendertarget* m_pFinalRendertarget;
            /// @brief Active Rendertarget
            ///
            IRendertarget* m_pActiveRenderTarget;
            /// @brief Rendertargets we use
            ///
            std::vector<Target*> m_Targets;
            /// @brief Camera we use, saved temporarily
            ///
            CCamera* m_pActivePostCamera;
            /// @brief Camera we use, saved temporarily
            ///
            CCamera* m_pActiveCamera;
            /// @brief Material we use, saved temporarily
            ///
            IMaterial* m_pActiveMaterial;
            /// @brief Graphics Object
            ///
            IGraphics* m_pGraphics;
            /// @brief Quad
            ///
            Quad* m_pQuad;

        public:
            /// @brief Constructor
            ///
            /// @param Graphic Object
            ///
            CRenderer(IGraphics* a_pGraphics);
            /// @brief Destructor
            ///
            ~CRenderer();

        public:
            ///////////// FUNCTIONS THAT ARE CALLED ANYTIME AND SORTED /////////////

            /// @brief Returns the Result of the Renderer
            ///
            /// @returns the Texture Object
            ///
            ITexture2D* GetResult();

            /// @brief Returns the Texture of a Rendertarget
            ///
            /// @param Target where we get the Texture from
            /// @param Texture we need
            ///
            /// @returns the Texture Object
            ///
            ITexture2D* GetTexture(uint32 a_Target, uint32 a_Texture);
            /// @brief Adds a Rendertarget
            ///
            /// @param Size of the Target
            ///
            void AddTarget(Vector2<int32> a_Size);

            /// @brief Delete all Targets
            ///
            /// @remarks no delete one target because order changes when deleting
            ///
            void DeleteTargets();

            /// @brief Used SSAO Material
            ///
            /// @param Index of the Target
            /// @param Material for SSAO
            /// @param Noise Texture
            ///
            void SetSSAO(uint32 a_Index, IMaterial* a_pMaterial, CSprite* a_pNoisePath);
            /// @brief Save the Emitter and render him later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Particle Emitter Object
            /// @param Material for this Emitter
            /// @param Model to be emitted
            ///
            void Draw(uint32 a_Index, bool a_Cull, CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CModel* a_pModel, EPrimitive a_Primitive,int32 a_RenderIndex=-1,float a_Fade=0.0f);
            /// @brief Save the Emitter and render him later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Particle Emitter Object
            /// @param Material for this Emitter
            /// @param Sprite to be emitted
            ///
            void Draw(uint32 a_Index, bool a_Cull, CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CSprite* a_pSprite, int32 a_RenderIndex = -1, float a_Fade = 0.0f);
            /// @brief Save the Font and It's arguments in the array to rende
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Font Object
            /// @param Text to display
            /// @param Material for this Font
            /// @param Position for this Font
            /// @param Rotation for this Font
            /// @param Size for this Font
            /// @param Offset for each Character
            ///
            void Draw(uint32 a_Index,bool a_Cull,CFont* a_pFont, IMaterial* a_pMaterial,
                std::string a_pText,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                float32 Offset = 1.0f,
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );

            /// @brief Save the Font and It's arguments in the array to render
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Font Object
            /// @param Text to display
            /// @param Material for this Font
            /// @param Position for this Font
            /// @param Rotation for this Font
            /// @param Size for this Font
            /// @param Offset for each Character
            ///
            void Draw(uint32 a_Index, bool a_Cull, CFont* a_pFont, IMaterial* a_pMaterial,
                std::string a_pText,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                float32 Offset = 1.0f,
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );

            /// @brief Save the Sprites and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Sprite Object
            /// @param Material for this Sprite
            /// @param Position for this Sprite
            /// @param Rotation for this Sprite
            /// @param Center for this Sprite
            /// @param Size for this Sprite
            /// @param Color for this Sprite
            ///
            void Draw(uint32 a_Index, bool a_Cull, CSprite* a_pSprite, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f),
                Vector2<float32> a_UVSize = Vector2<float32>(),
                Vector2<float32> a_UVPosition = Vector2<float32>(), int32 a_RenderIndex = -1
                );

            /// @brief Save the Sprites and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Sprite Object
            /// @param Material for this Sprite
            /// @param Position for this Sprite
            /// @param Rotation for this Sprite
            /// @param Center for this Sprite
            /// @param Size for this Sprite
            /// @param Color for this Sprite
            ///
            void Draw(uint32 a_Index, bool a_Cull, CSprite* a_pSprite, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f),
                Vector2<float32> a_UVSize = Vector2<float32>(),
                Vector2<float32> a_UVPosition = Vector2<float32>(), int32 a_RenderIndex = -1
                );

            /// @brief Save the Model and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Model Object
            /// @param Primitive
            /// @param Material for this Model
            /// @param Position for this Model
            /// @param Rotation for this Model
            /// @param Center for this Model
            /// @param Size for this Model
            /// @param Color for this Model
            ///
            void Draw(uint32 a_Index, bool a_Cull, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );

            /// @brief Save the Model and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Model Object
            /// @param Primitive
            /// @param Material for this Model
            /// @param Position for this Model
            /// @param Rotation for this Model
            /// @param Center for this Model
            /// @param Size for this Model
            /// @param Color for this Model
            ///
            void Draw(uint32 a_Index, bool a_Cull, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );

            /// @brief Save the VertexBuffer and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param VertexBuffer Object
            /// @param Primitive
            /// @param Material for this VertexBuffer
            /// @param Position for this VertexBuffer
            /// @param Rotation for this VertexBuffer
            /// @param Center for this VertexBuffer
            /// @param Size for this VertexBuffer
            /// @param Color for this VertexBuffer
            ///
            void Draw(uint32 a_Index, bool a_Cull, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );

            /// @brief Save the VertexBuffer and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param VertexBuffer Object
            /// @param Primitive
            /// @param Material for this VertexBuffer
            /// @param Position for this VertexBuffer
            /// @param Rotation for this VertexBuffer
            /// @param Center for this VertexBuffer
            /// @param Size for this VertexBuffer
            /// @param Color for this VertexBuffer
            ///
            void Draw(uint32 a_Index, bool a_Cull, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial,
                Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Matrix<float32> a_Rotation = Matrix<float32>(),
                Vector3<float32> a_Center = Vector3<float32>(0.0f, 0.0f, 0.0f),
                Vector3<float32> a_Size = Vector3<float32>(1.0f, 1.0f, 1.0f),
                Color a_Color = Color(1.0f, 1.0f, 1.0f, 1.0f), int32 a_RenderIndex = -1
                );
            /// @brief Save the Skybox and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Skybox Object
            /// @param Material for this Model
            /// @param Rotation for this Model
            ///
            void Draw(uint32 a_Index, bool a_Cull, CSkyBox* a_pSkyBox, IMaterial* a_pMaterial, Vector3<float32> a_Rotation = Vector3<float32>(0.0f, 0.0f, 0.0f), int32 a_RenderIndex = -1);
            /// @brief Save the Model and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param Model Object
            /// @param Primitive
            /// @param Material for this Model
            /// @param Instances to render
            /// @param Amount of Instances to Render
            ///
            void Draw(uint32 a_Index, bool a_Cull, CModel* a_pModel, EPrimitive a_Primitive, IMaterial* a_pMaterial, SRenderInstance* a_pInstances, int32 a_Instances, int32 a_RenderIndex = -1);
            /// @brief Save the VertexBuffer and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param VertexBuffer Object
            /// @param VertexBuffer Count
            /// @param Primitive
            /// @param Material for this Model
            /// @param Instances to render
            /// @param Amount of Instances to Render
            ///
            void Draw(uint32 a_Index, bool a_Cull, IVertexBuffer* a_pBuffer, int32 a_VertexCount, EPrimitive a_Primitive, IMaterial* a_pMaterial, SRenderInstance* a_pInstances, int32 a_Instances, int32 a_RenderIndex = -1);


            /// @brief Save the PointLight and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param PointLight Object
            /// @param Material for this Light
            /// @param Position for this Light
            /// @param Color for this Light
            /// @param Constant Attenuation for this Light
            /// @param Exponential Attenuation for this Light
            /// @param Linear Attenuation for this Light
            ///
            void Draw(uint32 a_Index, bool a_Cull, CPointLight* a_pPointLight, IMaterial* a_pMaterial, Vector3<float32> a_Position = Vector3<float32>(0.0f, 0.0f, 0.0f), Color a_Color = Color(1.0f, 0.0f, 0.0f, 1.0f), float32 a_Radius = 1.0f, float32 a_Intensity = 1.0f, int32 a_RenderIndex = -1);
            /// @brief Save the DirectionalLight and It's arguments in the array to render later
            ///
            /// @param Index of the Target
            /// @param Whether it should be culln or not
            /// @param DirectionalLight Object
            /// @param Material for this Light
            /// @param Direction for this Light
            /// @param Color for this Light
            ///
            void Draw(uint32 a_Index, bool a_Cull, CDirectionalLight* a_pDirectionalLight, IMaterial* a_pMaterial, Vector3<float32> a_Direction = Vector3<float32>(0.0f, 0.0f, 0.0f), Color a_Color = Color(1.0f, 0.0f, 0.0f, 1.0f), int32 a_RenderIndex = -1);

            /// @brief Defines whether culling should be turned on or off
            ///
            /// @param Index of the Target
            /// @param True for on, False for off
            /// @param Name within the shader
            ///
            void SetCulling(uint32 a_Index, bool a_Culling, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param float as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, float32 a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Vector2 as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, Vector2<float32> a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Vector3 as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, Vector3<float32> a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Vector4 as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, Vector4<float32> a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Color as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, Color a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Matrix as Value
            /// @param Name within the shader
            ///
            void Set(uint32 a_Index, Matrix<float32> a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param Texture2D as Value
            /// @param Name within the shader
            ///
            void SetTexture(uint32 a_Index, ITexture2D* a_Value, const char8* a_pName, int32 a_RenderIndex = -1);
            /// @brief Set the Value to pass it into a Shader
            ///
            /// @param Index of the Target
            /// @param CubeMap as Value
            /// @param Name within the shader
            ///
            void SetCubeMap(uint32 a_Index, ITexture2D* a_Value, const char8* a_pName, int32 a_RenderIndex = -1);


            /// @brief Render from a specific Camera
            ///
            /// @param Index of the Render
            /// @param Index of the Target
            /// @param Camera to render from
            /// @param Camera to render the Quad with
            /// @param PostMaterial used to combine everything
            /// @param Final Material only for rendering a quad with texture
            /// @param Position where the rendertarget will be at
            ///
            void Render(int32 a_Index, uint32 a_Target, CCamera* a_pCamera, IMaterial* a_pPostMaterial, IMaterial* a_pFinalMaterial, Vector3<float32> a_Position = Vector3<float32>());

            /// @brief Start Rendering
            ///
            void Begin(Color a_ClearColor);

            /// @brief End Rendering
            ///
            void End();
        private:

            /// @brief Add the Function and it's arguments to the Array
            ///
            /// @param Vector where it should be saved in
            /// @param Position where it should be saved in
            /// @param Function to save
            /// @param Arguments to save
            ///
            template<typename Calls, typename... Arguments>
            std::list<SCall>::iterator AddFunction(int32 a_RenderIndex,std::list<SCall>* a_pFunctions, std::list<SCall>::iterator a_Position, Calls&& a_rrFunction, Arguments&&... a_rrArgument);

            ///////////// FUNCTIONS THAT ARE CALLED WHEN RENDERED /////////////

            /// @brief Material to use from now on
            ///
            /// @param Material Object
            ///
            void ApplyMaterial(IMaterial* a_pMaterial);

            /// @brief Use this Float 
            ///
            /// @brief Material to use
            /// @param float as Value
            /// @param Name within the shader
            ///
            void UseFloat(IMaterial* a_pMaterial, float32 a_Value, const char8* a_pName);
            /// @brief Use this Vector2 
            ///
            /// @brief Material to use
            /// @param Vector2 as Value
            /// @param Name within the shader
            ///
            void UseVector2(IMaterial* a_pMaterial, Vector2<float32> a_Value, const char8* a_pName);
            /// @brief Use this Vector3 
            ///
            /// @brief Material to use
            /// @param Vector3 as Value
            /// @param Name within the shader
            ///
            void UseVector3(IMaterial* a_pMaterial, Vector3<float32> a_Value, const char8* a_pName);
            /// @brief Use this Vector4 
            ///
            /// @brief Material to use
            /// @param Vector4 as Value
            /// @param Name within the shader
            ///
            void UseVector4(IMaterial* a_pMaterial, Vector4<float32> a_Value, const char8* a_pName);
            /// @brief Use this Vector4 
            ///
            /// @brief Material to use
            /// @param Vector4 as Value
            /// @param Name within the shader
            ///
            void UseColor(IMaterial* a_pMaterial, Color a_Value, const char8* a_pName);
            /// @brief Use this Matrix 
            ///
            /// @brief Material to use
            /// @param Matrix as Value
            /// @param Name within the shader
            ///
            void UseMatrix(IMaterial* a_pMaterial, Matrix<float32> a_Value, const char8* a_pName);
            /// @brief Use this Texture2D
            ///
            /// @brief Material to use
            /// @param Texture2D as Value
            /// @param Name within the shader
            ///
            void UseTexture2D(IMaterial* a_pMaterial, ITexture2D* a_Value, const char8* a_pName, int32 m_TextureCount);
            /// @brief Use this CubeMap
            ///
            /// @brief Material to use
            /// @param CubeMap as Value
            /// @param Name within the shader
            ///
            void UseCubeMap(IMaterial* a_pMaterial, ITexture2D* a_Value, const char8* a_pName, int32 m_TextureCount);
            /// @brief Use this Function to Render one Directional Light
            ///
            /// @param DirectionalLight Object
            /// @param Material for this Light
            /// @param Direction for this Light
            /// @param Color for this Light
            ///
            void RenderDirectionalLight(CDirectionalLight* a_pDirectionalLight, IMaterial* a_pMaterial, Vector3<float32> a_Direction, Color a_Color);
            /// @brief Use this Function to Render one PointLight
            ///
            /// @param PointLight Object
            /// @param Material for this Light
            /// @param Position for this Light
            /// @param Color for this Light
            /// @param Constant Attenuation for this Light
            /// @param Exponential Attenuation for this Light
            /// @param Linear Attenuation for this Light
            ///
            void RenderPointLight(CPointLight* a_pPointLight, IMaterial* a_pMaterial, Vector3<float32> a_Position, Color a_Color, float32 a_Radius, float32 a_Intensity);
            /// @brief Use this Function to Render a instanced Vertex Buffer
            ///
            /// @param VertexBuffer Object
            /// @param VertexBuffer Count
            /// @param Primitive
            /// @param Material for this Model
            /// @param Instances to render
            ///
            void RenderInstancedVBuffer(IVertexBuffer* a_pBuffer,int32 a_VertexCount, IMaterial* a_pMaterial, EPrimitive a_Primitive, SRenderInstance* a_pInstances, int32 a_Instances);
            /// @brief Use this Function to Render instanced Models
            ///
            /// @param Model Object
            /// @param Primitive
            /// @param Material for this Model
            /// @param Instances to render
            ///
            void RenderInstancedModels(CModel* a_pModel, IMaterial* a_pMaterial, EPrimitive a_Primitive, SRenderInstance* a_pInstances, int32 a_Instances);
            /// @brief Use this Function to Render a Skybox
            ///
            /// @param Skybox Object
            /// @param Material for this Model
            /// @param Rotation
            ///
            void RenderSkybox(CSkyBox* a_pSkyBox, IMaterial* a_pMaterial, Vector3<float32> a_Rotation);

            /// @brief Use this Function to Render one Sprite
            ///
            /// @param Sprite Object
            /// @param Material for this Sprite
            /// @param Position for this Sprite
            /// @param Rotation for this Sprite
            /// @param Center for this Sprite
            /// @param Size for this Sprite
            /// @param Color for this Sprite
            /// @param Whether to check if he is inside or not
            ///
            void RenderSprite(CSprite* a_pSprite, IMaterial* a_pMaterial, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color, bool a_FrustrumCheck, Vector2<float32> a_UVSize, Vector2<float32> a_UVPosition);


            /// @brief Use this Function to Render one Font
            ///
            /// @param Font Object
            /// @param Material for this Font
            /// @param Text to display
            /// @param Position for this Font
            /// @param Rotation for this Font
            /// @param Size for this Font
            /// @param Offset for each Char
            ///
            void RenderFont(CFont* a_pFont, IMaterial* a_pMaterial, std::string a_Text, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Size, float32 a_Offset, bool a_FrustrumCheck, Color a_Color);

            /// @brief Use this Function to Render one VertexBuffer
            ///
            /// @param VertexBuffer Object
            /// @param VertexBuffer Count
            /// @param Material for this VertexBuffer
            /// @param Primitive
            /// @param Position for this VertexBuffer
            /// @param Rotation for this VertexBuffer
            /// @param Center for this VertexBuffer
            /// @param Size for this VertexBuffer
            /// @param Color for this VertexBuffer
            ///
            void RenderVertexBuffer(IVertexBuffer* a_pBuffer, int32 a_VertexCount, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color);
            /// @brief Use this Function to Render one Model
            ///
            /// @param Model Object
            /// @param Material for this Model
            /// @param Primitive
            /// @param Position for this Model
            /// @param Rotation for this Model
            /// @param Center for this Model
            /// @param Size for this Model
            /// @param Color for this Model
            /// @param Whether to check if he is inside or not
            ///
            void RenderModel(CModel* a_pModel, IMaterial* a_pMaterial, EPrimitive a_Primitive, Vector3<float32> a_Position, Matrix<float32> a_Rotation, Vector3<float32> a_Center, Vector3<float32> a_Size, Color a_Color,bool a_FrustrumCheck);
            /// @brief Use this Function to Render one Emitter Model
            ///
            /// @param ParticleEmitter Object
            /// @param Material for this Emitter
            /// @param Model Object to emitt
            /// @param Primitive
            /// @param Whether to check if he is inside or not
            ///
            void RenderEmitterModel(CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CModel* a_pModel, EPrimitive a_Primitive, bool a_FrustrumCheck, float a_Fade);
            /// @brief Use this Function to Render one Emitter Sprite
            ///
            /// @param ParticleEmitter Object
            /// @param Material for this Emitter
            /// @param Sprite Object to emitt
            /// @param Primitive
            /// @param Whether to check if he is inside or not
            ///
            void RenderEmitterSprite(CParticleEmitter* a_pEmitter, IMaterial* a_pMaterial, CSprite* a_pSprite, bool a_FrustrumCheck, float a_Fade);
            /// @brief Use this Function to set Culling
            ///
            /// @param True for culling, false for not
            ///
            void RenderCulling(bool a_Culling);
       };
    }
}
#endif /* _RENDERER_H_ */