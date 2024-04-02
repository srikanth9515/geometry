# Verilog source file directory
VERILOG_DIR = /home/sujith/esp32-fpga/fpga/rtl

# Verilog source files
VERILOG_SRC = $(VERILOG_DIR)/main.v
TESTBENCH_SRC = $(VERILOG_DIR)/testbench.v

# Simulation executable
SIM_EXEC = simulation

# Simulation output file
SIM_OUTPUT = output.txt

# Default target
all: compile simulate generate_output

# Compile Verilog source files and testbench
compile:
	iverilog -o $(SIM_EXEC) -g2012 $(TESTBENCH_SRC) $(VERILOG_SRC)

# Run simulation
simulate:
	./$(SIM_EXEC)

# Generate output text file
generate_output:
	@echo "Generating $(SIM_OUTPUT)..."
	@echo "$(SIM_OUTPUT) generated with content:"
	@cat $(SIM_OUTPUT)

# Clean generated files
clean:
	rm -f $(SIM_EXEC) $(SIM_OUTPUT)

.PHONY: all compile simulate generate_output clean

