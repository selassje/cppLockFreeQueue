for /f %%F in ('dir /s /b /a-d ^| findstr /vile ".bat"') do del /A /q /s "%%F"
REM for /f %%F in ('dir /s /b /a-d ^| findstr /vile ".bat"') do del /A:H /q "%%F" del /s /q "%%F"
for /f %%p in ('dir /A:D /b') do rd /s /q "%%p"