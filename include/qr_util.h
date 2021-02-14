#pragma once

template<typename T, size_t NUM_LEDS>
using array_t = T[NUM_LEDS];

using millis_t = decltype(millis());

namespace lw {

template<typename T>
struct ptr_t {
  public: // ctors
    // get resource
    ptr_t() : m_t(nullptr) {}
    ptr_t(T* t) : m_t(t) {}

    // non copyable
    ptr_t(const ptr_t& guard) = delete;
    ptr_t& operator=(const ptr_t& guard) = delete;

    // only movable
    ptr_t(ptr_t&& guard) {
      std::swap(m_t, guard.m_t);
    }
    ptr_t& operator=(ptr_t&& guard) {
      std::swap(m_t, guard.m_t);
      return *this;
    }
    ptr_t& operator=(T* t) {
      if (m_t != nullptr) {
        delete m_t;
      }
      m_t = t;
      return *this;
    }

    // release resource
    ~ptr_t() {
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

    operator T*() && {
      return release();
    }

  private: // members
    T* m_t;
};

template<typename T, typename... Args>
ptr_t<T> make_ptr(Args&&... args) {
  return new T(std::forward<Args>(args)...);
}

} // namespace lw
