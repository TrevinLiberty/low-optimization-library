#pragma once

#include "ObjectID.h"

#include <map>
#include <set>
#include <list>
#include <algorithm>

namespace lol
{
	/**
	* Do you want to have an object but not own it?
	* Do you enjoy using an ID to get an object instead of using silly pointers?
	* Do you not understand pointers and want someone to deal with that?
	* Are you afraid of a lot of things?
	*
	* If you said yes to some or none of these, this manager is for you!
	*/
	template <typename ObjectType>
	class ObjectManager
	{
	public:
		ObjectManager();
		virtual ~ObjectManager();

		ObjectID CreateNewObject();
		ObjectType* GetObject(ObjectID _id) const;
		void RemoveObject(ObjectID _id);

	private:
		ObjectID CreateNewObject(long long _index) const;

		std::map<long long, ObjectType*>* m_objects;
		std::map<long long, long long>* m_magicNumbers;
		std::set<long long>* m_freeObjectIndex;
	};

	//----------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------
	template <typename ObjectType>
	ObjectManager<ObjectType>::ObjectManager()
	{
		m_objects = new std::map<long long, ObjectType*>();
		m_magicNumbers = new std::map<long long, long long>();
		m_freeObjectIndex = new std::set<long long>();
	}

	template <typename ObjectType>
	ObjectManager<ObjectType>::~ObjectManager()
	{
		for(auto it = m_objects->begin(); it != m_objects->end(); ++it)
			delete it->second;

		delete m_objects;
		delete m_magicNumbers;
		delete m_freeObjectIndex;
	}

	template <typename ObjectType>
	ObjectID lol::ObjectManager<ObjectType>::CreateNewObject()
	{
		if(!m_freeObjectIndex->empty())
		{
			const auto freeIndexIT = m_freeObjectIndex->begin();
			ObjectID newObjectID = CreateNewObject(*freeIndexIT);
			m_freeObjectIndex->erase(freeIndexIT);
			return newObjectID;
		}
		else
		{
			if(m_objects->empty())
			{
				ObjectID newObjectID = CreateNewObject(0);
				return newObjectID;
			}

			std::list<long long*>* sortedList = new std::list<long long*>();
			for(auto it = m_objects->begin(); it != m_objects->end(); it++)
			{
				sortedList->push_back(new long long(it->first));
			}

			auto comp = [](long long* _lhs, long long* _rhs)
			{
				long long* pLHS = new long long(*_lhs);
				long long* pRHS = new long long(*_rhs);

				bool bResult = *pLHS > *pRHS;

				delete pLHS;
				delete pRHS;

				return bResult;
			};

			sortedList->sort(comp);

			const auto largestIndex = sortedList->begin();
			ObjectID newObjectID = CreateNewObject(*(*largestIndex) + 1);

			for(auto it = sortedList->begin(); it != sortedList->end(); it++)
				delete *it;
			delete sortedList;

			return newObjectID;
		}
	}

	template <typename ObjectType>
	ObjectType* ObjectManager<ObjectType>::GetObject(ObjectID _id) const
	{
		const auto isInFreeListIT = m_freeObjectIndex->find(_id.GetIndex());
		if(isInFreeListIT != m_freeObjectIndex->end())
			return nullptr;

		const auto curValidMagicNumber = (*m_magicNumbers)[_id.GetIndex()];
		if(curValidMagicNumber != _id.GetMagic())
			return nullptr;

		return (*m_objects)[_id.GetIndex()];
	}

	template <typename ObjectType>
	void ObjectManager<ObjectType>::RemoveObject(ObjectID _id)
	{
		const auto isInFreeListIT = m_freeObjectIndex->find(_id.GetIndex());
		if(isInFreeListIT != m_freeObjectIndex->end())
			return;

		const auto curValidMagicNumber = (*m_magicNumbers)[_id.GetIndex()];
		if(curValidMagicNumber != _id.GetMagic())
			return;

		delete (*m_objects)[_id.GetIndex()];
		(*m_objects)[_id.GetIndex()] = nullptr;

		m_freeObjectIndex->insert(_id.GetIndex());
	}

	//----------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------
	template <typename ObjectType>
	ObjectID ObjectManager<ObjectType>::CreateNewObject(long long _index) const
	{
		long long* pIndex    = new long long(_index);
		long long* pCurMagic = new long long((*m_magicNumbers)[*pIndex]);
		long long* pNewMagic = new long long(*pCurMagic + 1);

		ObjectID newObjectID;
		newObjectID.SetData(*pIndex, *pNewMagic);
		(*m_magicNumbers)[*pIndex] = *pNewMagic;
		(*m_objects)[*pIndex] = new ObjectType();

		delete pIndex;
		delete pCurMagic;
		delete pNewMagic;

		return newObjectID;
	}
}