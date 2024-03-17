#!/usr/bin/env bash

if [ -f "dist/game" ]; then
  cd dist
  ./game
  cd ..
else
  echo "Did not find game executable in the dist directory. Forget to build?"
fi

