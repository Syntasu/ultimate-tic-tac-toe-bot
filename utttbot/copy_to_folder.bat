set arg1=%1

mkdir xii%arg1%
xcopy ".\*.cpp" ".\xii%arg1%\*.cpp"
xcopy ".\*.h" ".\xii%arg1%\*.h"