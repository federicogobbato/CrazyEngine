#pragma once 

#include "../CoreMinimal.h"


namespace Engine {

    class Sprite
    {
        GLuint m_VBO; //Vertex Buffer Object
        GLuint m_VAO; //Vertex Array Object
        GLuint m_EBO; //Element array
        Vertex m_Square[4];
        Texture* m_Texture;
        Texture* m_SecondTexture;

        void alternateSprites(GLSLProgram* shaderProgram, float time);

    public:

        void setSecondTexture(Texture* texture) {
            m_SecondTexture = texture;
        }

        Sprite(Texture* texture, float x = -0.5, float y = -0.5, float width = 1, float height = 1);
        ~Sprite();

        void Init(GLSLProgram* shaderProgram);

        void draw(GLSLProgram* shaderProgram, float time = 1.0f);
    };
}
