# ShiFuMi

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f shifumi)

# TODO
- [ ] SDLK_ESCAPE bug
- [ ] refactor Game::result()
- [ ] 
