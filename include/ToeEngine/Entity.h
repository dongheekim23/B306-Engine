#pragma once

#include "Component.h"
#include "Includes.h"

namespace ToeEngine
{
  class Entity
  {
  public:
    void AddComponent(ComponentPtr component);

    void RemoveComponent(EnumeratedComponent ec);

    bool HasComponent(EnumeratedComponent ec) const;

    mask GetMask() const;

    // Check if this entity has all the components in the input mask
    bool CheckMask(mask m);

    const std::string& Name()
    {
      return m_name;
    }

    void SetName(std::string name)
    {
      m_name = name;
    }

#define GET_COMPONENT(type) GetCompoent<type>(EC_##type)

    template <typename T>
    std::shared_ptr<T> GetComponent(EnumeratedComponent ec);

  private:
    std::string m_name;
    mask m_mask = MC_Alive;
    ComponentPtr m_components[EC_Count];
  };

  typedef std::shared_ptr<Entity> EntityPtr;
  typedef std::vector<EntityPtr> EntityVec;
}