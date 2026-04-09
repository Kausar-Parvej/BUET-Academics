# M/M/1 Queue Simulation Runner Script

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  M/M/1 Queue Simulation" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Compile the program
Write-Host "Compiling..." -ForegroundColor Yellow
gcc -o mm1_queue 2005076_mm1_queue.cpp lcgrand.c -lm

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful!" -ForegroundColor Green
    Write-Host ""
    
    # Run the program
    Write-Host "Running simulation..." -ForegroundColor Yellow
    .\mm1_queue.exe
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Simulation completed successfully!" -ForegroundColor Green
        Write-Host ""
        
        # Display results
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host "  Output File 1: Summary Statistics" -ForegroundColor Cyan
        Write-Host "========================================" -ForegroundColor Cyan
        Get-Content mm1_out1.txt
        Write-Host ""
        
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host "  Output File 2: First 30 Events" -ForegroundColor Cyan
        Write-Host "========================================" -ForegroundColor Cyan
        Get-Content mm1_out2.txt -Head 30
        Write-Host ""
        Write-Host "... (see mm1_out2.txt for complete event log)" -ForegroundColor Gray
        Write-Host ""
        
        Write-Host "Output files created:" -ForegroundColor Green
        Write-Host "  - mm1_out1.txt (summary)" -ForegroundColor White
        Write-Host "  - mm1_out2.txt (detailed events)" -ForegroundColor White
    }
    else {
        Write-Host "Error: Simulation failed!" -ForegroundColor Red
    }
}
else {
    Write-Host "Error: Compilation failed!" -ForegroundColor Red
}

Write-Host ""
