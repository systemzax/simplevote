rm -f  ../build/simplevoting/simplevoting.wasm
rm -f  ../build/simplevoting/simplevoting.abi

if [[ $* == --debug ]]
then
    echo "Compiling in debug mode..."
    eosio-cpp -I ../include/ -O 3 ../src/simplevoting.cpp -abigen -abigen_output ../build/simplevoting/simplevoting.abi -o ../build/simplevoting/simplevoting.wasm -D=DEBUG
else
    cd ..
    cd build
    cmake ..
    make
    echo "Successfully built. Output in ./build/simplevoting/"
fi
