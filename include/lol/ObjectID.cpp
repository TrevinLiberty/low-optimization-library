#include "ObjectID.h"

namespace lol
{
	ObjectID::ObjectID()
		: m_pIndex(new long long()),
		  m_pMagic(new long long())
	{
		long long* defaultIndex = new long long(0);
		long long* defaultMagic = new long long(0);

		*m_pIndex = *defaultIndex;
		*m_pMagic = *defaultMagic;

		delete defaultIndex;
		delete defaultMagic;
	}

	ObjectID::ObjectID(const ObjectID& _rhs)
		: m_pIndex(new long long()),
		  m_pMagic(new long long())
	{
		*m_pIndex = *_rhs.m_pIndex;
		*m_pMagic = *_rhs.m_pMagic;
	}

	ObjectID::ObjectID(const ObjectID&& _rhs)
		: m_pIndex(new long long()),
		  m_pMagic(new long long())
	{
		*m_pIndex = *_rhs.m_pIndex;
		*m_pMagic = *_rhs.m_pMagic;
	}

	ObjectID::~ObjectID()
	{
		delete m_pIndex;
		delete m_pMagic;
	}

	ObjectID& ObjectID::operator=(const ObjectID& _rhs)
	{
		delete m_pIndex;
		delete m_pMagic;

		m_pIndex = new long long();
		m_pMagic = new long long();

		*m_pIndex = *_rhs.m_pIndex;
		*m_pMagic = *_rhs.m_pMagic;

		return *this;
	}

	ObjectID& ObjectID::operator=(const ObjectID&& _rhs)
	{		
		delete m_pIndex;
		delete m_pMagic;

		m_pIndex = new long long();
		m_pMagic = new long long();

		*m_pIndex = *_rhs.m_pIndex;
		*m_pMagic = *_rhs.m_pMagic;

		return *this;
	}

	bool ObjectID::operator==(const ObjectID& _rhs) const
	{
		long long* indexA = new long long(*m_pIndex);
		long long* indexB = new long long(*_rhs.m_pIndex);
		long long* magicA = new long long(*m_pMagic);
		long long* magicB = new long long(*_rhs.m_pMagic);

		bool result = false;
		if((*indexA == *indexB) && (*indexB == *indexA) && (*magicA == *magicB) && (*magicB == *magicA))
			result = true;

		delete indexA;
		delete indexB;
		delete magicA;
		delete magicB;

		return result;
	}

	long long ObjectID::GetIndex() const
	{
		return *m_pIndex;
	}

	long long ObjectID::GetMagic() const
	{
		return *m_pMagic;
	}

	//----------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------
	void ObjectID::SetData(long long _index, long long _magic)
	{
		delete m_pIndex;
		delete m_pMagic;

		m_pIndex = new long long(_index);
		m_pMagic = new long long(_magic);
	}
}