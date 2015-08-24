# SpacePirates

### Build Instructions
####Windows:
  Build with Visual Studio 2012. For distribution, build Release version, then copy library DLLs and images to
  the same directory as the EXE file.

Linux:
  sudo apt-get install freeglut3-dev libsdl1.2-dev libsdl-image1.2-dev
  make

Debian package:
  Ensure files in debian directory are correct (esp. control, spacepirates.dirs)

 start in the main source directory named [directoryName]
  cd ..
  (in the following command, replace 1.0 with the proper version number)
  tar czfv spacepirates_1.0.orig.tar.gz [directoryName]
  cd [directoryName]
  (in the following, replace 1.0-1 with [mainVersion]-[packageVersion])
  dch --create -v 1.0-1 --package spacepirates
  (now ensure debian/changelog values are correct)
  debuild -us -uc
  cd ..
  (you should see deb package here)

  *** Version number explanation from wiki.debian.org/IntroDebianPackaging
    The ["spacepirates"] part MUST be the same as the source package name. 1.0-1
 is the version. The 1.0 part is the upstream version. The -1 part is the 
  
####Debian: the first version of the Debian package of upstream version
    1.0. If the Debian package has a bug, and it gets fixed, but the upstream 
    version remains the same, then the next version of the package will be 
    called 1.0-2. Then 1.0-3, and so on.
 ***

#### License
The MIT License (MIT)

Copyright (c) 2015 Robert Pogue Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

