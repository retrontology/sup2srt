# sup2srt
Convert SUP graphic subtitles to text-based SRT format with Tesseract.

## Usage
```
usage: sup2srt [-h] [-vST] [-t track] [-l language] [-o output] input
  -h:  	        Display this help menu
  -v:  	        Display program Version
  -V:  	        Verbose - output srt as it's being written
  -T:  	        Dump TIFF images extracted from the PGS file to disk
  -S:  	        Write SUP file extracted from mkv to disk (only used when an mkv is input)
  -t track:  	Select track to extract from mkv. Can be multiple tracks separated by a comma (must be used when an mkv is input)
  -l language:  Select Tesseract language according to ISO 639-2/T. If not specified and an mkv is input, the program will try to use the track metadata. Must be used when a binary SUP file is input
  -o:  	        Output file (if not specified the file will be output to the same dir as the input).
  input:  	    file to parse SUP stream. Can either be a binary SUP file or an mkv. If the file doesn't end in .mkv, it will assume it is a binary SUP file.


usage: sup2disk [-hv] [-t track] input
  -h:  	     Display this help menu
  -v:  	     Display program Version
  -t track:  Select track to extract from mkv. Can be multiple tracks separated by a comma (must be used when an mkv is input)
  input:  	 file to parse SUP stream. Must be an mkv  	

Requires: libtiff, libtiffxx, leptonica, tesseract, libav/ffmpeg
```