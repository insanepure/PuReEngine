#ifndef _CAMERA_H_
#define _CAMERA_H_

// Engine specific includes
#include "Defines.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix.h"
#include "IMaterial.h"
#include "Plane.h"
#include "BoundingBox.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        /// @brief Enum for Camera's Projection Matrix
        ///
        enum CameraProjection
        {
            Perspective,
            Orthogonal
        };

        /// @brief Enum for the Planes
        ///
        enum Planes
        {
            Near,
            Far,
            Top,
            Bottom,
            Left,
            Right
        };

        /// @brief Class for Camera
        ///
        class CCamera
        {
        private:
            /// @brief Frustrum Planes used for frustum culling
            ///
            Plane<float32> m_FrustumPlanes[6];
            /// @brief Which Projection Matrix we use
            ///
            CameraProjection m_UsedProjection;
            /// @brief Our Inverted View Projection Matrix
            ///
            Matrix<float32> m_InvViewProjection;
            /// @brief Our Inverted Projection Matrix
            ///
            Matrix<float32> m_InvProjection;
            /// @brief Our Projection Matrix
            ///
            Matrix<float32> m_Projection;
            /// @brief Our View Matrix
            ///
            Matrix<float32> m_View;
            /// @brief Check if we update our Matrix, so we do not update it each frame
            ///
            bool m_UpdateMatrix;
            /// @brief Whether the Projection Matrix has been Set or not
            ///
            bool m_ProjectionSet;
            /// @brief Whether the View Matrix has been Set or not
            ///
            bool m_ViewSet;
            /// @brief Quaternion to describe our Rotation
            ///
            Quaternion<float32> m_Rotation;
            /// @brief Camera's Near / Far Plane
            ///
            Vector2<float32> m_NearFar;
            /// @brief Camera's Rotation
            ///
            Vector3<float32> m_AxisRotation;
            /// @brief Camera's Position in World Coordinations
            ///
            Vector3<float32> m_Position;
            /// @brief Camera's Forward
            ///
            Vector3<float32> m_Forward;
            /// @brief Camera's Up Vector
            ///
            Vector3<float32> m_Up;
            /// @brief Camera's Field of View
            ///
            float32 m_FoV;
            /// @brief Camera's Aspect Ratio
            ///
            float32 m_AspectRatio;
            /// @brief Graphics Resolution
            ///
            Vector2<float32> m_Resolution;
        public:
            /// @brief Creates an instance of Camera.
            ///
            /// @param Graphic's Resolution
            /// @param Camera's Projection Matrix we use
            ///
            CCamera(Vector2<float32> a_Resolution, CameraProjection a_UsedProjection);
            /// @brief Creates an instance of Camera.
            ///
            /// @param Camera's Position
            /// @param Camera's Forward Vector
            /// @param Camera's Up Vector
            /// @param Camera's Field of View in Degree
            /// @param Camera's Aspect Ratio
            /// @param Camera's Near Far Plane
            /// @param Camera's Projection Matrix we use
            /// @param Graphic's Resolution
            ///
            CCamera(Vector3<float32> a_Position, Vector3<float32> a_Forward, Vector3<float32> a_Up, float32 a_FOV, float32 a_AspectRatio,
                Vector2<float32> a_NearFar, Vector2<float32> a_Resolution, CameraProjection a_UsedProjection);

            /// @brief Destroyes the instance of camera
            ///
            ~CCamera();
        public:
            /// @brief Calculate if the Box is within the Frustum
            ///
            /// @param Box tested
            ///
            /// @returns if it is inside or not
            ///
            bool BoxInFrustum(CBoundingBox* a_pBox);

            /// @brief Calculate the Frustum for Culling.
            ///
            void CalculateFrustum();

            /// @brief Rotates the Camera around the three Axis in Degree.
            ///
            /// @param Rotation around the X_Axis
            /// @param Rotation around the Y_Axis
            /// @param Rotation around the Z_Axis
            ///
            void Rotate(float32 a_X_Axis, float32 a_Y_Axis, float32 a_Z_Axis);

            /// @brief Moves a Position
            ///
            /// @param Position to Move
            ///
            void Move(Vector3<float32> a_MovePosition);

            /// @brief Returns the Inverted View Projection Matrix of the Camera
            ///
            /// @returns Camera's Inverted View Projection Matrix
            ///
            Matrix<float32> GetInvertViewProjection();

            /// @brief Returns the Inverted Projection Matrix of the Camera
            ///
            /// @returns Camera's Inverted Projection Matrix
            ///
            Matrix<float32> GetInvertProjection();

            /// @brief Returns the View Matrix of the Camera
            ///
            /// @returns Camera's View Matrix
            ///
            Matrix<float32> GetView();

            /// @brief Returns the Projection Matrix of the Camera
            ///
            /// @returns Camera's Projection Matrix
            ///
            Matrix<float32> GetProjection();

            /// @brief Returns the FOV of the Camera
            ///
            /// @returns Camera's FOV
            ///
            float32 GetFOV();

            /// @brief Returns the NearFar Distance of the Camera
            ///
            /// @returns Camera's NearFar
            ///
            Vector2<float32> GetNearFar();

            /// @brief Returns the Side Vector of the Camera
            ///
            /// @returns Camera's Side Vector
            ///
            Vector3<float32> GetSide();

            /// @brief Return the Forward of the Camera
            ///
            /// @returns Forward as Vector3
            ///
            Vector3<float32> GetForward();

            /// @brief Returns the Up Vector of the Camera
            ///
            /// @returns Camera's Up Vector
            ///
            Vector3<float32> GetUp();


            /// @brief Returns the Rotation in Degree
            ///
            /// @returns Camera's Rotation
            ///
            Vector3<float32> GetRotation();


            /// @brief Returns the Rotation as Quaternion
            ///
            /// @returns Camera's Rotation
            ///
            Quaternion<float32> GetQuaternion();

            /// @brief Return the Position of the Camera
            ///
            /// @returns Position as Vector3
            ///
            Vector3<float32> GetPosition();

            /// @brief Return the Aspect Ratio
            ///
            /// @returns Aspect Ratio as float
            ///
            float32 GetAspect();

            /// @brief Return the Frustrum's Plane
            ///
            /// @param Index of the Plane we want
            ///
            /// @returns FrustrumPlane as Plane<float32>
            ///
            Plane<float32> GetFrustrumPlane(int32 a_Index);


            /// @brief sets the View Matrix of the Camera
            ///
            void ResetView();

            /// @brief sets the Projection Matrix of the Camera
            ///
            void ResetProjection();

            /// @brief sets the View Matrix of the Camera
            ///
            /// @param Camera's View
            ///
            void SetView(Matrix<float32> a_View);

            /// @brief sets the Projection Matrix of the Camera
            ///
            /// @param Camera's Projection
            ///
            void SetProjection(Matrix<float32> a_Projection);

            /// @brief sets the Forward of the Camera
            ///
            /// @param Camera's Forward
            ///
            void SetForward(Vector3<float32> a_Forward);

            /// @brief sets the Position of the Camera
            ///
            /// @param Camera's Position
            ///
            void SetPosition(Vector3<float32> a_Position);

            /// @brief sets the Rotation of the Camera
            ///
            /// @param Camera's Rotation
            ///
            void SetRotation(Vector3<float32> a_Rotation);

            /// @brief sets the Rotation of the Camera
            ///
            /// @param Camera's Rotation
            ///
            void SetRotation(Quaternion<float32> a_Rotation);

            /// @brief sets the Up Vector of the Camera
            ///
            /// @param Camera's Up Vector
            ///
            void SetUp(Vector3<float32> a_Up);

            /// @brief sets the Field ov View of the Camera in Degree
            ///
            /// @param Camera's Field ov View in Degree
            ///
            void SetFoV(float32 a_FoV);

            /// @brief sets the aspectratio of the Camera
            ///
            /// @param Camera's aspect ratio
            ///
            void setAspectRatio(float32 a_AspectRatio);

            /// @brief sets the Resolution of the Camera
            ///
            /// @param Camera's new Resolution
            ///
            void setResolution(Vector2<float32> a_Resolution);

            /// @brief sets the NearFar of the Camera
            ///
            /// @param Camera's new NearFar
            ///
            void setNearFar(Vector2<float32> a_NearFar);

            /// @brief Apply our Camera
            ///
            /// @param Material to append Camera to
            ///
            void Apply(IMaterial* a_oMaterial);

            /// @brief Use orthogonal Matrix
            ///
            /// @param Material to append Camera to
            ///
            void UseOrthogonal(IMaterial* a_pMaterial);


            /// @brief Updates the View and Projection Matrix
            ///
            void Update();
        };
    }

}
#endif /* _CAMERA_H_ */