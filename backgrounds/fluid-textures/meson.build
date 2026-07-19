fluid_textures_dir = datadir / 'backgrounds' / 'fluid-textures'

# pcolor uses the dark variant's dominant tone as the solid fallback color
# shown while the image loads.
fluid_textures_wallpapers = [
  ['abstract', 'Fluid Textures Abstract', '#515368'],
  ['ashen', 'Fluid Textures Ashen', '#463F46'],
  ['blue', 'Fluid Textures Blue', '#041D61'],
  ['glass', 'Fluid Textures Glass', '#2B2E30'],
  ['green', 'Fluid Textures Green', '#1E4852'],
  ['teal', 'Fluid Textures Teal', '#14445F'],
  ['yellow', 'Fluid Textures Yellow', '#6F4225'],
]

fluid_textures_images = []
foreach w : fluid_textures_wallpapers
  fluid_textures_images += 'fluid-textures-' + w[0] + '.png'
  fluid_textures_images += 'fluid-textures-' + w[0] + '-dark.png'
endforeach

install_data(fluid_textures_images, install_dir: fluid_textures_dir)
install_data('LICENSE', install_dir: fluid_textures_dir)

foreach w : fluid_textures_wallpapers
  conf = configuration_data()
  conf.set('NAME', w[1])
  conf.set('LIGHT', fluid_textures_dir / ('fluid-textures-' + w[0] + '.png'))
  conf.set('DARK', fluid_textures_dir / ('fluid-textures-' + w[0] + '-dark.png'))
  conf.set('PCOLOR', w[2])
  configure_file(
    input: 'fluid-textures.xml.in',
    output: 'fluid-textures-' + w[0] + '.xml',
    configuration: conf,
    install: true,
    install_dir: datadir / 'gnome-background-properties',
  )
endforeach
