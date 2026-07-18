#include "unity-background-source.h"

#include <gdesktop-enums.h>
#include <gnome-bg/gnome-bg.h>

#define BACKGROUND_SCHEMA_ID "org.gnome.desktop.background"
#define INTERFACE_SCHEMA_ID  "org.gnome.desktop.interface"
#define PICTURE_URI_KEY      "picture-uri"
#define PICTURE_URI_DARK_KEY "picture-uri-dark"
#define COLOR_SCHEME_KEY     "color-scheme"

struct _UnityBackgroundSource
{
  GObject parent_instance;

  GnomeBG   *bg;
  GSettings *background_settings;
  GSettings *interface_settings;
};

enum
{
  CHANGED,
  N_SIGNALS
};

static guint signals[N_SIGNALS];

G_DEFINE_FINAL_TYPE (UnityBackgroundSource, unity_background_source, G_TYPE_OBJECT)

static void
reload (UnityBackgroundSource *self)
{
  gboolean dark;
  const char *key;
  g_autofree char *uri = NULL;
  g_autofree char *path = NULL;

  gnome_bg_load_from_preferences (self->bg, self->background_settings);

  if (gnome_bg_get_placement (self->bg) == G_DESKTOP_BACKGROUND_STYLE_NONE)
    return;

  dark = g_settings_get_enum (self->interface_settings, COLOR_SCHEME_KEY)
         == G_DESKTOP_COLOR_SCHEME_PREFER_DARK;
  key = dark ? PICTURE_URI_DARK_KEY : PICTURE_URI_KEY;

  uri = g_settings_get_string (self->background_settings, key);
  if (uri != NULL && *uri != '\0')
    path = g_filename_from_uri (uri, NULL, NULL);
  if (path != NULL)
    gnome_bg_set_filename (self->bg, path);
}

GdkTexture *
unity_background_source_render (UnityBackgroundSource *self, int width, int height)
{
  GdkPixbuf *pixbuf;
  int rowstride;
  g_autoptr (GBytes) bytes = NULL;

  g_return_val_if_fail (UNITY_IS_BACKGROUND_SOURCE (self), NULL);
  g_return_val_if_fail (width > 0 && height > 0, NULL);

  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, width, height);
  gnome_bg_draw (self->bg, pixbuf);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  bytes = g_bytes_new_with_free_func (gdk_pixbuf_get_pixels (pixbuf),
                                      (gsize) rowstride * height,
                                      g_object_unref, pixbuf);

  return gdk_memory_texture_new (width, height, GDK_MEMORY_R8G8B8, bytes, rowstride);
}

gboolean
unity_background_source_has_wallpaper (UnityBackgroundSource *self)
{
  g_return_val_if_fail (UNITY_IS_BACKGROUND_SOURCE (self), FALSE);

  return gnome_bg_get_placement (self->bg) != G_DESKTOP_BACKGROUND_STYLE_NONE;
}

static void
on_settings_changed (GSettings *settings, char *key, gpointer user_data)
{
  UnityBackgroundSource *self = user_data;

  (void) settings;
  (void) key;

  reload (self);
  g_signal_emit (self, signals[CHANGED], 0);
}

static void
on_bg_changed (GnomeBG *bg, gpointer user_data)
{
  UnityBackgroundSource *self = user_data;

  (void) bg;

  g_signal_emit (self, signals[CHANGED], 0);
}

static void
unity_background_source_dispose (GObject *object)
{
  UnityBackgroundSource *self = UNITY_BACKGROUND_SOURCE (object);

  g_clear_object (&self->bg);
  g_clear_object (&self->background_settings);
  g_clear_object (&self->interface_settings);

  G_OBJECT_CLASS (unity_background_source_parent_class)->dispose (object);
}

static void
unity_background_source_class_init (UnityBackgroundSourceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose = unity_background_source_dispose;

  signals[CHANGED] = g_signal_new ("changed", G_TYPE_FROM_CLASS (klass),
                                   G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL,
                                   G_TYPE_NONE, 0);
}

static void
unity_background_source_init (UnityBackgroundSource *self)
{
  self->bg = gnome_bg_new ();
  self->background_settings = g_settings_new (BACKGROUND_SCHEMA_ID);
  self->interface_settings = g_settings_new (INTERFACE_SCHEMA_ID);

  g_signal_connect (self->background_settings, "changed",
                    G_CALLBACK (on_settings_changed), self);
  g_signal_connect (self->interface_settings, "changed::" COLOR_SCHEME_KEY,
                    G_CALLBACK (on_settings_changed), self);
  g_signal_connect (self->bg, "changed", G_CALLBACK (on_bg_changed), self);
  g_signal_connect (self->bg, "transitioned", G_CALLBACK (on_bg_changed), self);

  reload (self);
}

UnityBackgroundSource *
unity_background_source_new (void)
{
  return g_object_new (UNITY_TYPE_BACKGROUND_SOURCE, NULL);
}
