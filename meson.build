project(
  'unity-backgrounds',
  'c',
  version: '26',
  meson_version: '>= 1.0',
  default_options: [
    'c_std=gnu11',
    'warning_level=2',
  ],
)

add_project_arguments('-DGNOME_DESKTOP_USE_UNSTABLE_API', language: 'c')

dep_gtk = dependency('gtk4', version: '>= 4.22')
dep_gio = dependency('gio-2.0')
dep_gnomebg = dependency('gnome-bg-4')
dep_gsd = dependency('gsettings-desktop-schemas')
dep_pixbuf = dependency('gdk-pixbuf-2.0')

subdir('src')
