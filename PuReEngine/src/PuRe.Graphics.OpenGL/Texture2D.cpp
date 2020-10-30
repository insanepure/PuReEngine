#include "include/PuReEngine/OpenGL/Texture2D.h"    
#include "SOIL.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {


            // **************************************************************************
            // **************************************************************************
            CTexture2D::CTexture2D()
            {
                this->m_Description.Bpp = 32;
                this->m_Description.Height = 1;
                this->m_Description.Width = 1;
                this->m_TextureID = 0;
                glGenTextures(1, &this->m_TextureID);
            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D::CTexture2D(const STexture2DDescription& a_rDescription)
            {
                this->m_Description = a_rDescription;
                this->m_TextureID = 0;
                glGenTextures(1, &this->m_TextureID);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::Copy(ITexture2D* a_Target, bool a_Rendertarget)
            {
                glCopyImageSubData(this->m_TextureID, GL_TEXTURE_2D, 0, 0, 0, 0, (GLuint)a_Target->GetData(), GL_TEXTURE_2D, 0, 0, 0, 0, this->m_Description.Width, this->m_Description.Height, 1);

                if (a_Rendertarget)
                {

                    int size = this->m_Description.Width*this->m_Description.Height * 4;
                    uint8* pixels = new uint8[size];
                    uint8* pixels2 = new uint8[size];

                    glBindTexture(GL_TEXTURE_2D, (GLuint)a_Target->GetData());
                    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixels);

                    for (int32 y = 0; y < this->m_Description.Height; y++)
                    {
                        for (int32 x = 0; x < this->m_Description.Width; x++)
                        {
                            //flip it
                            int index = x + (y*this->m_Description.Width);
                            index *= 4;
                            //
                            int end = size - index - 4;
                            //flipped

                            pixels2[end] = pixels[index];
                            pixels2[end + 1] = pixels[index + 1];
                            pixels2[end + 2] = pixels[index + 2];
                            pixels2[end + 3] = pixels[index + 3];
                        }
                    }

                    for (int32 y = 0; y < this->m_Description.Height; y++)
                    {
                        for (int32 x = 0; x < this->m_Description.Width; x++)
                        {
                            //mirror it
                            int index = (this->m_Description.Width - x) + (y*this->m_Description.Width);
                            index *= 4;
                            //
                            int end = x + (y*this->m_Description.Width);
                            end *= 4;
                            //flipped

                            pixels[end] = pixels2[index];
                            pixels[end + 1] = pixels2[index + 1];
                            pixels[end + 2] = pixels2[index + 2];
                            pixels[end + 3] = pixels2[index + 3];
                        }
                    }
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
                    glBindTexture(GL_TEXTURE_2D, NULL);

                    SAFE_DELETE_ARRAY(pixels);
                    SAFE_DELETE_ARRAY(pixels2);
                }
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateCubeMap()
            {;
                //Bind texture ID
                glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);
                //Bind Texture repeat UV
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                //Generate buffer
                int32 size = this->m_Description.Height*this->m_Description.Width * 4;
                uint8* ppixels = new uint8[size];
                memset(ppixels, 30, size*sizeof(uint8));
                ppixels[3] = 255; //set alpha of last pixel to 255
                //add Data to Texture
                for (uint32 i = 0; i<6; i++)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ppixels);
                //Unbind
                glBindTexture(GL_TEXTURE_CUBE_MAP, NULL);
                SAFE_DELETE_ARRAY(ppixels);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateCubeMapFromMemory(uint8** a_ppPixels, int32 Width, int32 Height)
            {
                //Delete old
                glDeleteTextures(1, &this->m_TextureID);

                //Create new
                glGenTextures(1, &this->m_TextureID);
                //Bind texture ID
                glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);
                //Bind Texture repeat UV
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                //Load Data
                this->m_Description.Bpp = 32;
                this->m_Description.Width = Width;
                this->m_Description.Height = Height;

                //add Data to Texture
                for (uint32 i = 0; i<6; i++)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_ppPixels[i]);
                }
                //Unbind
                glBindTexture(GL_TEXTURE_2D, NULL);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateTexture()
            {
                //Bind texture ID
                glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
                //Bind Texture repeat UV
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                //Generate buffer
                int32 size = this->m_Description.Height*this->m_Description.Width * 4;
                uint8* ppixels = new uint8[size];
                memset(ppixels, 30, size*sizeof(uint8));
                ppixels[3] = 255; //set alpha of last pixel to 255
                //fill texture with buffer
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ppixels);

                //Unbind texture
                glBindTexture(GL_TEXTURE_2D, NULL);
                //free buffer
                SAFE_DELETE_ARRAY(ppixels);
            }

            // **************************************************************************
            // **************************************************************************
            void CTexture2D::CreateDepth()
            {
                //Bind texture ID
                glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
                //Bind Texture repeat UV
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                //fill texture with buffer
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->m_Description.Width, this->m_Description.Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

                //Unbind texture
                glBindTexture(GL_TEXTURE_2D, NULL);
            }

            // **************************************************************************
            // **************************************************************************
            CTexture2D::~CTexture2D()
            {
                glDeleteTextures(1, &this->m_TextureID);
            }

            // **************************************************************************
            // **************************************************************************
            void* CTexture2D::GetData()
            {
                return (void*)this->m_TextureID;
            }

            // **************************************************************************
            // **************************************************************************
            STexture2DDescription CTexture2D::GetDescription()
            {
                return this->m_Description;
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::LoadTextureFromMemory(uint8* a_pPixels, int32 a_Width, int32 a_Height)
            {
                //Delete old
                glDeleteTextures(1, &this->m_TextureID);

                //Create new
                glGenTextures(1, &this->m_TextureID);
                //Bind texture ID
                glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
                //Bind Texture repeat UV
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                //Load Data
                this->m_Description.Bpp = 32;
                this->m_Description.Width = a_Width;
                this->m_Description.Height = a_Height;
                //add Data to Texture
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_pPixels);
                //Unbind
                glBindTexture(GL_TEXTURE_2D, NULL);
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::SaveTextureToFile(const char8* a_pPath)
            {
                std::string ending = a_pPath;
                ending = ending.substr(ending.find_last_of(".") + 1);

                int size = this->m_Description.Width*this->m_Description.Height * 4;
                uint8* pixels = new uint8[size];

                glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
                glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixels);
                glBindTexture(GL_TEXTURE_2D, NULL);

                if (ending == "bmp")
                    SOIL_save_image(a_pPath, SOIL_SAVE_TYPE_BMP, this->m_Description.Width, this->m_Description.Height, 4, pixels);
                else if (ending == "dds")
                    SOIL_save_image(a_pPath, SOIL_SAVE_TYPE_DDS, this->m_Description.Width, this->m_Description.Height, 4, pixels);

                SAFE_DELETE_ARRAY(pixels);
            }
            // **************************************************************************
            // **************************************************************************
            void CTexture2D::SetPixels(uint8* a_pPixels)
            {
                //Bind texture ID
                glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
                //fill texture with buffer
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Description.Width, this->m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_pPixels);
                //Unbind texture
                glBindTexture(GL_TEXTURE_2D, NULL);
            }

        }
    }
}