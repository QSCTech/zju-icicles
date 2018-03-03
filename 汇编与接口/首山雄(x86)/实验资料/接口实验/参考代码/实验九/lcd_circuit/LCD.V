`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:28:19 11/09/2008 
// Design Name: 
// Module Name:    lcd 
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
module lcd(CLK,RST,SEND,LCD_E,LCD_RS,LCD_RW,sf_d,lcd_data,rotate);
		input      	CLK,RST,SEND,rotate;
		input[3:0]  lcd_data;
		output 		LCD_E,LCD_RS,LCD_RW;
		output[3:0] sf_d;

		reg 			k;
		
		reg 			LCD_E1, LCD_E2;
		reg 			LCD_RS1,LCD_RS2;
		reg 			LCD_RW;
		wire 			LCD_E;
		wire			LCD_RS;

		reg[3:0] 	sf_d1, sf_d2;
		wire[3:0] 	sf_d;
		
		wire[31:0] 	qout;
		wire[31:0] 	qout1;
		wire[31:0]	qout2;
		
		assign LCD_E = (k==0)? LCD_E1: LCD_E2;
		assign sf_d  = (k==0)? sf_d1 : sf_d2;
		assign LCD_RS = (k==0)? LCD_RS1 : LCD_RS2;
		
			
		time_1ms m2(CLK,clk_1ms);
		anti m1(CLK,clk_1ms,SEND,send);
		anti m3(CLK,clk_1ms,rotate,ROTATE);
		
		counter count(CLK, RST, qout, 1);
		counter1 count1(CLK, RST, qout1, k, send);
		counter2 count2(CLK, RST, qout2, ROTATE);
		always @(posedge CLK)begin
			if(RST)begin
				LCD_RS1 = 0;
				LCD_RW <= 0;
				k <= 0;
			end
			//initial and configure LCD
			else if(k == 0)begin
				//initial LCD:
				//ab
				if(qout[31:0] == 750000)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd3;
				end
				if(qout[31:0] == 750012)begin		
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//cd
				if(qout[31:0] == 955012)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd3;
				end
				if(qout[31:0] == 955024)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//ef
				if(qout[31:0] == 960024)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd3;
				end
				if(qout[31:0] == 960036)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//gh
				if(qout[31:0] == 962036)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd2;
				end
				if(qout[31:0] == 962048)begin
						sf_d1 <= 0;
						LCD_E1 <= 0;
				end
				//configure LCD:
				//iA
				if(qout[31:0] == 964048)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd2;
				end
				if(qout[31:0] == 964060)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 964110)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd8;
				end
				if(qout[31:0] == 964122)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//B
				if(qout[31:0] == 966122)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd0;
				end
				if(qout[31:0] == 966134)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 966184)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd6;
				end
				if(qout[31:0] == 966196)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//C
				if(qout[31:0] == 968196)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd0;
				end
				if(qout[31:0] == 968208)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 968258)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd12;
				end
				if(qout[31:0] == 968270)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				//D
				if(qout[31:0] == 970270)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd0;
				end
				if(qout[31:0] == 970282)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 970332)begin
						LCD_E1 <= 1;
						sf_d1 <= 4'd1;
				end
				if(qout[31:0] == 970344)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				
				//set ddram address
				if(qout[31:0] == 1052344)begin
						LCD_E1 <=1;
						sf_d1 <= 4'b1000;
				end
				if(qout[31:0] == 1052356)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 1052406)begin
						LCD_E1 <= 1;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 1052418)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
				end
				if(qout[31:0] == 1054418)begin
						LCD_E1 <= 0;
						sf_d1 <= 0;
						k <= 1;
						LCD_RS1 = 1;
				end
			end
		end
		
		//display and rotate control
		always @(posedge CLK)begin
			if(k==1)begin
				if(ROTATE)begin
					LCD_RS2 = 0;
					if(qout2[31:0] < 12)begin
							LCD_E2 <=1;
							sf_d2 <= 4'b0001;
					end
					if(qout2[31:0] == 12)begin
							LCD_E2 <= 0;
							sf_d2 <= 0;
					end
					if(qout2[31:0] == 62)begin
							LCD_E2 <= 1;
							sf_d2 <= 4'b1100;
					end
					if(qout2[31:0] == 74)begin
							LCD_E2 <= 0;
							sf_d2 <= 0;
					end
				end
				else begin
					LCD_RS2 = 1;
					if(qout1[31:0] < 12)begin
							LCD_E2 <=1;
							sf_d2 <= 4'b0100;
					end
					if(qout1[31:0] == 12)begin
							LCD_E2 <= 0;
							sf_d2 <= 0;
					end
					if(qout1[31:0] == 62)begin
							LCD_E2 <= 1;
							sf_d2 <= lcd_data;
					end
					if(qout1[31:0] == 74)begin
							LCD_E2 <= 0;
							sf_d2 <= 0;
					end
				end
			end
		end
endmodule

module counter(CLK,RST,qout,k);
	input  		CLK,RST,k;
	output 		qout;
	
	reg[31:0] 	qout;
	
	always@(posedge CLK)begin
		if(RST)
			qout = 0;
		else if(k == 1)
			qout[31:0]=qout[31:0]+1;
	end
endmodule

module counter1(CLK,RST,qout,k,send);
	input  		CLK,RST,k,send;
	output 		qout;
	
	reg[31:0] 	qout;
	
	always@(posedge CLK)begin
		if(RST)
			qout = 74;
		else if(send)
			qout = 0;
		else if(k == 1)
			qout[31:0]=qout[31:0]+1;
	end
endmodule

module counter2(CLK,RST,qout2,rotate);
	input  		CLK,RST,rotate;
	output 		qout2;
	
	reg[31:0] 	qout2;
	reg[15:0]	cnt;
	always@(posedge CLK)begin
		if(RST)
			cnt = 0;
		else cnt = cnt + 1;
	end
	
	always@(posedge cnt[15])begin
		if(RST)
			qout2 = 0;
		else if(rotate)begin
			if(qout2[31:0]==74)
				qout2 = 0;
			else
				qout2[31:0]=qout2[31:0]+1;
		end
		else qout2 = 0;
	end
endmodule

module time_1ms(clk,clk_1ms);
input clk;
output clk_1ms;
wire clk;
reg clk_1ms;
reg [15:0] cnt;

initial begin
   cnt[15:0]<=0;
	end
always@(posedge clk) begin
   if(cnt>=49999) begin
	   cnt<=0;
		clk_1ms<=1;
	  end
	else begin
	  cnt<=cnt+1;
	  clk_1ms<=0;
	  end
end

endmodule

module anti(clk,clk_1ms,btn_in,btn_out);
input clk;
input clk_1ms;
input[3:0] btn_in;
output[3:0] btn_out;
wire[3:0] btn_in;
reg[3:0] btn_out;
reg[3:0] cnt_aj;
reg[3:0] btn_old;

always@(posedge clk) begin
   if(btn_in!=btn_old) begin
	  cnt_aj<=4'b0000;
	  btn_old<=btn_in;
	end
	else begin
	  if(clk_1ms) begin
	  if(cnt_aj==4'b1111) begin
	    cnt_aj<=4'b0000;
		 btn_out<=btn_in;
		 end
	  cnt_aj<=cnt_aj+1;
	  end
	end
end
endmodule
