#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define UNITY_TYPE_BACKGROUND_SOURCE (unity_background_source_get_type ())

G_DECLARE_FINAL_TYPE (UnityBackgroundSource, unity_background_source, UNITY, BACKGROUND_SOURCE, GObject)

UnityBackgroundSource *unity_background_source_new (void);

GdkTexture *unity_background_source_render (UnityBackgroundSource *self,
                                            int                    width,
                                            int                    height);

gboolean unity_background_source_has_wallpaper (UnityBackgroundSource *self);

G_END_DECLS
