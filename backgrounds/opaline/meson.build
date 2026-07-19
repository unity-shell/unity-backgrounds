opaline_dir = datadir / 'backgrounds' / 'opaline'

# color: light dominant is inverted to a dark solid fallback color while the
# image loads, so pcolor uses the dark variant's dominant tone.
opaline_wallpapers = [
  ['blue', 'Opaline Blue', '#283F63'],
  ['green', 'Opaline Green', '#1C3B28'],
  ['orange', 'Opaline Orange', '#492820'],
  ['purple', 'Opaline Purple', '#2C2944'],
  ['yellow', 'Opaline Yellow', '#4F3B20'],
]

opaline_images = []
foreach w : opaline_wallpapers
  opaline_images += 'opaline-' + w[0] + '.jpg'
  opaline_images += 'opaline-' + w[0] + '-dark.jpg'
endforeach

install_data(opaline_images, install_dir: opaline_dir)
install_data('LICENSE', install_dir: opaline_dir)

foreach w : opaline_wallpapers
  conf = configuration_data()
  conf.set('NAME', w[1])
  conf.set('LIGHT', opaline_dir / ('opaline-' + w[0] + '.jpg'))
  conf.set('DARK', opaline_dir / ('opaline-' + w[0] + '-dark.jpg'))
  conf.set('PCOLOR', w[2])
  configure_file(
    input: 'opaline.xml.in',
    output: 'opaline-' + w[0] + '.xml',
    configuration: conf,
    install: true,
    install_dir: datadir / 'gnome-background-properties',
  )
endforeach
