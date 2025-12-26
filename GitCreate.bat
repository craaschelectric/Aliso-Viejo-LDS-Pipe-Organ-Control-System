@echo off
REM Git Repository Setup Script
REM This script initializes a Git repository, creates .gitignore, and prepares for GitHub push

echo ========================================
echo Git Repository Setup Script
echo ========================================
echo.

REM Check if Git is installed
git --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Git is not installed or not in PATH
    pause
    exit /b 1
)

REM Get current directory name for suggested repo name
for %%I in (.) do set FOLDER_NAME=%%~nxI
echo Current folder: %FOLDER_NAME%
echo.

REM Ask for repository name
set /p REPO_NAME="Enter GitHub repository name (or press Enter for '%FOLDER_NAME%'): "
if "%REPO_NAME%"=="" set REPO_NAME=%FOLDER_NAME%
echo Using repository name: %REPO_NAME%
echo.

REM Ask for project description
set /p DESCRIPTION="Enter project description: "
echo.

REM Ask for project type
echo Select project type:
echo 1. MPLAB X (PIC microcontroller)
echo 2. Arduino/Teensy
echo 3. KiCad only
echo 4. MPLAB X + KiCad
echo 5. Arduino/Teensy + KiCad
echo 6. MPLAB X + Arduino + KiCad
echo 7. MPLAB X + Arduino + KiCad + FreeCAD
echo 8. Java project
echo 9. Python project
echo 10. Custom (you'll edit .gitignore manually)
echo.
set /p PROJECT_TYPE="Enter number (1-10): "
echo.

REM Initialize Git repository
echo Initializing Git repository...
git init
if errorlevel 1 (
    echo ERROR: Failed to initialize Git repository
    pause
    exit /b 1
)
echo Done.
echo.

REM Create .gitignore based on project type
echo Creating .gitignore file...

if "%PROJECT_TYPE%"=="1" (
    echo Creating MPLAB X .gitignore...
    (
        echo # MPLAB X IDE
        echo nbproject/private/
        echo nbproject/Package-*.bash
        echo build/
        echo nbbuild/
        echo dist/
        echo nbdist/
        echo nbactions.xml
        echo nb-configuration.xml
        echo .dep.inc
        echo *.d
        echo *.pre
        echo *.p1
        echo *.lst
        echo *.sym
        echo *.obj
        echo *.o
        echo *.sdb
        echo *.obj.dmp
        echo html/
        echo *.map
        echo *.rlf
        echo *.cof
        echo *.hxl
        echo *.cod
        echo *.mcp
        echo *.mcs
        echo *.mcw
        echo *.dbg
        echo.
        echo # Build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo.
        echo # IDE files
        echo .generated_files/
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.bak
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="2" (
    echo Creating Arduino/Teensy .gitignore...
    (
        echo # Arduino/Teensy build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo *.map
        echo.
        echo # IDE files
        echo .vscode/
        echo .idea/
        echo *.suo
        echo *.user
        echo *.userosscache
        echo *.sln.docstates
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.bak
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="3" (
    echo Creating KiCad .gitignore...
    (
        echo # KiCad
        echo *.bak
        echo *.bck
        echo *-bak
        echo *.kicad_pcb-bak
        echo *.kicad_sch-bak
        echo *-backups/
        echo fp-info-cache
        echo *.kicad_prl
        echo *.lck
        echo ~*.kicad_pcb
        echo ~*.kicad_sch
        echo _autosave-*
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="4" (
    echo Creating MPLAB X + KiCad .gitignore...
    (
        echo # MPLAB X IDE
        echo nbproject/private/
        echo nbproject/Package-*.bash
        echo build/
        echo nbbuild/
        echo dist/
        echo nbdist/
        echo nbactions.xml
        echo nb-configuration.xml
        echo .dep.inc
        echo *.d
        echo *.pre
        echo *.p1
        echo *.lst
        echo *.sym
        echo *.obj
        echo *.o
        echo *.sdb
        echo *.obj.dmp
        echo html/
        echo *.map
        echo *.rlf
        echo *.cof
        echo *.hxl
        echo *.cod
        echo *.mcp
        echo *.mcs
        echo *.mcw
        echo *.dbg
        echo.
        echo # Build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo.
        echo # IDE files
        echo .generated_files/
        echo.
        echo # KiCad
        echo *.bak
        echo *.bck
        echo *-bak
        echo *.kicad_pcb-bak
        echo *.kicad_sch-bak
        echo *-backups/
        echo fp-info-cache
        echo *.kicad_prl
        echo *.lck
        echo ~*.kicad_pcb
        echo ~*.kicad_sch
        echo _autosave-*
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="5" (
    echo Creating Arduino/Teensy + KiCad .gitignore...
    (
        echo # Arduino/Teensy build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo *.map
        echo.
        echo # IDE files
        echo .vscode/
        echo .idea/
        echo *.suo
        echo *.user
        echo *.userosscache
        echo *.sln.docstates
        echo.
        echo # KiCad
        echo *.bak
        echo *.bck
        echo *-bak
        echo *.kicad_pcb-bak
        echo *.kicad_sch-bak
        echo *-backups/
        echo fp-info-cache
        echo *.kicad_prl
        echo *.lck
        echo ~*.kicad_pcb
        echo ~*.kicad_sch
        echo _autosave-*
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="6" (
    echo Creating MPLAB X + Arduino + KiCad .gitignore...
    (
        echo # MPLAB X IDE
        echo nbproject/private/
        echo nbproject/Package-*.bash
        echo build/
        echo nbbuild/
        echo dist/
        echo nbdist/
        echo nbactions.xml
        echo nb-configuration.xml
        echo .dep.inc
        echo *.d
        echo *.pre
        echo *.p1
        echo *.lst
        echo *.sym
        echo *.obj
        echo *.o
        echo *.sdb
        echo *.obj.dmp
        echo html/
        echo *.map
        echo *.rlf
        echo *.cof
        echo *.hxl
        echo *.cod
        echo *.mcp
        echo *.mcs
        echo *.mcw
        echo *.dbg
        echo.
        echo # Build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo.
        echo # Arduino/Teensy IDE files
        echo .vscode/
        echo .idea/
        echo .generated_files/
        echo.
        echo # KiCad
        echo *.bak
        echo *.bck
        echo *-bak
        echo *.kicad_pcb-bak
        echo *.kicad_sch-bak
        echo *-backups/
        echo fp-info-cache
        echo *.kicad_prl
        echo *.lck
        echo ~*.kicad_pcb
        echo ~*.kicad_sch
        echo _autosave-*
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="7" (
    echo Creating MPLAB X + Arduino + KiCad + FreeCAD .gitignore...
    (
        echo # MPLAB X IDE
        echo nbproject/private/
        echo nbproject/Package-*.bash
        echo build/
        echo nbbuild/
        echo dist/
        echo nbdist/
        echo nbactions.xml
        echo nb-configuration.xml
        echo .dep.inc
        echo *.d
        echo *.pre
        echo *.p1
        echo *.lst
        echo *.sym
        echo *.obj
        echo *.o
        echo *.sdb
        echo *.obj.dmp
        echo html/
        echo *.map
        echo *.rlf
        echo *.cof
        echo *.hxl
        echo *.cod
        echo *.mcp
        echo *.mcs
        echo *.mcw
        echo *.dbg
        echo.
        echo # Build outputs
        echo *.hex
        echo *.elf
        echo *.bin
        echo.
        echo # Arduino/Teensy IDE files
        echo .vscode/
        echo .idea/
        echo .generated_files/
        echo.
        echo # KiCad
        echo *.bak
        echo *.bck
        echo *-bak
        echo *.kicad_pcb-bak
        echo *.kicad_sch-bak
        echo *-backups/
        echo fp-info-cache
        echo *.kicad_prl
        echo *.lck
        echo ~*.kicad_pcb
        echo ~*.kicad_sch
        echo _autosave-*
        echo.
        echo # FreeCAD
        echo *.FCStd1
        echo *.FCStd2
        echo *.FCStd3
        echo *.FCStd4
        echo *.FCStd5
        echo *.FCStd6
        echo *.FCStd7
        echo *.FCStd8
        echo *.FCStd9
        echo *_autosave.FCStd
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="8" (
    echo Creating Java .gitignore...
    (
        echo # Java compiled files
        echo *.class
        echo *.jar
        echo *.war
        echo *.ear
        echo.
        echo # IDE files
        echo .idea/
        echo *.iml
        echo .vscode/
        echo .classpath
        echo .project
        echo .settings/
        echo bin/
        echo target/
        echo.
        echo # Build files
        echo build/
        echo out/
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.bak
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="9" (
    echo Creating Python .gitignore...
    (
        echo # Python
        echo __pycache__/
        echo *.py[cod]
        echo *$py.class
        echo *.so
        echo .Python
        echo env/
        echo venv/
        echo ENV/
        echo build/
        echo develop-eggs/
        echo dist/
        echo downloads/
        echo eggs/
        echo .eggs/
        echo lib/
        echo lib64/
        echo parts/
        echo sdist/
        echo var/
        echo wheels/
        echo *.egg-info/
        echo .installed.cfg
        echo *.egg
        echo.
        echo # IDE files
        echo .vscode/
        echo .idea/
        echo *.swp
        echo.
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *~
        echo.
        echo # Backup files
        echo *.bak
        echo *.orig
    ) > .gitignore
)

if "%PROJECT_TYPE%"=="10" (
    echo Creating basic .gitignore...
    (
        echo # OS files
        echo .DS_Store
        echo Thumbs.db
        echo *.swp
        echo *~
        echo.
        echo # Backup files
        echo *.bak
        echo *.orig
        echo.
        echo # Add your custom ignore patterns below:
    ) > .gitignore
    echo NOTE: You should edit .gitignore to add project-specific patterns
)

echo Done.
echo.

REM Add all files
echo Adding files to Git...
git add .
if errorlevel 1 (
    echo ERROR: Failed to add files
    pause
    exit /b 1
)
echo Done.
echo.

REM Show what will be committed
echo Files to be committed:
echo ----------------------------------------
git status --short
echo ----------------------------------------
echo.

set /p CONFIRM="Does this look correct? (Y/N): "
if /i not "%CONFIRM%"=="Y" (
    echo Aborted. You can manually adjust files and run 'git add .' again.
    pause
    exit /b 0
)
echo.

REM Create initial commit
echo Creating initial commit...
if "%DESCRIPTION%"=="" (
    git commit -m "Initial commit"
) else (
    git commit -m "Initial commit: %DESCRIPTION%"
)
if errorlevel 1 (
    echo ERROR: Failed to create commit
    pause
    exit /b 1
)
echo Done.
echo.

REM Add GitHub remote
echo Adding GitHub remote...
git remote add origin https://github.com/craaschelectric/%REPO_NAME%.git
echo Done.
echo.

REM Set main branch
echo Setting branch to main...
git branch -M main
echo Done.
echo.

echo ========================================
echo Setup Complete!
echo ========================================
echo.
echo NEXT STEPS:
echo 1. Create repository on GitHub: https://github.com/new
echo    - Repository name: %REPO_NAME%
echo    - Description: %DESCRIPTION%
echo    - Do NOT initialize with README, .gitignore, or license
echo.
echo 2. Run this command to push your code:
echo    git push -u origin main
echo.
echo 3. When prompted, enter:
echo    - Username: craaschelectric
echo    - Password: [Your Personal Access Token]
echo.
echo Repository is ready in: %CD%
echo ========================================
pause