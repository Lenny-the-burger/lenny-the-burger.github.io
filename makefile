# Simple Emscripten build
EMCC = emcc
SRC = src/main.c
OUT = docs/app.js

build:
	$(EMCC) $(SRC) -O3 \
		-sMODULARIZE=1 -sEXPORT_NAME=createApp \
		-sALLOW_MEMORY_GROWTH=1 \
		-sENVIRONMENT=web \
		-o $(OUT)

serve:
	cd docs && python3 -m http.server 8080

clean:
	rm -f docs/app.js docs/app.wasm
