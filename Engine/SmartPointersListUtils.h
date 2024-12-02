#pragma once

namespace SmartPointersListUtils
{
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using weak_ptr = std::weak_ptr<T>;
	template<typename T> using shared_ptr = std::shared_ptr<T>;
	template<typename T> using list = std::list<T>;

	template<typename T>
	bool WeakPtrListContainsShared(const list<weak_ptr<T>>& list, const shared_ptr<T>& sharedPtr)
	{
		for (const auto& weakItem : list)
			if (auto sharedItem = weakItem.lock())
				if (sharedItem == sharedPtr)
					return true;

		return false;
	}

	template<typename T>
	void RemoveWeakPointerFromList(list<weak_ptr<T>>& weakList, const weak_ptr<T>& targetWeak)
	{
		shared_ptr<T> target = targetWeak.lock();
		if (target == nullptr)
			return;

		for (auto itWeak = weakList.begin(); itWeak != weakList.end(); ++itWeak)
		{
			if (auto it = itWeak->lock())
				if (it == target)
				{
					weakList.erase(itWeak);
					return;
				}
		}
	}
}