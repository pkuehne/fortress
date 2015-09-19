---
layout: post
title:  "Alpha 2 is complete!"
date:   2015-09-18 20:34:00
categories: fortress
tags:
- Alpha 2
- Progress
---

It's done! Alpha 2 is complete and with it, a huge number of improvements. Most of them behind the scenes, but there are definitely visible improvements for the player as well. The full list of issues that were closed (20!) is [here](https://github.com/pkuehne/fortress/issues?q=milestone%3A%22Alpha+2%22) but for a short overview:

* New Start Screen
* Quickstart works like the old splash->game
* Create world lets you create your own level with parameters (like number of rooms, depth, etc)
* You can now carry equipment, like swords, shields, helmets, etc
* Drop and equip/unequip items with new Equipment Window
* Weapons determine amount of damage dealt
* You can drop and pick up equipment
* UI drawing should now be snappier as well
* There is a sidebar with the command keys listed
* You can now see your health in the sidebar
* Loading and Saving! Save your game in the map and load from the start screen
* The game now starts in maximised size by default (overridable in config)
* Messages in the map view will now cut off rather than overflow, same for item descriptions

So that's a pretty nice list, not including the number of infrastructure changes that I implemented behind the scenes, such as having an actual map, making Component management easier and lots more. There's lots more to be done of course, but those items will go into the next Alpha.

Here's a sneak preview of what is planned:

* Overground terrain, linking multiple dungeons together
* More accurate FOV for the player
* More accurate pathing for enemies
* Potions to be able to replenish health
* Prefabs will be loadable from file, quickly expanding the number of monsters and items in the game

Peter
