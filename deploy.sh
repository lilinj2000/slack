#! /bin/sh

home_app=~/app

if test -d /llj/app ; then
   home_app=/llj/app
fi

home_slack=${home_app}/slack

./configure --prefix=${home_slack}

if test -d ${home_slack}; then
    rm -rf ${home_slack}
fi

make install

make distclean
