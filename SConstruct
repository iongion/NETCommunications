import os, sys

sources = Glob('*.c')

env = Environment(
  CCFLAGS = [
    '-Wall', 
    '-O3',
    '-I.',
    '-I./common/include',
  ], 
  CPPDEFINES = {
  },
  CPPPATH = [
  ],
  LIBPATH = [
    './liblog',
    './libamfext',
  ],
  LIBS = [
    'liblog',
    'libamfext',
  ]
)
config = Configure(env)

if env['PLATFORM'] == 'cygwin':
    env.Append (
      LINKFLAGS = [
        '-Wl,-subsystem,windows',
        '-static',
        '-lmingw32',
      ],
      LIBS = [
        'libws2_32', 
        'libwinmm', 
        'libgdi32', 
        'libwsock32',
      ],
    )

if env ['PLATFORM'] == 'win32':
    Tool('mingw')(env)
    env.Append (
      LINKFLAGS = [
        '-Wl,-subsystem,windows',
        '-static',
        #'-lmingw32',
      ],
      LIBS = [
        'libws2_32', 
        'libwinmm', 
        'libgdi32', 
        'libwsock32',
      ],
    )


env = config.Finish()

liblog = SConscript('liblog/SConscript')
libamfext = SConscript('libamfext/SConscript')
libamfexttests = SConscript('libamfexttests/SConscript')

Depends( libamfext, liblog )
Depends( libamfexttests, libamfext )

AlwaysBuild( liblog )
AlwaysBuild( libamfext )
AlwaysBuild( libamfexttests )
