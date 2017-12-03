#include "Arkanoid.h"

#include <Engine\ExtraFunctions.h>
#include <Engine\Window.h>

using namespace Engine;

Arkanoid::Arkanoid() :
    m_CurrentLevel(nullptr),
    m_CurrentLevelNumber(1),
    m_MaxLevelNumber(2)
{
    m_Window = static_cast<WindowOPENGL*>(Window::GetSingleton());
}

Arkanoid::~Arkanoid()
{
    for (auto it = m_Levels.begin(); it != m_Levels.end(); it++)
    {
        delete it->second;
    }
}

void Arkanoid::init()
{
    m_Camera.init((float)m_Window->getScreenWidth(), (float)m_Window->getScreenHeight());
    initShaders();
    m_ActorsSpriteBatch.init();
    srand(time(0));
    loadLevel("Levels/Level1.txt", m_CurrentLevelNumber); 
}

void Arkanoid::initShaders()
{
    m_TextureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    m_TextureProgram.addAttribute("vertexPosition");
    m_TextureProgram.addAttribute("vertexColor");
    m_TextureProgram.addAttribute("vertexUV");
    m_TextureProgram.linkShader();
}

void Arkanoid::loadLevel(const std::string &levelPath, int levelNumber)
{
    auto it = m_Levels.find(levelNumber);
    if (it != m_Levels.end())
    {
        // Reload the level 
        m_Levels[levelNumber]->reloadLevel();
        m_CurrentLevel = m_Levels[levelNumber];
    }
    else
    {
        // Create a new level
        Level *newLevel = new Level();
        newLevel->loadLevelMap(levelPath, m_Window->getScreenWidth(), m_Window->getScreenHeight());
        newLevel->loadLevelElements(m_Window->getScreenWidth(), m_Window->getScreenHeight());
        m_Levels[levelNumber] = newLevel;
        m_CurrentLevel = newLevel;
    }   
}

void Arkanoid::update()
{
    static int timerAtBegin = SDL_GetTicks();
    static int timerPrevSecond = timerAtBegin;

    int currentTime = SDL_GetTicks();

    int physicStep = 0;

    // Every frame we update the position and check the collisions "MaxPhysicSteps" times
    while (physicStep < m_Window->getMaxPhysicSteps())
    {        
        m_CurrentLevel->updateLevel(m_Window->getFixedDeltaTime());
        physicStep++;

        if (m_Window->getGameState() == GameState::NEXT_LEVEL)
        {
            m_CurrentLevelNumber++;
            if (m_CurrentLevelNumber > m_MaxLevelNumber) {
                m_CurrentLevelNumber = 1;
            }
            loadLevel("Levels/Level" + std::to_string(m_CurrentLevelNumber) + ".txt", m_CurrentLevelNumber);
            m_Window->setGameState(GameState::PLAY);
            break;
        }

        // Update the Input Manager to build the map of the keys pressed the first physic step 
        m_Window->processEvent();
    }

    m_Camera.update();
    render();
}

void Arkanoid::render()
{
    m_TextureProgram.use();
    setUniformShaderVariables();

    m_ActorsSpriteBatch.begin();
     
    m_CurrentLevel->drawLevel(m_ActorsSpriteBatch);

    m_ActorsSpriteBatch.end();
    m_ActorsSpriteBatch.renderBatch();
 
    m_TextureProgram.unuse();
}

void Arkanoid::setUniformShaderVariables()
{
    // We are using texture unit 0
    glActiveTexture(GL_TEXTURE0);
    // Get the uniform location
    GLint textureLocation = m_TextureProgram.getUniformLocation("myTexture");
    // Tell the shader that the texture is in texture unit 0
    glUniform1i(textureLocation, 0); 

    //Set the camera matrix
    GLint cameraLocation = m_TextureProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = m_Camera.getCameraMatrix();
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
}
