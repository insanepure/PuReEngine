#include "include/PuReEngine/Camera.h"


// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {


        // **************************************************************************
        // **************************************************************************
        CCamera::CCamera(Vector2<float32> a_Resolution, CameraProjection a_UsedProjection)
            : m_Resolution(a_Resolution), m_UsedProjection(a_UsedProjection)
        {
            this->m_Position = Vector3<float32>(0, 0, -1);

            this->m_Forward = Vector3<float32>(0, 0, 1);
            this->m_Up = Vector3<float32>(0, 1, 0);
            this->m_FoV = 100.0f;
            this->m_AspectRatio = a_Resolution.X / a_Resolution.Y;
            this->m_NearFar = Vector2<float32>(0.1f, 100.0f);

            this->m_AxisRotation = Vector3<float32>();
            this->m_Rotation = Quaternion<float32>();
            this->CalculateFrustum();
            this->m_UpdateMatrix = true;
            this->m_ViewSet = false;
            this->m_ProjectionSet = false;
        }
        // **************************************************************************
        // **************************************************************************
        CCamera::CCamera(Vector3<float32> a_Position, Vector3<float32> a_Forward, Vector3<float32> a_Up, float32 a_FoV, float32 a_AspectRatio,
            Vector2<float32> a_NearFar, Vector2<float32> a_Resolution, CameraProjection a_UsedProjection)
            : m_Position(a_Position), m_Forward(a_Forward), m_Up(a_Up), m_FoV(a_FoV), m_AspectRatio(a_AspectRatio),
            m_NearFar(a_NearFar), m_Resolution(a_Resolution), m_UsedProjection(a_UsedProjection)
        {
            this->m_AxisRotation = Vector3<float32>();
            this->m_Rotation = Quaternion<float32>();
            this->CalculateFrustum();
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        CCamera::~CCamera()
        {

        }
        // **************************************************************************
        // **************************************************************************
        Plane<float32> CCamera::GetFrustrumPlane(int32 a_Index)
        {
            if (a_Index < 6)
                return this->m_FrustumPlanes[a_Index];
            else
                return Plane<float32>();
        }
        // **************************************************************************
        // **************************************************************************
        bool CCamera::BoxInFrustum(CBoundingBox* a_pBox)
        {
            if (this->m_UpdateMatrix)
                this->Update();
            for (int32 i = 0; i < 6; i++)
            {
                Vector3<float32> p = a_pBox->m_Position;
                Vector3<float32> n = a_pBox->m_Size;
                if (this->m_FrustumPlanes[i].Normal.X >= 0)
                {
                    p.X = a_pBox->m_Size.X;
                    n.X = a_pBox->m_Position.X;
                }
                if (this->m_FrustumPlanes[i].Normal.Y >= 0)
                {
                    p.Y = a_pBox->m_Size.Y;
                    n.Y = a_pBox->m_Position.Y;
                }
                if (this->m_FrustumPlanes[i].Normal.Z >= 0)
                {
                    p.Z = a_pBox->m_Size.Z;
                    n.Z = a_pBox->m_Position.Z;
                }
                //positive side is outside, 
                if (Plane<float32>::Distance(this->m_FrustumPlanes[i], p) < 0)
                    return false;
            }
            //testing with n results in whether it INTERSECTS or is FULL inside, so return true anyway
            return true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::CalculateFrustum()
        {
            Vector3<float32> zAxis = -this->GetForward(); //new forward vector
            Vector3<float32> xAxis = Vector3<float32>::Normalize(Vector3<float32>::Cross(this->GetUp(), zAxis)); //new side vector
            Vector3<float32> yAxis = Vector3<float32>::Normalize(Vector3<float32>::Cross(zAxis, xAxis)); //new up vector

            Vector3<float32> nearCenter = this->m_Position - zAxis * this->m_NearFar.X;
            Vector3<float32> farCenter = this->m_Position - zAxis * this->m_NearFar.Y;

            float32 hNear = 2 * tan(this->m_FoV / 2.0f) * this->m_NearFar.X;
            float32 wNear = hNear * this->m_AspectRatio;

            Vector3<float32> mzAxis = -zAxis;
            this->m_FrustumPlanes[Near] = Plane<float32>(mzAxis, nearCenter);
            this->m_FrustumPlanes[Far] = Plane<float32>(zAxis, farCenter);

            Vector3<float32> aux, normal,point;

            aux = Vector3<float32>::Normalize((nearCenter + yAxis*hNear) - this->m_Position);
            normal = Vector3<float32>::Cross(aux, xAxis);
            point = nearCenter + yAxis*hNear;

            this->m_FrustumPlanes[Top] = Plane<float32>(normal, point);

            aux = Vector3<float32>::Normalize((nearCenter - yAxis*hNear) - this->m_Position);
            normal = Vector3<float32>::Cross(xAxis, aux);
            point = nearCenter - yAxis*hNear;

            this->m_FrustumPlanes[Bottom] = Plane<float32>(normal, point);

            aux = Vector3<float32>::Normalize((nearCenter - xAxis*wNear) - this->m_Position);
            normal = Vector3<float32>::Cross(aux, yAxis);
            point = nearCenter - xAxis*wNear;

            this->m_FrustumPlanes[Left] = Plane<float32>(normal, point);

            aux = Vector3<float32>::Normalize((nearCenter + xAxis*wNear) - this->m_Position);
            normal = Vector3<float32>::Cross(yAxis, aux);
            point = nearCenter + xAxis*wNear;

            this->m_FrustumPlanes[Right] = Plane<float32>(normal, point);
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::Rotate(float32 a_X_Axis, float32 a_Y_Axis, float32 a_Z_Axis)
        {
            this->m_AxisRotation.X += a_X_Axis;
            this->m_AxisRotation.Y += a_Y_Axis;
            this->m_AxisRotation.Z += a_Z_Axis;
            this->m_Rotation = Quaternion<float32>(this->m_AxisRotation.X*PuRe_DegToRad, this->m_AxisRotation.Y*PuRe_DegToRad, this->m_AxisRotation.Z*PuRe_DegToRad);
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::Move(Vector3<float32> a_MovePosition)
        {
            this->m_Position += a_MovePosition * this->m_Rotation.GetMatrix();
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        Quaternion<float32> CCamera::GetQuaternion()
        {
            return this->m_Rotation;
        }
        // **************************************************************************
        // **************************************************************************
        Vector2<float32> CCamera::GetNearFar()
        {
            return this->m_NearFar;
        }
        // **************************************************************************
        // **************************************************************************
        Vector3<float32> CCamera::GetRotation()
        {
            return this->m_AxisRotation;
        }
        // **************************************************************************
        // **************************************************************************
        float32 CCamera::GetAspect()
        {
            return this->m_AspectRatio;
        }
        // **************************************************************************
        // **************************************************************************
        Vector3<float32> CCamera::GetPosition()
        {
            return this->m_Position;
        }
        // **************************************************************************
        // **************************************************************************
        Matrix<float32> CCamera::GetView()
        {
            return this->m_View;
        }
        // **************************************************************************
        // **************************************************************************
        Matrix<float32> CCamera::GetProjection()
        {
            return this->m_Projection;
        }
        // **************************************************************************
        // **************************************************************************
        Matrix<float32> CCamera::GetInvertViewProjection()
        {
            return this->m_InvViewProjection;
        }
        // **************************************************************************
        // **************************************************************************
        Matrix<float32> CCamera::GetInvertProjection()
        {
            return this->m_InvProjection;
        }
        // **************************************************************************
        // **************************************************************************
        float32 CCamera::GetFOV()
        {
            return this->m_FoV;
        }
        // **************************************************************************
        // **************************************************************************
        Vector3<float32> CCamera::GetSide()
        {
            return Vector3<float32>::Normalize(Vector3<float32>::Cross(this->GetForward(), this->GetUp()));
        }
        // **************************************************************************
        // **************************************************************************
        Vector3<float32> CCamera::GetForward()
        {
            return Vector3<float32>::Normalize(this->m_Forward * this->m_Rotation.GetMatrix());
        }
        // **************************************************************************
        // **************************************************************************
        Vector3<float32> CCamera::GetUp()
        {
            return Vector3<float32>::Normalize(this->m_Up * this->m_Rotation.GetMatrix());
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::ResetView()
        {
            this->m_ViewSet = false;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::ResetProjection()
        {
            this->m_ProjectionSet = false;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetProjection(Matrix<float32> a_Projection)
        {
            this->m_Projection = a_Projection;
            this->m_ProjectionSet = true;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetView(Matrix<float32> a_View)
        {
            this->m_View = a_View;
            this->m_ViewSet = true;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetPosition(Vector3<float32> a_Position)
        {
            this->m_Position = a_Position;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetForward(Vector3<float32> a_Forward)
        {
            this->m_Forward = a_Forward;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetUp(Vector3<float32> a_Up)
        {
            this->m_Up = a_Up;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetFoV(float32 a_FoV)
        {
            this->m_FoV = a_FoV;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::setAspectRatio(float32 a_AspectRatio)
        {
            this->m_AspectRatio = a_AspectRatio;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::setNearFar(Vector2<float32> a_NearFar)
        {
            this->m_NearFar = a_NearFar;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::setResolution(Vector2<float32> a_Resolution)
        {
            this->m_Resolution = a_Resolution;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetRotation(Vector3<float32> a_Rotation)
        {
            this->m_AxisRotation = a_Rotation;
            this->m_Rotation = Quaternion<float32>(this->m_AxisRotation.X*PuRe_DegToRad, this->m_AxisRotation.Y*PuRe_DegToRad, this->m_AxisRotation.Z*PuRe_DegToRad);
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::SetRotation(Quaternion<float32> a_Rotation)
        {
            this->m_AxisRotation = a_Rotation.GetAxisAngles();
            //Rad to Deg
            this->m_AxisRotation.X *= PuRe_RadToDeg;
            this->m_AxisRotation.Y *= PuRe_RadToDeg;
            this->m_AxisRotation.Z *= PuRe_RadToDeg;

            this->m_Rotation = a_Rotation;
            this->m_UpdateMatrix = true;
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::Apply(IMaterial* a_pMaterial)
        {
            //If our Data has been updated, calculate our Matrix
            if (this->m_UpdateMatrix)
                this->Update();
            //Everytime apply is called, set our Matrix
            a_pMaterial->SetMatrix(this->m_Projection, "Projection");
            a_pMaterial->SetMatrix(this->m_View, "View");
        }
        // **************************************************************************
        // **************************************************************************
        void CCamera::Update()
        {
            //Switch which Matrix we use
            if (!this->m_ProjectionSet)
            {
                switch (this->m_UsedProjection)
                {
                case CameraProjection::Orthogonal:
                    this->m_Projection = Matrix<float32>::ProjectionOrthogonalOffCenterLH(0.0f, this->m_Resolution.X, 0.0f, this->m_Resolution.Y, this->m_NearFar.X, this->m_NearFar.Y);
                    break;
                case CameraProjection::Perspective:
                    this->m_Projection = Matrix<float32>::ProjectionPerspectiveFovLH(this->m_FoV*PuRe_DegToRad, this->m_Resolution.X / this->m_Resolution.Y, this->m_NearFar.X, this->m_NearFar.Y);
                    break;
                }
            }
            if (!this->m_ViewSet)
                this->m_View = Matrix<float32>::ViewLH(this->m_Position, this->GetForward(), this->GetUp());

            this->m_InvViewProjection = Matrix<float32>::Invert(this->m_View * this->m_Projection);

            this->CalculateFrustum();
            this->m_UpdateMatrix = false;
        }
    }

}