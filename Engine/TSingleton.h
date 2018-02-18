#pragma once


namespace Engine {

    template <class T> class TSingleton
    {
        static T* m_istance;

        //TSingleton() {}

    public:

        TSingleton() {
            if (m_istance == nullptr) {
                //If the class T inherit TSingleton
                m_istance = static_cast <T*> (this);
            }   
        }

        static T* GetSingleton()
        {
            if (m_istance != nullptr) {
                return m_istance;
            }
        }

        //static T* GetSingleton()
        //{
        //    if (m_istance == nullptr) {
        //        m_istance = new T();
        //    }
        //    return m_istance;
        //}

        ~TSingleton() {
            if (m_istance != nullptr) {
                m_istance = 0;
            }
        }

    };

    template <typename T>
    T* TSingleton <T>::m_istance = 0;

}


