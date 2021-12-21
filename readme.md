# Connor's personnal dwm config

Welcome! this is my dwm config. dwm is a source-based tilling wm, which means to configure it you do it in the source code. This is my config which is ^^Almost all done so you can just run the commands to install it then you are good to go.

I have a [blog post](https://fediverse.blog/~/Cmm/installing-suckless's-dwm-how-it-works-and-how-to-install-my-build) on how to install this build.

In my build there are six layouts: `[=]` Tile, `[~]` Floating, `[*]` Monocle, `[@]` Spiral, `[\]` dwindle, `[M]` centered master, `[F]` floating master, `[T]` bottom stack and `[#]` grid.

I changed a few of the keybindings like: 

* the mod key is the super key.
* to close a window you press `mod + shift + q`. 
* to exit dwm you press `mod + shift  c`
* to restart dwm you press `mod + ctrl + shift + c`.
* `mod + o` opens surf in tabbed.
* `PrtSc` should do a screenshot.
* `mod + ` ` (mod + grave) will open up a quick floatig terminal.
*  You can lowerm, raise and mute the volume using there own keys (XF86XK_AudioRaiseVolume, etc.)
*  `mod + r` goes into spiral layout
*  `mod + shift + r` goes into dwindle
*  `mod + g` goes into gaps layout.
*  `mod + u` goes into centered master layout
*  `mod + shift + u` goes into floating master layout.
*  `mod + y` goes into bottom stack layout.
*  Alternatively, you can cycle the layouts using `mod + ,` / `.`.
*  `mod + y` makes the gaps smaller, `mod + =` makes them bigger, `mod + shift + =` deletes the gaps.


## Patches

I have put on all of these patches:

* actualfullscreen (to actually have fullscreen)
* alpha (to make the bar t r a n s p a r e n t)
* bar height (so that you can manually size the bar)
* par padding (to make the bar having padding if your into that)
* cyclelayouts (To scroll throught the layouts with `,` and `.`)
* hide vacant tags (so that you will only see the tags with stuff on them)
* notitle (don't show the window title in the bar)
* pertag (so that the layouts will only be for a certain tag)
* restartsig (so that you can restart dwm)
* scheme switch (to easily switch colourschemes)
* swallow (for window swallowing)
* uselessgaps (for gaps)
* wrap (for mouse warping)

