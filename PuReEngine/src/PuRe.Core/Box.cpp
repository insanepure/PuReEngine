#include "include/PuReEngine/Box.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine
{
    namespace Core
    {

        // **************************************************************************
        // **************************************************************************

        Box::Box(IGraphics* a_pGraphics) : m_pGraphics(a_pGraphics)
        {
            int stride = sizeof(SVertex);
            this->m_pVertexBuffer = this->m_pGraphics->CreateVertexBuffer(stride * 36, stride); //9 Floats (3 Position, 2 UV,4 Color) * 36 Vertices
            //Lock it
            SVertex* pdata = (SVertex*)this->m_pVertexBuffer->Lock();
            //copy data into it
            this->GetVertices(pdata);
            //unlock it
            this->m_pVertexBuffer->Unlock();
        }

        // **************************************************************************
        // **************************************************************************

        Box::~Box()
        {
            SAFE_DELETE(this->m_pVertexBuffer);
        }

        // **************************************************************************
        // **************************************************************************

        void Box::GetVertices(SVertex* a_pVertex)
        {
            int8 count = 0;
            /* TRIANGLE 1 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.999110f, 0.498923f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            /* TRIANGLE 2 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.999455f, 0.249620f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.999110f, 0.498923f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 0.000000f, 1.000000f);
            count++;
            /* TRIANGLE 3 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.001085f, 0.249620f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.249682f, 0.250323f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            /* TRIANGLE 4 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.001517f, 0.500006f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.001085f, 0.249620f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-1.000000f, -0.000000f, 0.000000f);
            count++;
            /* TRIANGLE 5 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(0.999999f, 1.000000f, -1.000001f);
            a_pVertex[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            /* TRIANGLE 6 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.250471f, 0.499298f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.249682f, 0.250323f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000001f, 0.000000f, -1.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(0.999999f, 1.000000f, -1.000001f);
            a_pVertex[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -0.000000f, -1.000000f);
            count++;
            /* TRIANGLE 7 */
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            /* TRIANGLE 8 */
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(0.999999f, 1.000000f, -1.000001f);
            a_pVertex[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, 0.000000f, -0.000001f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(1.000000f, -0.000000f, -0.000000f);
            count++;
            /* TRIANGLE 9 */
            a_pVertex[count].Position = Vector3<float32>(0.999999f, 1.000000f, -1.000001f);
            a_pVertex[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748355f, 0.001770f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748573f, 0.249588f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            /* TRIANGLE 10 */
            a_pVertex[count].Position = Vector3<float32>(0.999999f, 1.000000f, -1.000001f);
            a_pVertex[count].UV = Vector2<float32>(0.500149f, 0.249834f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.500193f, 0.001272f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, 1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748355f, 0.001770f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(0.000000f, 1.000000f, 0.000000f);
            count++;
            /* TRIANGLE 11 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.498993f, 0.749585f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.499422f, 0.499761f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            /* TRIANGLE 12 */
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.748953f, 0.749080f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(-1.000000f, -1.000000f, -1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.498993f, 0.749585f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
            a_pVertex[count].Position = Vector3<float32>(1.000000f, -1.000000f, 1.000000f);
            a_pVertex[count].UV = Vector2<float32>(0.749279f, 0.498716f);
            a_pVertex[count].Color = Vector3<float32>(1.000000f, 0.000000f, 0.000000f);
            a_pVertex[count].Normal = Vector3<float32>(-0.000000f, -1.000000f, -0.000000f);
            count++;
        }

        // **************************************************************************
        // **************************************************************************

        IVertexBuffer* Box::GetBuffer()
        {
            return this->m_pVertexBuffer;
        }
    }
}