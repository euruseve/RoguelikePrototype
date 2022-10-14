#pragma once

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <bitset>

class Entity;
class Component;
class Manager;

constexpr size_t MAX_COMPONENTS = 32;
constexpr size_t MAX_GROUPS = 32;

using ComponentId = size_t;
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

using Group = size_t;
using GroupBitSet = std::bitset<MAX_GROUPS>;

inline ComponentId GetNewComponentTypeId()
{
	static ComponentId lastId = 0u;
	return lastId++;
}

template<typename T> 
inline ComponentId GetComponentTypeId() noexcept
{
	static ComponentId typeId = GetNewComponentTypeId();
	return typeId;
}

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
public:

	Entity(Manager& mManager) : manager(mManager) {}

	void Update()
	{
		for (auto& c : components)
			c->Update();
	}

	void Draw()
	{
		for (auto& c : components)
			c->Draw();
	}

	void Destroy() { active = false; }	

	bool IsActive() const { return active; }

	bool HasGroup(Group mGroup) { return groupBitSet[mGroup]; }


	void AddGroup(Group mGroup);

	void DeleteGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template<typename T>
	bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeId<T>()];
	}

	template<typename T, typename ... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeId<T>()] = c;
		componentBitSet[GetComponentTypeId<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T>
	T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeId<T>()]);
		return *static_cast<T*>(ptr);
	}



private:
	Manager& manager;

	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

	GroupBitSet groupBitSet;
};

class Manager
{
public:

	void Update()
	{
		for (auto& e : entities)
			e->Update();
	}

	void Draw()
	{
		for (auto& e : entities)
			e->Draw();
	}

	void Refresh()
	{
		for (auto i(0u); i < MAX_GROUPS; i++)
		{
			auto& v(groupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v),
				[&](Entity* mEntity)
				{
					return !mEntity->IsActive() || !mEntity->HasGroup(i);
				}),
				std::end(v)
			);
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
		std::end(entities)
		);
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& GetGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };

		entities.emplace_back(std::move(uPtr));

		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> groupedEntities;
};