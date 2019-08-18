#include "Entity.h"

namespace ToeEngine
{
  void Entity::AddComponent(ComponentPtr component)
  {
    m_components[component->m_type] = component;

    m_mask |= component->m_mask;


  }

  void Entity::RemoveComponent(EnumeratedComponent ec)
  {
    if (m_components[ec])
    {
      m_mask &= ~(m_components[ec]->m_mask);

      m_components[ec].reset();
    }
  }

  bool Entity::HasComponent(EnumeratedComponent ec) const
  {
    return static_cast<bool>(m_components[ec]);
  }

  mask Entity::GetMask() const
  {
    return m_mask;
  }

  bool Entity::CheckMask(mask m)
  {
    return ((m_mask & m) == m);
  }

  template <typename T>
  std::shared_ptr<T> Entity::GetComponent(EnumeratedComponent ec)
  {
    assert(m_components[ec]);
    return std::static_pointer_cast<T>(m_components[ec]);
  }
}