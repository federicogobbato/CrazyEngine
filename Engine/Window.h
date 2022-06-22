#pragma once

#include "CoreMinimal.h"

namespace Engine 
{
    class Window : public TSingleton<Window>
    {

    protected:

        SDL_Window* m_SDLWindow;
        SDL_DisplayMode* m_Display;
		InputManager* m_InputManager;

        /* Used to specify some window preference */
        unsigned int m_WindowFlags;

        int m_Width;
        int m_Height;

		int m_DesiredFPS;

        bool m_ShowFPS = true;

        /*Last 60 frames time in nanoseconds */
        long long m_LastSixtyFrameTime = 0;

        /*Number of frames detected (used to calculate the FPS)*/
		int m_FramesDetected = 0;

        /*Duretion of a frame (used to to calculate DeltaTime)*/
		float m_FixedDeltaTime = 0;

        /*Times physics, gameplay and inputs are updated every frame*/
		int m_MaxPhysicSteps = 3;

        GameState m_GameState = START;

        void getDisplayInfo();

    public:


        const float m_MAXFPS = 1000.0f;

        /* Initialize the SDL */
        void initSDL();

        /* Create thw window */
        virtual SDL_Window* initSystem(int width= 1280, int height= 720, int desiredFPS= 60, std::string windowName= "test", unsigned int windowFlags = 0);
        
        virtual void quitSystem();

        /*Update Input */
        bool processEvent();

        /*Save the duration of the last frame time*/
        void calculateFixedDeltaTime();

        /*If 60 frames time are saved calculate the average fps*/
        void showFPS();

        virtual ~Window();

        //! PURE VIRTUAL METHODS
        virtual void clearRenderer() = 0;
        virtual void swapBuffer() = 0;
        virtual void setVSync() = 0;
        virtual void disableVSync() = 0;

#pragma region SET&GET

        inline struct SDL_Window* getSDLWindow() const { return m_SDLWindow; }

        inline int getMonitoRefreshRate() const { return m_Display[0].refresh_rate; }

        inline int getScreenWidth() const { return m_Width; }

        inline int getScreenHeight() const { return m_Height; }

        inline GameState getGameState() { return m_GameState; }

        inline int getMaxPhysicSteps() { return m_MaxPhysicSteps; }

        inline float getFixedDeltaTime() const { return m_FixedDeltaTime; }


        inline void setGameState(GameState gameState) { m_GameState = gameState; }

        inline void setShowFPS(bool value) { m_ShowFPS = value; }

#pragma endregion SET&GET

       
    };
}




