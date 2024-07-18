@echo off
echo Building Prism Launcher
cmake --build build --config Debug -- /p:UseMultiToolTask=true /p:EnforceProcessCountAcrossBuilds=true
echo Installing Prism Launcher
cmake --install build --config Debug