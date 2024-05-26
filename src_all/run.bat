@echo off
:: 打开第一个cmd窗口运行node server.js
start /b cmd /k "cd /d D:\Users\SevenGrass\Documents\WILLIAMZHANG\DataStrucCourseDes\MyGithub\src_all\backend && node server.js"

:: 等待第一个cmd窗口启动
timeout /t 5

:: 打开第二个cmd窗口运行npm run serve
start /b cmd /k "cd /d D:\Users\SevenGrass\Documents\WILLIAMZHANG\DataStrucCourseDes\MyGithub\src_all\frontend && npm run serve"

echo.
echo 两个命令都已启动，按任意键关闭窗口...
pause >nul