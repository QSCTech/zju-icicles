`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:26:15 12/20/2008 
// Design Name: 
// Module Name:    ex7 
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
module ex7(clk, rst, sel, ps2_clk, ps2_data, out);
	input clk;
	input rst;
	input sel;
	input ps2_clk;
	input ps2_data;
	output[7:0] out;

	reg[3:0] i;
	reg[1:0] stored_ps2_clk;
	reg[10:0] data,data_pre;
	reg[7:0] ascii;
	reg shift_on;

	wire[7:0] out;
	wire falg_fallingedge;
	wire[8:0] key_pressed;

	assign out = sel ? data[8:1] : ascii;
	assign flag_fallingedge = (stored_ps2_clk[1:0] == 2'b10);

	always @(posedge clk)
		stored_ps2_clk <= {stored_ps2_clk[0],ps2_clk};

	always @(posedge clk) begin
		if (rst)
			i <= 0;
		else begin
			if (flag_fallingedge) begin
				if (i == 0) begin
					data_pre <= data;
					data <= 11'b11111111111;
				end
				data[i] <= ps2_data;
				if (i < 10)
					i <= i + 1;
				else begin
					i <= 0;
					if (data[8:1] == 8'b00010010)
						shift_on <= (data_pre[8:1] == 8'b11110000) ? 0 : 1;
					else if (data[8:1] == 8'b01011001)
						shift_on <= (data_pre[8:1] == 8'b11110000) ? 0 : 1;
				end
			end					
		end	 
	end
	 
//	always @(data) begin
//		if (data[8:1] == 8'b00010010)
//			shift_on <= (data_pre[8:1] == 8'b11110000) ? 0 : 1;
//		else if (data[8:1] == 8'b01011001)
//			shift_on <= (data_pre[8:1] == 8'b11110000) ? 0 : 1;
//	end
	
	assign key_pressed = {3'b000, shift_on, data[8:1]};
	always @(key_pressed) begin
		case (key_pressed)
			12'h?29 : ascii <= 8'h20;  // Space
			12'h116 : ascii <= 8'h21;  // !
			12'h152 : ascii <= 8'h22;  // "
			12'h126 : ascii <= 8'h23;  // #
			12'h125 : ascii <= 8'h24;  // $
			12'h12e : ascii <= 8'h25;  // %
			12'h13d : ascii <= 8'h26;  // &
			12'h052 : ascii <= 8'h27;  // '
			12'h146 : ascii <= 8'h28;  // (
			12'h145 : ascii <= 8'h29;  // )
			12'h13e : ascii <= 8'h2a;  // *
			12'h155 : ascii <= 8'h2b;  // +
			12'h041 : ascii <= 8'h2c;  // ,
			12'h04e : ascii <= 8'h2d;  // -
			12'h049 : ascii <= 8'h2e;  // .
			12'h04a : ascii <= 8'h2f;  // /
			12'h045 : ascii <= 8'h30;  // 0
			12'h016 : ascii <= 8'h31;  // 1
			12'h01e : ascii <= 8'h32;  // 2
			12'h026 : ascii <= 8'h33;  // 3
			12'h025 : ascii <= 8'h34;  // 4
			12'h02e : ascii <= 8'h35;  // 5
			12'h036 : ascii <= 8'h36;  // 6
			12'h03d : ascii <= 8'h37;  // 7
			12'h03e : ascii <= 8'h38;  // 8
			12'h046 : ascii <= 8'h39;  // 9
			12'h14c : ascii <= 8'h3a;  // :
			12'h04c : ascii <= 8'h3b;  // ;
			12'h141 : ascii <= 8'h3c;  // <
			12'h055 : ascii <= 8'h3d;  // =
			12'h149 : ascii <= 8'h3e;  // >
			12'h14a : ascii <= 8'h3f;  // ?
			12'h11e : ascii <= 8'h40;  // @
			12'h11c : ascii <= 8'h41;  // A
			12'h132 : ascii <= 8'h42;  // B
			12'h121 : ascii <= 8'h43;  // C
			12'h123 : ascii <= 8'h44;  // D
			12'h124 : ascii <= 8'h45;  // E
			12'h12b : ascii <= 8'h46;  // F
			12'h134 : ascii <= 8'h47;  // G
			12'h133 : ascii <= 8'h48;  // H
			12'h143 : ascii <= 8'h49;  // I
			12'h13b : ascii <= 8'h4a;  // J
			12'h142 : ascii <= 8'h4b;  // K
			12'h14b : ascii <= 8'h4c;  // L
			12'h13a : ascii <= 8'h4d;  // M
			12'h131 : ascii <= 8'h4e;  // N
			12'h144 : ascii <= 8'h4f;  // O
			12'h14d : ascii <= 8'h50;  // P
			12'h115 : ascii <= 8'h51;  // Q
			12'h12d : ascii <= 8'h52;  // R
			12'h11b : ascii <= 8'h53;  // S
			12'h12c : ascii <= 8'h54;  // T
			12'h13c : ascii <= 8'h55;  // U
			12'h12a : ascii <= 8'h56;  // V
			12'h11d : ascii <= 8'h57;  // W
			12'h122 : ascii <= 8'h58;  // X
			12'h135 : ascii <= 8'h59;  // Y
			12'h11a : ascii <= 8'h5a;  // Z
			12'h054 : ascii <= 8'h5b;  // [
			12'h05d : ascii <= 8'h5c;  // 
			12'h05b : ascii <= 8'h5d;  // ]
			12'h136 : ascii <= 8'h5e;  // ^
			12'h14e : ascii <= 8'h5f;  // _
			12'h00e : ascii <= 8'h60;  // `
			12'h01c : ascii <= 8'h61;  // a
			12'h032 : ascii <= 8'h62;  // b
			12'h021 : ascii <= 8'h63;  // c
			12'h023 : ascii <= 8'h64;  // d
			12'h024 : ascii <= 8'h65;  // e
			12'h02b : ascii <= 8'h66;  // f
			12'h034 : ascii <= 8'h67;  // g
			12'h033 : ascii <= 8'h68;  // h
			12'h043 : ascii <= 8'h69;  // i
			12'h03b : ascii <= 8'h6a;  // j
			12'h042 : ascii <= 8'h6b;  // k
			12'h04b : ascii <= 8'h6c;  // l
			12'h03a : ascii <= 8'h6d;  // m
			12'h031 : ascii <= 8'h6e;  // n
			12'h044 : ascii <= 8'h6f;  // o
			12'h04d : ascii <= 8'h70;  // p
			12'h015 : ascii <= 8'h71;  // q
			12'h02d : ascii <= 8'h72;  // r
			12'h01b : ascii <= 8'h73;  // s
			12'h02c : ascii <= 8'h74;  // t
			12'h03c : ascii <= 8'h75;  // u
			12'h02a : ascii <= 8'h76;  // v
			12'h01d : ascii <= 8'h77;  // w
			12'h022 : ascii <= 8'h78;  // x
			12'h035 : ascii <= 8'h79;  // y
			12'h01a : ascii <= 8'h7a;  // z
			12'h154 : ascii <= 8'h7b;  // {
			12'h15d : ascii <= 8'h7c;  // |
			12'h15b : ascii <= 8'h7d;  // }
			12'h10e : ascii <= 8'h7e;  // ~
			default : ascii <= 8'h00;  //used for unlisted characters.
		endcase
	end
endmodule
