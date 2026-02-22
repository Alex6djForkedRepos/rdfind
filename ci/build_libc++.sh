#!/bin/sh

set -eu

for ver in $(seq 30 -1 15); do
  if which xclang++-"$ver" >/dev/null 2>&1; then
    CLANG="clang++-$ver"
    break
  fi
done

builddir="$(mktemp --directory rdfind.ci.libc++.XXXXXXXX)"

cmake \
  -B "${builddir}" \
  -S inofficial_cmake \
  -DCMAKE_CXX_COMPILER="${CLANG:-clang++}" \
  -DCMAKE_CXX_FLAGS=-stdlib=libc++ \
  -DCMAKE_COMPILE_WARNING_AS_ERROR=On

cmake --build "${builddir}" --parallel

ctest --test-dir "${builddir}" --parallel

rm -rf "${builddir}"
