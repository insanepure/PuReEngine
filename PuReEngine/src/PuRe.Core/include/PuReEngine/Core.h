#ifndef _CORE_H_
#define _CORE_H_

#include "Socket.h"
#include "IPlatform.h"
#include "Application.h"
#include "IGraphics.h"
#include "IInput.h"
#include "IScene.h"
#include "IMaterial.h"
#include "Color.h"
#include "Vector3.h"
#include "ITexture2D.h"
#include "IRendertarget.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "IWindow.h"
#include "GraphicsModuleType.h"
#include "IIndexBuffer.h"
#include "IVertexBuffer.h"
#include "IInstanceBuffer.h"
#include "Texture2DDescription.h"
#include "Camera.h"
#include "Sprite.h"
#include "Quad.h"
#include "Sphere.h"
#include "Box.h"
#include "Model.h"
#include "Timer.h"
#include "Font.h"
#include "BoundingBox.h"
#include "SoundPlayer.h"
#include "SkyBox.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ParticleEmitter.h"
#include "Renderer.h"

#include <vector>
#include <array>


#define PuRe_Application ::PuReEngine::Core::CApplication
#define PuRe_ApplicationDescription ::PuReEngine::Core::SApplicationDescription
#define PuRe_GraphicsDescription ::PuReEngine::Core::SGraphicsDescription
#define PuRe_WindowDescription ::PuReEngine::Core::SWindowDescription
#define PuRe_DisplaySetting ::PuReEngine::Core::EDisplaySetting
#define PuRe_IGraphics ::PuReEngine::Core::IGraphics
#define PuRe_IInput ::PuReEngine::Core::IInput
#define PuRe_IScene ::PuReEngine::Core::IScene
#define PuRe_IMaterial ::PuReEngine::Core::IMaterial
#define PuRe_Color ::PuReEngine::Core::Color
#define PuRe_Rendertarget ::PuReEngine::Core::IRendertarget
#define PuRe_ITexture2D ::PuReEngine::Core::ITexture2D
#define PuRe_QuaternionF ::PuReEngine::Core::Quaternion<float>
#define PuRe_QuaternionD ::PuReEngine::Core::Quaternion<double>
#define PuRe_MatrixD ::PuReEngine::Core::Matrix<double>
#define PuRe_MatrixF ::PuReEngine::Core::Matrix<float>
#define PuRe_MatrixD ::PuReEngine::Core::Matrix<double>
#define PuRe_Vector2F ::PuReEngine::Core::Vector2<float>
#define PuRe_Vector2D ::PuReEngine::Core::Vector2<double>
#define PuRe_Vector2I ::PuReEngine::Core::Vector2<int>
#define PuRe_Vector2L ::PuReEngine::Core::Vector2<long>
#define PuRe_Vector3F ::PuReEngine::Core::Vector3<float>
#define PuRe_Vector3D ::PuReEngine::Core::Vector3<double>
#define PuRe_Vector3I ::PuReEngine::Core::Vector3<int>
#define PuRe_Vector3L ::PuReEngine::Core::Vector3<long>
#define PuRe_Vector4F ::PuReEngine::Core::Vector4<float>
#define PuRe_Vector4D ::PuReEngine::Core::Vector4<double>
#define PuRe_Vector4I ::PuReEngine::Core::Vector4<int>
#define PuRe_Vector4L ::PuReEngine::Core::Vector4<long>
#define PuRe_IWindow ::PuReEngine::Core::IWindow
#define PuRe_IPlatform ::PuReEngine::Core::IPlatform
#define PuRe_GraphicsModuleType ::PuReEngine::Core::EGraphicsModuleType
#define PuRe_IVertexBuffer ::PuReEngine::Core::IVertexBuffer
#define PuRe_Vertex ::PuReEngine::Core::SVertex
#define PuRe_IIndexBuffer ::PuReEngine::Core::IIndexBuffer
#define PuRe_IInstanceBuffer ::PuReEngine::Core::IInstanceBuffer
#define PuRe_Texture2DDescription ::PuReEngine::Core::STexture2DDescription
#define PuRe_Camera ::PuReEngine::Core::CCamera
#define PuRe_CameraProjection ::PuReEngine::Core::CameraProjection
#define PuRe_Camera_Orthogonal ::PuReEngine::Core::CameraProjection::Orthogonal
#define PuRe_Camera_Perspective ::PuReEngine::Core::CameraProjection::Perspective
#define PuRe_Sprite ::PuReEngine::Core::CSprite
#define PuRe_BoundingBox ::PuReEngine::Core::CBoundingBox
#define PuRe_Quad ::PuReEngine::Core::Quad
#define PuRe_Box ::PuReEngine::Core::Box
#define PuRe_Sphere ::PuReEngine::Core::Sphere
#define PuRe_Timer ::PuReEngine::Core::CTimer
#define PuRe_SoundPlayer ::PuReEngine::Core::CSoundPlayer
#define PuRe_Primitive ::PuReEngine::Core::EPrimitive
#define PuRe_Model ::PuReEngine::Core::CModel
#define PuRe_Socket ::PuReEngine::Core::CSocket
#define PuRe_Protocol ::PuReEngine::Core::ESocketProtocol
#define PuRe_SocketType ::PuReEngine::Core::ESocketType
#define PuRe_SocketSelect ::PuReEngine::Core::ESelect
#define PuRe_Font ::PuReEngine::Core::CFont
#define PuRe_SkyBox ::PuReEngine::Core::CSkyBox
#define PuRe_PointLight ::PuReEngine::Core::CPointLight
#define PuRe_DirectionalLight ::PuReEngine::Core::CDirectionalLight
#define PuRe_Renderer ::PuReEngine::Core::CRenderer
#define PuRe_RenderInstance ::PuReEngine::Core::SRenderInstance
#define PuRe_ParticleEmitter ::PuReEngine::Core::CParticleEmitter
#define PuRe_List std::vector
#define PuRe_Array std::array
#define PuRe_PI 3.14159265358979f

#endif /* _CORE_H_ */