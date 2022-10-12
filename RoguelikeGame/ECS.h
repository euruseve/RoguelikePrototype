#pragma once

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <bitset>

class Entity;
class Component;

constexpr size_t maxComponents = 32;

using ComponentId = size_t;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentId GetComponentTypeId()
{
	static ComponentId lastId = 0;
	return lastId++;
}

template<typename T> 
inline ComponentId GetComponentTypeId() noexcept
{
	static ComponentId typeId = GetComponentTypeId();
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

	void Update()
	{
		for (auto& c : components)
			c->Update();

		for (auto& c : components)
			c->Draw();
	}

	void Draw(){}

	void Destroy() { active = false; }	

	bool IsActive() const { return active; }

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
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
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
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
		std::end(entities)
		);
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };

		entities.emplace_back(std::move(uPtr));

		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
};