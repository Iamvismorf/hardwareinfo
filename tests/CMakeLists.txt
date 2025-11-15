# qt6_policy(SET QTP0001 NEW)
qt_add_executable(tester
   main.cpp
)
qt_add_qml_module(tester
   URI test
   VERSION 1.0
   QML_FILES main.qml
   SOURCES
     ../include/Cpu.hpp
     ../src/Cpu.cpp

     ../include/Ram.hpp
     ../src/Ram.cpp


)
target_include_directories(tester PRIVATE ../include)
target_link_libraries(tester
   PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::Gui
)
