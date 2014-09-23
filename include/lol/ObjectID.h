#pragma once

namespace lol
{
	/**
	* This is the ID to reference objects in ObjectManager.
	* There are plenty of allocations in this class.
	*/
	class ObjectID
	{
	public:
		ObjectID();
		ObjectID(const ObjectID& _rhs);
		ObjectID(const ObjectID&& _rhs);
		virtual ~ObjectID();

		ObjectID& operator=(const ObjectID& _rhs);
		ObjectID& operator=(const ObjectID&& _rhs);

		bool operator==(const ObjectID& _rhs) const;

		long long GetIndex() const;
		long long GetMagic() const;

	protected:
		template <typename ObjectType>
		friend class ObjectManager;
		void SetData(long long _index, long long _magic);

	private:
		long long* m_pIndex;
		long long* m_pMagic;
	};
}