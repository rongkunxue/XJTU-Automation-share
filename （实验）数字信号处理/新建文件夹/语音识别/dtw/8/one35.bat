@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION
COLOR 0A
TITLE keith batch rename tool
ECHO.
ECHO =================================
ECHO     欢迎使用keith批量命名工具
ECHO =================================
ECHO.
ECHO 请选择要批量修改的处理的后缀名：
ECHO.
ECHO 1. 所有文件(只会修改文件名)
ECHO 2. txt
ECHO 3. png
ECHO 4. 其他,我自己来输入
ECHO.
CHOICE /C 1234 /m "你的选择是: "
IF %ERRORlEVEL% equ 1 SET suffix=*
IF %ERRORlEVEL% equ 2 SET suffix=txt
IF %ERRORlEVEL% equ 3 SET suffix=png
IF %ERRORlEVEL% equ 4 (
ECHO.
SET /P suffix="请输入要批量处理的后缀名: "
)
ECHO.
SET /p prefix="请输入你修改成的文件名的开头: "
ECHO.
ECHO 修改ing...
ECHO.
SET /a index=0
FOR %%i in (*.!suffix!) do (
    SET /a index=!index!+1
    SET name=!prefix!!index!.!suffix!
    REN "%%i" !name!
)
IF %ERRORlEVEL% equ 0 (
    ECHO 修改成功!
) ELSE (
    ECHO 修改失败!
)
ECHO.
PAUSE
