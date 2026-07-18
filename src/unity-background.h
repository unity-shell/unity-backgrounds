#pragma once

#include <gtk/gtk.h>

#include "unity-background-source.h"

G_BEGIN_DECLS

#define UNITY_TYPE_BACKGROUND (unity_background_get_type ())

G_DECLARE_FINAL_TYPE (UnityBackground, unity_background, UNITY, BACKGROUND, GtkWidget)

GtkWidget *unity_background_new (UnityBackgroundSource *source);

G_END_DECLS
