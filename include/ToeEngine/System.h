#pragma once

#include "Component.h"
// EntityPtr, EntityVec
#include "Entity.h"
#include "Message.h"
#include "Includes.h"

namespace ToeEngine
{
  enum EnumeratedSystem
  {
    ES_WindowSDL,
    ES_Movement,

    ES_Count
  };

  typedef EnumeratedSystem ESys;

  class System
  {
  public:
    System(std::string name, ESys es)
      : m_name(name), 
      m_type(es), 
      m_mask(MC_Alive)
    {
    }

    // To call proper destructor of a derived class
    virtual ~System() {}

    // Let derived class handle them...
    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Shutdown() = 0;

    // This is not pure virtual since sending message is optional
    virtual void SendMsg(EntityPtr e1, EntityPtr e2, Message::Message msg) {}

    // Specify which component should be used for this system
    void RegisterComponent(BitfieldComponent bc)
    {
      m_mask |= bc;
    }

    inline mask GetMask() { return m_mask; }

    friend class Space;
    friend class Engine;

  protected:
    std::string m_name;
    ESys m_type;
    mask m_mask;
    EntityVec m_entityVec;

  private:
    // Default constructor not allowed
    System() = delete;
  };

  typedef std::shared_ptr<System> SystemPtr;
  typedef std::vector<SystemPtr> SystemVec;
}