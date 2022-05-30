# simul-ide-qttp-swagger
 this is an experimental non-working project
 
# perspectives
Now work:
 -Docker
Will fix later:
 -Swaggerless
 -qttpless


# Building QT5 (Debian 11)

sudo apt-get install bison build-essential flex gperf libasound2-dev libatkmm-1.6-dev libbz2-dev libcap-dev libcups2-dev libdrm-dev libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev libgcrypt20-dev libglu1-mesa-dev libgstreamer1.0-dev libicu-dev libnss3-dev libpci-dev libpulse-dev libssl-dev libudev-dev libx11-dev libx11-xcb-dev libxcb-composite0 libxcb-composite0-dev libxcb-cursor-dev libxcb-cursor0 libxcb-damage0 libxcb-damage0-dev libxcb-dpms0 libxcb-dpms0-dev libxcb-dri2-0 libxcb-dri2-0-dev libxcb-dri3-0 libxcb-dri3-dev libxcb-ewmh-dev libxcb-ewmh2 libxcb-glx0 libxcb-glx0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-image0 libxcb-image0-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-present-dev libxcb-present0 libxcb-randr0 libxcb-randr0-dev libxcb-record0 libxcb-record0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-render0 libxcb-render0-dev libxcb-res0 libxcb-res0-dev libxcb-screensaver0 libxcb-screensaver0-dev libxcb-shape0 libxcb-shape0-dev libxcb-shm0 libxcb-shm0-dev libxcb-sync-dev libxcb-sync0-dev libxcb-sync1 libxcb-util-dev libxcb-util0-dev libxcb-util1 libxcb-xf86dri0 libxcb-xf86dri0-dev libxcb-xfixes0 libxcb-xfixes0-dev libxcb-xinerama0 libxcb-xinerama0-dev libxcb-xkb-dev libxcb-xkb1 libxcb-xtest0 libxcb-xtest0-dev libxcb-xv0 libxcb-xv0-dev libxcb-xvmc0 libxcb-xvmc0-dev libxcb1 libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxrandr-dev libxrender-dev libxslt-dev libxss-dev libxtst-dev perl python ruby libx11-xcb-dev libglu1-mesa-dev build-essential openssl libssl-dev libssl1.0 libgl1-mesa-dev libqt5x11extras5 git cmake build-essential

#Maybe with enother package from:
#https://doc.qt.io/qt-5/linux.html
#https://doc.qt.io/qt-5/linux-requirements.html
#https://www.ics.com/blog/how-compile-qt-source-code-linux
#https://wiki.qt.io/Building_Qt_5_from_Git

git clone git://code.qt.io/qt/qt5.git

cd qt5/

git checkout 5.15.2

perl init-repository

mkdir qt6-build

mkdir qt6-comp

cd qt6-build/

../configure -prefix ../qt6-comp/ -xcb -xcb-xlib -bundled-xcb-xinput #Maybe without "-bundled-xcb-xinput"

c y

make -j12

make install

The folder with the compiled qt library should be on the path /home/$USER/qt5/qt6-comp

#Run
sudo docker build -t test1 -f Dockerfile /home/$USER/
sudo docker run -p 5900:5900 --rm test1
open VNC client (Remmina for example) and set address "127.0.0.1:5900" and password "trustno1"
You will see something like this:

![image](https://user-images.githubusercontent.com/96019653/170889580-69174297-78fe-48fc-a7a8-4e09e6f66a59.png)
# Tests:
1. you can see the valgrid_log in the project
2. you can see the heaptrack.gz in the project
![image](https://user-images.githubusercontent.com/96019653/170943982-35e8a25d-63b1-40fd-b5d3-fa4ae0a2e59f.png)


After testing the project using the valgrid and heaptrack utilities, no significant shortcomings were identified. The tests passed successfully, no memory leaks and excessive gluttony were found.
