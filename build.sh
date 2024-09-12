#!/bin/bash -e
red_start="\033[31m"
red_end="\033[0m"
green_start="\033[32m"
green_end="\033[0m"

CMAKE_PROJECT_ROOT=$(pwd)
CMAKE_BUILD_ROOT=$CMAKE_PROJECT_ROOT/build
export CMAKE_BUILD_ROOT
function build_app()
{
    echo -e "${green_start}build app $1 ...${green_end}"
    ${SHELL_FOLDER}/single_build.sh $1
    echo -e "${green_start}build app $1 complete!${green_end}\n"
}

function create_make_files()
{
    echo -e "${green_start}create make files ...${green_end}"
    # remove build directory
    rm -rf ${CMAKE_BUILD_ROOT}

    mkdir -p ${CMAKE_BUILD_ROOT} && cd ${CMAKE_BUILD_ROOT}
    # generate make files
    cmake -G "Unix Makefiles" ${CMAKE_OPTION} ${CMAKE_PROJECT_ROOT}

    echo -e "${green_start}create make files complete!${green_end}\n"
}

function clean_modules()
{
    echo -e "${green_start}clean modules ...${green_end}"

    # enter build directory
    build_dir=${CMAKE_BUILD_ROOT}
    [ -d ${build_dir} ] && cd ${build_dir}

    # build modules
    rm -rf ${CMAKE_OUTPUT_ROOT}
    make clean

    echo -e "${green_start}clean modules complete!${green_end}\n"
}

function build_modules()
{
    echo -e "${green_start}build modules ...${green_end}"

    # enter build directory
    build_dir=${CMAKE_BUILD_ROOT}
    [ -d ${build_dir} ] && cd ${build_dir}

    # build modules
    make -j8 -s --no-print-directory

    echo -e "${green_start}build modules complete!${green_end}\n"
}



if [ $# == 0 ]; then
    c_type=create
else
    c_type=$1
fi

case ${c_type} in
    create)
        create_make_files
        ;;
    clean)
        clean_modules
        ;;
    build)
        build_modules
        ;;
    app)
        build_modules
        ;;
    apps)
        build_modules
        ;;
    all)
        create_make_files
        clean_modules
        build_modules
        ;;
esac

exit 0
