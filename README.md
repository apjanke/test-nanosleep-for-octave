test-nanosleep-for-octave
=========================

Some test code to see why Octave's pause() is misbehaving and taking too long

This is repro code for https://savannah.gnu.org/bugs/?55940

## Use

To build this, do:

```
autoreconf
./configure
make
```

Then to run the test:

```
src/my_nanosleep_test
```
