# 🎮 Atari’s GC Simple Render

*A barebones fork of GC-simple-render, aiming to provide several hotfixes and PRs to bother the original team’s DevOps 😇*

Welcome to Atari’s GC Simple Render, our fork of the original GC-simple-render, lovingly fixed, cleaned up, and upgraded by the Atari class. (It’s a lie)
This version keeps the same base but adds several quality-of-life hotfixes, without actually touching any of the structure or rendering backend. (It’s a bit like in Sea of Thieves, when you stick wooden planks to your ship to repair it.. but with a rendering library.)

---

## ✨ What’s New & Improved

Here’s what our fork adds on top of the original:

* 🧾 **Fixed text rendering**
  Text & fonts are now separated, and you can set the font after creating the object.

* 🧩 **Unified namespace aliases**
  Useful objects from the `gce::` namespace are now also accessible under the `sr::` namespace for better clarity.

* 🏗️ **Custom geometry loading (OBJ support!)**
  Use your own `.obj` models directly using the `sr::CustomGeometry` for 200% more coolness!

* 💡 **Customizable lighting system**
  Add and configure multiple light sources with custom colors, intensities, and directions, instead of only having access to the default one.

* ⚙️ **Window parameter flags**
  Easily toggle render passes (shadows, anti-aliasing, you get it..) through simple flags.

* ⏱️ **Built-in `deltaTime` method**
  Automatically provides last-frame delta time, no need for manual calculation (crazy stuff, I know).

* 🖱️ **"Improved" mouse input handling**
  Includes a new method for retrieving mouse delta (groundbreaking, I know).

---

## 🧠 Why This Exists

This fork was made because we needed to use the library for a school project, but it was in an early stage (shout out to all the people who worked on it, you did an amazing job for one week of work). So we thought we’d make some changes to be able to work more comfortably with it.

---

## ⚡ Credits

* Huge shout-out to the original author of the lib: @MithanielVillard
* As well as all the people who worked on the GC-Engine project :)
* Forked & improved by **Atari class**, with <3 and brainrot
* Special thanks to @AymericMATTE for sacrificing his weekend to help :)

---