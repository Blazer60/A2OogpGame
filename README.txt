SDL2 Game | OOGP A2 Assignment

A Bullet Hell type of game using SDL2 and GLM libraries. Collisions are handled though a Quad Tree system that can
handle up to 5,000 (depending on your PC specs). There is a single boss, Mecha Chad, that pursuits you with multiple
attacks. There are four types of projectile they can use: basic, momentum, hexed (cursed) and ricochet projectiles.

Project Dependencies

The project uses:
- GLM
- SDL2
- SDL Image
- SDL Mixer
- SDL TTF

All dependencies can be found in the Vendor Folder. The project can be built in either x86 mode or
amd64 mode. This can be set by using CMakeLists.txt to toggle between the two. The project may only be built using msvc
on windows. No other platforms or compilers have be implemented or tested.

How to Play

In the game:
- Move - wasd
- Dodge - space + wasd or space
- Pause - p
- Change Music - zero
- Quit - Esc

Most menus will tell you the controls.