# Ziggurat normal random number generator

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

Header-only C++ library of a fast normal random number generator implementing
the [ziggurat algorithm][ziggurat].

[Download][header-url]

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://raw.githubusercontent.com/snsinfu/cxx-ziggurat/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/cxx-ziggurat.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/cxx-ziggurat
[ziggurat]: https://en.wikipedia.org/wiki/Ziggurat_algorithm
[header-url]: https://raw.githubusercontent.com/snsinfu/cxx-ziggurat/master/include/ziggurat.hpp

## Usage

```c++
#include <iostream>
#include <random>
#include <ziggurat.hpp>

int main()
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;
    std::cout << normal(random) << '\n';
}
```

## Testing

```console
git clone https://github.com/snsinfu/cxx-ziggurat
cd cxx-ziggurat/tests
make
```

## License

Boost Software License, Version 1.0.
