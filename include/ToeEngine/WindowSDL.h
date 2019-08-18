#pragma once

#include "System.h"
#include "Message.h"
#include "Engine.h"
#include "Includes.h"

namespace ToeEngine
{
  namespace Systems
  {
    class WindowSDL : public System
    {
    public:
      WindowSDL();

      void Init();
      void Update(float dt);
      void Shutdown();

      // Mouse functions
      bool GetMouseTriggered();
      bool GetMouseReleased();
      glm::vec2 GetMousePosition();

      void ToggleFullscreen();
      void NewFrame();
      void EndFrame();
      int GetWindowHeight() { return m_height; }
      int GetWindowWidth() { return m_width; }

      void SendMsg(EntityPtr e1, EntityPtr e2, Message::Message msg);

    private:

      // struct for mouse status
      struct SDLMouse
      {
        glm::vec2 pos;
        bool pressed;
        bool released;
        bool triggered;
      };
      
      void PollEvents(); // Calls three functions below
      void PollWindowEvent(SDL_Event& currEvent);
      void PollKeyEvent(SDL_Event& currEvent);
      void PollMouseEvent(SDL_Event& currEvent);

      typedef Uint32 eventType;

      void PushSDLEvent(eventType type);

      SDL_Window* m_window;
      SDL_GLContext m_context; // OpenGL context (not sure if we will use it)
      SDL_Event m_event; // For SDL event
      bool m_isFullscreen;
      int m_width;
      int m_height;
      SDLMouse m_mouse;
    };

    typedef std::shared_ptr<WindowSDL> WindowSDLPtr;
  }
}