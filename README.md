## How to compile

```console
me@machine:~$ sudo apt-get install xorg-dev # if you don't have it installed
me@machine:~$ sudo apt-get install libglew-dev # if you don't have it installed
me@machine:~$ sudo apt-get install libtbb-dev # if you don't have it installed
me@machine:~$ mkdir bin
me@machine:~$ cd bin/
me@machine:~$ cmake ..
me@machine:~$ make
```

## Targets

```console
me@machine:~$ ./cpp_threading/main_cpp nb_flocks #example : ./cpp_threading/main_cpp 10
me@machine:~$ ./cuda/main_cuda nb_flocks #example ./cuda/main_cuda 10
```
