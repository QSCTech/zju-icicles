`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:55:41 12/20/2008 
// Design Name: 
// Module Name:    ex6 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ex6(clk, rst, ps2_clk, ps2_data, data);
	input clk;
	input rst;
	input ps2_clk;
	input ps2_data;
	output[10:0] data;

	reg[3:0] i;
	reg[1:0] stored_ps2_clk;
	reg[10:0] data;
	wire flag_fallingedge;

	assign flag_fallingedge = (stored_ps2_clk[1:0] == 2'b10);

	always @(posedge clk)
		stored_ps2_clk <= {stored_ps2_clk[0],ps2_clk};

	always @(posedge clk) begin
		if (rst)
			i <= 0;
		else begin
			if (flag_fallingedge) begin
				data[i] <= ps2_data;
				if (i < 10)
					i <= i + 1;
				else
					i <= 0;
			end					
		end	 
	end

endmodule
