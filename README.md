# sup2srt
Convert SUP graphic subtitles to text-based SRT format with Tesseract.

## Requirements
- libtiff
- libtiffxx
- leptonica
- tesseract
- libav/ffmpeg
- CMake

## Build
1. Clone the repo
    ```
    git clone https://github.com/retrontology/sup2srt
    ```
2. Enter the repo and create the build directory
    ```
    cd sup2srt
    mkdir build
    ```
3. Enter the build directory and prepare the build
    ```
    cd build
    cmake ..
    ```
4. Build the program
    ```
    make -j ${nproc}
    ```

## Install (optional)
1. Install the program
   ```
   sudo make install
   ```

## Usage
```
usage: sup2srt [-h] [-vST] [-t track] [-l language] [-o output] input
  -h:  	        Display this help menu
  -v:  	        Display program Version
  -V:  	        Verbose - output srt as it's being written
  -T:  	        Dump TIFF images extracted from the PGS file to disk
  -S:  	        Write SUP file extracted from mkv to disk (only used when an mkv or m2ts is input)
  -t track:  	Select track to extract from mkv. Can be multiple tracks separated by a comma (must be used when an mkv or m2ts is input)
  -l language:  Select Tesseract language according to ISO 639-2/T. If not specified and an mkv or m2ts is input, the program will try to use the track metadata. Must be used when a binary SUP file is input
  -o:  	        Output file (if not specified the file will be output to the same dir as the input).
  input:  	    file to parse SUP stream. Can either be a binary SUP file or an mkv/m2ts. If the file doesn't end in .mkv or .m2ts, it will assume it is a binary SUP file.


usage: sup2disk [-hv] [-t track] input
  -h:  	     Display this help menu
  -v:  	     Display program Version
  -t track:  Select track to extract from mkv. Can be multiple tracks separated by a comma (must be used when an mkv is input)
  input:  	 file to parse SUP stream. Must be an mkv  	
```

## Docker Usage

### Requirements

Install docker, podman or containerd


1. Build the docker image

```bash
docker build . -t sup2srt
```

2. Mount your location to make it available to the container and shell into it.

```bash
docker run -v /Users/christopher/Movies/:/movies/ -ti --entrypoint /bin/bash localhost/sup2srt:latest
```

3. If you already have sup files generated using mkvextract do the `sup2srt` command

```bash
root@06f7be310582:/movies/movie-title# sup2srt eng.sup -l eng
```

4. If you don't

```bash
root@06f7be310582:/movies/moviefolder# sup2disk movie.mkv -t 4
```
