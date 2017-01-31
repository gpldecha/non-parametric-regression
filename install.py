import sys
import os
import shutil
import subprocess

import imp
sys.path.append('/usr/lib/python2.7/dist-packages/')
import apt

if __name__ == "__main__":


    print '=== Installing ==='

    dependencies = ['build-essential', 'libarmadillo-dev','libboost-python-dev',
                    'libflann-dev','python-numpy']

    cache = apt.Cache()

    W  = '\033[0m'  # white (normal)
    R  = '\033[31m' # red
    G  = '\033[32m' # green

    print '..... checking dependencies'
    for package in dependencies:
        pkg = cache[package]
        if pkg.is_installed:
          print package, '    ', G+'found'+W
        else:
            print package, '    ', R+'missing'+W
            pkg.mark_install()
            try:
                cache.commit()
            except Exception, arg:
                print >> sys.stderr, "Sorry, package installation failed [{err}]".format(err=str(arg))

    print '..... build and install npr'
    # build and install NPR package
    if os.path.exists('./npr/build'):
        shutil.rmtree('./npr/build')
    os.makedirs('./npr/build')
    os.chdir( './npr/build' )
    os.system('cmake ..')
    os.system('make')
    os.system('sudo make install')
    os.chdir('../..')

    print '..... build and install pynpr'
    # build and install PYNPR
    if os.path.exists('./pynpr/build'):
        shutil.rmtree('./pynpr/build')
    os.makedirs('./pynpr/build')
    os.chdir( './pynpr/build' )
    os.system('cmake ..')
    os.system('make')
    os.system('sudo make install')
    os.chdir('../..')
