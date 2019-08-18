#pragma once

#include "Includes.h"
#include "Space.h"
#include "Message.h"
#include "WindowSDL.h"

namespace ToeEngine
{
  class Engine
  {
  public:
    Engine();

    void Init();
    void Update();
    void Shutdown();

    // Used to send out messages to all the systems and current game state
    void SendMsg(EntityPtr e1, EntityPtr e2, Message::Message msg);

    SpacePtr CreateSpace(std::string name);
    SpacePtr GetSpace(std::string name);
    SpacePtr SetActiveSpace(std::string name);
    SpacePtr GetActiceSpace();
    bool SpaceExists(std::string name);
    
    float GetDT() { return m_dt; }
    void Stop() { m_running = false; }

    template <typename T>
    std::shared_ptr<T> GetSystem(EnumeratedSystem sysType);

  private:

    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;

    float m_dt;
    timePoint m_start;

    bool m_running;

    SystemVec m_systemVec;
  };

#define GETSYS(sysType) ENGINE->GetSystem<sysType>(ES_##sysType)
}