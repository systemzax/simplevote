rm -f  ../build/simplevote/simplevote.wasm
rm -f  ../build/simplevote/simplevote.abi

if [[ $* == --debug ]]
then
    echo "Compiling in debug mode..."
    eosio-cpp -I ../include/ -O 3 ../src/simplevote.cpp -abigen -abigen_output ../build/simplevote/simplevote.abi -o ../build/simplevote/simplevote.wasm -D=DEBUG
else
    cd ..
    cd build
    cmake ..
    make
    echo "Successfully built. Output in ./build/simplevote/"
fi
