BD=../build/
QMAKE=$(BD)
CFLAGS=-c# -Wall -Wextra -Werror
LDFLAGS=#-Wall -Wextra -Werror
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest -I./ -L./
SRC=model.cpp credit_model.cpp deposit_model.cpp 
OBJ=$(addprefix $(BD),$(SRC:.cpp=.o))
EXE=$(QMAKE)SmartCalc.app/Contents/MacOS/SmartCalc
APP=$(QMAKE)SmartCalc.app
APPDIR=$(HOME)/Applications/SmartCalc/
APP_EXE=$(APPDIR)SmartCalc.app/Contents/MacOS/SmartCalc
CC=g++

all: install
	$(APP_EXE)

build: $(BD) $(BD)qmake.pro
	cd $(QMAKE); qmake qmake.pro
	make -C $(QMAKE)

./$(BD):
	mkdir $(BD)

arrange:
	rm -f $(QMAKE)qmake.*
	cd $(QMAKE); qmake -project ../src/; mv build.pro ../src/qmake.pro

./$(BD)qmake.pro:
	cp qmake.pro $(QMAKE)

./$(BD)%.o: */%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

install: build 
	@mkdir $(APPDIR) || echo "Directory already exists. Skip."
	cp -rf manual/ $(APPDIR)manual/
	cp -rf $(APP) $(APPDIR)
	make clean

uninstall:
	rm -rf $(APPDIR)
	rm -rf $(HOME)/Applications/SmartCalc.tar.gz

dvi:
	open manual/documentatuon.html

dist:
	tar -cvf $(APPDIR)../SmartCalc.tar $(APPDIR)
	gzip $(APPDIR)../SmartCalc.tar

#### TEST #####
test: clean $(BD)main_test_exe
	./$(BD)main_test_exe

./$(BD)main_test_exe: $(OBJ) $(BD)main_test.o
	$(CC) $(LDFLAGS) $^ -o $@ $(GTESTFLAGS)

#### GCOV #####
gcov_report: gcov_build $(BD)main_test.o
	$(CC) $(LDFLAGS) $(LCOVFLAGS) $(OBJ) $(BD)main_test.o -o $(BD)main_gcov_exe $(GTESTFLAGS)
	./$(BD)main_gcov_exe
	# mv *.gcda *.gcno ./$(BD)
	lcov -t "gcov_report" -o $(BD)gcov_report.info -c -d ./$(BD)
	genhtml -o $(BD)report $(BD)gcov_report.info
	open $(BD)report/$(PWD)/model/index.html

gcov_build:
	$(CC) $(CFLAGS) $(LCOVFLAGS) model/model.cpp -o $(BD)model.o
	$(CC) $(CFLAGS) $(LCOVFLAGS) model/credit_model.cpp -o $(BD)credit_model.o
	$(CC) $(CFLAGS) $(LCOVFLAGS) model/deposit_model.cpp -o $(BD)deposit_model.o

clean:
	test -f $(QMAKE)Makefile && make distclean -C $(QMAKE) || printf ""
	rm -rf ./$(BD)*

clang:
	cp ../materials/linters/.clang-format . && \
	clang-format -n */*.cpp *.cpp */*.h; \
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format . && \
	clang-format -i */*.cpp *.cpp */*.h; \
	rm -f .clang-format

cppcheck:
	cppcheck --enable=all --suppress=unknownMacro --suppress=useStlAlgorithm --suppress=missingInclude --suppress=unusedFunction --force ../src/

leaks:
	leaks --atExit -- ./$(BD)main_test_exe

valgrind:
	valgrind --undef-value-errors=no --log-file=valgrind-out.txt ./$(BD)main_test_exe

