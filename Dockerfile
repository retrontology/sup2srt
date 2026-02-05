FROM ubuntu:latest AS builder
WORKDIR /app

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    ffmpeg \
    libssl-dev \
    libpng-dev \
    libtiff-dev \
    libleptonica-dev \
    gcc \
    g++ \
    cmake \
    make && \
    rm -rf /var/lib/apt/lists/*

COPY . /app

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    pkg-config \
    libavutil-dev \
    libavdevice-dev \
    libavformat-dev \
    libavcodec-dev \
    libtesseract-dev && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j8 && \
    make install

FROM ubuntu:latest

WORKDIR /app

COPY --from=builder /usr/local/bin/sup2srt /app/sup2srt
COPY --from=builder /usr/local/bin/sup2disk /app/sup2disk

ARG TESSERACT_LANGS="eng"

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libtiff-dev \
    libleptonica-dev \
    libtiff6 \
    libavcodec60 \
    libavformat60 \
    libavutil58 \
    libtesseract5 \
    $(echo $TESSERACT_LANGS | sed 's/\([^ ]\+\)/tesseract-ocr-\1/g') && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /app && chown -R ubuntu:ubuntu /app

COPY --chown=ubuntu:ubuntu entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sed -i 's/\r$//' /usr/local/bin/entrypoint.sh && chmod +x /usr/local/bin/entrypoint.sh

USER ubuntu

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD []