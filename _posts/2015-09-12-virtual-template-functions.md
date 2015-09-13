---
layout: post
title:  "Virtual Template Functions"
date:   2015-09-12 11:34:00
categories: fortress
tags:
- virtual
- templates
- c++
---
So I learned something new today. You can't have a virtual template function.

Let me start by explaining what I was trying to do. If you've looked at the code for Fortress, you will have seen the EntityManager class. Inside, it declares a function for every potential Component an Entity could have, i.e. all Components that are in the repository. This is time-consuming to add to and more over, it just doesn't look like a nice design. So instead I wanted to move the Components out of the EntityManager class and do something akin to this:

{% highlight C++ %}
class GameEngine {
public:
    ...
    template <class T>
    T* getComponent (EntityId entity) {
        for (ComponentBase* component : m_components[entity]) {
            T* retval = dynamic_cast<T*> (component);
            if (retval) return retval;
        }
    }
    template <class T>
    void addComponent (EntityId entity, T* component) {
        m_components[entity].insert (component);
    }
    ...
private:
    std::map<EntityId, unordered_set<ComponentBase*> m_components;
};
{% endhighlight %}

Which would then allow you to write code like this, in order to retrieve a Component for a given Entity:

{% highlight C++ %}
...
    // Given an EntityId entity
    SpriteComoponent* l_sprite = getEngine()->getComponent<SpriteComponent>(entity);
...
{% endhighlight %}

So that looks like a nice, compact solution, why can't we implement it? The problem is that I can't add the code to a class that derives from a virtual base class, which is pretty much every class in the project. Why is everything derived from an interface? Because unit testing. In order to mock all the classes (and in particular the GameEngine class) they must derived from a common interface.

So it seems like we're in a bit of a bind when it comes to implementing template functions. Perhaps the only other option would be to write a mini ComponentManager class that does nothing but the above code, though it won't be mockable.

Peter
