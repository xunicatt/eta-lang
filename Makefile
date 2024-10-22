PROJECT=eta
BUILDDIR=build
.PHONY: configure build run clean
all: build run

configure:
	mkdir -p $(BUILDDIR)
	cmake -S . -B $(BUILDDIR)
	ln -s $(BUILDDIR)/compile_commands.json

build:
	cmake --build build

run:
	@./$(BUILDDIR)/$(PROJECT)

clean:
	@rm -rf .cache
	@rm -f compile_commands.json
	@rm -rf $(BUILDDIR)
