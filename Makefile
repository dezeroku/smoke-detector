BOARD=arduino:avr:uno
PORT=/dev/ttyACM0

build: src/.build-done

src/.build-done: $(wildcard src/*.ino) .core-setup
	arduino-cli compile --fqbn $(BOARD) src/ --output-dir src/.build && touch src/.build-done

install: src/.build-done
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) src/ --input-dir src/.build

clean:
	rm -rf src/.build src/.build-done

.core-setup:
	arduino-cli core install arduino:avr && touch .core-setup

serial:
	minicom -D $(PORT) -b 115200

.PHONY: serial install clean
