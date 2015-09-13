---
layout: post
title:  "Breaking out the Generator"
date:   2015-09-13 20:34:00
categories: fortress
tags:
- design
- worldgen
- generator
- Alpha 2
---

If you read my previous update, I ended up going with the idea I postulated at the end. Create a non-derived class which will hold all the Components. It works rather well, and except for three very annoying and hard to track down bugs, it went pretty smoothly. Components can now be added on the fly, as long as they derive from the ComponentBase. Similarly they can be removed and retrieved by simply using the type. This should make it easier to implement new Components in the future.

This post is more about the Generator that's currently creating the levels. It works fine for the moment, but I want to let players chose the parameters of the levels (and later on, the world as a whole). So for this I'm breaking the Generator out of the GameEngine itself. Rather than the engine creating the levels when it comes up, the Generator should be independent (apart from calling the engine to create Entities).

After this, I can create a new screen, where the player can set the parameters for the levels. These currently only consist of width, height, number of rooms and orc density. This should suffice though to make easier or harder levels to suit the player.

As of writing, I've done some work on the screen for chosing, though there's plenty of work still left before I can hook it up to the Generator, which I also still need to break out. After that Generator work will mostly focus on providing a) different types of dungeons b) Overground levels of different biomes c) An entire world of these biomes with potentially hundreds of levels. That's the dream anyway. We'll need some little things, like loading and saving of Entities to make this work as well.

Once that's done, we're pretty close to the release of [Alpha 2](https://github.com/pkuehne/fortress/milestones/Alpha%202).
