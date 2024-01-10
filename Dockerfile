# Use an official base image.
FROM ubuntu:latest AS builder

# Set the working directory to /app.
WORKDIR /app

# Install dependencies needed for libtiff and tesseract.
RUN apt-get update \
    && apt-get install -y --no-install-recommends ffmpeg libssl-dev libpng-dev libtiff-dev libleptonica-dev gcc g++ cmake make \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

RUN apt-get update \
    && apt-get install -y --no-install-recommends pkg-config libavutil-dev libavdevice-dev libavformat-dev libavcodec-dev libtesseract-dev \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir build
RUN cd build && cmake .. && make -j 8 && make install

FROM ubuntu:latest

COPY --from=builder /usr/local/bin/sup2srt /usr/local/bin/sup2srt
COPY --from=builder /usr/local/bin/sup2disk /usr/local/bin/sup2disk

# Install dependencies needed for libtiff and tesseract.
RUN apt-get update \
    && apt-get install -y --no-install-recommends ffmpeg libssl-dev libpng-dev libtiff-dev libleptonica-dev libavutil-dev libavdevice-dev libavformat-dev libavcodec-dev libtesseract-dev && tesseract-ocr-eng \
    && rm -rf /var/lib/apt/lists/*
