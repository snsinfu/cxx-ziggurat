# Ziggurat normal random number generator

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

Header-only C++ library of a fast normal random number generator implementing
the [ziggurat algorithm][ziggurat].

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://raw.githubusercontent.com/snsinfu/cxx-ziggurat/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/cxx-ziggurat.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/cxx-ziggurat
[ziggurat]: https://en.wikipedia.org/wiki/Ziggurat_algorithm

## Usage

Download and include [ziggurat.hpp][header-url]. The header defines
`cxx::ziggurat_normal_distribution<T>` class template. It can be used as a
replacement for `std::normal_distribution`.

```c++
#include <iostream>
#include <random>
#include <ziggurat.hpp>

int main()
{
    std::mt19937_64 random;
    cxx::ziggurat_normal_distribution<double> normal{1.2, 0.8};
    std::cout << normal(random) << '\n';
}
```

[header-url]: https://raw.githubusercontent.com/snsinfu/cxx-ziggurat/master/include/ziggurat.hpp

## Testing

```console
git clone https://github.com/snsinfu/cxx-ziggurat
cd cxx-ziggurat/tests
make
```

## License

Boost Software License, Version 1.0.
