`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:48:58 11/01/2008 
// Design Name: 
// Module Name:    SP2 
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
module PS2(clk, rst, ps2_clk, ps2_data, data2);

input 	    clk, rst, ps2_clk , ps2_data;
output[10:0] data2;


reg [3:0] 	 i;
reg [10:0] 	 data;
reg [10:0] 	 data2;


reg [2:0] 	 ps2_clkr;
always @(posedge clk) 
	ps2_clkr <= {ps2_clkr[1:0], ps2_clk}; // 准备读取接口电平信号

//确定上升沿和下降沿
wire ps2_clk_risingedge  = (ps2_clkr[2:1]==2'b01); 
wire ps2_clk_fallingedge = (ps2_clkr[2:1]==2'b10);


always @(posedge clk)
if(rst)
	i <= 0;
else begin
	if(ps2_clk_fallingedge)begin
		data2[i] <= data[i];   // 输出上一位数据
		data[i]  <= ps2_data;  //读入当前接口处的数据位
		if(i<10) 			//连续读取十一次数据位方接受完当前数据包
			i <= i+1;
		else 
			i <= 0;
	end
end

endmodule

