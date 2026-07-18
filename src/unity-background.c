#include "unity-background.h"

struct _UnityBackground
{
  GtkWidget parent_instance;

  UnityBackgroundSource *source;
  gulong                 changed_id;
  GdkTexture            *cache;
  int                    cache_width;
  int                    cache_height;
};

G_DEFINE_FINAL_TYPE (UnityBackground, unity_background, GTK_TYPE_WIDGET)

static void
drop_cache (UnityBackground *self)
{
  g_clear_object (&self->cache);
  self->cache_width = 0;
  self->cache_height = 0;
}

static void
on_source_changed (UnityBackgroundSource *source, gpointer user_data)
{
  UnityBackground *self = user_data;

  (void) source;

  drop_cache (self);
  gtk_widget_queue_draw (GTK_WIDGET (self));
}

static UnityBackgroundSource *
ensure_source (UnityBackground *self)
{
  if (self->source == NULL)
    {
      self->source = unity_background_source_new ();
      self->changed_id = g_signal_connect (self->source, "changed",
                                           G_CALLBACK (on_source_changed), self);
    }

  return self->source;
}

static void
unity_background_snapshot (GtkWidget *widget, GtkSnapshot *snapshot)
{
  UnityBackground *self = UNITY_BACKGROUND (widget);
  int width = gtk_widget_get_width (widget);
  int height = gtk_widget_get_height (widget);
  int scale = gtk_widget_get_scale_factor (widget);
  int device_width = width * scale;
  int device_height = height * scale;

  if (device_width <= 0 || device_height <= 0)
    return;

  if (self->cache == NULL
      || self->cache_width != device_width
      || self->cache_height != device_height)
    {
      drop_cache (self);
      self->cache = unity_background_source_render (ensure_source (self),
                                                    device_width, device_height);
      self->cache_width = device_width;
      self->cache_height = device_height;
    }

  if (self->cache != NULL)
    gtk_snapshot_append_texture (snapshot, self->cache,
                                 &GRAPHENE_RECT_INIT (0, 0, width, height));
}

static void
unity_background_dispose (GObject *object)
{
  UnityBackground *self = UNITY_BACKGROUND (object);

  g_clear_signal_handler (&self->changed_id, self->source);
  g_clear_object (&self->source);
  drop_cache (self);

  G_OBJECT_CLASS (unity_background_parent_class)->dispose (object);
}

static void
unity_background_class_init (UnityBackgroundClass *klass)
{
  G_OBJECT_CLASS (klass)->dispose = unity_background_dispose;
  GTK_WIDGET_CLASS (klass)->snapshot = unity_background_snapshot;
}

static void
unity_background_init (UnityBackground *self)
{
  (void) self;
}

GtkWidget *
unity_background_new (UnityBackgroundSource *source)
{
  UnityBackground *self = g_object_new (UNITY_TYPE_BACKGROUND, NULL);

  if (source != NULL)
    {
      self->source = g_object_ref (source);
      self->changed_id = g_signal_connect (self->source, "changed",
                                           G_CALLBACK (on_source_changed), self);
    }

  return GTK_WIDGET (self);
}
