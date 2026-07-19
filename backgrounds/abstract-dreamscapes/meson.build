abstract_dreamscapes_dir = datadir / 'backgrounds' / 'abstract-dreamscapes'

# pcolor uses the dark variant's dominant tone as the solid fallback color
# shown while the image loads.
abstract_dreamscapes_wallpapers = [
  ['bloom', 'Abstract Dreamscapes Bloom', '#814F4A'],
  ['bw', 'Abstract Dreamscapes Black and White', '#171717'],
  ['cone', 'Abstract Dreamscapes Cone', '#322737'],
  ['curve', 'Abstract Dreamscapes Curve', '#6D5556'],
  ['helical', 'Abstract Dreamscapes Helical', '#665F76'],
]

abstract_dreamscapes_images = []
foreach w : abstract_dreamscapes_wallpapers
  abstract_dreamscapes_images += 'abstract-dreamscapes-' + w[0] + '.png'
  abstract_dreamscapes_images += 'abstract-dreamscapes-' + w[0] + '-dark.png'
endforeach

install_data(abstract_dreamscapes_images, install_dir: abstract_dreamscapes_dir)
install_data('LICENSE', install_dir: abstract_dreamscapes_dir)

foreach w : abstract_dreamscapes_wallpapers
  conf = configuration_data()
  conf.set('NAME', w[1])
  conf.set('LIGHT', abstract_dreamscapes_dir / ('abstract-dreamscapes-' + w[0] + '.png'))
  conf.set('DARK', abstract_dreamscapes_dir / ('abstract-dreamscapes-' + w[0] + '-dark.png'))
  conf.set('PCOLOR', w[2])
  configure_file(
    input: 'abstract-dreamscapes.xml.in',
    output: 'abstract-dreamscapes-' + w[0] + '.xml',
    configuration: conf,
    install: true,
    install_dir: datadir / 'gnome-background-properties',
  )
endforeach
