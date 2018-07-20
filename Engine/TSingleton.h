#pragma once

#include <assert.h>

namespace Engine {

    template <class T> class TSingleton
    {
        static T* m_istance;

        TSingleton(const TSingleton<T>& copy) = delete;
        TSingleton<T>& operator=(const TSingleton<T>& copy) = delete;

    public:

        TSingleton() {
            assert(m_istance == nullptr);
            m_istance = static_cast <T*> (this);
        }

        static T* GetSingleton()
        {
            if (m_istance != nullptr) {
                return m_istance;
            }
        }

        ~TSingleton() {
            if (m_istance != nullptr) {
                m_istance = 0;
            }
        }

    };

    template <typename T> T* TSingleton <T>::m_istance = 0;

}


