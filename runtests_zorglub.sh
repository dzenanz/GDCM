#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

#ctest -S zorglub-gcc4-64-makefiles.cmake -V -O zorglub-gcc4-64-makefiles.log
ctest -S zorglub-gcc43-64-makefiles.cmake -V -O zorglub-gcc43-64-makefiles.log
ctest -S zorglub-gcc-64-makefiles.cmake -V -O zorglub-gcc-64-makefiles.log
ctest -S zorglub-gcc-snap-64-makefiles.cmake -V -O zorglub-gcc-snap-64-makefiles.log

# Nightly doxygen:
cd $HOME/Dashboards/MyTests/gdcm-nightly && touch Utilities/doxygen/Doxyfile
cd $HOME/Dashboards/MyTests/gdcm-nightly && make -j8
cd $HOME/Dashboards/MyTests/gdcm-nightly && make rebuild_cache && make vtkgdcmDoxygenDoc
#cd $HOME/Dashboards/MyTests/gdcm-nightly/Utilities/doxygen/vtk && make vtkgdcmDoxygenDoc
#cd $HOME/Dashboards/MyTests/gdcm-nightly
rsync --quiet -av Utilities/doxygen/gdcm-2.1.0-doc.tar.gz malat,gdcm@web.sourceforge.net:htdocs
rsync --quiet -av -r Utilities/doxygen/html malat,gdcm@web.sourceforge.net:htdocs

# Nightly PDF Doxygen
cd $HOME/Dashboards/MyTests/gdcm-nightly/Utilities/doxygen/latex
rsync --quiet -av gdcm-2.1.0.pdf malat,gdcm@web.sourceforge.net:htdocs
