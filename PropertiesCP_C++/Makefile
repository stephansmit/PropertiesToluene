TARGET           = LUTTable.out
OBJECT_01        = main.o
SOURCE_01        = main.cpp

$(TARGET): $(OBJECT_01) 

$(OBJECT_01) : $(SOURCE_01) 
	         g++ -g -o $(TARGET) $(SOURCE_01)   -I/home/azureuser/CoolProp/include -I/home/azureuser/CoolProp/externals/cppformat -L/home/azureuser/CoolProp/build -lCoolProp -ldl


all : 

clean :
	-rm $(TARGET)  $(OBJECT_01)



