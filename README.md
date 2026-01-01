# ElectricDB

## Dependencies

Run this command to install dependencies

```
brew install cmake
```

## Building

### Debug build

```
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug

cmake --build build-debug
```

### Release build

```
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release

cmake --build build-release
```

### Formatting
```
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug

cmake --build build-debug --target format
```
