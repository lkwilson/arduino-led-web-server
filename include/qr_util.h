#pragma once

template<typename T, size_t NUM_LEDS>
using array_t = T[NUM_LEDS];

using millis_t = decltype(millis());

namespace PtrUtils {

template<typename T>
struct PointerGuard {
  public: // ctors
    // get resource
    PointerGuard() : m_t(nullptr) {}
    PointerGuard(T* t) : m_t(t) {}

    // non copyable
    PointerGuard(const PointerGuard& guard) = delete;
    PointerGuard& operator=(const PointerGuard& guard) = delete;

    // only movable
    PointerGuard(PointerGuard&& guard) {
      std::swap(m_t, guard.m_t);
    }
    PointerGuard& operator=(PointerGuard&& guard) {
      std::swap(m_t, guard.m_t);
      return *this;
    }
    PointerGuard& operator=(T* t) {
      if (m_t != nullptr) {
        delete m_t;
      }
      m_t = t;
      return *this;
    }

    // release resource
    ~PointerGuard() {
      if (m_t != nullptr) {
        delete m_t;
      }
    }

  public: // methods
    // Set the pointer. Deallocs current pointer if any.
    void set(const T* t) {
      if (m_t != nullptr) {
        delete m_t;
      }
      m_t = t;
    }

    // Get the pointer
    T* get() const {
      return m_t;
    }

    // Release the pointer from the guard. It must be freed manually once
    // released.
    T* release() {
      auto ptr = m_t;
      m_t = nullptr;
      return ptr;
    }

    // Dealloc the current pointer and set to nullptr.
    void clear() {
      delete m_t;
      m_t = nullptr;
    }

  public: // operators
    T& operator*() const {
      return *m_t;
    }

    T* operator->() const {
      return m_t;
    }

    operator bool() const {
      return m_t != nullptr;
    }

  private: // members
    T* m_t;
};

template<typename T, typename... Args>
PointerGuard<T> make_pointer_guard(Args&&... args) {
  return new T(std::forward<Args>(args)...);
}

} // namespace PtrUtils
