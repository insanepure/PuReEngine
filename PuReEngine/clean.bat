@echo off
cls
Color 1F
echo *******************************************************************************
echo *                               Clean up                                      *
echo *******************************************************************************

echo Cleaning up ...
echo.
del src\*.sdf
del src\*.ncb
del src\*.opensdf
del src\*.suo /A:H
rd  src\ipch /Q /S
del src\Game\*.aps
rd  src\Game\intermediate /Q /S
del src\PuRe.Core\*.aps
del src\PuRe.Core\*.obj
del src\PuRe.Core\*.idb
del src\PuRe.Core\*.pdb
del src\PuRe.Core\*.log
rd  src\PuRe.Core\PuRe.Core.tlog /Q /S
rd  src\PuRe.Core\intermediate /Q /S
rd  src\PuRe.Core\obj /Q /S
del src\PuRe.Graphics.DirectX10\*.aps
rd  src\PuRe.Graphics.DirectX10\intermediate /Q /S
del src\PuRe.Graphics.DirectX11\*.aps
rd  src\PuRe.Graphics.DirectX11\intermediate /Q /S
del src\PuRe.Graphics.OpenGL\*.aps
rd  src\PuRe.Graphics.OpenGL\intermediate /Q /S
del Release_Win32\*.ilk
del Release_Win32\*.pdb
del Release_Win32\modules\*.ilk
del Release_Win32\modules\*.pdb
del Release_Win32\modules\*.exp
del Release_Win32\modules\*.lib
del Release_x64\*.ilk
del Release_x64\*.pdb
del Release_x64\modules\*.ilk
del Release_x64\modules\*.pdb
del Release_x64\modules\*.exp
del Release_x64\modules\*.lib
del Debug_Win32\*.ilk
del Debug_Win32\*.pdb
del Debug_Win32\modules\*.ilk
del Debug_Win32\modules\*.pdb
del Debug_Win32\modules\*.exp
del Debug_Win32\modules\*.lib
del Debug_x64\*.ilk
del Debug_x64\*.pdb
del Debug_x64\modules\*.ilk
del Debug_x64\modules\*.pdb
del Debug_x64\modules\*.exp
del Debug_x64\modules\*.lib
del Debug_Linux\*.ilk
del Debug_Linux\*.pdb
del Debug_Linux\modules\*.ilk
del Debug_Linux\modules\*.pdb
del Debug_Linux\modules\*.exp
del Debug_Linux\modules\*.lib
del Release_Linux\*.ilk
del Release_Linux\*.pdb
del Release_Linux\modules\*.ilk
del Release_Linux\modules\*.pdb
del Release_Linux\modules\*.exp
del Release_Linux\modules\*.lib