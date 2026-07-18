dependency('gi-docgen', version: '>= 2021.1',
           fallback: ['gi-docgen', 'dummy_dep'],
           native: true,
           required: get_option('documentation'))

gidocgen = find_program('gi-docgen')

doc_toml = configure_file(
  input: 'unity-backgrounds.toml.in',
  output: 'unity-backgrounds.toml',
  configuration: {'VERSION': meson.project_version()},
)

custom_target('unity-backgrounds-doc',
  input: [doc_toml, unity_backgrounds_gir[0]],
  output: 'unity-backgrounds',
  command: [
    gidocgen,
    'generate',
    '--quiet',
    '--no-namespace-dir',
    '--config=@INPUT0@',
    '--output-dir=@OUTPUT@',
    '--content-dir=@0@'.format(meson.current_source_dir()),
    '@INPUT1@',
  ],
  depend_files: files('urlmap.js'),
  build_by_default: true,
  install: true,
  install_dir: datadir / 'doc',
)

test('doc-check',
  gidocgen,
  args: [
    'check',
    '--config=@0@'.format(doc_toml),
    '--add-include-path=@0@'.format(meson.current_build_dir() / '../src'),
    unity_backgrounds_gir[0],
  ],
  depends: unity_backgrounds_gir[0],
  suite: 'doc',
)
