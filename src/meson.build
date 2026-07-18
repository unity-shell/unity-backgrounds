unity_backgrounds_deps = [
  dep_gtk,
  dep_gio,
  dep_gnomebg,
  dep_gsd,
  dep_pixbuf,
]

unity_backgrounds_sources = [
  'unity-background-source.c',
  'unity-background.c',
]

unity_backgrounds_headers = [
  'unity-background-source.h',
  'unity-background.h',
]

unity_backgrounds_lib = library(
  'unity-backgrounds',
  unity_backgrounds_sources,
  dependencies: unity_backgrounds_deps,
  include_directories: include_directories('.'),
  version: meson.project_version(),
  soversion: '0',
  install: true,
)

install_headers(unity_backgrounds_headers, subdir: 'unity-backgrounds')

unity_backgrounds_dep = declare_dependency(
  link_with: unity_backgrounds_lib,
  include_directories: include_directories('.'),
  dependencies: unity_backgrounds_deps,
)

pkg = import('pkgconfig')
pkg.generate(
  unity_backgrounds_lib,
  name: 'unity-backgrounds',
  description: 'Unity desktop background renderer',
  subdirs: 'unity-backgrounds',
  requires: [dep_gtk, dep_gnomebg],
)

build_gir = get_option('introspection').allowed()
unity_backgrounds_gir = []
if build_gir
  unity_backgrounds_gir = gnome.generate_gir(
    unity_backgrounds_lib,
    sources: unity_backgrounds_sources + unity_backgrounds_headers,
    namespace: 'Unity',
    nsversion: '0.1',
    identifier_prefix: 'Unity',
    symbol_prefix: 'unity',
    export_packages: 'unity-backgrounds',
    includes: ['GObject-2.0', 'Gtk-4.0'],
    dependencies: unity_backgrounds_deps,
    header: 'unity-background.h',
    install: true,
  )
endif
