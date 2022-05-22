CFLAGS = -Wall -Werror -Wextra
all: clean Viewer

Viewer:
	@gcc view.c controller.c model.c 3d-viewer.c  `pkg-config --cflags --libs gtk+-3.0` -o 3DViewer
	./3DViewer

clean:
	@rm -f *.o Test calc *.out *.gcov *.gcda *.gcno *.info *.a
	@rm -rf ./report
	@rm -rf app