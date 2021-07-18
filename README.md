# ZisaSFC
ZisaSFC is strives to compute space-filling curves in two and three dimension.
Currently, the Hilbert curve in 2D and a generalized Hilbert curve called Luna
\[[1]\] are implemented.

[1]: https://arxiv.org/abs/1109.2323
\[1\]: [https://arxiv.org/abs/1109.2323](https://arxiv.org/abs/1109.2323)

## Quickstart
Start by cloning the repository

    $ git clone https://github.com/1uc/ZisaSFC.git

and change into the newly created directory. Then proceed to install the
dependencies:

    $ bin/install_dir.sh COMPILER DIRECTORY DEPENDENCY_FLAGS

they will be placed into a subdirectory of `DIRECTORY` and print
part of the CMake command needed to include the dependencies. `COMPILER` must
be replaced with the compiler you want to use. The available `DEPENDENCY_FLAGS`
are

  * `--zisa_has_mpi={0,1}` to request MPI.
  * `--zisa_has_cuda={0,1}` to request CUDA (experimental).

If this worked continue by running the `cmake` command and compiling the
library. Take a look at the [project specific flags] for CMake if you want to
modify something. If this didn't work, it's not going to be a quick start.
Please read [Dependencies] and then [Building].

[project specific flags]: https://1uc.github.io/ZisaSFC/md_cmake.html#cmake_flags
[Dependencies]: https://1uc.github.io/ZisaSFC/md_dependencies.html
[Building]: https://1uc.github.io/ZisaSFC/md_cmake.html
