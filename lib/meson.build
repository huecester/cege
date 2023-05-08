libcege_sources = [
	'context.cpp',
	'ecs/component.cpp',
	'ecs/constants.hpp',
	'ecs/entity.cpp',
	'ecs/scene.cpp',
	'ecs/types.hpp',
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