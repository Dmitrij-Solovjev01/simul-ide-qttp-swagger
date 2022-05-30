# syntax=docker/docker_file_test:1
# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
#
#sudo docker build -t test1 -f Dockerfile /home/dima/
#sudo docker run -p 5900:5900 --rm test1
#127.0.0.1:5900

FROM debian:latest as build

# Установим рабочую директорию 
WORKDIR /app

RUN         apt-get update \
                && apt-get install -y \
                    software-properties-common \
                    wget \
                && apt-get update \
                && apt-get install -y make git curl \
                && apt-get install -y gcc g++ cmake

# Скопируем директорию  в контейнер
COPY ./QT_Project/SimulIDE_build ./QT_Project/SimulIDE_build
#################################################################
#либы лежат тут /home/dima/qt5/qt6-comp/lib
#сами мы находимся в /home/dima/QT_Project
#################################################################
RUN apt-get update && apt-get  -y install qttools5-dev-tools
RUN apt-get update && apt-get -y  install build-essential
ADD ./qt5/qt6-comp /home/dima/qt5/qt6-comp
#RUN cp ./qt5/qt6-comp/lib /home/dima/qt5/qt6-comp/lib
RUN /home/dima/qt5/qt6-comp/bin/qmake ./QT_Project/SimulIDE_build/SimulIDE.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug

RUN apt-get update && \
    apt-get install -y \
      libboost-dev libboost-program-options-dev \
      libgtest-dev  libgl1-mesa-dev elfutils ocaml libelf-dev libelf1 \
      libpulse-dev libpulse0
#    && \
 #   cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
  #  cmake --build . && \
   # mv lib*.a /usr/lib


RUN make -j`nproc`  -C ./QT_Project/SimulIDE_build/
# Запуск ---------------------------------------

# Добавим пользователя, потому как в Docker по умолчанию используется root
# Запускать незнакомое приложение под root'ом неприлично :)
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

FROM debian:latest
ARG DEBIAN_FRONTEND=noninteractive


# Установим рабочую директорию нашего приложения
WORKDIR /app

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=build /app/QT_Project/SimulIDE_build/debug/SimulIDE_0.4.13-SR5-CE/bin/simulide .
COPY --from=build /home/dima/qt5/qt6-comp /home/dima/qt5/qt6-comp

RUN apt-get update
#RUN apt-get -y install curl
RUN apt-get update && apt-get install -y x11vnc xvfb
RUN apt-get install -y bison build-essential flex gperf libasound2-dev libatkmm-1.6-dev libbz2-dev libcap-dev libcups2-dev libdrm-dev libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev libgcrypt20-dev libglu1-mesa-dev libgstreamer1.0-dev libicu-dev libnss3-dev libpci-dev libpulse-dev libssl-dev libudev-dev libx11-dev libx11-xcb-dev libxcb-composite0 libxcb-composite0-dev libxcb-cursor-dev libxcb-cursor0 libxcb-damage0 libxcb-damage0-dev libxcb-dpms0 libxcb-dpms0-dev libxcb-dri2-0 libxcb-dri2-0-dev libxcb-dri3-0 libxcb-dri3-dev libxcb-ewmh-dev libxcb-ewmh2 libxcb-glx0 libxcb-glx0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-image0 libxcb-image0-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-present-dev libxcb-present0 libxcb-randr0 libxcb-randr0-dev libxcb-record0 libxcb-record0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-render0 libxcb-render0-dev libxcb-res0 libxcb-res0-dev libxcb-screensaver0 libxcb-screensaver0-dev libxcb-shape0 libxcb-shape0-dev libxcb-shm0 libxcb-shm0-dev libxcb-sync-dev libxcb-sync0-dev libxcb-sync1 libxcb-util-dev libxcb-util0-dev libxcb-util1 libxcb-xf86dri0 libxcb-xf86dri0-dev libxcb-xfixes0 libxcb-xfixes0-dev libxcb-xinerama0 libxcb-xinerama0-dev libxcb-xkb-dev libxcb-xkb1 libxcb-xtest0 libxcb-xtest0-dev libxcb-xv0 libxcb-xv0-dev libxcb-xvmc0 libxcb-xvmc0-dev libxcb1 libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxrandr-dev libxrender-dev libxslt-dev libxss-dev libxtst-dev perl python ruby libx11-xcb-dev libglu1-mesa-dev build-essential openssl libssl-dev libssl1.0 libgl1-mesa-dev libqt5x11extras5 git cmake build-essential

RUN apt-get update && apt-get install -y libqt5gui5
#ENV QT_DEBUG_PLUGINS=1
RUN apt-get install -y libxcb-util1
RUN apt-get install -y '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev

ENV QT_DEBUG_PLUGINS=1
RUN export QT_DEBUG_PLUGINS=1

RUN apt-get install -qqy x11-apps
ENV DISPLAY :0

# Установим точку входа
#ENTRYPOINT ["/app/simulide"]
RUN echo "exec /app/simulide" > ~/.xinitrc && chmod +x ~/.xinitrc
CMD ["x11vnc", "-create", "-noxrecord", "-noxfixes", "-noxdamage", "-forever", "-passwd", "trustno1"]
