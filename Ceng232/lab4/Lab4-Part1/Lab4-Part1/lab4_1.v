`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);

	// write your ROM code here



endmodule

module Difference_RAM (
input mode,
input [2:0] addr,
input [7:0] dataIn,
input [7:0] mask,
input CLK,
output reg [7:0] dataOut);

	// write your XOR_RAM code here


endmodule


module EncodedMemory (
input mode,
input [2:0] index,
input [7:0] number,
input CLK,
output [7:0] result);

	wire [7:0] mask;

	ROM R(index, mask);
	Difference_RAM DR(mode, index, number, mask, CLK, result);

endmodule


