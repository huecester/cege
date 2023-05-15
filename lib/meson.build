libcege_sources = [
	'context.cpp',
	'ecs/component.cpp',
	'ecs/entity.cpp',
	'ecs/scene.cpp',
	'ecs/system.cpp',
	'sdl/texture.cpp',
	'sdl/util.cpp',
	'sdl/window.cpp',
]

libcege_dependencies = [
	dependency('fmt'),
	dependency('sdl2'),
	dependency('sdl2_image'),
]

libcege = library(
	'cege',
	libcege_sources,
	dependencies: libcege_dependencies,
)

inccege = include_directories('.')