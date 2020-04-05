# Hilbert's curve
A Hilbert curve (also known as a Hilbert space-filling curve) is a continuous fractal space-filling curve first described by the German mathematician David Hilbert in 1891. -[Wikipedia](https://en.wikipedia.org/wiki/Hilbert_curve). See [1Blue1Brown's youtube video](https://www.youtube.com/watch?v=3s7h2MHQtxc) for an explanation and visualization.

This is an implementation of the algorithm for a standard 24 or 32 bit bitmap. To compile and run:

```
$ gcc traverse.c dibdump.c headers/dibdump.h -o traverse
$ traverse
```