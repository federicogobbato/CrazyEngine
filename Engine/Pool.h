#pragma once

#include <vector>
#include <iostream>

namespace Engine {

	template <class Object>
	class Pool;

	template <class Object>
	class PoolObject {
		Object* Element;
		PoolObject* NextElement = nullptr;
		bool state = true;
	public:
		Object* getElement() {
			return Element;
		}

		friend class Pool<Object>;
	};

	template <class Object>
	class Pool {
		std::vector<PoolObject<Object>*> m_Elements;
		PoolObject<Object>* m_NextFreeElement;

	public:
		Pool();
		Pool(int size);

		void addElement(Object* newObject);

		~Pool() {
			for each (auto it in m_Elements) {
				delete it;
			}
		}

		PoolObject<Object>* getElement();
		void returnElement(PoolObject<Object>* element);

		std::vector<PoolObject<Object>*>& getElements() {
			return m_Elements;
		}
	};


	template <class Object>
	Pool<Object>::Pool():
		m_NextFreeElement(nullptr)
	{}

	template <class Object>
	Pool<Object>::Pool(int size) : m_NextFreeElement(nullptr)
	{
		if (size > 0) {
			PoolObject<Object>* newElement = new PoolObject<Object>;
			m_Elements.push_back(newElement);

			for (int i = 1; i < size; i++) {
				PoolObject<Object>* newElement = new PoolObject<Object>;
				m_Elements.push_back(newElement);
				m_Elements[i - 1]->NextElement = m_Elements[i];
			}
		}
	};


	template <class Object>
	void Pool<Object>::addElement(Object* newObject) {
		PoolObject<Object>* newElement = new PoolObject<Object>;
		newElement->Element = newObject;
		if (m_NextFreeElement == nullptr) {
			m_Elements.push_back(newElement);
			m_NextFreeElement = newElement;
		}
		else
		{
			PoolObject<Object>* prevNextElement = m_Elements.back()->NextElement;
			m_Elements.back()->NextElement = newElement;
			m_Elements.push_back(newElement);
			newElement->NextElement = prevNextElement;
		}	
	}


	template <class Object>
	PoolObject<Object>* Pool<Object>::getElement() {
		if (m_NextFreeElement != nullptr) {
			PoolObject<Object>* element = m_NextFreeElement;
			m_NextFreeElement = m_NextFreeElement->NextElement;
			element->state = false;
			return element;
		}
		return nullptr;
	};

	template <class Object>
	void Pool<Object>::returnElement(PoolObject<Object>* element) {
		element->state = true;
		PoolObject<Object>* prevNextElement = m_NextFreeElement;
		m_NextFreeElement = element;
		m_NextFreeElement->NextElement = prevNextElement;
	};

}



	

	
	
	