import sys
import os
import shutil
import subprocess
from subprocess import STDOUT, check_call


if __name__ == "__main__":

    print '=== Installing ==='

    dependencies = ['build-essential', 'libarmadillo-dev','libboost-python-dev',
                    'libflann-dev','python-numpy']

    #cache = apt.Cache()

    W  = '\033[0m'  # white (normal)
    R  = '\033[31m' # red
    G  = '\033[32m' # green

    bCheckDependencies = True
    bBuildInstall      = True


    if bCheckDependencies:
        print '..... checking dependencies'
        for package in dependencies:
            proc = subprocess.Popen(['dpkg-query -l ' + package], stdout=subprocess.PIPE, shell=True)
            (out, err) = proc.communicate()
            if out != '':
                print package, '    ', G+'found'+W
            else:
                print package, '    ', R+'missing'+W
                os.system('sudo apt-get install ' + package)

    if bBuildInstall:
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
