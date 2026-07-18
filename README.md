## unity-backgrounds

library for drawing the desktop wallpaper for use in unity-shell.

It wraps [GnomeBG](https://gitlab.gnome.org/GNOME/gnome-desktop) and exposes two
objects:

- **`UnityBackgroundSource`**: reads `org.gnome.desktop.background`, follows `color-scheme` key, and renders the wallpaper to texture.
- **`UnityBackground`**: draws a source at its own size and scale factor. Fills whatever it is given; repaints when the source changes.

The widget and source are separate so one source can drive several widgets — the
same wallpaper on every monitor.

### build

install the deps:

- `gtk4` (>= 4.22)
- `gio-2.0`
- `gnome-bg-4`
- `gsettings-desktop-schemas`
- `gdk-pixbuf-2.0`
- `meson`

```sh
meson setup build
ninja -C build
sudo meson install -C build
```

### docs

<https://unity-shell.github.io/unity-backgrounds/>
