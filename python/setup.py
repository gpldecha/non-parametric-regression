from distutils.core import setup, Extension

module1 = Extension('demo',
                    sources = ['demo.c'])

setup(name = 'npr',
      version = '1.0',
      description = 'This is a demo package',
      ext_modules = ['pylwr.so'])
