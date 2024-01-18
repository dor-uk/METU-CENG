`timescale 1ns / 1ps

//
// NOTE: This is a sample testbench, provided to you as a guidance.
//

module testbench_ram(
    );

	reg mode;
	reg	[2:0] index;
	reg	[7:0] number;
	reg clk;
	wire result;

	// Instantiate the Unit Under Test (UUT)
   EncodedMemory uut(
		mode,
		index,
		number,
		clk,
		result
	);

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
   	initial clk = 0;
	always #5 clk = ~clk;

	initial begin

		//... you may add your tests here

		$finish;

	end

endmodule
