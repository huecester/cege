libcege_sources = [
	'context.cpp',
	'texture.cpp',
	'util.cpp',
	'window.cpp',
]

libcege_dependencies = [
	dependency('sdl2'),
	dependency('sdl2_image'),
]

libcege = library(
	'cege',
	libcege_sources,
	dependencies: libcege_dependencies,
)

inccege = include_directories('.')