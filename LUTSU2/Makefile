TARGET           = LUTTable.out
OBJECT_01        = main.o
SOURCE_01        = main.cpp

$(TARGET): $(OBJECT_01)
	         g++ -g -o $(TARGET) $(OBJECT_01) -lstdc++

$(OBJECT_01) : $(SOURCE_01) 
	         g++ -g -c $(SOURCE_01) -o $(OBJECT_01)

all : $(TARGET)

clean :
	-rm $(TARGET)  $(OBJECT_01)
