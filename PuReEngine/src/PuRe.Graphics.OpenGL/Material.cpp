#include "include/PuReEngine/OpenGL/Material.h"

namespace PuReEngine
{
    namespace Graphics
    {
        namespace OpenGL
        {

            CMaterial::CMaterial(const char8* a_pFile)
            {
                std::string filename = a_pFile;
                this->m_ProgramID = NULL;
                //create Program
                this->m_ProgramID = glCreateProgram();
                //Load Vertex
                this->m_VertexID = this->loadShader((filename + ".vertex").c_str(), GL_VERTEX_SHADER);
                //Attach Vertex and Program
                glAttachShader(this->m_ProgramID, this->m_VertexID);
                //Load Fragment
                this->m_FragmentID = this->loadShader((filename + ".fragment").c_str(), GL_FRAGMENT_SHADER);
                //Attach Fragment and Program
                glAttachShader(this->m_ProgramID, this->m_FragmentID);
                //Link program
                glLinkProgram(this->m_ProgramID);

                //Check for Errors
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(this->m_ProgramID, GL_LINK_STATUS, &programSuccess);
                if (programSuccess != GL_TRUE)
                {
                    printf("Error linking program %d!\n", this->m_ProgramID);
                    this->ProgramLog(this->m_ProgramID);
                    glDeleteProgram(this->m_ProgramID);
                    this->m_ProgramID = 0;
                }
            }
            CMaterial::~CMaterial()
            {
                glDeleteProgram(this->m_ProgramID);
                glUseProgram(NULL);
            }

            void CMaterial::SetMatrix(Matrix<float32>& a_rMatrix, const char8* a_pName)
            {
                glUniformMatrix4fv(glGetUniformLocation(this->m_ProgramID, a_pName), 1, 0, a_rMatrix);
                //const GLenum ErrorValue = glGetError();
            }

            void CMaterial::SetCubeMap(ITexture2D* a_pTexture, const char8* a_pName, int32 a_Position)
            {
                glDepthFunc(GL_LEQUAL);
                glActiveTexture(GL_TEXTURE0 + a_Position);
                glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)a_pTexture->GetData());
                glUniform1i(glGetUniformLocation(this->m_ProgramID, a_pName), a_Position);
            }

            void CMaterial::SetTexture2D(ITexture2D* a_pTexture, const char8* a_pName, int32 a_Position)
            {
                glActiveTexture(GL_TEXTURE0 + a_Position);
                glBindTexture(GL_TEXTURE_2D, (GLuint)a_pTexture->GetData());
                glUniform1i(glGetUniformLocation(this->m_ProgramID, a_pName), a_Position);
            }

            void CMaterial::SetFloat(float32 a_Value, const char8* a_pName)
            {
                glUniform1f(glGetUniformLocation(this->m_ProgramID, a_pName), a_Value);
            }

            void CMaterial::SetVector2(Vector2<float32> a_Vector, const char8* a_pName)
            {
                glUniform2fv(glGetUniformLocation(this->m_ProgramID, a_pName), 1, a_Vector);
            }

            void CMaterial::SetVector3(Vector3<float32> a_Vector, const char8* a_pName)
            {
                glUniform3fv(glGetUniformLocation(this->m_ProgramID, a_pName), 1, a_Vector);
            }

            void CMaterial::SetVector4(Vector4<float32> a_Vector, const char8* a_pName)
            {
                glUniform4fv(glGetUniformLocation(this->m_ProgramID, a_pName), 1, a_Vector);
            }

            void CMaterial::SetColor(Color a_Value, const char8* a_pName)
            {
                glUniform4fv(glGetUniformLocation(this->m_ProgramID, a_pName),1, a_Value);
            }

            void CMaterial::Apply()
            {
                glUseProgram(this->m_ProgramID);
            }

            GLuint CMaterial::loadShader(const char* a_pPath, GLenum a_ShaderType)
            {
                GLuint shader = 0;
                //Open File
                std::ifstream file(a_pPath, std::ifstream::binary);
                if (file)
                {
                    //Get Length
                    file.seekg(0, file.end);
                    int32 size = (int32)file.tellg();
                    //Go back to Start
                    file.seekg(0, file.beg);
                    //Create Shader
                    shader = glCreateShader(a_ShaderType);
                    //Create Buffer
                    char8* pbuffer = (char8*)malloc(sizeof(char8)*size + 1);
                    //Put everything inside the buffe
                    file.read(pbuffer, size);
                    pbuffer[size] = 0;
                    //set content of buffer als shadersource
                    glShaderSource(shader, 1, (const GLchar**)&pbuffer, NULL);
                    //compile
                    glCompileShader(shader);
                    //check for errors
                    GLint shaderCompiled = GL_FALSE;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
                    if (shaderCompiled != GL_TRUE)
                    {
                        //Errors
                        printf("Unable to compile shader %d!\n\nSource:\n%s\n", shader, pbuffer);
                        //Call Log
                        this->ShaderLog(shader);
                        glDeleteShader(shader);
                        shader = 0;
                    }
                    //Free Memory
                    free(pbuffer);
                    file.close();
                }
                else
                {
                    printf("Unable to open file %s\n", a_pPath);
                }
                return shader;
            }
            void CMaterial::ProgramLog(GLuint a_Program)
            {
                //if program existst
                if (glIsProgram(a_Program))
                {
                    //get length
                    int32 infoLogLength = 0;
                    int32 maxLength = infoLogLength;

                    //get length of error
                    glGetProgramiv(a_Program, GL_INFO_LOG_LENGTH, &maxLength);

                    //Allocate string
                    char8* infoLog = new char8[maxLength];

                    //get error
                    glGetProgramInfoLog(a_Program, maxLength, &infoLogLength, infoLog);
                    if (infoLogLength > 0)
                    {
                        //Print it
                        printf("%s\n", infoLog);
                    }

                    //Deallocate string
                    delete[] infoLog;
                }
                else
                {
                    printf("Name %d is not a program\n", a_Program);
                }
            }
            void CMaterial::ShaderLog(GLuint a_Shader)
            {
                //if its a shader
                if (glIsShader(a_Shader))
                {
                    //get length
                    int infoLogLength = 0;
                    int maxLength = infoLogLength;

                    //get length of error
                    glGetShaderiv(a_Shader, GL_INFO_LOG_LENGTH, &maxLength);

                    //Allocate string
                    char8* infoLog = new char8[maxLength];

                    //get error
                    glGetShaderInfoLog(a_Shader, maxLength, &infoLogLength, infoLog);
                    if (infoLogLength > 0)
                    {
                        //Print it
                        printf("%s\n", infoLog);
                    }

                    //Deallocate string
                    delete[] infoLog;
                }
                else
                {
                    printf("Name %d is not a shader\n", a_Shader);
                }
            }

        }
    }
}
