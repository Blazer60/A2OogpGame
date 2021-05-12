[GameImage]: mainImage.jpg "Mecha Chad firing Ricochet projectiles."
[VendorFolder]: vendor "Vendor Folder"
[GLM]: https://github.com/g-truc/glm "GLM Github page"
[SDL2]: https://github.com/libsdl-org/SDL "SDL Github page"
[SDLImage]: https://github.com/libsdl-org/SDL_image "SDL Image Github page"
[SDLMixer]: https://github.com/SDL-mirror/SDL_mixer "SDL Mixer Github page"
[SDLTtf]: https://github.com/SDL-mirror/SDL_ttf "SDL TTF Github page"

# SDL2 Game | OOGP A2 Assignment
![GameImage]
---
A Bullet Hell type of game using SDL2 and GLM libraries. Collisions are handled though a Quad Tree system that can
handle up to 5,000 (depending on your PC specs). There is a single boss, Mecha Chad, that pursuits you with multiple
attacks. There are four types of projectile they can use: basic, momentum, hexed (cursed) and ricochet projectiles.

## Project Dependencies
The project uses:
- [GLM][GLM]
- [SDL2][SDL2]
- [SDL Image][SDLImage]
- [SDL Mixer][SDLMixer]
- [SDL TTF][SDLTtf]

All dependencies can be found in the [Vendor folder][VendorFolder]. The project can be built in either x86 mode or
amd64 mode. This can be set by using CMakeLists.txt to toggle between the two. The project may only be built using msvc
on windows. No other platforms or compilers have be implemented or tested.

## How to Play
In the game:
- Move - wasd
- Dodge - space + wasd or space
- Pause - p
- Change Music - zero
- Quit - Esc

Most menus will tell you the controls.

## References
All of the following are sfx & music that can be found in the game.
1. Zapsplat, Shuriken, throwing star, kung fu weapon throw 2 [online]. Available from: https://www.zapsplat.com/music/shuriken-throwing-star-kung-fu-weapon-throw-2/ [Accessed 3 May 2021]
1. Free Music Archive, Dreamworld, Feel The Power [online]. Available from: https://freemusicarchive.org/music/Dreamworld/Best_Bytes_Volume_3/13_-_Dreamworld_-_Feel_The_Power [Accessed 3 May 2021]
1. Zapsplat, Science fiction, cyberpunk equipment, activate, ascending beep 2 [online]. Available from: https://www.zapsplat.com/music/science-fiction-cyberpunk-equipment-activate-ascending-beep-2/ [Accessed 6 May 2021]
1. Zapsplat, Game sound, positive, warm and bright bell mallet tone, short 3 [online]. Available from: https://www.zapsplat.com/music/game-sound-positive-warm-and-bright-bell-mallet-tone-short-3/ [Accessed 6 May 2021]
1. Zapsplat, Game sound, positive, warm and bright bell mallet tone, short 2 [online]. Available from: https://www.zapsplat.com/music/game-sound-positive-warm-and-bright-bell-mallet-tone-short-2/ [Accessed 6 May 2021]
1. Zapsplat, Sawsquarenoise, Dojokratos Album [online]. Available from: https://freemusicarchive.org/music/sawsquarenoise/dojokratos [Accessed 9 May 2021]
1. Zapsplat, Science fiction, cyberpunk, robot, metallic hit, fizz into a beep, chirp [online]. Available from: https://www.zapsplat.com/music/science-fiction-cyberpunk-robot-metallic-hit-fizz-into-a-beep-chirp/ [Accessed 9 May 2021]
1. Zapsplat, Weapon or other object throw, whoosh and spin thorough air. Version 2 [online] Available from: https://www.zapsplat.com/music/science-fiction-cyberpunk-robot-metallic-hit-fizz-into-a-beep-chirp/ [Accessed 9 May 2021]
1. Zapsplat, Science fiction laser hit, impact with a thud 1 [online]. Available from: https://www.zapsplat.com/music/science-fiction-laser-hit-impact-with-a-thud-1/ [Accessed 9 May 2021]
1. Zapsplat, Bow and arrow, bow elastic release, ping, shoot 2 [online]. Available from: https://www.zapsplat.com/music/bow-and-arrow-bow-elastic-release-ping-shoot-2/ [Accessed 9 May 2021]
1. Zapsplat, Science fiction, robot power up [online]. Available from: https://www.zapsplat.com/music/science-fiction-robot-power-up/ [Accessed 9 May 2021]
1. Zapsplat, Science function, cyberpunk, robot, fast ascending beep, chirp 2 [online]. Available from: https://www.zapsplat.com/music/science-fiction-cyberpunk-robot-fast-ascending-beep-chirp-2/ [Accessed 9 May 2021]
1. Zapsplat, Sci-fi large robot, futuristic robotic swell, morph, transition 25 [online]. Available from: https://www.zapsplat.com/music/sci-fi-large-robot-futuristic-robotic-swell-morph-transition-25/ [Accessed 9 May 20201]
1. Zapsplat, Science fiction, cyberpunk robot power surge, short 5 [online]. Available from: https://www.zapsplat.com/music/science-fiction-cyberpunk-robot-power-surge-short-5/ [Accessed 9 May 2021]
